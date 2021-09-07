#ifndef VIDEOPROCESSORINTERFACE_H
#define VIDEOPROCESSORINTERFACE_H

#include <QObject>
#include <QThread>

#include <VideoProcessorWorker.h>

class VideoProcessorInterface : public QObject
{
    Q_OBJECT
public:
    VideoProcessorInterface();
    ~VideoProcessorInterface();

public:
    Q_INVOKABLE void requestProcessing(
        std::string const& srcPath,
        std::string const& dstPath,
        bool const circleEffect,
        bool const numericalEffect);

signals:
    void progressChanged(float);

private:
    QThread _workerThread;
    VideoProcessorWorker _workerObject;
};

#endif // VIDEOPROCESSORINTERFACE_H
