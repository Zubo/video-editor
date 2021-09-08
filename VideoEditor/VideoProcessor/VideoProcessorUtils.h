#ifndef VIDEOPROCESSORUTILS_H
#define VIDEOPROCESSORUTILS_H

#include <string>

#include <opencv2/opencv.hpp>

class VideoProcessorUtils
{
public:
	static cv::Point2i getVideoResolution(std::string const& videoPath);

public:
	VideoProcessorUtils() = delete;
};

#endif // VIDEOPROCESSORUTILS_H
