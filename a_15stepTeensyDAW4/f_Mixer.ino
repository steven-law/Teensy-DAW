void selectSolo(byte tracknumber) {

  if (!track[tracknumber].solo_state) {
    for (byte others = 0; others <= 7; others++) {
      track[others].solo_mutes_state = HIGH;
    }
    track[tracknumber].solo_mutes_state = LOW;
    track[tracknumber].solo_state = HIGH;
  } else if (track[tracknumber].solo_state) {
    for (byte others = 0; others <= 7; others++) {
      track[others].solo_mutes_state = LOW;
    }
    track[tracknumber].solo_mutes_state = LOW;
    track[tracknumber].solo_state = LOW;
  }
}
void selectMute(byte tracknumber) {
  if (!track[tracknumber].mute_state) {
    track[tracknumber].mute_state = HIGH;
  } else if (track[tracknumber].mute_state) {
    track[tracknumber].mute_state = LOW;
  }
}


void Mixer_Settings() {
  sgtl5000_1.enable();
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

  //mixer8 for plugins 1-16
  mixer8.gain(0, 1);
  mixer8.gain(1, 1);
  mixer8.gain(2, 1);
  mixer8.gain(3, 1);

  //mixer9 for sum of dry and fx
  mixer9.gain(0, 1);
  mixer9.gain(1, 1);
  mixer9.gain(2, 1);
  mixer9.gain(3, 1);

  //mixer8 for plugins 9-12
  mixer10.gain(0, 1);
  mixer10.gain(1, 1);
  mixer10.gain(2, 1);
  mixer10.gain(3, 1);



  //mixer1 for FX3
  FX3mixer1.gain(0, 0);
  FX3mixer1.gain(1, 0);
  FX3mixer1.gain(2, 0);
  FX3mixer1.gain(3, 0);
  //mixer2 for FX3
  FX3mixer2.gain(0, 0);
  FX3mixer2.gain(1, 0);
  FX3mixer2.gain(2, 0);
  FX3mixer2.gain(3, 0);
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
}

