#ifndef PROGRESSBARVIDEOEFFECT_H
#define PROGRESSBARVIDEOEFFECT_H

#include <opencv2/opencv.hpp>

#include <VideoProcessor/ImageEffect/AbstractVideoEffect.hpp>

class ProgressBarVideoEffect : public AbstractVideoEffect
{
public:
	static ProgressBarVideoEffect create(float const width, float const height);

private:
	ProgressBarVideoEffect(float const width, float const height);

public:
	cv::Mat const& getImageEffect() const override;
	void update(float deltaTime) override;
	std::unique_ptr<AbstractVideoEffect> clone() const override;

private:
	float getProgress() const;
	void updateEffect();

private:
	float _elapsedTime = 0.0F;
	int _width;
	int _height;
	cv::Mat _effect;

private:
	static constexpr float LOOP_DURATION_MS = 500.0F;
	static const cv::Scalar BACKGROUND_COLOR;
	static const cv::Scalar PROGRESS_COLOR;
};

#endif // PROGRESSBARVIDEOEFFECT_H
