#ifndef CIRCLEVIDEOEFFECT_H
#define CIRCLEVIDEOEFFECT_H

#include <BLL/VideoProcessor/ImageEffect/AbstractRandomizableVideoEffect.hpp>

class CircleVideoEffect : public AbstractRandomizableVideoEffect
{
public:
    static CircleVideoEffect create(int const radius = DEFAULT_RADIUS);

public:
    static constexpr float RANDOMIZATION_INTERVAL_MS = 1000.0F;

private:
	static constexpr int DEFAULT_RADIUS = 50;

public:
    CircleVideoEffect(CircleVideoEffect const& other);

private:
    CircleVideoEffect(int const radius);

public:
	cv::Mat const& getImageEffect() const override;
	void randomize() override;
	std::unique_ptr<AbstractVideoEffect> clone() const override;

private:
    void updateEffect(cv::Scalar const& firstColor, cv::Scalar const& secondColor);

private:
    int _radius;
    cv::Mat _effect;
};

#endif // CIRCLEVIDEOEFFECT_H
