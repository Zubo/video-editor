#ifndef PROGRESSBARVIDEOEFFECT_H
#define PROGRESSBARVIDEOEFFECT_H

#include <opencv2/opencv.hpp>

#include <BLL/VideoProcessor/VideoEffect/AbstractVideoEffect.hpp>

class ProgressBarVideoEffect : public AbstractVideoEffect
{
public:
    static ProgressBarVideoEffect create(int const width, int const height);

private:
	static const cv::Scalar BACKGROUND_COLOR;
	static const cv::Scalar PROGRESS_COLOR;

private:
	static constexpr float LOOP_DURATION_MS = 500.0F;

private:
    ProgressBarVideoEffect(int const width, int const height);

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
};

#endif // PROGRESSBARVIDEOEFFECT_H
