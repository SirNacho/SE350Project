#pragma once
#include <string>

extern "C" {
  #include <leif/leif.h>
}

struct metaDataStruct
{
  std::string title;
  std::string artist;
  std::string album;
  int durationInSeconds;
  LfTexture thumbnail;
};

class metaDataHelper
{
  public:
    static metaDataStruct getMetaData(const std::string& filePath);
};
