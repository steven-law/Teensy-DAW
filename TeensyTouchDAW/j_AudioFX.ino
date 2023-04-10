/////////////////////////////////////////////////////////////////////////////////////////////
//reverb
void FX1reverb_settings() {

  reverb1.reverbTime(1000);
  //mixer1 for FX1
  FX1mixer1.gain(0, 1);
  FX1mixer1.gain(1, 1);
  FX1mixer1.gain(2, 1);
  FX1mixer1.gain(3, 1);
  //mixer2 for FX1
  FX1mixer2.gain(0, 1);
  FX1mixer2.gain(1, 1);
  FX1mixer2.gain(2, 1);
  FX1mixer2.gain(3, 1);
  //mixer2 for FX1
  FX1mixer3.gain(0, 1);
  FX1mixer3.gain(1, 1);
  FX1mixer3.gain(2, 1);
  FX1mixer3.gain(3, 1);
  //mixer2 for FX1
  FX1mixer4.gain(0, 1);
  FX1mixer4.gain(1, 1);
  FX1mixer4.gain(2, 1);
  FX1mixer4.gain(3, 1);
  //mixer2 for FX1
  FX1mixer5.gain(0, 1);
  FX1mixer5.gain(1, 1);
  FX1mixer5.gain(2, 1);
  FX1mixer5.gain(3, 1);
  //mixer2 for FX1
  FX1mixer6.gain(0, 1);
  FX1mixer6.gain(1, 1);
  FX1mixer6.gain(2, 1);
  FX1mixer6.gain(3, 1);
}
void FX1reverb_static() {
  clearWorkSpace();
  drawActiveRect(18, 3, 2, 2, false, "Main", ILI9341_LIGHTGREY);
  drawActiveRect(18, 5, 2, 2, false, "D-4", ILI9341_LIGHTGREY);
  drawActiveRect(18, 7, 2, 2, false, "5-8", ILI9341_LIGHTGREY);

  drawActiveRect(1, 5, 2, 2, true, "Rvrb", ILI9341_YELLOW);
  drawActiveRect(1, 8, 2, 2, false, "BitC", ILI9341_LIGHTGREY);
  drawActiveRect(1, 11, 2, 2, false, "Dly", ILI9341_LIGHTGREY);



  draw_reverb_reverbTime(fx1NR, FX1REVERB, 0, 0, 0, 2000, "RTime");
}
void FX1reverb_dynamic() {

  //reverb time

  reverb_reverbTime(fx1NR, FX1REVERB, 0, 0, 0, 2000, "RTime");


  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {



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
      if (gridTouchY == 11 || gridTouchY == 12) {
        selectPage = FX3_PAGE1;
        FX3Delay_static();
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
    for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      //myFile.print((char)fx1reverbtime_graph);
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
    for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      //fx1reverbtime_graph = myFile.read();
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
/////////////////////////////////////////////////////////////////////////////////////////////
//bitcrush
void FX2Bitcrush_settings() {
  //bitcrusher1 controlled by startKnob on page 3
  bitcrusher2.bits(4);
  bitcrusher2.sampleRate(11025);

  //mixer1 for FX2
  FX2mixer1.gain(0, 1);
  FX2mixer1.gain(1, 1);
  FX2mixer1.gain(2, 1);
  FX2mixer1.gain(3, 1);
  //mixer2 for FX2
  FX2mixer2.gain(0, 1);
  FX2mixer2.gain(1, 1);
  FX2mixer2.gain(2, 1);
  FX2mixer2.gain(3, 1);
  //mixer2 for FX2
  FX2mixer3.gain(0, 1);
  FX2mixer3.gain(1, 1);
  FX2mixer3.gain(2, 1);
  FX2mixer3.gain(3, 1);
  //mixer2 for FX2
  FX2mixer4.gain(0, 1);
  FX2mixer4.gain(1, 1);
  FX2mixer4.gain(2, 1);
  FX2mixer4.gain(3, 1);
  //mixer2 for FX2
  FX2mixer5.gain(0, 1);
  FX2mixer5.gain(1, 1);
  FX2mixer5.gain(2, 1);
  FX2mixer5.gain(3, 1);
  //mixer2 for FX2
  FX2mixer6.gain(0, 1);
  FX2mixer6.gain(1, 1);
  FX2mixer6.gain(2, 1);
  FX2mixer6.gain(3, 1);
}
void FX2Bitcrush_static() {
  clearWorkSpace();
  drawActiveRect(18, 3, 2, 2, false, "Main", ILI9341_LIGHTGREY);
  drawActiveRect(18, 5, 2, 2, false, "D-4", ILI9341_LIGHTGREY);
  drawActiveRect(18, 7, 2, 2, false, "5-8", ILI9341_LIGHTGREY);

  drawActiveRect(1, 5, 2, 2, false, "Rvrb", ILI9341_YELLOW);
  drawActiveRect(1, 8, 2, 2, true, "BitC", ILI9341_LIGHTGREY);
  drawActiveRect(1, 11, 2, 2, false, "Dly", ILI9341_LIGHTGREY);

   //saple rate
  draw_bitCrush_sampleRate(fx2NR, FX2BITCRUSH, 0, 0, 1, 44100, "SRate");
  //bitcrush
  draw_bitCrush_bits(fx2NR, FX2BITCRUSH, 1, 0, 1, 16, "Bits");
}
void FX2Bitcrush_dynamic() {
  //saple rate
  bitCrush_sampleRate(fx2NR, FX2BITCRUSH, 0, 0, 1, 44100, "SRate");
  //bitcrush
  bitCrush_bits(fx2NR, FX2BITCRUSH, 1, 0, 1, 16, "Bits");


  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {


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
      if (gridTouchY == 11 || gridTouchY == 12) {
        selectPage = FX3_PAGE1;
        FX3Delay_static();
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
    for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
    //  myFile.print((char)fx2samplerate_graph);
    //  myFile.print((char)fx2bitcrush_graph);
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
    for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      //fx2samplerate_graph = myFile.read();
      //fx2bitcrush_graph = myFile.read();
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

/////////////////////////////////////////////////////////////////////////////////////////////
//delay
void FX3Delay_settings() {
  //bitcrusher1 controlled by startKnob on page 3
  dldelay1.delay(0, fx3delayTime);
  dlmixer1.gain(0, fx3delayAmount);
  dlmixer1.gain(1, fx3delayFeedback);
  dlmixer1.gain(2, 0);
  dlfilter1.frequency(fx3delayFilterFreq);
  dlfilter1.resonance(fx3delayFilterReso);

  //mixer1 for FX3
  FX3mixer1.gain(0, 1);
  FX3mixer1.gain(1, 1);
  FX3mixer1.gain(2, 1);
  FX3mixer1.gain(3, 1);
  //mixer2 for FX3
  FX3mixer2.gain(0, 1);
  FX3mixer2.gain(1, 1);
  FX3mixer2.gain(2, 1);
  FX3mixer2.gain(3, 1);
  //mixer2 for FX3
  FX3mixer3.gain(0, 1);
  FX3mixer3.gain(1, 1);
  FX3mixer3.gain(2, 1);
  FX3mixer3.gain(3, 1);
  //mixer2 for FX3
  FX3mixer4.gain(0, 1);
  FX3mixer4.gain(1, 1);
  FX3mixer4.gain(2, 1);
  FX3mixer4.gain(3, 1);
  //mixer2 for FX3
  FX3mixer5.gain(0, 1);
  FX3mixer5.gain(1, 1);
  FX3mixer5.gain(2, 1);
  FX3mixer5.gain(3, 1);
  //mixer2 for FX3
  FX3mixer6.gain(0, 1);
  FX3mixer6.gain(1, 1);
  FX3mixer6.gain(2, 1);
  FX3mixer6.gain(3, 1);
}
void FX3Delay_static() {
  clearWorkSpace();
  drawActiveRect(18, 3, 2, 2, false, "Main", ILI9341_LIGHTGREY);
  drawActiveRect(18, 5, 2, 2, false, "D-4", ILI9341_LIGHTGREY);
  drawActiveRect(18, 7, 2, 2, false, "5-8", ILI9341_LIGHTGREY);

  drawActiveRect(1, 5, 2, 2, false, "Rvrb", ILI9341_YELLOW);
  drawActiveRect(1, 8, 2, 2, false, "BitC", ILI9341_LIGHTGREY);
  drawActiveRect(1, 11, 2, 2, true, "Dly", ILI9341_BLUE);

  drawPot(0, 0, fx3delayTime_graph, fx3delayTime, "DTime", trackColor[desired_instrument]);
  drawPot(1, 0, fx3delayFeedback_graph, fx3delayFeedback, "Fdbk", trackColor[desired_instrument]);
  drawPot(2, 0, fx3delayAmount_graph, fx3delayAmount_graph, "Amnt", trackColor[desired_instrument]);

  drawPot(0, 1, fx3delayFilterFreq_graph, fx3delayFilterFreq, "Freq", trackColor[desired_instrument]);
  drawPot(1, 1, fx3delayFilterReso_graph, fx3delayFilterReso, "Reso", trackColor[desired_instrument]);
}
void FX3Delay_dynamic() {
  //delaytime
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        Potentiometer[0] = fx3delayTime_graph;
        if (enc_moved[0]) {
          fx3delayTime_graph = constrain((fx3delayTime_graph + encoded[0]), 0, 127);
          fx3delayTime = map(fx3delayTime_graph, 0, 127, 0, 1000);
          dldelay1.delay(0, fx3delayTime);
          drawPot(0, lastPotRow, fx3delayTime_graph, fx3delayTime, "DTime", trackColor[desired_instrument]);
        }
        //feedback
        Potentiometer[1] = fx3delayFeedback_graph;
        if (enc_moved[1]) {
          fx3delayFeedback_graph = constrain((fx3delayFeedback_graph + encoded[1]), 0, 127);
          fx3delayFeedback = fx3delayFeedback_graph / 127.00;
          dlmixer1.gain(1, fx3delayFeedback);
          drawPot(1, lastPotRow, fx3delayFeedback_graph, fx3delayFeedback_graph, "Fdbk", trackColor[desired_instrument]);
        }
        //feedback
        Potentiometer[2] = fx3delayAmount_graph;
        if (enc_moved[2]) {
          fx3delayAmount_graph = constrain((fx3delayAmount_graph + encoded[2]), 0, 127);
          fx3delayAmount = fx3delayAmount_graph / 127.00;
          dlmixer1.gain(0, fx3delayAmount);
          drawPot(2, lastPotRow, fx3delayAmount_graph, fx3delayAmount_graph, "Amnt", trackColor[desired_instrument]);
        }
        break;

        //filterfreq
      case 1:
        Potentiometer[0] = fx3delayFilterFreq_graph;
        if (enc_moved[0]) {
          fx3delayFilterFreq_graph = constrain((fx3delayFilterFreq_graph + encoded[0]), 0, 127);
          fx3delayFilterFreq = note_frequency[fx3delayFilterFreq_graph]* tuning;
          dlfilter1.frequency(fx3delayFilterFreq);
          drawPot(0, lastPotRow, fx3delayFilterFreq_graph, fx3delayFilterFreq, "Freq", trackColor[desired_instrument]);
        }
        //filterreso
        Potentiometer[1] = fx3delayFilterReso_graph;
        if (enc_moved[1]) {
          fx3delayFilterReso_graph = constrain((fx3delayFilterReso_graph + encoded[1]), 0, 127);
          fx3delayFilterReso = fx3delayFilterReso_graph / 127.00;
          dlfilter1.resonance(fx3delayFilterReso);
          drawPot(1, lastPotRow, fx3delayFilterReso_graph, fx3delayFilterReso_graph, "Reso", trackColor[desired_instrument]);
        }
        break;
    }
  }
  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {


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
        selectPage = FX3_PAGE1;
        FX1reverb_static();
      }
      if (gridTouchY == 8 || gridTouchY == 9) {
        selectPage = FX3_PAGE1;
        FX2Bitcrush_static();
      }
      if (gridTouchY == 11 || gridTouchY == 12) {
        selectPage = FX3_PAGE1;
        FX3Delay_static();
      }
    }
  }
}
/*
void saveFX3() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing FX3.txt...");
  SD.remove("FX3.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening FX3.txt...");
  myFile = SD.open("FX3.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    tft.print("Writing plugin 1 to FX3.txt...");
    //save plugin 1 variables
    for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      myFile.print((char)FX3samplerate_graph);
      myFile.print((char)FX3bitcrush_graph);
    }
    tft.println("Done");
    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening FX3.txt");
  }
}
void loadFX3() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("FX3.txt");
  if (myFile) {
    tft.println("opening FX3.txt:");

    //load plugin 1 variables
    tft.print("reading plugin 1 from FX3.txt...");
    for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      FX3samplerate_graph = myFile.read();
      FX3bitcrush_graph = myFile.read();
    }
    tft.println("Done");


    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening FX3.txt");
  }
}*/