#include <PLL/ThumbnailGeneratorInterface.hpp>

ThumbnailGeneratorInterface::ThumbnailGeneratorInterface(BLLContext& bllContext) :
	QObject(nullptr),
	_bllContext(bllContext)
{
}

ThumbnailGeneratorInterface::~ThumbnailGeneratorInterface()
{
    stopGenerating();
}

Q_INVOKABLE void ThumbnailGeneratorInterface::requestThumbnailGeneration()
{
	if (_thumbnailGeneratorThread.has_value() || _thumbnailGeneratorWorkerObject.has_value()) {
		return;
	}

	QThread& workerThread = _thumbnailGeneratorThread.emplace();
	ThumbnailGeneratorWorker& workerObject = _thumbnailGeneratorWorkerObject.emplace();
	workerObject.registerPath(_bllContext.RawVideosDirectoryPath);
	workerObject.registerPath(_bllContext.EditedVideosDirectoryPath);
	workerObject.registerExtension(".mp4");
	workerObject.registerExtension(".mkv");

	workerObject.moveToThread(&workerThread);

	connect(&workerThread, &QThread::started, &workerObject, &ThumbnailGeneratorWorker::generateThumbnails);
	connect(&workerObject, &ThumbnailGeneratorWorker::generatingStopped, this, &ThumbnailGeneratorInterface::requestThumbnailGeneration);

	workerThread.start();
}

void ThumbnailGeneratorInterface::stopGenerating()
{
	if (_thumbnailGeneratorWorkerObject.has_value()) {
		_thumbnailGeneratorWorkerObject->abort();
	}

	waitForThumbnailGeneratorThreadToFinish();
}

void ThumbnailGeneratorInterface::waitForThumbnailGeneratorThreadToFinish()
{
	if (_thumbnailGeneratorThread.has_value()) {
		_thumbnailGeneratorThread->quit();
		_thumbnailGeneratorThread->wait();

		_thumbnailGeneratorWorkerObject.reset();
		_thumbnailGeneratorThread.reset();
	}
}
