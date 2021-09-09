#include <BLL/VideoProcessor/ImageEffect/VideoEffectApplierEntry.hpp>

VideoEffectApplierEntry::VideoEffectApplierEntry(std::unique_ptr<AbstractVideoEffect> videoEffectUnique, cv::Point2i pos) :
	_videoEffectUnique(std::move(videoEffectUnique)),
	_position(pos)
{
}

VideoEffectApplierEntry::VideoEffectApplierEntry(VideoEffectApplierEntry const& other) :
	_videoEffectUnique(other._videoEffectUnique->clone()),
	_position(other._position)
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
