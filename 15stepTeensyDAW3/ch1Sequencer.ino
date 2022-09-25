void griddrumStepSequencer() {  //static Display rendering
  clearWorkSpace();
  drawStepSequencerStatic(0);
}

void drumStepSequencer() {
  for (byte tone = 0; tone < 12; tone++) {
    for (byte steps = 0; steps < STEP_QUANT; steps++) {
      if (channel1Clip[ch1Clip][tone][steps]) {
        tft.fillCircle((steps * STEP_FRAME_W) + DOT_OFFSET_X, ((tone)*STEP_FRAME_H) + DOT_OFFSET_Y, DOT_RADIUS, trackColor[0]);
      }
    }
  }
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (ts.touched()) {

      //draw MIDIchannel number
      if (gridTouchX >= 18 && gridTouchY == 11) {
        int MIDIChannelAssign = Potentiometer1;
        track[0].MIDIchannel = map(MIDIChannelAssign, 0, 1023, 1, MAX_CHANNELS);
        tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 11 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        tft.setCursor(STEP_FRAME_W * 18 + 8, STEP_FRAME_H * 11 + 3);
        tft.setFont(Arial_10);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.print(track[0].MIDIchannel);
      }
      //draw Plugin
      for (int plugintext = 0; plugintext <= MAX_PLUGINS; plugintext++) {
        if (track[0].MIDIchannel == plugintext + 17) {
          tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 12 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
          tft.setCursor(STEP_FRAME_W * 18 + 2, STEP_FRAME_H * 12 + 2);
          tft.setFont(Arial_8);
          tft.setTextColor(ILI9341_WHITE);
          tft.setTextSize(1);
          tft.print(pluginName[plugintext]);
        }
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
      if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {
        ch1tone = (gridTouchY - 1);
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

      //plugin_1_view
      for (int pluginSelection = 0; pluginSelection <= MAX_PLUGINS; pluginSelection++) {
        if (track[0].MIDIchannel == pluginSelection + 17) {
          if (gridTouchX >= 18 && gridTouchY == 12) {
            for (byte others = 0; others <= MAX_PAGES; others++) {
              selectPage[others] = LOW;
            }
            selectPage[pluginSelection + 20] = HIGH;
            //track[0].MIDIchannel = pluginSelection + 17;
            Plugin_View_Static();
          }
        }
      }
    }
  }
}