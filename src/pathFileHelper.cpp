#include "pathFileHelper.h"
#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

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

  if (extension == ".mp3" || extension == ".wav" || extension == ".flac")
  {
    return true;
  } 
  else
  {
    return false;
  }
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

  for (const auto& entry : fs::directory_iterator(currentPath))
  {
    std::string currentPathStr = entry.path().string();

    if (isSupportedAudioFile(currentPathStr)) 
    { 
      musicFiles.push_back(currentPathStr); 
    }
  }

  return musicFiles;
}
