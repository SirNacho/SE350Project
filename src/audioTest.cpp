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

//Strats
#include "concreteStrategies.h"
#include "playBackStrategy.h"

int audioTest()
{
    
    /*
     * Note: This function is to test if music is able to play.
     * It uses src/assets folder to test the music in sequential and shuffled playback modes. -SF
     *
     */ 

    audioEngine& engine = audioEngine::getInstance();
    
    try
    {
        //Path Check Section
        fs::path pwd = fs::current_path();
        std::cout << "Current directory: " << pwd << std::endl;
        
        fs::path testPath = pwd / "src" / "assets";
        
        if (!fs::is_directory(testPath)) 
        {
          std::cout << "Please put me at the root of the repo so that I can reach src/assets" << std::endl;
          std::cout << "Error: This path " << testPath.string() << " doesn't exist. Shutting down the program..." << std::endl;
          return 0;
        }
        
        //Music Files Check Section
        std::vector<std::string> availableTracks = getMusicFilesInDirectory(testPath);
        int trackCount = availableTracks.size();

        if (trackCount == 0) 
        {
          std::cout << "Error: No supported audio files found in " << testPath.string() << std::endl; 
          return 0;
        }
        
        //test 1 section (SequentialPlaybackStrategy)
        std::cout << "Test 1: Testing sequential strategy" << std::endl;
        std::unique_ptr<playBackStrategy> seqStrategy = std::make_unique<sequentialPlaybackStrategy>(testPath.string());

        for (int i = 0; i < trackCount; i++) 
        {
          std::string nextTrack = seqStrategy->getNextTrack();
          if (nextTrack.empty()) { break; }

          std::cout << "(Sequential) Playing (" << (i + 1) << "/" << trackCount << "): " << nextTrack << std::endl;
          engine.playFile(nextTrack);

          std::this_thread::sleep_for(std::chrono::seconds(10));
        }

        //Test 2 Section (shufflePlaybackStrategy)
        std::cout << "Test 2: Testing shuffle strategy" << std::endl;
        std::unique_ptr<playBackStrategy> shuffleStrategy = std::make_unique<shufflePlaybackStrategy>(testPath.string());

        for (int i = 0; i < trackCount; i++)
        {
          std::string nextTrack = shuffleStrategy->getNextTrack();
          if (nextTrack.empty()) { break; }

          std::cout << "(Shuffle) Playing (" << (i + 1) << "/" << trackCount << "): " << nextTrack << std::endl;
          engine.playFile(nextTrack);
          std::this_thread::sleep_for(std::chrono::seconds(10));
        }

        std::cout << "\n Test is completed, stopping engine..." << std::endl;
        engine.stop();

        std::cout << "Press enter to exit:" << std::endl;
        std::cin.get();

        return 1;

    }
    catch (const fs::filesystem_error& e)
    {
        std::cout << "Error: cannot get directory of the music library. Shutting down the program...\n" << std::endl;
        return 0;
    }
}
