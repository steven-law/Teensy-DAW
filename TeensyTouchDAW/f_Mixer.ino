void selectSolo(int tracknumber) {

  if (!track[tracknumber].solo_state) {
    for (int others = 0; others <= 7; others++) {
      track[others].solo_mutes_state = HIGH;
    }
    track[tracknumber].solo_mutes_state = LOW;
    track[tracknumber].solo_state = HIGH;
  } else if (track[tracknumber].solo_state) {
    for (int others = 0; others <= 7; others++) {
      track[others].solo_mutes_state = LOW;
    }
    track[tracknumber].solo_mutes_state = LOW;
    track[tracknumber].solo_state = LOW;
  }
}
void selectMute(int tracknumber) {
  if (!track[tracknumber].mute_state) {
    track[tracknumber].mute_state = HIGH;
  } else if (track[tracknumber].mute_state) {
    track[tracknumber].mute_state = LOW;
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



  drawPot(0, 0, track[0].gain_graph, track[0].gain_graph, "TrD", trackColor[0]);
  drawActiveRect(3, 5, 1, 1, track[0].mute_state, "M", ILI9341_RED);
  drawActiveRect(4, 5, 1, 1, track[0].solo_state, "S", ILI9341_WHITE);
  drawPot(1, 0, track[1].gain_graph, track[1].gain_graph, "Tr2", trackColor[1]);
  drawActiveRect(7, 5, 1, 1, track[1].mute_state, "M", ILI9341_RED);
  drawActiveRect(8, 5, 1, 1, track[1].solo_state, "S", ILI9341_WHITE);
  drawPot(2, 0, track[2].gain_graph, track[2].gain_graph, "Tr3", trackColor[2]);
  drawActiveRect(11, 5, 1, 1, track[2].mute_state, "M", ILI9341_RED);
  drawActiveRect(12, 5, 1, 1, track[2].solo_state, "S", ILI9341_WHITE);
  drawPot(3, 0, track[3].gain_graph, track[3].gain_graph, "Tr4", trackColor[3]);
  drawActiveRect(15, 5, 1, 1, track[3].mute_state, "M", ILI9341_RED);
  drawActiveRect(16, 5, 1, 1, track[3].solo_state, "S", ILI9341_WHITE);

  drawPot(0, 2, track[4].gain_graph, track[4].gain_graph, "Tr5", trackColor[4]);
  drawActiveRect(3, 11, 1, 1, track[4].mute_state, "M", ILI9341_RED);
  drawActiveRect(4, 11, 1, 1, track[4].solo_state, "S", ILI9341_WHITE);
  drawPot(1, 2, track[5].gain_graph, track[5].gain_graph, "Tr6", trackColor[5]);
  drawActiveRect(7, 11, 1, 1, track[5].mute_state, "M", ILI9341_RED);
  drawActiveRect(8, 11, 1, 1, track[5].solo_state, "S", ILI9341_WHITE);
  drawPot(2, 2, track[6].gain_graph, track[6].gain_graph, "Tr7", trackColor[6]);
  drawActiveRect(11, 11, 1, 1, track[6].mute_state, "M", ILI9341_RED);
  drawActiveRect(12, 11, 1, 1, track[6].solo_state, "S", ILI9341_WHITE);
  drawPot(3, 2, track[7].gain_graph, track[7].gain_graph, "Tr8", trackColor[7]);
  drawActiveRect(15, 11, 1, 1, track[7].mute_state, "M", ILI9341_RED);
  drawActiveRect(16, 11, 1, 1, track[7].solo_state, "S", ILI9341_WHITE);
  drawPot(5, 4, MasterVol_graph, MasterVol_graph, "OUT", ILI9341_BLACK);
}
void MixerPage1_Dynamic() {
  switch (lastPotRow) {
    case 0:

      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        //Row1
        if (enc_moved[MixerColumn]) {
          track[MixerColumn].gain_graph = constrain((track[MixerColumn].gain_graph + encoded[MixerColumn]), 0, 127);
          drawPot(MixerColumn, 0, track[MixerColumn].gain_graph, track[MixerColumn].gain_graph, trackNames_short[MixerColumn], trackColor[MixerColumn]);
          if (track[MixerColumn].MIDIchannel > 16) {
            track[MixerColumn].gain = track[MixerColumn].gain_graph / 127.00;
            pluginGain(track[MixerColumn].MIDIchannel, track[MixerColumn].gain);
          }
        }


        /* if (abs(Potentiometer[MixerColumn] - track[MixerColumn].gain_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (track[MixerColumn].gain_graph != Potentiometer[MixerColumn]) {
            track[MixerColumn].gain_graph = Potentiometer[MixerColumn];


            drawPot(MixerColumn, 3, track[MixerColumn].gain_graph, track[MixerColumn].gain_graph, trackNames_short[MixerColumn], trackColor[MixerColumn]);
          }
          if (track[MixerColumn].MIDIchannel > 16) {
            track[MixerColumn].gain = track[MixerColumn].gain_graph / 127.00;
            pluginGain(track[MixerColumn].MIDIchannel, track[MixerColumn].gain);
          }
        }*/
      }

      break;
    case 1:

      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        //Row2
        if (enc_moved[MixerColumn]) {
          track[MixerColumn + 4].gain_graph = constrain((track[MixerColumn + 4].gain_graph + encoded[MixerColumn]), 0, 127);
          drawPot(MixerColumn, 2, track[MixerColumn + 4].gain_graph, track[MixerColumn + 4].gain_graph, trackNames_short[MixerColumn + 4], trackColor[MixerColumn + 4]);
          if (track[MixerColumn + 4].MIDIchannel > 16) {
            track[MixerColumn + 4].gain = track[MixerColumn + 4].gain_graph / 127.00;
            pluginGain(track[MixerColumn + 4].MIDIchannel, track[MixerColumn + 4].gain);
          }
        }

        /*if (abs(Potentiometer[MixerColumn] - track[MixerColumn + 4].gain_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (track[MixerColumn + 4].gain_graph != Potentiometer[MixerColumn]) {
            track[MixerColumn + 4].gain_graph = Potentiometer[MixerColumn];

            drawPot(MixerColumn, 9, track[MixerColumn + 4].gain_graph, track[MixerColumn + 4].gain_graph, trackNames_short[MixerColumn + 4], trackColor[MixerColumn + 4]);
          }
          if (track[MixerColumn + 4].MIDIchannel > 16) {
            track[MixerColumn + 4].gain = track[MixerColumn + 4].gain_graph / 127.00;
            pluginGain(track[MixerColumn + 4].MIDIchannel, track[MixerColumn + 4].gain);
          }
        }*/
      }

      break;
    case 2:
      //Row3
      if (enc_moved[3]) {
        MasterVol_graph = constrain((MasterVol_graph + encoded[3]), 0, 127);
        MasterVol = MasterVol_graph / 127.00;
        sgtl5000_1.volume(MasterVol);
        drawPot(4, 3, MasterVol_graph, MasterVol_graph, "OUT", ILI9341_BLACK);
      }
      /* if (abs(Potentiometer[3] - MasterVol_graph) < POTPICKUP) {
        if (MasterVol_graph != Potentiometer[3]) {
          MasterVol_graph = Potentiometer[3];
          MasterVol = MasterVol_graph / 127.00;
          sgtl5000_1.volume(MasterVol);
          drawPot(18, 12, MasterVol_graph, MasterVol_graph, "OUT", ILI9341_BLACK);
        }
      }*/

      break;
  }
  static bool touched;
  if (!ts.touched() && !button[15]) {
    touched = false;
  }
  if (ts.touched() || button[15]) {
    if (!touched) {

      if (gridTouchY >= 2 && gridTouchY <= 4) {
        lastPotRow = 0;
      }

      if (gridTouchY >= 5 && gridTouchY <= 7) {
        lastPotRow = 1;
      }

      if (gridTouchX >= 18 || gridTouchY >= 12) {
        lastPotRow = 2;
      }




      //mute and solo states track 1-4
      //for better behaviour here we wait for "interval, unless it would switch within micrseconds
      if (gridTouchY == 5) {

        for (int mutes = 0; mutes < 4; mutes++) {
          if (gridTouchX == (((mutes + 1) * 4) - 1)) {
            touched = true;
            selectMute(mutes);
            drawActiveRect((((mutes + 1) * 4) - 1), 5, 1, 1, track[mutes].mute_state, "M", ILI9341_RED);
          }
        }
        for (int solos = 0; solos < 4; solos++) {
          if (gridTouchX == (solos + 1) * 4) {
            touched = true;
            selectSolo(solos);
            drawActiveRect((solos + 1) * 4, 5, 1, 1, track[solos].solo_state, "S", ILI9341_WHITE);
          }
        }
      }
      //mute and solo states Track 5-8
      //for better behaviour here we wait for "interval, unless it would switch within micrseconds
      if (gridTouchY == 11) {

        for (int mutes = 0; mutes < 4; mutes++) {
          if (gridTouchX == (((mutes + 1) * 4) - 1)) {
            selectMute(mutes + 4);
            drawActiveRect((((mutes + 1) * 4) - 1), 11, 1, 1, track[mutes + 4].mute_state, "M", ILI9341_RED);
            touched = true;
          }
        }
        for (int solos = 0; solos < 4; solos++) {
          if (gridTouchX == (solos + 1) * 4) {
            touched = true;
            selectSolo(solos + 4);
            drawActiveRect((solos + 1) * 4, 11, 1, 1, track[solos + 4].solo_state, "S", ILI9341_WHITE);
          }
        }
      }

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

    drawPot(0, 0, track[0].FXDryVolume_graph, track[0].FXDryVolume_graph, trackNames_short[8], trackColor[0]);
    drawPot(1, 0, track[1].FXDryVolume_graph, track[1].FXDryVolume_graph, trackNames_short[8], trackColor[1]);
    drawPot(2, 0, track[2].FXDryVolume_graph, track[2].FXDryVolume_graph, trackNames_short[8], trackColor[2]);
    drawPot(3, 0, track[3].FXDryVolume_graph, track[3].FXDryVolume_graph, trackNames_short[8], trackColor[3]);

    drawPot(0, 1, track[0].FX1Volume_graph, track[0].FX1Volume_graph, trackNames_short[8], trackColor[0]);
    drawPot(1, 1, track[1].FX1Volume_graph, track[1].FX1Volume_graph, trackNames_short[8], trackColor[1]);
    drawPot(2, 1, track[2].FX1Volume_graph, track[2].FX1Volume_graph, trackNames_short[8], trackColor[2]);
    drawPot(3, 1, track[3].FX1Volume_graph, track[3].FX1Volume_graph, trackNames_short[8], trackColor[3]);

    drawPot(0, 2, track[0].FX2Volume_graph, track[0].FX2Volume_graph, trackNames_short[8], trackColor[0]);
    drawPot(1, 2, track[1].FX2Volume_graph, track[1].FX2Volume_graph, trackNames_short[8], trackColor[1]);
    drawPot(2, 2, track[2].FX2Volume_graph, track[2].FX2Volume_graph, trackNames_short[8], trackColor[2]);
    drawPot(3, 2, track[3].FX2Volume_graph, track[3].FX2Volume_graph, trackNames_short[8], trackColor[3]);

    drawPot(0, 3, track[0].FX3Volume_graph, track[0].FX3Volume_graph, trackNames_short[0], trackColor[0]);
    drawPot(1, 3, track[1].FX3Volume_graph, track[1].FX3Volume_graph, trackNames_short[1], trackColor[1]);
    drawPot(2, 3, track[2].FX3Volume_graph, track[2].FX3Volume_graph, trackNames_short[2], trackColor[2]);
    drawPot(3, 3, track[3].FX3Volume_graph, track[3].FX3Volume_graph, trackNames_short[3], trackColor[3]);
  }
  void MixerPage2_Dynamic() {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          if (enc_moved[MixerColumn]) {
            track[MixerColumn].FXDryVolume_graph = constrain((track[MixerColumn].FXDryVolume_graph + encoded[MixerColumn]), 0, 127);
            track[MixerColumn].FXDryVolume = track[MixerColumn].FXDryVolume_graph / 127.00;
            dryVolume[track[MixerColumn].MIDIchannel - 17]->gain(track[MixerColumn].FXDryVolume);
            drawPot(MixerColumn, lastPotRow, track[MixerColumn].FXDryVolume_graph, track[MixerColumn].FXDryVolume_graph, trackNames_short[8], trackColor[MixerColumn]);
          }
          /*if (abs(Potentiometer[MixerColumn] - track[MixerColumn].FXDryVolume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (track[MixerColumn].FXDryVolume_graph != Potentiometer[MixerColumn]) {
            drawPot(MixerColumn, lastPotRow, track[MixerColumn].FXDryVolume_graph, track[MixerColumn].FXDryVolume_graph, trackNames_short[8], trackColor[MixerColumn]);
            track[MixerColumn].FXDryVolume_graph = Potentiometer[MixerColumn];
            track[MixerColumn].FXDryVolume = track[MixerColumn].FXDryVolume_graph / 127.00;
            FXDrypluginVolume(track[MixerColumn].MIDIchannel, track[MixerColumn].FXDryVolume);
          }
        }*/
        }

        break;
      case 1:

        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {


          if (enc_moved[MixerColumn]) {
            track[MixerColumn].FX1Volume_graph = constrain((track[MixerColumn].FX1Volume_graph + encoded[MixerColumn]), 0, 127);
            track[MixerColumn].FX1Volume = track[MixerColumn].FX1Volume_graph / 127.00;
            FX1Volume[track[MixerColumn].MIDIchannel - 17]->gain(track[MixerColumn].FX1Volume);
            drawPot(MixerColumn, lastPotRow, track[MixerColumn].FX1Volume_graph, track[MixerColumn].FX1Volume_graph, trackNames_short[8], trackColor[MixerColumn]);
          }
          /*if (abs(Potentiometer[MixerColumn] - track[MixerColumn].FX1Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (track[MixerColumn].FX1Volume_graph != Potentiometer[MixerColumn]) {
            drawPot(MixerColumn, lastPotRow, track[MixerColumn].FX1Volume_graph, track[MixerColumn].FX1Volume_graph, trackNames_short[8], trackColor[MixerColumn]);
            track[MixerColumn].FX1Volume_graph = Potentiometer[MixerColumn];
            track[MixerColumn].FX1Volume = track[MixerColumn].FX1Volume_graph / 127.00;
            FX1pluginVolume(track[MixerColumn].MIDIchannel, track[MixerColumn].FX1Volume);
          }
        }*/
        }

        break;
      case 2:

        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          if (enc_moved[MixerColumn]) {
            track[MixerColumn].FX2Volume_graph = constrain((track[MixerColumn].FX2Volume_graph + encoded[MixerColumn]), 0, 127);
            track[MixerColumn].FX2Volume = track[MixerColumn].FX2Volume_graph / 127.00;
            FX2Volume[track[MixerColumn].MIDIchannel - 17]->gain(track[MixerColumn].FX2Volume);
            drawPot(MixerColumn, lastPotRow, track[MixerColumn].FX2Volume_graph, track[MixerColumn].FX2Volume_graph, trackNames_short[8], trackColor[MixerColumn]);
          }

          /* if (abs(Potentiometer[MixerColumn] - track[MixerColumn].FX2Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (track[MixerColumn].FX2Volume_graph != Potentiometer[MixerColumn]) {
            drawPot(MixerColumn, lastPotRow, track[MixerColumn].FX2Volume_graph, track[MixerColumn].FX2Volume_graph, trackNames_short[8], trackColor[MixerColumn]);
            track[MixerColumn].FX2Volume_graph = Potentiometer[MixerColumn];
            track[MixerColumn].FX2Volume = track[MixerColumn].FX2Volume_graph / 127.00;
            FX2pluginVolume(track[MixerColumn].MIDIchannel, track[MixerColumn].FX2Volume);
          }
        }*/
        }

        break;
      case 3:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          if (enc_moved[MixerColumn]) {
            track[MixerColumn].FX3Volume_graph = constrain((track[MixerColumn].FX3Volume_graph + encoded[MixerColumn]), 0, 127);
            track[MixerColumn].FX3Volume = track[MixerColumn].FX3Volume_graph / 127.00;
            FX3Volume[track[MixerColumn].MIDIchannel - 17]->gain(track[MixerColumn].FX3Volume);
            drawPot(MixerColumn, lastPotRow, track[MixerColumn].FX3Volume_graph, track[MixerColumn].FX3Volume_graph, trackNames_short[8], trackColor[MixerColumn]);
          }

          /* if (abs(Potentiometer[MixerColumn] - track[MixerColumn].FX3Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (track[MixerColumn].FX3Volume_graph != Potentiometer[MixerColumn]) {
            drawPot(MixerColumn, lastPotRow, track[MixerColumn].FX3Volume_graph, track[MixerColumn].FX3Volume_graph, trackNames_short[8], trackColor[MixerColumn]);
            track[MixerColumn].FX3Volume_graph = Potentiometer[MixerColumn];
            track[MixerColumn].FX3Volume = track[MixerColumn].FX3Volume_graph / 127.00;
            FX3pluginVolume(track[MixerColumn].MIDIchannel, track[MixerColumn].FX3Volume);
          }
        }*/
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

    drawPot(0, 0, track[4].FXDryVolume_graph, track[4].FXDryVolume_graph, trackNames_short[8], trackColor[4]);
    drawPot(1, 0, track[5].FXDryVolume_graph, track[5].FXDryVolume_graph, trackNames_short[8], trackColor[5]);
    drawPot(2, 0, track[6].FXDryVolume_graph, track[6].FXDryVolume_graph, trackNames_short[8], trackColor[6]);
    drawPot(3, 0, track[7].FXDryVolume_graph, track[7].FXDryVolume_graph, trackNames_short[8], trackColor[7]);

    drawPot(0, 1, track[4].FX1Volume_graph, track[4].FX1Volume_graph, trackNames_short[8], trackColor[4]);
    drawPot(1, 1, track[5].FX1Volume_graph, track[5].FX1Volume_graph, trackNames_short[8], trackColor[5]);
    drawPot(2, 1, track[6].FX1Volume_graph, track[6].FX1Volume_graph, trackNames_short[8], trackColor[6]);
    drawPot(3, 1, track[7].FX1Volume_graph, track[7].FX1Volume_graph, trackNames_short[8], trackColor[7]);

    drawPot(0, 2, track[4].FX2Volume_graph, track[4].FX2Volume_graph, trackNames_short[8], trackColor[4]);
    drawPot(1, 2, track[5].FX2Volume_graph, track[5].FX2Volume_graph, trackNames_short[8], trackColor[5]);
    drawPot(2, 2, track[6].FX2Volume_graph, track[6].FX2Volume_graph, trackNames_short[8], trackColor[6]);
    drawPot(3, 2, track[7].FX2Volume_graph, track[7].FX2Volume_graph, trackNames_short[8], trackColor[7]);

    drawPot(0, 3, track[4].FX3Volume_graph, track[4].FX3Volume_graph, trackNames_short[4], trackColor[4]);
    drawPot(1, 3, track[5].FX3Volume_graph, track[5].FX3Volume_graph, trackNames_short[5], trackColor[5]);
    drawPot(2, 3, track[6].FX3Volume_graph, track[6].FX3Volume_graph, trackNames_short[6], trackColor[6]);
    drawPot(3, 3, track[7].FX3Volume_graph, track[7].FX3Volume_graph, trackNames_short[7], trackColor[7]);
  }
  void MixerPage3_Dynamic() {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {


          if (enc_moved[MixerColumn]) {
            track[MixerColumn + 4].FXDryVolume_graph = constrain((track[MixerColumn + 4].FXDryVolume_graph + encoded[MixerColumn]), 0, 127);
            track[MixerColumn + 4].FXDryVolume = track[MixerColumn + 4].FXDryVolume_graph / 127.00;
            dryVolume[track[MixerColumn + 4].MIDIchannel - 17]->gain(track[MixerColumn + 4].FXDryVolume);
            drawPot(MixerColumn, lastPotRow, track[MixerColumn + 4].FXDryVolume_graph, track[MixerColumn + 4].FXDryVolume_graph, trackNames_short[8], trackColor[MixerColumn + 4]);
          }
        }

        break;
      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          if (enc_moved[MixerColumn]) {
            track[MixerColumn + 4].FX1Volume_graph = constrain((track[MixerColumn + 4].FX1Volume_graph + encoded[MixerColumn]), 0, 127);
            track[MixerColumn + 4].FX1Volume = track[MixerColumn + 4].FX1Volume_graph / 127.00;
            FX1Volume[track[MixerColumn + 4].MIDIchannel - 17]->gain(track[MixerColumn + 4].FX1Volume);
            drawPot(MixerColumn, lastPotRow, track[MixerColumn + 4].FX1Volume_graph, track[MixerColumn + 4].FX1Volume_graph, trackNames_short[8], trackColor[MixerColumn + 4]);
          }
        }
        break;
      case 2:

        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          if (enc_moved[MixerColumn]) {
            track[MixerColumn + 4].FX2Volume_graph = constrain((track[MixerColumn + 4].FX2Volume_graph + encoded[MixerColumn]), 0, 127);
            track[MixerColumn + 4].FX2Volume = track[MixerColumn + 4].FX2Volume_graph / 127.00;
            FX2Volume[track[MixerColumn + 4].MIDIchannel - 17]->gain(track[MixerColumn + 4].FX2Volume);
            drawPot(MixerColumn, lastPotRow, track[MixerColumn + 4].FX2Volume_graph, track[MixerColumn + 4].FX2Volume_graph, trackNames_short[8], trackColor[MixerColumn + 4]);
          }
          /*if (abs(Potentiometer[MixerColumn] - track[MixerColumn + 4].FX2Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (track[MixerColumn + 4].FX2Volume_graph != Potentiometer[MixerColumn]) {
            drawPot(MixerColumn, lastPotRow, track[MixerColumn + 4].FX2Volume_graph, track[MixerColumn + 4].FX2Volume_graph, trackNames_short[8], trackColor[MixerColumn + 4]);
            track[MixerColumn + 4].FX2Volume_graph = Potentiometer[MixerColumn];
            track[MixerColumn + 4].FX2Volume = track[MixerColumn + 4].FX2Volume_graph / 127.00;
            FX2pluginVolume(track[MixerColumn + 4].MIDIchannel, track[MixerColumn + 4].FX2Volume);
          }
        }*/
        }
        // }
        break;
      case 3:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          if (enc_moved[MixerColumn]) {
            track[MixerColumn + 4].FX3Volume_graph = constrain((track[MixerColumn + 4].FX3Volume_graph + encoded[MixerColumn]), 0, 127);
            track[MixerColumn + 4].FX3Volume = track[MixerColumn + 4].FX3Volume_graph / 127.00;
            FX3Volume[track[MixerColumn + 4].MIDIchannel - 17]->gain(track[MixerColumn + 4].FX3Volume);
            drawPot(MixerColumn, lastPotRow, track[MixerColumn + 4].FX3Volume_graph, track[MixerColumn + 4].FX3Volume_graph, trackNames_short[8], trackColor[MixerColumn + 4]);
          }
          /*if (abs(Potentiometer[MixerColumn] - track[MixerColumn + 4].FX3Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (track[MixerColumn + 4].FX3Volume_graph != Potentiometer[MixerColumn]) {
            drawPot(MixerColumn, CTRL_ROW_3, track[MixerColumn + 4].FX3Volume_graph, track[MixerColumn + 4].FX3Volume_graph, trackNames_short[8], trackColor[MixerColumn + 4]);
            track[MixerColumn + 4].FX3Volume_graph = Potentiometer[MixerColumn];
            track[MixerColumn + 4].FX3Volume = track[MixerColumn + 4].FX3Volume_graph / 127.00;
            FX3pluginVolume(track[MixerColumn + 4].MIDIchannel, track[MixerColumn + 4].FX3Volume);
          }
        }*/
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

  void pluginGain(int pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
    for (int pluginn = 0; pluginn < 16; pluginn++) {
      if (pluginchannel == pluginn + 17) {
        gainmax[pluginn]->gain(volume);
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
        myFile.print((char)track[MixerColumn].gain_graph);
        myFile.print((char)track[MixerColumn + 4].gain_graph);
        myFile.print((char)track[MixerColumn].FXDryVolume_graph);
        myFile.print((char)track[MixerColumn + 4].FXDryVolume_graph);
        myFile.print((char)track[MixerColumn].FX1Volume_graph);
        myFile.print((char)track[MixerColumn + 4].FX1Volume_graph);
        myFile.print((char)track[MixerColumn].FX2Volume_graph);
        myFile.print((char)track[MixerColumn + 4].FX2Volume_graph);
        myFile.print((char)track[MixerColumn].FX3Volume_graph);
        myFile.print((char)track[MixerColumn + 4].FX3Volume_graph);
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
        track[MixerColumn].gain_graph = myFile.read();
        track[MixerColumn + 4].gain_graph = myFile.read();
        track[MixerColumn].FXDryVolume_graph = myFile.read();
        track[MixerColumn + 4].FXDryVolume_graph = myFile.read();
        track[MixerColumn].FX1Volume_graph = myFile.read();
        track[MixerColumn + 4].FX1Volume_graph = myFile.read();
        track[MixerColumn].FX2Volume_graph = myFile.read();
        track[MixerColumn + 4].FX2Volume_graph = myFile.read();
        track[MixerColumn].FX3Volume_graph = myFile.read();
        track[MixerColumn + 4].FX3Volume_graph = myFile.read();
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