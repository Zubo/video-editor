#ifndef NUMERICALVALUEVIDEOEFFECT_H
#define NUMERICALVALUEVIDEOEFFECT_H

#include <BLL/VideoProcessor/VideoEffect/AbstractRandomizableVideoEffect.hpp>

class NumericalVideoEffect : public AbstractRandomizableVideoEffect
{
public:
	static NumericalVideoEffect create(int const fontScale = DEFAULT_FONT_SCALE);

public:
	static constexpr float RANDOMIZATION_INTERVAL_MS = 300.0F;

private:
    static constexpr int DEFAULT_FONT_SCALE = 7;

public:
	NumericalVideoEffect(NumericalVideoEffect const& other);

private:
    NumericalVideoEffect(int const fontScale);

public:
	cv::Mat const& getImageEffect() const override;
	void randomize() override;
	std::unique_ptr<AbstractVideoEffect> clone() const override;

private:
	void updateEffect(int const num);

private:
	int _fontScale;
	cv::Mat _effect;
};

#endif // NUMERICALVALUEVIDEOEFFECT_H
