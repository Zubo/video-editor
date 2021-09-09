#ifndef BLLCONTEXT_H
#define BLLCONTEXT_H

#include <string>

#include <BLL/VideoProcessor/ImageEffect/CircleImageEffectProvider.hpp>
#include <BLL/VideoProcessor/ImageEffect/NumericalValueImageEffectProvider.h>
#include <BLL/VideoProcessor/ImageEffect/ProgressBarVideoEffect.h>
#include <BLL/ThumbnailGenerator.h>

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
	CircleImageEffectProvider _CircleEffect;
	NumericalValueImageEffectProvider _NumericalEffect;
	ProgressBarVideoEffect _ProgressBarEffect;
	ThumbnailGenerator _ThumbnailGenerator;
	std::string RawVideosDirectoryPath;
	std::string EditedVideosDirectoryPath;
};

#endif // BLLCONTEXT_H
