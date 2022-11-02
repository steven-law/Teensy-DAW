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

  //mixer8 for plugins 9-12
  mixer8.gain(0, 1);
  mixer8.gain(1, 1);
  mixer8.gain(2, 1);
  mixer8.gain(3, 1);

  //mixer9 for sum of dry and fx
  mixer9.gain(0, 1);
  mixer9.gain(1, 1);
  mixer9.gain(2, 1);
  mixer9.gain(3, 1);





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
}

void mixerPage1_Static(byte mixerpage) {
  clearWorkSpace();
  drawActiveRect(18, 3, 2, 2, true, "Main", ILI9341_LIGHTGREY);
  drawActiveRect(18, 5, 2, 2, false, "D-4", ILI9341_LIGHTGREY);
  drawActiveRect(18, 7, 2, 2, false, "5-8", ILI9341_LIGHTGREY);



  drawPot(3, 3, track[0].velocity_ON_graph, track[0].velocity_ON, "TrD", trackColor[0]);
  drawActiveRect(3, 5, 1, 1, track[0].mute_state, "M", ILI9341_RED);
  drawActiveRect(4, 5, 1, 1, track[0].solo_state, "S", ILI9341_WHITE);
  drawPot(7, 3, track[1].velocity_ON_graph, track[1].velocity_ON, "Tr2", trackColor[1]);
  drawActiveRect(7, 5, 1, 1, track[1].mute_state, "M", ILI9341_RED);
  drawActiveRect(8, 5, 1, 1, track[1].solo_state, "S", ILI9341_WHITE);
  drawPot(11, 3, track[2].velocity_ON_graph, track[2].velocity_ON, "Tr3", trackColor[2]);
  drawActiveRect(11, 5, 1, 1, track[2].mute_state, "M", ILI9341_RED);
  drawActiveRect(12, 5, 1, 1, track[2].solo_state, "S", ILI9341_WHITE);
  drawPot(15, 3, track[3].velocity_ON_graph, track[3].velocity_ON, "Tr4", trackColor[3]);
  drawActiveRect(15, 5, 1, 1, track[3].mute_state, "M", ILI9341_RED);
  drawActiveRect(16, 5, 1, 1, track[3].solo_state, "S", ILI9341_WHITE);

  drawPot(3, 9, track[4].velocity_ON_graph, track[4].velocity_ON, "Tr5", trackColor[4]);
  drawActiveRect(3, 11, 1, 1, track[4].mute_state, "M", ILI9341_RED);
  drawActiveRect(4, 11, 1, 1, track[4].solo_state, "S", ILI9341_WHITE);
  drawPot(7, 9, track[5].velocity_ON_graph, track[5].velocity_ON, "Tr6", trackColor[5]);
  drawActiveRect(7, 11, 1, 1, track[5].mute_state, "M", ILI9341_RED);
  drawActiveRect(8, 11, 1, 1, track[5].solo_state, "S", ILI9341_WHITE);
  drawPot(11, 9, track[6].velocity_ON_graph, track[6].velocity_ON, "Tr7", trackColor[6]);
  drawActiveRect(11, 11, 1, 1, track[6].mute_state, "M", ILI9341_RED);
  drawActiveRect(12, 11, 1, 1, track[6].solo_state, "S", ILI9341_WHITE);
  drawPot(15, 9, track[7].velocity_ON_graph, track[7].velocity_ON, "Tr8", trackColor[7]);
  drawActiveRect(15, 11, 1, 1, track[7].mute_state, "M", ILI9341_RED);
  drawActiveRect(16, 11, 1, 1, track[7].solo_state, "S", ILI9341_WHITE);
}
void MixerPage1_Dynamic() {
  if (ts.touched() || !buttons[6].read()) {
    if (millis() % 20 > 15) {
      
      //Track D - 4
      if (gridTouchY == 3) {
        for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
          byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
          if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
            if (abs(Potentiometer1 - track[MixerRow].velocity_ON_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              track[MixerRow].velocity_ON_graph = Potentiometer1;
              track[MixerRow].velocity_ON = track[MixerRow].velocity_ON_graph;

              if (track[MixerRow].MIDIchannel > 16) {
                plugin[track[MixerRow].MIDIchannel - 16].Volume_graph = Potentiometer1;
                plugin[track[MixerRow].MIDIchannel - 16].Volume = plugin[track[MixerRow].MIDIchannel - 16].Volume_graph / 127.00;
                pluginVolume(track[MixerRow].MIDIchannel, plugin[track[MixerRow].MIDIchannel - 16].Volume);
              }
              drawPot(mixerRowPos, 3, track[MixerRow].velocity_ON_graph, track[MixerRow].velocity_ON, trackNames_short[MixerRow], trackColor[MixerRow]);
            }
          }
        }
      }

      //Track 5 - 8
      if (gridTouchY == 9) {
        for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
          byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
          if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
            if (abs(Potentiometer1 - track[MixerRow + 4].velocity_ON_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              track[MixerRow + 4].velocity_ON_graph = Potentiometer1;
              track[MixerRow + 4].velocity_ON = track[MixerRow + 4].velocity_ON_graph;

              if (track[MixerRow + 4].MIDIchannel > 16) {
                plugin[track[MixerRow + 4].MIDIchannel - 16].Volume_graph = Potentiometer1;
                plugin[track[MixerRow + 4].MIDIchannel - 16].Volume = plugin[track[MixerRow + 4].MIDIchannel - 16].Volume_graph / 127.00;
                pluginVolume(track[MixerRow + 4].MIDIchannel, plugin[track[MixerRow + 4].MIDIchannel - 16].Volume);
              }
              drawPot(mixerRowPos, 9, track[MixerRow + 4].velocity_ON_graph, track[MixerRow + 4].velocity_ON, trackNames_short[MixerRow + 4], trackColor[MixerRow + 4]);
            }
          }
        }
      }
    }
    //mute and solo states track 1-4
    //for better behaviour here we wait for "interval, unless it would switch within micrseconds
    if (gridTouchY == 5) {
      unsigned long currentMillis = millis();
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
      unsigned long currentMillis = millis();
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

  drawActiveRect(1, 5, 2, 2, false, "Rvrb", ILI9341_LIGHTGREY);
  drawActiveRect(1, 8, 2, 2, false, "BitC", ILI9341_LIGHTGREY);
  drawActiveRect(1, 11, 2, 2, false, "Dly", ILI9341_LIGHTGREY);

  drawPot(3, CONTROL_ROW_0, plugin[track[0].MIDIchannel - 16].FXDryVolume_graph, plugin[track[0].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[0]);
  drawPot(7, CONTROL_ROW_0, plugin[track[1].MIDIchannel - 16].FXDryVolume_graph, plugin[track[1].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[1]);
  drawPot(11, CONTROL_ROW_0, plugin[track[2].MIDIchannel - 16].FXDryVolume_graph, plugin[track[2].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[2]);
  drawPot(15, CONTROL_ROW_0, plugin[track[3].MIDIchannel - 16].FXDryVolume_graph, plugin[track[3].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[3]);

  drawPot(3, CONTROL_ROW_1, plugin[track[0].MIDIchannel - 16].FX1Volume_graph, plugin[track[0].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[0]);
  drawPot(7, CONTROL_ROW_1, plugin[track[1].MIDIchannel - 16].FX1Volume_graph, plugin[track[1].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[1]);
  drawPot(11, CONTROL_ROW_1, plugin[track[2].MIDIchannel - 16].FX1Volume_graph, plugin[track[2].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[2]);
  drawPot(15, CONTROL_ROW_1, plugin[track[3].MIDIchannel - 16].FX1Volume_graph, plugin[track[3].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[3]);

  drawPot(3, CONTROL_ROW_2, plugin[track[0].MIDIchannel - 16].FX2Volume_graph, plugin[track[0].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[0]);
  drawPot(7, CONTROL_ROW_2, plugin[track[1].MIDIchannel - 16].FX2Volume_graph, plugin[track[1].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[1]);
  drawPot(11, CONTROL_ROW_2, plugin[track[2].MIDIchannel - 16].FX2Volume_graph, plugin[track[2].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[2]);
  drawPot(15, CONTROL_ROW_2, plugin[track[3].MIDIchannel - 16].FX2Volume_graph, plugin[track[3].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[3]);

  drawPot(3, CONTROL_ROW_3, plugin[track[0].MIDIchannel - 16].FX3Volume_graph, plugin[track[0].MIDIchannel - 16].FX3Volume_graph, trackNames_short[0], trackColor[0]);
  drawPot(7, CONTROL_ROW_3, plugin[track[1].MIDIchannel - 16].FX3Volume_graph, plugin[track[1].MIDIchannel - 16].FX3Volume_graph, trackNames_short[1], trackColor[1]);
  drawPot(11, CONTROL_ROW_3, plugin[track[2].MIDIchannel - 16].FX3Volume_graph, plugin[track[2].MIDIchannel - 16].FX3Volume_graph, trackNames_short[2], trackColor[2]);
  drawPot(15, CONTROL_ROW_3, plugin[track[3].MIDIchannel - 16].FX3Volume_graph, plugin[track[3].MIDIchannel - 16].FX3Volume_graph, trackNames_short[3], trackColor[3]);
}
void MixerPage2_Dynamic() {
  if (ts.touched() || !buttons[6].read()) {
    if (millis() % 20 > 15) {

      //Dry siganl for Track D - 4
      if (gridTouchY == CONTROL_ROW_0) {
        for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
          byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
          if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
            drawPot(mixerRowPos, CONTROL_ROW_0, plugin[track[MixerRow].MIDIchannel - 16].FXDryVolume_graph, plugin[track[MixerRow].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[MixerRow]);
            if (abs(Potentiometer1 - plugin[track[MixerRow].MIDIchannel - 16].FXDryVolume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              plugin[track[MixerRow].MIDIchannel - 16].FXDryVolume_graph = Potentiometer1;
              plugin[track[MixerRow].MIDIchannel - 16].FXDryVolume = plugin[track[MixerRow].MIDIchannel - 16].FXDryVolume_graph / 127.00;
              FXDrypluginVolume(track[MixerRow].MIDIchannel, plugin[track[MixerRow].MIDIchannel - 16].FXDryVolume);
            }
          }
        }
      }


      //Send to FX1 Reverb Track D - 4
      if (gridTouchY == CONTROL_ROW_1) {
        for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
          byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
          if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
            drawPot(mixerRowPos, CONTROL_ROW_1, plugin[track[MixerRow].MIDIchannel - 16].FX1Volume_graph, plugin[track[MixerRow].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[MixerRow]);
            if (abs(Potentiometer1 - plugin[track[MixerRow].MIDIchannel - 16].FX1Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              plugin[track[MixerRow].MIDIchannel - 16].FX1Volume_graph = Potentiometer1;
              plugin[track[MixerRow].MIDIchannel - 16].FX1Volume = plugin[track[MixerRow].MIDIchannel - 16].FX1Volume_graph / 127.00;
              FX1pluginVolume(track[MixerRow].MIDIchannel, plugin[track[MixerRow].MIDIchannel - 16].FX1Volume);
            }
          }
        }
      }
      //Send to FX2 Bitcrusher Track D - 4
      if (gridTouchY == CONTROL_ROW_2) {
        for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
          byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
          if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
            drawPot(mixerRowPos, CONTROL_ROW_2, plugin[track[MixerRow].MIDIchannel - 16].FX2Volume_graph, plugin[track[MixerRow].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[MixerRow]);
            if (abs(Potentiometer1 - plugin[track[MixerRow].MIDIchannel - 16].FX2Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              plugin[track[MixerRow].MIDIchannel - 16].FX2Volume_graph = Potentiometer1;
              plugin[track[MixerRow].MIDIchannel - 16].FX2Volume = plugin[track[MixerRow].MIDIchannel - 16].FX2Volume_graph / 127.00;
              FX2pluginVolume(track[MixerRow].MIDIchannel, plugin[track[MixerRow].MIDIchannel - 16].FX2Volume);
            }
          }
        }
      }
      //Send to FX3 Delay Track D - 4
      if (gridTouchY == CONTROL_ROW_3) {
        for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
          byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
          if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
            drawPot(mixerRowPos, CONTROL_ROW_3, plugin[track[MixerRow].MIDIchannel - 16].FX3Volume_graph, plugin[track[MixerRow].MIDIchannel - 16].FX3Volume_graph, trackNames_short[MixerRow], trackColor[MixerRow]);
            if (abs(Potentiometer1 - plugin[track[MixerRow].MIDIchannel - 16].FX3Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              plugin[track[MixerRow].MIDIchannel - 16].FX3Volume_graph = Potentiometer1;
              plugin[track[MixerRow].MIDIchannel - 16].FX3Volume = plugin[track[MixerRow].MIDIchannel - 16].FX3Volume_graph / 127.00;
              FX3pluginVolume(track[MixerRow].MIDIchannel, plugin[track[MixerRow].MIDIchannel - 16].FX3Volume);
            }
          }
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

  drawActiveRect(1, 5, 2, 2, false, "Rvrb", ILI9341_LIGHTGREY);
  drawActiveRect(1, 8, 2, 2, false, "BitC", ILI9341_LIGHTGREY);
  drawActiveRect(1, 11, 2, 2, false, "Dly", ILI9341_LIGHTGREY);

  drawPot(3, CONTROL_ROW_0, plugin[track[4].MIDIchannel - 16].FXDryVolume_graph, plugin[track[4].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[4]);
  drawPot(7, CONTROL_ROW_0, plugin[track[5].MIDIchannel - 16].FXDryVolume_graph, plugin[track[5].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[5]);
  drawPot(11, CONTROL_ROW_0, plugin[track[6].MIDIchannel - 16].FXDryVolume_graph, plugin[track[6].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[6]);
  drawPot(15, CONTROL_ROW_0, plugin[track[7].MIDIchannel - 16].FXDryVolume_graph, plugin[track[7].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[7]);

  drawPot(3, CONTROL_ROW_1, plugin[track[4].MIDIchannel - 16].FX1Volume_graph, plugin[track[4].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[4]);
  drawPot(7, CONTROL_ROW_1, plugin[track[5].MIDIchannel - 16].FX1Volume_graph, plugin[track[5].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[5]);
  drawPot(11, CONTROL_ROW_1, plugin[track[6].MIDIchannel - 16].FX1Volume_graph, plugin[track[6].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[6]);
  drawPot(15, CONTROL_ROW_1, plugin[track[7].MIDIchannel - 16].FX1Volume_graph, plugin[track[7].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[7]);

  drawPot(3, CONTROL_ROW_2, plugin[track[4].MIDIchannel - 16].FX2Volume_graph, plugin[track[4].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[4]);
  drawPot(7, CONTROL_ROW_2, plugin[track[5].MIDIchannel - 16].FX2Volume_graph, plugin[track[5].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[5]);
  drawPot(11, CONTROL_ROW_2, plugin[track[6].MIDIchannel - 16].FX2Volume_graph, plugin[track[6].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[6]);
  drawPot(15, CONTROL_ROW_2, plugin[track[7].MIDIchannel - 16].FX2Volume_graph, plugin[track[7].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[7]);

  drawPot(3, CONTROL_ROW_3, plugin[track[4].MIDIchannel - 16].FX3Volume_graph, plugin[track[4].MIDIchannel - 16].FX3Volume_graph, trackNames_short[4], trackColor[4]);
  drawPot(7, CONTROL_ROW_3, plugin[track[5].MIDIchannel - 16].FX3Volume_graph, plugin[track[5].MIDIchannel - 16].FX3Volume_graph, trackNames_short[5], trackColor[5]);
  drawPot(11, CONTROL_ROW_3, plugin[track[6].MIDIchannel - 16].FX3Volume_graph, plugin[track[6].MIDIchannel - 16].FX3Volume_graph, trackNames_short[6], trackColor[6]);
  drawPot(15, CONTROL_ROW_3, plugin[track[7].MIDIchannel - 16].FX3Volume_graph, plugin[track[7].MIDIchannel - 16].FX3Volume_graph, trackNames_short[7], trackColor[7]);
}
void MixerPage3_Dynamic() {
  if (ts.touched() || !buttons[6].read()) {
    if (millis() % 20 > 15) {
      //Dry siganl for Track D - 4
      if (gridTouchY == CONTROL_ROW_0) {
        for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
          byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
          if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
            drawPot(mixerRowPos, CONTROL_ROW_0, plugin[track[MixerRow + 4].MIDIchannel - 16].FXDryVolume_graph, plugin[track[MixerRow + 4].MIDIchannel - 16].FXDryVolume_graph, trackNames_short[8], trackColor[MixerRow + 4]);
            if (abs(Potentiometer1 - plugin[track[MixerRow + 4].MIDIchannel - 16].FXDryVolume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              plugin[track[MixerRow + 4].MIDIchannel - 16].FXDryVolume_graph = Potentiometer1;
              plugin[track[MixerRow + 4].MIDIchannel - 16].FXDryVolume = plugin[track[MixerRow + 4].MIDIchannel - 16].FXDryVolume_graph / 127.00;
              FXDrypluginVolume(track[MixerRow + 4].MIDIchannel, plugin[track[MixerRow + 4].MIDIchannel - 16].FXDryVolume);
            }
          }
        }
      }


      //Send to FX1 Reverb Track D - 4
      if (gridTouchY == CONTROL_ROW_1) {
        for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
          byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
          if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
            drawPot(mixerRowPos, CONTROL_ROW_1, plugin[track[MixerRow + 4].MIDIchannel - 16].FX1Volume_graph, plugin[track[MixerRow + 4].MIDIchannel - 16].FX1Volume_graph, trackNames_short[8], trackColor[MixerRow + 4]);
            if (abs(Potentiometer1 - plugin[track[MixerRow + 4].MIDIchannel - 16].FX1Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              plugin[track[MixerRow + 4].MIDIchannel - 16].FX1Volume_graph = Potentiometer1;
              plugin[track[MixerRow + 4].MIDIchannel - 16].FX1Volume = plugin[track[MixerRow + 4].MIDIchannel - 16].FX1Volume_graph / 127.00;
              FX1pluginVolume(track[MixerRow + 4].MIDIchannel, plugin[track[MixerRow + 4].MIDIchannel - 16].FX1Volume);
            }
          }
        }
      }
      //Send to FX2 Bitcrusher Track 5 - 8
      if (gridTouchY == CONTROL_ROW_2) {
        for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
          byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
          if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
            drawPot(mixerRowPos, CONTROL_ROW_2, plugin[track[MixerRow + 4].MIDIchannel - 16].FX2Volume_graph, plugin[track[MixerRow + 4].MIDIchannel - 16].FX2Volume_graph, trackNames_short[8], trackColor[MixerRow + 4]);
            if (abs(Potentiometer1 - plugin[track[MixerRow + 4].MIDIchannel - 16].FX2Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              plugin[track[MixerRow + 4].MIDIchannel - 16].FX2Volume_graph = Potentiometer1;
              plugin[track[MixerRow + 4].MIDIchannel - 16].FX2Volume = plugin[track[MixerRow + 4].MIDIchannel - 16].FX2Volume_graph / 127.00;
              FX2pluginVolume(track[MixerRow + 4].MIDIchannel, plugin[track[MixerRow + 4].MIDIchannel - 16].FX2Volume);
            }
          }
        }
      }
      //Send to FX3 Delay Track 5 - 8
      if (gridTouchY == CONTROL_ROW_3) {
        for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
          byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
          if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
            drawPot(mixerRowPos, CONTROL_ROW_3, plugin[track[MixerRow + 4].MIDIchannel - 16].FX3Volume_graph, plugin[track[MixerRow + 4].MIDIchannel - 16].FX3Volume_graph, trackNames_short[MixerRow + 4], trackColor[MixerRow + 4]);
            if (abs(Potentiometer1 - plugin[track[MixerRow + 4].MIDIchannel - 16].FX3Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              plugin[track[MixerRow + 4].MIDIchannel - 16].FX3Volume_graph = Potentiometer1;
              plugin[track[MixerRow + 4].MIDIchannel - 16].FX3Volume = plugin[track[MixerRow + 4].MIDIchannel - 16].FX3Volume_graph / 127.00;
              FX3pluginVolume(track[MixerRow + 4].MIDIchannel, plugin[track[MixerRow + 4].MIDIchannel - 16].FX3Volume);
            }
          }
        }
      }
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