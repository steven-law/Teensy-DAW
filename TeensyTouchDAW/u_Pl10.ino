void Plugin_10_Settings() {

  pl10waveform1.begin(WAVEFORM_SINE);
  pl10waveform1.amplitude(1);
  pl10waveform1.frequency(note_frequency[3] * tuning);

  pl10pwm1.amplitude(1);
  pl10pwm1.amplitude(1);

  pl10mixer1.gain(0, 1);
  pl10mixer1.gain(1, 1);
  pl10mixer1.gain(2, 1);

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
  //place here the (copied!) shown controls for your plugin
  //if needed draw selecting pages buttons
  //draw_sub_page_buttons(n); //max 4
  draw_DC_LVL(pl10NR, pl10DC, 0, 0);
  draw_DC_LVL(pl10NR, pl10DC, 1, 0);
  //draw_OSC_Detune(pl10NR, pl10OSC_1, 2, 0);
  draw_OSC_ModRate(pl10NR, pl10OSC_1, 3, 0, 20.00);

  draw_PWM_LVL(pl10NR, pl10OSC_0, 0, 1);
  draw_PWM_LVL(pl10NR, pl10OSC_1, 1, 1);
  draw_WHITE_LVL(pl10NR, pl10WHITE, 2, 1);
  draw_OSC_LVL(pl10NR, pl10OSC_0, 3, 1);

  draw_StateVar_Filter(pl10NR, pl10SVF, 0, 2);

  draw_ADSR(pl10NR, pl10ADSR1, 0, 3);
  draw_ADSR(pl10NR, pl10ADSR2, 0, 3);
}
void Plugin10_Page1_Dynamic() {

  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      plpreset[1] = constrain((plpreset[1] + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[1], ILI9341_PURPLE);
      Plugin10_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        DC_LVL(pl10NR, pl10DC, 0, 0, 127.00);
        DC_LVL(pl10NR, pl10DC1, 1, 0, 127.00);
        OSC_Detune(pl10NR, pl10OSC_1, 2, 0);
        OSC_ModRate(pl10NR, pl10OSC_M, 3, 0, 20.00);
        break;
      case 1:
        PWM_LVL(pl10NR, pl10OSC_0, 0, 1, 127.00);
        PWM_LVL(pl10NR, pl10OSC_1, 1, 1, 127.00);
        WHITE_LVL(pl10NR, pl10WHITE, 2, 1);
        OSC_LVL(pl10NR, pl10OSC_M, 3, 1, 127.00);
        break;
      case 2:
        StateVar_Filter(pl10NR, pl10SVF, 0, 2);
        break;
      case 3:
        ADSR(pl10NR, pl10ADSR1, 0, 3);
        ADSR(pl10NR, pl10ADSR2, 0, 3);
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
