#include "thumbnailHelper.h"

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tbytevector.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>

#include <glad/glad.h>

#include <stb_image.h>

#include <iostream>

LfTexture loadMp3Thumbnail(const std::string& filepath) 
{
  LfTexture texture = {0, 0, 0};

  TagLib::MPEG::File file(filepath.c_str());
  TagLib::ID3v2::Tag *id3v2tag = file.ID3v2Tag();

  if (!id3v2tag) return texture;

  TagLib::ID3v2::FrameList frames = id3v2tag->frameListMap()["APIC"];
  if (frames.isEmpty()) return texture;

  TagLib::ID3v2::AttachedPictureFrame *frame = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frames.front());
  TagLib::ByteVector pictureBytes = frame->picture();

  int width, height, channels;
  unsigned char* pixels = stbi_load_from_memory(
      (const unsigned char*)pictureBytes.data(),
      pictureBytes.size(),
      &width, &height, &channels, 4
      );

  if (pixels) 
  {
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(pixels);

    texture.id = textureId;
    texture.width = width;
    texture.height = height;
  }

  return texture;
}
