//small 4Osc chord synthvoice, select the note-offsets from your played note (equal to set your chord), change gain for the 4 osc´s
//toDo: change waveform, add pw control



void Plugin_1_Settings() {
  pl1waveform1.begin(WAVEFORM_SAWTOOTH);
  pl1waveform1.amplitude(1);
  pl1waveform1.frequency(note_frequency[36]);
  pl1waveform1.pulseWidth(0.15);

  pl1waveformMod1.begin(WAVEFORM_SAWTOOTH);
  pl1waveformMod1.amplitude(1);
  pl1waveformMod1.frequency(note_frequency[36]);
  //pl1waveformMod1.pulseWidth(0.15);

  pl1waveformMod2.begin(WAVEFORM_SAWTOOTH);
  pl1waveformMod2.amplitude(1);
  pl1waveformMod2.frequency(note_frequency[36]);
  //pl1waveformMod2.pulseWidth(0.15);

  pl1waveformMod3.begin(WAVEFORM_SAWTOOTH);
  pl1waveformMod3.amplitude(1);
  pl1waveformMod3.frequency(note_frequency[36]);
  //pl1waveformMod3.pulseWidth(0.15);

  pl1waveformMod4.begin(WAVEFORM_SAWTOOTH);
  pl1waveformMod4.amplitude(1);
  pl1waveformMod4.frequency(note_frequency[36]);
  //pl1waveformMod4.pulseWidth(0.15);

  mixer1.gain(0, 1);
  mixer1.gain(1, 1);
  mixer1.gain(2, 1);
  mixer1.gain(3, 1);



  pl1mixer2.gain(0, 1);
  pl1mixer2.gain(1, 0);
  pl1mixer2.gain(2, 0);
  pl1mixer2.gain(3, 0);

  envelope1.delay(0);
  envelope1.hold(0);
  envelope1.sustain(0.8);


  pl1dc1.amplitude(1);
  envelope2.delay(0);
  envelope2.hold(0);
  envelope2.sustain(0.8);


  pl1amp.gain(1);
  pl1amp2.gain(1);
}
void Plugin1_Control() {


  switch (lastPotRow) {
    case 0:
      //1 Row 1 note Offset
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        if (plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[MixerColumn] != Potentiometer[MixerColumn]) {
          plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[MixerColumn] = Potentiometer[MixerColumn];
          drawPot(MixerColumn, lastPotRow, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[MixerColumn], map(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[MixerColumn], 0, 127, -18, 18), "Offset", trackColor[desired_instrument]);
        }
      }
      break;
  }
}

