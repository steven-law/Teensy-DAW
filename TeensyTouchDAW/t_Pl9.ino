void Plugin_9_Settings() {
  //place here the Audio settings for your plugin
  pl9bpinput.begin(WAVEFORM_SINE);
  pl9bpinput.frequency(1);
  pl9bpinput.amplitude(1);
  pl9bpfilter.frequency(130);
  pl9bpfilter.resonance(3);
  pl9bpfilter.octaveControl(4);
  pl9filter2.frequency(130);
  pl9filter2.resonance(3);
  pl9filter2.octaveControl(4);
  pl9mixer1.gain(0, 1);
  pl9mixer1.gain(1, 0);
  pl9mixer1.gain(2, 0);
  pl9dc1.amplitude(0.06);

  pl9amp.gain(1);
  pl9amp2.gain(1);
}
void Plugin9_Control() {
  switch (lastPotRow) {
    case 0:

      if (plugin[8].preset[plpreset[8]].Pot_Value[0] != Potentiometer[0]) {
        plugin[8].preset[plpreset[8]].Pot_Value[0] = Potentiometer[0] / 10;
        pl9bpinput.begin(plugin[8].preset[plpreset[8]].Pot_Value[0] / 10);
        drawPot(CTRL_COL_0, lastPotRow, plugin[8].preset[plpreset[8]].Pot_Value[0], plugin[8].preset[plpreset[8]].Pot_Value[0] / 10, "WForm", trackColor[desired_track]);
      }
      if (plugin[8].preset[plpreset[8]].Pot_Value[1] != Potentiometer[1]) {
        plugin[8].preset[plpreset[8]].Pot_Value[1] = (Potentiometer[1]);
        pl9bpinput.frequency((float)(plugin[8].preset[plpreset[8]].Pot_Value[1])/16.00);
        drawPot_2(CTRL_COL_1, lastPotRow, plugin[8].preset[plpreset[8]].Pot_Value[1], plugin[8].preset[plpreset[8]].Pot_Value[1], "Rate", trackColor[desired_track]);
      }
      if (plugin[8].preset[plpreset[8]].Pot_Value[2] != Potentiometer[2]) {
        plugin[8].preset[plpreset[8]].Pot_Value[2] = Potentiometer[2];
        pl9bpfilter.octaveControl((float)(plugin[8].preset[plpreset[8]].Pot_Value[2] / 127.00));
        drawPot_2(CTRL_COL_2, lastPotRow, plugin[8].preset[plpreset[8]].Pot_Value[2], plugin[8].preset[plpreset[8]].Pot_Value[2], "Depth", trackColor[desired_track]);
      }

      break;
    case 1:
      if (plugin[8].preset[plpreset[8]].Pot_Value[4] != Potentiometer[0]) {
        plugin[8].preset[plpreset[8]].Pot_Value[4] = Potentiometer[0];
        pl9bpfilter.frequency(plugin[8].preset[plpreset[8]].Pot_Value[4]*16);
        drawPot(CTRL_COL_0, lastPotRow, plugin[8].preset[plpreset[8]].Pot_Value[4], plugin[8].preset[plpreset[8]].Pot_Value[4], "Freq", trackColor[desired_track]);
      }
      if (plugin[8].preset[plpreset[8]].Pot_Value[5] != Potentiometer[1]) {
        plugin[8].preset[plpreset[8]].Pot_Value[5] = Potentiometer[1];
        pl9bpfilter.resonance((float)(plugin[8].preset[plpreset[8]].Pot_Value[5] / 25.40));
        drawPot_2(CTRL_COL_1, lastPotRow, plugin[8].preset[plpreset[8]].Pot_Value[5], plugin[8].preset[plpreset[8]].Pot_Value[5], "Reso", trackColor[desired_track]);
      }

      break;
    case 2:
      if (plugin[8].preset[plpreset[8]].Pot_Value[8] != Potentiometer[0]) {
        plugin[8].preset[plpreset[8]].Pot_Value[8] = Potentiometer[0];

        pl9dc1.amplitude((float)((plugin[8].preset[plpreset[8]].Pot_Value[8] / 64.00) + 0.06));
        drawPot(CTRL_COL_0, lastPotRow, plugin[8].preset[plpreset[8]].Pot_Value[8], plugin[8].preset[plpreset[8]].Pot_Value[8], "WFold", trackColor[desired_track]);
      }
      break;
    case 3:

      break;
  }
}
void Plugin9_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      plpreset[8] = constrain((plpreset[8] + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[8], ILI9341_PURPLE);
      //Plugin9_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //wah-wah
        //Waveform

        if (enc_moved[0]) {
          Potentiometer[0] = constrain((plugin[8].preset[plpreset[8]].Pot_Value[0] + encoded[0]), 0, 127);
          plugin[8].preset[plpreset[8]].Pot_Value[0] = Potentiometer[0]/10;
        }
        //Rate

        if (enc_moved[1]) {
          Potentiometer[1] = constrain((plugin[8].preset[plpreset[8]].Pot_Value[1] + encoded[1]), 0, 127);
          plugin[8].preset[plpreset[8]].Pot_Value[1] = Potentiometer[1];
        }
        //Amount

        if (enc_moved[2]) {
          Potentiometer[2] = constrain((plugin[8].preset[plpreset[8]].Pot_Value[2] + encoded[2]), 0, 127);
          plugin[8].preset[plpreset[8]].Pot_Value[2] = Potentiometer[2];
        }
        break;

      case 1:
        //Freq

        if (enc_moved[0]) {
          Potentiometer[0] = constrain((plugin[8].preset[plpreset[8]].Pot_Value[4] + encoded[0]), 0, 127);
          plugin[8].preset[plpreset[8]].Pot_Value[4] = Potentiometer[0];
        }
        //Reso

        if (enc_moved[1]) {
          Potentiometer[1] = constrain((plugin[8].preset[plpreset[8]].Pot_Value[5] + encoded[1]), 0, 127);
          plugin[8].preset[plpreset[8]].Pot_Value[5] = Potentiometer[1];
        }
        break;
      case 2:
        //Wavefold

        if (enc_moved[0]) {
          Potentiometer[0] = constrain((plugin[8].preset[plpreset[8]].Pot_Value[8] + encoded[0]), 0, 127);
          plugin[8].preset[plpreset[8]].Pot_Value[8] = Potentiometer[0];
        }
        break;

      case 3:
        //Filter Frequency

        if (enc_moved[0]) {
          Potentiometer[0] = constrain((plugin[8].preset[plpreset[8]].Pot_Value[4] + encoded[0]), 0, 127);
          plugin[8].preset[plpreset[8]].Pot_Value[4] = Potentiometer[0];
        }
        //Resonance

        if (enc_moved[1]) {
          Potentiometer[1] = constrain((plugin[8].preset[plpreset[8]].Pot_Value[5] + encoded[1]), 0, 127);
          plugin[8].preset[plpreset[8]].Pot_Value[5] = Potentiometer[1];
        }
        //Sweep

        if (enc_moved[2]) {
          Potentiometer[2] = constrain((plugin[8].preset[plpreset[8]].Pot_Value[6] + encoded[2]), 0, 127);
          plugin[8].preset[plpreset[8]].Pot_Value[6] = Potentiometer[2];
        }
        //Filtertype

        if (enc_moved[3]) {
          Potentiometer[3] = constrain((plugin[8].preset[plpreset[8]].Pot_Value[7] + encoded[3]), 0, 2);
          plugin[8].preset[plpreset[8]].Pot_Value[7] = Potentiometer[3];
        }
        break;
    }
  }

  if (ts.touched() || button[15]) {

    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin9", 25);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin9", 25);
      }
    }
    //change preset
    if (gridTouchX >= 18 && gridTouchY == 1) {
      /* drawNrInRect(18, 1, plpreset[8], ILI9341_PURPLE);
      if ((abs(map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1) - plpreset[8]) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        plpreset[8] = map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1);
      }*/
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
void Plugin9_Page_Static() {
  clearWorkSpace();
  Plugin9_Change();
  //place here the (copied!) shown controls for your plugin
  //if needed draw selecting pages buttons
  //draw_sub_page_buttons(n); //max 4
  drawNrInRect(18, 1, plpreset[8], ILI9341_PURPLE);
  drawPot(CTRL_COL_0, 0, plugin[8].preset[plpreset[8]].Pot_Value[0], plugin[8].preset[plpreset[8]].Pot_Value[0]/10, "WForm", trackColor[desired_track]);
  drawPot(CTRL_COL_1, 0, plugin[8].preset[plpreset[8]].Pot_Value[1], plugin[8].preset[plpreset[8]].Pot_Value[1]/16.00, "Rate", trackColor[desired_track]);
  drawPot(CTRL_COL_2, 0, plugin[8].preset[plpreset[8]].Pot_Value[2], plugin[8].preset[plpreset[8]].Pot_Value[2], "Depth", trackColor[desired_track]);

  drawPot(CTRL_COL_0, 1, plugin[8].preset[plpreset[8]].Pot_Value[4], plugin[8].preset[plpreset[8]].Pot_Value[4], "Freq", trackColor[desired_track]);
  drawPot(CTRL_COL_1, 1, plugin[8].preset[plpreset[8]].Pot_Value[5], plugin[8].preset[plpreset[8]].Pot_Value[5], "Reso", trackColor[desired_track]);

  //drawPot(CTRL_COL_0, CTRL_ROW_2, plugin[8].preset[plpreset[8]].Pot_Value[8], plugin[8].preset[plpreset[8]].Pot_Value[8], "WFold", trackColor[desired_track]);

  //drawPot(CTRL_COL_0, CTRL_ROW_3, plugin[8].preset[plpreset[8]].Pot_Value[4], plugin[8].preset[plpreset[8]].Filter1_Frequency, "Freq", trackColor[desired_track]);
  //drawPot(CTRL_COL_1, CTRL_ROW_3, plugin[8].preset[plpreset[8]].Pot_Value[5], plugin[8].preset[plpreset[8]].Pot_Value[5], "Reso", trackColor[desired_track]);
  //drawPot(CTRL_COL_2, CTRL_ROW_3, plugin[8].preset[plpreset[8]].Pot_Value[6], plugin[8].preset[plpreset[8]].Pot_Value[6], "Swp", trackColor[desired_track]);
  //drawPot(CTRL_COL_3, CTRL_ROW_3, plugin[8].preset[plpreset[8]].Pot_Value[7]_graph, plugin[8].preset[plpreset[8]].Pot_Value[7], "", trackColor[desired_track]);
  //drawChar(CTRL_COL_3, 13, filterType[plugin[8].preset[plpreset[8]].Pot_Value[7]], ILI9341_WHITE);
}
void Plugin9_Change() {

  pl9bpinput.begin(plugin[8].preset[plpreset[8]].Pot_Value[0] / 10);
  pl9bpinput.frequency((float)(plugin[8].preset[plpreset[8]].Pot_Value[1])/16.00);
  pl9bpfilter.octaveControl((float)(plugin[8].preset[plpreset[8]].Pot_Value[2] / 127.00));

  pl9bpfilter.frequency(plugin[8].preset[plpreset[8]].Pot_Value[4]*16);
  pl9bpfilter.resonance((float)(plugin[8].preset[plpreset[8]].Pot_Value[5] / 25.40));
  
  pl9dc1.amplitude((float)((plugin[8].preset[plpreset[8]].Pot_Value[8] / 64.00) + 0.06));
}
