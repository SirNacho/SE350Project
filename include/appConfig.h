#pragma once
#include <string>
#include <vector>
#include <filesystem>

struct appConfig 
{
  //Profile Settings
  std::string startingFilePath = "";
  bool shufflePlayback = false;
  float initialVolume = 1.0f;
  bool headlessMode = false;
  bool justVersionName = false; //Seems inefficent but I'll fix it later. -SF
  bool testMode = false;
  std::string projectName = "Crisp"; //Note: remember to replace this with cmake project name and version! -SF
  std::string projectVersion = "1.5";
  

  static appConfig parseArgs(int argc, char* argv[]);
};

class ICommand
{
  public:
    virtual ~ICommand() = default;
    virtual void execute(int& i, int argc, char*[]) = 0;
};
