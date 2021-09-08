#include <cstdlib>

#include <VideoProcessor/ImageEffect/CircleImageEffectProvider.hpp>

#include <opencv2/opencv.hpp>

CircleImageEffectProvider CircleImageEffectProvider::create(int const radius)
{
    CircleImageEffectProvider circleShapeProvider{ radius };
	circleShapeProvider.randomize();

    return circleShapeProvider;
}
CircleImageEffectProvider::CircleImageEffectProvider(int const radius) :
	_radius(radius),
    _effect(_radius * 2.1F, _radius * 2.1F, CV_8UC4, cv::Scalar::all(0))
{
}

CircleImageEffectProvider::CircleImageEffectProvider(CircleImageEffectProvider const& other) :
	_radius(other._radius),
	_effect(other._effect.clone())
{
}

cv::Mat const & CircleImageEffectProvider::getImageEffect() const
{
    return _effect;
}

void CircleImageEffectProvider::randomize()
{
	cv::Scalar firstColor(std::rand() % 256, std::rand() % 256, std::rand() % 256, 255);
	cv::Scalar secondColor(std::rand() % 256, std::rand() % 256, std::rand() % 256, 255);
	updateEffect(firstColor, secondColor);
}

std::unique_ptr<AbstractVideoEffect> CircleImageEffectProvider::clone() const
{
	return std::make_unique<CircleImageEffectProvider>(*this);
}

void CircleImageEffectProvider::updateEffect(cv::Scalar const& firstColor, cv::Scalar const& secondColor) {
	cv::Point const center{ _effect.cols / 2, _effect.rows / 2 };

	for (int i = 0; i < _radius; ++i) {
		float const transitionPercent = (static_cast<float>(i) / _radius);
		cv::Scalar color = (transitionPercent * firstColor) + ((1.0F - transitionPercent) * secondColor);
		cv::circle(_effect, center, i, color, 2);
	}
}