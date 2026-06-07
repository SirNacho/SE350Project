#include <string>

#include "nowPlayingState.h"

//Setting up progessSlider
nowPlayingState::nowPlayingState() : currentProgress(0)
{
  progressSlider = {0};
  progressSlider.val = &currentProgress;
  progressSlider.min = 0;
  progressSlider.max = 0;
  progressSlider.width = 400;
  progressSlider.height = 5;
  progressSlider.handle_size = 15;
}

//Responsible for drawing the UI
void nowPlayingState::draw(UIContext* context)
{
  progressSlider.max = context->currentTrack.durationInSeconds;
  
  lf_set_ptr_y_absolute(100.0f);
//Gets the thumbnail image
  if (context->currentTrack.thumbnail.id != 0)
  {
    float imageX = (context->screenWidth - context->currentTrack.thumbnail.width) / 2.0f;
    lf_set_ptr_x_absolute(imageX);
    lf_image(context->currentTrack.thumbnail);
  }
  else
  {
    const char* noArtText = "No Album art is found.";
    float textX = (context->screenWidth - lf_text_dimension(noArtText).x) / 2.0f;
    lf_set_ptr_x_absolute(textX);
    lf_text(noArtText);
  }
  lf_next_line();

  lf_set_ptr_y_absolute(lf_get_ptr_y() + 20.0f);

  //Gets the title metadata
  const char* titleText = context->currentTrack.title.c_str();
  float titleX = (context->screenWidth - lf_text_dimension(titleText).x) / 2.0f;
  lf_set_ptr_x_absolute(titleX);
  lf_text(titleText);

  lf_next_line();

  //Gets the artist and album metadata
  std::string subTextStr = context->currentTrack.artist + " - " + context->currentTrack.album;
  const char* subText = subTextStr.c_str();
  float subTextX = (context->screenWidth - lf_text_dimension(subText).x) / 2.0f;
  lf_set_ptr_x_absolute(subTextX);
  lf_text(subText);

  lf_next_line();

  //Set up the slider and slider state
  lf_set_ptr_y_absolute(lf_get_ptr_y() + 20.0f);

  float sliderX = (context->screenWidth - progressSlider.width) / 2.0f;
  lf_set_ptr_x_absolute(sliderX);

  if(!progressSlider.held) { currentProgress = context->engine.getPlaybackPosition(); }

  LfClickableItemState sliderState = lf_slider_int(&progressSlider);
  lf_next_line();

  if (sliderState == LF_CLICKED || sliderState == LF_RELEASED)
  {
    context->engine.setPlaybackPosition(currentProgress);
  }

  int curMin = currentProgress / 60;
  int curSec = currentProgress % 60;
  int toMin = context->currentTrack.durationInSeconds / 60;
  int toSec = context->currentTrack.durationInSeconds % 60;

  //Gets the current time and song duration time
  char timeText[64];

  snprintf(timeText, sizeof(timeText), "%d:%02d / %d:%02d", curMin, curSec, toMin, toSec);

  float timeX = (context->screenWidth - lf_text_dimension(timeText).x) / 2.0f;
  lf_set_ptr_x_absolute(timeX);
  lf_text(timeText);
  lf_next_line();

  //Sets up the play and pause button
  lf_set_ptr_y_absolute(lf_get_ptr_y() + 20.0f);
  const char* buttonText = context->engine.isAudioPlaying() ? "Pause" : "Play";

  float buttonWidth = 100.0f;
  float buttonX = (context->screenWidth - buttonWidth) / 2.0f;
  lf_set_ptr_x_absolute(buttonX);

  //Checks if the button is clicked.
  if (lf_button_fixed(buttonText, buttonWidth, -1) == LF_CLICKED)
  {
    context->engine.togglePlayPause();
  }
  lf_next_line();

}
