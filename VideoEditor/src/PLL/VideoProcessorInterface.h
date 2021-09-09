#ifndef VIDEOPROCESSORINTERFACE_H
#define VIDEOPROCESSORINTERFACE_H

#include <optional>

#include <QPoint>
#include <QString>
#include <QObject>
#include <QThread>
#include <QVariant>

#include <PLL/BLLContext.h>
#include <PLL/ThumbnailGeneratorWorker.h>
#include <PLL/VideoProcessorWorker.h>

class VideoProcessorInterface : public QObject
{
    Q_OBJECT
public:
    VideoProcessorInterface(BLLContext& bllContext);
    ~VideoProcessorInterface();

public:
    Q_INVOKABLE void requestProcessing(QVariant const processingParams);
    Q_INVOKABLE QPoint getVideoResolution(QString videoPath) const;
    Q_INVOKABLE void requestThumbnailGeneration();

public slots:
    void stopProcessing();

signals:
    void progressChanged(float);
    void processingCompleted();
    void videoProcessingAborted(QString msg);

private slots:
    void waitVideoProcessorThreadToFinish();
    void waitForThumbnailGeneratorThreadToFinish();

private:
    std::optional<QThread> _videoProcessorThread;
    std::optional<VideoProcessorWorker> _videoProcessorWorkingObject;
    std::optional<QThread> _thumbnailGeneratorThread;
    std::optional<ThumbnailGeneratorWorker> _thumbnailGeneratorWorkerObject;
    BLLContext& _bllContext;
};

#endif // VIDEOPROCESSORINTERFACE_H
