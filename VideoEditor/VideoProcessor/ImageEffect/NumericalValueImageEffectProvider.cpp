#include <string>

#include <VideoProcessor/Const.hpp>
#include <VideoProcessor/ImageEffect/NumericalValueImageEffectProvider.h>

NumericalValueImageEffectProvider NumericalValueImageEffectProvider::create(int const num, int const fontScale)
{
	std::string const text = std::to_string(num);
	int constexpr fontFace = cv::FONT_HERSHEY_SIMPLEX;
    int const thickness = 1;
	int baseLine = 0;
	cv::Size textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseLine);
	baseLine += thickness;

    NumericalValueImageEffectProvider effectProvider(textSize.width + thickness, textSize.height + thickness);

	cv::Point textOrg{
		0,
		textSize.height
	};

    cv::putText(effectProvider._effect, text, textOrg, fontFace, fontScale, Const::BlueColorScalar, 2);

	return effectProvider;
}

NumericalValueImageEffectProvider::NumericalValueImageEffectProvider(int const width, int const height) :
	_effect(height, width, CV_8UC4, cv::Scalar::all(0))
{
}

cv::Mat const& NumericalValueImageEffectProvider::getImageEffect() const
{
	return _effect;
}
