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
}

void Plugin9_Page_Static(byte Pagenumber) {
  clearWorkSpace();
  //place here the (copied!) shown controls for your plugin
  //if needed draw selecting pages buttons
  //draw_sub_page_buttons(n); //max 4
  drawPot(CTRL_COL_0, CTRL_ROW_0, pl9[pl9presetNr].wah_form_graph, pl9[pl9presetNr].wah_form, "WForm", trackColor[desired_track]);
  drawPot(CTRL_COL_1, CTRL_ROW_0, pl9[pl9presetNr].wah_rate_graph, pl9[pl9presetNr].wah_rate, "Rate", trackColor[desired_track]);
  drawPot(CTRL_COL_2, CTRL_ROW_0, pl9[pl9presetNr].wah_sweep_graph, pl9[pl9presetNr].wah_sweep_graph, "Depth", trackColor[desired_track]);

  drawPot(CTRL_COL_0, CTRL_ROW_1, pl9[pl9presetNr].wah_freq_graph, pl9[pl9presetNr].wah_freq_graph, "Freq", trackColor[desired_track]);
  drawPot(CTRL_COL_1, CTRL_ROW_1, pl9[pl9presetNr].wah_reso_graph, pl9[pl9presetNr].wah_reso_graph, "Reso", trackColor[desired_track]);

  drawPot(CTRL_COL_0, CTRL_ROW_2, pl9[pl9presetNr].wavefold_graph, pl9[pl9presetNr].wavefold_graph, "WFold", trackColor[desired_track]);

  drawPot(CTRL_COL_0, CTRL_ROW_3, pl9[pl9presetNr].Filter1_Frequency_graph, pl9[pl9presetNr].Filter1_Frequency, "Frq", trackColor[desired_track]);
  drawPot(CTRL_COL_1, CTRL_ROW_3, pl9[pl9presetNr].Filter1_Resonance_graph, pl9[pl9presetNr].Filter1_Resonance_graph, "Res", trackColor[desired_track]);
  drawPot(CTRL_COL_2, CTRL_ROW_3, pl9[pl9presetNr].Filter1_Sweep_graph, pl9[pl9presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_track]);
  drawPot(CTRL_COL_3, CTRL_ROW_3, pl9[pl9presetNr].Filter1_Type_graph, pl9[pl9presetNr].Filter1_Type, "", trackColor[desired_track]);
  drawChar(CTRL_COL_3, 13, filterType[pl9[pl9presetNr].Filter1_Type], ILI9341_WHITE);
}

