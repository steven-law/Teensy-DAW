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
void Plugin4_Page_Static(byte Pagenumber) {
  clearWorkSpace();
  drawNrInRect(18, 1, pl4presetNr, ILI9341_PURPLE);
  for (byte touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, CTRL_ROW_0, pl4[pl4presetNr].Vol_rnd[touchX - 1], pl4[pl4presetNr].Vol_rnd[touchX - 1], showVOL[touchX - 1], trackColor[desired_instrument]);
    drawPot(touchX * 4 - 1, CTRL_ROW_1, pl4[pl4presetNr].Vol_rnd[touchX + 3], pl4[pl4presetNr].Vol_rnd[touchX + 3], showVOL[touchX + 3], trackColor[desired_instrument]);
    drawPot(touchX * 4 - 1, CTRL_ROW_2, pl4[pl4presetNr].Vol_rnd[touchX + 7], pl4[pl4presetNr].Vol_rnd[touchX + 7], showVOL[touchX + 7], trackColor[desired_instrument]);
  }
}


void Plugin4_Page1_Dynamic() {
  //change preset
  if (button_15) {
    if (enc_moved[0]) {
      pl4presetNr = constrain((pl4presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, pl4presetNr, ILI9341_PURPLE);
      Plugin4_Page_Static(0);
    }
  }

  if (!button_15) {
    switch (lastPotRow) {
      case 0:

        for (byte touchX = 1; touchX < 5; touchX++) {
          if (enc_moved[touchX - 1]) {
            pl4[pl4presetNr].Vol_rnd[touchX - 1] = constrain((pl4[pl4presetNr].Vol_rnd[touchX - 1] + encoded[touchX - 1]), 0, 127);
            pl4[pl4presetNr].Vol[touchX - 1] = pl4[pl4presetNr].Vol_rnd[touchX - 1] / 127.00;
            drummixer1.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX - 1]);
            drawPot(touchX * 4 - 1, CTRL_ROW_0, pl4[pl4presetNr].Vol_rnd[touchX - 1], pl4[pl4presetNr].Vol_rnd[touchX - 1], showVOL[touchX - 1], trackColor[desired_instrument]);
          }

          /*if (abs(Potentiometer[touchX - 1] - pl4[pl4presetNr].Vol_rnd[touchX - 1]) < POTPICKUP) {
          if (pl4[pl4presetNr].Vol_rnd[touchX - 1] != Potentiometer[touchX - 1]) {
            drawPot(touchX * 4 - 1, CTRL_ROW_0, pl4[pl4presetNr].Vol_rnd[touchX - 1], pl4[pl4presetNr].Vol_rnd[touchX - 1], showVOL[touchX - 1], trackColor[desired_instrument]);
            pl4[pl4presetNr].Vol_rnd[touchX - 1] = Potentiometer[touchX - 1];
            pl4[pl4presetNr].Vol[touchX - 1] = pl4[pl4presetNr].Vol_rnd[touchX - 1] / 127.00;
            drummixer1.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX - 1]);
          }
        }*/
        }



        break;
      case 1:

        for (byte touchX = 1; touchX < 5; touchX++) {
          if (enc_moved[touchX - 1]) {
            pl4[pl4presetNr].Vol_rnd[touchX + 3] = constrain((pl4[pl4presetNr].Vol_rnd[touchX + 3] + encoded[touchX - 1]), 0, 127);
            pl4[pl4presetNr].Vol[touchX + 3] = pl4[pl4presetNr].Vol_rnd[touchX + 3] / 127.00;
            drummixer2.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX + 3]);
            drawPot(touchX * 4 - 1, CTRL_ROW_1, pl4[pl4presetNr].Vol_rnd[touchX + 3], pl4[pl4presetNr].Vol_rnd[touchX + 3], showVOL[touchX + 3], trackColor[desired_instrument]);
          }

          /*  if (abs(Potentiometer[touchX - 1] - pl4[pl4presetNr].Vol_rnd[touchX + 3]) < POTPICKUP) {
          if (pl4[pl4presetNr].Vol_rnd[touchX + 3] != Potentiometer[touchX - 1]) {
            drawPot(touchX * 4 - 1, CTRL_ROW_1, pl4[pl4presetNr].Vol_rnd[touchX + 3], pl4[pl4presetNr].Vol_rnd[touchX + 3], showVOL[touchX + 3], trackColor[desired_instrument]);
            pl4[pl4presetNr].Vol_rnd[touchX + 3] = Potentiometer[touchX - 1];
            pl4[pl4presetNr].Vol[touchX + 3] = pl4[pl4presetNr].Vol_rnd[touchX + 3] / 127.00;
            drummixer2.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX + 3]);
          }
        }*/
        }

        break;
      case 2:

        for (byte touchX = 1; touchX < 5; touchX++) {

          if (enc_moved[touchX - 1]) {
            pl4[pl4presetNr].Vol_rnd[touchX + 7] = constrain((pl4[pl4presetNr].Vol_rnd[touchX + 7] + encoded[touchX - 1]), 0, 127);
            pl4[pl4presetNr].Vol[touchX + 7] = pl4[pl4presetNr].Vol_rnd[touchX + 7] / 127.00;
            drummixer2.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX + 7]);
            drawPot(touchX * 4 - 1, CTRL_ROW_2, pl4[pl4presetNr].Vol_rnd[touchX + 7], pl4[pl4presetNr].Vol_rnd[touchX + 7], showVOL[touchX + 7], trackColor[desired_instrument]);
          }

          /* if (abs(Potentiometer[touchX - 1] - pl4[pl4presetNr].Vol_rnd[touchX + 7]) < POTPICKUP) {
          if (pl4[pl4presetNr].Vol_rnd[touchX + 7] != Potentiometer[touchX - 1]) {
            drawPot(touchX * 4 - 1, CTRL_ROW_2, pl4[pl4presetNr].Vol_rnd[touchX + 7], pl4[pl4presetNr].Vol_rnd[touchX + 7], showVOL[touchX + 7], trackColor[desired_instrument]);
            pl4[pl4presetNr].Vol_rnd[touchX + 7] = Potentiometer[touchX - 1];
            pl4[pl4presetNr].Vol[touchX + 7] = pl4[pl4presetNr].Vol_rnd[touchX + 7] / 127.00;
            drummixer3.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX + 7]);
          }
        }*/
        }

        break;
    }
  }
  TS_Point p = ts.getPoint();
  if (ts.touched() || enter_button) {


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