#include <string.h>

#include <VideoProcessorInterface.h>

#include <VideoProcessor/ImageEffect/VideoEffectApplier.h>
#include <VideoProcessor/VideoProcessorUtils.h>

VideoProcessorInterface::VideoProcessorInterface(BLLContext& bllContext) :
    QObject(nullptr),
    _bllContext(bllContext)
{
}

VideoProcessorInterface::~VideoProcessorInterface()
{
    stopProcessing();
}

Q_INVOKABLE void VideoProcessorInterface::requestProcessing(QVariant const processingParams)
{
    VideoEffectApplier applier(_bllContext.EditedVideosDirectoryPath);
    // fill the applier

    QMap<QString, QVariant> jsonParamsMap = processingParams.toMap();
    QString qSrcPath = jsonParamsMap.value("srcPath").toString();
    std::string srcPath = qSrcPath.toStdString();

	bool circleEffect = jsonParamsMap.value("useCircleEffect").toBool();
    if (circleEffect) {
        QPoint const pos = jsonParamsMap.value("circleEffectPos", QPoint(0, 0)).toPoint();
        applier.registerEffect(
            std::make_unique<CircleImageEffectProvider>(_bllContext._CircleEffect),
            cv::Point2i(pos.x(), pos.y()),
            CircleImageEffectProvider::RANDOMIZATION_INTERVAL_MS
        );
    }

	bool numericalEffect = jsonParamsMap.value("useNumericalEffect").toBool();
    
	if (numericalEffect) {
		QPoint const pos = jsonParamsMap.value("numericalEffectPos", QPoint(0, 0)).toPoint();
        applier.registerEffect(
            std::make_unique<NumericalValueImageEffectProvider>(_bllContext._NumericalEffect),
            cv::Point2i(pos.x(), pos.y()),
            NumericalValueImageEffectProvider::RANDOMIZATION_INTERVAL_MS
        );
    }

    QThread& workerThread = _videoProcessorThread.emplace();
    VideoProcessorWorker& workerObject = _videoProcessorWorkingObject.emplace();
    workerObject.moveToThread(&workerThread);
    connect(&workerThread, &QThread::started, &workerObject, [srcPath, applier, &workerObject]() { workerObject.processVideo(srcPath, applier); });
    connect(&workerObject, &VideoProcessorWorker::videoProcessingProgressChanged, [this](float val){ emit progressChanged(val); });
    connect(&workerObject, &VideoProcessorWorker::finished, [this]() { emit processingCompleted(); });
    connect(&workerObject, &VideoProcessorWorker::finished, this, &VideoProcessorInterface::waitVideoProcessorThreadToFinish);
    connect(&workerObject, &VideoProcessorWorker::finished, [this]() { requestThumbnailGeneration(); });
    connect(&workerObject, &VideoProcessorWorker::aborted, [this](QString msg) { emit videoProcessingAborted(msg); });
    workerThread.start();
}

Q_INVOKABLE QPoint VideoProcessorInterface::getVideoResolution(QString videoPath) const
{
    std::string const stdStringPath = videoPath.toStdString();
    cv::Point2i resolution = VideoProcessorUtils::getVideoResolution(stdStringPath);

    return QPoint(resolution.x, resolution.y);
}

Q_INVOKABLE void VideoProcessorInterface::requestThumbnailGeneration()
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
    connect(&workerObject, &ThumbnailGeneratorWorker::generatingStopped, this, &VideoProcessorInterface::waitForThumbnailGeneratorThreadToFinish);

    workerThread.start();
}

void VideoProcessorInterface::stopProcessing()
{
    if (_videoProcessorWorkingObject.has_value())
    {
	    _videoProcessorWorkingObject->stop();
    }
    waitVideoProcessorThreadToFinish();
}

void VideoProcessorInterface::waitVideoProcessorThreadToFinish()
{
    if (_videoProcessorThread.has_value()) {
        _videoProcessorThread->quit();
        _videoProcessorThread->wait();

        _videoProcessorWorkingObject.reset();
        _videoProcessorThread.reset();
    }
}

void VideoProcessorInterface::waitForThumbnailGeneratorThreadToFinish()
{
    if (_thumbnailGeneratorThread.has_value()) {
        _thumbnailGeneratorThread->quit();
        _thumbnailGeneratorThread->wait();

        _thumbnailGeneratorWorkerObject.reset();
        _thumbnailGeneratorThread.reset();
    }
}