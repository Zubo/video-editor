#include "VideoThumbnailProvider.hpp"

cv::Mat VideoThumbnailProvider::getThumbnail(std::string const& videoPath)
{
    cv::VideoCapture videoCapture;

	videoCapture.open(videoPath);

	bool const captureOpen = videoCapture.isOpened();

    if (!captureOpen) {
        return cv::Mat(100, 100, CV_8UC4);
    }

	int const frameCount{ static_cast<int>(videoCapture.get(cv::CAP_PROP_FRAME_COUNT)) };

	cv::Mat thumbnail;

	for (int i = 0; i < frameCount / 2; ++i) {
		videoCapture >> thumbnail;
	}

	cv::rotate(thumbnail, thumbnail, cv::ROTATE_90_COUNTERCLOCKWISE);

	return thumbnail;
}
