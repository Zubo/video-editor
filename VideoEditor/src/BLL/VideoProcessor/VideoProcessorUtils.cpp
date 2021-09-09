#include <BLL/VideoProcessor/VideoProcessorUtils.h>

cv::Point2i VideoProcessorUtils::getVideoResolution(std::string const& videoPath)
{
	cv::VideoCapture videoCapture(videoPath);

	if (!videoCapture.isOpened()) {
		return {};
	}

	double const width{ videoCapture.get(cv::CAP_PROP_FRAME_WIDTH) };
	double const height{ videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT) };

	return cv::Point2i(static_cast<int>(width), static_cast<int>(height));
}
