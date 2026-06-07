#pragma once
#include <string>
#include <vector>

std::string getDefaultMusicDirectory();

bool checkAudioPath(const std::string& inputPath);

bool isSupportedAudioFile(const std::string& inputPath);

std::vector<std::string> getMusicFilesInDirectory(const std::string& inputPath);
