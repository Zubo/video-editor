#ifndef VIDEOPROCESSORQTHREAD_H
#define VIDEOPROCESSORQTHREAD_H

#include <functional>
#include <optional>
#include <string>

#include <QObject>

#include <VideoProcessor/ImageEffect/VideoEffectApplier.h>

class VideoProcessorWorker : public QObject
{
    using EffectApplierOptionalRef = std::optional< std::reference_wrapper<VideoEffectApplier> >;

    Q_OBJECT
public:
    VideoProcessorWorker();

public slots:
	void processVideo(std::string srcPath, class VideoEffectApplier videoEffectApplier);

public:
    void stop();

signals:
    void videoProcessingProgressChanged(float val);
    void finished();
    void aborted();

private:
    EffectApplierOptionalRef _effectApplierOptionalRef;
};

#endif // VIDEOPROCESSORQTHREAD_H
