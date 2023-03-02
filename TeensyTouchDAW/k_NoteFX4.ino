void NoteFX4_Settings() {
}
void NoteFX4_Control() {
}
void NoteFX4_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      NFX4presetNr = constrain((NFX4presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, NFX4presetNr, trackColor[desired_instrument]);
      NoteFX4_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = NFX4[NFX4presetNr].Pot_Value[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn] + encoded[MixerColumn]), 0, NUM_STEPS);
            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn] + encoded[MixerColumn]), 0, NUM_STEPS - 1);
          }
        }
        break;

      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = NFX4[NFX4presetNr].Pot_Value[MixerColumn + 4];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn + 4] + encoded[MixerColumn]), 0, NUM_STEPS);
            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn + 4] + encoded[MixerColumn]), 0, NUM_STEPS - 1);
          }
        }
        break;

      case 2:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = NFX4[NFX4presetNr].Pot_Value[MixerColumn + 8];
          if (enc_moved[MixerColumn]) {

            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn + 8] + encoded[MixerColumn]), 0, NUM_STEPS);

            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn + 8] + encoded[MixerColumn]), 0, NUM_STEPS - 1);
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
        saveNoteFX4();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadNoteFX4();
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
void NoteFX4_Page_Static() {
  clearWorkSpace();
  NoteFX4_Change();
  drawNrInRect(18, 1, NFX4presetNr, ILI9341_PURPLE);
  drawChar(18, 3, seqModes[track[desired_track].seqMode], trackColor[desired_track]);
  for (int touchX = 1; touchX < 5; touchX++) {

    drawPotDrum(touchX * 4 - 1, CTRL_ROW_0, NFX4[NFX4presetNr].Pot_Value[touchX - 1], NFX4[NFX4presetNr].Pot_Value[touchX - 1], drumnote[touchX - 1], trackColor[desired_instrument]);
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    drawPotDrum(touchX * 4 - 1, CTRL_ROW_1, NFX4[NFX4presetNr].Pot_Value[touchX + 3], NFX4[NFX4presetNr].Pot_Value[touchX + 3], drumnote[touchX + 3], trackColor[desired_instrument]);
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    drawPotDrum(touchX * 4 - 1, CTRL_ROW_2, NFX4[NFX4presetNr].Pot_Value[touchX + 7], NFX4[NFX4presetNr].Pot_Value[touchX + 7], drumnote[touchX + 7], trackColor[desired_instrument]);
  }
}

void NoteFX4_Change() {
  for (int touchX = 1; touchX < 5; touchX++) {

    NFX4[NFX4presetNr].Pot_Value[touchX - 1];
  }
  for (int touchX = 1; touchX < 5; touchX++) {

    NFX4[NFX4presetNr].Pot_Value[touchX + 3];
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    NFX4[NFX4presetNr].Pot_Value[touchX + 7];
  }
}


void saveNoteFX4() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing NoteFX4.txt...");
  SD.remove("NoteFX4.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening NoteFX4.txt...");
  myFile = SD.open("NoteFX4.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    tft.print("Writing NoteFX4 to NoteFX4.txt...");
    //save plugin 3 variables
    for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      for (int touchX = 1; touchX < 5; touchX++) {
        myFile.print((char)NFX4[maxpreset].Pot_Value[touchX - 1]);
        myFile.print((char)NFX4[maxpreset].Pot_Value[touchX + 3]);
        myFile.print((char)NFX4[maxpreset].Pot_Value[touchX + 7]);
      }
    }

    tft.println("Done");

    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening NoteFX4.txt");
  }
}

void loadNoteFX4() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("NoteFX4.txt");
  if (myFile) {
    tft.println("opening NoteFX4.txt:");

    // read from the file until there's nothing else in it:

    //load NoteFX4 variables
    tft.print("reading NoteFX4 from NoteFX4.txt...");
    for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      for (int touchX = 1; touchX < 5; touchX++) {
        //  NFX4[maxpreset].Pot_Value_graph[touchX - 1] = myFile.read();
        //  NFX4[maxpreset].Pot_Value_graph[touchX + 3] = myFile.read();
        //  NFX4[maxpreset].Pot_Value_graph[touchX + 7] = myFile.read();
      }
    }

    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening NoteFX4.txt");
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    NFX4[NFX4presetNr].Pot_Value[touchX - 1] = NFX4[NFX4presetNr].Pot_Value[touchX - 1];

    NFX4[NFX4presetNr].Pot_Value[touchX + 3] = NFX4[NFX4presetNr].Pot_Value[touchX + 3];

    NFX4[NFX4presetNr].Pot_Value[touchX + 7] = NFX4[NFX4presetNr].Pot_Value[touchX + 7];
  }
}