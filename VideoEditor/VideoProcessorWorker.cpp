#include "VideoProcessorWorker.h"

#include <QThread>
#include <iostream>

#include <VideoProcessor/ImageEffect/VideoEffectApplier.h>

VideoProcessorWorker::VideoProcessorWorker() :
    QObject(nullptr)
{

}

void VideoProcessorWorker::processVideo(std::string srcPath, class VideoEffectApplier videoEffectApplier)
{
    _effectApplierOptionalRef.emplace(videoEffectApplier);

    auto const progressChangedCallback = [this](float const val) {
        emit progressChanged(val);
    };

    videoEffectApplier.process(srcPath, progressChangedCallback);

    _effectApplierOptionalRef.reset();

    emit finished();
}

void VideoProcessorWorker::stop()
{
    if (_effectApplierOptionalRef.has_value()) {
        VideoEffectApplier& effectApplier = _effectApplierOptionalRef->get();
        effectApplier.abortProcessing();
    }
}
