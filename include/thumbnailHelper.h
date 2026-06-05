#pragma once
#include <string>

extern "C" 
{
#include <leif/leif.h>
}

LfTexture loadMp3Thumbnail(const std::string& filepath);
