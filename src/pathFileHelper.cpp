#include "pathFileHelper.h"
#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

//This is where I mostly put directory related functions.

bool checkAudioPath(const std::string& inputPath)
{
  fs::path currentPath(inputPath);
  
  if (fs::exists(currentPath) && fs::is_regular_file(currentPath)) { return true; }
  
  return false;
}

bool isSupportedAudioFile(const std::string& inputPath)
{
  if (!checkAudioPath(inputPath)) { return false; }

  fs::path currentPath(inputPath);
  std::string extension = currentPath.extension().string();

  if (extension == ".mp3" || extension == ".wav" || extension == ".flac"){ return true; } 
  else{ return false; }
}

std::vector<std::string> getMusicFilesInDirectory(const std::string& inputPath)
{
  std::vector<std::string> musicFiles;
  fs::path currentPath(inputPath);

  if (!fs::exists(inputPath) || !fs::is_directory(currentPath))
  {
    std::cout << "Error: Invalid directory path provided." << std::endl;
    return musicFiles;
  }
  
  for (const auto& entry : fs::recursive_directory_iterator(currentPath))
  {
    std::string currentPathStr = entry.path().string();

    if (isSupportedAudioFile(currentPathStr)) { musicFiles.push_back(currentPathStr); }
  }
   
  return musicFiles;
}


//Note: Although Crisp doesn't have windows support, I thought to check for windows
//directory anyway in case I do support windows some day. -SF
std::string getDefaultMusicDirectory() 
{
  const char* homeEnv = std::getenv("HOME");
  if (homeEnv == nullptr) { homeEnv = std::getenv("USERPROFILE"); }

  if (homeEnv != nullptr) 
  {
    fs::path musicPath = fs::path(homeEnv) / "Music";
    if (fs::exists(musicPath) && fs::is_directory(musicPath)) 
    {
      return musicPath.string();
    }
  }

  return "";
}
