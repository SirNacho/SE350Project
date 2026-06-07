#include <iostream>
#include <atomic>
#include <filesystem>
#include <string>
#include <cstdlib>

//define
#define MINIAUDIO_IMPLEMENTATION
namespace fs = std::filesystem;

//External Libraries
#include <GLFW/glfw3.h>
#include "miniaudio.h"

//Tells the compiler to only use C on leif
extern "C" {
    #include <leif/leif.h>
}

//Classes I made
#include "audioEngine.h"
#include "audioTest.h"
#include "appConfig.h"
#include "thumbnailHelper.h"
#include "pathFileHelper.h"
#include "IObserver.h"
#include "metaDataHelper.h"
#include "playBackStrategy.h"
#include "concreteStrategies.h"
#include "UIContext.h"
#include "nowPlayingState.h"
#include "IPlaybackCreator.h"


class UIController : public IObserver 
{
  private:
    audioEngine& engine;
    std::unique_ptr<playBackStrategy> strategy;

  public:
    std::atomic<bool> trackStateChanged{false};

    UIController(audioEngine& eng, std::unique_ptr<IPlaybackCreator> crt, const std::string& musicPath) : engine(eng) 
    {
      engine.attach(this);
      strategy = crt->create(musicPath);
    }

    ~UIController()
    {
      engine.detach(this);
    }
    
    void update() override
    {
      trackStateChanged = true;
    }
    
    std::string getNextTrack() { return strategy->getNextTrack(); }
};


int main(int argc, char* argv[])
{
  //Getting configuration based on arguments
  appConfig config = appConfig::parseArgs(argc, argv);
  //Created strategyCreator to get argument on playlist mode.
  std::unique_ptr<IPlaybackCreator> strategyCreator;

  if (config.justVersionName) { return EXIT_SUCCESS; }

  if (config.testMode) 
  {
    audioTest();
    return EXIT_SUCCESS;
  }

  if (config.shufflePlayback)
  {
    std::cout << "Started in shuffle playlist." << std::endl;
    strategyCreator = std::make_unique<shuffleCreator>();
  }
  else
  {
    std::cout << "Started in sequential playlist." << std::endl;
    strategyCreator = std::make_unique<sequentialCreator>();
  }

  std::string finalMusicPath = config.startingFilePath;
  
  if (finalMusicPath.empty()) 
  {
    finalMusicPath = getDefaultMusicDirectory();
    if (finalMusicPath.empty()) 
    {
      std::cerr << "Error: Couldn't determine the User's music directory. (Maybe ~/Music doesn't exist?)" << std::endl;
      return EXIT_FAILURE;
    }
  }

  //Audio Engine Setup
  audioEngine& engine = audioEngine::getInstance();
  
  //UI Setup



  UIController ui(engine, std::move(strategyCreator), finalMusicPath);
  UIContext uiContext(engine);
  
  //Leif (GUI) Setup
  
  if (!glfwInit()) 
  {
    std::cerr << "Failed to initialize gui *GLFW" << std::endl;
    return EXIT_FAILURE; 
  }
  
  GLFWwindow* window = glfwCreateWindow(uiContext.screenWidth, uiContext.screenHeight, "crisp", NULL, NULL);
  glfwMakeContextCurrent(window);

  lf_init_glfw(uiContext.screenWidth, uiContext.screenHeight, window);
  
  
  //Fetching directory and all music files in said directory.
  std::string pathText = "I'm currently in: " + finalMusicPath;
  std::string firstTrack = ui.getNextTrack();

  //Getting the meta data of the current track.
  metaDataStruct currentTrack;
  if (!firstTrack.empty()) 
  {
    currentTrack = metaDataHelper::getMetaData(firstTrack);
    engine.playFile(firstTrack);
  }


  uiContext.currentTrack = currentTrack;
  uiContext.changeState(std::make_unique<nowPlayingState>());

  //glfw ui loop
  while(!glfwWindowShouldClose(window)) {

    if (ui.trackStateChanged)
    {
      std::cout << "Track has finished or skipped, ready for the next song." << std::endl;

      std::string next = ui.getNextTrack();

      if(!next.empty())
      {
        uiContext.currentTrack = metaDataHelper::getMetaData(next);
        engine.playFile(next);
      }

      ui.trackStateChanged = false;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    //The state pattern is responsible for drawing the UI
    lf_begin();
    uiContext.requestDraw();
    lf_end();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  lf_terminate();
  glfwDestroyWindow(window);
  glfwTerminate();
  
  return EXIT_SUCCESS;

}

