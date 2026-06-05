#include <iostream>
#include <atomic> //Note: This is for multi threading
#include <filesystem>
#include <string>

//define
#define MINIAUDIO_IMPLEMENTATION

namespace fs = std::filesystem;

//External Libraries
#include <GLFW/glfw3.h>

//Tells the compiler to only use C on leif
extern "C" {
    #include <leif/leif.h>
}

#include "miniaudio.h"

//Classes I made
#include "audioEngine.h"
#include "audioTest.h"
#include "appConfig.h"

//Constants
constexpr int screenWidth = 640;
constexpr int screenHeight = 480;

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
  
  //Audio Engine Setup
  audioEngine& engine = audioEngine::getInstance();
  
  //Leif (GUI) Setup
  
  if (!glfwInit()) 
  {
    std::cerr << "Failed to initialize gui *GLFW" << std::endl;
    return EXIT_FAILURE; // Exit the program if graphics fail
  }
  
  // If we made it here, GLFW initialized successfully! Create the window.
  GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Hello", NULL, NULL);
  glfwMakeContextCurrent(window);

  lf_init_glfw(screenWidth, screenHeight, window);

  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    lf_begin();

    lf_text("Hello, SE350!");

    lf_end();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  lf_terminate();
  glfwDestroyWindow(window);
  glfwTerminate();
  
  return EXIT_SUCCESS;

}

