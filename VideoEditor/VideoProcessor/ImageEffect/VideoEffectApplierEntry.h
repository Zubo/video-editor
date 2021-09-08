#ifndef VIDEOEFFECTAPPLIERENTRY_H
#define VIDEOEFFECTAPPLIERENTRY_H

#include <functional>

#include <opencv2/opencv.hpp>

#include <VideoProcessor/ImageEffect/AbstractVideoEffect.hpp>

struct VideoEffectApplierEntry
{
public:
    VideoEffectApplierEntry(AbstractVideoEffect const & videoEffect, cv::Point2i pos);

    std::reference_wrapper<const AbstractVideoEffect> VideoEffect;
    cv::Point2i Position;
};

#endif // VIDEOEFFECTAPPLIERENTRY_H
