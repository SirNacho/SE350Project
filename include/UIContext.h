#pragma once
#include <memory>

#include "IUIState.h"
#include "audioEngine.h"
#include "metaDataHelper.h"

//Handles the UI of the app using state pattern. 
//Loads the UI from nowPlayingState.cpp instead of main.cpp.
class UIContext
{

  private:
    std::unique_ptr<IUIState> state;

  public:
    audioEngine& engine;
    metaDataStruct currentTrack;
    
    int screenWidth = 770;
    int screenHeight = 1050;
    
    bool requestNext = false;
    bool requestPrev = false;

    UIContext(audioEngine& eng) : engine(eng), state(nullptr) {}
    
    void changeState(std::unique_ptr<IUIState> newState) { state = std::move(newState); }
    
    void requestDraw()
    {
      if (state) { state->draw(this); }
    }
};
