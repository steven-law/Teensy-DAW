//this is a simple sampleplayer. It reads directly from the sdcard, maybe this is something to change
//about 6-8 samples can be played simultaniously, WHEN WAV-files are Mono and as short as possible (16-bit, 44100Hz)
//a possible alternate would be to change to read from memory.
//No problem for a teensy 4.x but maybe in the future for my 3.5.


void Plugin_2_Settings() {


  drummixer4.gain(0, 1);
  drummixer4.gain(1, 1);
  drummixer4.gain(2, 1);
  drummixer4.gain(3, 1);

  pl2amp.gain(1);
  pl2amp2.gain(1);
}
void Plugin2_Page1_Dynamic() {
  change_preset(1);


  if (!button[14] && !button[9]) {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          pl2MIX(1, 0, MixerColumn, lastPotRow);
        }
        break;
      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          pl2MIX(1, 1, MixerColumn, lastPotRow);
        }
        break;
      case 2:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          pl2MIX(1, 2, MixerColumn, lastPotRow);
        }
        break;
      case 3:
        //pl2File(1, 0, 0, 3);
        break;
    }
  }
  if (button[9]) {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          pl2File(1, 0, MixerColumn, lastPotRow);
        }
        break;
      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          pl2File(1, 1, MixerColumn, lastPotRow);
        }
        break;
      case 2:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          pl2File(1, 2, MixerColumn, lastPotRow);
        }
        break;
      case 3:
        //pl2File(1, 0, 0, 3);
        break;
    }
  }

  if (ts.touched() || button[15]) {

    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin2", 1);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin2", 1);
      }
    }
  }
}
void Plugin2_Page_Static() {
  clearWorkSpace();
  Plugin2_Change();
  drawNrInRect(18, 1, plpreset[1], ILI9341_PURPLE);
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

    sprintf(_pl2Filename, "%s%d\0", wavKits[MixerColumn], plugin[1].preset[plpreset[1]].Pot_Value2[MixerColumn]);
    drawPot(MixerColumn, 0, plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn], plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn], _pl2Filename, trackColor[desired_instrument]);

    sprintf(_pl2Filename, "%s%d\0", wavKits[MixerColumn + 4], plugin[1].preset[plpreset[1]].Pot_Value2[MixerColumn + 4]);
    drawPot(MixerColumn, 1, plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn + 4], plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn + 4], _pl2Filename, trackColor[desired_instrument]);

    sprintf(_pl2Filename, "%s%d\0", wavKits[MixerColumn + 8], plugin[1].preset[plpreset[1]].Pot_Value2[MixerColumn + 8]);
    drawPot(MixerColumn, 2, plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn + 8], plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn + 8], _pl2Filename, trackColor[desired_instrument]);
  }
}
void Plugin2_Change() {
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    drummixer1.gain(MixerColumn, (float)(plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn] / 127.00));
    drummixer2.gain(MixerColumn, (float)(plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn + 4] / 127.00));
    drummixer3.gain(MixerColumn, (float)(plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn + 8] / 127.00));
  }
}
//this is a simple sampleplayer. It reads directly from plash memory, maybe this is something to change
//about 6-8 samples can be played simultaniously, WHEN code-files are Mono and as short as possible (16-bit, 44100Hz)

void Plugin_4_Settings() {


  pl4drummixer4.gain(0, 1);
  pl4drummixer4.gain(1, 1);
  pl4drummixer4.gain(2, 1);
  pl4drummixer4.gain(3, 1);

  pl4amp.gain(1);
  pl4amp2.gain(1);
}
void Plugin4_Page1_Dynamic() {
  change_preset(3);

  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          pl4MIX(3, 0, MixerColumn, lastPotRow);
        }
        break;
      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          pl4MIX(3, 1, MixerColumn, lastPotRow);
        }
        break;
      case 2:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          pl4MIX(3, 2, MixerColumn, lastPotRow);
        }
        break;
    }
  }

  if (ts.touched() || button[15]) {
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin4", 3);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin4", 3);
      }
    }
  }
}
void Plugin4_Page_Static() {
  clearWorkSpace();
  Plugin4_Change();
  drawNrInRect(18, 1, plpreset[3], ILI9341_PURPLE);
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    drawPot(MixerColumn, 0, plugin[3].preset[plpreset[3]].Pot_Value[MixerColumn], plugin[3].preset[plpreset[3]].Pot_Value[MixerColumn], showVOL[MixerColumn], trackColor[desired_instrument]);
    drawPot(MixerColumn, 1, plugin[3].preset[plpreset[3]].Pot_Value[MixerColumn + 4], plugin[3].preset[plpreset[3]].Pot_Value[MixerColumn + 4], showVOL[MixerColumn + 4], trackColor[desired_instrument]);
    drawPot(MixerColumn, 2, plugin[3].preset[plpreset[3]].Pot_Value[MixerColumn + 8], plugin[3].preset[plpreset[3]].Pot_Value[MixerColumn + 8], showVOL[MixerColumn + 8], trackColor[desired_instrument]);
  }
}
void Plugin4_Change() {
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    pl4drummixer1.gain(MixerColumn, (float)(plugin[3].preset[plpreset[3]].Pot_Value[MixerColumn] / 127.00));
  }
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    pl4drummixer2.gain(MixerColumn, (float)(plugin[3].preset[plpreset[3]].Pot_Value[MixerColumn + 4] / 127.00));
  }
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    pl4drummixer3.gain(MixerColumn, (float)(plugin[3].preset[plpreset[3]].Pot_Value[MixerColumn + 8] / 127.00));
  }
}

