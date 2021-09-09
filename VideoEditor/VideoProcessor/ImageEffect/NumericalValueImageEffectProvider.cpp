#include <cstdlib>
#include <ctime>
#include <string>

#include <opencv2/opencv.hpp>

#include <VideoProcessor/Const.hpp>
#include <VideoProcessor/ImageEffect/NumericalValueImageEffectProvider.h>

NumericalValueImageEffectProvider NumericalValueImageEffectProvider::create(int const fontScale)
{
    NumericalValueImageEffectProvider effectProvider(fontScale);
    effectProvider.randomize();

    return effectProvider;
}

NumericalValueImageEffectProvider::NumericalValueImageEffectProvider(int const fontScale) :
	AbstractRandomizableVideoEffect(RANDOMIZATION_INTERVAL_MS),
	_fontScale(fontScale)
{
}

NumericalValueImageEffectProvider::NumericalValueImageEffectProvider(NumericalValueImageEffectProvider const& other) :
	AbstractRandomizableVideoEffect(other),
	_fontScale(other._fontScale),
	_effect(other._effect.clone())
{

}

void NumericalValueImageEffectProvider::randomize()
{
	int const randomNum = std::rand() % 100;
	updateEffect(randomNum);
}

std::unique_ptr<AbstractVideoEffect> NumericalValueImageEffectProvider::clone() const
{
	return std::make_unique<NumericalValueImageEffectProvider>(*this);
}

void NumericalValueImageEffectProvider::updateEffect(int const num)
{
	std::string const text = std::to_string(num);
	int constexpr fontFace = cv::FONT_HERSHEY_SIMPLEX;
	int const thickness = 3;
	int baseLine = 0;
	cv::Size textSize = cv::getTextSize(text, fontFace, _fontScale, thickness, &baseLine);
	baseLine += thickness;

	cv::Point textOrg{
		0,
		textSize.height
	};

    int const imageWidth = textSize.width + thickness;
    int const imageHeight = textSize.height + thickness;
    _effect = cv::Mat(imageHeight, imageWidth, CV_8UC4, cv::Scalar::all(0));

	cv::putText(_effect, text, textOrg, fontFace, _fontScale, Const::BlueColorScalar, 2);
}

cv::Mat const& NumericalValueImageEffectProvider::getImageEffect() const
{
    return _effect;
}
