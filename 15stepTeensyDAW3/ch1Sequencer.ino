void griddrumStepSequencer() {  //static Display rendering
  clearWorkSpace();
  drawStepSequencerStatic(0);
  drawActiveDrumSteps();

  //draw active steps
}


void drumStepSequencer() {
  /*unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    //show stuff


    }*/
  //drawActiveDrumSteps();
  for (int i = 0; i < 7; i++) {
    if (buttons[i].changed()) {
      drawActiveSteps();
    }
  }

  if (ts.touched() || !buttons[6].read()) {

    //draw active steps
    drawActiveDrumSteps();
    //midichannel selection
    //draw MIDIchannel number
    if (gridTouchX >= 18 && gridTouchY == 11) {
      int MIDIChannelAssign = Potentiometer1;
      track[0].MIDIchannel = map(MIDIChannelAssign, 0, 1023, 1, MAX_CHANNELS);
      drawMIDIchannel();
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
    //assign drumsteps on the grid
    //for better behaviour here we wait for "interval, unless it would switch within micrseconds
    if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        ch1tone = (gridTouchY - 1);
        int step_number = gridTouchX - 2;

        if (!channel1Clip[ch1Clip][ch1tone][step_number]) {
          channel1Clip[ch1Clip][ch1tone][step_number] = true;
          tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, trackColor[0] + track[0].clip_selector * 20);  //draw the active steps circles
        } else if (channel1Clip[ch1Clip][ch1tone][step_number]) {
          channel1Clip[ch1Clip][ch1tone][step_number] = false;
          tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, ILI9341_DARKGREY);  //draw the active steps circles
        }
      }
    }

    //clipselecting
    if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
      ch1Clip = (gridTouchX / 2);
      clearStepsGrid();
      //draw active steps
      drawActiveDrumSteps();
    }


    //midicc_view
    for (int midiccSelection = 0; midiccSelection <= 16; midiccSelection++) {
      if (track[0].MIDIchannel == midiccSelection) {
        if (gridTouchX >= 18 && gridTouchY == 12) {
          select_page(MIDICC_PAGE_1);
          midiCC_view_Static(0, 0);
        }
      }
    }


    //plugin_1_view
    for (int pluginSelection = 0; pluginSelection <= MAX_PLUGINS; pluginSelection++) {
      if (track[0].MIDIchannel == pluginSelection + 17) {
        if (gridTouchX >= 18 && gridTouchY == 12) {
          select_page(pluginSelection + 40);
          Plugin_View_Static(0);
        }
      }
    }
  }
}