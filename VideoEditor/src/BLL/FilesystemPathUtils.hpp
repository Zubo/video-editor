#ifndef FILESYSTEMPATHUTILS_H
#define FILESYSTEMPATHUTILS_H

#include <filesystem>

namespace fs = std::filesystem;

class FilesystemPathUtils
{
public:
    static fs::path replaceFilePathExtension(fs::path const& filePath, fs::path const& newDirectoryPath);

private:
    FilesystemPathUtils() = delete;
};

#endif // FILESYSTEMPATHUTILS_H
