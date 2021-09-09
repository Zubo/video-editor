#include <PLL/BLLContext.hpp>

#include <opencv2/opencv.hpp>

BLLContext::BLLContext(std::string const & currentDirectoryPath) :
	_CircleEffect(CircleImageEffectProvider::create()),
	_NumericalEffect(NumericalValueImageEffectProvider::create()),
	_ProgressBarEffect(ProgressBarVideoEffect::create(150.0F, 50.0F)),
	RawVideosDirectoryPath(currentDirectoryPath + RAW_DIR_NAME),
	EditedVideosDirectoryPath(currentDirectoryPath + EDITED_DIR_NAME)
{
}

void BLLContext::init() const
{
    std::filesystem::create_directory(RawVideosDirectoryPath);
    std::filesystem::create_directory(EditedVideosDirectoryPath);
}
