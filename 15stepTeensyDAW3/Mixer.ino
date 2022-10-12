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
void pluginVolume(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  if (pluginchannel == 17) {
    mixer5.gain(0, volume);
  }
  if (pluginchannel == 18) {
    mixer5.gain(1, volume);
  }
  if (pluginchannel == 19) {
    mixer5.gain(2, volume);
  }
  if (pluginchannel == 20) {
    mixer5.gain(3, volume);
  }

  if (pluginchannel == 21) {
    mixer6.gain(0, volume);
  }
  if (pluginchannel == 22) {
    mixer6.gain(1, volume);
  }
  if (pluginchannel == 23) {
    mixer6.gain(2, volume);
  }
  if (pluginchannel == 24) {
    mixer6.gain(3, volume);
  }
}
void FXDrypluginVolume(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  if (pluginchannel == 17) {
    mixer5.gain(0, volume);
  }
  if (pluginchannel == 18) {
    mixer5.gain(1, volume);
  }
  if (pluginchannel == 19) {
    mixer5.gain(2, volume);
  }
  if (pluginchannel == 20) {
    mixer5.gain(3, volume);
  }

  if (pluginchannel == 21) {
    mixer6.gain(0, volume);
  }
  if (pluginchannel == 22) {
    mixer6.gain(1, volume);
  }
  if (pluginchannel == 23) {
    mixer6.gain(2, volume);
  }
  if (pluginchannel == 24) {
    mixer6.gain(3, volume);
  }
}



