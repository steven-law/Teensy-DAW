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

          drawPot(MixerColumnPos, CTRL_ROW_0, NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn], NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 1:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 4] != Potentiometer[MixerColumn]) {
          NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 4] = Potentiometer[MixerColumn];
          NFX5[NFX5presetNr].Pot_Value[MixerColumn + 4] = NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 4];

          drawPot(MixerColumnPos, CTRL_ROW_1, NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 4], NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 4], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 2:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 8] != Potentiometer[MixerColumn]) {
          NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 8] = Potentiometer[MixerColumn];
          NFX5[NFX5presetNr].Pot_Value[MixerColumn + 8] = NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 8];

          drawPot(MixerColumnPos, CTRL_ROW_2, NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 8], NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 8], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
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
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      NFX5presetNr = constrain((NFX5presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, NFX5presetNr, trackColor[desired_instrument]);
      NoteFX5_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn] + encoded[MixerColumn]), 0, 128);
          }
        }
        break;

      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 4];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 4] + encoded[MixerColumn]), 0, 128);
          }
        }
        break;

      case 2:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 8];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX5[NFX5presetNr].Pot_Value_graph[MixerColumn + 8] + encoded[MixerColumn]), 0, 128);
          }
        }
        break;

      case 3:
        break;
    }
  }
  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {
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
  drawNrInRect(18, 1, NFX5presetNr, ILI9341_PURPLE);
  drawChar(18, 3, seqModes[track[desired_track].seqMode], trackColor[desired_track]);
  for (int touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, CTRL_ROW_0, NFX5[NFX5presetNr].Pot_Value_graph[touchX - 1], NFX5[NFX5presetNr].Pot_Value_graph[touchX - 1], NFX3_ROW2[touchX - 1], trackColor[desired_instrument]);
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, CTRL_ROW_1, NFX5[NFX5presetNr].Pot_Value_graph[touchX + 3], NFX5[NFX5presetNr].Pot_Value_graph[touchX + 3], NFX3_ROW2[touchX - 1], trackColor[desired_instrument]);
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, CTRL_ROW_2, NFX5[NFX5presetNr].Pot_Value_graph[touchX + 7], NFX5[NFX5presetNr].Pot_Value_graph[touchX + 7], NFX3_ROW2[touchX - 1], trackColor[desired_instrument]);
  }
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