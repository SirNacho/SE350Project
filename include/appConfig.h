#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

struct appConfig 
{
  //Profile Settings
  std::string startingFilePath = "";
  float initialVolume = 1.0f;
  bool headlessMode = false;
  bool justVersionName = false; //Seems inefficent but I'll fix it later. -SF
  bool testMode = false;
  std::string projectName = "SE350 Engine"; //Note: remember to replace this with cmake project name and version! -SF
  std::string projectVersion = "1.1";
  

  static appConfig parseArgs(int argc, char* argv[]);
};
