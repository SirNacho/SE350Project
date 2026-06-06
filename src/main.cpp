#include <iostream>
#include <atomic> //Note: This is for multi threading
#include <filesystem>
#include <string>
#include <cstdlib>

//define
#define MINIAUDIO_IMPLEMENTATION

namespace fs = std::filesystem;

//External Libraries

//Tells the compiler to only use C on leif
extern "C" {
    #include <leif/leif.h>
}
#include <GLFW/glfw3.h>
#include "miniaudio.h"

//Classes I made
#include "audioEngine.h"
#include "audioTest.h"
#include "appConfig.h"
#include "thumbnailHelper.h"
#include "pathFileHelper.h"
#include "IObserver.h"

//Constants
constexpr int screenWidth = 640;
constexpr int screenHeight = 480;

class UIController : public IObserver 
{
  private:
    audioEngine& engine;

  public:
    std::atomic<bool> trackStateChanged{false};

    UIController(audioEngine& eng) : engine(eng) 
    {
      engine.attach(this);
    }

    ~UIController()
    {
      engine.detach(this);
    }
    
    void update() override
    {
      //Note: this flips the flag and get out of the background thread.
      trackStateChanged = true;
    }
};


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

  std::string finalMusicPath = "";

  if (config.startingFilePath.empty())
  {
    const char* homeEnv = std::getenv("HOME");

    if (homeEnv == nullptr) 
    {
      homeEnv = std::getenv("USERPROFILE");
    }

    if (homeEnv != nullptr) 
    {
      fs::path musicPath = fs::path(homeEnv) / "Music";
      
      if (!fs::exists(musicPath) || !fs::is_directory(musicPath))
      {
        std::cerr << "Error: Default music directory not found at " << musicPath << std::endl;
        return EXIT_FAILURE;
      }
      
      finalMusicPath = musicPath.string(); 
    }
    else 
    {
      std::cerr << "Error: Unable to get the home directory." << std::endl;
      return EXIT_FAILURE;
    }
  }
  else
  {
    finalMusicPath = config.startingFilePath;
  }
   
  //Audio Engine Setup
  audioEngine& engine = audioEngine::getInstance();
  
  UIController ui(engine);

  //Leif (GUI) Setup
  
  if (!glfwInit()) 
  {
    std::cerr << "Failed to initialize gui *GLFW" << std::endl;
    return EXIT_FAILURE; 
  }
  
  GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "crisp", NULL, NULL);
  glfwMakeContextCurrent(window);

  lf_init_glfw(screenWidth, screenHeight, window);
  
  
  //Fetching directory and all music files in said directory.
  std::string pathText = "I'm currently in: " + finalMusicPath;
  std::vector<std::string> musicFiles = getMusicFilesInDirectory(finalMusicPath);

  while(!glfwWindowShouldClose(window)) {

    if (ui.trackStateChanged)
    {
      if (!engine.isPlaying())
      {
        std::cout <<"\nTrack has finished or stopped, ready for the next song." << std::endl;
      }
      else
      {
        std::cout << "\n A new track started playing." << std::endl;
      }

      ui.trackStateChanged = false;
    }


    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    lf_begin();

    lf_text("Hello, SE350!");
    lf_next_line();
    lf_text(pathText.c_str());
    lf_next_line();
    lf_text("Available Tracks:");
    lf_next_line();

    if (musicFiles.empty()) 
    {
      lf_text("No supported audio files can be found.");
    }
    else 
    {
      for (const std::string& filePath : musicFiles) 
      {
        std::string fileName = fs::path(filePath).filename().string();

        lf_text(fileName.c_str());
        lf_next_line();
      }
    }
    
    lf_end();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  lf_terminate();
  glfwDestroyWindow(window);
  glfwTerminate();
  
  return EXIT_SUCCESS;

}

