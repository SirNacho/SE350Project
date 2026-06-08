#pragma once
#include <string>
#include <vector>
#include <atomic>

#include "miniaudio.h"
#include "ISubject.h"

class audioEngine : public ISubject
{

  /*
   * Redoing audioEngine.cpp and header file to allign with observers pattern.
   * This is to save CPU resource as I find it a bit lacking when I have to use
   * a while loop for the engine in main.cpp. -SF
   * */
  
  public:
    static audioEngine& getInstance();
    
    //Functions that handles how the engine should play or handles music.
    void playFile(const std::string& pwd);
    void stop();
    void togglePlayPause();
    bool isAudioPlaying();
    void handleSoundEnd();
    int getPlaybackPosition();
    void setPlaybackPosition(int seconds);

    //observers implementation.
    void attach(IObserver* observer) override;
    void detach(IObserver* observer) override;
    void notifyObservers() override;

    bool isTrackLoaded() const { return mSoundLoaded; }

  private:
    std::vector<IObserver*> observers;

    //Note: This is so that the program won't access miniaudio except for this class.
    //(Based on Singleton pattern)
    audioEngine();
    ~audioEngine();

    ma_engine maEngine;
    bool m_isIntialized = false;

    ma_sound mCurrentSound;
    std::atomic<bool> mSoundLoaded{false};

    //Note: To delete copy constructor and assignment operator to enforce Singleton pattern.
    audioEngine(const audioEngine&) = delete;
    audioEngine& operator=(const audioEngine&) = delete;

    bool init();
};
