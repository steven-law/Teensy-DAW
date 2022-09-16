void griddrumStepSequencer() {  //static Display rendering
  clearWorkSpace();
  drawStepSequencerStatic(0);
}

void drumStepSequencer() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    TS_Point p = ts.getPoint();
    gridTouchX = map(p.x, 180, 3730, 0, 19);  // mapping the touch coordinates to a grid of 20
    gridTouchY = map(p.y, 260, 3760, 0, 14);  //mapping the touch coordinates to a grid of 15

    byte tone_start = ch1Octaves * 12;
    byte tone_end = (ch1Octaves + 1) * 12;
    for (byte tone = tone_start; tone < tone_end; tone++) {
      for (byte steps = 0; steps < STEP_QUANT; steps++) {
        if (channel1Clip[ch1Clip][tone][steps]) {
          tft.fillCircle((steps * STEP_FRAME_W) + DOT_OFFSET_X, ((tone - tone_start) * STEP_FRAME_H) + DOT_OFFSET_Y, DOT_RADIUS, trackColor[0]);
        }
      }
    }
    if (ts.touched()) {
      /*
    //draw the octave number
    tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 4, STEP_FRAME_W * 2, STEP_FRAME_H * 3 + 1, ILI9341_DARKGREY);
    tft.setCursor(STEP_FRAME_W * 18 + 12, STEP_FRAME_H * 5);
    tft.setFont(Arial_16);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(1);
    tft.print(ch1Octaves);

    //octave selection
    
      if (gridTouchX == OCTAVE_CHANGE_LEFTMOST || gridTouchX == OCTAVE_CHANGE_RIGHTMOST - 1) {
        if (gridTouchY >= OCTAVE_CHANGE_UP_TOPMOST && gridTouchY < OCTAVE_CHANGE_UP_BOTTOMMOST) {
          ch1Octaves--;
          clearStepsGrid();
        }
        if (gridTouchY >= OCTAVE_CHANGE_DOWN_TOPMOST && gridTouchY < OCTAVE_CHANGE_DOWN_BOTTOMMOST) {
          ch1Octaves++;
          clearStepsGrid();
        }
      }
      //draw the octave number
      tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 4, STEP_FRAME_W * 2, STEP_FRAME_H * 3, ILI9341_DARKGREY);
      tft.setCursor(STEP_FRAME_W * 18 + 12, STEP_FRAME_H * 4 + 8);
      tft.setFont(Arial_16);
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(1);
      tft.print(ch1Octaves);
*/
      //draw MIDIchannel number
      if (gridTouchX >= 18 && gridTouchY == 11) {
        int MIDIChannelAssign = analogRead(A1);
        track[desired_instrument].MIDIchannel = map(MIDIChannelAssign, 0, 1023, 1, 17);
        tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 11 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        tft.setCursor(STEP_FRAME_W * 18 + 8, STEP_FRAME_H * 11 + 3);
        tft.setFont(Arial_10);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.print(track[desired_instrument].MIDIchannel);
      }


      //assign drumnotes on the left
      if (gridTouchX == 1) {
        int noteselector = Potentiometer1;
        for (int i = 0; i < 12; i++) {
          drumnote[gridTouchY - 1] = map(noteselector, 0, 1023, 0, 48);
          tft.fillRect(STEP_FRAME_W, STEP_FRAME_H * i + STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H, trackColor[0]);
          tft.setCursor(18, STEP_FRAME_H * i + 18);
          tft.setFont(Arial_8);
          tft.setTextColor(ILI9341_BLACK);
          tft.setTextSize(1);
          tft.print(drumnote[i]);
        }
      }
      if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {
        ch1tone = (gridTouchY - 1) + ch1Octaves * 12;
        int step_number = gridTouchX - 2;
        if (channel1Clip[ch1Clip][ch1tone][step_number] == LOW) {
          channel1Clip[ch1Clip][ch1tone][step_number] = HIGH;
          tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, trackColor[0]);  //draw the active steps circles
        } else if (channel1Clip[ch1Clip][ch1tone][step_number] == HIGH) {
          channel1Clip[ch1Clip][ch1tone][step_number] = LOW;
          tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, ILI9341_DARKGREY);  //draw the active steps circles
        }
      }
      if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
        ch1Clip = (gridTouchX / 2) - 1;
        clearStepsGrid();
      }
    }
  }
}