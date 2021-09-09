#ifndef VIDEOEFFECTAPPLIERENTRY_H
#define VIDEOEFFECTAPPLIERENTRY_H

#include <functional>
#include <memory>

#include <opencv2/opencv.hpp>

#include <BLL/VideoProcessor/ImageEffect/AbstractVideoEffect.hpp>

class VideoEffectApplierEntry
{
public:
    VideoEffectApplierEntry(std::unique_ptr<AbstractVideoEffect> videoEffectUnique, cv::Point2i pos);
    VideoEffectApplierEntry(VideoEffectApplierEntry const& other);

public:
    AbstractVideoEffect & getEffect() const;
    cv::Point2i const getPosition() const;

private:
    std::unique_ptr<AbstractVideoEffect> _videoEffectUnique;
    cv::Point2i _position;
    float _timeSinceLastRandomizaion = 0.0F;
};

#endif // VIDEOEFFECTAPPLIERENTRY_H
