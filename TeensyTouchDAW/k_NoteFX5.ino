void NoteFX5_Settings() {
}
void NoteFX5_Control() {
  switch (lastPotRow) {
    case 0:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn] != Potentiometer[MixerColumn]) {
          NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn] = Potentiometer[MixerColumn];
          NFX5[NFX5presetNr].Pot_Value[MixerColumn] = NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn];

          // drawPot(MixerColumnPos, CTRL_ROW_0, NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn], NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 1:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 4] != Potentiometer[MixerColumn]) {
          NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 4] = Potentiometer[MixerColumn];
          NFX5[NFX5presetNr].Pot_Value[MixerColumn + 4] = NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 4];

          //  drawPot(MixerColumnPos, CTRL_ROW_1, NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 4], NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 4], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 2:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 8] != Potentiometer[MixerColumn]) {
          NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 8] = Potentiometer[MixerColumn];
          NFX5[NFX5presetNr].Pot_Value[MixerColumn + 8] = NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 8];

          //  drawPot(MixerColumnPos, CTRL_ROW_2, NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 8], NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 8], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 3:
      break;
  }
}
void NoteFX5_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    /*
    if (enc_moved[1]) {

      int noteselector = constrain((drumnote[gridTouchY - 1] + encoded[0]), 0, 99);
      for (int i = 0; i < 12; i++) {
        drumnote[gridTouchY - 1] = noteselector;
        tft.fillRect(STEP_FRAME_W, STEP_FRAME_H * i + STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H, trackColor[0]);
        tft.setCursor(18, STEP_FRAME_H * i + 18);
        tft.setFont(Arial_8);
        tft.setTextColor(ILI9341_BLACK);
        tft.setTextSize(1);
        tft.print(drumnote[i]);
      }
    }*/
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
        saveNoteFX5();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadNoteFX5();
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
  drawActiveRatchetSteps();
  drawNrInRect(18, 1, NFX5presetNr, trackColor[desired_instrument]);
  drawChar(18, 3, seqModes[track[desired_track].seqMode], trackColor[desired_track]);


  midi01.sendControlChange(0, 0, 1);
  LP_drawStepsequencer();
  LP_drawOctave(3);
}

void NoteFX5_Change() {
  for (int touchX = 1; touchX < 5; touchX++) {

    NFX5[NFX5presetNr].Pot_Value_graph[touchX - 1];
  }
  for (int touchX = 1; touchX < 5; touchX++) {

    NFX5[NFX5presetNr].Pot_Value_graph[touchX + 3];
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    NFX5[NFX5presetNr].Pot_Value_graph[touchX + 7];
  }
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

void saveNoteFX5() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing NoteFX5.txt...");
  SD.remove("NoteFX5.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening NoteFX5.txt...");
  myFile = SD.open("NoteFX5.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    tft.print("Writing NoteFX5 to NoteFX5.txt...");
    //save plugin 3 variables
    for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      for (int touchX = 1; touchX < 5; touchX++) {
        myFile.print((char)NFX5[maxpreset].Pot_Value_graph[touchX - 1]);
        myFile.print((char)NFX5[maxpreset].Pot_Value_graph[touchX + 3]);
        myFile.print((char)NFX5[maxpreset].Pot_Value_graph[touchX + 7]);
      }
    }

    tft.println("Done");

    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening NoteFX5.txt");
  }
}

void loadNoteFX5() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("NoteFX5.txt");
  if (myFile) {
    tft.println("opening NoteFX5.txt:");

    // read from the file until there's nothing else in it:

    //load NoteFX5 variables
    tft.print("reading NoteFX5 from NoteFX5.txt...");
    for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      for (int touchX = 1; touchX < 5; touchX++) {
        NFX5[maxpreset].Pot_Value_graph[touchX - 1] = myFile.read();
        NFX5[maxpreset].Pot_Value_graph[touchX + 3] = myFile.read();
        NFX5[maxpreset].Pot_Value_graph[touchX + 7] = myFile.read();
      }
    }

    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening NoteFX5.txt");
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    NFX5[NFX5presetNr].Pot_Value[touchX - 1] = NFX5[NFX5presetNr].Pot_Value_graph[touchX - 1];

    NFX5[NFX5presetNr].Pot_Value[touchX + 3] = NFX5[NFX5presetNr].Pot_Value_graph[touchX + 3];

    NFX5[NFX5presetNr].Pot_Value[touchX + 7] = NFX5[NFX5presetNr].Pot_Value_graph[touchX + 7];
  }
}