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
  draw_SeqMode();
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

void NoteFX2_Settings() {
}
void NoteFX2_Control() {
  switch (lastPotRow) {
    case 0:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX2[NFX2presetNr].Pot_Value[MixerColumn] != Potentiometer[MixerColumn]) {
          NFX2[NFX2presetNr].Pot_Value[MixerColumn] = Potentiometer[MixerColumn];
          NFX2[NFX2presetNr].Pot_Value[MixerColumn] = NFX2[NFX2presetNr].Pot_Value[MixerColumn];

          drawPot(MixerColumn, lastPotRow, NFX2[NFX2presetNr].Pot_Value[MixerColumn], NFX2[NFX2presetNr].Pot_Value[MixerColumn], NFX2_ROW1[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 1:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4] != Potentiometer[MixerColumn]) {
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4] = Potentiometer[MixerColumn];
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4];

          drawPot(MixerColumn, lastPotRow, NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4], NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4], noteNames[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 2:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8] != Potentiometer[MixerColumn]) {
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8] = Potentiometer[MixerColumn];
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8];

          drawPot(MixerColumn, lastPotRow, NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8], NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8], noteNames[MixerColumn + 4], trackColor[desired_instrument]);
        }
      }
      break;

    case 3:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12] != Potentiometer[MixerColumn]) {
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12] = Potentiometer[MixerColumn];
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12];

          drawPot(MixerColumn, lastPotRow, NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12], NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12], noteNames[MixerColumn + 8], trackColor[desired_instrument]);
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

          Potentiometer[MixerColumn] = NFX2[NFX2presetNr].Pot_Value[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX2[NFX2presetNr].Pot_Value[MixerColumn] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 2:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 3:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

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
  draw_SeqMode();
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    drawPot(MixerColumn, 0, NFX2[NFX2presetNr].Pot_Value[MixerColumn], NFX2[NFX2presetNr].Pot_Value[MixerColumn], NFX2_ROW1[MixerColumn], trackColor[desired_instrument]);

    drawPot(MixerColumn, 1, NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4], NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4], noteNames[MixerColumn], trackColor[desired_instrument]);
    drawPot(MixerColumn, 2, NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8], NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8], noteNames[MixerColumn + 4], trackColor[desired_instrument]);

    drawPot(MixerColumn, 3, NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12], NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12], noteNames[MixerColumn + 8], trackColor[desired_instrument]);
  }
}

void NoteFX2_Change() {
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    NFX2[NFX2presetNr].Pot_Value[MixerColumn];
    NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4];
    NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8];
    NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12];
  }
}

void NoteFX3_Settings() {
}
void NoteFX3_Control() {
  switch (lastPotRow) {
    case 0:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX3[NFX3presetNr].Pot_Value[MixerColumn] != Potentiometer[MixerColumn]) {
          NFX3[NFX3presetNr].Pot_Value[MixerColumn] = Potentiometer[MixerColumn];
          NFX3[NFX3presetNr].Pot_Value[MixerColumn] = NFX3[NFX3presetNr].Pot_Value[MixerColumn];

          drawPot(MixerColumn, lastPotRow, NFX3[NFX3presetNr].Pot_Value[MixerColumn], NFX3[NFX3presetNr].Pot_Value[MixerColumn], NFX3_ROW1[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 1:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4] != Potentiometer[MixerColumn]) {
          NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4] = Potentiometer[MixerColumn];
          NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4] = NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4];

          drawPot(MixerColumn, lastPotRow, NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4], NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 2:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8] != Potentiometer[MixerColumn]) {
          NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8] = Potentiometer[MixerColumn];
          NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8] = NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8];

          drawPot(MixerColumn, lastPotRow, NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8], NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 3:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12] != Potentiometer[MixerColumn]) {
          NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12] = Potentiometer[MixerColumn];
          NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12] = NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12];

          drawPot(MixerColumn, lastPotRow, NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12], NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;
  }
}
void NoteFX3_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      NFX3presetNr = constrain((NFX3presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, NFX3presetNr, trackColor[desired_instrument]);
      NoteFX3_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX3[NFX3presetNr].Pot_Value[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX3[NFX3presetNr].Pot_Value[MixerColumn] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 2:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 3:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12] + encoded[MixerColumn]), 0, 127);
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
        saveNoteFX("NoteFX3", 2);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadNoteFX("NoteFX3", 2);
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
void NoteFX3_Page_Static() {
  clearWorkSpace();
  NoteFX3_Change();
  drawNrInRect(18, 1, NFX3presetNr, ILI9341_PURPLE);
  draw_SeqMode();
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    drawPot(MixerColumn, 0, NFX3[NFX3presetNr].Pot_Value[MixerColumn], NFX3[NFX3presetNr].Pot_Value[MixerColumn], NFX3_ROW1[MixerColumn], trackColor[desired_instrument]);
    drawPot(MixerColumn, 1, NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4], NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
    drawPot(MixerColumn, 2, NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8], NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
    drawPot(MixerColumn, 3, NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12], NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
  }
}

