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
  progressSlider.max = context->currentTrack.durationInSeconds > 0 ? context->currentTrack.durationInSeconds : 1;

  const char* titleText = context->currentTrack.title.c_str();
  std::string subTextStr = context->currentTrack.artist + " - " + context->currentTrack.album;
  const char* subText = subTextStr.c_str();

  int curMin = currentProgress / 60;
  int curSec = currentProgress % 60;
  int toMin = context->currentTrack.durationInSeconds / 60;
  int toSec = context->currentTrack.durationInSeconds % 60;
  
  char timeText[64];
  snprintf(timeText, sizeof(timeText), "%d:%02d / %d:%02d", curMin, curSec, toMin, toSec);

  LfTexture scaledImage = context->currentTrack.thumbnail;
  if (scaledImage.id != 0)
  {
    float maxImageHeight = context->screenHeight * 0.45f;
    if (scaledImage.height > maxImageHeight && scaledImage.height > 0)
    {
      float ratio = (float)scaledImage.width / (float)scaledImage.height;
      scaledImage.height = maxImageHeight;
      scaledImage.width = maxImageHeight * ratio;
    }
  }

  float totalHeight = 0.0f;
  if (scaledImage.id != 0) { totalHeight += scaledImage.height; }
  else { totalHeight += lf_text_dimension("No Album art is found.").y; }
  
  totalHeight += 20.0f; 
  totalHeight += lf_text_dimension(titleText).y;
  totalHeight += 5.0f; 
  totalHeight += lf_text_dimension(subText).y;
  totalHeight += 20.0f; 
  totalHeight += progressSlider.handle_size;
  totalHeight += 10.0f; 
  totalHeight += lf_text_dimension(timeText).y;
  totalHeight += 20.0f; 
  totalHeight += 30.0f; 

  float startY = (context->screenHeight - totalHeight) / 2.0f;
  if (startY < 10.0f) startY = 10.0f;
  float currentY = startY;

  lf_set_ptr_y_absolute(currentY);

//Gets the thumbnail image
  if (scaledImage.id != 0)
  {
    float imageX = (context->screenWidth - scaledImage.width) / 2.0f;
    lf_set_ptr_x_absolute(imageX);
    lf_image(scaledImage);
    currentY += scaledImage.height;
  }
  else
  {
    const char* noArtText = "No Album art is found.";
    float textX = (context->screenWidth - lf_text_dimension(noArtText).x) / 2.0f;
    lf_set_ptr_x_absolute(textX);
    lf_text(noArtText);
    currentY += lf_text_dimension(noArtText).y;
  }
  lf_next_line();

  currentY += 20.0f;
  lf_set_ptr_y_absolute(currentY);

  //Gets the title metadata
  float titleX = (context->screenWidth - lf_text_dimension(titleText).x) / 2.0f;
  lf_set_ptr_x_absolute(titleX);
  lf_text(titleText);
  currentY += lf_text_dimension(titleText).y;
  lf_next_line();

  currentY += 5.0f;
  lf_set_ptr_y_absolute(currentY);

  //Gets the artist and album metadata
  float subTextX = (context->screenWidth - lf_text_dimension(subText).x) / 2.0f;
  lf_set_ptr_x_absolute(subTextX);
  lf_text(subText);
  currentY += lf_text_dimension(subText).y;
  lf_next_line();

  //Set up the slider and slider state
  currentY += 20.0f;
  lf_set_ptr_y_absolute(currentY);

  float sliderX = (context->screenWidth - progressSlider.width) / 2.0f;
  lf_set_ptr_x_absolute(sliderX);

  if(!progressSlider.held) { currentProgress = context->engine.getPlaybackPosition(); }

  LfClickableItemState sliderState = lf_slider_int(&progressSlider);
  currentY += progressSlider.handle_size;
  lf_next_line();

  if (sliderState == LF_CLICKED || sliderState == LF_RELEASED)
  {
    context->engine.setPlaybackPosition(currentProgress);
  }

  currentY += 10.0f;
  lf_set_ptr_y_absolute(currentY);

  //Gets the current time and song duration time
  float timeX = (context->screenWidth - lf_text_dimension(timeText).x) / 2.0f;
  lf_set_ptr_x_absolute(timeX);
  lf_text(timeText);
  currentY += lf_text_dimension(timeText).y;
  lf_next_line();

  //Sets up the UI buttons
  currentY += 20.0f;
  lf_set_ptr_y_absolute(currentY);
  
  float buttonWidth = 80.0f;
  float spacing = 20.0f;
  float totalWidth = (buttonWidth * 3) + (spacing * 2);
  float startX = (context->screenWidth - totalWidth) / 2.0f;
  
  //Previous button section
  lf_set_ptr_x_absolute(startX);
  if (lf_button_fixed("Prev", buttonWidth, -1) == LF_CLICKED)
  {
    context->requestPrev = true;
  }
  
  //Play/Pause button section
  lf_set_ptr_x_absolute(startX + buttonWidth + spacing);
  const char* buttonText = context->engine.isAudioPlaying() ? "Pause" : "Play";
  if (lf_button_fixed(buttonText, buttonWidth, -1) == LF_CLICKED) 
  {
    context->engine.togglePlayPause();
  }

  lf_set_ptr_x_absolute(startX + (buttonWidth * 2) + (spacing * 2));
  if (lf_button_fixed("Next", buttonWidth, -1) == LF_CLICKED)
  {
    context->requestNext = true;
  }

  lf_next_line();
}
