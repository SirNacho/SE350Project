#pragma once

#include <memory>
#include <string>

#include "playBackStrategy.h"
#include "concreteStrategies.h"

class IPlaybackCreator
{
  public:
    virtual ~IPlaybackCreator() = default;

    virtual std::unique_ptr<playBackStrategy> create(const std::string& musicPath) = 0;
};

class sequentialCreator : public IPlaybackCreator
{
  public:
    std::unique_ptr<playBackStrategy> create(const std::string& musicPath) override
    {
      return std::make_unique<sequentialPlaybackStrategy>(musicPath);
    }
};

class shuffleCreator : public IPlaybackCreator
{
  public:
    std::unique_ptr<playBackStrategy> create(const std::string& musicPath) override
    {
      return std::make_unique<shufflePlaybackStrategy>(musicPath);
    }
};
