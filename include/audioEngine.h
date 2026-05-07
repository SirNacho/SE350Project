#pragma once
#include <string>
#include "miniaudio.h"

class audioEngine 
{
  public:
  audioEngine();
  ~AudioEngine();

  bool init();
  void playFile(const std::String& pwd);
  void stop();

  private:
  //Note: This is so that the program won't access miniaudio except for this class.
  miniAudioEngine maEngine;
  bool m_isIntialized = false;
}
