//this is a simple sampleplayer. It reads directly from the sdcard, maybe this is something to change
//about 6-8 samples can be played simultaniously, WHEN WAV-files are Mono and as short as possible (16-bit, 44100Hz)




void NoteFX2_Settings() {
}
void NoteFX2_Control() {
  switch (lastPotRow) {
    case 0:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (NFX2[NFX2presetNr].Pot_Value[MixerColumn] != Potentiometer[MixerColumn]) {
          NFX2[NFX2presetNr].Pot_Value[MixerColumn] = Potentiometer[MixerColumn];
          NFX2[NFX2presetNr].Pot_Value[MixerColumn] = NFX2[NFX2presetNr].Pot_Value[MixerColumn];

          drawPot(MixerColumnPos, lastPotRow, NFX2[NFX2presetNr].Pot_Value[MixerColumn], NFX2[NFX2presetNr].Pot_Value[MixerColumn], NFX2_ROW1[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 1:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4] != Potentiometer[MixerColumn]) {
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4] = Potentiometer[MixerColumn];
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4];

          drawPot(MixerColumnPos, lastPotRow, NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4], NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4], noteNames[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 2:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8] != Potentiometer[MixerColumn]) {
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8] = Potentiometer[MixerColumn];
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8];

          drawPot(MixerColumnPos, lastPotRow, NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8], NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8], noteNames[MixerColumn + 4], trackColor[desired_instrument]);
        }
      }
      break;

    case 3:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12] != Potentiometer[MixerColumn]) {
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12] = Potentiometer[MixerColumn];
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12];

          drawPot(MixerColumnPos, lastPotRow, NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12], NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12], noteNames[MixerColumn + 8], trackColor[desired_instrument]);
        }
      }
      break;
  }
}
void NoteFX2_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      NFX2presetNr = constrain((NFX2presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, NFX2presetNr, trackColor[desired_instrument]);
      NoteFX2_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = NFX2[NFX2presetNr].Pot_Value[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX2[NFX2presetNr].Pot_Value[MixerColumn] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 2:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 3:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
    }
  }
  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        saveNoteFX("NoteFX2", 1);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadNoteFX("NoteFX2", 1);
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
void NoteFX2_Page_Static() {
  clearWorkSpace();
  NoteFX2_Change();
  drawNrInRect(18, 1, NFX2presetNr, ILI9341_PURPLE);
  drawChar(18, 3, seqModes[track[desired_track].seqMode], trackColor[desired_track]);
  for (int touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, 0, NFX2[NFX2presetNr].Pot_Value[touchX - 1], NFX2[NFX2presetNr].Pot_Value[touchX - 1], NFX2_ROW1[touchX - 1], trackColor[desired_instrument]);
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, 1, NFX2[NFX2presetNr].Pot_Value[touchX + 3], NFX2[NFX2presetNr].Pot_Value[touchX + 3], noteNames[touchX - 1], trackColor[desired_instrument]);
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, 2, NFX2[NFX2presetNr].Pot_Value[touchX + 7], NFX2[NFX2presetNr].Pot_Value[touchX + 7], noteNames[touchX + 3], trackColor[desired_instrument]);
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 4 - 1, 3, NFX2[NFX2presetNr].Pot_Value[touchX + 11], NFX2[NFX2presetNr].Pot_Value[touchX + 11], noteNames[touchX + 7], trackColor[desired_instrument]);
  }
}

void NoteFX2_Change() {
  for (int touchX = 1; touchX < 5; touchX++) {

    NFX2[NFX2presetNr].Pot_Value[touchX - 1];
  }
  for (int touchX = 1; touchX < 5; touchX++) {

    NFX2[NFX2presetNr].Pot_Value[touchX + 3];
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    NFX2[NFX2presetNr].Pot_Value[touchX + 7];
  }
  for (int touchX = 1; touchX < 5; touchX++) {
    NFX2[NFX2presetNr].Pot_Value[touchX + 11];
  }
}
