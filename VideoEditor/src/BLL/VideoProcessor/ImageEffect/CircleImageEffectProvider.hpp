#ifndef CIRCLEIMAGEEFFECTPROVIDER_H
#define CIRCLEIMAGEEFFECTPROVIDER_H

#include <BLL/VideoProcessor/ImageEffect/AbstractRandomizableVideoEffect.h>

class CircleImageEffectProvider : public AbstractRandomizableVideoEffect
{
public:
    static CircleImageEffectProvider create(int const radius = DEFAULT_RADIUS);

public:
    static constexpr float RANDOMIZATION_INTERVAL_MS = 1000.0F;

private:
	static constexpr int DEFAULT_RADIUS = 50;

public:
    CircleImageEffectProvider(CircleImageEffectProvider const& other);

private:
    CircleImageEffectProvider(int const radius);

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

#endif // CIRCLEIMAGEEFFECTPROVIDER_H
