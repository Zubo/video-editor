#include "VideoThumbnailProvider.hpp"

cv::Mat VideoThumbnailProvider::getThumbnail(std::string const& videoPath)
{
    cv::VideoCapture videoCapture;

    char const * p = videoPath.c_str();
    videoCapture.open(p);

	bool const captureOpen = videoCapture.isOpened();

    if (!captureOpen) {
        return cv::Mat(100, 100, CV_8UC4);
    }

    int const frameCount{ static_cast<int>(videoCapture.get(cv::CAP_PROP_FRAME_COUNT)) };

	cv::Mat thumbnail;
    int const frameIndex = (frameCount > 1000) ? 1000 : frameCount / 2;

    for (int i = 0; i < frameIndex; ++i) {
		videoCapture >> thumbnail;
	}

	return thumbnail;
}
