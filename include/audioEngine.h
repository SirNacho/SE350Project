#pragma once
#include <string>
#include "miniaudio.h"

class audioEngine 
{
  public:
    audioEngine();
    ~audioEngine();

    bool init();
    void playFile(const std::string& pwd);
    void stop();

  private:
    //Note: This is so that the program won't access miniaudio except for this class.
    ma_engine maEngine;
    bool m_isIntialized = false;
};
