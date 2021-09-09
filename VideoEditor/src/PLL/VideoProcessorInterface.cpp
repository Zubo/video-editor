#include <string>

#include <PLL/VideoProcessorInterface.hpp>

#include <BLL/VideoProcessor/VideoEffect/VideoEffectApplier.hpp>
#include <BLL/VideoProcessor/VideoProcessorUtils.hpp>

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
            std::make_unique<CircleVideoEffect>(_bllContext._CircleEffect),
            cv::Point2i(pos.x(), pos.y())
        );
    }

	bool numericalEffect = jsonParamsMap.value("useNumericalEffect").toBool();
    
	if (numericalEffect) {
		QPoint const pos = jsonParamsMap.value("numericalEffectPos", QPoint(0, 0)).toPoint();
        applier.registerEffect(
            std::make_unique<NumericalVideoEffect>(_bllContext._NumericalEffect),
            cv::Point2i(pos.x(), pos.y())
        );
    }

    bool progressbarEffect = jsonParamsMap.value("useProgressbarEffect").toBool();

    if (progressbarEffect) {
        QPoint const pos = jsonParamsMap.value("progressbarEffectPos", QPoint(0,0)).toPoint();
        applier.registerEffect(
            std::make_unique<ProgressBarVideoEffect>(_bllContext._ProgressBarEffect),
            cv::Point2i(pos.x(), pos.y())
        );
    }

    QThread& workerThread = _videoProcessorThread.emplace();
    VideoProcessorWorker& workerObject = _videoProcessorWorkingObject.emplace();
    workerObject.moveToThread(&workerThread);
    connect(&workerThread, &QThread::started, &workerObject, [srcPath, applier, &workerObject]() { workerObject.processVideo(srcPath, applier); });
    connect(&workerObject, &VideoProcessorWorker::videoProcessingProgressChanged, [this](float val){ emit progressChanged(val); });
    connect(&workerObject, &VideoProcessorWorker::finished, [this]() { emit processingCompleted(); });
	connect(&workerObject, &VideoProcessorWorker::finished, this, &VideoProcessorInterface::waitVideoProcessorThreadToFinish);
	connect(&workerObject, &VideoProcessorWorker::aborted, [this](QString msg) { emit videoProcessingAborted(msg); });
	connect(&workerObject, &VideoProcessorWorker::aborted, this, &VideoProcessorInterface::waitVideoProcessorThreadToFinish);
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

