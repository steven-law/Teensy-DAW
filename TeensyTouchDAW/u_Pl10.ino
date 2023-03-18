void Plugin_10_Settings() {

  pl10waveform1.begin(WAVEFORM_SINE);
  pl10waveform1.amplitude(1);
  pl10waveform1.frequency(note_frequency[3] * tuning);

  pl10pwm1.amplitude(1);
  pl10pwm1.amplitude(1);

  pl10mixer1.gain(0, 1);
  pl10mixer1.gain(1, 1);
  pl10mixer1.gain(2, 1);
  pl10filter1.octaveControl(6);
  pl10mixer3.gain(0, 1);
  pl10mixer3.gain(1, 1);
  pl10mixer4.gain(0, 1);
  pl10mixer4.gain(1, 1);

  pl10dc1.amplitude(1);
  pl10envelope1.delay(0);
  pl10envelope1.hold(0);


  //place here the Audio settings for your plugin
  pl10amp.gain(1);
  pl10amp2.gain(1);
}
void Plugin10_Page_Static() {
  clearWorkSpace();
  drawNrInRect(18, 1, plpreset[pl10NR], ILI9341_PURPLE);
  Plugin10_Change();
  //place here the (copied!) shown controls for your plugin
  //if needed draw selecting pages buttons
  //draw_sub_page_buttons(n); //max 4
  draw_DC_amplitude(pl10NR, pl10DC2, 0, 0, 0.00, 1.00, "PW1");   //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  draw_DC_amplitude(pl10NR, pl10DC3, 1, 0, 0.00, 1.00, "PW2");   //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  draw_OSC_Detune(pl10NR, pl10OSC_M, 2, 0, 0, 1.00, "dTune");    //MIN: unused MAX: unused
  draw_OSC_frequency(pl10NR, pl10OSC_M, 3, 0, 0, 20.00, "LFO");  //MIN: frequency MAX: frequency |range: 0-22000

  draw_PWM_amplitude(pl10NR, pl10PWM1, 0, 1, 0, 1.00, "LVL");      //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  draw_PWM_amplitude(pl10NR, pl10PWM2, 1, 1, 0, 1.00, "LVL");      //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  draw_WHITE_amplitude(pl10NR, pl10WHITE, 2, 1, 0, 1.00, "White");  //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  draw_OSC_amplitude(pl10NR, pl10OSC_M, 3, 1, 0, GAIN_MULT_1, "Amnt");     //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude

  draw_SVF_frequency(pl10NR, pl10SVF, 0, 2, 0, 127, "Freq");  //MIN: unused MAX: unused
  draw_SVF_resonance(pl10NR, pl10SVF, 1, 2, 0, MAX_RESONANCE, "Reso");         //MIN: unused MAX: unused
  draw_DC_amplitude(pl10NR, pl10DC1, 2, 2, 0, 1.00, "Swp");           //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  draw_SVF_Type(pl10NR, pl10TYPE, 3, 2, 0, 2, "");                     //MIN: unused MAX: unused

  draw_ENV_ADSR(pl10NR, pl10ADSR1, 0, 3, 127, RELEASE_TIME, "");
  draw_ENV_ADSR(pl10NR, pl10ADSR2, 0, 3, 127, RELEASE_TIME, "");
}
void Plugin10_Page1_Dynamic() {
  change_preset(pl10NR);

  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        DC_amplitude(pl10NR, pl10DC2, 0, 0, 0.00, 1.00, "PW1");   //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
        DC_amplitude(pl10NR, pl10DC3, 1, 0, 0.00, 1.00, "PW2");   //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
        OSC_Detune(pl10NR, pl10OSC_M, 2, 0, 0, 1.00, "dTune");    //MIN: unused MAX: unused
        OSC_frequency(pl10NR, pl10OSC_M, 3, 0, 0, 20.00, "LFO");  //MIN: frequency MAX: frequency |range: 0-22000
        break;
      case 1:
        PWM_amplitude(pl10NR, pl10PWM1, 0, 1, 0, GAIN_MULT_1, "LVL");      //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
        PWM_amplitude(pl10NR, pl10PWM2, 1, 1, 0, GAIN_MULT_1, "LVL");      //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
        WHITE_amplitude(pl10NR, pl10WHITE, 2, 1, 0, GAIN_MULT_1, "White");  //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
        OSC_amplitude(pl10NR, pl10OSC_M, 3, 1, 0, GAIN_MULT_1, "Amnt");     //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
        break;
      case 2:
        SVF_frequency(pl10NR, pl10SVF, 0, 2, 0, 127, "Freq");  //MIN: unused MAX: unused
        SVF_resonance(pl10NR, pl10SVF, 1, 2, 0, 5.00, "Reso");         //MIN: unused MAX: unused
        DC_amplitude(pl10NR, pl10DC1, 2, 2, 0, 1.00, "Swp");           //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
        SVF_Type(pl10NR, pl10TYPE, 3, 2, 0, 2, "");                     //MIN: unused MAX: unused
        break;
      case 3:
        ENV_ADSR(pl10NR, pl10ADSR1, 0, 3, 127, RELEASE_TIME, "");
        ENV_ADSR(pl10NR, pl10ADSR2, 0, 3, 127, RELEASE_TIME, "");
        break;
    }
  }

  if (ts.touched() || button[15]) {
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin10", 26);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin10", 26);
      }
    }
  }
}
void Plugin10_Change() {
  change_DC_amplitude(pl10NR, pl10DC2, 0, 0, 0.00, 1.00, "PW1");   //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  change_DC_amplitude(pl10NR, pl10DC3, 1, 0, 0.00, 1.00, "PW2");   //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  change_OSC_Detune(pl10NR, pl10OSC_M, 2, 0, 0, 1.00, "dTune");    //MIN: unused MAX: unused
  change_OSC_frequency(pl10NR, pl10OSC_M, 3, 0, 0, 20.00, "LFO");  //MIN: frequency MAX: frequency |range: 0-22000

  change_PWM_amplitude(pl10NR, pl10PWM1, 0, 1, 0, 1.00, "LVL");      //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  change_PWM_amplitude(pl10NR, pl10PWM2, 1, 1, 0, 1.00, "LVL");      //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  change_WHITE_amplitude(pl10NR, pl10WHITE, 2, 1, 0, 1.00, "White");  //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  change_OSC_amplitude(pl10NR, pl10OSC_M, 3, 1, 0, GAIN_MULT_1, "Amnt");     //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude

  change_SVF_frequency(pl10NR, pl10SVF, 0, 2, 0, 127, "Freq");  //MIN: unused MAX: unused
  change_SVF_resonance(pl10NR, pl10SVF, 1, 2, 0, 5.00, "Reso");         //MIN: unused MAX: unused
  change_DC_amplitude(pl10NR, pl10DC1, 2, 2, 0, 1.00, "Swp");           //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  change_SVF_Type(pl10NR, pl1TYPE, 3, 2, 0, 2, "");                     //MIN: unused MAX: unused

  change_ENV_ADSR(pl10NR, pl10ADSR1, 0, 3, 127, RELEASE_TIME, "");
  change_ENV_ADSR(pl10NR, pl10ADSR2, 0, 3, 127, RELEASE_TIME, "");
}



