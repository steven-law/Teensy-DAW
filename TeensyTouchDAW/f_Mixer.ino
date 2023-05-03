
void selectSolo(int XPos, int YPos) {
  int tracknumber = XPos + (YPos * 4);
  byte YPosition = 5 + (YPos*2);
  for (int others = 0; others <= 7; others++) {
    allTracks[others]->muteThruSolo = true;
  }
  allTracks[tracknumber]->muteThruSolo = false;
  allTracks[tracknumber]->soloed = true;
  drawActiveRect((XPos + 1) * 4, YPosition, 1, 1, allTracks[tracknumber]->soloed, "S", ILI9341_WHITE);
}
void selectMute(int XPos, int YPos) {
  int tracknumber = XPos + (YPos * 4);
   byte YPosition = 5 + (YPos*2);
  allTracks[tracknumber]->muted = true;
  drawActiveRect((((XPos + 1) * 4) - 1), YPosition, 1, 1, allTracks[tracknumber]->muted, "M", ILI9341_RED);
}
void unselectMuteSolo(int XPos, int YPos) {
  int tracknumber = XPos + (YPos * 4);
   byte YPosition = 5 + (YPos*2);
  //unmute desired track
  allTracks[tracknumber]->muted = false;
  drawActiveRect((((XPos + 1) * 4) - 1), YPosition, 1, 1, allTracks[tracknumber]->muted, "M", ILI9341_RED);
  //unsolo desired track
  for (int others = 0; others <= 7; others++) {
    allTracks[others]->muteThruSolo = false;
  }
  allTracks[tracknumber]->muteThruSolo = false;
  allTracks[tracknumber]->soloed = false;
  drawActiveRect((XPos + 1) * 4, YPosition, 1, 1, allTracks[tracknumber]->soloed, "S", ILI9341_WHITE);
}
void setMuteSolo(byte XPos, byte YPos, int encoder) {
  static byte muteSolo = 1;
  if (enc_moved[XPos] || incomingCC_changed[XPos]) {
    incomingCC_changed[XPos] = false;
    muteSolo = constrain(getValue(XPos, 1, muteSolo), 0, 2);
    if (muteSolo == 2) {
      selectSolo(XPos, YPos);
    }
    if (muteSolo == 1) {
      unselectMuteSolo(XPos, YPos);
    }
    if (muteSolo == 0) {
      selectMute(XPos, YPos);
    }
  }
}

