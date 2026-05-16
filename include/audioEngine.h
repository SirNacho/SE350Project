#pragma once
#include <string>
#include "miniaudio.h"

class audioEngine 
{
  public:
    static audioEngine& getInstance();
    
    //Note: I am deleting copy constructor and assignment operators so that the audioEngine can't be copied.
    //      I am using the singleton pattern.
    audioEngine(const audioEngine&) = delete;
    void operator=(const audioEngine&) = delete;

    bool init();
    void playFile(const std::string& pwd);
    void stop();

  private:
    //Note: This is so that the program won't access miniaudio except for this class.
    
    audioEngine();
    ~audioEngine();

    ma_engine maEngine;
    bool m_isIntialized = false;

    ma_sound mCurrentSound;
    bool mSoundLoaded = false;
};