void FX1pluginVolume(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  if (pluginchannel == 17) {
    FX1mixer1.gain(0, volume);
  }
  if (pluginchannel == 18) {
    FX1mixer1.gain(1, volume);
  }
  if (pluginchannel == 19) {
    FX1mixer1.gain(2, volume);
  }
  if (pluginchannel == 20) {
    FX1mixer1.gain(3, volume);
  }

  if (pluginchannel == 21) {
    FX1mixer2.gain(0, volume);
  }
  if (pluginchannel == 22) {
    FX1mixer2.gain(1, volume);
  }
  if (pluginchannel == 23) {
    FX1mixer2.gain(2, volume);
  }
  if (pluginchannel == 24) {
    FX1mixer2.gain(3, volume);
  }
}
void FX2pluginVolume(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  if (pluginchannel == 17) {
    FX2mixer1.gain(0, volume);
  }
  if (pluginchannel == 18) {
    FX2mixer1.gain(1, volume);
  }
  if (pluginchannel == 19) {
    FX2mixer1.gain(2, volume);
  }
  if (pluginchannel == 20) {
    FX2mixer1.gain(3, volume);
  }

  if (pluginchannel == 21) {
    FX2mixer2.gain(0, volume);
  }
  if (pluginchannel == 22) {
    FX2mixer2.gain(1, volume);
  }
  if (pluginchannel == 23) {
    FX2mixer2.gain(2, volume);
  }
  if (pluginchannel == 24) {
    FX2mixer2.gain(3, volume);
  }
}
void FX3pluginVolume(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  if (pluginchannel == 17) {
    FX3mixer1.gain(0, volume);
  }
  if (pluginchannel == 18) {
    FX3mixer1.gain(1, volume);
  }
  if (pluginchannel == 19) {
    FX3mixer1.gain(2, volume);
  }
  if (pluginchannel == 20) {
    FX3mixer1.gain(3, volume);
  }

  if (pluginchannel == 21) {
    FX3mixer2.gain(0, volume);
  }
  if (pluginchannel == 22) {
    FX3mixer2.gain(1, volume);
  }
  if (pluginchannel == 23) {
    FX3mixer2.gain(2, volume);
  }
  if (pluginchannel == 24) {
    FX3mixer2.gain(3, volume);
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
  drawActiveSquare(18, 3, 2, true, "Main", ILI9341_LIGHTGREY);
  drawActiveSquare(18, 5, 2, false, "D-4", ILI9341_LIGHTGREY);
  drawActiveSquare(18, 7, 2, false, "5-8", ILI9341_LIGHTGREY);



  drawPot(3, 3, track[0].velocity_ON_graph, track[0].velocity_ON, "TrD", ILI9341_RED);
  drawActiveSquare(3, 5, 1, track[0].mute_state, "M", ILI9341_RED);
  drawActiveSquare(4, 5, 1, track[0].solo_state, "S", ILI9341_WHITE);
  drawPot(7, 3, track[1].velocity_ON_graph, track[1].velocity_ON, "Tr2", ILI9341_RED);
  drawActiveSquare(7, 5, 1, track[1].mute_state, "M", ILI9341_RED);
  drawActiveSquare(8, 5, 1, track[1].solo_state, "S", ILI9341_WHITE);
  drawPot(11, 3, track[2].velocity_ON_graph, track[2].velocity_ON, "Tr3", ILI9341_RED);
  drawActiveSquare(11, 5, 1, track[2].mute_state, "M", ILI9341_RED);
  drawActiveSquare(12, 5, 1, track[2].solo_state, "S", ILI9341_WHITE);
  drawPot(15, 3, track[3].velocity_ON_graph, track[3].velocity_ON, "Tr4", ILI9341_RED);
  drawActiveSquare(15, 5, 1, track[3].mute_state, "M", ILI9341_RED);
  drawActiveSquare(16, 5, 1, track[3].solo_state, "S", ILI9341_WHITE);

  drawPot(3, 9, track[4].velocity_ON_graph, track[4].velocity_ON, "Tr5", ILI9341_RED);
  drawActiveSquare(3, 11, 1, track[4].mute_state, "M", ILI9341_RED);
  drawActiveSquare(4, 11, 1, track[4].solo_state, "S", ILI9341_WHITE);
  drawPot(7, 9, track[5].velocity_ON_graph, track[5].velocity_ON, "Tr6", ILI9341_RED);
  drawActiveSquare(7, 11, 1, track[5].mute_state, "M", ILI9341_RED);
  drawActiveSquare(8, 11, 1, track[5].solo_state, "S", ILI9341_WHITE);
  drawPot(11, 9, track[6].velocity_ON_graph, track[6].velocity_ON, "Tr7", ILI9341_RED);
  drawActiveSquare(11, 11, 1, track[6].mute_state, "M", ILI9341_RED);
  drawActiveSquare(12, 11, 1, track[6].solo_state, "S", ILI9341_WHITE);
  drawPot(15, 9, track[7].velocity_ON_graph, track[7].velocity_ON, "Tr8", ILI9341_RED);
  drawActiveSquare(15, 11, 1, track[7].mute_state, "M", ILI9341_RED);
  drawActiveSquare(16, 11, 1, track[7].solo_state, "S", ILI9341_WHITE);
}
void MixerPage1_Dynamic() {
  if (ts.touched() || !buttons[6].read()) {

    //Track D - 4
    if (gridTouchY == 3) {
      for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
        byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
        if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
          if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - track[MixerRow].velocity_ON_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            track[MixerRow].velocity_ON = map(Potentiometer1, 0, 1023, 0, 127);
            track[MixerRow].velocity_ON_graph = map(Potentiometer1, 0, 1023, 0, 100);
            if (track[MixerRow].MIDIchannel > 16) {
              plugin[track[MixerRow].MIDIchannel - 16].Volume_rnd = map(Potentiometer1, 0, 1023, 0, 100);
              plugin[track[MixerRow].MIDIchannel - 16].Volume = plugin[track[MixerRow].MIDIchannel - 16].Volume_rnd / 100.00;
              plugin[track[MixerRow].MIDIchannel - 16].Volume_graph = map(Potentiometer1, 0, 1023, 0, 100);
              pluginVolume(track[MixerRow].MIDIchannel, plugin[track[MixerRow].MIDIchannel - 16].Volume);
            }
            drawPot(mixerRowPos, 3, track[MixerRow].velocity_ON_graph, track[MixerRow].velocity_ON, track[MixerRow].trackNames_short[MixerRow], ILI9341_RED);
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
            drawActiveSquare((((mutes + 1) * 4) - 1), 5, 1, track[mutes].mute_state, "M", ILI9341_RED);
          }
        }
        for (byte solos = 0; solos < 4; solos++) {
          if (gridTouchX == (solos + 1) * 4) {
            selectSolo(solos);
            drawActiveSquare((solos + 1) * 4, 5, 1, track[solos].solo_state, "S", ILI9341_WHITE);
          }
        }
      }
    }

    //Track 5 - 8
    if (gridTouchY == 9) {
      for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
        byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
        if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
          if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - track[MixerRow + 4].velocity_ON_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            track[MixerRow + 4].velocity_ON = map(Potentiometer1, 0, 1023, 0, 127);
            track[MixerRow + 4].velocity_ON_graph = map(Potentiometer1, 0, 1023, 0, 100);
            if (track[MixerRow + 4].MIDIchannel > 16) {
              plugin[track[MixerRow + 4].MIDIchannel - 16].Volume_rnd = map(Potentiometer1, 0, 1023, 0, 100);
              plugin[track[MixerRow + 4].MIDIchannel - 16].Volume = plugin[track[MixerRow + 4].MIDIchannel - 16].Volume_rnd / 100.00;
              plugin[track[MixerRow + 4].MIDIchannel - 16].Volume_graph = map(Potentiometer1, 0, 1023, 0, 100);
              pluginVolume(track[MixerRow + 4].MIDIchannel, plugin[track[MixerRow + 4].MIDIchannel - 16].Volume);
            }
            drawPot(mixerRowPos, 9, track[MixerRow + 4].velocity_ON_graph, track[MixerRow + 4].velocity_ON, track[MixerRow + 4].trackNames_short[MixerRow + 4], ILI9341_RED);
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
            drawActiveSquare((((mutes + 1) * 4) - 1), 11, 1, track[mutes + 4].mute_state, "M", ILI9341_RED);
          }
        }
        for (byte solos = 0; solos < 4; solos++) {
          if (gridTouchX == (solos + 1) * 4) {
            selectSolo(solos + 4);
            drawActiveSquare((solos + 1) * 4, 11, 1, track[solos + 4].solo_state, "S", ILI9341_WHITE);
          }
        }
      }
    }

    //page selection
    if (gridTouchX >= 18 && gridTouchY >= 3 && gridTouchY <= 4) {
      select_page(MIXER_PAGE_1);
      mixerPage1_Static(0);
      MixerPage1_Dynamic();
    }
    if (gridTouchX >= 18 && gridTouchY >= 5 && gridTouchY <= 6) {
      select_page(MIXER_PAGE_2);
      mixerPage2_Static();
      MixerPage2_Dynamic();
    }
    if (gridTouchX >= 18 && gridTouchY >= 7 && gridTouchY <= 8) {
      select_page(MIXER_PAGE_3);
      mixerPage3_Static();
      MixerPage3_Dynamic();
    }
  }
}



