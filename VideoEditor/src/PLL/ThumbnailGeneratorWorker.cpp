#include <PLL/ThumbnailGeneratorWorker.h>


ThumbnailGeneratorWorker::ThumbnailGeneratorWorker() :
	QObject(nullptr)
{
}

void ThumbnailGeneratorWorker::registerPath(std::string const& path)
{
	_thumbnailGenerator.registerPath(path);
}

void ThumbnailGeneratorWorker::registerExtension(std::string const& extension)
{
	_thumbnailGenerator.registerExtension(extension);
}

void ThumbnailGeneratorWorker::generateThumbnails()
{
	_thumbnailGenerator.generate();

	emit generatingStopped();
}

void ThumbnailGeneratorWorker::abort()
{
	_thumbnailGenerator.abort();
}
