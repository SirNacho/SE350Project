#include "audioEngine.h"
#include <iostream>

audioEngine& audioEngine::getInstance()
{
  static audioEngine instance; //Gets destroyed and Intialized on first use thread safely
  return instance;
}

audioEngine::audioEngine() 
{
  if (init()) 
  {
    std::cout << "Audio Engine Intialized!" << std::endl;
  }
}

audioEngine::~audioEngine() 
{
  if (m_isIntialized) { ma_engine_uninit(&maEngine); }
}

bool audioEngine::init() 
{
  if (ma_engine_init(NULL, &maEngine) != MA_SUCCESS) { return false; }
  m_isIntialized = true;
  return true;
}

void audioEngine::playFile(const std::string& pwd) 
{
  if (!m_isIntialized) return;
  
  std::cout << "Loading File: " << pwd << std::endl;

  if (mSoundLoaded) 
  {
    ma_sound_stop(&mCurrentSound);
    ma_sound_uninit(&mCurrentSound);
    mSoundLoaded = false;
  }

  ma_result result = ma_sound_init_from_file(
      &maEngine,
      pwd.c_str(),
      0,                //Sound flags
      NULL,             //Group routing
      NULL,             //Explicit fence notification handler
      &mCurrentSound
    );
  
  if (result == MA_SUCCESS) 
  {
    mSoundLoaded = true;
    ma_sound_start(&mCurrentSound);
  }
  else
  {
    std::cout << "Error: Miniaudio has failed to load the sound file." << std::endl;
  }
}

void audioEngine::stop()
{
  if (m_isIntialized && mSoundLoaded)
  {
    ma_sound_stop(&mCurrentSound);
    std::cout << "Playback stopped." << std::endl;
  }
}

