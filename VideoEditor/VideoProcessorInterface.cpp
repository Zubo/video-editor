#include <VideoProcessorInterface.h>

VideoProcessorInterface::VideoProcessorInterface() :
    QObject(0)
{
}

VideoProcessorInterface::~VideoProcessorInterface()
{
    _workerThread.quit();
    _workerObject.stop();
    _workerThread.wait();
}

void VideoProcessorInterface::requestProcessing(const bool circleEffect, const bool numericalEffect)
{
    _workerObject.moveToThread(&_workerThread);
    connect(&_workerThread, &QThread::started, &_workerObject, &VideoProcessorWorker::processVideo);
    connect(&_workerObject, &VideoProcessorWorker::progressChanged, [this](float val){emit progressChanged(val);});
    _workerThread.start();
}
