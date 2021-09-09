#include "VideoEffectApplier.h"

#include <exception>
#include <filesystem>

#include <FilesystemPathUtils.h>
#include <ThumbnailGenerator.h>

namespace fs = std::filesystem;


VideoEffectApplier::VideoEffectApplier(std::string const& destDirectoryPath) :
	_destDirectoryPath(destDirectoryPath)
{
}

void VideoEffectApplier::registerEffect(std::unique_ptr<AbstractVideoEffect> videoEffectUnique, cv::Point2i pos, float randomizationInterval)
{
	_entries.emplace_back(std::move(videoEffectUnique), pos, randomizationInterval);
}

void VideoEffectApplier::process(std::string sourcePath, std::function<void(float)> progressChanged, std::function<void()> onAborted)
{
	_isRunning = true;

	cv::VideoCapture inputVideoCapture(sourcePath);
	std::string destPath = getDestinationFilePath(sourcePath);
	int const frameWidth = inputVideoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
	int const frameHeight = inputVideoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
	double const fps = inputVideoCapture.get(cv::CAP_PROP_FPS);
	int const fourcc = inputVideoCapture.get(cv::CAP_PROP_FOURCC);
    cv::VideoWriter outputVideoWriter(destPath, fourcc, fps, cv::Size(frameWidth, frameHeight));

	if (!outputVideoWriter.isOpened()) {
		throw std::runtime_error("Error: Could not open output stream for processed video!");
	}

	deleteExistingThumbnailForVideo(destPath);

    int const frameCount = inputVideoCapture.get(cv::CAP_PROP_FRAME_COUNT);

	cv::Mat frame;
    float lastFrameTimestamp = 0.0F;
	for (int i = 0; i < frameCount; ++i) {
        if (!_isRunning) {
			if (onAborted) {
				onAborted();
			}
            break;
        }

		inputVideoCapture >> frame;

		if (frame.empty()) {
			break;
		}

        double const posMiliseconds = inputVideoCapture.get(cv::CAP_PROP_POS_MSEC);
        float const deltaTime = static_cast<float>(posMiliseconds - lastFrameTimestamp);
		for (auto& applierEntry : _entries) {
            applierEntry.update(deltaTime);
			applierEntry.getEffect().applyToImage(frame, applierEntry.getPosition());
		}
		outputVideoWriter.write(frame);

        if (progressChanged && (i % 100 == 0)) {
            float const progress = static_cast<float>(i) / frameCount;
			progressChanged(progress);
		}

        lastFrameTimestamp = posMiliseconds;
	}

	inputVideoCapture.release();
	outputVideoWriter.release();
	_isRunning = false;
}

void VideoEffectApplier::abortProcessing()
{
	_isRunning = false;
}

void VideoEffectApplier::deleteExistingThumbnailForVideo(std::string const& videoPath)
{
	fs::path p = fs::path(videoPath);
	p.replace_extension(ThumbnailGenerator::THUMBNAIL_EXTENSION);

	if (fs::exists(p)) {
		fs::remove(p);
	}
}

std::string VideoEffectApplier::getDestinationFilePath(std::string const& sourcePath) const
{
	fs::path const srcP = sourcePath;
	fs::path const destDirP(_destDirectoryPath);
	fs::path const destP = FilesystemPathUtils::replaceFilePathExtension(srcP, destDirP);

	return destP.string();
}
