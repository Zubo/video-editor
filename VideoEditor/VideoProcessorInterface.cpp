#include <string.h>

#include <VideoProcessorInterface.h>

#include <VideoProcessor/ImageEffect/VideoEffectApplier.h>

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
        applier.registerEffect(_bllContext._CircleEffect);
    }

	bool numericalEffect = jsonParamsMap.value("useNumericalEffect").toBool();
    
    if (numericalEffect) {
        applier.registerEffect(_bllContext._NumericalEffect);
    }

    _workerObject.moveToThread(&_workerThread);
    connect(&_workerThread, &QThread::started, &_workerObject, [=]() { _workerObject.processVideo(srcPath, applier); });
    connect(&_workerObject, &VideoProcessorWorker::progressChanged, [this](float val){ emit progressChanged(val); });
    connect(&_workerObject, &VideoProcessorWorker::finished, [this]() { emit processingCompleted(); });
    _workerThread.start();
}

void VideoProcessorInterface::stopProcessing()
{
	_workerThread.quit();
	_workerObject.stop();
	_workerThread.wait();
}
