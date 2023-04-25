//this file holds the various sequencermodes inside
//grid sequencer
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
    readTouchinput();
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
    readTouchinput();
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
    readTouchinput();
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
    readTouchinput();
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
}


