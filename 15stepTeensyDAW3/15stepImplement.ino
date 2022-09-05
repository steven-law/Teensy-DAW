///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                         SEQUENCER CALLBACKS                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


byte thickness = 3;


// called when the step position changes. both the current
// position and last are passed to the callback
void step(int current, int last) {



  //send midinotes for drumtrack #1
  for (int i = 0; i < 127; i++) {
    if (channel1Clip[ch1Clip][i][current] == HIGH) {
      usbMIDI.sendNoteOn(i, VELOCITY, channel1channel);
    }
    if (channel1Clip[ch1Clip][i][current + 1] == LOW) {
      usbMIDI.sendNoteOff(i, VELOCITYOFF, channel1channel);
    }
  }



  //send midinotes for melodic track #2 -8
  for (int track_number = 1; track_number <= 7; track_number++) {
    if (clip[track_number][track[track_number].clip_songMode][current] > VALUE_NOTEOFF) {
      usbMIDI.sendNoteOn(clip[track_number][track[track_number].clip_songMode][current], VELOCITY, track[track_number].MIDIchannel);
    }
    if (clip[track_number][track[track_number].clip_songMode][current] == VALUE_NOTEOFF) {
      usbMIDI.sendNoteOff(clip[track_number][track[track_number].clip_songMode][last], VELOCITYOFF, track[track_number].MIDIchannel);
    }
  }




  for (int songPointerThickness = 0; songPointerThickness <= thickness; songPointerThickness++) {
    for (int stepwidth = 1; stepwidth <= 16; stepwidth++) {
      tft.drawFastHLine(current * stepwidth + STEP_FRAME_W * 2, STEP_POSITION_POINTER_Y + songPointerThickness, STEP_FRAME_W, ILI9341_GREEN);
      tft.drawFastHLine(last * stepwidth + STEP_FRAME_W * 2, STEP_POSITION_POINTER_Y + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);
    }
  }
  for (int songPointerThickness = 0; songPointerThickness <= thickness; songPointerThickness++) {
    if (current == 0) {
      tft.drawFastHLine(STEP_FRAME_W * 17, STEP_POSITION_POINTER_Y + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);

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
      tft.drawPixel(barClock + STEP_FRAME_W * 2, (SONG_POSITION_POINTER_Y + songPointerThickness) , ILI9341_GREEN);
      tft.drawFastHLine(pixelbarClock * phraseSegmentLength + STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y + songPointerThickness, phraseSegmentLength, ILI9341_GREEN);
      tft.drawFastHLine((pixelbarClock - 1) * phraseSegmentLength + STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y + songPointerThickness, phraseSegmentLength, ILI9341_DARKGREY);
    }

    if (barClock % 2 == 0) {
      phrase++;
      //      if (arrangment1[0][phrase] == -1) {
      //        ch1songModePlayedClip = 8;
      //      }
      if (arrangment1[7][phrase] == -1) {
        track[7].clip_songMode = 8;
      }

      track[7].clip_songMode = arrangment1[7][phrase];
      //      ch1songModePlayedClip = arrangment1[0][phrase];
    }
    if (pixelbarClock == 255 / phraseSegmentLength) {
      pixelbarClock = 0;
      tft.fillRect(STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y, STEP_FRAME_W * 20, 4, ILI9341_DARKGREY);
    }
    if (barClock == 255) {
      barClock = 0;
      phrase = 0;
      tft.fillRect(STEP_FRAME_W * 2, SONG_POSITION_POINTER_Y, STEP_FRAME_W * 20, 4, ILI9341_DARKGREY);
    }
  }

}
