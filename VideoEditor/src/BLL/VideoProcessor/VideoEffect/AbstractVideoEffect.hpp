#ifndef IABSTRACTVIDEOEFFECT_H
#define IABSTRACTVIDEOEFFECT_H

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
    virtual void update(float deltaTime) = 0;
    virtual std::unique_ptr<AbstractVideoEffect> clone() const = 0;
};

#endif // IABSTRACTVIDEOEFFECT_H
