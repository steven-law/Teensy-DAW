//this is a simple sampleplayer. It reads directly from the sdcard, maybe this is something to change
//about 6-8 samples can be played simultaniously, WHEN WAV-files are Mono and as short as possible (16-bit, 44100Hz)

void Plugin_4_Settings() {
  pl4drummixer1.gain(0, 1);
  pl4drummixer1.gain(1, 1);
  pl4drummixer1.gain(2, 1);
  pl4drummixer1.gain(3, 1);

  pl4drummixer2.gain(0, 1);
  pl4drummixer2.gain(1, 1);
  pl4drummixer2.gain(2, 1);
  pl4drummixer2.gain(3, 1);

  pl4drummixer3.gain(0, 1);
  pl4drummixer3.gain(1, 1);
  pl4drummixer3.gain(2, 1);
  pl4drummixer3.gain(3, 1);

  pl4drummixer4.gain(0, 1);
  pl4drummixer4.gain(1, 1);
  pl4drummixer4.gain(2, 1);
  pl4drummixer4.gain(3, 1);

  pl4amp.gain(1);
  pl4amp2.gain(1);
}
void Plugin4_Control() {
  switch (lastPotRow) {
    case 0:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (pl4[pl4presetNr].Pot_Value_graph[MixerColumn] != Potentiometer[MixerColumn]) {
          pl4[pl4presetNr].Pot_Value_graph[MixerColumn] = Potentiometer[MixerColumn];
          pl4[pl4presetNr].Pot_Value[MixerColumn] = pl4[pl4presetNr].Pot_Value_graph[MixerColumn] / 127.00;
          pl4drummixer1.gain(MixerColumn, pl4[pl4presetNr].Pot_Value[MixerColumn]);
          drawPot(MixerColumnPos, CTRL_ROW_0, pl4[pl4presetNr].Pot_Value_graph[MixerColumn], pl4[pl4presetNr].Pot_Value_graph[MixerColumn], showVOL[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 1:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (pl4[pl4presetNr].Pot_Value_graph[MixerColumn + 4] != Potentiometer[MixerColumn]) {
          pl4[pl4presetNr].Pot_Value_graph[MixerColumn + 4] = Potentiometer[MixerColumn];
          pl4[pl4presetNr].Pot_Value[MixerColumn + 4] = pl4[pl4presetNr].Pot_Value_graph[MixerColumn + 4] / 127.00;
          pl4drummixer2.gain(MixerColumn, pl4[pl4presetNr].Pot_Value[MixerColumn + 4]);
          drawPot(MixerColumnPos, CTRL_ROW_1, pl4[pl4presetNr].Pot_Value_graph[MixerColumn + 4], pl4[pl4presetNr].Pot_Value_graph[MixerColumn + 4], showVOL[MixerColumn + 4], trackColor[desired_instrument]);
        }
      }
      break;

    case 2:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (pl4[pl4presetNr].Pot_Value_graph[MixerColumn + 8] != Potentiometer[MixerColumn]) {
          pl4[pl4presetNr].Pot_Value_graph[MixerColumn + 8] = Potentiometer[MixerColumn];
          pl4[pl4presetNr].Pot_Value[MixerColumn + 8] = pl4[pl4presetNr].Pot_Value_graph[MixerColumn + 8] / 127.00;
          pl4drummixer3.gain(MixerColumn, pl4[pl4presetNr].Pot_Value[MixerColumn + 8]);
          drawPot(MixerColumnPos, CTRL_ROW_2, pl4[pl4presetNr].Pot_Value_graph[MixerColumn + 8], pl4[pl4presetNr].Pot_Value_graph[MixerColumn + 8], showVOL[MixerColumn + 8], trackColor[desired_instrument]);
        }
      }
      break;

    case 3:
      break;
  }
}
void Plugin4_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      pl4presetNr = constrain((pl4presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, pl4presetNr, ILI9341_PURPLE);
      Plugin4_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = pl4[pl4presetNr].Pot_Value_graph[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((pl4[pl4presetNr].Pot_Value_graph[MixerColumn] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;

      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = pl4[pl4presetNr].Pot_Value_graph[MixerColumn + 4];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((pl4[pl4presetNr].Pot_Value_graph[MixerColumn + 4] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;

      case 2:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = pl4[pl4presetNr].Pot_Value_graph[MixerColumn + 8];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((pl4[pl4presetNr].Pot_Value_graph[MixerColumn + 8] + encoded[MixerColumn]), 0, 127);
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
        savePlugin("plugin4", 20);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin4", 20);
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
void Plugin4_Page_Static() {
  clearWorkSpace();
  Plugin4_Change();
  drawNrInRect(18, 1, pl4presetNr, ILI9341_PURPLE);
  for (int touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, CTRL_ROW_0, pl4[pl4presetNr].Pot_Value_graph[touchX - 1], pl4[pl4presetNr].Pot_Value_graph[touchX - 1], showVOL[touchX - 1], trackColor[desired_instrument]);
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, CTRL_ROW_1, pl4[pl4presetNr].Pot_Value_graph[touchX + 3], pl4[pl4presetNr].Pot_Value_graph[touchX + 3], showVOL[touchX + 3], trackColor[desired_instrument]);
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, CTRL_ROW_2, pl4[pl4presetNr].Pot_Value_graph[touchX + 7], pl4[pl4presetNr].Pot_Value_graph[touchX + 7], showVOL[touchX + 7], trackColor[desired_instrument]);
  }
}

void Plugin4_Change() {
  for (int touchX = 1; touchX < 5; touchX++) {
    pl4drummixer1.gain(touchX - 1, pl4[pl4presetNr].Pot_Value[touchX - 1]);
    pl4[pl4presetNr].Pot_Value_graph[touchX - 1];
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    pl4drummixer2.gain(touchX - 1, pl4[pl4presetNr].Pot_Value[touchX + 3]);
    pl4[pl4presetNr].Pot_Value_graph[touchX + 3];
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    pl4drummixer3.gain(touchX - 1, pl4[pl4presetNr].Pot_Value[touchX + 7]);
  }
}
