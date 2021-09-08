#ifndef VIDEOEFFECTAPPLIERENTRY_H
#define VIDEOEFFECTAPPLIERENTRY_H

#include <functional>
#include <memory>

#include <opencv2/opencv.hpp>

#include <VideoProcessor/ImageEffect/AbstractVideoEffect.hpp>

class VideoEffectApplierEntry
{
public:
    VideoEffectApplierEntry(std::unique_ptr<AbstractVideoEffect> videoEffectUnique, cv::Point2i pos, float const randomizationInterval);
    VideoEffectApplierEntry(VideoEffectApplierEntry const& other);

public:
    AbstractVideoEffect & getEffect() const;
    cv::Point2i const getPosition() const;
    void update(float const deltaTime);

private:
    std::unique_ptr<AbstractVideoEffect> _videoEffectUnique;
    cv::Point2i _position;
    float _randomizationInterval;
    float _timeSinceLastRandomizaion = 0.0F;
};

#endif // VIDEOEFFECTAPPLIERENTRY_H