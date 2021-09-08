#ifndef VIDEOPROCESSORINTERFACE_H
#define VIDEOPROCESSORINTERFACE_H

#include <optional>

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

public slots:
    void stopProcessing();


signals:
    void progressChanged(float);
    void processingCompleted();
    void processingAborted();

private slots:
    void waitThreadToFinish();

private:
    std::optional<QThread> _workerThread;
    std::optional<VideoProcessorWorker> _workerObject;
    BLLContext& _bllContext;
};

#endif // VIDEOPROCESSORINTERFACE_H
