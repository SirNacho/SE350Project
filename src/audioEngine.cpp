#include "audioEngine.h"

#include <iostream>
#include <algorithm>

//Acts as a trigger that fires automatically when a song finishes.
void soundEndCallback(void* pUserData, ma_sound* pSound)
{
  audioEngine* engine = static_cast<audioEngine*>(pUserData);

  engine->handleSoundEnd();
}

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

//observer pattern implementation section:
void audioEngine::attach(IObserver* observer)
{
  observers.push_back(observer);
}

void audioEngine::detach(IObserver* observer)
{
  observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void audioEngine::notifyObservers()
{
  for (IObserver* obs : observers)
  {
    obs->update();
  }
}

void audioEngine::handleSoundEnd()
{
  notifyObservers();
}


//audio controls section:
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

    ma_sound_set_end_callback(&mCurrentSound, soundEndCallback, this);

    ma_sound_start(&mCurrentSound);
  }
  else
  {
    std::cout << "Error: Miniaudio has failed to load the sound file." << std::endl;
  }
}

void audioEngine::togglePlayPause()
{
  //Checks if no song is loaded
  if (!mSoundLoaded) { return; }

  if(ma_sound_is_playing(&mCurrentSound)) { ma_sound_stop(&mCurrentSound); }
  else { ma_sound_start(&mCurrentSound); }
}

bool audioEngine::isAudioPlaying() 
{
  if (!mSoundLoaded) { return false; }
  return ma_sound_is_playing(&mCurrentSound);
}

int audioEngine::getPlaybackPosition()
{
  if (!mSoundLoaded) { return 0; }

  ma_uint64 cursorFrames;
  ma_sound_get_cursor_in_pcm_frames(&mCurrentSound, &cursorFrames);

  ma_uint32 sampleRate;
  ma_sound_get_data_format(&mCurrentSound, NULL, NULL, &sampleRate, NULL, 0);

  if(sampleRate == 0) { return 0; }
  return (int)(cursorFrames / sampleRate);
}

void audioEngine::setPlaybackPosition(int seconds)
{
  if (!mSoundLoaded) { return; }

  ma_uint32 sampleRate;
  ma_sound_get_data_format(&mCurrentSound, NULL, NULL, &sampleRate, NULL, 0);

  ma_uint64 targetFrame = (ma_uint64)seconds * sampleRate;
  ma_sound_seek_to_pcm_frame(&mCurrentSound, targetFrame);
}

void audioEngine::stop()
{
  if (m_isIntialized && mSoundLoaded)
  {
    ma_sound_stop(&mCurrentSound);
    mSoundLoaded = false;
    std::cout << "Playback stopped." << std::endl;

    //Let the UI know that playback was manually stop.
    notifyObservers();
  }
}

