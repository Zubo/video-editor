#ifndef ABSTRACTRANDOMIZABLEVIDEOEFFECT_H
#define ABSTRACTRANDOMIZABLEVIDEOEFFECT_H

#include <BLL/VideoProcessor/ImageEffect/AbstractVideoEffect.hpp>

class AbstractRandomizableVideoEffect : public AbstractVideoEffect
{
public:
	AbstractRandomizableVideoEffect(float const randomizationInterval);

public:
	void update(float const deltaTime) override;
	virtual void randomize() = 0;

protected:
	float _randomizationInterval;
	float _timeSinceLastRandomizaion = 0.0F;
};

#endif // ABSTRACTRANDOMIZABLEVIDEOEFFECT_H