void NoteFX3_Change() {
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    NFX3[NFX3presetNr].Pot_Value[MixerColumn];
    NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4];
    NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8];
    NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12];
  }
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
  draw_SeqMode();
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    drawPotDrum(MixerColumn, 0, NFX4[NFX4presetNr].Pot_Value[MixerColumn], NFX4[NFX4presetNr].Pot_Value[MixerColumn], drumnote[MixerColumn], trackColor[desired_instrument]);
    drawPotDrum(MixerColumn, 1, NFX4[NFX4presetNr].Pot_Value[MixerColumn + 4], NFX4[NFX4presetNr].Pot_Value[MixerColumn + 4], drumnote[MixerColumn + 4], trackColor[desired_instrument]);
    drawPotDrum(MixerColumn, 2, NFX4[NFX4presetNr].Pot_Value[MixerColumn + 8], NFX4[NFX4presetNr].Pot_Value[MixerColumn + 8], drumnote[MixerColumn + 8], trackColor[desired_instrument]);
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

void NoteFX5_Page1_Dynamic() {
  //change preset
  if (button[14]) {

    if (enc_moved[0]) {
      int noteselector = constrain((NFX5[NFX5presetNr].Pot_Value[gridTouchY - 1] + encoded[0]), 1, track[0].MIDItick_reset - 1);
      NFX5[NFX5presetNr].Pot_Value[gridTouchY - 1] = noteselector;
      draw_Ratchrate();
    }

    if (enc_moved[1]) {
      int noteselector = constrain((NFX5[NFX5presetNr].repeats[gridTouchY - 1] + encoded[1]), 1, track[0].MIDItick_reset - 1);
      NFX5[NFX5presetNr].repeats[gridTouchY - 1] = noteselector;
      draw_Ratchrate();
    }

    if (enc_moved[3]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      NFX5presetNr = constrain((NFX5presetNr + encoded[3]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, NFX5presetNr, trackColor[desired_instrument]);
      NoteFX5_Page_Static();
    }
  }
  if (!button[14]) {
    //gridTouchX
    if (enc_moved[0]) {
      gridTouchX = constrain((gridTouchX + encoded[0]), 0, 19);
      drawCursor();
      showCoordinates();
    }
    //gridTouchY
    if (enc_moved[1]) {
      gridTouchY = constrain((gridTouchY + encoded[1]), 0, 14);
      drawCursor();
      showCoordinates();
    }
  }

  TS_Point p = ts.getPoint();


  static bool touched;
  if (!ts.touched() && !button[15]) {
    touched = false;
  }
  if (ts.touched() || button[15]) {
    if (!touched) {


      if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {

        int dot_on_X = (gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X;
        int dot_on_Y = (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y;

        ch1tone = (gridTouchY - 1);
        int step_number = gridTouchX - 2;

        if (!ratchet[NFX5presetNr][ch1tone][step_number]) {
          touched = true;
          ratchet[NFX5presetNr][ch1tone][step_number] = true;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, (trackColor[0] + (NFX5presetNr)*20));  //draw the active steps circles
        } else if (ratchet[NFX5presetNr][ch1tone][step_number]) {
          touched = true;
          ratchet[NFX5presetNr][ch1tone][step_number] = false;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, ILI9341_DARKGREY);  //draw the inactive steps circles
        }
      }
    }

    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        saveNoteFX("NoteFX5", 4);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadNoteFX("NoteFX5", 4);
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
void NoteFX5_Page_Static() {
  clearWorkSpace();
  drawStepSequencerStatic(16);
  draw_Ratchrate();
  drawActiveRatchetSteps();
  drawNrInRect(18, 1, NFX5presetNr, trackColor[desired_instrument]);
  draw_SeqMode();


  midi01.sendControlChange(0, 0, 1);
  LP_drawStepsequencer();
  LP_drawOctave(3);
}
void drawActiveRatchetSteps() {
  for (int tone = 0; tone < 12; tone++) {
    for (int steps = 0; steps < STEP_QUANT; steps++) {
      if (ratchet[NFX5presetNr][tone][steps]) {
        tft.fillCircle((steps * STEP_FRAME_W) + DOT_OFFSET_X, ((tone)*STEP_FRAME_H) + DOT_OFFSET_Y, DOT_RADIUS, trackColor[0] + ((track[0].clip_selector) * 20));
      }
    }
  }
}
void draw_Ratchrate() {
  for (int n = 0; n < 12; n++) {  //hor notes
    tft.fillRect(STEP_FRAME_W, STEP_FRAME_H * n + STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H, trackColor[desired_instrument]);
    tft.setCursor(18, STEP_FRAME_H * n + 18);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(1);
    tft.print(NFX5[NFX5presetNr].Pot_Value[n]);
    tft.setCursor(26, STEP_FRAME_H * n + 23);
    tft.print(NFX5[NFX5presetNr].repeats[n]);
  }
}

void NoteFX8_Page_Static() {  //static Display rendering

  clearWorkSpace();
  draw_Notenames();
  drawOctaveTriangle();
  drawOctaveNumber();
  drawStepSequencerStatic(12);
  clearPixelGrid();
  drawActivePolyPixel();
  draw_SeqMode();
  drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
  drawNrInRect(18, 6, ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].voiceCount, trackColor[desired_instrument]);

  /*
  if (launchpad) {
    midi01.sendControlChange(0, 0, 1);
    LP_drawStepsequencer();
    LP_drawOctave(3);
    //LP_drawOctave(5);
    midi01.sendNoteOn(LP_grid_notes[31], LP_GREEN, 1);
    midi01.sendNoteOn(LP_grid_notes[24], LP_RED, 1);
  }*/
}

void NoteFX8_Page1_Dynamic() {

  int touched_step = gridTouchX - 2;
  int touched_note = gridTouchY - 1;
  /*
    if (launchpad) {
    for (int LPclips = 0; LPclips < 8; LPclips++) {
      if (LP_grid_bool[LPclips]) {
        LP_drawclipRow();
      }
    }
    for (int notes = 0; notes < 12; notes++) {
      for (int steps = 0; steps < 16; steps++) {
        if (LP_octave_bool[notes] || LP_grid_bool[24] || LP_grid_bool[31] || LP_step_bool[steps])
          LP_melodicstep();
      }
    }
    }
    */
  if (!button[14]) {
    //gridTouchX
    if (enc_moved[0]) {
      pixelTouchX = constrain((pixelTouchX + (encoded[0] * 2)), 0, 320);
      drawCursorPixel();
      showCoordinates();
      gridTouchX = (pixelTouchX + 7) / 16;
    }
    //gridTouchY
    if (enc_moved[1]) {
      gridTouchY = constrain((gridTouchY + encoded[1]), 0, 14);
      drawCursorPixel();
      showCoordinates();
    }


    //voiceCount
    if (enc_moved[2]) {
      ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].voiceCount = constrain((ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].voiceCount + encoded[2]), 0, (MAX_VOICES - 1));
      drawNrInRect(18, 6, ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].voiceCount, trackColor[desired_instrument]);
    }

    //clip
    if (enc_moved[3]) {
      track[desired_instrument].clip_selector = constrain((track[desired_instrument].clip_selector + encoded[3]), 0, MAX_CLIPS - 1);
      drawActivePolyPixel();
      drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
    }
  }

  //octaves
  if (button[14]) {
    if (enc_moved[0]) {
      track[desired_instrument].shown_octaves = track[desired_instrument].shown_octaves + encoded[0];
      drawActivePolyPixel();
      drawOctaveNumber();
    }
    //seqMode
    if (enc_moved[1]) {
      track[desired_instrument].seqMode = constrain((track[desired_instrument].seqMode + encoded[1]), 0, MAX_SEQMODES - 1);
      drawChar(18, 9, seqModes[track[desired_instrument].seqMode], trackColor[desired_instrument]);
    }
    //step diviion
    if (enc_moved[2]) {
      track[desired_instrument].MIDItick_reset = constrain((track[desired_instrument].MIDItick_reset + encoded[2]), 0, 97);
      drawNrInRect(18, 8, track[desired_instrument].MIDItick_reset, trackColor[desired_instrument]);
    }
    //step length
    if (enc_moved[3]) {
      track[desired_instrument].stepLength = constrain((track[desired_instrument].stepLength + encoded[3]), 0, (track[desired_instrument].MIDItick_reset - 1));
      drawNrInRect(18, 7, track[desired_instrument].stepLength, trackColor[desired_instrument]);
    }
  }




  static bool touched;
  if (!ts.touched() && !button[15]) {
    touched = false;
  }
  if (enc_moved[0]) {
    touched = false;
  }
  if (ts.touched() || button[15]) {

    //clear clip
    if (gridTouchX >= 18 && gridTouchY == 9) {
      for (int tickrs = 0; tickrs < MAX_TICKS; tickrs++) {
        for (int polys = 0; polys < MAX_VOICES; polys++) {
          ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].tick[tickrs].voice[polys] = VALUE_NOTEOFF;
        }
        ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].voiceCount = 0;
      }
      drawActivePolyPixel();
    }

    if (pixelTouchX >= 30 && pixelTouchX <= 220 && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {
      if (!touched) {
        //some variables
        int desired_tick = ((pixelTouchX + 2) - (2 * STEP_FRAME_W)) / 2;
        int note = touched_note + track[desired_instrument].shown_octaves * 12;

        //assign notes to voices
        for (int polys = 0; polys < MAX_VOICES; polys++) {
          if (ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].voiceCount == polys) {
            if (ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].tick[desired_tick].voice[polys] == VALUE_NOTEOFF) {
              touched = true;
              ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].tick[desired_tick].voice[polys] = note;
            } else if (ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].tick[desired_tick].voice[polys] > VALUE_NOTEOFF) {
              touched = true;
              ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].tick[desired_tick].voice[polys] = VALUE_NOTEOFF;
            }
          }
        }
        drawActivePolyPixelY(desired_tick);
      }

      touched = true;
      //octave selection
      if (gridTouchX >= OCTAVE_CHANGE_LEFTMOST) {
        if (gridTouchY >= OCTAVE_CHANGE_UP_TOPMOST && gridTouchY < OCTAVE_CHANGE_UP_BOTTOMMOST) {
          track[desired_instrument].shown_octaves--;
        }
        if (gridTouchY >= OCTAVE_CHANGE_DOWN_TOPMOST && gridTouchY < OCTAVE_CHANGE_DOWN_BOTTOMMOST) {
          track[desired_instrument].shown_octaves++;
        }
        clearPixelGrid();
        //draw the octave number
        drawOctaveNumber();
        drawActivePolyPixel();
      }


      //load and save
      if (gridTouchY == 0) {
        //Save button
        if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
          touched = true;
          saveTrack(trackNames_long[desired_instrument], desired_instrument);
          //saveMIDItrack(trackNames_long[desired_instrument], desired_instrument);
        }
        //Load button
        if (gridTouchX == POSITION_LOAD_BUTTON) {
          touched = true;
          loadTrack(trackNames_long[desired_instrument], desired_instrument);
        }
      }
      //clipselecting
      if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
        touched = true;
        track[desired_instrument].clip_selector = (gridTouchX / 2) - 1;
        clearPixelGrid();
        drawActivePolyPixel();
        drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
      }
    }
  }
}
