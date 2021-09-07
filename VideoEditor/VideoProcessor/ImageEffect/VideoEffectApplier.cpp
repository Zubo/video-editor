#include "VideoEffectApplier.h"

void VideoEffectApplier::registerEffect(AbstractVideoEffect const& effect, cv::Point2i pos)
{
	_entries.emplace_back(effect, pos);
}

void VideoEffectApplier::process(std::string sourcePath, std::string destinationPath, std::function<void(float)> progressChanged)
{
	_isRunning = true;

	cv::VideoCapture inputVideoCapture;
	cv::VideoCapture outputVideoCapture;

	float val = 0.0F;

	while (val < 1.0F && _isRunning) {
		val += 0.001;

		if (progressChanged) {
			progressChanged(val);
		}
	}

	_isRunning = false;
}

void VideoEffectApplier::abortProcessing()
{
	_isRunning = false;
}