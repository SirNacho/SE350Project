#include <iostream>
#include <atomic> //Note: This is for multi threading
#include <filesystem>
#include <vector>
#include <chrono>
#include <thread>

namespace fs = std::filesystem;

//External Libraries
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include "miniaudio.h"

//Classes I made
#include "audioEngine.h"
#include "pathFileHelper.h"

int audioTest()
{
    
    /*
     * Note: This function is to test if music is able to play.
     * It uses test.mp3 on src/assets to test the music. -SF
     *
     */ 

    audioEngine& engine = audioEngine::getInstance();
    
    try
    {
        fs::path pwd = fs::current_path();
        std::cout << "Current directory: " << pwd << std::endl;
        
        fs::path testPath = pwd / "src" / "assets" / "test.mp3";
        
        if (!fs::exists(testPath)) 
        {
          std::cout << "Please put me at the root of the repo so that I can reach src/assets/test.mp3." << std::endl;
          std::cout << "Error: This path " << testPath.string() << " doesn't exist. Shutting down the program..." << std::endl;
          return 0;
        }

        std::cout << "Playing test music... Press enter to stop." << std::endl;
        engine.playFile(testPath.string());
        std::cin.get();

        std::cout << "Stopped music!" << std::endl;
        return 1;
    }
    catch (const fs::filesystem_error& e)
    {
        std::cout << "Error: cannot get directory of the music library. Shutting down the program...\n" << std::endl;
        return 0;
    }
}
