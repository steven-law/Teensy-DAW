void NoteFX5_Settings() {
}
void NoteFX5_Control() {
}
void NoteFX5_Page1_Dynamic() {
  //change preset
  if (button[14]) {

    if (enc_moved[0]) {
      int noteselector = constrain((NFX5[NFX5presetNr].Pot_Value[gridTouchY - 1] + encoded[0]), 1, track[0].MIDItick_reset - 1);
      NFX5[NFX5presetNr].Pot_Value[gridTouchY - 1] = noteselector;
      draw_Ratchrate();
    }

    if (enc_moved[1]) {
      int noteselector = constrain((NFX5[NFX5presetNr].repeats[gridTouchY - 1] + encoded[1]), 1, track[0].MIDItick_reset - 1);
      NFX5[NFX5presetNr].repeats[gridTouchY - 1] = noteselector;
      draw_Ratchrate();
    }

    if (enc_moved[3]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      NFX5presetNr = constrain((NFX5presetNr + encoded[3]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, NFX5presetNr, trackColor[desired_instrument]);
      NoteFX5_Page_Static();
    }
  }
  if (!button[14]) {
    //gridTouchX
    if (enc_moved[0]) {
      gridTouchX = constrain((gridTouchX + encoded[0]), 0, 19);
      drawCursor();
      showCoordinates();
    }
    //gridTouchY
    if (enc_moved[1]) {
      gridTouchY = constrain((gridTouchY + encoded[1]), 0, 14);
      drawCursor();
      showCoordinates();
    }
  }

  TS_Point p = ts.getPoint();


  if (ts.touched() || button[15]) {


    unsigned long currentMillis = millis();  //worse input haptic, better bpm drop when longpress (-2bpm)
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;


      if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {

        int dot_on_X = (gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X;
        int dot_on_Y = (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y;

        ch1tone = (gridTouchY - 1);
        int step_number = gridTouchX - 2;

        if (!ratchet[NFX5presetNr][ch1tone][step_number]) {
          ratchet[NFX5presetNr][ch1tone][step_number] = true;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, (trackColor[0] + (NFX5presetNr)*20));  //draw the active steps circles
        } else if (ratchet[NFX5presetNr][ch1tone][step_number]) {
          ratchet[NFX5presetNr][ch1tone][step_number] = false;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, ILI9341_DARKGREY);  //draw the inactive steps circles
        }
      }
    }

    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        saveNoteFX("NoteFX5", 4);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadNoteFX("NoteFX5", 4);
      }
    }

    if (gridTouchY >= 2 && gridTouchY <= 4) {
      lastPotRow = 0;
    }

    if (gridTouchY >= 5 && gridTouchY <= 7) {
      lastPotRow = 1;
    }

    if (gridTouchY >= 8 && gridTouchY <= 10) {
      lastPotRow = 2;
    }
    if (gridTouchY >= 11 && gridTouchY <= 13) {
      lastPotRow = 3;
    }
  }
}
void NoteFX5_Page_Static() {
  clearWorkSpace();
  NoteFX5_Change();
  drawStepSequencerStatic(0);
  draw_Ratchrate();
  drawActiveRatchetSteps();
  drawNrInRect(18, 1, NFX5presetNr, trackColor[desired_instrument]);
  drawChar(18, 3, seqModes[track[desired_track].seqMode], trackColor[desired_track]);


  midi01.sendControlChange(0, 0, 1);
  LP_drawStepsequencer();
  LP_drawOctave(3);
}

void NoteFX5_Change() {
}

void drawActiveRatchetSteps() {
  for (int tone = 0; tone < 12; tone++) {
    for (int steps = 0; steps < STEP_QUANT; steps++) {
      if (ratchet[NFX5presetNr][tone][steps]) {
        tft.fillCircle((steps * STEP_FRAME_W) + DOT_OFFSET_X, ((tone)*STEP_FRAME_H) + DOT_OFFSET_Y, DOT_RADIUS, trackColor[0] + ((track[0].clip_selector) * 20));
      }
    }
  }
}
void draw_Ratchrate() {
  for (int n = 0; n < 12; n++) {  //hor notes
    tft.fillRect(STEP_FRAME_W, STEP_FRAME_H * n + STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H, trackColor[desired_instrument]);
    tft.setCursor(18, STEP_FRAME_H * n + 18);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(1);
    tft.print(NFX5[NFX5presetNr].Pot_Value[n]);
    tft.setCursor(26, STEP_FRAME_H * n + 23);
    tft.print(NFX5[NFX5presetNr].repeats[n]);
  }
}
