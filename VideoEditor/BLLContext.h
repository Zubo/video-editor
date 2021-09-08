#ifndef BLLCONTEXT_H
#define BLLCONTEXT_H

#include <string>

#include <VideoProcessor/ImageEffect/CircleImageEffectProvider.hpp>
#include <VideoProcessor/ImageEffect/NumericalValueImageEffectProvider.h>
#include <ThumbnailGenerator.h>

class BLLContext
{
public:
    BLLContext(std::string const & currentDirectoryPath);

public:
    void init() const;

public:
	CircleImageEffectProvider _CircleEffect;
	NumericalValueImageEffectProvider _NumericalEffect;
	ThumbnailGenerator _ThumbnailGenerator;
	std::string RawVideosDirectoryPath;
	std::string EditedVideosDirectoryPath;

public:
    static constexpr const char* const RAW_DIR_NAME = "/Raw";
    static constexpr const char* const EDITED_DIR_NAME = "/Edited";
};

#endif // BLLCONTEXT_H
