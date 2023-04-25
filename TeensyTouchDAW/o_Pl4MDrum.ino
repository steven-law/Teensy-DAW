//this is a simple sampleplayer. It reads directly from the sdcard, maybe this is something to change
//about 6-8 samples can be played simultaniously, WHEN WAV-files are Mono and as short as possible (16-bit, 44100Hz)

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
