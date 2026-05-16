#include <iostream>
#include <atomic> //Note: This is for multi threading
#include <filesystem>

namespace fs = std::filesystem;

//External Libraries
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include "miniaudio.h"

//Classes I made
#include "audioEngine.h"

int audioTest()
{
    
    /*
     * Note: This function is to test if music is able to play.
     * It uses test.mp3 on src/assets to test the music. -SF
     *
     */ 

    audioEngine engine;
    
    try
    {
        fs::path pwd = fs::current_path();
        std::cout << "Current directory: \n" << pwd << std::endl;
        std::cout << "Playing test music... Press enter to stop." << std::endl;
        fs::path testPath = pwd / "src" / "assets" / "test.mp3";
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
