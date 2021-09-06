#include <filesystem>

#include <opencv2/opencv.hpp>

#include <VideoProcessor/VideoThumbnailProvider.hpp>
#include <ThumbnailGenerator.h>

namespace fs = std::filesystem;

void ThumbnailGenerator::registerPath(std::string const& path)
{
	_directoryPaths.push_back(path);
}

void ThumbnailGenerator::registerExtension(std::string const& extension)
{
	_supportedExtensions.push_back(extension);
}

void ThumbnailGenerator::generate() const
{
	for (std::string const & dirPath : _directoryPaths) {
		generateForDirectory(dirPath);
	}
}

void ThumbnailGenerator::generateForDirectory(std::string const& dirPath) const
{
	for (fs::directory_entry const& directoryEntry : fs::directory_iterator(dirPath)) {
		fs::path const& filePath = directoryEntry.path();
		fs::path const extension = filePath.extension();

		if (isExtensionSupported(extension)) {
			fs::path thumbnailPath = fs::path(filePath).replace_extension(fs::path(".png"));

			if (!fs::exists(thumbnailPath)) {
				cv::Mat thumbnail = VideoThumbnailProvider::getThumbnail(filePath.string());
				cv::imwrite(thumbnailPath.string(), thumbnail);
			}
		}
	}
}

bool ThumbnailGenerator::isExtensionSupported(fs::path extension) const
{
	auto extIter = std::find(_supportedExtensions.cbegin(), _supportedExtensions.cend(), extension);

	return extIter != _supportedExtensions.cend();
}
