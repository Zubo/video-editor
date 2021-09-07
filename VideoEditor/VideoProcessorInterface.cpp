#include <string.h>

#include <VideoProcessorInterface.h>

#include <VideoProcessor/ImageEffect/VideoEffectApplier.h>

VideoProcessorInterface::VideoProcessorInterface() :
    QObject(nullptr)
{
}

VideoProcessorInterface::~VideoProcessorInterface()
{
    _workerThread.quit();
    _workerObject.stop();
    _workerThread.wait();
}

void VideoProcessorInterface::requestProcessing(
    std::string const & srcPath,
    std::string const & dstPath,
    const bool circleEffect,
    const bool numericalEffect)
{
    VideoEffectApplier applier;
    // fill the applier

    _workerObject.moveToThread(&_workerThread);
    connect(&_workerThread, &QThread::started, &_workerObject, [=]() { _workerObject.processVideo(srcPath, dstPath, applier); });
    connect(&_workerObject, &VideoProcessorWorker::progressChanged, [this](float val){emit progressChanged(val);});
    _workerThread.start();
}
