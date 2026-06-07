#pragma once
#include "IUIState.h"
#include "UIContext.h"

extern "C"{
  #include <leif/leif.h>
}

class nowPlayingState : public IUIState
{
  private:
    LfSlider progressSlider;
    int32_t currentProgress;

  public:
    nowPlayingState();

    void draw(UIContext* context) override;
};
