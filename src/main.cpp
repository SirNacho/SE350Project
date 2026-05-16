#include <iostream>
#include <atomic> //Note: This is for multi threading
#include <filesystem>

//define
#define MINIAUDIO_IMPLEMENTATION

namespace fs = std::filesystem;

//External Libraries
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include "miniaudio.h"

//Classes I made
#include "audioEngine.h"
#include "audioTest.h"
#include "appConfig.h"

//Constants
constexpr int kScreenWidth = 640;
constexpr int kScreenHeight = 480;

int main(int argc, char* argv[])
{
  //Getting configuration based on arguments
  appConfig config = appConfig::parseArgs(argc, argv);
  
  if (config.justVersionName) { return EXIT_SUCCESS; }

  if (config.testMode) 
  {
    audioTest();
    return EXIT_SUCCESS;
  }

  audioEngine& engine = audioEngine::getInstance();
  
  std::cout << "Hello!\n";
  
  return EXIT_SUCCESS;

}

