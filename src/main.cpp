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

//Constants
constexpr int kScreenWidth = 640;
constexpr int kScreenHeight = 480;

int main(int argc, char* argv[])
{

  audioEngine engine;

  try
  {
    fs::path pwd = fs::current_path();
    std::cout << "Current directory: \n" << pwd << std::endl;
  }
  catch (const fs::filesystem_error& e)
  {
    std::cout << "Error: cannot get directory of the music library. Shutting down the program...\n" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Playing test music... Press enter to stop.\n" << std::endl;
  engine.playFile("assets/test.mp3")
  std::cin.get();

  std::cout << "Stopped music!" << std::endl;

  
  
  return EXIT_SUCCESS;
}
