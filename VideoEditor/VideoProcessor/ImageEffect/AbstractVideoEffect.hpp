#ifndef IIMAGEEFFECTPROVIDER_H
#define IIMAGEEFFECTPROVIDER_H

#include <functional>
#include <vector>

#include <opencv2/opencv.hpp>

class AbstractVideoEffect
{
public:
    virtual ~AbstractVideoEffect() = 0;

public:
	virtual cv::Mat const& getImageEffect() const = 0;
    void applyToImage(cv::Mat& img, cv::Point2i const pos) const;
    virtual void randomize() = 0;
};

#endif // IIMAGEEFFECTPROVIDER_H
