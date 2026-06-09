#pragma once
#include <string>

class playBackStrategy 
{
  public:
    virtual ~playBackStrategy() = default;
    
    virtual std::string getNextTrack() = 0;
    virtual std::string getPrevTrack() = 0;
};
