#include "audioEngine.h"
#include <iostream>

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
  printf("Directory: %s", pwd.c_str());
  if (m_isIntialized) { ma_engine_play_sound(&maEngine, pwd.c_str(), NULL); }
}
