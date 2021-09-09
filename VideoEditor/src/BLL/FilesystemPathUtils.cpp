#include <BLL/FilesystemPathUtils.h>

fs::path FilesystemPathUtils::replaceFilePathExtension(fs::path const & filePath, fs::path const & newDirectoryPath)
{
	fs::path const filename = filePath.filename();
	fs::path destP = newDirectoryPath;
	destP /= filename;
	return destP;
}
