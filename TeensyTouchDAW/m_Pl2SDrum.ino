//this is a simple sampleplayer. It reads directly from the sdcard, maybe this is something to change
//about 6-8 samples can be played simultaniously, WHEN WAV-files are Mono and as short as possible (16-bit, 44100Hz)
//a possible alternate would be to change to read from memory.
//No problem for a teensy 4.x but maybe in the future for my 3.5.


void Plugin_2_Settings() {
  drummixer1.gain(0, 1);
  drummixer1.gain(1, 1);
  drummixer1.gain(2, 1);
  drummixer1.gain(3, 1);

  drummixer2.gain(0, 1);
  drummixer2.gain(1, 1);
  drummixer2.gain(2, 1);
  drummixer2.gain(3, 1);

  drummixer3.gain(0, 1);
  drummixer3.gain(1, 1);
  drummixer3.gain(2, 1);
  drummixer3.gain(3, 1);

  drummixer4.gain(0, 1);
  drummixer4.gain(1, 1);
  drummixer4.gain(2, 1);
  drummixer4.gain(3, 1);

  pl2amp.gain(1);
  pl2amp2.gain(1);
}
void Plugin2_Control() {
  switch (lastPotRow) {
    case 0:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (pl2[pl2presetNr].Pot_Value_graph[MixerColumn] != Potentiometer[MixerColumn]) {
          pl2[pl2presetNr].Pot_Value_graph[MixerColumn] = Potentiometer[MixerColumn];
          pl2[pl2presetNr].Pot_Value[MixerColumn] = pl2[pl2presetNr].Pot_Value_graph[MixerColumn] / 127.00;
          drummixer1.gain(MixerColumn, pl2[pl2presetNr].Pot_Value[MixerColumn]);
          drawPot(MixerColumnPos, CTRL_ROW_0, pl2[pl2presetNr].Pot_Value_graph[MixerColumn], pl2[pl2presetNr].Pot_Value_graph[MixerColumn], showVOL[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 1:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (pl2[pl2presetNr].Pot_Value_graph[MixerColumn + 4] != Potentiometer[MixerColumn]) {
          pl2[pl2presetNr].Pot_Value_graph[MixerColumn + 4] = Potentiometer[MixerColumn];
          pl2[pl2presetNr].Pot_Value[MixerColumn + 4] = pl2[pl2presetNr].Pot_Value_graph[MixerColumn + 4] / 127.00;
          drummixer2.gain(MixerColumn, pl2[pl2presetNr].Pot_Value[MixerColumn + 4]);
          drawPot(MixerColumnPos, CTRL_ROW_1, pl2[pl2presetNr].Pot_Value_graph[MixerColumn + 4], pl2[pl2presetNr].Pot_Value_graph[MixerColumn + 4], showVOL[MixerColumn + 4], trackColor[desired_instrument]);
        }
      }
      break;

    case 2:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (pl2[pl2presetNr].Pot_Value_graph[MixerColumn + 8] != Potentiometer[MixerColumn]) {
          pl2[pl2presetNr].Pot_Value_graph[MixerColumn + 8] = Potentiometer[MixerColumn];
          pl2[pl2presetNr].Pot_Value[MixerColumn + 8] = pl2[pl2presetNr].Pot_Value_graph[MixerColumn + 8] / 127.00;
          drummixer3.gain(MixerColumn, pl2[pl2presetNr].Pot_Value[MixerColumn + 8]);
          drawPot(MixerColumnPos, CTRL_ROW_2, pl2[pl2presetNr].Pot_Value_graph[MixerColumn + 8], pl2[pl2presetNr].Pot_Value_graph[MixerColumn + 8], showVOL[MixerColumn + 8], trackColor[desired_instrument]);
        }
      }
      break;

    case 3:
      break;
  }
}
void Plugin2_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      pl2presetNr = constrain((pl2presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, pl2presetNr, ILI9341_PURPLE);
      Plugin2_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = pl2[pl2presetNr].Pot_Value_graph[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((pl2[pl2presetNr].Pot_Value_graph[MixerColumn] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;

      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = pl2[pl2presetNr].Pot_Value_graph[MixerColumn + 4];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((pl2[pl2presetNr].Pot_Value_graph[MixerColumn + 4] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;

      case 2:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = pl2[pl2presetNr].Pot_Value_graph[MixerColumn + 8];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((pl2[pl2presetNr].Pot_Value_graph[MixerColumn + 8] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;

      case 3:
        break;
    }
  }
  TS_Point p = ts.getPoint();
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
  }
}
void Plugin2_Page_Static() {
  clearWorkSpace();
  Plugin2_Change();
  drawNrInRect(18, 1, pl2presetNr, ILI9341_PURPLE);
  for (int touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, CTRL_ROW_0, pl2[pl2presetNr].Pot_Value_graph[touchX - 1], pl2[pl2presetNr].Pot_Value_graph[touchX - 1], showVOL[touchX - 1], trackColor[desired_instrument]);
    drawPot(touchX * 4 - 1, CTRL_ROW_1, pl2[pl2presetNr].Pot_Value_graph[touchX + 3], pl2[pl2presetNr].Pot_Value_graph[touchX + 3], showVOL[touchX + 3], trackColor[desired_instrument]);
    drawPot(touchX * 4 - 1, CTRL_ROW_2, pl2[pl2presetNr].Pot_Value_graph[touchX + 7], pl2[pl2presetNr].Pot_Value_graph[touchX + 7], showVOL[touchX + 7], trackColor[desired_instrument]);
  }
}
void Plugin2_Change() {
  for (int touchX = 1; touchX < 5; touchX++) {
    drummixer1.gain(touchX - 1, pl2[pl2presetNr].Pot_Value[touchX - 1]);
    drummixer2.gain(touchX - 1, pl2[pl2presetNr].Pot_Value[touchX + 3]);
    drummixer3.gain(touchX - 1, pl2[pl2presetNr].Pot_Value[touchX + 7]);
  }
}


