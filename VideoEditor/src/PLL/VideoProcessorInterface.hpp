#ifndef VIDEOPROCESSORINTERFACE_H
#define VIDEOPROCESSORINTERFACE_H

#include <optional>

#include <QPoint>
#include <QString>
#include <QObject>
#include <QThread>
#include <QVariant>

#include <PLL/BLLContext.hpp>
#include <PLL/VideoProcessorWorker.hpp>

class VideoProcessorInterface : public QObject
{
    Q_OBJECT
public:
	VideoProcessorInterface(BLLContext& bllContext);
	virtual ~VideoProcessorInterface();

public:
    Q_INVOKABLE void requestProcessing(QVariant const processingParams);
    Q_INVOKABLE QPoint getVideoResolution(QString videoPath) const;

public slots:
    void stopProcessing();

signals:
    void progressChanged(float);
    void processingCompleted();
    void videoProcessingAborted(QString msg);

private slots:
    void waitVideoProcessorThreadToFinish();

private:
    std::optional<QThread> _videoProcessorThread;
    std::optional<VideoProcessorWorker> _videoProcessorWorkingObject;
    BLLContext& _bllContext;
};

#endif // VIDEOPROCESSORINTERFACE_H
