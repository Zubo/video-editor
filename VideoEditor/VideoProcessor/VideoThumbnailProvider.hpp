#ifndef VIDEOTHUMBNAILPROVIDER_HPP
#define VIDEOTHUMBNAILPROVIDER_HPP

#include <string>

#include <opencv2/opencv.hpp>

class VideoThumbnailProvider
{
public:
	static cv::Mat getThumbnail(std::string const & videoPath);
};

#endif // VIDEOTHUMBNAILPROVIDER_HPP
