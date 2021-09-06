#include <VideoProcessor/ImageEffect/CircleImageEffectProvider.hpp>

#include <opencv2/opencv.hpp>

CircleImageEffectProvider CircleImageEffectProvider::create(int const radius, cv::Scalar const & firstColor, cv::Scalar const & secondColor)
{
    CircleImageEffectProvider circleShapeProvider{ radius };
    cv::Point const center{ circleShapeProvider._effect.cols / 2, circleShapeProvider._effect.rows / 2 };

    for (int i = 0; i < radius; ++i) {
        float const transitionPercent = (static_cast<float>(i) / radius);
        cv::Scalar color = (transitionPercent * firstColor) + ((1.0F - transitionPercent) * secondColor);
        cv::circle(circleShapeProvider._effect, center, i, color, 2);
    }

    return circleShapeProvider;
}

CircleImageEffectProvider CircleImageEffectProvider::create()
{
    return create(50, cv::Scalar(0, 0, 255, 255), cv::Scalar(0, 255, 0, 255));
}

CircleImageEffectProvider::CircleImageEffectProvider(int const radius) :
    _effect(radius * 2.1F, radius * 2.1F, CV_8UC4, cv::Scalar::all(0))
{
}

cv::Mat const & CircleImageEffectProvider::getImageEffect() const
{
    return _effect;
}
