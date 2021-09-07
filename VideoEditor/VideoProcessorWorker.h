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
	void processVideo(std::string srcPath, std::string destPath, class VideoEffectApplier videoEffectApplier);

public:
    void stop();

signals:
    void progressChanged(float val);
    void finished();

private:
    std::string _sourceFilePath;
    std::string _destinationFilePath;
    EffectApplierOptionalRef _effectApplierOptionalRef;
};

#endif // VIDEOPROCESSORQTHREAD_H
