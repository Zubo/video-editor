#ifndef BLLCONTEXT_H
#define BLLCONTEXT_H

#include <string>

#include <BLL/VideoProcessor/VideoEffect/CircleVideoEffect.hpp>
#include <BLL/VideoProcessor/VideoEffect/NumericalVideoEffect.hpp>
#include <BLL/VideoProcessor/VideoEffect/ProgressBarVideoEffect.hpp>
#include <BLL/ThumbnailGenerator.hpp>

class BLLContext
{
public:
	static constexpr const char* const RAW_DIR_NAME = "/Raw";
	static constexpr const char* const EDITED_DIR_NAME = "/Edited";

public:
    BLLContext(std::string const & currentDirectoryPath);

public:
    void init() const;

public:
	CircleVideoEffect _CircleEffect;
	NumericalVideoEffect _NumericalEffect;
	ProgressBarVideoEffect _ProgressBarEffect;
	std::string RawVideosDirectoryPath;
	std::string EditedVideosDirectoryPath;
};

#endif // BLLCONTEXT_H
