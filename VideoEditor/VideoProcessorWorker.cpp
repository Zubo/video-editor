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

    bool isAborted = false;

    auto const abortedCallback = [this, &isAborted]() {
        isAborted = true;
    };

    videoEffectApplier.process(srcPath, progressChangedCallback, abortedCallback);

    _effectApplierOptionalRef.reset();

	if (isAborted) {
		emit aborted();
	}
    else {
        emit finished();
    }
}

void VideoProcessorWorker::stop()
{
    if (_effectApplierOptionalRef.has_value()) {
        VideoEffectApplier& effectApplier = _effectApplierOptionalRef->get();
        effectApplier.abortProcessing();
    }
}
