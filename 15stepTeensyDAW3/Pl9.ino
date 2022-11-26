void Plugin_9_Settings() {
  //place here the Audio settings for your plugin
  pl9bpinput.begin(WAVEFORM_SINE);
  pl9bpinput.frequency(1);
  pl9bpinput.amplitude(1);
  pl9bpfilter.frequency(130);
  pl9bpfilter.resonance(3);
  pl9bpfilter.octaveControl(4);

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
}

void Plugin9_Page1_Dynamic() {

  if (ts.touched() || !buttons[6].read()) {


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
      if ((abs(map(Potentiometer1, 0, 127, 0, MAX_PRESETS - 1) - pl8presetNr) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        pl9presetNr = map(Potentiometer1, 0, 127, 0, MAX_PRESETS - 1);
      }
    }

    if (millis() % 20 > 15) {
      //wah-wah
      if (gridTouchY == CTRL_ROW_0) {

        //Waveform
        if (gridTouchX == CTRL_COL_0 || gridTouchX == CTRL_COL_0 + 1) {
          drawPot(CTRL_COL_0, CTRL_ROW_0, pl9[pl9presetNr].wah_form_graph, pl9[pl9presetNr].wah_form, "WForm", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl9[pl9presetNr].wah_form_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl9[pl9presetNr].wah_form_graph = Potentiometer1;
            pl9[pl9presetNr].wah_form = pl9[pl9presetNr].wah_form_graph / 10;
            pl9bpinput.begin(pl9[pl9presetNr].wah_form);
          }
        }
        //Rate
        if (gridTouchX == CTRL_COL_1 || gridTouchX == CTRL_COL_1 + 1) {
          drawPot(CTRL_COL_1, CTRL_ROW_0, pl9[pl9presetNr].wah_rate_graph, pl9[pl9presetNr].wah_rate, "Rate", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl9[pl9presetNr].wah_rate_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl9[pl9presetNr].wah_rate_graph = Potentiometer1;
            pl9[pl9presetNr].wah_rate = pl9[pl9presetNr].wah_rate_graph / 16.00;
            pl9bpinput.frequency(pl9[pl9presetNr].wah_rate);
          }
        }
        //Amount
        if (gridTouchX == CTRL_COL_2 || gridTouchX == CTRL_COL_2 + 1) {
          drawPot(CTRL_COL_2, CTRL_ROW_0, pl9[pl9presetNr].wah_sweep_graph, pl9[pl9presetNr].wah_sweep_graph, "Depth", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl9[pl9presetNr].wah_sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl9[pl9presetNr].wah_sweep_graph = Potentiometer1;
            pl9[pl9presetNr].wah_sweep = pl9[pl9presetNr].wah_sweep_graph / 18.30;
            pl9bpfilter.octaveControl(pl9[pl9presetNr].wah_sweep);
          }
        }
      }
      if (gridTouchY == CTRL_ROW_1) {

        //Freq
        if (gridTouchX == CTRL_COL_0 || gridTouchX == CTRL_COL_0 + 1) {
          drawPot(CTRL_COL_0, CTRL_ROW_1, pl9[pl9presetNr].wah_freq_graph, pl9[pl9presetNr].wah_freq_graph, "Freq", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl9[pl9presetNr].wah_freq_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl9[pl9presetNr].wah_freq_graph = Potentiometer1;
            pl9[pl9presetNr].wah_freq = map(pl9[pl9presetNr].wah_freq_graph, 0, 127, 20, 2000);
            pl9bpfilter.frequency(pl9[pl9presetNr].wah_freq);
          }
        }
        //Reso
        if (gridTouchX == CTRL_COL_1 || gridTouchX == CTRL_COL_1 + 1) {
          drawPot(CTRL_COL_1, CTRL_ROW_1, pl9[pl9presetNr].wah_reso_graph, pl9[pl9presetNr].wah_reso_graph, "Reso", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl9[pl9presetNr].wah_reso_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl9[pl9presetNr].wah_reso_graph = Potentiometer1;
            pl9[pl9presetNr].wah_reso = pl9[pl9presetNr].wah_reso_graph / 25.40;
            pl9bpfilter.resonance(pl9[pl9presetNr].wah_reso);
          }
        }
      }

      if (gridTouchY == CTRL_ROW_2) {

        //Wavefold
        if (gridTouchX == CTRL_COL_0 || gridTouchX == CTRL_COL_0 + 1) {
          drawPot(CTRL_COL_0, CTRL_ROW_2, pl9[pl9presetNr].wavefold_graph, pl9[pl9presetNr].wavefold_graph, "WFold", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl9[pl9presetNr].wavefold_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl9[pl9presetNr].wavefold_graph = Potentiometer1;
            pl9[pl9presetNr].wavefold = (pl9[pl9presetNr].wavefold_graph / 64.00) + 0.06;
            pl9dc1.amplitude(pl9[pl9presetNr].wavefold);
          }
        }
      }
    }
  }
}