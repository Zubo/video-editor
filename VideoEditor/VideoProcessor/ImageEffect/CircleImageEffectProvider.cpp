#include <VideoProcessor/ImageEffect/CircleImageEffectProvider.hpp>

#include <opencv2/opencv.hpp>

CircleImageEffectProvider CircleImageEffectProvider::create(int const radius, cv::Scalar const & firstColor, cv::Scalar const & secondColor)
{
    CircleImageEffectProvider circleShapeProvider{ radius };
    cv::Point const center{ radius, radius };

    for (int i = 0; i < radius; ++i) {
        float const transitionPercent = (static_cast<float>(i) / radius);
        cv::Scalar color = (transitionPercent * firstColor) + ((1.0F - transitionPercent) * secondColor);
        cv::circle(circleShapeProvider._effect, center, i, color, 1);
    }

    return circleShapeProvider;
}

CircleImageEffectProvider::CircleImageEffectProvider(int const radius) :
    _effect(radius * 2, radius * 2, CV_8UC4, cv::Scalar::all(0))
{
}

cv::Mat const & CircleImageEffectProvider::getImageEffect() const
{
    return _effect;
}
