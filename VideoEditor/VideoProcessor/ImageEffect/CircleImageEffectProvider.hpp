#ifndef CIRCLEIMAGEEFFECTPROVIDER_H
#define CIRCLEIMAGEEFFECTPROVIDER_H

#include <VideoProcessor/ImageEffect/AbstractVideoEffect.hpp>

class CircleImageEffectProvider : public AbstractVideoEffect
{
public:
    static CircleImageEffectProvider create(int const radius = DEFAULT_RADIUS);

private:
    CircleImageEffectProvider(int const radius);

public:
	cv::Mat const& getImageEffect() const override;
    void randomize() override;

private:
    void updateEffect(cv::Scalar const& firstColor, cv::Scalar const& secondColor);

private:
    int _radius;
    cv::Mat _effect;

private:
    static constexpr int DEFAULT_RADIUS = 50;
};

#endif // CIRCLEIMAGEEFFECTPROVIDER_H
