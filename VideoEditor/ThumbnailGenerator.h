#ifndef THUMBNAILGENERATOR_H
#define THUMBNAILGENERATOR_H

#include <string>
#include <vector>

class ThumbnailGenerator
{
public:
    ThumbnailGenerator() = default;

public:
    void registerPath(std::string const & path);
    void registerExtension(std::string const& extension);
    void generate() const;

private:
	void generateForDirectory(std::string const& dirPath) const;
    bool isExtensionSupported(std::filesystem::path extension) const;

private:
    std::vector<std::string> _directoryPaths;
    std::vector<std::string> _supportedExtensions;
};

#endif // THUMBNAILGENERATOR_H