void mixerPage1_Static(byte mixerpage) {
  clearWorkSpace();
  drawActiveRect(18, 3, 2, 2, true, "Main", ILI9341_LIGHTGREY);
  drawActiveRect(18, 5, 2, 2, false, "D-4", ILI9341_LIGHTGREY);
  drawActiveRect(18, 7, 2, 2, false, "5-8", ILI9341_LIGHTGREY);



  drawPot(CTRL_COL_0, 3, track[0].velocity_ON_graph, track[0].velocity_ON, "TrD", trackColor[0]);
  drawActiveRect(3, 5, 1, 1, track[0].mute_state, "M", ILI9341_RED);
  drawActiveRect(4, 5, 1, 1, track[0].solo_state, "S", ILI9341_WHITE);
  drawPot(CTRL_COL_1, 3, track[1].velocity_ON_graph, track[1].velocity_ON, "Tr2", trackColor[1]);
  drawActiveRect(7, 5, 1, 1, track[1].mute_state, "M", ILI9341_RED);
  drawActiveRect(8, 5, 1, 1, track[1].solo_state, "S", ILI9341_WHITE);
  drawPot(CTRL_COL_2, 3, track[2].velocity_ON_graph, track[2].velocity_ON, "Tr3", trackColor[2]);
  drawActiveRect(11, 5, 1, 1, track[2].mute_state, "M", ILI9341_RED);
  drawActiveRect(12, 5, 1, 1, track[2].solo_state, "S", ILI9341_WHITE);
  drawPot(CTRL_COL_3, 3, track[3].velocity_ON_graph, track[3].velocity_ON, "Tr4", trackColor[3]);
  drawActiveRect(15, 5, 1, 1, track[3].mute_state, "M", ILI9341_RED);
  drawActiveRect(16, 5, 1, 1, track[3].solo_state, "S", ILI9341_WHITE);

  drawPot(CTRL_COL_0, 9, track[4].velocity_ON_graph, track[4].velocity_ON, "Tr5", trackColor[4]);
  drawActiveRect(3, 11, 1, 1, track[4].mute_state, "M", ILI9341_RED);
  drawActiveRect(4, 11, 1, 1, track[4].solo_state, "S", ILI9341_WHITE);
  drawPot(CTRL_COL_1, 9, track[5].velocity_ON_graph, track[5].velocity_ON, "Tr6", trackColor[5]);
  drawActiveRect(7, 11, 1, 1, track[5].mute_state, "M", ILI9341_RED);
  drawActiveRect(8, 11, 1, 1, track[5].solo_state, "S", ILI9341_WHITE);
  drawPot(CTRL_COL_2, 9, track[6].velocity_ON_graph, track[6].velocity_ON, "Tr7", trackColor[6]);
  drawActiveRect(11, 11, 1, 1, track[6].mute_state, "M", ILI9341_RED);
  drawActiveRect(12, 11, 1, 1, track[6].solo_state, "S", ILI9341_WHITE);
  drawPot(CTRL_COL_3, 9, track[7].velocity_ON_graph, track[7].velocity_ON, "Tr8", trackColor[7]);
  drawActiveRect(15, 11, 1, 1, track[7].mute_state, "M", ILI9341_RED);
  drawActiveRect(16, 11, 1, 1, track[7].solo_state, "S", ILI9341_WHITE);
  drawPot(18, 12, MasterVol_graph, MasterVol_graph, "OUT", ILI9341_BLACK);
}
void MixerPage1_Dynamic() {
  switch (lastPotRow) {
    case 0:
      if (msecs % 11 == 0) {
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          if (abs(Potentiometer[MixerColumn] - track[MixerColumn].velocity_ON_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[MixerColumn].velocity_ON_graph != Potentiometer[MixerColumn]) {
              track[MixerColumn].velocity_ON_graph = Potentiometer[MixerColumn];
              track[MixerColumn].velocity_ON = track[MixerColumn].velocity_ON_graph;
              drawPot(MixerColumnPos, 3, track[MixerColumn].velocity_ON_graph, track[MixerColumn].velocity_ON, trackNames_short[MixerColumn], trackColor[MixerColumn]);
            }

            if (track[MixerColumn].MIDIchannel > 16) {
              plugin[track[MixerColumn].MIDIchannel - 16].Volume_graph = Potentiometer[MixerColumn];
              plugin[track[MixerColumn].MIDIchannel - 16].Volume = plugin[track[MixerColumn].MIDIchannel - 16].Volume_graph / 127.00;
              pluginVolume(track[MixerColumn].MIDIchannel, plugin[track[MixerColumn].MIDIchannel - 16].Volume);
            }
          }
        }
      }
      break;
    case 1:
      if (msecs % 11 == 0) {
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          if (abs(Potentiometer[MixerColumn] - track[MixerColumn + 4].velocity_ON_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[MixerColumn + 4].velocity_ON_graph != Potentiometer[MixerColumn]) {
              track[MixerColumn + 4].velocity_ON_graph = Potentiometer[MixerColumn];
              track[MixerColumn + 4].velocity_ON = track[MixerColumn + 4].velocity_ON_graph;
              drawPot(MixerColumnPos, 9, track[MixerColumn + 4].velocity_ON_graph, track[MixerColumn + 4].velocity_ON, trackNames_short[MixerColumn + 4], trackColor[MixerColumn + 4]);
            }

            if (track[MixerColumn + 4].MIDIchannel > 16) {
              plugin[track[MixerColumn + 4].MIDIchannel - 16].Volume_graph = Potentiometer[MixerColumn];
              plugin[track[MixerColumn + 4].MIDIchannel - 16].Volume = plugin[track[MixerColumn + 4].MIDIchannel - 16].Volume_graph / 127.00;
              pluginVolume(track[MixerColumn + 4].MIDIchannel, plugin[track[MixerColumn + 4].MIDIchannel - 16].Volume);
            }
          }
        }
      }
      break;
    case 2:
      if (abs(Potentiometer[3] - MasterVol_graph) < POTPICKUP) {
        if (MasterVol_graph != Potentiometer[3]) {
          MasterVol_graph = Potentiometer[3];
          MasterVol = MasterVol_graph / 127.00;
          sgtl5000_1.volume(MasterVol);
          drawPot(18, 12, MasterVol_graph, MasterVol_graph, "OUT", ILI9341_BLACK);
        }
      }
      break;
  }
  if (ts.touched() || enter_button) {

    if (gridTouchY >= 2 && gridTouchY <= 4) {
      lastPotRow = 0;
    }

    if (gridTouchY >= 5 && gridTouchY <= 7) {
      lastPotRow = 1;
    }

    if (gridTouchX >= 18 || gridTouchY >= 12) {
      lastPotRow = 2;
    }
    //if (gridTouchY >= 11 && gridTouchY <= 13) {
    //lastPotRow = 3;
    //}



    //mute and solo states track 1-4
    //for better behaviour here we wait for "interval, unless it would switch within micrseconds
    if (gridTouchY == 5) {
      unsigned long currentMillis = msecs;
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        for (byte mutes = 0; mutes < 4; mutes++) {
          if (gridTouchX == (((mutes + 1) * 4) - 1)) {
            selectMute(mutes);
            drawActiveRect((((mutes + 1) * 4) - 1), 5, 1, 1, track[mutes].mute_state, "M", ILI9341_RED);
          }
        }
        for (byte solos = 0; solos < 4; solos++) {
          if (gridTouchX == (solos + 1) * 4) {
            selectSolo(solos);
            drawActiveRect((solos + 1) * 4, 5, 1, 1, track[solos].solo_state, "S", ILI9341_WHITE);
          }
        }
      }
    }
    //mute and solo states Track 5-8
    //for better behaviour here we wait for "interval, unless it would switch within micrseconds
    if (gridTouchY == 11) {
      unsigned long currentMillis = msecs;
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        for (byte mutes = 0; mutes < 4; mutes++) {
          if (gridTouchX == (((mutes + 1) * 4) - 1)) {
            selectMute(mutes + 4);
            drawActiveRect((((mutes + 1) * 4) - 1), 11, 1, 1, track[mutes + 4].mute_state, "M", ILI9341_RED);
          }
        }
        for (byte solos = 0; solos < 4; solos++) {
          if (gridTouchX == (solos + 1) * 4) {
            selectSolo(solos + 4);
            drawActiveRect((solos + 1) * 4, 11, 1, 1, track[solos + 4].solo_state, "S", ILI9341_WHITE);
          }
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



void mixerPage2_Static() {
  clearWorkSpace();
  //draw_sub_page_buttons(2);
  drawActiveRect(18, 3, 2, 2, false, "Main", ILI9341_LIGHTGREY);
  drawActiveRect(18, 5, 2, 2, true, "D-4", ILI9341_LIGHTGREY);
  drawActiveRect(18, 7, 2, 2, false, "5-8", ILI9341_LIGHTGREY);

  drawActiveRect(1, 5, 2, 2, false, "Rvrb", ILI9341_YELLOW);
  drawActiveRect(1, 8, 2, 2, false, "BitC", ILI9341_LIGHTGREY);
  drawActiveRect(1, 11, 2, 2, false, "Dly", ILI9341_LIGHTGREY);

  drawPot(CTRL_COL_0, CTRL_ROW_0, plugin[track[0].MIDIchannel - 16].FXDryVolume_graph, plugin[track[0].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[0]);
  drawPot(CTRL_COL_1, CTRL_ROW_0, plugin[track[1].MIDIchannel - 16].FXDryVolume_graph, plugin[track[1].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[1]);
  drawPot(CTRL_COL_2, CTRL_ROW_0, plugin[track[2].MIDIchannel - 16].FXDryVolume_graph, plugin[track[2].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[2]);
  drawPot(CTRL_COL_3, CTRL_ROW_0, plugin[track[3].MIDIchannel - 16].FXDryVolume_graph, plugin[track[3].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[3]);

  drawPot(CTRL_COL_0, CTRL_ROW_1, plugin[track[0].MIDIchannel - 16].FX1Volume_graph, plugin[track[0].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[0]);
  drawPot(CTRL_COL_1, CTRL_ROW_1, plugin[track[1].MIDIchannel - 16].FX1Volume_graph, plugin[track[1].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[1]);
  drawPot(CTRL_COL_2, CTRL_ROW_1, plugin[track[2].MIDIchannel - 16].FX1Volume_graph, plugin[track[2].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[2]);
  drawPot(CTRL_COL_3, CTRL_ROW_1, plugin[track[3].MIDIchannel - 16].FX1Volume_graph, plugin[track[3].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[3]);

  drawPot(CTRL_COL_0, CTRL_ROW_2, plugin[track[0].MIDIchannel - 16].FX2Volume_graph, plugin[track[0].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[0]);
  drawPot(CTRL_COL_1, CTRL_ROW_2, plugin[track[1].MIDIchannel - 16].FX2Volume_graph, plugin[track[1].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[1]);
  drawPot(CTRL_COL_2, CTRL_ROW_2, plugin[track[2].MIDIchannel - 16].FX2Volume_graph, plugin[track[2].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[2]);
  drawPot(CTRL_COL_3, CTRL_ROW_2, plugin[track[3].MIDIchannel - 16].FX2Volume_graph, plugin[track[3].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[3]);

  drawPot(CTRL_COL_0, CTRL_ROW_3, plugin[track[0].MIDIchannel - 16].FX3Volume_graph, plugin[track[0].MIDIchannel - 16].FX3Volume_graph, trackNames_short[0], trackColor[0]);
  drawPot(CTRL_COL_1, CTRL_ROW_3, plugin[track[1].MIDIchannel - 16].FX3Volume_graph, plugin[track[1].MIDIchannel - 16].FX3Volume_graph, trackNames_short[1], trackColor[1]);
  drawPot(CTRL_COL_2, CTRL_ROW_3, plugin[track[2].MIDIchannel - 16].FX3Volume_graph, plugin[track[2].MIDIchannel - 16].FX3Volume_graph, trackNames_short[2], trackColor[2]);
  drawPot(CTRL_COL_3, CTRL_ROW_3, plugin[track[3].MIDIchannel - 16].FX3Volume_graph, plugin[track[3].MIDIchannel - 16].FX3Volume_graph, trackNames_short[3], trackColor[3]);
}
void MixerPage2_Dynamic() {
  switch (lastPotRow) {
    case 0:
      if (msecs % 11 == 0) {
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          if (abs(Potentiometer[MixerColumn] - plugin[track[MixerColumn].MIDIchannel - 16].FXDryVolume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (plugin[track[MixerColumn].MIDIchannel - 16].FXDryVolume_graph != Potentiometer[MixerColumn]) {
              drawPot(MixerColumnPos, CTRL_ROW_0, plugin[track[MixerColumn].MIDIchannel - 16].FXDryVolume_graph, plugin[track[MixerColumn].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[MixerColumn]);
              plugin[track[MixerColumn].MIDIchannel - 16].FXDryVolume_graph = Potentiometer[MixerColumn];
              plugin[track[MixerColumn].MIDIchannel - 16].FXDryVolume = plugin[track[MixerColumn].MIDIchannel - 16].FXDryVolume_graph / 127.00;
              FXDrypluginVolume(track[MixerColumn].MIDIchannel, plugin[track[MixerColumn].MIDIchannel - 16].FXDryVolume);
            }
          }
        }
      }
      break;
    case 1:
      if (msecs % 11 == 0) {
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          if (abs(Potentiometer[MixerColumn] - plugin[track[MixerColumn].MIDIchannel - 16].FX1Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (plugin[track[MixerColumn].MIDIchannel - 16].FX1Volume_graph != Potentiometer[MixerColumn]) {
              drawPot(MixerColumnPos, CTRL_ROW_1, plugin[track[MixerColumn].MIDIchannel - 16].FX1Volume_graph, plugin[track[MixerColumn].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[MixerColumn]);
              plugin[track[MixerColumn].MIDIchannel - 16].FX1Volume_graph = Potentiometer[MixerColumn];
              plugin[track[MixerColumn].MIDIchannel - 16].FX1Volume = plugin[track[MixerColumn].MIDIchannel - 16].FX1Volume_graph / 127.00;
              FX1pluginVolume(track[MixerColumn].MIDIchannel, plugin[track[MixerColumn].MIDIchannel - 16].FX1Volume);
            }
          }
        }
      }
      break;
    case 2:
      if (msecs % 11 == 0) {
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          if (abs(Potentiometer[MixerColumn] - plugin[track[MixerColumn].MIDIchannel - 16].FX2Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (plugin[track[MixerColumn].MIDIchannel - 16].FX2Volume_graph != Potentiometer[MixerColumn]) {
              drawPot(MixerColumnPos, CTRL_ROW_2, plugin[track[MixerColumn].MIDIchannel - 16].FX2Volume_graph, plugin[track[MixerColumn].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[MixerColumn]);
              plugin[track[MixerColumn].MIDIchannel - 16].FX2Volume_graph = Potentiometer[MixerColumn];
              plugin[track[MixerColumn].MIDIchannel - 16].FX2Volume = plugin[track[MixerColumn].MIDIchannel - 16].FX2Volume_graph / 127.00;
              FX2pluginVolume(track[MixerColumn].MIDIchannel, plugin[track[MixerColumn].MIDIchannel - 16].FX2Volume);
            }
          }
        }
      }
      break;
    case 3:
      if (msecs % 11 == 0) {
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          if (abs(Potentiometer[MixerColumn] - plugin[track[MixerColumn].MIDIchannel - 16].FX3Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (plugin[track[MixerColumn].MIDIchannel - 16].FX3Volume_graph != Potentiometer[MixerColumn]) {
              drawPot(MixerColumnPos, CTRL_ROW_3, plugin[track[MixerColumn].MIDIchannel - 16].FX3Volume_graph, plugin[track[MixerColumn].MIDIchannel - 16].FX3Volume_graph, trackNames_short[8], trackColor[MixerColumn]);
              plugin[track[MixerColumn].MIDIchannel - 16].FX3Volume_graph = Potentiometer[MixerColumn];
              plugin[track[MixerColumn].MIDIchannel - 16].FX3Volume = plugin[track[MixerColumn].MIDIchannel - 16].FX3Volume_graph / 127.00;
              FX3pluginVolume(track[MixerColumn].MIDIchannel, plugin[track[MixerColumn].MIDIchannel - 16].FX3Volume);
            }
          }
        }
      }
      break;
  }
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

  drawPot(CTRL_COL_0, CTRL_ROW_0, plugin[track[4].MIDIchannel - 16].FXDryVolume_graph, plugin[track[4].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[4]);
  drawPot(CTRL_COL_1, CTRL_ROW_0, plugin[track[5].MIDIchannel - 16].FXDryVolume_graph, plugin[track[5].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[5]);
  drawPot(CTRL_COL_2, CTRL_ROW_0, plugin[track[6].MIDIchannel - 16].FXDryVolume_graph, plugin[track[6].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[6]);
  drawPot(CTRL_COL_3, CTRL_ROW_0, plugin[track[7].MIDIchannel - 16].FXDryVolume_graph, plugin[track[7].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[7]);

  drawPot(CTRL_COL_0, CTRL_ROW_1, plugin[track[4].MIDIchannel - 16].FX1Volume_graph, plugin[track[4].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[4]);
  drawPot(CTRL_COL_1, CTRL_ROW_1, plugin[track[5].MIDIchannel - 16].FX1Volume_graph, plugin[track[5].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[5]);
  drawPot(CTRL_COL_2, CTRL_ROW_1, plugin[track[6].MIDIchannel - 16].FX1Volume_graph, plugin[track[6].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[6]);
  drawPot(CTRL_COL_3, CTRL_ROW_1, plugin[track[7].MIDIchannel - 16].FX1Volume_graph, plugin[track[7].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[7]);

  drawPot(CTRL_COL_0, CTRL_ROW_2, plugin[track[4].MIDIchannel - 16].FX2Volume_graph, plugin[track[4].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[4]);
  drawPot(CTRL_COL_1, CTRL_ROW_2, plugin[track[5].MIDIchannel - 16].FX2Volume_graph, plugin[track[5].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[5]);
  drawPot(CTRL_COL_2, CTRL_ROW_2, plugin[track[6].MIDIchannel - 16].FX2Volume_graph, plugin[track[6].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[6]);
  drawPot(CTRL_COL_3, CTRL_ROW_2, plugin[track[7].MIDIchannel - 16].FX2Volume_graph, plugin[track[7].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[7]);

  drawPot(CTRL_COL_0, CTRL_ROW_3, plugin[track[4].MIDIchannel - 16].FX3Volume_graph, plugin[track[4].MIDIchannel - 16].FX3Volume_graph, trackNames_short[4], trackColor[4]);
  drawPot(CTRL_COL_1, CTRL_ROW_3, plugin[track[5].MIDIchannel - 16].FX3Volume_graph, plugin[track[5].MIDIchannel - 16].FX3Volume_graph, trackNames_short[5], trackColor[5]);
  drawPot(CTRL_COL_2, CTRL_ROW_3, plugin[track[6].MIDIchannel - 16].FX3Volume_graph, plugin[track[6].MIDIchannel - 16].FX3Volume_graph, trackNames_short[6], trackColor[6]);
  drawPot(CTRL_COL_3, CTRL_ROW_3, plugin[track[7].MIDIchannel - 16].FX3Volume_graph, plugin[track[7].MIDIchannel - 16].FX3Volume_graph, trackNames_short[7], trackColor[7]);
}
void MixerPage3_Dynamic() {
  switch (lastPotRow) {
    case 0:
      if (msecs % 11 == 0) {
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          if (abs(Potentiometer[MixerColumn] - plugin[track[MixerColumn + 4].MIDIchannel - 16].FXDryVolume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (plugin[track[MixerColumn + 4].MIDIchannel - 16].FXDryVolume_graph != Potentiometer[MixerColumn]) {
              drawPot(MixerColumnPos, CTRL_ROW_0, plugin[track[MixerColumn + 4].MIDIchannel - 16].FXDryVolume_graph, plugin[track[MixerColumn + 4].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[MixerColumn + 4]);
              plugin[track[MixerColumn + 4].MIDIchannel - 16].FXDryVolume_graph = Potentiometer[MixerColumn];
              plugin[track[MixerColumn + 4].MIDIchannel - 16].FXDryVolume = plugin[track[MixerColumn + 4].MIDIchannel - 16].FXDryVolume_graph / 127.44;
              FXDrypluginVolume(track[MixerColumn + 4].MIDIchannel, plugin[track[MixerColumn + 4].MIDIchannel - 16].FXDryVolume);
            }
          }
        }
      }
      break;
    case 1:
      if (msecs % 11 == 0) {
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          if (abs(Potentiometer[MixerColumn] - plugin[track[MixerColumn + 4].MIDIchannel - 16].FX1Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (plugin[track[MixerColumn + 4].MIDIchannel - 16].FX1Volume_graph != Potentiometer[MixerColumn]) {
              drawPot(MixerColumnPos, CTRL_ROW_1, plugin[track[MixerColumn + 4].MIDIchannel - 16].FX1Volume_graph, plugin[track[MixerColumn + 4].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[MixerColumn + 4]);
              plugin[track[MixerColumn + 4].MIDIchannel - 16].FX1Volume_graph = Potentiometer[MixerColumn];
              plugin[track[MixerColumn + 4].MIDIchannel - 16].FX1Volume = plugin[track[MixerColumn + 4].MIDIchannel - 16].FX1Volume_graph / 127.00;
              FX1pluginVolume(track[MixerColumn + 4].MIDIchannel, plugin[track[MixerColumn + 4].MIDIchannel - 16].FX1Volume);
            }
          }
        }
      }
      break;
    case 2:
      if (msecs % 11 == 0) {
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          if (abs(Potentiometer[MixerColumn] - plugin[track[MixerColumn + 4].MIDIchannel - 16].FX2Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (plugin[track[MixerColumn + 4].MIDIchannel - 16].FX2Volume_graph != Potentiometer[MixerColumn]) {
              drawPot(MixerColumnPos, CTRL_ROW_2, plugin[track[MixerColumn + 4].MIDIchannel - 16].FX2Volume_graph, plugin[track[MixerColumn + 4].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[MixerColumn + 4]);
              plugin[track[MixerColumn + 4].MIDIchannel - 16].FX2Volume_graph = Potentiometer[MixerColumn];
              plugin[track[MixerColumn + 4].MIDIchannel - 16].FX2Volume = plugin[track[MixerColumn + 4].MIDIchannel - 16].FX2Volume_graph / 127.00;
              FX2pluginVolume(track[MixerColumn + 4].MIDIchannel, plugin[track[MixerColumn + 4].MIDIchannel - 16].FX2Volume);
            }
          }
        }
      }
      break;
    case 3:
      if (msecs % 11 == 0) {
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          if (abs(Potentiometer[MixerColumn] - plugin[track[MixerColumn + 4].MIDIchannel - 16].FX3Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (plugin[track[MixerColumn + 4].MIDIchannel - 16].FX3Volume_graph != Potentiometer[MixerColumn]) {
              drawPot(MixerColumnPos, CTRL_ROW_3, plugin[track[MixerColumn + 4].MIDIchannel - 16].FX3Volume_graph, plugin[track[MixerColumn + 4].MIDIchannel - 16].FX3Volume_graph, trackNames_short[8], trackColor[MixerColumn + 4]);
              plugin[track[MixerColumn + 4].MIDIchannel - 16].FX3Volume_graph = Potentiometer[MixerColumn];
              plugin[track[MixerColumn + 4].MIDIchannel - 16].FX3Volume = plugin[track[MixerColumn + 4].MIDIchannel - 16].FX3Volume_graph / 127.00;
              FX3pluginVolume(track[MixerColumn + 4].MIDIchannel, plugin[track[MixerColumn + 4].MIDIchannel - 16].FX3Volume);
            }
          }
        }
      }
      break;
  }
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
    }
  }
}