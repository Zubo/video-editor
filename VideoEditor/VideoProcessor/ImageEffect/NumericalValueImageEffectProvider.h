#ifndef NUMERICALVALUEIMAGEEFFECTPROVIDER_H
#define NUMERICALVALUEIMAGEEFFECTPROVIDER_H

#include <VideoProcessor/ImageEffect/AbstractRandomizableVideoEffect.h>

class NumericalValueImageEffectProvider : public AbstractRandomizableVideoEffect
{
public:
	static NumericalValueImageEffectProvider create(int const fontScale = DEFAULT_FONT_SCALE);

public:
	static constexpr float RANDOMIZATION_INTERVAL_MS = 300.0F;

public:
	NumericalValueImageEffectProvider(NumericalValueImageEffectProvider const& other);

private:
    NumericalValueImageEffectProvider(int const fontScale);

public:
	cv::Mat const& getImageEffect() const override;
	void randomize() override;
	std::unique_ptr<AbstractVideoEffect> clone() const override;

private:
	void updateEffect(int const num);

private:
	int _fontScale;
	cv::Mat _effect;

private:
	static constexpr int DEFAULT_FONT_SCALE = 10;
};

#endif // NUMERICALVALUEIMAGEEFFECTPROVIDER_H
