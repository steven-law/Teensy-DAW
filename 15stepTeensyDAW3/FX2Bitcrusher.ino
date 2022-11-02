void FX2Bitcrush_settings() {
  //bitcrusher1 controlled by startKnob on page 3
  bitcrusher2.bits(4);
  bitcrusher2.sampleRate(11025);

  //mixer1 for FX2
  FX2mixer1.gain(0, 0);
  FX2mixer1.gain(1, 0);
  FX2mixer1.gain(2, 0);
  FX2mixer1.gain(3, 0);
  //mixer2 for FX2
  FX2mixer2.gain(0, 0);
  FX2mixer2.gain(1, 0);
  FX2mixer2.gain(2, 0);
  FX2mixer2.gain(3, 0);
  //mixer2 for FX2
  FX2mixer3.gain(0, 1);
  FX2mixer3.gain(1, 1);
  FX2mixer3.gain(2, 1);
  FX2mixer3.gain(3, 1);
}

void FX2Bitcrush_static() {
  clearWorkSpace();
  drawActiveRect(18, 3, 2, 2, false, "Main", ILI9341_LIGHTGREY);
  drawActiveRect(18, 5, 2, 2, false, "D-4", ILI9341_LIGHTGREY);
  drawActiveRect(18, 7, 2, 2, false, "5-8", ILI9341_LIGHTGREY);

  drawActiveRect(1, 5, 2, 2, false, "Rvrb", ILI9341_LIGHTGREY);
  drawActiveRect(1, 8, 2, 2, true, "BitC", ILI9341_LIGHTGREY);
  drawActiveRect(1, 11, 2, 2, false, "Dly", ILI9341_LIGHTGREY);

  drawPot(3, 3, fx2samplerate_graph, fx2samplerate, "SRate", trackColor[desired_instrument]);
  drawPot(7, 3, fx2bitcrush_graph, fx2bitcrush, "Crush", trackColor[desired_instrument]);
}

void FX2Bitcrush_dynamic() {
    TS_Point p = ts.getPoint();
  if (ts.touched() || !buttons[6].read()) {
    gridTouchX = map(p.x, TS_MINX, TS_MAXX, 0, 19);
    gridTouchY = map(p.y, TS_MINY, TS_MAXY, 0, 14);


    if (gridTouchY == 3) {

      //samplerate
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, 3, fx2samplerate_graph, fx2samplerate, "SRate", trackColor[desired_instrument]);
        if (abs(Potentiometer1 - fx2samplerate_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          fx2samplerate_graph = Potentiometer1;
          fx2samplerate = map(fx2samplerate_graph, 0, 127, 0, 44200);
          bitcrusher2.sampleRate(fx2samplerate);
        }
      }

      //samplerate
      if (gridTouchX == 7 || gridTouchX == 8) {
        drawPot(7, 3, fx2bitcrush_graph, fx2bitcrush, "Crush", trackColor[desired_instrument]);
        if (abs(Potentiometer1 - fx2bitcrush_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          fx2bitcrush_graph = Potentiometer1;
          fx2bitcrush = map(fx2bitcrush_graph, 0, 127, 0, 12);
          bitcrusher2.bits(fx2bitcrush);
        }
      }
    }
    if (gridTouchX >= 18) {
      //page selection
      if (gridTouchY >= 3 && gridTouchY <= 4) {
        selectPage = MIXER_PAGE_1;
        mixerPage1_Static(0);
        MixerPage1_Dynamic();
      }
      if (gridTouchY >= 5 && gridTouchY <= 6) {
        selectPage = MIXER_PAGE_2;
        mixerPage2_Static();
        MixerPage2_Dynamic();
      }
      if (gridTouchY >= 7 && gridTouchY <= 8) {
        selectPage = MIXER_PAGE_3;
        mixerPage3_Static();
        MixerPage3_Dynamic();
      }
    }
    if (gridTouchX == 1 || gridTouchX == 2) {

      if (gridTouchY == 5 || gridTouchY == 6) {
        selectPage = FX2_PAGE1;
        FX1reverb_static();
      }
      if (gridTouchY == 8 || gridTouchY == 9) {
        selectPage = FX2_PAGE1;
        FX2Bitcrush_static();
      }
    }
  }
}

void saveFX2() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing FX2.txt...");
  SD.remove("FX2.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening FX2.txt...");
  myFile = SD.open("FX2.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    tft.print("Writing plugin 1 to FX2.txt...");
    //save plugin 1 variables
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      myFile.print((char)fx2samplerate_graph);
      myFile.print((char)fx2bitcrush_graph);
    }
    tft.println("Done");
    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening FX2.txt");
  }
}
void loadFX2() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("FX2.txt");
  if (myFile) {
    tft.println("opening FX2.txt:");

    //load plugin 1 variables
    tft.print("reading plugin 1 from FX2.txt...");
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      fx2samplerate_graph = myFile.read();
      fx2bitcrush_graph = myFile.read();
    }
    tft.println("Done");


    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening FX2.txt");
  }
}