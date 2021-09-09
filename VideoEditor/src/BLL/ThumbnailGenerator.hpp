#ifndef THUMBNAILGENERATOR_H
#define THUMBNAILGENERATOR_H

#include <filesystem>
#include <string>
#include <vector>

class ThumbnailGenerator
{
public:
    static constexpr const char* THUMBNAIL_EXTENSION = ".png";

public:
    ThumbnailGenerator() = default;

public:
    void registerPath(std::string const & path);
    void registerExtension(std::string const& extension);
    void generate();
    void abort();

private:
	void generateForDirectory(std::string const& dirPath) const;
    bool isExtensionSupported(std::filesystem::path extension) const;

private:
    std::vector<std::string> _directoryPaths;
    std::vector<std::string> _supportedExtensions;
    bool _isRunning = false;
};

#endif // THUMBNAILGENERATOR_H
