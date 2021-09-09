#include <cmath>
#include <memory>

#include <BLL/VideoProcessor/VideoEffect/ProgressBarVideoEffect.hpp>
#include <BLL/VideoProcessor/Const.hpp>

const cv::Scalar ProgressBarVideoEffect::BACKGROUND_COLOR = Const::BlueColorScalar;
const cv::Scalar ProgressBarVideoEffect::PROGRESS_COLOR = Const::RedColorScalar;

ProgressBarVideoEffect ProgressBarVideoEffect::create(int const width, int const height)
{
	return ProgressBarVideoEffect(width, height);
}

ProgressBarVideoEffect::ProgressBarVideoEffect(int const width, int const height) :
	_width(width),
	_height(height),
    _effect(_height, _width, CV_8UC4, cv::Scalar::all(0))
{
}

cv::Mat const& ProgressBarVideoEffect::getImageEffect() const
{
	return _effect;
}

void ProgressBarVideoEffect::update(float deltaTime)
{
	_elapsedTime += deltaTime;
	updateEffect();
}

std::unique_ptr<AbstractVideoEffect> ProgressBarVideoEffect::clone() const
{
	return std::make_unique<ProgressBarVideoEffect>(*this);
}

float ProgressBarVideoEffect::getProgress() const
{
	float const timeMod = std::fmod(_elapsedTime, LOOP_DURATION_MS);

	if (timeMod > LOOP_DURATION_MS / 2.0F) {
		return 2.0F - (2.0F * timeMod / LOOP_DURATION_MS);
	}
	else {
        return 2.0F * timeMod / LOOP_DURATION_MS;
	}
}

void ProgressBarVideoEffect::updateEffect()
{
	float const progress = getProgress();
	cv::Rect backgroundRect(0, 0, _width, _height);
	cv::rectangle(_effect, backgroundRect, BACKGROUND_COLOR, -1);
	cv::Rect progressRect(0, 0, progress * _width, _height);
	cv::rectangle(_effect, progressRect, PROGRESS_COLOR, -1);
}
