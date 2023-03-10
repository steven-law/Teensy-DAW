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
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      plpreset[1] = constrain((plpreset[1] + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[1], ILI9341_PURPLE);
      Plugin2_Page_Static();
    }
  }
  if (!button[14]) {
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
      default:  //next taster push brings us back to page 0
        lastPotRow = 0;
    }
  }

  if (ts.touched() || button[15]) {
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin2", 18);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin2", 18);
      }
    }
  }
}
void Plugin2_Page_Static() {
  clearWorkSpace();
  Plugin2_Change();
  drawNrInRect(18, 1, plpreset[1], ILI9341_PURPLE);
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    drawPot(MixerColumn, 0, plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn], plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn], showVOL[MixerColumn], trackColor[desired_instrument]);
    drawPot(MixerColumn, 1, plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn + 4], plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn + 4], showVOL[MixerColumn + 4], trackColor[desired_instrument]);
    drawPot(MixerColumn, 2, plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn + 8], plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn + 8], showVOL[MixerColumn + 8], trackColor[desired_instrument]);
  }
}
void Plugin2_Change() {
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    drummixer1.gain(MixerColumn, (float)(plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn] / 127.00));
    drummixer2.gain(MixerColumn, (float)(plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn + 4] / 127.00));
    drummixer3.gain(MixerColumn, (float)(plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn + 8] / 127.00));
  }
}
