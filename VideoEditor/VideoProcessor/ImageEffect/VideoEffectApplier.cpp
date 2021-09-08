#include "VideoEffectApplier.h"

#include <filesystem>

namespace fs = std::filesystem;


VideoEffectApplier::VideoEffectApplier(std::string const& destDirectoryPath) :
	_destDirectoryPath(destDirectoryPath)
{
}

void VideoEffectApplier::registerEffect(AbstractVideoEffect const& effect, cv::Point2i pos)
{
	_entries.emplace_back(effect, pos);
}

void VideoEffectApplier::process(std::string sourcePath, std::function<void(float)> progressChanged)
{
	_isRunning = true;

	cv::VideoCapture inputVideoCapture(sourcePath);
	std::string destPath = getDestinationFilePath(sourcePath);
	int const frameWidth = inputVideoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
	int const frameHeight = inputVideoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
	double const fps = inputVideoCapture.get(cv::CAP_PROP_FPS);
	int const fourcc = inputVideoCapture.get(cv::CAP_PROP_FOURCC);
	cv::VideoWriter outputVideoWriter(destPath, fourcc, fps, cv::Size(frameWidth, frameHeight));

	assert(outputVideoWriter.isOpened());

	int const frameCount = inputVideoCapture.get(cv::CAP_PROP_FRAME_COUNT);
	int const progressStep = frameCount / 100;

	cv::Mat frame;

	for (int i = 0; i < frameCount; ++i) {
		inputVideoCapture >> frame;

		if (frame.empty()) {
			break;
		}

		for (auto const& applierEntry : _entries) {
			applierEntry.VideoEffect.get().applyToImage(frame, applierEntry.Position);
		}
		outputVideoWriter.write(frame);

		if (progressChanged && (i % progressStep == 0)) {
			float const progress = static_cast<float>(i) / progressStep;
			progressChanged(progress);
		}
	}

	inputVideoCapture.release();
	outputVideoWriter.release();
	_isRunning = false;
}

void VideoEffectApplier::abortProcessing()
{
	_isRunning = false;
}

std::string VideoEffectApplier::getDestinationFilePath(std::string const& sourcePath) const
{
	fs::path const srcP = sourcePath;
	fs::path const filename = srcP.filename();
	fs::path const destDirP(_destDirectoryPath);
	fs::path destP = destDirP;
	destP /= filename;
	return destP.string();
}