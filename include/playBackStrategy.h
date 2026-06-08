#pragma once
#include "concreteStrategies.h"
#include "pathFileHelper.h"
#include <vector>
#include <string>
#include <random>
#include <algorithm>

//This strategy will play through the directory files one by one in order.
class sequentialPlaybackStrategy : public playBackStrategy
{
  private:
    std::vector<std::string> mPlaylist;
    int mCurrentIndex = 0;

  public:

    sequentialPlaybackStrategy(const std::string& inputPath) 
    {
      mPlaylist = getMusicFilesInDirectory(inputPath);
    }

    std::string getNextTrack() override 
    {
      if (mPlaylist.empty()) { return ""; }

      std::string track = mPlaylist[mCurrentIndex];
      mCurrentIndex = (mCurrentIndex + 1) % mPlaylist.size();
      return track;
    }

    std::string getPrevTrack() override
    {
      if (mPlaylist.empty()) { return ""; }

      int prevIndex = (mCurrentIndex - 2 + (mPlaylist.size() * 2)) % mPlaylist.size();
      mCurrentIndex = (prevIndex + 1) % mPlaylist.size();

      return mPlaylist[prevIndex];
    }
};

//this strategy will play through the directory files in a random order.
class shufflePlaybackStrategy : public playBackStrategy
{
  private:
    std::vector<std::string> mPlaylist;
    int mCurrentIndex = 0;
  
  public:
    shufflePlaybackStrategy(const std::string& inputPath) 
    {
      mPlaylist = getMusicFilesInDirectory(inputPath);
      
      //randomizes the mPlaylist list.
      std::random_device rd;
      std::mt19937 g(rd());
      std::shuffle(mPlaylist.begin(), mPlaylist.end(), g);
    }

    std::string getNextTrack() override 
    {
      if (mPlaylist.empty()) return "";

      std::string track = mPlaylist[mCurrentIndex];
      mCurrentIndex = (mCurrentIndex + 1) % mPlaylist.size();
      return track;
    }

    std::string getPrevTrack() override 
    {
      if (mPlaylist.empty()) { return ""; }
      
      int prevIndex = (mCurrentIndex - 2 + (mPlaylist.size() * 2)) % mPlaylist.size();
      mCurrentIndex = (prevIndex + 1) % mPlaylist.size();

      return mPlaylist[prevIndex];
    }
};