void Plugin9_Page1_Dynamic() {
  switch (lastPotRow) {
    case 0:
      if (msecs % 11 == 0) {
        //wah-wah
        //Waveform
        if (abs(Potentiometer[0] - pl9[pl9presetNr].wah_form_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].wah_form_graph != Potentiometer[0]) {
            pl9[pl9presetNr].wah_form_graph = Potentiometer[0];
            pl9[pl9presetNr].wah_form = pl9[pl9presetNr].wah_form_graph / 10;
            pl9bpinput.begin(pl9[pl9presetNr].wah_form);
            drawPot(CTRL_COL_0, CTRL_ROW_0, pl9[pl9presetNr].wah_form_graph, pl9[pl9presetNr].wah_form, "WForm", trackColor[desired_track]);
          }
        }
        //Rate
        if (abs(Potentiometer[1] - pl9[pl9presetNr].wah_rate_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].wah_rate_graph != Potentiometer[1]) {
            pl9[pl9presetNr].wah_rate_graph = Potentiometer[1];
            pl9[pl9presetNr].wah_rate = pl9[pl9presetNr].wah_rate_graph / 16.00;
            pl9bpinput.frequency(pl9[pl9presetNr].wah_rate);
            drawPot(CTRL_COL_1, CTRL_ROW_0, pl9[pl9presetNr].wah_rate_graph, pl9[pl9presetNr].wah_rate, "Rate", trackColor[desired_track]);
          }
        }
        //Amount
        if (abs(Potentiometer[2] - pl9[pl9presetNr].wah_sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].wah_sweep_graph != Potentiometer[2]) {
            pl9[pl9presetNr].wah_sweep_graph = Potentiometer[2];
            pl9[pl9presetNr].wah_sweep = pl9[pl9presetNr].wah_sweep_graph / 18.30;
            pl9bpfilter.octaveControl(pl9[pl9presetNr].wah_sweep);
            drawPot(CTRL_COL_2, CTRL_ROW_0, pl9[pl9presetNr].wah_sweep_graph, pl9[pl9presetNr].wah_sweep_graph, "Depth", trackColor[desired_track]);
          }
        }
      }
      break;
    case 1:
      if (msecs % 11 == 0) {
        //Freq
        if (abs(Potentiometer[0] - pl9[pl9presetNr].wah_freq_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].wah_freq_graph != Potentiometer[0]) {
            pl9[pl9presetNr].wah_freq_graph = Potentiometer[0];
            pl9[pl9presetNr].wah_freq = map(pl9[pl9presetNr].wah_freq_graph, 0, 127, 20, 2000);
            pl9bpfilter.frequency(pl9[pl9presetNr].wah_freq);
            drawPot(CTRL_COL_0, CTRL_ROW_1, pl9[pl9presetNr].wah_freq_graph, pl9[pl9presetNr].wah_freq_graph, "Freq", trackColor[desired_track]);
          }
        }
        //Reso
        if (abs(Potentiometer[1] - pl9[pl9presetNr].wah_reso_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].wah_reso_graph != Potentiometer[1]) {
            pl9[pl9presetNr].wah_reso_graph = Potentiometer[1];
            pl9[pl9presetNr].wah_reso = pl9[pl9presetNr].wah_reso_graph / 25.40;
            pl9bpfilter.resonance(pl9[pl9presetNr].wah_reso);
            drawPot(CTRL_COL_1, CTRL_ROW_1, pl9[pl9presetNr].wah_reso_graph, pl9[pl9presetNr].wah_reso_graph, "Reso", trackColor[desired_track]);
          }
        }
      }
      break;
    case 2:
      if (msecs % 11 == 0) {
        //Wavefold
        if (abs(Potentiometer[0] - pl9[pl9presetNr].wavefold_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].wavefold_graph != Potentiometer[0]) {
            pl9[pl9presetNr].wavefold_graph = Potentiometer[0];
            pl9[pl9presetNr].wavefold = (pl9[pl9presetNr].wavefold_graph / 64.00) + 0.06;
            pl9dc1.amplitude(pl9[pl9presetNr].wavefold);
            drawPot(CTRL_COL_0, CTRL_ROW_2, pl9[pl9presetNr].wavefold_graph, pl9[pl9presetNr].wavefold_graph, "WFold", trackColor[desired_track]);
          }
        }
      }
      break;
    case 3:
      if (msecs % 11 == 0) {
        //Filter Frequency
        if (abs(Potentiometer[0] - pl9[pl9presetNr].Filter1_Frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].Filter1_Frequency_graph != Potentiometer[0]) {
            pl9[pl9presetNr].Filter1_Frequency_graph = Potentiometer[0];
            pl9[pl9presetNr].Filter1_Frequency = map(pl9[pl9presetNr].Filter1_Frequency_graph, 0, 127, 40, 5900.00);
            pl9filter2.frequency(pl9[pl9presetNr].Filter1_Frequency);
            drawPot(CTRL_COL_0, CTRL_ROW_3, pl9[pl9presetNr].Filter1_Frequency_graph, pl9[pl9presetNr].Filter1_Frequency, "Frq", trackColor[desired_track]);
          }
        }
        //Resonance
        if (abs(Potentiometer[1] - pl9[pl9presetNr].Filter1_Resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].Filter1_Resonance_graph != Potentiometer[1]) {
            pl9[pl9presetNr].Filter1_Resonance_graph = Potentiometer[1];
            pl9[pl9presetNr].Filter1_Resonance = pl9[pl9presetNr].Filter1_Resonance_graph / 25.40;
            pl9filter2.resonance(pl9[pl9presetNr].Filter1_Resonance);
            drawPot(CTRL_COL_1, CTRL_ROW_3, pl9[pl9presetNr].Filter1_Resonance_graph, pl9[pl9presetNr].Filter1_Resonance_graph, "Res", trackColor[desired_track]);
          }
        }
        //Sweep
        if (abs(Potentiometer[2] - pl9[pl9presetNr].Filter1_Sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].Filter1_Sweep_graph != Potentiometer[2]) {
            pl9[pl9presetNr].Filter1_Sweep_graph = Potentiometer[2];
            pl9[pl9presetNr].Filter1_Sweep = pl9[pl9presetNr].Filter1_Sweep_graph / 18.14;
            pl9filter2.octaveControl(pl9[pl9presetNr].Filter1_Sweep);
            drawPot(CTRL_COL_2, CTRL_ROW_3, pl9[pl9presetNr].Filter1_Sweep_graph, pl9[pl9presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_track]);
          }
        }
        //Filtertype
        if (abs(Potentiometer[3] - pl9[pl9presetNr].Filter1_Type_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].Filter1_Type_graph != Potentiometer[3]) {
            pl9[pl9presetNr].Filter1_Type_graph = Potentiometer[3];
            pl9[pl9presetNr].Filter1_Type = pl9[pl9presetNr].Filter1_Type_graph / 43;
            selectFilterType(25, pl9[pl1presetNr].Filter1_Type);
            drawPot(CTRL_COL_3, CTRL_ROW_3, pl9[pl9presetNr].Filter1_Type_graph, pl9[pl9presetNr].Filter1_Type, "", trackColor[desired_track]);
            drawChar(CTRL_COL_3, 13, filterType[pl9[pl9presetNr].Filter1_Type], ILI9341_WHITE);
          }
        }
      }      
      break;
  }

  if (ts.touched() || enter_button) {


    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        //savePlugin9();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        //loadPlugin9();
      }
    }
    //change preset
    if (gridTouchX >= 18 && gridTouchY == 1) {
      drawNrInRect(18, 1, pl8presetNr, ILI9341_PURPLE);
      if ((abs(map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1) - pl8presetNr) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        pl9presetNr = map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1);
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