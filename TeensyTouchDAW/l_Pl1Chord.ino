//small 4Osc chord synthvoice, select the note-offsets from your played note (equal to set your chord), change gain for the 4 osc´s
//toDo: change waveform, add pw control



void Plugin_1_Settings() {
  pl1waveform1.begin(WAVEFORM_SAWTOOTH);
  pl1waveform1.amplitude(1);
  pl1waveform1.frequency(note_frequency[36] * tuning);
  pl1waveform1.pulseWidth(0.15);

  pl1waveformMod1.begin(WAVEFORM_SAWTOOTH);
  pl1waveformMod1.amplitude(1);
  pl1waveformMod1.frequency(note_frequency[36] * tuning);
  //pl1waveformMod1.pulseWidth(0.15);

  pl1waveformMod2.begin(WAVEFORM_SAWTOOTH);
  pl1waveformMod2.amplitude(1);
  pl1waveformMod2.frequency(note_frequency[36] * tuning);
  //pl1waveformMod2.pulseWidth(0.15);

  pl1waveformMod3.begin(WAVEFORM_SAWTOOTH);
  pl1waveformMod3.amplitude(1);
  pl1waveformMod3.frequency(note_frequency[36] * tuning);
  //pl1waveformMod3.pulseWidth(0.15);

  pl1waveformMod4.begin(WAVEFORM_SAWTOOTH);
  pl1waveformMod4.amplitude(1);
  pl1waveformMod4.frequency(note_frequency[36] * tuning);
  //pl1waveformMod4.pulseWidth(0.15);

  mixer1.gain(0, 1);
  mixer1.gain(1, 1);
  mixer1.gain(2, 1);
  mixer1.gain(3, 1);

  filter1.octaveControl(6);

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
        OSC_MOD_Waveform(pl1NR, 0, 0, 1, 0, OSC_MOD_MAX_WF, "W~F");  //pluginNr, pointerarrayPos, column, row
        OSC_MOD_Waveform(pl1NR, 1, 1, 1, 0, OSC_MOD_MAX_WF, "W~F");  //pluginNr, pointerarrayPos, column, row
        OSC_MOD_Waveform(pl1NR, 2, 2, 1, 0, OSC_MOD_MAX_WF, "W~F");  //pluginNr, pointerarrayPos, column, row
        OSC_MOD_Waveform(pl1NR, 3, 3, 1, 0, OSC_MOD_MAX_WF, "W~F");  //pluginNr, pointerarrayPos, column, row
        break;
      case 2:
        //1 Row 2 note Velocity

        OSC_MOD_amplitude(pl1NR, 0, 0, 2, 0, GAIN_MULT_1, "Vol");  //pluginNr, pointerarrayPos, column, row
        OSC_MOD_amplitude(pl1NR, 1, 1, 2, 0, GAIN_MULT_1, "Vol");
        OSC_MOD_amplitude(pl1NR, 2, 2, 2, 0, GAIN_MULT_1, "Vol");
        OSC_MOD_amplitude(pl1NR, 3, 3, 2, 0, GAIN_MULT_1, "Vol");

        break;
      case 3:
        OSC_frequency(pl1NR, pl1OSC, 0, 3, 0, 15.00, "LFO");         //pluginNr, pointerarrayPos, column, row, max freq
        OSC_amplitude(pl1NR, pl1OSC, 1, 3, 0, GAIN_DIV_32, "Amnt");  //pluginNr, pointerarrayPos, column, row
        OSC_Waveform(pl1NR, pl1OSC, 2, 3, 0, 8, "W~F");              //pluginNr, pointerarrayPos, column, row
        break;
    }
  }

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
        SVF_frequency(pl1NR, pl1SVF, 0, 0, 0, 127, "Freq");            //MIN: unused MAX: unused
        SVF_resonance(pl1NR, pl1SVF, 1, 0, 0, MAX_RESONANCE, "Reso");  //MIN: unused MAX: unused
        DC_amplitude(pl1NR, pl1DC1, 2, 0, 0, 1.00, "Swp");             //MIN: unused MAX: amplitude
        SVF_Type(pl1NR, pl1SVF, 3, 0, 0, 2, "");                       //MIN: unused MAX: unused
        break;
      case 1:
        ENV_ADSR(pl1NR, pl1ADSR1, 0, 1, ATTACK_TIME, RELEASE_TIME, "");
        ENV_ADSR(pl1NR, pl1ADSR2, 0, 1, ATTACK_TIME, RELEASE_TIME, "");
        break;
    }
  }


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
      drawPot(voice, 1, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[voice], plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[voice + 4], "W~F", trackColor[desired_instrument]);
      drawPot(voice, 2, plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[voice], plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[voice + 8], "Vol", trackColor[desired_instrument]);
    }
    draw_OSC_frequency(pl1NR, pl1OSC, 0, 3, 0, 15.00, "LFO");     //pluginNr, pointerarrayPos, column, row, max freq
    draw_OSC_amplitude(pl1NR, pl1OSC, 1, 3, 0, 4048.00, "Amnt");  //pluginNr, pointerarrayPos, column, row
    draw_OSC_Waveform(pl1NR, pl1OSC, 2, 3, 0, 8, "W~F");          //pluginNr, pointerarrayPos, column, row
  }
  if (Pagenumber == 1) {
    draw_SVF_frequency(pl1NR, pl1SVF, 0, 0, 0, 127, "Freq");            //MIN: unused MAX: unused
    draw_SVF_resonance(pl1NR, pl1SVF, 1, 0, 0, MAX_RESONANCE, "Reso");  //MIN: unused MAX: unused
    draw_DC_amplitude(pl1NR, pl1DC1, 2, 0, 0, 1.00, "Swp");             //MIN: unused MAX: amplitude
    draw_SVF_Type(pl1NR, pl1SVF, 3, 0, 0, 2, "");                       //MIN: unused MAX: unused

    draw_ENV_ADSR(pl1NR, pl1ADSR1, 0, 1, ATTACK_TIME, RELEASE_TIME, "");
    draw_ENV_ADSR(pl1NR, pl1ADSR2, 0, 1, ATTACK_TIME, RELEASE_TIME, "");
  }
}
void Plugin1_Change() {
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[MixerColumn];
    OSC_MOD[MixerColumn]->begin(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[MixerColumn + 4] / 10);
    mixer1.gain(0, (float)(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[MixerColumn + 8] / 127.00));
  }

  change_SVF_frequency(pl1NR, pl1SVF, 0, 0, 0, 127, "Freq");            //MIN: unused MAX: unused
  change_SVF_resonance(pl1NR, pl1SVF, 1, 0, 0, MAX_RESONANCE, "Reso");  //MIN: unused MAX: unused
  change_DC_amplitude(pl1NR, pl1DC1, 2, 0, 0, 1.00, "Swp");             //MIN: unused MAX: amplitude
  change_SVF_Type(pl1NR, pl1SVF, 3, 0, 0, 2, "");                       //MIN: unused MAX: unused

  change_ENV_ADSR(pl1NR, pl1ADSR1, 0, 1, ATTACK_TIME, RELEASE_TIME, "");
  change_ENV_ADSR(pl1NR, pl1ADSR2, 0, 1, ATTACK_TIME, RELEASE_TIME, "");
}