void Plugin1_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      plpreset[pl1NR] = constrain((plpreset[pl1NR] + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[pl1NR], ILI9341_PURPLE);
      Plugin1_Page_Static(0);
    }
  }

  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //1 Row 1 note Offset
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          Encoder2_to_4x127(0, MixerColumn, lastPotRow);
        }
        break;
      case 1:
        //1 Row 2 Waveform
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          OSC_MOD_Waveform(pl1NR, MixerColumn, MixerColumn, lastPotRow);  //pluginNr, pointerarrayPos, column, row
        }
        break;
      case 2:
        //1 Row 2 note Velocity
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          OSC_MOD_LVL(pl1NR, MixerColumn, MixerColumn, lastPotRow);  //pluginNr, pointerarrayPos, column, row
        }
        break;
      case 3:
        OSC_ModRate(pl1NR, pl1OSC, 0, lastPotRow, 15);  //pluginNr, pointerarrayPos, column, row, max freq
        OSC_LVL(pl1NR, pl1OSC, 1, lastPotRow, 4048.00);          //pluginNr, pointerarrayPos, column, row
        OSC_Waveform(pl1NR, pl1OSC, 2, lastPotRow);     //pluginNr, pointerarrayPos, column, row
        break;
    }
  }
  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {

    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin1", 17);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin1", 17);
      }
    }
    //change preset
    if (gridTouchX >= 18 && gridTouchY == 1) {
      /* drawNrInRect(18, 1, plpreset[pl1NR], ILI9341_PURPLE);
      if ((abs(map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1) - plpreset[pl1NR]) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        plpreset[pl1NR] = map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1);
      }*/
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




    //page selection
    if (gridTouchX >= 18) {
      //page1
      if (gridTouchY == 3 || gridTouchY == 4) {
        selectPage = PLUGIN1_PAGE1;
        Plugin_View_Static();
      }
      //page2
      if (gridTouchY == 5 || gridTouchY == 6) {
        selectPage = PLUGIN1_PAGE2;
        Plugin_View_Static();
      }
      /*
      //page3
      if (gridTouchY == 7 || gridTouchY == 8) {
        selectPage = PLUGIN1_PAGE3;
        Plugin_View_Static();
      }
      //page4
      if (gridTouchY == 9 || gridTouchY == 10) {
        selectPage = PLUGIN1_PAGE4;
        Plugin_View_Static();
      }*/
    }
  }
}
void Plugin1_Page2_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      plpreset[pl1NR] = constrain((plpreset[pl1NR] + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[pl1NR], ILI9341_PURPLE);
      Plugin1_Page_Static(1);
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        StateVar_Filter(pl1NR, pl1SVF, 0, lastPotRow);
        break;
      case 1:
        ADSR(pl1NR, pl1ADSR1, 0, lastPotRow, 0);
        ADSR(pl1NR, pl1ADSR2, 0, lastPotRow, 1);
        break;
    }
  }

  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {


    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin1", 17);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin1", 17);
      }
    }




    //page selection
    if (gridTouchX >= 18) {
      //page1
      if (gridTouchY == 3 || gridTouchY == 4) {
        selectPage = PLUGIN1_PAGE1;
        Plugin_View_Static();
      }
      //page2
      if (gridTouchY == 5 || gridTouchY == 6) {
        selectPage = PLUGIN1_PAGE2;
        Plugin_View_Static();
      }
      /*
      //page3
      if (gridTouchY == 7 || gridTouchY == 8) {
        selectPage = PLUGIN1_PAGE3;
        Plugin_View_Static();
      }
      //page4
      if (gridTouchY == 9 || gridTouchY == 10) {
        selectPage = PLUGIN1_PAGE4;
        Plugin_View_Static();
      }*/
    }
  }
}
void Plugin1_Page_Static(int Pagenumber) {
  clearWorkSpace();
  Plugin1_Change();
  //draw selecting pages buttons
  draw_sub_page_buttons(2);
  drawNrInRect(18, 1, plpreset[pl1NR], ILI9341_PURPLE);
  if (Pagenumber == 0) {
    for (int voice = 0; voice < 4; voice++) {

      drawPot(voice, 0, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[voice], plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[voice], "Offset", trackColor[desired_instrument]);
      drawPot(voice, 1, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[voice], plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[voice + 4] / 10, "W~F", trackColor[desired_instrument]);
      drawPot(voice, 2, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[voice], plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[voice + 8], "Vel", trackColor[desired_instrument]);
    }
    drawPot(1, 3, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[2], plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[1], "LVL", trackColor[desired_track]);
    drawPot(0, 3, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[1], plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[2], "ModRate", trackColor[desired_track]);
    drawPot(2, 3, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[3] * 10, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[3], "W~F", trackColor[desired_track]);
  }
  if (Pagenumber == 1) {
    drawPot(0, 0, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[0], note_frequency[plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[0]], "Freq", trackColor[desired_instrument]);
    drawPot(1, 0, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[1], plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[1], "Reso", trackColor[desired_instrument]);
    drawPot(2, 0, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[2], plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[2], "Swp", trackColor[desired_instrument]);
    drawPot(3, 0, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[3] * SVF_TYP, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[3], "", trackColor[desired_track]);
    drawChar(CTRL_COL_3, 4, filterType[plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[3]], ILI9341_WHITE);
    drawPot(0, 1, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[4], map(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[4], 0, 127, 0, ATTACK_TIME), "Atck", trackColor[desired_instrument]);
    drawPot(1, 1, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[5], map(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[5], 0, 127, 0, DECAY_TIME), "Dec", trackColor[desired_track]);
    drawPot(2, 1, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[6], plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[6], "Sus", trackColor[desired_track]);
    drawPot(3, 1, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[7], map(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[7], 0, 127, 0, RELEASE_TIME), "Rel", trackColor[desired_instrument]);
  }
}
void Plugin1_Change() {
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[MixerColumn];
    OSC_MOD[MixerColumn]->begin(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[MixerColumn + 4] / 10);
    mixer1.gain(0, (float)(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[MixerColumn + 8] / 127.00));
  }

  filter1.frequency(note_frequency[plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[0]]);
  filter1.resonance((float)(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[1] / SVF_RES));
  filter1.octaveControl((float)(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[2] / SVF_SWP));
  selectFilterType(17, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[3]);
  envelope1.attack(map(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[4], 0, 127, 0, ATTACK_TIME));
  envelope2.attack(map(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[4], 0, 127, 0, ATTACK_TIME));
  envelope1.decay(map(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[5], 0, 127, 0, DECAY_TIME));
  envelope2.decay(map(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[5], 0, 127, 0, DECAY_TIME));
  envelope1.sustain((float)(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[6] / SUSTAIN_LVL));
  envelope2.sustain((float)(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[6] / SUSTAIN_LVL));
  envelope1.release(map(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[7], 0, 127, 0, RELEASE_TIME));
  envelope2.release(map(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[7], 0, 127, 0, RELEASE_TIME));
}
