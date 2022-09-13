///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                         SEQUENCER CALLBACKS                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


byte thickness = 3;


// called when the step position changes. both the current
// position and last are passed to the callback
void step(int current, int last) {
  for (int i = 0; i < 127; i++) {
    if (channel1Clip[ch1Clip][i][current] == HIGH) {
      usbMIDI.sendNoteOn(i, velocity, channel1channel);
    }
    if (channel1Clip[ch1Clip][i][current + 1] == LOW) {
      usbMIDI.sendNoteOff(i, velocityOff, channel1channel);
    }
  }



  if (clip[1][ch2Clip][current] > 0) {
    usbMIDI.sendNoteOn(clip[1][ch2Clip][current], velocity, channel2channel);
  }
  else if (clip[1][ch3Clip][current + 1] <= 0) {
    usbMIDI.sendNoteOff(clip[1][ch2Clip][current], velocityOff, channel2channel);
  }



  if (clip[2][ch3Clip][current] > 0) {
    usbMIDI.sendNoteOn(clip[2][ch3Clip][current], velocity, channel3channel);
  }
  else if (clip[2][ch3Clip][current + 1] <= 0) {
    usbMIDI.sendNoteOff(clip[2][ch3Clip][current], velocityOff, channel3channel);
  }



  if (clip[3][ch4Clip][current] > 0) {
    usbMIDI.sendNoteOn(clip[3][ch4Clip][current], velocity, channel4channel);
  }
  else if (clip[3][ch4Clip][current + 1] <= 0) {
    usbMIDI.sendNoteOff(clip[3][ch4Clip][current], velocityOff, channel4channel);
  }



  if (clip[4][ch5Clip][current] > 0) {
    usbMIDI.sendNoteOn(clip[4][ch5Clip][current], velocity, channel5channel);
  }
  else if (clip[4][ch5Clip][current + 1] <= 0) {
    usbMIDI.sendNoteOff(clip[4][ch5Clip][current], velocityOff, channel5channel);
  }




  if (clip[5][ch6Clip][current] > 0) {
    usbMIDI.sendNoteOn(clip[5][ch6Clip][current], velocity, channel6channel);
  }
  else if (clip[5][ch6Clip][current + 1] <= 0) {
    usbMIDI.sendNoteOff(clip[5][ch6Clip][current], velocityOff, channel6channel);
  }




  if (clip[6][ch7Clip][current] > VALUE_NOTEOFF) {
    usbMIDI.sendNoteOn(clip[6][ch7Clip][current], velocity, channel7channel);
  }
  else if (clip[6][ch7Clip][current + 1] == VALUE_NOTEOFF) {

    usbMIDI.sendNoteOff(clip[6][ch7Clip][current], velocityOff, channel7channel);
  }

  if (clip[7][ch8songModePlayedClip][current] > VALUE_NOTEOFF) {
    usbMIDI.sendNoteOn(clip[7][ch8songModePlayedClip][current], velocity, channel8channel);
  }
  if (clip[7][ch8songModePlayedClip][current] == VALUE_NOTEOFF) {
    usbMIDI.sendNoteOff(clip[7][ch8songModePlayedClip][last], velocityOff, channel8channel);
  }


  for (int songPointerThickness = 0; songPointerThickness <= thickness; songPointerThickness++) {
    for (int stepwidth = 1; stepwidth <= 16; stepwidth++) {
      tft.drawFastHLine(current * stepwidth + STEP_FRAME_W * 2, stepPositionY + songPointerThickness, STEP_FRAME_W, ILI9341_GREEN);
      tft.drawFastHLine((current - 1) * stepwidth + STEP_FRAME_W * 2, stepPositionY + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);
    }
  }
  for (int songPointerThickness = 0; songPointerThickness <= thickness; songPointerThickness++) {
    if (current == 0) {
      tft.drawFastHLine(STEP_FRAME_W * 17, stepPositionY + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);

    }
  }
  if (current == 0) {
    barClock++;
    pixelbarClock++;
    tft.fillRect(STEP_FRAME_W * POSITION_BAR_BUTTON - 1, 2, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 3, ILI9341_DARKGREY);
    tft.setTextColor(ILI9341_WHITE);
    tft.setFont(Arial_9);
    tft.setCursor(STEP_FRAME_W * POSITION_BAR_BUTTON + 2, 3);
    tft.print(barClock + 1);
    for (int songPointerThickness = 0; songPointerThickness <= thickness; songPointerThickness++) {
      tft.drawPixel(barClock + STEP_FRAME_W * 2, (songPositionY + songPointerThickness) , ILI9341_GREEN);
      tft.drawFastHLine(pixelbarClock * PHRASE_SEGMENT_LENGTH + STEP_FRAME_W * 2, gridPositionY + songPointerThickness, PHRASE_SEGMENT_LENGTH, ILI9341_GREEN);
      tft.drawFastHLine((pixelbarClock - 1) * PHRASE_SEGMENT_LENGTH + STEP_FRAME_W * 2, gridPositionY + songPointerThickness, PHRASE_SEGMENT_LENGTH, ILI9341_DARKGREY);
    }

    if (barClock % 2 == 0) {
      phrase++;
//      if (arrangment1[0][phrase] == -1) {
//        ch1songModePlayedClip = 8;
//      }
      if (arrangment1[7][phrase] == -1) {
        ch8songModePlayedClip = 8;
      }

      ch8songModePlayedClip = arrangment1[7][phrase];
//      ch1songModePlayedClip = arrangment1[0][phrase];
    }
    if (pixelbarClock == 255 / PHRASE_SEGMENT_LENGTH) {
      pixelbarClock = 0;
      tft.fillRect(STEP_FRAME_W * 2, gridPositionY, STEP_FRAME_W * 20, 4, ILI9341_DARKGREY);
    }
    if (barClock == 255) {
      barClock = 0;
      phrase = 0;
      tft.fillRect(STEP_FRAME_W * 2, songPositionY, STEP_FRAME_W * 20, 4, ILI9341_DARKGREY);
    }
  }

}
