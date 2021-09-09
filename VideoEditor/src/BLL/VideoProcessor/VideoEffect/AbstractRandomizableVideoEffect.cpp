#include <BLL/VideoProcessor/VideoEffect/AbstractRandomizableVideoEffect.hpp>

AbstractRandomizableVideoEffect::AbstractRandomizableVideoEffect(float const randomizationInterval) :
	_randomizationInterval(randomizationInterval)
{
}

void AbstractRandomizableVideoEffect::update(float const deltaTime)
{
	_timeSinceLastRandomizaion += deltaTime;

	if (_timeSinceLastRandomizaion > _randomizationInterval) {
		randomize();
		_timeSinceLastRandomizaion = 0.0F;
	}
}
