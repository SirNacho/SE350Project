#include "appConfig.h"
#include <iostream>
#include <filesystem>
#include <string>

appConfig appConfig::parseArgs(int argc, char* argv[]) 
{
  /*
   * parseArgs: Parses the args and return a 
   * 
   */ 

  appConfig config;

  for (int i = 1; i < argc; i++) 
  {

    /*
     * NOTE: I do a simple if else cases since the project is simple.
     * In the future, if there is too much options, use a unordered map. -SF
     * 
     */

    std::string arg = argv[i];

    if (arg == "--version" || arg == "-v")
    {
      std::cout << config.projectName << " Version " << config.projectVersion << std::endl;
      config.justVersionName = true;
    }

    if (arg == "--test" || arg == "-t")
    {
      config.testMode = true;
    }

    if (arg == "--headless" || arg == "-hl") 
    {
      config.headlessMode = true;
    }

    else if (arg == "--volume" || arg == "-v") 
    {
      if (i + 1 < argc) 
      {
        try 
        {
          config.initialVolume = std::stof(argv[i + 1]);
          i++;
        }

        catch (const std::out_of_range& e) 
        {
          std::cout << "Error: Volume number is too large or small" << std::endl;
        }

        catch (const std::invalid_argument& e) 
        {
          std::cout << "Error: Invalid volume. Must be a number" << std::endl;
          std::cout << "Usage: " << config.projectName << " --volume {0.0f - 1.0f}" << std::endl;
        }
      }
      else
      {
        std::cout << "Error: --volume requires a value.\n";
        std::cout << "Usage: " << config.projectName << " --volume {0.0f - 1.0f}" << std::endl;
      }
    }

    else if (arg == "--path" || arg == "-p") 
    {
      if (i + 1 < argc)
      {
        std::string inputPath = argv[i + 1];

        if (fs::exists(inputPath)) 
        {
          if (fs::is_directory(inputPath)) 
          {
            config.startingFilePath = inputPath;
          }
          else
          {
            std::cout << "Error: This path exists, but it is a file, not a folder." << std::endl;
          }
        }
        else 
        {
          std::cout << "Error: This path doesn't exist." << std::endl;
        }
      }
      else
      {
        std::cout << "Usage: " << config.projectName << " --path {path to music directory}" << std::endl;
      }
    }
  }

  return config;
}
