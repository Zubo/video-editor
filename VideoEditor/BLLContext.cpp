#include "BLLContext.h"

#include <opencv2/opencv.hpp>

BLLContext::BLLContext(std::string const & currentDirectoryPath) :
	_CircleEffect(CircleImageEffectProvider::create()),
	_NumericalEffect(NumericalValueImageEffectProvider::create()),
	_ThumbnailGenerator(),
	RawVideosDirectoryPath(currentDirectoryPath + RAW_DIR_NAME),
	EditedVideosDirectoryPath(currentDirectoryPath + EDITED_DIR_NAME)
{
	_ThumbnailGenerator.registerPath(currentDirectoryPath);
}
