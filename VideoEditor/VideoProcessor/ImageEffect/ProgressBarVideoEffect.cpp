#include <cmath>
#include <memory>

#include <VideoProcessor/ImageEffect/ProgressBarVideoEffect.h>

ProgressBarVideoEffect ProgressBarVideoEffect::create(float const width, float const height)
{
	return ProgressBarVideoEffect(width, height);
}

ProgressBarVideoEffect::ProgressBarVideoEffect(float const width, float const height) :
	_width(width),
	_height(height),
	_effect(_width, _height, CV_8UC4, cv::Scalar::all(0))
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
		return 2.0 * timeMod / LOOP_DURATION_MS;
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

const cv::Scalar ProgressBarVideoEffect::BACKGROUND_COLOR = cv::Scalar(255, 0, 0, 255);
const cv::Scalar ProgressBarVideoEffect::PROGRESS_COLOR = cv::Scalar(0, 0, 255, 255);