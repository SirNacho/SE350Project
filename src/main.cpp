#include <iostream>
#include <atomic>
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
#include "metaDataHelper.h"
#include "playBackStrategy.h"
#include "concreteStrategies.h"

//Constants
constexpr int screenWidth = 768;
constexpr int screenHeight = 1050;

class UIController : public IObserver 
{
  private:
    audioEngine& engine;
    std::unique_ptr<playBackStrategy> strategy;

  public:
    std::atomic<bool> trackStateChanged{false};

    UIController(audioEngine& eng, const std::string& musicPath) : engine(eng) 
    {
      engine.attach(this);
      strategy = std::make_unique<sequentialPlaybackStrategy>(musicPath);
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

  if (config.justVersionName) { return EXIT_SUCCESS; }

  if (config.testMode) 
  {
    audioTest();
    return EXIT_SUCCESS;
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
  
  UIController ui(engine, finalMusicPath);

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
  std::string firstTrack = ui.getNextTrack();

  //Getting the meta data of the current track.
  metaDataStruct currentTrack;
  if (!firstTrack.empty()) 
  {
    currentTrack = metaDataHelper::getMetaData(firstTrack);
    engine.playFile(firstTrack);
  }

  //Slider Setup:
  int32_t currentProgress = 0;
  int32_t maxDuration = currentTrack.durationInSeconds;

  LfSlider progressSlider = {0};
  progressSlider.val = &currentProgress;
  progressSlider.min = 0;
  progressSlider.max = maxDuration;
  progressSlider.width = 400;
  progressSlider.height = 5;
  progressSlider.handle_size = 15;
  
  //glfw ui loop
  while(!glfwWindowShouldClose(window)) {

    if (ui.trackStateChanged)
    {
      std::cout << "Track has finished or skipped, ready for the next song." << std::endl;

      std::string next = ui.getNextTrack();
      if(!next.empty())
      {
        currentTrack = metaDataHelper::getMetaData(next);
        engine.playFile(next);

        maxDuration = currentTrack.durationInSeconds;
        progressSlider.max = maxDuration;
      }

      ui.trackStateChanged = false;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    lf_begin();
    lf_set_ptr_y_absolute(100.0f);
    
    //Gets the thumbnail image
    if (currentTrack.thumbnail.id != 0)
    {
      float imageX = (screenWidth - currentTrack.thumbnail.width) / 2.0f;
      lf_set_ptr_x_absolute(imageX);
      lf_image(currentTrack.thumbnail);
    }
    else
    {
      const char* noArtText = "No Album art is found.";
      float textX = (screenWidth - lf_text_dimension(noArtText).x) / 2.0f;
      lf_set_ptr_x_absolute(textX);
      lf_text(noArtText);
    }
    lf_next_line();

    lf_set_ptr_y_absolute(lf_get_ptr_y() + 20.0f);

    //Gets the title metadata
    const char* titleText = currentTrack.title.c_str();
    float titleX = (screenWidth - lf_text_dimension(titleText).x) / 2.0f;
    lf_set_ptr_x_absolute(titleX);
    lf_text(titleText);

    lf_next_line();
    
    //Gets the artist and album metadata
    std::string subTextStr = currentTrack.artist + " - " + currentTrack.album;
    const char* subText = subTextStr.c_str();
    float subTextX = (screenWidth - lf_text_dimension(subText).x) / 2.0f;
    lf_set_ptr_x_absolute(subTextX);
    lf_text(subText);

    lf_next_line();
    
    //Set up the slider and slider state
    lf_set_ptr_y_absolute(lf_get_ptr_y() + 20.0f);

    float sliderX = (screenWidth - progressSlider.width) / 2.0f;
    lf_set_ptr_x_absolute(sliderX);
    
    if(!progressSlider.held) { currentProgress = engine.getPlaybackPosition(); }

    LfClickableItemState sliderState = lf_slider_int(&progressSlider);
    lf_next_line();

    if (sliderState == LF_CLICKED || sliderState == LF_RELEASED)
    {
      engine.setPlaybackPosition(currentProgress);
    }
    
    int curMin = currentProgress / 60;
    int curSec = currentProgress % 60;
    int toMin = maxDuration / 60;
    int toSec = maxDuration % 60;
    
    //Gets the current time and song duration time
    char timeText[64];

    snprintf(timeText, sizeof(timeText), "%d:%02d / %d:%02d", curMin, curSec, toMin, toSec);
    
    float timeX = (screenWidth - lf_text_dimension(timeText).x) / 2.0f;
    lf_set_ptr_x_absolute(timeX);
    lf_text(timeText);
    lf_next_line();

    //Sets up the play and pause button
    lf_set_ptr_y_absolute(lf_get_ptr_y() + 20.0f);
    const char* buttonText = engine.isAudioPlaying() ? "Pause" : "Play";

    float buttonWidth = 100.0f;
    float buttonX = (screenWidth - buttonWidth) / 2.0f;
    lf_set_ptr_x_absolute(buttonX);
    
    //Checks if the button is clicked.
    if (lf_button_fixed(buttonText, buttonWidth, -1) == LF_CLICKED)
    {
      engine.togglePlayPause();
    }
    lf_next_line();

    lf_end();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  lf_terminate();
  glfwDestroyWindow(window);
  glfwTerminate();
  
  return EXIT_SUCCESS;

}

