#include "metaDataHelper.h"
#include "thumbnailHelper.h"

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/audioproperties.h>
#include <filesystem>

metaDataStruct metaDataHelper::getMetaData(const std::string& filePath)
{
  metaDataStruct data;

  data.title = std::filesystem::path(filePath).filename().string();
  data.artist = "Placeholder Artist";
  data.album = "Placeholder Album";
  data.durationInSeconds = 0;
  data.thumbnail = {0, 0, 0};

  TagLib::FileRef f(filePath.c_str());

  if (!f.isNull() && f.tag())
  {
    TagLib::Tag *tag = f.tag();
    if(!tag->title().isEmpty()) { data.title = tag->title().to8Bit(true); }
    if(!tag->artist().isEmpty()) { data.artist = tag->artist().to8Bit(true); }
    if(!tag->album().isEmpty()) { data.album = tag->album().to8Bit(true); }
  }

  if(!f.isNull() && f.audioProperties())
  {
    TagLib::AudioProperties *properties = f.audioProperties();
    data.durationInSeconds = properties->lengthInSeconds();
  }
  
  data.thumbnail = loadMp3Thumbnail(filePath);
  return data;
}
