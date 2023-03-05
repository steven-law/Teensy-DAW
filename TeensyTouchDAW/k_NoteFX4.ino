void NoteFX4_Settings() {
}
void NoteFX4_Control() {
}
void NoteFX4_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      NFX4presetNr = constrain((NFX4presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, NFX4presetNr, trackColor[desired_instrument]);
      NoteFX4_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          
          Potentiometer[MixerColumn] = NFX4[NFX4presetNr].Pot_Value[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn] + encoded[MixerColumn]), 0, NUM_STEPS);
            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn] + encoded[MixerColumn]), 0, NUM_STEPS - 1);
          }
        }
        break;

      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
         
          Potentiometer[MixerColumn] = NFX4[NFX4presetNr].Pot_Value[MixerColumn + 4];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn + 4] + encoded[MixerColumn]), 0, NUM_STEPS);
            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn + 4] + encoded[MixerColumn]), 0, NUM_STEPS - 1);
          }
        }
        break;

      case 2:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
       
          Potentiometer[MixerColumn] = NFX4[NFX4presetNr].Pot_Value[MixerColumn + 8];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn + 8] + encoded[MixerColumn]), 0, NUM_STEPS);
            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn + 8] + encoded[MixerColumn]), 0, NUM_STEPS - 1);
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
        saveNoteFX("NoteFX4", 3);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadNoteFX("NoteFX4", 3);
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
void NoteFX4_Page_Static() {
  clearWorkSpace();
  NoteFX4_Change();
  drawNrInRect(18, 1, NFX4presetNr, ILI9341_PURPLE);
  drawChar(18, 3, seqModes[track[desired_track].seqMode], trackColor[desired_track]);
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    drawPotDrum(MixerColumn, 0, NFX4[NFX4presetNr].Pot_Value[MixerColumn], NFX4[NFX4presetNr].Pot_Value[MixerColumn], drumnote[MixerColumn], trackColor[desired_instrument]);
    drawPotDrum(MixerColumn + 4, 1, NFX4[NFX4presetNr].Pot_Value[MixerColumn + 4], NFX4[NFX4presetNr].Pot_Value[MixerColumn + 4], drumnote[MixerColumn + 4], trackColor[desired_instrument]);
    drawPotDrum(MixerColumn + 8, 2, NFX4[NFX4presetNr].Pot_Value[MixerColumn + 8], NFX4[NFX4presetNr].Pot_Value[MixerColumn + 8], drumnote[MixerColumn + 8], trackColor[desired_instrument]);
  }
}

void NoteFX4_Change() {
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

    NFX4[NFX4presetNr].Pot_Value[MixerColumn];
  }
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

    NFX4[NFX4presetNr].Pot_Value[MixerColumn + 4];
  }
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    NFX4[NFX4presetNr].Pot_Value[MixerColumn + 8];
  }
}
