void FX1reverb_settings() {

  reverb1.reverbTime(1000);
  //mixer1 for FX1
  FX1mixer1.gain(0, 0);
  FX1mixer1.gain(1, 0);
  FX1mixer1.gain(2, 0);
  FX1mixer1.gain(3, 0);
  //mixer2 for FX1
  FX1mixer2.gain(0, 0);
  FX1mixer2.gain(1, 0);
  FX1mixer2.gain(2, 0);
  FX1mixer2.gain(3, 0);
  //mixer2 for FX1
  FX1mixer3.gain(0, 1);
  FX1mixer3.gain(1, 1);
  FX1mixer3.gain(2, 1);
  FX1mixer3.gain(3, 1);
  //mixer2 for FX1
  FX1mixer4.gain(0, 0);
  FX1mixer4.gain(1, 0);
  FX1mixer4.gain(2, 0);
  FX1mixer4.gain(3, 0);
}

void FX1reverb_static() {
  clearWorkSpace();
  drawActiveRect(18, 3, 2, 2, false, "Main", ILI9341_LIGHTGREY);
  drawActiveRect(18, 5, 2, 2, false, "D-4", ILI9341_LIGHTGREY);
  drawActiveRect(18, 7, 2, 2, false, "5-8", ILI9341_LIGHTGREY);

  drawActiveRect(1, 5, 2, 2, true, "Rvrb", ILI9341_YELLOW);
  drawActiveRect(1, 8, 2, 2, false, "BitC", ILI9341_LIGHTGREY);
  drawActiveRect(1, 11, 2, 2, false, "Dly", ILI9341_LIGHTGREY);



  drawPot(CTRL_COL_0, CTRL_ROW_0, fx1reverbtime_graph, fx1reverbtime_graph, "Reverb", ILI9341_YELLOW);
}

void FX1reverb_dynamic() {
  //if (msecs % 20 == 0) {

    if (abs(Potentiometer[0] - fx1reverbtime_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
      if (fx1reverbtime_graph != Potentiometer[0]) {
        drawPot(CTRL_COL_0, CTRL_ROW_0, fx1reverbtime_graph, fx1reverbtime_graph, "Reverb", ILI9341_YELLOW);
        fx1reverbtime_graph = Potentiometer[0];
        fx1reverbtime = fx1reverbtime_graph / 10;
        reverb1.reverbTime(fx1reverbtime);
      }
    }
  //}

  
  TS_Point p = ts.getPoint();
  if (ts.touched() || enter_button) {



    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        saveFX1();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadFX1();
      }
    }

    if (gridTouchX >= 18) {
      //page selection
      if (gridTouchY == 3 || gridTouchY == 4) {
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
        selectPage = FX1_PAGE1;
        FX1reverb_static();
      }
      if (gridTouchY == 8 || gridTouchY == 9) {
        selectPage = FX2_PAGE1;
        FX2Bitcrush_static();
      }
    }
  }
}



void saveFX1() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing FX1.txt...");
  SD.remove("FX1.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening FX1.txt...");
  myFile = SD.open("FX1.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    tft.print("Writing plugin 1 to FX1.txt...");
    //save plugin 1 variables
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      myFile.print((char)fx1reverbtime_graph);
    }
    tft.println("Done");
    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening FX1.txt");
  }
}
void loadFX1() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("FX1.txt");
  if (myFile) {
    tft.println("opening FX1.txt:");

    //load plugin 1 variables
    tft.print("reading plugin 1 from FX1.txt...");
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      fx1reverbtime_graph = myFile.read();
    }
    tft.println("Done");


    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening FX1.txt");
  }
}