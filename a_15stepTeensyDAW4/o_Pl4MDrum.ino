//this is a simple sampleplayer. It reads directly from the sdcard, maybe this is something to change
//about 6-8 samples can be played simultaniously, WHEN WAV-files are Mono and as short as possible (16-bit, 44100Hz)




void Plugin_4_Settings() {
  pl4drummixer1.gain(0, 1);
  pl4drummixer1.gain(1, 1);
  pl4drummixer1.gain(2, 1);
  pl4drummixer1.gain(3, 1);

  pl4drummixer2.gain(0, 1);
  pl4drummixer2.gain(1, 1);
  pl4drummixer2.gain(2, 1);
  pl4drummixer2.gain(3, 1);

  pl4drummixer3.gain(0, 1);
  pl4drummixer3.gain(1, 1);
  pl4drummixer3.gain(2, 1);
  pl4drummixer3.gain(3, 1);

  pl4drummixer4.gain(0, 1);
  pl4drummixer4.gain(1, 1);
  pl4drummixer4.gain(2, 1);
  pl4drummixer4.gain(3, 1);

  pl4amp.gain(1);
  pl4amp2.gain(1);
}
void Plugin4_Control() {
  switch (lastPotRow) {
    case 0:
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (pl4[pl4presetNr].Vol_rnd[MixerColumn] != Potentiometer[MixerColumn]) {
          pl4[pl4presetNr].Vol_rnd[MixerColumn] = Potentiometer[MixerColumn];
          pl4[pl4presetNr].Vol[MixerColumn] = pl4[pl4presetNr].Vol_rnd[MixerColumn] / 127.00;
          pl4drummixer1.gain(MixerColumn, pl4[pl4presetNr].Vol[MixerColumn]);
          drawPot(MixerColumnPos, CTRL_ROW_0, pl4[pl4presetNr].Vol_rnd[MixerColumn], pl4[pl4presetNr].Vol_rnd[MixerColumn], showVOL[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 1:
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (pl4[pl4presetNr].Vol_rnd[MixerColumn + 4] != Potentiometer[MixerColumn]) {
          pl4[pl4presetNr].Vol_rnd[MixerColumn + 4] = Potentiometer[MixerColumn];
          pl4[pl4presetNr].Vol[MixerColumn + 4] = pl4[pl4presetNr].Vol_rnd[MixerColumn + 4] / 127.00;
          pl4drummixer2.gain(MixerColumn, pl4[pl4presetNr].Vol[MixerColumn + 4]);
          drawPot(MixerColumnPos, CTRL_ROW_1, pl4[pl4presetNr].Vol_rnd[MixerColumn + 4], pl4[pl4presetNr].Vol_rnd[MixerColumn + 4], showVOL[MixerColumn + 4], trackColor[desired_instrument]);
        }
      }
      break;

    case 2:
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (pl4[pl4presetNr].Vol_rnd[MixerColumn + 8] != Potentiometer[MixerColumn]) {
          pl4[pl4presetNr].Vol_rnd[MixerColumn + 8] = Potentiometer[MixerColumn];
          pl4[pl4presetNr].Vol[MixerColumn + 8] = pl4[pl4presetNr].Vol_rnd[MixerColumn + 8] / 127.00;
          pl4drummixer3.gain(MixerColumn, pl4[pl4presetNr].Vol[MixerColumn + 8]);
          drawPot(MixerColumnPos, CTRL_ROW_2, pl4[pl4presetNr].Vol_rnd[MixerColumn + 8], pl4[pl4presetNr].Vol_rnd[MixerColumn + 8], showVOL[MixerColumn + 8], trackColor[desired_instrument]);
        }
      }
      break;

    case 3:
      break;
  }
}
void Plugin4_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      pl4presetNr = constrain((pl4presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, pl4presetNr, ILI9341_PURPLE);
      Plugin4_Page_Static(0);
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = pl4[pl4presetNr].Vol_rnd[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((pl4[pl4presetNr].Vol_rnd[MixerColumn] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;

      case 1:
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = pl4[pl4presetNr].Vol_rnd[MixerColumn + 4];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((pl4[pl4presetNr].Vol_rnd[MixerColumn + 4] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;

      case 2:
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = pl4[pl4presetNr].Vol_rnd[MixerColumn + 8];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((pl4[pl4presetNr].Vol_rnd[MixerColumn + 8] + encoded[MixerColumn]), 0, 127);
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
        savePlugin4();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin4();
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
void Plugin4_Page_Static(byte Pagenumber) {
  clearWorkSpace();
  Plugin4_Change();
  drawNrInRect(18, 1, pl4presetNr, ILI9341_PURPLE);
  for (byte touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, CTRL_ROW_0, pl4[pl4presetNr].Vol_rnd[touchX - 1], pl4[pl4presetNr].Vol_rnd[touchX - 1], showVOL[touchX - 1], trackColor[desired_instrument]);
    drawPot(touchX * 4 - 1, CTRL_ROW_1, pl4[pl4presetNr].Vol_rnd[touchX + 3], pl4[pl4presetNr].Vol_rnd[touchX + 3], showVOL[touchX + 3], trackColor[desired_instrument]);
    drawPot(touchX * 4 - 1, CTRL_ROW_2, pl4[pl4presetNr].Vol_rnd[touchX + 7], pl4[pl4presetNr].Vol_rnd[touchX + 7], showVOL[touchX + 7], trackColor[desired_instrument]);
  }
}
void Plugin4_Change() {
  for (byte touchX = 1; touchX < 5; touchX++) {
    pl4drummixer1.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX - 1]);
  }
  for (byte touchX = 1; touchX < 5; touchX++) {
    pl4drummixer2.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX + 3]);
  }   
  for (byte touchX = 1; touchX < 5; touchX++) {
    pl4drummixer3.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX + 7]);
  }
}

