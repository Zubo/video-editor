#ifndef VIDEOEFFECTAPPLIER_H
#define VIDEOEFFECTAPPLIER_H

#include <functional>
#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

#include <VideoProcessor/ImageEffect/VideoEffectApplierEntry.h>

class VideoEffectApplier
{
public:
	VideoEffectApplier() = default;

public:
    void registerEffect(AbstractVideoEffect const& effect, cv::Point2i pos);
    void process(std::string sourcePath, std::string destinationPath, std::function<void(float)> progressChanged);
    void abortProcessing();

private:
    std::vector<VideoEffectApplierEntry> _entries;
    bool _isRunning = false;
};

#endif // VIDEOEFFECTAPPLIER_H
