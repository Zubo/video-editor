#include "VideoProcessorWorker.h"

#include <QThread>
#include <iostream>

VideoProcessorWorker::VideoProcessorWorker() :
    QObject(nullptr)
{

}

void VideoProcessorWorker::processVideo()
{
    _stop = false;

    float val = 0.0F;

    while (val < 1.0F && !_stop) {
        val += 0.001;
        emit progressChanged(val);
        QThread::msleep(5);
    }

    emit finished();
}

void VideoProcessorWorker::stop()
{
    _stop = true;
}