void Plugin_11_Settings() {
  //place here the Audio settings for your plugin
  pl11amp.gain(1);
  pl11amp2.gain(1);
}
void Plugin11_Page_Static() {
  //place here the (copied!) shown controls for your plugin
  //if needed draw selecting pages buttons
  //draw_sub_page_buttons(n); //max 4
}
void Plugin11_Page1_Dynamic() {

  switch (lastPotRow) {
    case 0:

      break;
    case 1:

      break;
    case 2:

      break;
    case 3:

      break;
  }
  if (ts.touched()) {
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

void Plugin_12_Settings() {
  //place here the Audio settings for your plugin
  pl12amp.gain(1);
  pl12amp2.gain(1);
}
void Plugin12_Page_Static() {
  //place here the (copied!) shown controls for your plugin
  //if needed draw selecting pages buttons
  //draw_sub_page_buttons(n); //max 4
}
void Plugin12_Page1_Dynamic() {

  switch (lastPotRow) {
    case 0:

      break;
    case 1:

      break;
    case 2:

      break;
    case 3:

      break;
  }
  if (ts.touched()) {
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

void Plugin_13_Settings() {
  //place here the Audio settings for your plugin
  pl13amp.gain(1);
  pl13amp2.gain(1);
}
void Plugin13_Page_Static() {
  //place here the (copied!) shown controls for your plugin
  //if needed draw selecting pages buttons
  //draw_sub_page_buttons(n); //max 4
}
void Plugin13_Page1_Dynamic() {

  switch (lastPotRow) {
    case 0:

      break;
    case 1:

      break;
    case 2:

      break;
    case 3:

      break;
  }
  if (ts.touched()) {
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

void Plugin_14_Settings() {
  //place here the Audio settings for your plugin
  pl14amp.gain(1);
  pl14amp2.gain(1);
}
void Plugin14_Page_Static() {
  //place here the (copied!) shown controls for your plugin
  //if needed draw selecting pages buttons
  //draw_sub_page_buttons(n); //max 4
}
void Plugin14_Page1_Dynamic() {

  switch (lastPotRow) {
    case 0:

      break;
    case 1:

      break;
    case 2:

      break;
    case 3:

      break;
  }
  if (ts.touched()) {
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

void Plugin_15_Settings() {
  //place here the Audio settings for your plugin
  pl15amp.gain(1);
  pl15amp2.gain(1);
}
void Plugin15_Page_Static() {
  //place here the (copied!) shown controls for your plugin
  //if needed draw selecting pages buttons
  //draw_sub_page_buttons(n); //max 4
}
void Plugin15_Page1_Dynamic() {

  switch (lastPotRow) {
    case 0:

      break;
    case 1:

      break;
    case 2:

      break;
    case 3:

      break;
  }
  if (ts.touched()) {
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

void Plugin_16_Settings() {
  //place here the Audio settings for your plugin
  pl16amp.gain(1);
  pl16amp2.gain(1);
}
void Plugin16_Page_Static() {
  //place here the (copied!) shown controls for your plugin
  //if needed draw selecting pages buttons
  //draw_sub_page_buttons(n); //max 4
}
void Plugin16_Page1_Dynamic() {

  switch (lastPotRow) {
    case 0:

      break;
    case 1:

      break;
    case 2:

      break;
    case 3:

      break;
  }
  if (ts.touched()) {
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
