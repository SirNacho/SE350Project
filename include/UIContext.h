#pragma once
#include <memory>

#include "IUIState.h"
#include "audioEngine.h"
#include "metaDataHelper.h"

class UIContext
{
  private:
    std::unique_ptr<IUIState> state;

  public:
    audioEngine& engine;
    metaDataStruct currentTrack;
    
    const int screenWidth = 768;
    const int screenHeight = 1050;
    
    UIContext(audioEngine& eng) : engine(eng), state(nullptr) {}
    
    void changeState(std::unique_ptr<IUIState> newState) { state = std::move(newState); }
    
    void requestDraw()
    {
      if (state) { state->draw(this); }
    }
};
