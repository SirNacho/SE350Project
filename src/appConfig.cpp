#include "appConfig.h"
#include <iostream>
#include <unordered_map>
#include <memory>

namespace fs = std::filesystem;

/*
 * I rewrote this program cause I don't like how many if statements are there. Looks confusing to implement.
 * I will implement the command pattern on this since I feel this is a best pattern to fix this. -SF
 * */


//Concrete commands
class versionCommand : public ICommand
{
  
  private:
    appConfig& receiver;
  
  public:
    versionCommand(appConfig& config) : receiver(config) {}
    void execute(int& i, int argc, char* argv[]) override
    {
      std::cout << receiver.projectName << " Version " << receiver.projectVersion << std::endl;
      receiver.justVersionName = true;
    }

};

class testModeCommand : public ICommand 
{
  
  private:
    appConfig& receiver;
  
  public:
    testModeCommand(appConfig& config) : receiver(config) {}
    void execute(int& i, int argc, char* argv[]) override 
    {
      receiver.testMode = true;
    }
};

class headlessCommand : public ICommand 
{
  private:
    appConfig& receiver;
  public:
    headlessCommand(appConfig& config) : receiver(config) {}
    void execute(int& i, int argc, char* argv[]) override
    {
      receiver.headlessMode = true;
    }
};

class volumeCommand : public ICommand
{
  private:
    appConfig& receiver;

  public:
    volumeCommand(appConfig& config) : receiver(config) {}
    void execute(int& i, int argc, char* argv[]) override
    {
      if (i + 1 < argc)
      {
        try
        {
          receiver.initialVolume = std::stof(argv[i + 1]);
          i++;
        }
        catch (const std::exception& e)
        {
          std::cout << "Error: Invalid volume. Must be a number." << std::endl;
        }
      }
      else
      {
        std::cout << "error: --volume requires a value." << std::endl;
      }
    }
};

class pathCommand : public ICommand
{
  private:
    appConfig& receiver;
  public:
    pathCommand(appConfig& config) : receiver(config) {}
    void execute(int& i, int argc, char* argv[]) override
    {
      if (i + 1 < argc)
      {
        std::string inputPath = argv [i + 1];
        if (fs::exists(inputPath) && fs::is_directory(inputPath))
        {
          receiver.startingFilePath = inputPath;
        }
        else
        {
          std::cout << "Error: Path is invalid or not a directory." << std::endl;
        }
        i++;
      }
      else
      {
        std::cout << "Usage: " << receiver.projectName << " --path {directory}" << std::endl;
      }
    }
};

//Invoker and Client
appConfig appConfig::parseArgs(int argc, char* argv[])
{
  appConfig config;

  std::unordered_map<std::string, std::unique_ptr<ICommand>> commands;

  commands["--version"]     = std::make_unique<versionCommand>(config);
  commands["-v"]            = std::make_unique<versionCommand>(config);

  commands["--test"]        = std::make_unique<testModeCommand>(config);
  commands["-t"]            = std::make_unique<testModeCommand>(config);

  commands["--headless"]    = std::make_unique<headlessCommand>(config);
  commands["-hl"]          = std::make_unique<headlessCommand>(config);

  commands["--volume"]      = std::make_unique<volumeCommand>(config);
  commands["-vo"]           = std::make_unique<volumeCommand>(config);

  commands["--path"]        = std::make_unique<pathCommand>(config);
  commands["-p"]            = std::make_unique<pathCommand>(config);

  for (int i = 1; i < argc; i++)
  {
    std::string arg = argv[i];
    auto it = commands.find(arg);

    if (it != commands.end()) { it->second->execute(i, argc, argv); }
    else { std::cout << "warning: Unknown argument '" << arg << "'" << std::endl; }
  }

  return config;
}
