#include <cstdlib>

#include <BLL/VideoProcessor/VideoEffect/CircleVideoEffect.hpp>

#include <opencv2/opencv.hpp>

CircleVideoEffect CircleVideoEffect::create(int const radius)
{
    CircleVideoEffect circleShapeProvider{ radius };
	circleShapeProvider.randomize();

    return circleShapeProvider;
}
CircleVideoEffect::CircleVideoEffect(int const radius) :
	AbstractRandomizableVideoEffect(RANDOMIZATION_INTERVAL_MS),
	_radius(radius),
    _effect(static_cast<int>(_radius * 2.1F), static_cast<int>(_radius * 2.1F), CV_8UC4, cv::Scalar::all(0))
{
}

CircleVideoEffect::CircleVideoEffect(CircleVideoEffect const& other) :
	AbstractRandomizableVideoEffect(other),
	_radius(other._radius),
	_effect(other._effect.clone())
{
}

cv::Mat const & CircleVideoEffect::getImageEffect() const
{
    return _effect;
}

void CircleVideoEffect::randomize()
{
	cv::Scalar firstColor(std::rand() % 256, std::rand() % 256, std::rand() % 256, 255);
	cv::Scalar secondColor(std::rand() % 256, std::rand() % 256, std::rand() % 256, 255);
	updateEffect(firstColor, secondColor);
}

std::unique_ptr<AbstractVideoEffect> CircleVideoEffect::clone() const
{
	return std::make_unique<CircleVideoEffect>(*this);
}

void CircleVideoEffect::updateEffect(cv::Scalar const& firstColor, cv::Scalar const& secondColor) {
	cv::Point const center{ _effect.cols / 2, _effect.rows / 2 };

	for (int i = 0; i < _radius; ++i) {
		float const transitionPercent = (static_cast<float>(i) / _radius);
		cv::Scalar color = (transitionPercent * firstColor) + ((1.0F - transitionPercent) * secondColor);
		cv::circle(_effect, center, i, color, 2);
	}
}
