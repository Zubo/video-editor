#include <PLL/VideoProcessorWorker.hpp>

#include <exception>

#include <QThread>
#include <iostream>

#include <BLL/VideoProcessor/ImageEffect/VideoEffectApplier.hpp>

VideoProcessorWorker::VideoProcessorWorker() :
    QObject(nullptr)
{

}

void VideoProcessorWorker::processVideo(std::string srcPath, class VideoEffectApplier videoEffectApplier)
{
    _effectApplierOptionalRef.emplace(videoEffectApplier);

    auto const progressChangedCallback = [this](float const val) {
        emit videoProcessingProgressChanged(val);
    };

    bool isAborted = false;

    auto const abortedCallback = [this, &isAborted]() {
        isAborted = true;
    };

    try {
        videoEffectApplier.process(srcPath, progressChangedCallback, abortedCallback);
    }
    catch (std::exception const& ex) {
        emit aborted(QString("Error processing video: ") + ex.what());
        return;
    }

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
