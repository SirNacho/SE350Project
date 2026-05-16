#pragma once
#include <string>
#include <vector>

bool checkAudioPath(const std::string& inputPath);

bool isSupportedAudioFile(const std::string& inputPath);

std::vector<std::string> getMusicFilesInDirectory(const std::string& inputPath);
