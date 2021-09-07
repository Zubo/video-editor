#include "VideoEffectApplierEntry.h"

VideoEffectApplierEntry::VideoEffectApplierEntry(AbstractVideoEffect const& videoEffect, cv::Point2i pos) :
	VideoEffect(videoEffect),
	Position(pos)
{
}