#ifndef VIDEOEFFECTAPPLIER_H
#define VIDEOEFFECTAPPLIER_H

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

#include <BLL/VideoProcessor/ImageEffect/VideoEffectApplierEntry.h>

class VideoEffectApplier
{
public:
	explicit VideoEffectApplier(std::string const & destDirectoryPath);

public:
    void registerEffect(std::unique_ptr<AbstractVideoEffect> effectUnique, cv::Point2i pos);
    void process(std::string sourcePath, std::function<void(float)> progressChanged, std::function<void()> onAborted);
    void abortProcessing();

private:
    void deleteExistingThumbnailForVideo(std::string const& videoPath);
    std::string getDestinationFilePath(std::string const& sourcePath) const;

private:
    std::vector<VideoEffectApplierEntry> _entries;
    std::string _destDirectoryPath;
    bool _isRunning = false;
};

#endif // VIDEOEFFECTAPPLIER_H