//this is a simple sampleplayer. It reads RAW files directly from the sdcard, maybe this is something to change
//about 6-8 samples can be played simultaniously, WHEN RAW-files are Mono and as short as possible (16-bit, 44100Hz)
//a possible alternate would be to change to read from memory.


void Plugin_11_Settings() {
  pl11mixer5.gain(0, 1);
  pl11mixer5.gain(1, 1);
  pl11mixer5.gain(2, 1);
  pl11mixer5.gain(3, 1);

  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    WAVETABLE[pl11WAVETABLES[MixerColumn]]->setInstrument(Viola);
  }

  pl11amp.gain(1);
  pl11amp2.gain(1);
}
void Plugin11_Page1_Dynamic() {
  change_preset(1);


  if (!button[14] && !button[9]) {
    switch (lastPotRow) {
      case 0:
        WAVETABLE_file(pl11NR, pl11WAVETABLES[0], 0, 0, 0, 4, "Table");
        SVF_frequency(pl11NR, pl11SVF1, 1, 0, 0, 127, "Freq");                //MIN: unused MAX: unused
        SVF_resonance(pl11NR, pl11SVF1, 2, 0, 0, MAX_RESONANCE, "Reso");      //MIN: unused MAX: unused
        SVF_Type(pl11NR, pl11TYPE1, 3, 0, ZERO, 2, "Typ");  //MIN: unused M
        break;
      case 1:
        WAVETABLE_file(pl11NR, pl11WAVETABLES[1], 0, 1, 0, 4, "Table");
        SVF_frequency(pl11NR, pl11SVF2, 1, 1, 0, 127, "Freq");                //MIN: unused MAX: unused
        SVF_resonance(pl11NR, pl11SVF2, 2, 1, 0, MAX_RESONANCE, "Reso");      //MIN: unused MAX: unused
        SVF_Type(pl11NR, pl11TYPE2, 3, 1, ZERO, 2, "Typ");  //MIN: unused M
        break;
      case 2:
        WAVETABLE_file(pl11NR, pl11WAVETABLES[2], 0, 2, 0, 4, "Table");
        SVF_frequency(pl11NR, pl11SVF3, 1, 2, 0, 127, "Freq");                //MIN: unused MAX: unused
        SVF_resonance(pl11NR, pl11SVF3, 2, 2, 0, MAX_RESONANCE, "Reso");      //MIN: unused MAX: unused
        SVF_Type(pl11NR, pl11TYPE3, 3, 2, ZERO, 2, "Typ");  //MIN: unused M
        break;
      case 3:
        WAVETABLE_file(pl11NR, pl11WAVETABLES[3], 0, 3, 0, 4, "Table");
        SVF_frequency(pl11NR, pl11SVF4, 1, 3, 0, 127, "Freq");                //MIN: unused MAX: unused
        SVF_resonance(pl11NR, pl11SVF4, 2, 3, 0, MAX_RESONANCE, "Reso");      //MIN: unused MAX: unused
        SVF_Type(pl11NR, pl11TYPE4, 3, 3, ZERO, 2, "Typ");  //MIN: unused M
        break;
    }
  }
  if (button[9]) {
    switch (lastPotRow) {
      case 0:

        break;
      case 1:

        break;
      case 2:

        break;
      case 3:

        break;
    }
  }

  if (ts.touched() || button[15]) {

    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin11", pl11NR);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin11", pl11NR);
      }
    }
  }
}
void Plugin11_Page_Static() {
  clearWorkSpace();
  Plugin11_Change();
  drawNrInRect(18, 1, plpreset[pl11NR], ILI9341_PURPLE);

  draw_WAVETABLE_file(pl11NR, pl11WAVETABLES[0], 0, 0, 0, 4, "Table");
  draw_SVF_frequency(pl11NR, pl11SVF1, 1, 0, 0, 127, "Freq");                //MIN: unused MAX: unused
  draw_SVF_resonance(pl11NR, pl11SVF1, 2, 0, 0, MAX_RESONANCE, "Reso");      //MIN: unused MAX: unused
  draw_SVF_Type(pl11NR, pl11TYPE1, 3, 0, ZERO, 2, "Typ");  //MIN: unused M

  draw_WAVETABLE_file(pl11NR, pl11WAVETABLES[1], 0, 1, 0, 4, "Table");
  draw_SVF_frequency(pl11NR, pl11SVF2, 1, 1, 0, 127, "Freq");                //MIN: unused MAX: unused
  draw_SVF_resonance(pl11NR, pl11SVF2, 2, 1, 0, MAX_RESONANCE, "Reso");      //MIN: unused MAX: unused
  draw_SVF_Type(pl11NR, pl11TYPE2, 3, 1, ZERO, 2, "Typ");  //MIN: unused M

  draw_WAVETABLE_file(pl11NR, pl11WAVETABLES[2], 0, 2, 0, 4, "Table");
  draw_SVF_frequency(pl11NR, pl11SVF3, 1, 2, 0, 127, "Freq");                //MIN: unused MAX: unused
  draw_SVF_resonance(pl11NR, pl11SVF3, 2, 2, 0, MAX_RESONANCE, "Reso");      //MIN: unused MAX: unused
  draw_SVF_Type(pl11NR, pl11TYPE3, 3, 2, ZERO, 2, "Typ");  //MIN: unused M

  draw_WAVETABLE_file(pl11NR, pl11WAVETABLES[3], 0, 3, 0, 4, "Table");
  draw_SVF_frequency(pl11NR, pl11SVF4, 1, 3, 0, 127, "Freq");                //MIN: unused MAX: unused
  draw_SVF_resonance(pl11NR, pl11SVF4, 2, 3, 0, MAX_RESONANCE, "Reso");      //MIN: unused MAX: unused
  draw_SVF_Type(pl11NR, pl11TYPE4, 3, 3, ZERO, 2, "Typ");  //MIN: unused M
}
void Plugin11_Change() {
  change_WAVETABLE_file(pl11NR, pl11WAVETABLES[0], 0, 0, 0, 4, "Table");
  change_SVF_frequency(pl11NR, pl11SVF1, 1, 0, 0, 127, "Freq");                //MIN: unused MAX: unused
  change_SVF_resonance(pl11NR, pl11SVF1, 2, 0, 0, MAX_RESONANCE, "Reso");      //MIN: unused MAX: unused
  change_SVF_Type(pl11NR, pl11TYPE1, 3, 0, ZERO, 2, "Typ");  //MIN: unused M

  change_WAVETABLE_file(pl11NR, pl11WAVETABLES[1], 0, 1, 0, 4, "Table");
  change_SVF_frequency(pl11NR, pl11SVF2, 1, 1, 0, 127, "Freq");                //MIN: unused MAX: unused
  change_SVF_resonance(pl11NR, pl11SVF2, 2, 1, 0, MAX_RESONANCE, "Reso");      //MIN: unused MAX: unused
  change_SVF_Type(pl11NR, pl11TYPE2, 3, 1, ZERO, 2, "Typ");  //MIN: unused M

  change_WAVETABLE_file(pl11NR, pl11WAVETABLES[2], 0, 2, 0, 4, "Table");
  change_SVF_frequency(pl11NR, pl11SVF3, 1, 2, 0, 127, "Freq");                //MIN: unused MAX: unused
  change_SVF_resonance(pl11NR, pl11SVF3, 2, 2, 0, MAX_RESONANCE, "Reso");      //MIN: unused MAX: unused
  change_SVF_Type(pl11NR, pl11TYPE3, 3, 2, ZERO, 2, "Typ");  //MIN: unused M

  change_WAVETABLE_file(pl11NR, pl11WAVETABLES[3], 0, 3, 0, 4, "Table");
  change_SVF_frequency(pl11NR, pl11SVF4, 1, 3, 0, 127, "Freq");                //MIN: unused MAX: unused
  change_SVF_resonance(pl11NR, pl11SVF4, 2, 3, 0, MAX_RESONANCE, "Reso");      //MIN: unused MAX: unused
  change_SVF_Type(pl11NR, pl11TYPE4, 3, 3, ZERO, 2, "Typ");  //MIN: unused M
}