void Mixer_Settings() {
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.lineInLevel(8);
  sgtl5000_1.volume(0.12);
  //mixer5 for plugins 1-4
  mixer5.gain(0, 1);
  mixer5.gain(1, 1);
  mixer5.gain(2, 1);
  mixer5.gain(3, 1);

  //mixer6 for plugins 5-8
  mixer6.gain(0, 1);
  mixer6.gain(1, 1);
  mixer6.gain(2, 1);
  mixer6.gain(3, 1);

  //drymixer1 for plugins 1-64
  drymixer1.gain(0, 1);
  drymixer1.gain(1, 1);
  drymixer1.gain(2, 1);
  drymixer1.gain(3, 1);

  //drymixer2 for plugins 1-16
  drymixer2.gain(0, 1);
  drymixer2.gain(1, 1);
  drymixer2.gain(2, 1);
  drymixer2.gain(3, 1);

  //drymixer3 for plugins 17-32
  drymixer2.gain(0, 1);
  drymixer2.gain(1, 1);
  drymixer2.gain(2, 1);
  drymixer2.gain(3, 1);

  //mixer9 for sum of dry and fx
  mixer9.gain(0, 1);
  mixer9.gain(1, 1);
  mixer9.gain(2, 1);
  mixer9.gain(3, 1);

  //drymixer2 for plugins 9-12
  mixer10.gain(0, 1);
  mixer10.gain(1, 1);
  mixer10.gain(2, 1);
  mixer10.gain(3, 1);

  //mixer for Audiorecorder
  mixer11.gain(0, 1);
  mixer11.gain(1, 0);


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

void mixerPage1_Static(int mixerpage) {
  clearWorkSpace();
  drawActiveRect(18, 3, 2, 2, true, "Main", ILI9341_LIGHTGREY);
  drawActiveRect(18, 5, 2, 2, false, "D-4", ILI9341_LIGHTGREY);
  drawActiveRect(18, 7, 2, 2, false, "5-8", ILI9341_LIGHTGREY);
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    allTracks[MixerColumn]->drawPotPos(MixerColumn, 0, allTracks[MixerColumn]->gainVol);
  }
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    allTracks[MixerColumn + 4]->drawPotPos(MixerColumn, 2, allTracks[MixerColumn + 4]->gainVol);
  }

  drawActiveRect(3, 5, 1, 1, allTracks[0]->muted, "M", ILI9341_RED);
  drawActiveRect(4, 5, 1, 1, allTracks[0]->soloed, "S", ILI9341_WHITE);

  drawActiveRect(7, 5, 1, 1, allTracks[1]->muted, "M", ILI9341_RED);
  drawActiveRect(8, 5, 1, 1, allTracks[1]->soloed, "S", ILI9341_WHITE);

  drawActiveRect(11, 5, 1, 1, allTracks[2]->muted, "M", ILI9341_RED);
  drawActiveRect(12, 5, 1, 1, allTracks[2]->soloed, "S", ILI9341_WHITE);

  drawActiveRect(15, 5, 1, 1, allTracks[3]->muted, "M", ILI9341_RED);
  drawActiveRect(16, 5, 1, 1, allTracks[3]->soloed, "S", ILI9341_WHITE);

  drawActiveRect(3, 11, 1, 1, allTracks[4]->muted, "M", ILI9341_RED);
  drawActiveRect(4, 11, 1, 1, allTracks[4]->soloed, "S", ILI9341_WHITE);


  drawActiveRect(7, 11, 1, 1, allTracks[5]->muted, "M", ILI9341_RED);
  drawActiveRect(8, 11, 1, 1, allTracks[5]->soloed, "S", ILI9341_WHITE);

  drawActiveRect(11, 11, 1, 1, allTracks[6]->muted, "M", ILI9341_RED);
  drawActiveRect(12, 11, 1, 1, allTracks[6]->soloed, "S", ILI9341_WHITE);

  drawActiveRect(15, 11, 1, 1, allTracks[7]->muted, "M", ILI9341_RED);
  drawActiveRect(16, 11, 1, 1, allTracks[7]->soloed, "S", ILI9341_WHITE);

  drawPot(3, 3, MasterVol_graph, MasterVol_graph, "OUT", ILI9341_BLACK);
}
void MixerPage1_Dynamic() {

  switch (lastPotRow) {
    case 0:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        allTracks[MixerColumn]->setVolGain(MixerColumn, 0);
      }
      break;
    case 1:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        setMuteSolo(MixerColumn, 0, encoded[MixerColumn]);
      }
      break;
    case 2:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        allTracks[MixerColumn + 4]->setVolGain(MixerColumn, 2);
      }
      break;
    case 3:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        setMuteSolo(MixerColumn, 3, encoded[MixerColumn]);
      }
      break;
  }

  if (!ts.touched() && !button[15]) {
    touched = false;
  }
  if (ts.touched() || button[15]) {
    if (!touched) {

      readTouchinput();

      //page selection
      if (gridTouchX >= 18 && gridTouchY >= 3 && gridTouchY <= 4) {
        selectPage = MIXER_PAGE_1;
        mixerPage1_Static(0);
        MixerPage1_Dynamic();
      }
      if (gridTouchX >= 18 && gridTouchY >= 5 && gridTouchY <= 6) {
        selectPage = MIXER_PAGE_2;
        mixerPage2_Static();
        MixerPage2_Dynamic();
      }
      if (gridTouchX >= 18 && gridTouchY >= 7 && gridTouchY <= 8) {
        selectPage = MIXER_PAGE_3;
        mixerPage3_Static();
        MixerPage3_Dynamic();
      }
    }
  }
}


