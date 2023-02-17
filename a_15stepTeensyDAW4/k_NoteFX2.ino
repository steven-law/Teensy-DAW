//this is a simple sampleplayer. It reads directly from the sdcard, maybe this is something to change
//about 6-8 samples can be played simultaniously, WHEN WAV-files are Mono and as short as possible (16-bit, 44100Hz)




void NoteFX2_Settings() {
}
void NoteFX2_Control() {
  switch (lastPotRow) {
    case 0:
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn] != Potentiometer[MixerColumn]) {
          NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn] = Potentiometer[MixerColumn];
          NFX2[NFX2presetNr].Pot_Value[MixerColumn] = NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn];

          drawPot(MixerColumnPos, CTRL_ROW_0, NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn], NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn], NFX2_ROW1[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 1:
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 4] != Potentiometer[MixerColumn]) {
          NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 4] = Potentiometer[MixerColumn];
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4] = NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 4];

          drawPot(MixerColumnPos, CTRL_ROW_1, NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 4], NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 4], NFX2_ROW2[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 2:
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 8] != Potentiometer[MixerColumn]) {
          NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 8] = Potentiometer[MixerColumn];
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8] = NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 8];

          drawPot(MixerColumnPos, CTRL_ROW_2, NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 8], NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 8], NFX2_ROW3[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 3:
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 12] != Potentiometer[MixerColumn]) {
          NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 12] = Potentiometer[MixerColumn];
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12] = NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 12];

          drawPot(MixerColumnPos, CTRL_ROW_3, NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 12], NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 12], NFX2_ROW4[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;
  }
}
void NoteFX2_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      NFX2presetNr = constrain((NFX2presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, NFX2presetNr, trackColor[desired_instrument]);
      NoteFX2_Page_Static(0);
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 1:
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 4];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 4] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 2:
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 8];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 8] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 3:
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 12];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX2[NFX2presetNr].Pot_Value_graph[MixerColumn + 12] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
    }
  }
  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        saveNoteFX2();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadNoteFX2();
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
void NoteFX2_Page_Static(byte Pagenumber) {
  clearWorkSpace();
  NoteFX2_Change();
  drawNrInRect(18, 1, NFX2presetNr, ILI9341_PURPLE);
  drawChar(18, 3, seqModes[track[desired_track].seqMode], trackColor[desired_track]);
  for (byte touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, CTRL_ROW_0, NFX2[NFX2presetNr].Pot_Value_graph[touchX - 1], NFX2[NFX2presetNr].Pot_Value_graph[touchX - 1], NFX2_ROW1[touchX - 1], trackColor[desired_instrument]);
  }
  for (byte touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, CTRL_ROW_1, NFX2[NFX2presetNr].Pot_Value_graph[touchX + 3], NFX2[NFX2presetNr].Pot_Value_graph[touchX + 3], NFX2_ROW2[touchX -1], trackColor[desired_instrument]);
  }
  for (byte touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, CTRL_ROW_2, NFX2[NFX2presetNr].Pot_Value_graph[touchX + 7], NFX2[NFX2presetNr].Pot_Value_graph[touchX + 7], NFX2_ROW3[touchX -1], trackColor[desired_instrument]);
  }
  for (byte touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, CTRL_ROW_3, NFX2[NFX2presetNr].Pot_Value_graph[touchX + 11], NFX2[NFX2presetNr].Pot_Value_graph[touchX + 11], NFX2_ROW4[touchX -1], trackColor[desired_instrument]);
  }
}

void NoteFX2_Change() {
  for (byte touchX = 1; touchX < 5; touchX++) {

    NFX2[NFX2presetNr].Pot_Value_graph[touchX - 1];
  }
  for (byte touchX = 1; touchX < 5; touchX++) {

    NFX2[NFX2presetNr].Pot_Value_graph[touchX + 3];
  }
  for (byte touchX = 1; touchX < 5; touchX++) {
    NFX2[NFX2presetNr].Pot_Value_graph[touchX + 7];
  }
  for (byte touchX = 1; touchX < 5; touchX++) {
    NFX2[NFX2presetNr].Pot_Value_graph[touchX + 11];
  }
}


void saveNoteFX2() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing NoteFX2.txt...");
  SD.remove("NoteFX2.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening NoteFX2.txt...");
  myFile = SD.open("NoteFX2.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    tft.print("Writing NoteFX2 to NoteFX2.txt...");
    //save plugin 3 variables
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      for (byte touchX = 1; touchX < 5; touchX++) {
        myFile.print((char)NFX2[maxpreset].Pot_Value_graph[touchX - 1]);
        myFile.print((char)NFX2[maxpreset].Pot_Value_graph[touchX + 3]);
        myFile.print((char)NFX2[maxpreset].Pot_Value_graph[touchX + 7]);
        myFile.print((char)NFX2[maxpreset].Pot_Value_graph[touchX + 11]);
      }
    }

    tft.println("Done");

    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening NoteFX2.txt");
  }
}

void loadNoteFX2() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("NoteFX2.txt");
  if (myFile) {
    tft.println("opening NoteFX2.txt:");

    // read from the file until there's nothing else in it:

    //load NoteFX2 variables
    tft.print("reading NoteFX2 from NoteFX2.txt...");
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      for (byte touchX = 1; touchX < 5; touchX++) {
        NFX2[maxpreset].Pot_Value_graph[touchX - 1] = myFile.read();
        NFX2[maxpreset].Pot_Value_graph[touchX + 3] = myFile.read();
        NFX2[maxpreset].Pot_Value_graph[touchX + 7] = myFile.read();
        NFX2[maxpreset].Pot_Value_graph[touchX + 11] = myFile.read();
      }
    }

    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening NoteFX2.txt");
  }
  for (byte touchX = 1; touchX < 5; touchX++) {
    NFX2[NFX2presetNr].Pot_Value[touchX - 1] = NFX2[NFX2presetNr].Pot_Value_graph[touchX - 1];

    NFX2[NFX2presetNr].Pot_Value[touchX + 3] = NFX2[NFX2presetNr].Pot_Value_graph[touchX + 3];

    NFX2[NFX2presetNr].Pot_Value[touchX + 7] = NFX2[NFX2presetNr].Pot_Value_graph[touchX + 7];
    NFX2[NFX2presetNr].Pot_Value[touchX + 11] = NFX2[NFX2presetNr].Pot_Value_graph[touchX + 11];
  }
}
