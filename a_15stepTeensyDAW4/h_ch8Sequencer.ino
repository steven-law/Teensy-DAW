void gridStepSequencer(byte desired_instrument) {  //static Display rendering

  clearWorkSpace();
  drawStepSequencerStatic(desired_instrument);
  drawActiveSteps();
  drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
  drawMIDIchannel();
  //draw Octavebuttons
  int leftmost = STEP_FRAME_W * OCTAVE_CHANGE_LEFTMOST;
  int rightmost = STEP_FRAME_W * OCTAVE_CHANGE_RIGHTMOST;
  int UP_topmost = STEP_FRAME_H * OCTAVE_CHANGE_UP_TOPMOST;
  int UP_bottommost = STEP_FRAME_H * OCTAVE_CHANGE_UP_BOTTOMMOST;
  int DOWN_topmost = STEP_FRAME_H * OCTAVE_CHANGE_DOWN_TOPMOST;
  int DOWN_bottommost = STEP_FRAME_H * OCTAVE_CHANGE_DOWN_BOTTOMMOST;
  tft.fillRect(leftmost + 1, STEP_FRAME_H * 2, STEP_FRAME_W * 2, STEP_FRAME_H * 3, ILI9341_DARKGREY);
  tft.fillTriangle(leftmost + 1, UP_bottommost, rightmost, UP_bottommost, leftmost + STEP_FRAME_W, UP_topmost, ILI9341_LIGHTGREY);         //octave arrow up
  tft.fillTriangle(leftmost + 1, DOWN_topmost, rightmost - 2, DOWN_topmost, leftmost + STEP_FRAME_W, DOWN_bottommost, ILI9341_LIGHTGREY);  //x1, y1, x2, y2, x3, y3

  //draw the octave number
  tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * OCTAVE_CHANGE_TEXT, STEP_FRAME_W * 2, STEP_FRAME_H * 1 + 1, ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * 18 + 11, STEP_FRAME_H * OCTAVE_CHANGE_TEXT);
  tft.setFont(Arial_16);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print(track[desired_instrument].shown_octaves);
}

void melodicStepSequencer(byte desired_instrument) {

  if (msecs % 50 == 0) {
    //midichannel
    if (abs(map(Potentiometer[2], 0, 127, 1, MAX_CHANNELS) - track[desired_instrument].MIDIchannel) < 2) {
      if (track[desired_instrument].MIDIchannel != map(Potentiometer[2], 0, 127, 1, MAX_CHANNELS)) {
        track[desired_instrument].MIDIchannel = map(Potentiometer[2], 0, 127, 1, MAX_CHANNELS);
        drawMIDIchannel();
      }
    }
    //clip
    if (abs(map(Potentiometer[3], 0, 127, 0, 7) - track[desired_instrument].clip_selector) < 2) {
      if (track[desired_instrument].clip_selector != map(Potentiometer[3], 0, 127, 0, 7)) {
        track[desired_instrument].clip_selector = map(Potentiometer[3], 0, 127, 0, 7);
        clearStepsGrid();
        drawActiveSteps();
        //Cliprect
        drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
      }
    }
    //octaves
    if (!button_15) {
      if (abs(map(Potentiometer[1], 0, 127, 0, 9) - track[desired_instrument].shown_octaves) < 2) {
        if (track[desired_instrument].shown_octaves != map(Potentiometer[1], 0, 127, 0, 9)) {
          track[desired_instrument].shown_octaves = map(Potentiometer[1], 0, 127, 0, 9);
          clearStepsGrid();
          drawActiveSteps();
          //draw the octave number
          tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * OCTAVE_CHANGE_TEXT, STEP_FRAME_W * 2, STEP_FRAME_H * 1 + 1, ILI9341_DARKGREY);
          tft.setCursor(STEP_FRAME_W * 18 + 11, STEP_FRAME_H * OCTAVE_CHANGE_TEXT);
          tft.setFont(Arial_16);
          tft.setTextColor(ILI9341_WHITE);
          tft.setTextSize(1);
          tft.print(track[desired_instrument].shown_octaves);
        }
      }
    }
  }



  int touched_step = gridTouchX - 2;
  byte touched_note = gridTouchY - 1;



  TS_Point p = ts.getPoint();
  if (ts.touched() || enter_button) {

    //manually assigning steps to the grid;
    //for better behaviour here we wait for "interval, unless it would switch within micrseconds
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;


      if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {
        track[desired_instrument].tone = touched_note + track[desired_instrument].shown_octaves * 12;
        int dot_on_X = touched_step * STEP_FRAME_W + DOT_OFFSET_X;
        int dot_on_Y = touched_note * STEP_FRAME_H + DOT_OFFSET_Y;
        int notevalue_on_step = ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[touched_step];

        if (notevalue_on_step == VALUE_NOTEOFF) {
          ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[touched_step] = track[desired_instrument].tone;
          clearStepsGridY();
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));  //draw the active steps circles

        } else if (notevalue_on_step > VALUE_NOTEOFF) {
          ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[touched_step] = VALUE_NOTEOFF;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, ILI9341_DARKGREY);  //draw the in-active steps circles
        }
      }


      //octave selection
      if (gridTouchX >= OCTAVE_CHANGE_LEFTMOST) {
        if (gridTouchY >= OCTAVE_CHANGE_UP_TOPMOST && gridTouchY < OCTAVE_CHANGE_UP_BOTTOMMOST) {
          track[desired_instrument].shown_octaves--;
          clearStepsGrid();
        }
        if (gridTouchY >= OCTAVE_CHANGE_DOWN_TOPMOST && gridTouchY < OCTAVE_CHANGE_DOWN_BOTTOMMOST) {
          track[desired_instrument].shown_octaves++;
          clearStepsGrid();
        }
        //draw the octave number
        tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * OCTAVE_CHANGE_TEXT, STEP_FRAME_W * 2, STEP_FRAME_H * 1 + 1, ILI9341_DARKGREY);
        tft.setCursor(STEP_FRAME_W * 18 + 11, STEP_FRAME_H * OCTAVE_CHANGE_TEXT);
        tft.setFont(Arial_16);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.print(track[desired_instrument].shown_octaves);
      }
    }


    //clipselecting
    if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
      track[desired_instrument].clip_selector = (gridTouchX / 2) - 1;
      clearStepsGrid();
      drawActiveSteps();
      drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
    }
  }
}

void drawActiveSteps() {
  byte tone_start = track[desired_instrument].shown_octaves * 12;
  //draw active steps
  for (byte steps = 0; steps < STEP_QUANT; steps++) {
    int dot_on_X = (steps * STEP_FRAME_W) + DOT_OFFSET_X;
    int dot_on_Y = ((ctrack[desired_track].sequence[track[desired_track].clip_selector].step[steps] - tone_start) * STEP_FRAME_H) + DOT_OFFSET_Y;
    if (ctrack[desired_track].sequence[track[desired_track].clip_selector].step[steps] > VALUE_NOTEOFF) {
      tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, trackColor[desired_track] + (track[desired_track].clip_selector * 20));
    }
    if (ctrack[desired_track].sequence[track[desired_track].clip_selector].step[steps] == VALUE_NOTEOFF) {
      tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, ILI9341_DARKGREY);
    }
  }
}