#ifndef VIDEOPROCESSORINTERFACE_H
#define VIDEOPROCESSORINTERFACE_H

#include <QObject>
#include <QThread>
#include <QVariant>

#include <VideoProcessorWorker.h>
#include <BLLContext.h>

class VideoProcessorInterface : public QObject
{
    Q_OBJECT
public:
    VideoProcessorInterface(BLLContext& bllContext);
    ~VideoProcessorInterface();

public:
    Q_INVOKABLE void requestProcessing(QVariant const processingParams);

signals:
    void progressChanged(float);

private:
    QThread _workerThread;
    VideoProcessorWorker _workerObject;
    BLLContext& _bllContext;
};

#endif // VIDEOPROCESSORINTERFACE_H