void savePlugin4() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing plugin4.txt...");
  SD.remove("plugin4.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening plugin4.txt...");
  myFile = SD.open("plugin4.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    tft.print("Writing plugin4 to plugin4.txt...");
    //save plugin 3 variables
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      for (byte touchX = 1; touchX < 5; touchX++) {
        myFile.print((char)pl4[maxpreset].Vol_rnd[touchX - 1]);
        myFile.print((char)pl4[maxpreset].Vol_rnd[touchX + 3]);
        myFile.print((char)pl4[maxpreset].Vol_rnd[touchX + 7]);
      }
    }

    tft.println("Done");

    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin4.txt");
  }
}

void loadPlugin4() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("plugin4.txt");
  if (myFile) {
    tft.println("opening plugin4.txt:");

    // read from the file until there's nothing else in it:

    //load plugin4 variables
    tft.print("reading plugin4 from plugin4.txt...");
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      for (byte touchX = 1; touchX < 5; touchX++) {
        pl4[maxpreset].Vol_rnd[touchX - 1] = myFile.read();
        pl4[maxpreset].Vol_rnd[touchX + 3] = myFile.read();
        pl4[maxpreset].Vol_rnd[touchX + 7] = myFile.read();
      }
    }

    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin4.txt");
  }
  for (byte touchX = 1; touchX < 5; touchX++) {
    pl4[pl4presetNr].Vol[touchX - 1] = pl4[pl4presetNr].Vol_rnd[touchX - 1] / 127.00;
    pl4drummixer1.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX - 1]);
    pl4[pl4presetNr].Vol[touchX + 3] = pl4[pl4presetNr].Vol_rnd[touchX + 3] / 127.00;
    pl4drummixer2.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX + 3]);
    pl4[pl4presetNr].Vol[touchX + 7] = pl4[pl4presetNr].Vol_rnd[touchX + 7] / 127.00;
    pl4drummixer3.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX + 7]);
  }
}