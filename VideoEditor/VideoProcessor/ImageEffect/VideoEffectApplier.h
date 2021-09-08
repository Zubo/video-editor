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
	explicit VideoEffectApplier(std::string const & destDirectoryPath);

public:
    void registerEffect(AbstractVideoEffect const& effect, cv::Point2i pos = cv::Point2i());
    void process(std::string sourcePath, std::function<void(float)> progressChanged);
    void abortProcessing();

private:
    std::string getDestinationFilePath(std::string const& sourcePath) const;

private:
    std::vector<VideoEffectApplierEntry> _entries;
    std::string _destDirectoryPath;
    bool _isRunning = false;
};

#endif // VIDEOEFFECTAPPLIER_H
