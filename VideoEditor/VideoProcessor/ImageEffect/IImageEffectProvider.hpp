#ifndef IIMAGEEFFECTPROVIDER_H
#define IIMAGEEFFECTPROVIDER_H

#include <opencv2/opencv.hpp>

class IImageEffectProvider
{
public:
    virtual ~IImageEffectProvider() = 0;

public:
    virtual cv::Mat const & getImageEffect() const = 0;
};

#endif // IIMAGEEFFECTPROVIDER_H
