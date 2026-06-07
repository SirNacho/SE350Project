#pragma once

class UIContext;

class IUIState
{
  public:
    virtual ~IUIState() = default;
    
    virtual void draw(UIContext* context) = 0;
};