void mixerPage2_Static() {
  clearWorkSpace();
  //draw_sub_page_buttons(2);
  drawActiveSquare(18, 3, 2, false, "Main", ILI9341_LIGHTGREY);
  drawActiveSquare(18, 5, 2, true, "D-4", ILI9341_LIGHTGREY);
  drawActiveSquare(18, 7, 2, false, "5-8", ILI9341_LIGHTGREY);

  drawActiveSquare(1, 5, 2, false, "Rvrb", ILI9341_LIGHTGREY);
  drawActiveSquare(1, 8, 2, false, "BitC", ILI9341_LIGHTGREY);
  drawActiveSquare(1, 11, 2, false, "Dly", ILI9341_LIGHTGREY);

  drawPot(3, MixerPage2_Dynamic_ROW_0, plugin[track[0].MIDIchannel - 16].FXDryVolume_graph, plugin[track[0].MIDIchannel - 16].FXDryVolume_rnd, track[0].trackNames_short[8], ILI9341_RED);
  drawPot(7, MixerPage2_Dynamic_ROW_0, plugin[track[1].MIDIchannel - 16].FXDryVolume_graph, plugin[track[1].MIDIchannel - 16].FXDryVolume_rnd, track[1].trackNames_short[8], ILI9341_RED);
  drawPot(11, MixerPage2_Dynamic_ROW_0, plugin[track[2].MIDIchannel - 16].FXDryVolume_graph, plugin[track[2].MIDIchannel - 16].FXDryVolume_rnd, track[2].trackNames_short[8], ILI9341_RED);
  drawPot(15, MixerPage2_Dynamic_ROW_0, plugin[track[3].MIDIchannel - 16].FXDryVolume_graph, plugin[track[3].MIDIchannel - 16].FXDryVolume_rnd, track[3].trackNames_short[8], ILI9341_RED);

  drawPot(3, MixerPage2_Dynamic_ROW_1, plugin[track[0].MIDIchannel - 16].FX1Volume_graph, plugin[track[0].MIDIchannel - 16].FX1Volume_rnd, track[0].trackNames_short[8], ILI9341_RED);
  drawPot(7, MixerPage2_Dynamic_ROW_1, plugin[track[1].MIDIchannel - 16].FX1Volume_graph, plugin[track[1].MIDIchannel - 16].FX1Volume_rnd, track[1].trackNames_short[8], ILI9341_RED);
  drawPot(11, MixerPage2_Dynamic_ROW_1, plugin[track[2].MIDIchannel - 16].FX1Volume_graph, plugin[track[2].MIDIchannel - 16].FX1Volume_rnd, track[2].trackNames_short[8], ILI9341_RED);
  drawPot(15, MixerPage2_Dynamic_ROW_1, plugin[track[3].MIDIchannel - 16].FX1Volume_graph, plugin[track[3].MIDIchannel - 16].FX1Volume_rnd, track[3].trackNames_short[8], ILI9341_RED);

  drawPot(3, MixerPage2_Dynamic_ROW_2, plugin[track[0].MIDIchannel - 16].FX2Volume_graph, plugin[track[0].MIDIchannel - 16].FX2Volume_rnd, track[0].trackNames_short[8], ILI9341_RED);
  drawPot(7, MixerPage2_Dynamic_ROW_2, plugin[track[1].MIDIchannel - 16].FX2Volume_graph, plugin[track[1].MIDIchannel - 16].FX2Volume_rnd, track[1].trackNames_short[8], ILI9341_RED);
  drawPot(11, MixerPage2_Dynamic_ROW_2, plugin[track[2].MIDIchannel - 16].FX2Volume_graph, plugin[track[2].MIDIchannel - 16].FX2Volume_rnd, track[2].trackNames_short[8], ILI9341_RED);
  drawPot(15, MixerPage2_Dynamic_ROW_2, plugin[track[3].MIDIchannel - 16].FX2Volume_graph, plugin[track[3].MIDIchannel - 16].FX2Volume_rnd, track[3].trackNames_short[8], ILI9341_RED);

  drawPot(3, MixerPage2_Dynamic_ROW_3, plugin[track[0].MIDIchannel - 16].FX3Volume_graph, plugin[track[0].MIDIchannel - 16].FX3Volume_rnd, track[0].trackNames_short[0], ILI9341_RED);
  drawPot(7, MixerPage2_Dynamic_ROW_3, plugin[track[1].MIDIchannel - 16].FX3Volume_graph, plugin[track[1].MIDIchannel - 16].FX3Volume_rnd, track[1].trackNames_short[1], ILI9341_RED);
  drawPot(11, MixerPage2_Dynamic_ROW_3, plugin[track[2].MIDIchannel - 16].FX3Volume_graph, plugin[track[2].MIDIchannel - 16].FX3Volume_rnd, track[2].trackNames_short[2], ILI9341_RED);
  drawPot(15, MixerPage2_Dynamic_ROW_3, plugin[track[3].MIDIchannel - 16].FX3Volume_graph, plugin[track[3].MIDIchannel - 16].FX3Volume_rnd, track[3].trackNames_short[3], ILI9341_RED);
}
void MixerPage2_Dynamic() {
  if (ts.touched() || !buttons[6].read()) {

    //Dry siganl for Track D - 4
    if (gridTouchY == MixerPage2_Dynamic_ROW_0) {
      for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
        byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
        if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
          drawPot(mixerRowPos, MixerPage2_Dynamic_ROW_0, plugin[track[MixerRow].MIDIchannel - 16].FXDryVolume_graph, plugin[track[MixerRow].MIDIchannel - 16].FXDryVolume_rnd, track[MixerRow].trackNames_short[8], ILI9341_RED);
          if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - plugin[track[MixerRow].MIDIchannel - 16].FXDryVolume_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            //decrease dry volume
            plugin[track[MixerRow].MIDIchannel - 16].FXDryVolume_rnd = map(Potentiometer1, 0, 1023, 0, 100);
            plugin[track[MixerRow].MIDIchannel - 16].FXDryVolume = plugin[track[MixerRow].MIDIchannel - 16].FXDryVolume_rnd / 100.00;
            plugin[track[MixerRow].MIDIchannel - 16].FXDryVolume_graph = map(Potentiometer1, 0, 1023, 0, 100);
            FXDrypluginVolume(track[MixerRow].MIDIchannel, plugin[track[MixerRow].MIDIchannel - 16].FXDryVolume);
          }
        }
      }
    }


    //Send to FX1 Reverb Track D - 4
    if (gridTouchY == MixerPage2_Dynamic_ROW_1) {
      for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
        byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
        if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
          drawPot(mixerRowPos, MixerPage2_Dynamic_ROW_1, plugin[track[MixerRow].MIDIchannel - 16].FX1Volume_graph, plugin[track[MixerRow].MIDIchannel - 16].FX1Volume_rnd, track[MixerRow].trackNames_short[8], ILI9341_RED);
          if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - plugin[track[MixerRow].MIDIchannel - 16].FX1Volume_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            //increase FX volume
            plugin[track[MixerRow].MIDIchannel - 16].FX1Volume_rnd = map(Potentiometer1, 0, 1023, 0, 100);
            plugin[track[MixerRow].MIDIchannel - 16].FX1Volume = plugin[track[MixerRow].MIDIchannel - 16].FX1Volume_rnd / 100.00;
            plugin[track[MixerRow].MIDIchannel - 16].FX1Volume_graph = map(Potentiometer1, 0, 1023, 0, 100);
            FX1pluginVolume(track[MixerRow].MIDIchannel, plugin[track[MixerRow].MIDIchannel - 16].FX1Volume);
          }
        }
      }
    }
    //Send to FX2 Bitcrusher Track D - 4
    if (gridTouchY == MixerPage2_Dynamic_ROW_2) {
      for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
        byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
        if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
          drawPot(mixerRowPos, MixerPage2_Dynamic_ROW_2, plugin[track[MixerRow].MIDIchannel - 16].FX2Volume_graph, plugin[track[MixerRow].MIDIchannel - 16].FX2Volume_rnd, track[MixerRow].trackNames_short[8], ILI9341_RED);
          if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - plugin[track[MixerRow].MIDIchannel - 16].FX2Volume_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            //increase FX volume
            plugin[track[MixerRow].MIDIchannel - 16].FX2Volume_rnd = map(Potentiometer1, 0, 1023, 0, 100);
            plugin[track[MixerRow].MIDIchannel - 16].FX2Volume = plugin[track[MixerRow].MIDIchannel - 16].FX2Volume_rnd / 100.00;
            plugin[track[MixerRow].MIDIchannel - 16].FX2Volume_graph = map(Potentiometer1, 0, 1023, 0, 100);
            FX2pluginVolume(track[MixerRow].MIDIchannel, plugin[track[MixerRow].MIDIchannel - 16].FX2Volume);
          }
        }
      }
    }
    //Send to FX3 Delay Track D - 4
    if (gridTouchY == MixerPage2_Dynamic_ROW_3) {
      for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
        byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
        if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
          drawPot(mixerRowPos, MixerPage2_Dynamic_ROW_3, plugin[track[MixerRow].MIDIchannel - 16].FX3Volume_graph, plugin[track[MixerRow].MIDIchannel - 16].FX3Volume_rnd, track[MixerRow].trackNames_short[MixerRow], ILI9341_RED);
          if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - plugin[track[MixerRow].MIDIchannel - 16].FX3Volume_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen

            //increase FX volume
            plugin[track[MixerRow].MIDIchannel - 16].FX3Volume_rnd = map(Potentiometer1, 0, 1023, 0, 100);
            plugin[track[MixerRow].MIDIchannel - 16].FX3Volume = plugin[track[MixerRow].MIDIchannel - 16].FX3Volume_rnd / 100.00;
            plugin[track[MixerRow].MIDIchannel - 16].FX3Volume_graph = map(Potentiometer1, 0, 1023, 0, 100);
            FX3pluginVolume(track[MixerRow].MIDIchannel, plugin[track[MixerRow].MIDIchannel - 16].FX3Volume);
          }
        }
      }
    }
    if (gridTouchX >= 18) {
        //page selection
        if (gridTouchY >= 3 && gridTouchY <= 4) {
          select_page(MIXER_PAGE_1);
          mixerPage1_Static(0);
          MixerPage1_Dynamic();
        }
        if (gridTouchY >= 5 && gridTouchY <= 6) {
          select_page(MIXER_PAGE_2);
          mixerPage2_Static();
          MixerPage2_Dynamic();
        }
        if (gridTouchY >= 7 && gridTouchY <= 8) {
          select_page(MIXER_PAGE_3);
          mixerPage3_Static();
          MixerPage3_Dynamic();
        }
      }
      if (gridTouchX == 1 || gridTouchX == 2) {

        if (gridTouchY == 5 || gridTouchY == 6) {
          select_page(FX1_PAGE1);
          FX1reverb_static();
        }    
        if (gridTouchY == 8 || gridTouchY == 9) {
          select_page(FX2_PAGE1);
          FX2Bitcrush_static();
        }
      }
  }
}

