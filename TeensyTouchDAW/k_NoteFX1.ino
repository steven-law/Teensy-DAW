//this is a simple sampleplayer. It reads directly from the sdcard, maybe this is something to change
//about 6-8 samples can be played simultaniously, WHEN WAV-files are Mono and as short as possible (16-bit, 44100Hz)




void NoteFX1_Settings() {
}
void NoteFX1_Control() {
  switch (lastPotRow) {
    case 0:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
       
        if (NFX1[NFX1presetNr].Pot_Value[MixerColumn] != Potentiometer[MixerColumn]) {
          NFX1[NFX1presetNr].Pot_Value[MixerColumn] = Potentiometer[MixerColumn];
          drawPotDrum(MixerColumn, lastPotRow, NFX1[NFX1presetNr].Pot_Value[MixerColumn], NFX1[NFX1presetNr].Pot_Value[MixerColumn], drumnote[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 1:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
       
        if (NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4] != Potentiometer[MixerColumn]) {
          NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4] = Potentiometer[MixerColumn];
          drawPotDrum(MixerColumn, lastPotRow, NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4], NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4], drumnote[MixerColumn + 4], trackColor[desired_instrument]);
        }
      }
      break;

    case 2:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
       
        if (NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8] != Potentiometer[MixerColumn]) {
          NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8] = Potentiometer[MixerColumn];
          drawPotDrum(MixerColumn, lastPotRow, NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8], NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8], drumnote[MixerColumn + 8], trackColor[desired_instrument]);
        }
      }
      break;
    case 3:
      break;
  }
}
void NoteFX1_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      NFX1presetNr = constrain((NFX1presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, NFX1presetNr, trackColor[desired_instrument]);
      NoteFX1_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
         
          Potentiometer[MixerColumn] = NFX1[NFX1presetNr].Pot_Value[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX1[NFX1presetNr].Pot_Value[MixerColumn] + encoded[MixerColumn]), 0, BEAT_ARRAY_SIZE);
          }
        }
        break;

      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
         
          Potentiometer[MixerColumn] = NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4] + encoded[MixerColumn]), 0, BEAT_ARRAY_SIZE);
          }
        }
        break;

      case 2:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
         
          Potentiometer[MixerColumn] = NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8] + encoded[MixerColumn]), 0, BEAT_ARRAY_SIZE);
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
        saveNoteFX("NoteFX1", 0);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadNoteFX("NoteFX1", 0);
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
void NoteFX1_Page_Static() {
  clearWorkSpace();
  NoteFX1_Change();
  drawNrInRect(18, 1, NFX1presetNr, ILI9341_PURPLE);
  drawChar(18, 3, seqModes[track[desired_track].seqMode], trackColor[desired_track]);
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    drawPotDrum(MixerColumn, 0, NFX1[NFX1presetNr].Pot_Value[MixerColumn], NFX1[NFX1presetNr].Pot_Value[MixerColumn], drumnote[MixerColumn], trackColor[desired_instrument]);
  
    drawPotDrum(MixerColumn, 1, NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4], NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4], drumnote[MixerColumn + 4], trackColor[desired_instrument]);
 
    drawPotDrum(MixerColumn, 2, NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8], NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8], drumnote[MixerColumn + 8], trackColor[desired_instrument]);
  }
}

void NoteFX1_Change() {
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

    NFX1[NFX1presetNr].Pot_Value[MixerColumn];
  }
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

    NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4];
  }
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8];
  }
}



