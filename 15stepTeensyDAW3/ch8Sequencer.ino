void gridStepSequencer(byte desired_instrument) {  //static Display rendering
  desired_track = desired_instrument;
  byte tone_start = track[desired_instrument].shown_octaves * 12;
  clearWorkSpace();
  drawStepSequencerStatic(desired_instrument);
  drawActiveSteps();
  drawMIDIchannel();
}

void melodicStepSequencer(byte desired_instrument) {
  //drawActiveSteps();
  desired_track = desired_instrument;
  int touched_step = gridTouchX - 2;
  byte touched_note = gridTouchY - 1;
  byte tone_start = track[desired_instrument].shown_octaves * 12;
  byte tone_end = (track[desired_instrument].shown_octaves + 1) * 12;
  for (int i = 0; i < 7; i++) {
    if (buttons[i].changed()) {
      drawActiveSteps();
    }
  }
  if (ts.touched() || !buttons[6].read()) {
    drawActiveSteps();
    //octave selection
    if (gridTouchX == OCTAVE_CHANGE_LEFTMOST || gridTouchX == OCTAVE_CHANGE_RIGHTMOST - 1) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        if (gridTouchY >= OCTAVE_CHANGE_UP_TOPMOST && gridTouchY < OCTAVE_CHANGE_UP_BOTTOMMOST) {
          track[desired_instrument].shown_octaves--;
          clearStepsGrid();
        }
        if (gridTouchY >= OCTAVE_CHANGE_DOWN_TOPMOST && gridTouchY < OCTAVE_CHANGE_DOWN_BOTTOMMOST) {
          track[desired_instrument].shown_octaves++;
          clearStepsGrid();
        }
        //draw the octave number
        tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 4, STEP_FRAME_W * 2, STEP_FRAME_H * 3 + 1, ILI9341_DARKGREY);
        tft.setCursor(STEP_FRAME_W * 18 + 12, STEP_FRAME_H * 5);
        tft.setFont(Arial_16);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.print(track[desired_instrument].shown_octaves);
      }
    }

    //midichannel selection
    if (gridTouchX >= 18 && gridTouchY == 11) {
      int MIDIChannelAssign = Potentiometer1;
      track[desired_instrument].MIDIchannel = map(MIDIChannelAssign, 0, 1023, 1, MAX_CHANNELS);
      //draw MIDIchannel number
      drawMIDIchannel();
    }

    //manually assigning steps to the grid;
    //for better behaviour here we wait for "interval, unless it would switch within micrseconds
    if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        track[desired_instrument].tone = touched_note + track[desired_instrument].shown_octaves * 12;
        int dot_on_X = touched_step * STEP_FRAME_W + DOT_OFFSET_X;
        int dot_on_Y = touched_note * STEP_FRAME_H + DOT_OFFSET_Y;
        int notevalue_on_step = ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[touched_step];

        if (notevalue_on_step == VALUE_NOTEOFF) {
          ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[touched_step] = track[desired_instrument].tone;
          clearStepsGridY();
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, trackColor[desired_instrument] + track[desired_instrument].clip_selector * 20);  //draw the active steps circles

        } else if (notevalue_on_step > VALUE_NOTEOFF) {
          ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[touched_step] = VALUE_NOTEOFF;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, ILI9341_DARKGREY);  //draw the in-active steps circles
        }
      }
    }

    //clipselecting
    if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
      track[desired_instrument].clip_selector = (gridTouchX / 2) - 1;
      clearStepsGrid();
      drawActiveSteps();
    }
    //midicc_view
    for (int midiccSelection = 0; midiccSelection <= 16; midiccSelection++) {
      if (track[0].MIDIchannel == midiccSelection) {
        if (gridTouchX >= 18 && gridTouchY == 12) {
          select_page(MIDICC_PAGE_1);
          midiCC_view_Static(0, desired_track);
        }
      }
    }

    //plugin_1_view
    for (int pluginSelection = 0; pluginSelection <= MAX_PLUGINS; pluginSelection++) {
      if (track[desired_instrument].MIDIchannel == pluginSelection + 17) {
        if (gridTouchX >= 18 && gridTouchY == 12) {
          select_page(pluginSelection + 40);
          Plugin_View_Static(desired_track);
        }
      }
    }
  }
}