void mixerPage3_Static() {
  clearWorkSpace();
  //draw_sub_page_buttons(2);
  drawActiveSquare(18, 3, 2, false, "Main", ILI9341_LIGHTGREY);
  drawActiveSquare(18, 5, 2, false, "D-4", ILI9341_LIGHTGREY);
  drawActiveSquare(18, 7, 2, true, "5-8", ILI9341_LIGHTGREY);

  drawActiveSquare(1, 5, 2, false, "Rvrb", ILI9341_LIGHTGREY);
  drawActiveSquare(1, 8, 2, false, "BitC", ILI9341_LIGHTGREY);
  drawActiveSquare(1, 11, 2, false, "Dly", ILI9341_LIGHTGREY);

  drawPot(3, MixerPage2_Dynamic_ROW_0, plugin[track[4].MIDIchannel - 16].FXDryVolume_graph, plugin[track[4].MIDIchannel - 16].FXDryVolume_rnd, track[4].trackNames_short[8], ILI9341_RED);
  drawPot(7, MixerPage2_Dynamic_ROW_0, plugin[track[5].MIDIchannel - 16].FXDryVolume_graph, plugin[track[5].MIDIchannel - 16].FXDryVolume_rnd, track[5].trackNames_short[8], ILI9341_RED);
  drawPot(11, MixerPage2_Dynamic_ROW_0, plugin[track[6].MIDIchannel - 16].FXDryVolume_graph, plugin[track[6].MIDIchannel - 16].FXDryVolume_rnd, track[6].trackNames_short[8], ILI9341_RED);
  drawPot(15, MixerPage2_Dynamic_ROW_0, plugin[track[7].MIDIchannel - 16].FXDryVolume_graph, plugin[track[7].MIDIchannel - 16].FXDryVolume_rnd, track[7].trackNames_short[8], ILI9341_RED);

  drawPot(3, MixerPage2_Dynamic_ROW_1, plugin[track[4].MIDIchannel - 16].FX1Volume_graph, plugin[track[4].MIDIchannel - 16].FX1Volume_rnd, track[4].trackNames_short[8], ILI9341_RED);
  drawPot(7, MixerPage2_Dynamic_ROW_1, plugin[track[5].MIDIchannel - 16].FX1Volume_graph, plugin[track[5].MIDIchannel - 16].FX1Volume_rnd, track[5].trackNames_short[8], ILI9341_RED);
  drawPot(11, MixerPage2_Dynamic_ROW_1, plugin[track[6].MIDIchannel - 16].FX1Volume_graph, plugin[track[6].MIDIchannel - 16].FX1Volume_rnd, track[6].trackNames_short[8], ILI9341_RED);
  drawPot(15, MixerPage2_Dynamic_ROW_1, plugin[track[7].MIDIchannel - 16].FX1Volume_graph, plugin[track[7].MIDIchannel - 16].FX1Volume_rnd, track[7].trackNames_short[8], ILI9341_RED);

  drawPot(3, MixerPage2_Dynamic_ROW_2, plugin[track[4].MIDIchannel - 16].FX2Volume_graph, plugin[track[4].MIDIchannel - 16].FX2Volume_rnd, track[4].trackNames_short[8], ILI9341_RED);
  drawPot(7, MixerPage2_Dynamic_ROW_2, plugin[track[5].MIDIchannel - 16].FX2Volume_graph, plugin[track[5].MIDIchannel - 16].FX2Volume_rnd, track[5].trackNames_short[8], ILI9341_RED);
  drawPot(11, MixerPage2_Dynamic_ROW_2, plugin[track[6].MIDIchannel - 16].FX2Volume_graph, plugin[track[6].MIDIchannel - 16].FX2Volume_rnd, track[6].trackNames_short[8], ILI9341_RED);
  drawPot(15, MixerPage2_Dynamic_ROW_2, plugin[track[7].MIDIchannel - 16].FX2Volume_graph, plugin[track[7].MIDIchannel - 16].FX2Volume_rnd, track[7].trackNames_short[8], ILI9341_RED);

  drawPot(3, MixerPage2_Dynamic_ROW_3, plugin[track[4].MIDIchannel - 16].FX3Volume_graph, plugin[track[4].MIDIchannel - 16].FX3Volume_rnd, track[4].trackNames_short[4], ILI9341_RED);
  drawPot(7, MixerPage2_Dynamic_ROW_3, plugin[track[5].MIDIchannel - 16].FX3Volume_graph, plugin[track[5].MIDIchannel - 16].FX3Volume_rnd, track[5].trackNames_short[5], ILI9341_RED);
  drawPot(11, MixerPage2_Dynamic_ROW_3, plugin[track[6].MIDIchannel - 16].FX3Volume_graph, plugin[track[6].MIDIchannel - 16].FX3Volume_rnd, track[6].trackNames_short[6], ILI9341_RED);
  drawPot(15, MixerPage2_Dynamic_ROW_3, plugin[track[7].MIDIchannel - 16].FX3Volume_graph, plugin[track[7].MIDIchannel - 16].FX3Volume_rnd, track[7].trackNames_short[7], ILI9341_RED);
}
void MixerPage3_Dynamic() {
  if (ts.touched() || !buttons[6].read()) {

    //Dry siganl for Track D - 4
    if (gridTouchY == MixerPage2_Dynamic_ROW_0) {
      for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
        byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
        if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
          drawPot(mixerRowPos, MixerPage2_Dynamic_ROW_0, plugin[track[MixerRow + 4].MIDIchannel - 16].FXDryVolume_graph, plugin[track[MixerRow + 4].MIDIchannel - 16].FXDryVolume_rnd, track[MixerRow].trackNames_short[8], ILI9341_RED);
          if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - plugin[track[MixerRow + 4].MIDIchannel - 16].FXDryVolume_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            //decrease dry volume
            plugin[track[MixerRow + 4].MIDIchannel - 16].FXDryVolume_rnd = map(Potentiometer1, 0, 1023, 0, 100);
            plugin[track[MixerRow + 4].MIDIchannel - 16].FXDryVolume = plugin[track[MixerRow + 4].MIDIchannel - 16].FXDryVolume_rnd / 100.00;
            plugin[track[MixerRow + 4].MIDIchannel - 16].FXDryVolume_graph = map(Potentiometer1, 0, 1023, 0, 100);
            FXDrypluginVolume(track[MixerRow + 4].MIDIchannel, plugin[track[MixerRow + 4].MIDIchannel - 16].FXDryVolume);
          }
        }
      }
    }


    //Send to FX1 Reverb Track D - 4
    if (gridTouchY == MixerPage2_Dynamic_ROW_1) {
      for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
        byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
        if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
          drawPot(mixerRowPos, MixerPage2_Dynamic_ROW_1, plugin[track[MixerRow + 4].MIDIchannel - 16].FX1Volume_graph, plugin[track[MixerRow + 4].MIDIchannel - 16].FX1Volume_rnd, track[MixerRow + 4].trackNames_short[8], ILI9341_RED);
          if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - plugin[track[MixerRow + 4].MIDIchannel - 16].FX1Volume_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            //increase FX volume
            plugin[track[MixerRow + 4].MIDIchannel - 16].FX1Volume_rnd = map(Potentiometer1, 0, 1023, 0, 100);
            plugin[track[MixerRow + 4].MIDIchannel - 16].FX1Volume = plugin[track[MixerRow + 4].MIDIchannel - 16].FX1Volume_rnd / 100.00;
            plugin[track[MixerRow + 4].MIDIchannel - 16].FX1Volume_graph = map(Potentiometer1, 0, 1023, 0, 100);
            FX1pluginVolume(track[MixerRow + 4].MIDIchannel, plugin[track[MixerRow + 4].MIDIchannel - 16].FX1Volume);
          }
        }
      }
    }
    //Send to FX2 Bitcrusher Track 5 - 8
    if (gridTouchY == MixerPage2_Dynamic_ROW_2) {
      for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
        byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
        if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
          drawPot(mixerRowPos, MixerPage2_Dynamic_ROW_2, plugin[track[MixerRow + 4].MIDIchannel - 16].FX2Volume_graph, plugin[track[MixerRow + 4].MIDIchannel - 16].FX2Volume_rnd, track[MixerRow + 4].trackNames_short[8], ILI9341_RED);
          if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - plugin[track[MixerRow + 4].MIDIchannel - 16].FX2Volume_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            //increase FX volume
            plugin[track[MixerRow + 4].MIDIchannel - 16].FX2Volume_rnd = map(Potentiometer1, 0, 1023, 0, 100);
            plugin[track[MixerRow + 4].MIDIchannel - 16].FX2Volume = plugin[track[MixerRow + 4].MIDIchannel - 16].FX2Volume_rnd / 100.00;
            plugin[track[MixerRow + 4].MIDIchannel - 16].FX2Volume_graph = map(Potentiometer1, 0, 1023, 0, 100);
            FX2pluginVolume(track[MixerRow + 4].MIDIchannel, plugin[track[MixerRow + 4].MIDIchannel - 16].FX2Volume);
          }
        }
      }
    }
    //Send to FX3 Delay Track 5 - 8
    if (gridTouchY == MixerPage2_Dynamic_ROW_3) {
      for (byte MixerRow = 0; MixerRow < 4; MixerRow++) {
        byte mixerRowPos = ((MixerRow + 1) * 4) - 1;
        if (gridTouchX == mixerRowPos || gridTouchX == mixerRowPos + 1) {
          drawPot(mixerRowPos, MixerPage2_Dynamic_ROW_3, plugin[track[MixerRow + 4].MIDIchannel - 16].FX3Volume_graph, plugin[track[MixerRow + 4].MIDIchannel - 16].FX3Volume_rnd, track[MixerRow + 4].trackNames_short[MixerRow + 4], ILI9341_RED);
          if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - plugin[track[MixerRow + 4].MIDIchannel - 16].FX3Volume_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen

            //increase FX volume
            plugin[track[MixerRow + 4].MIDIchannel - 16].FX3Volume_rnd = map(Potentiometer1, 0, 1023, 0, 100);
            plugin[track[MixerRow + 4].MIDIchannel - 16].FX3Volume = plugin[track[MixerRow + 4].MIDIchannel - 16].FX3Volume_rnd / 100.00;
            plugin[track[MixerRow + 4].MIDIchannel - 16].FX3Volume_graph = map(Potentiometer1, 0, 1023, 0, 100);
            FX3pluginVolume(track[MixerRow + 4].MIDIchannel, plugin[track[MixerRow + 4].MIDIchannel - 16].FX3Volume);
          }
        }
      }
    }
    if (gridTouchX >= 18) {
        //page selection
        if (gridTouchY >= 3 && gridTouchY <= 4) {
          select_page(MIXER_PAGE_1);
          mixerPage1_Static(0);
        }
        if (gridTouchY >= 5 && gridTouchY <= 6) {
          select_page(MIXER_PAGE_2);
          mixerPage2_Static();

        }
        if (gridTouchY >= 7 && gridTouchY <= 8) {
          select_page(MIXER_PAGE_3);
          mixerPage3_Static();

        }
      }
      if (gridTouchX == 1 || gridTouchX == 2) {

        if (gridTouchY == 5 || gridTouchY == 6) {
          select_page(FX1_PAGE1);
          FX1reverb_static();
        }    
        if (gridTouchY == 8 || gridTouchY == 9) {
          select_page(FX2_PAGE1);
          FX2Bitcrush_static();
        }
      }
  }
}