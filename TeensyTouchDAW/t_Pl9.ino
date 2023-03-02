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

      if (pl9[pl9presetNr].wah_form_graph != Potentiometer[0]) {
        pl9[pl9presetNr].wah_form = Potentiometer[0] / 11;
        pl9[pl9presetNr].wah_form_graph = pl9[pl9presetNr].wah_form * 11;
        pl9bpinput.begin(pl9[pl9presetNr].wah_form);
        drawPot(CTRL_COL_0, CTRL_ROW_0, pl9[pl9presetNr].wah_form_graph, pl9[pl9presetNr].wah_form, "WForm", trackColor[desired_track]);
      }
      if (pl9[pl9presetNr].wah_rate_graph != Potentiometer[1]) {
        pl9[pl9presetNr].wah_rate_graph = Potentiometer[1];
        pl9[pl9presetNr].wah_rate = pl9[pl9presetNr].wah_rate_graph / 16.00;
        pl9bpinput.frequency(pl9[pl9presetNr].wah_rate);
        drawPot_2(CTRL_COL_1, CTRL_ROW_0, pl9[pl9presetNr].wah_rate_graph, pl9[pl9presetNr].wah_rate_graph, "Rate", trackColor[desired_track]);
      }
      if (pl9[pl9presetNr].wah_sweep_graph != Potentiometer[2]) {
        pl9[pl9presetNr].wah_sweep_graph = Potentiometer[2];
        pl9[pl9presetNr].wah_sweep = pl9[pl9presetNr].wah_sweep_graph / 127.00;
        pl9bpfilter.octaveControl(pl9[pl9presetNr].wah_sweep);
        drawPot_2(CTRL_COL_2, CTRL_ROW_0, pl9[pl9presetNr].wah_sweep_graph, pl9[pl9presetNr].wah_sweep_graph, "Depth", trackColor[desired_track]);
      }

      break;
    case 1:
      if (pl9[pl9presetNr].wah_freq_graph != Potentiometer[0]) {
        pl9[pl9presetNr].wah_freq_graph = Potentiometer[0];
        pl9[pl9presetNr].wah_freq = map(pl9[pl9presetNr].wah_freq_graph, 0, 127, 20, 2000);
        pl9bpfilter.frequency(pl9[pl9presetNr].wah_freq);
        drawPot(CTRL_COL_0, CTRL_ROW_1, pl9[pl9presetNr].wah_freq_graph, pl9[pl9presetNr].wah_freq_graph, "Freq", trackColor[desired_track]);
      }
      if (pl9[pl9presetNr].wah_reso_graph != Potentiometer[1]) {
        pl9[pl9presetNr].wah_reso_graph = Potentiometer[1];
        pl9[pl9presetNr].wah_reso = pl9[pl9presetNr].wah_reso_graph / 25.40;
        pl9bpfilter.resonance(pl9[pl9presetNr].wah_reso);
        drawPot_2(CTRL_COL_1, CTRL_ROW_1, pl9[pl9presetNr].wah_reso_graph, pl9[pl9presetNr].wah_reso_graph, "Reso", trackColor[desired_track]);
      }
     
      break;
    case 2:
      if (pl9[pl9presetNr].wavefold_graph != Potentiometer[0]) {
        pl9[pl9presetNr].wavefold_graph = Potentiometer[0];
        pl9[pl9presetNr].wavefold = (pl9[pl9presetNr].wavefold_graph / 64.00) + 0.06;
        pl9dc1.amplitude(pl9[pl9presetNr].wavefold);
        drawPot(CTRL_COL_0, CTRL_ROW_2, pl9[pl9presetNr].wavefold_graph, pl9[pl9presetNr].wavefold_graph, "WFold", trackColor[desired_track]);
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
      pl9presetNr = constrain((pl9presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, pl9presetNr, ILI9341_PURPLE);
      Plugin9_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //wah-wah
        //Waveform
        Potentiometer[0] = pl9[pl9presetNr].wah_form * 11;
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl9[pl9presetNr].wah_form + encoded[0]), 0, 12) * 11;
        }
        //Rate
        Potentiometer[1] = pl9[pl9presetNr].wah_rate_graph;
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl9[pl9presetNr].wah_rate_graph + encoded[1]), 0, 127);
        }
        //Amount
        Potentiometer[2] = pl9[pl9presetNr].wah_sweep_graph;
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((pl9[pl9presetNr].wah_sweep_graph + encoded[2]), 0, 127);
        }
        break;

      case 1:
        //Freq
        Potentiometer[0] = pl9[pl9presetNr].wah_freq_graph;
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl9[pl9presetNr].wah_freq_graph + encoded[0]), 0, 127);
        }
        //Reso
        Potentiometer[1] = pl9[pl9presetNr].wah_reso_graph;
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl9[pl9presetNr].wah_reso_graph + encoded[1]), 0, 127);
        }
        break;
      case 2:
        //Wavefold
        Potentiometer[0] = pl9[pl9presetNr].wavefold_graph;
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl9[pl9presetNr].wavefold_graph + encoded[0]), 0, 127);
        }
        break;

      case 3:
        //Filter Frequency
        Potentiometer[0] = pl9[pl9presetNr].Pot_Value[4];
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl9[pl9presetNr].Pot_Value[4] + encoded[0]), 0, 127);
        }
        //Resonance
        Potentiometer[1] = pl9[pl9presetNr].Pot_Value[5];
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl9[pl9presetNr].Pot_Value[5] + encoded[1]), 0, 127);
        }
        //Sweep
        Potentiometer[2] = pl9[pl9presetNr].Pot_Value[6];
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((pl9[pl9presetNr].Pot_Value[6] + encoded[2]), 0, 127);
        }
        //Filtertype
        Potentiometer[3] = pl9[pl9presetNr].Pot_Value[7] *SVF_TYP;
        if (enc_moved[3]) {
          Potentiometer[3] = constrain((pl9[pl9presetNr].Pot_Value[7] + encoded[3]), 0, 2) *SVF_TYP;
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
      /* drawNrInRect(18, 1, pl8presetNr, ILI9341_PURPLE);
      if ((abs(map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1) - pl8presetNr) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        pl9presetNr = map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1);
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
  drawNrInRect(18, 1, pl9presetNr, ILI9341_PURPLE);
  drawPot(CTRL_COL_0, CTRL_ROW_0, pl9[pl9presetNr].wah_form_graph, pl9[pl9presetNr].wah_form, "WForm", trackColor[desired_track]);
  drawPot(CTRL_COL_1, CTRL_ROW_0, pl9[pl9presetNr].wah_rate_graph, pl9[pl9presetNr].wah_rate, "Rate", trackColor[desired_track]);
  drawPot(CTRL_COL_2, CTRL_ROW_0, pl9[pl9presetNr].wah_sweep_graph, pl9[pl9presetNr].wah_sweep_graph, "Depth", trackColor[desired_track]);

  drawPot(CTRL_COL_0, CTRL_ROW_1, pl9[pl9presetNr].wah_freq_graph, pl9[pl9presetNr].wah_freq_graph, "Freq", trackColor[desired_track]);
  drawPot(CTRL_COL_1, CTRL_ROW_1, pl9[pl9presetNr].wah_reso_graph, pl9[pl9presetNr].wah_reso_graph, "Reso", trackColor[desired_track]);

  //drawPot(CTRL_COL_0, CTRL_ROW_2, pl9[pl9presetNr].wavefold_graph, pl9[pl9presetNr].wavefold_graph, "WFold", trackColor[desired_track]);

  //drawPot(CTRL_COL_0, CTRL_ROW_3, pl9[pl9presetNr].Pot_Value[4], pl9[pl9presetNr].Filter1_Frequency, "Freq", trackColor[desired_track]);
  //drawPot(CTRL_COL_1, CTRL_ROW_3, pl9[pl9presetNr].Pot_Value[5], pl9[pl9presetNr].Pot_Value[5], "Reso", trackColor[desired_track]);
  //drawPot(CTRL_COL_2, CTRL_ROW_3, pl9[pl9presetNr].Pot_Value[6], pl9[pl9presetNr].Pot_Value[6], "Swp", trackColor[desired_track]);
  //drawPot(CTRL_COL_3, CTRL_ROW_3, pl9[pl9presetNr].Pot_Value[7]_graph, pl9[pl9presetNr].Pot_Value[7], "", trackColor[desired_track]);
  //drawChar(CTRL_COL_3, 13, filterType[pl9[pl9presetNr].Pot_Value[7]], ILI9341_WHITE);
}
void Plugin9_Change() {
  pl9bpinput.begin(pl9[pl9presetNr].wah_form);
  pl9bpinput.frequency(pl9[pl9presetNr].wah_rate);
  pl9bpfilter.frequency(pl9[pl9presetNr].wah_freq);
  pl9bpfilter.resonance(pl9[pl9presetNr].wah_reso);
  pl9bpfilter.octaveControl(pl9[pl9presetNr].wah_sweep);
  pl9dc1.amplitude(pl9[pl9presetNr].wavefold);
  filter1.frequency(pl9[pl9presetNr].Filter1_Frequency);
  filter1.resonance(pl9[pl9presetNr].Filter1_Resonance);
  filter1.octaveControl(pl9[pl9presetNr].Filter1_Sweep);
  selectFilterType(21, pl9[pl9presetNr].Pot_Value[7]);
}

