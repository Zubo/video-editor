#include "VideoEffectApplierEntry.h"

VideoEffectApplierEntry::VideoEffectApplierEntry(std::unique_ptr<AbstractVideoEffect> videoEffectUnique, cv::Point2i pos, float const randomizationInterval) :
	_videoEffectUnique(std::move(videoEffectUnique)),
	_position(pos),
	_randomizationInterval(randomizationInterval)
{
}

VideoEffectApplierEntry::VideoEffectApplierEntry(VideoEffectApplierEntry const& other) :
	_videoEffectUnique(other._videoEffectUnique->clone()),
	_position(other._position),
	_randomizationInterval(other._randomizationInterval)
{
}

AbstractVideoEffect & VideoEffectApplierEntry::getEffect() const
{
	return *_videoEffectUnique;
}

cv::Point2i const VideoEffectApplierEntry::getPosition() const
{
	return _position;
}

void VideoEffectApplierEntry::update(float const deltaTime)
{
	_timeSinceLastRandomizaion += deltaTime;

	if (_timeSinceLastRandomizaion > _randomizationInterval) {
		_videoEffectUnique->randomize();
		_timeSinceLastRandomizaion = 0.0F;
	}
}