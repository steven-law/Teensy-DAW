void midiCC_view_Static(byte mixerpage, byte desired_instrument) {
  clearWorkSpace();
  draw_sub_page_buttons(1);
  drawActiveSquare(18, 3, 2, track[desired_instrument].sendCC, "Send", ILI9341_LIGHTGREY);

  for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    byte mixerColumnPos = ((MixerColumn + 1) * 4) - 1;
    drawPotCC(mixerColumnPos, 3, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_number_row_1[MixerColumn], trackColor[desired_instrument]);
    drawPotCC(mixerColumnPos, 7, track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);
    drawPotCC(mixerColumnPos, 11, track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_number_row_3[MixerColumn], trackColor[desired_instrument]);
  }
}




void midiCCpage1_Dynamic(byte desired_instrument) {
  if (ts.touched() || !buttons[6].read()) {

    if (gridTouchX >= 18 && gridTouchY == 3 || gridTouchX >= 18 && gridTouchY == 4) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        drawActiveSquare(18, 3, 2, track[desired_instrument].sendCC, "Send", ILI9341_LIGHTGREY);
        if (track[desired_instrument].sendCC) {
          track[desired_instrument].sendCC = false;
        } else if (!track[desired_instrument].sendCC) {
          track[desired_instrument].sendCC = true;
        }
      }
    }

    //Row1
    if (gridTouchY == 3) {
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte mixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (gridTouchX == mixerColumnPos || gridTouchX == mixerColumnPos + 1) {
          drawPotCC(mixerColumnPos, 3, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_number_row_1[MixerColumn], trackColor[desired_instrument]);
          if ((abs(map(Potentiometer1, 0, 1023, 0, 127) - track[desired_instrument].midicc_value_row_1[MixerColumn]) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            track[desired_instrument].midicc_value_row_1[MixerColumn] = map(Potentiometer1, 0, 1023, 0, 127);
          }
        }
      }
    }
    if (gridTouchY == 4) {
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte mixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (gridTouchX == mixerColumnPos || gridTouchX == mixerColumnPos + 1) {
          drawPotCC(mixerColumnPos, 3, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_number_row_1[MixerColumn], trackColor[desired_instrument]);
          if ((abs(map(Potentiometer1, 0, 1023, 0, 127) - track[desired_instrument].midicc_number_row_1[MixerColumn]) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            track[desired_instrument].midicc_number_row_1[MixerColumn] = map(Potentiometer1, 0, 1023, 0, 127);
          }
        }
      }
    }

    //Row2
    if (gridTouchY == 7) {
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte mixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (gridTouchX == mixerColumnPos || gridTouchX == mixerColumnPos + 1) {
          drawPotCC(mixerColumnPos, 7, track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);
          if ((abs(map(Potentiometer1, 0, 1023, 0, 127) - track[desired_instrument].midicc_value_row_2[MixerColumn]) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            track[desired_instrument].midicc_value_row_2[MixerColumn] = map(Potentiometer1, 0, 1023, 0, 127);
          }
        }
      }
    }
    if (gridTouchY == 8) {
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte mixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (gridTouchX == mixerColumnPos || gridTouchX == mixerColumnPos + 1) {
          drawPotCC(mixerColumnPos, 7, track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);
          if ((abs(map(Potentiometer1, 0, 1023, 0, 127) - track[desired_instrument].midicc_number_row_2[MixerColumn]) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            track[desired_instrument].midicc_number_row_2[MixerColumn] = map(Potentiometer1, 0, 1023, 0, 127);
          }
        }
      }
    }
    //Row3
    if (gridTouchY == 11) {
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte mixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (gridTouchX == mixerColumnPos || gridTouchX == mixerColumnPos + 1) {
          drawPotCC(mixerColumnPos, 11, track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_number_row_3[MixerColumn], trackColor[desired_instrument]);
          if ((abs(map(Potentiometer1, 0, 1023, 0, 127) - track[desired_instrument].midicc_value_row_3[MixerColumn]) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            track[desired_instrument].midicc_value_row_3[MixerColumn] = map(Potentiometer1, 0, 1023, 0, 127);
          }
        }
      }
    }
    if (gridTouchY == 12) {
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte mixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (gridTouchX == mixerColumnPos || gridTouchX == mixerColumnPos + 1) {
          drawPotCC(mixerColumnPos, 11, track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_number_row_3[MixerColumn], trackColor[desired_instrument]);
          if ((abs(map(Potentiometer1, 0, 1023, 0, 127) - track[desired_instrument].midicc_number_row_3[MixerColumn]) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            track[desired_instrument].midicc_number_row_3[MixerColumn] = map(Potentiometer1, 0, 1023, 0, 127);
          }
        }
      }
    }
  }
}