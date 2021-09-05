#ifndef CIRCLEIMAGEEFFECTPROVIDER_H
#define CIRCLEIMAGEEFFECTPROVIDER_H

#include <VideoProcessor/ImageEffect/IImageEffectProvider.hpp>

class CircleImageEffectProvider : public IImageEffectProvider
{
public:
    static CircleImageEffectProvider create(int const radius, cv::Scalar const & firstColor, cv::Scalar const & secondColor);

private:
    CircleImageEffectProvider(int const radius);

public:
    cv::Mat const & getImageEffect() const override;

private:
    cv::Mat _effect;
};

#endif // CIRCLEIMAGEEFFECTPROVIDER_H
