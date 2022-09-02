
void gridchannelSequencer (byte desired_instrument) {   //static Display rendering
  clearWorkSpace();
  drawMelodicSequencerStatic(desired_instrument);

}

void channel8Sequencer (byte desired_instrument) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    TS_Point p = ts.getPoint();
    gridTouchX = map(p.x, 180, 3730, 0, 19);  // mapping the touch coordinates to a grid of 20
    gridTouchY = map(p.y, 260, 3760, 0, 14);  //mapping the touch coordinates to a grid of 15

    byte tone_start = ch8Octaves * 12;
    byte tone_end = (ch8Octaves + 1) * 12;
    //    for (byte ch8tone = tone_start ; ch8tone < tone_end) {
    for (byte steps = 0 ; steps < STEP_QUANT ; steps++) {
      if (clip[desired_instrument][ch8Clip][steps] > VALUE_NOTEOFF) {
        tft.fillCircle((steps * STEP_FRAME_W) + DOT_OFFSET_X, ((clip[desired_instrument][ch8Clip][steps] - tone_start) * STEP_FRAME_H) + DOT_OFFSET_Y, DOT_RADIUS, trackColor[desired_instrument]);
      }
    }
    //    }
    //draw the octave number
    tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 4, STEP_FRAME_W * 2, STEP_FRAME_H * 4, ILI9341_DARKGREY);
    tft.setCursor(STEP_FRAME_W * 18 + 12, STEP_FRAME_H * 5 + 8);
    tft.setFont(Arial_16);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(1);
    tft.print(ch8Octaves);


    //octave selection
    if (ts.touched()) {
      if (gridTouchX > OCTAVE_CHANGE_LEFTMOST && gridTouchX < OCTAVE_CHANGE_RIGHTMOST  && gridTouchY > OCTAVE_CHANGE_UP_TOPMOST && gridTouchY < OCTAVE_CHANGE_UP_BOTTOMMOST) {
        ch8Octaves--;
        clearStepsGrid();
      }
      if (gridTouchX > OCTAVE_CHANGE_LEFTMOST && gridTouchX < OCTAVE_CHANGE_RIGHTMOST  && gridTouchY > OCTAVE_CHANGE_DOWN_TOPMOST && gridTouchY < OCTAVE_CHANGE_DOWN_BOTTOMMOST) {
        ch8Octaves++;
        clearStepsGrid();
      }


      if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {
        ch8tone = (gridTouchY - 1) + ch8Octaves * 12;
        int step_number = gridTouchX - 2;
        if (clip[desired_instrument][ch8Clip][step_number] == VALUE_NOTEOFF) {
          clip[desired_instrument][ch8Clip][step_number] = ch8tone;
          //          clipOctaves[7][ch8Clip][step_number] = ch8Octaves;
          tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, trackColor[desired_instrument]); //draw the active steps circles
        }
        else if (clip[desired_instrument][ch8Clip][step_number] > VALUE_NOTEOFF) {
          clip[desired_instrument][ch8Clip][step_number] = VALUE_NOTEOFF;
          tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, ILI9341_DARKGREY); //draw the active steps circles
        }
      }
      if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
        ch8Clip = (gridTouchX / 2) - 1;
        clearStepsGrid();
      }
    }

  }
}
