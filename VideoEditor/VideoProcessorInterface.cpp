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

    QThread& workerThread = _workerThread.emplace();
    VideoProcessorWorker& workerObject = _workerObject.emplace();
    workerObject.moveToThread(&workerThread);
    connect(&workerThread, &QThread::started, &workerObject, [srcPath, applier, &workerObject]() { workerObject.processVideo(srcPath, applier); });
    connect(&workerObject, &VideoProcessorWorker::progressChanged, [this](float val){ emit progressChanged(val); });
    connect(&workerObject, &VideoProcessorWorker::finished, [this]() { emit processingCompleted(); });
    connect(&workerObject, &VideoProcessorWorker::finished, this, &VideoProcessorInterface::waitThreadToFinish);
    connect(&workerObject, &VideoProcessorWorker::aborted, [this]() { emit processingAborted(); });
    workerThread.start();
}

Q_INVOKABLE QPoint VideoProcessorInterface::getVideoResolution(QString videoPath) const
{
    std::string const stdStringPath = videoPath.toStdString();
    cv::Point2i resolution = VideoProcessorUtils::getVideoResolution(stdStringPath);

    return QPoint(resolution.x, resolution.y);
}

void VideoProcessorInterface::stopProcessing()
{
    if (_workerObject.has_value())
    {
	    _workerObject->stop();
    }
    waitThreadToFinish();
}

void VideoProcessorInterface::waitThreadToFinish()
{
    if (_workerThread.has_value()) {
        _workerThread->quit();
        _workerThread->wait();

        _workerObject.reset();
        _workerThread.reset();
    }
}
