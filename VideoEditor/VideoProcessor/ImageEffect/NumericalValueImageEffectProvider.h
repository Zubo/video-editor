#ifndef NUMERICALVALUEIMAGEEFFECTPROVIDER_H
#define NUMERICALVALUEIMAGEEFFECTPROVIDER_H

#include <VideoProcessor/ImageEffect/IImageEffectProvider.hpp>

class NumericalValueImageEffectProvider : public IImageEffectProvider
{
public:
	static NumericalValueImageEffectProvider create(int const num, int const fontScale);
	static NumericalValueImageEffectProvider create();

private:
    NumericalValueImageEffectProvider(int const width, int const height);

public:
	cv::Mat const& getImageEffect() const override;

private:
	cv::Mat _effect;
};

#endif // NUMERICALVALUEIMAGEEFFECTPROVIDER_H