void mixerPage2_Static() {
  clearWorkSpace();
  //draw_sub_page_buttons(2);
  drawActiveRect(18, 3, 2, 2, false, "Main", ILI9341_LIGHTGREY);
  drawActiveRect(18, 5, 2, 2, true, "D-4", ILI9341_LIGHTGREY);
  drawActiveRect(18, 7, 2, 2, false, "5-8", ILI9341_LIGHTGREY);

  drawActiveRect(1, 5, 2, 2, false, "Rvrb", ILI9341_YELLOW);
  drawActiveRect(1, 8, 2, 2, false, "BitC", ILI9341_LIGHTGREY);
  drawActiveRect(1, 11, 2, 2, false, "Dly", ILI9341_LIGHTGREY);

  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    allTracks[MixerColumn]->drawPotPos(MixerColumn, 0, allTracks[MixerColumn]->dryVol);
    allTracks[MixerColumn]->drawPotPos(MixerColumn, 1, allTracks[MixerColumn]->FX1Vol);
    allTracks[MixerColumn]->drawPotPos(MixerColumn, 2, allTracks[MixerColumn]->FX2Vol);
    allTracks[MixerColumn]->drawPotPos(MixerColumn, 3, allTracks[MixerColumn]->FX3Vol);
  }
}
void MixerPage2_Dynamic() {
  switch (lastPotRow) {
    case 0:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        if (enc_moved[MixerColumn]) {
          Potentiometer[MixerColumn] = constrain(allTracks[MixerColumn]->dryVol + encoded[MixerColumn], 0, 127);
          allTracks[MixerColumn]->setVolDry(MixerColumn, 0, Potentiometer[MixerColumn]);
        }
      }
      break;
    case 1:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        if (enc_moved[MixerColumn]) {
          Potentiometer[MixerColumn] = constrain(allTracks[MixerColumn]->FX1Vol + encoded[MixerColumn], 0, 127);
          allTracks[MixerColumn]->setVolFX1(MixerColumn, 1, Potentiometer[MixerColumn]);
        }
      }
      break;
    case 2:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        if (enc_moved[MixerColumn]) {
          Potentiometer[MixerColumn] = constrain(allTracks[MixerColumn]->FX2Vol + encoded[MixerColumn], 0, 127);
          allTracks[MixerColumn]->setVolFX2(MixerColumn, 2, Potentiometer[MixerColumn]);
        }
      }
      break;
    case 3:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        if (enc_moved[MixerColumn]) {
          Potentiometer[MixerColumn] = constrain(allTracks[MixerColumn]->FX3Vol + encoded[MixerColumn], 0, 127);
          allTracks[MixerColumn]->setVolFX3(MixerColumn, 3, Potentiometer[MixerColumn]);
        }
      }
      break;
  }
  if (ts.touched() || button[15]) {
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

void mixerPage3_Static() {
  clearWorkSpace();
  //draw_sub_page_buttons(2);
  drawActiveRect(18, 3, 2, 2, false, "Main", ILI9341_LIGHTGREY);
  drawActiveRect(18, 5, 2, 2, false, "D-4", ILI9341_LIGHTGREY);
  drawActiveRect(18, 7, 2, 2, true, "5-8", ILI9341_LIGHTGREY);

  drawActiveRect(1, 5, 2, 2, false, "Rvrb", ILI9341_YELLOW);
  drawActiveRect(1, 8, 2, 2, false, "BitC", ILI9341_LIGHTGREY);
  drawActiveRect(1, 11, 2, 2, false, "Dly", ILI9341_LIGHTGREY);

  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    allTracks[MixerColumn + 4]->drawPotPos(MixerColumn, 0, allTracks[MixerColumn + 4]->dryVol);
    allTracks[MixerColumn + 4]->drawPotPos(MixerColumn, 1, allTracks[MixerColumn + 4]->FX1Vol);
    allTracks[MixerColumn + 4]->drawPotPos(MixerColumn, 2, allTracks[MixerColumn + 4]->FX2Vol);
    allTracks[MixerColumn + 4]->drawPotPos(MixerColumn, 3, allTracks[MixerColumn + 4]->FX3Vol);
  }
}
void MixerPage3_Dynamic() {
  switch (lastPotRow) {
    case 0:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        allTracks[MixerColumn + 4]->setVolDry(MixerColumn, 0, Potentiometer[MixerColumn]);
      }
      break;
    case 1:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        allTracks[MixerColumn + 4]->setVolFX1(MixerColumn, 1, Potentiometer[MixerColumn]);
      }
      break;
    case 2:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        allTracks[MixerColumn + 4]->setVolFX2(MixerColumn, 2, Potentiometer[MixerColumn]);
      }
      break;
    case 3:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        allTracks[MixerColumn + 4]->setVolFX3(MixerColumn, 3, Potentiometer[MixerColumn]);
      }
      break;
  }
  if (ts.touched() || button[15]) {

    if (gridTouchX >= 18) {
      //page selection
      if (gridTouchY >= 3 && gridTouchY <= 4) {
        selectPage = MIXER_PAGE_1;
        mixerPage1_Static(0);
      }
      if (gridTouchY >= 5 && gridTouchY <= 6) {
        selectPage = MIXER_PAGE_2;
        mixerPage2_Static();
      }
      if (gridTouchY >= 7 && gridTouchY <= 8) {
        selectPage = MIXER_PAGE_3;
        mixerPage3_Static();
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
void pluginVolume(int pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  for (int pluginn = 0; pluginn < 16; pluginn++) {
    if (pluginchannel == pluginn + 17) {
      gainPerBar[pluginn]->gain(volume);
    }
  }
}

void saveMixer() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing mixer.txt...");
  SD.remove("mixer.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening mixer.txt...");
  myFile = SD.open("mixer.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    tft.print("Writing mixer to mixer.txt...");
    //save mixer variables

    for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

      myFile.print((char)allTracks[MixerColumn]->gainVol);
      myFile.print((char)allTracks[MixerColumn + 4]->gainVol);
      myFile.print((char)allTracks[MixerColumn]->dryVol);
      myFile.print((char)allTracks[MixerColumn + 4]->dryVol);
      myFile.print((char)allTracks[MixerColumn]->FX1Vol);
      myFile.print((char)allTracks[MixerColumn + 4]->FX1Vol);
      myFile.print((char)allTracks[MixerColumn]->FX2Vol);
      myFile.print((char)allTracks[MixerColumn + 4]->FX2Vol);
      myFile.print((char)allTracks[MixerColumn]->FX3Vol);
      myFile.print((char)allTracks[MixerColumn + 4]->FX3Vol);
    }


    tft.println("Done");

    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening mixer.txt");
  }
}

void loadMixer() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("mixer.txt");
  if (myFile) {
    tft.println("opening mixer.txt:");

    // read from the file until there's nothing else in it:

    //load mixer variables
    tft.print("reading mixer from mixer.txt...");
    for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
      allTracks[MixerColumn]->gainVol = myFile.read();
      allTracks[MixerColumn + 4]->gainVol = myFile.read();
      allTracks[MixerColumn]->dryVol = myFile.read();
      allTracks[MixerColumn + 4]->dryVol = myFile.read();
      allTracks[MixerColumn]->FX1Vol = myFile.read();
      allTracks[MixerColumn + 4]->FX1Vol = myFile.read();
      allTracks[MixerColumn]->FX2Vol = myFile.read();
      allTracks[MixerColumn + 4]->FX2Vol = myFile.read();
      allTracks[MixerColumn]->FX3Vol = myFile.read();
      allTracks[MixerColumn + 4]->FX3Vol = myFile.read();
    }


    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin2.txt");
  }
  //execute changes
}