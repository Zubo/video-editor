#ifndef NUMERICALVALUEIMAGEEFFECTPROVIDER_H
#define NUMERICALVALUEIMAGEEFFECTPROVIDER_H

#include <VideoProcessor/ImageEffect/AbstractVideoEffect.hpp>

class NumericalValueImageEffectProvider : public AbstractVideoEffect
{
public:
	static NumericalValueImageEffectProvider create(int const fontScale = DEFAULT_FONT_SCALE);

private:
    NumericalValueImageEffectProvider(int const fontScale);

public:
	cv::Mat const& getImageEffect() const override;
	void randomize() override;

private:
	void updateEffect(int const num);

private:
	int _fontScale;
	cv::Mat _effect;

private:
	static constexpr int DEFAULT_FONT_SCALE = 10;
};

#endif // NUMERICALVALUEIMAGEEFFECTPROVIDER_H
