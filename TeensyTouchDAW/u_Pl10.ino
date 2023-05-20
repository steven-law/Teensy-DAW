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

  draw_PWM_amplitude(pl10NR, pl10PWM1, 0, 1, 0, 1.00, "LVL");           //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  draw_PWM_amplitude(pl10NR, pl10PWM2, 1, 1, 0, 1.00, "LVL");           //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  draw_WHITE_amplitude(pl10NR, pl10WHITE, 2, 1, 0, 1.00, "White");      //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  draw_OSC_amplitude(pl10NR, pl10OSC_M, 3, 1, 0, GAIN_MULT_1, "Amnt");  //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude

  draw_SVF_frequency(pl10NR, pl10SVF, 0, 2, 0, 127, "Freq");            //MIN: unused MAX: unused
  draw_SVF_resonance(pl10NR, pl10SVF, 1, 2, 0, MAX_RESONANCE, "Reso");  //MIN: unused MAX: unused
  draw_DC_amplitude(pl10NR, pl10DC1, 2, 2, 0, 1.00, "Swp");             //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  draw_SVF_Type(pl10NR, pl10TYPE, 3, 2, 0, 2, "");                      //MIN: unused MAX: unused

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
        PWM_amplitude(pl10NR, pl10PWM1, 0, 1, 0, GAIN_MULT_1, "LVL");       //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
        PWM_amplitude(pl10NR, pl10PWM2, 1, 1, 0, GAIN_MULT_1, "LVL");       //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
        WHITE_amplitude(pl10NR, pl10WHITE, 2, 1, 0, GAIN_MULT_1, "White");  //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
        OSC_amplitude(pl10NR, pl10OSC_M, 3, 1, 0, GAIN_MULT_1, "Amnt");     //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
        break;
      case 2:
        SVF_frequency(pl10NR, pl10SVF, 0, 2, 0, 127, "Freq");   //MIN: unused MAX: unused
        SVF_resonance(pl10NR, pl10SVF, 1, 2, 0, 5.00, "Reso");  //MIN: unused MAX: unused
        DC_amplitude(pl10NR, pl10DC1, 2, 2, 0, 1.00, "Swp");    //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
        SVF_Type(pl10NR, pl10TYPE, 3, 2, 0, 2, "");             //MIN: unused MAX: unused
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
        savePlugin("plugin10", 9);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin10", 9);
      }
    }
  }
}
void Plugin10_Change() {
  change_DC_amplitude(pl10NR, pl10DC2, 0, 0, 0.00, 1.00, "PW1");   //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  change_DC_amplitude(pl10NR, pl10DC3, 1, 0, 0.00, 1.00, "PW2");   //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  change_OSC_Detune(pl10NR, pl10OSC_M, 2, 0, 0, 1.00, "dTune");    //MIN: unused MAX: unused
  change_OSC_frequency(pl10NR, pl10OSC_M, 3, 0, 0, 20.00, "LFO");  //MIN: frequency MAX: frequency |range: 0-22000

  change_PWM_amplitude(pl10NR, pl10PWM1, 0, 1, 0, 1.00, "LVL");           //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  change_PWM_amplitude(pl10NR, pl10PWM2, 1, 1, 0, 1.00, "LVL");           //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  change_WHITE_amplitude(pl10NR, pl10WHITE, 2, 1, 0, 1.00, "White");      //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  change_OSC_amplitude(pl10NR, pl10OSC_M, 3, 1, 0, GAIN_MULT_1, "Amnt");  //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude

  change_SVF_frequency(pl10NR, pl10SVF, 0, 2, 0, 127, "Freq");   //MIN: unused MAX: unused
  change_SVF_resonance(pl10NR, pl10SVF, 1, 2, 0, 5.00, "Reso");  //MIN: unused MAX: unused
  change_DC_amplitude(pl10NR, pl10DC1, 2, 2, 0, 1.00, "Swp");    //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  change_SVF_Type(pl10NR, pl1TYPE, 3, 2, 0, 2, "");              //MIN: unused MAX: unused

  change_ENV_ADSR(pl10NR, pl10ADSR1, 0, 3, 127, RELEASE_TIME, "");
  change_ENV_ADSR(pl10NR, pl10ADSR2, 0, 3, 127, RELEASE_TIME, "");
}



void Plugin_12_Settings() {


  pl12waveform.amplitude(1);


  pl12waveformMod.begin(WAVEFORM_ARBITRARY);
  pl12waveformMod.amplitude(1);
  pl12waveformMod.frequencyModulation(1);
  pl12waveformMod.arbitraryWaveform(singleCycleWaveform, 172.0);


  pl12envelope1.delay(0);
  pl12envelope1.hold(0);
  pl12envelope2.delay(0);
  pl12envelope2.hold(0);

  pl12filter.octaveControl(6);

  pl12mixer.gain(0, 1);
  pl12mixer.gain(1, 0);
  pl12mixer.gain(2, 0);
  pl12mixer.gain(3, 0);

  pl12dc.amplitude(1);
  pl12amp.gain(1);
  pl12amp2.gain(1);
}
void clearSingleCycleWaveform() {
  pl12WaveformAssigned = false;
  for (int i = 0; i < 256; i++) {
    singleCycleWaveform[i] = 0;
  }
  old_singleCycleValue = 0;
  old_xPos_SingleCyclePixel = 32;
  selectPage = PLUGIN12_PAGE1;
  Plugin12_Page_Static();
}
void Plugin12_Page_Static() {
  if (pl12WaveformAssigned) {
    Plugin12_Page2_Static();
  }
  //place here the (copied!) shown controls for your plugin
  //if needed draw selecting pages buttons
  //draw_sub_page_buttons(n); //max 4
  clearWorkSpace();
  tft.drawFastHLine(STEP_FRAME_W * 2, 120, 256, ILI9341_WHITE);
  drawActiveRect(18, 12, 2, 2, pl12WaveformAssigned, "Enter", ILI9341_ORANGE);
  drawActiveRect(18, 13, 2, 2, true, "clear", ILI9341_RED);
  tft.drawRect(STEP_FRAME_W * 2 - 1, STEP_FRAME_H * 1 - 1, 256 + 2, 208 + 2, ILI9341_BLACK);
  for (int i = 0; i < 256; i++) {
    int xpos = i + 32;
    int ypos = map(singleCycleWaveform[i], 32768, -32768, 16, 224);
    tft.drawLine(xpos_old, ypos_old, xpos, ypos, ILI9341_WHITE);
    xpos_old = xpos;
    ypos_old = ypos;
  }
}
void Plugin12_Page1_Dynamic() {
  static int xPos_SingleCyclePixel;
  static byte yPos_SingleCyclePixel;
  static int16_t singleCycleValue;
  switch (lastPotRow) {
    case 0:
      //Waveform
      //OSC_MOD_Waveform(pl12NR, pl12OSC_MOD, 0, 0, ZERO, OSC_MOD_MAX_WF, "W~F");  //pluginNr, pointerarrayPos, column, row
      OSC_frequency(pl12NR, pl12OSC, 1, 0, ZERO, 15.00, "LFO");       //pluginNr, pointerarrayPos, column, row, max freq
      OSC_amplitude(pl12NR, pl12OSC, 2, 0, ZERO, GAIN_DIV_4, "LVL");  //pluginNr, pointerarrayPos, column, row
      OSC_Waveform(pl12NR, pl12OSC, 3, 0, ZERO, OSC_MAX_WF, "W~F");   //pluginNr, pointerarrayPos, column, row
      break;
    case 1:
      SVF_frequency(pl12NR, pl12SVF, 0, 1, ZERO, 127, "Freq");             //MIN: unused MAX: unused
      SVF_resonance(pl12NR, pl12SVF, 1, 1, ZERO, MAX_RESONANCE, "Reso");   //MIN: unused MAX: unused
      SVF_octaveControl(pl12NR, pl12SVF, 2, 1, ZERO, SVF_MAX_OCT, "Swp");  //MIN: unused MAX: amplitud
      SVF_Type(pl12NR, pl12TYPE, 3, 1, 0, 2, "");                          //MIN: unused MAX: unused
      break;
    case 2:
      ENV_ADSR(pl12NR, pl12ADSR1, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
      ENV_ADSR(pl12NR, pl12ADSR2, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
      break;
      //draw singleCycle Waveform BY ENCODERS
    case 3:
      //if (1 < gridTouchX && gridTouchX < 18 && 0 < gridTouchY && gridTouchY < 13) {
      if (enc_moved[0] || enc_moved[1]) {

        static int old_X;
        static int old_Y;
        xPos_SingleCyclePixel = constrain(xPos_SingleCyclePixel + encoded[0], STEP_FRAME_W * 2, 288);
        yPos_SingleCyclePixel = constrain(yPos_SingleCyclePixel + encoded[1], STEP_FRAME_H, 224);
        tft.drawRect(old_X - 1, old_Y - 1, 3, 3, ILI9341_DARKGREY);
        tft.drawRect(xPos_SingleCyclePixel - 1, yPos_SingleCyclePixel - 1, 3, 3, ILI9341_RED);
        old_X = xPos_SingleCyclePixel;
        old_Y = yPos_SingleCyclePixel;
      }

      if (button[15]) {
        button[15] = false;
        Serial.println("button pressed");
        singleCycleValue = map(yPos_SingleCyclePixel, 16, 224, 32768, -32768);
        int old_xpos = old_xPos_SingleCyclePixel - 32;
        int new_xpos = xPos_SingleCyclePixel - 32;
        for (int i = old_xpos; i < new_xpos; i++) {
          int16_t yPosToArray = old_singleCycleValue + (((singleCycleValue - old_singleCycleValue) / (new_xpos - old_xpos)) * (i - old_xpos));
          singleCycleWaveform[i] = yPosToArray;
          Serial.println("");
          Serial.println("");
          Serial.println("");
          Serial.printf("xOld=%i, x=%i, yOld=%i, y=%i\n", old_xPos_SingleCyclePixel, xPos_SingleCyclePixel, old_yPos_SingleCyclePixel, yPos_SingleCyclePixel);
          Serial.printf("vOld=%i, v=%i\n", old_singleCycleValue, singleCycleValue);
          Serial.printf("ArrayPos=%d, sampleData=%i\n", i, singleCycleWaveform[i]);
        }
        tft.drawLine(old_xPos_SingleCyclePixel, old_yPos_SingleCyclePixel, xPos_SingleCyclePixel, yPos_SingleCyclePixel, ILI9341_WHITE);
        old_singleCycleValue = singleCycleValue;
        old_xPos_SingleCyclePixel = xPos_SingleCyclePixel;
        old_yPos_SingleCyclePixel = yPos_SingleCyclePixel;
      }
      break;
  }
  //clear singleCycle Waveform
  if (button[14]) {
    button[14] = false;
    Serial.println("begin of Wavetable");
    for (int i = 0; i < 256; i++) {
      Serial.println(singleCycleWaveform[i]);
    }
    Serial.println("end of Wavetable");
  }
  //draw singleCycle Waveform BY HAND
  if (ts.touched()) {

    TS_Point p = ts.getPoint();
    int SCdrawX = map(p.x, TS_MINX, TS_MAXX, 0, 320);
    int SCdrawY = map(p.y, TS_MINY, TS_MAXY, 0, 240);

    if (!enc_moved[0] && !enc_moved[1]) {
      xPos_SingleCyclePixel = constrain(SCdrawX, 32, 288);
      yPos_SingleCyclePixel = constrain(SCdrawY, 16, 224);
    }
    if (1 < gridTouchX && gridTouchX < 18 && 0 < gridTouchY && gridTouchY < 13) {
      int arrayPos = constrain(xPos_SingleCyclePixel - 32, 0, 255);
      singleCycleValue = map(yPos_SingleCyclePixel, 16, 224, 32768, -32768);
      singleCycleWaveform[arrayPos] = singleCycleValue;
      Serial.printf("ArrayPos=%d, sampleData=%i\n", arrayPos, singleCycleValue);
      //tft.drawPixel(xPos_SingleCyclePixel, yPos_SingleCyclePixel, ILI9341_WHITE);
      tft.drawLine(old_xPos_SingleCyclePixel, old_yPos_SingleCyclePixel, xPos_SingleCyclePixel, yPos_SingleCyclePixel, ILI9341_WHITE);
      old_singleCycleValue = singleCycleValue;
      old_xPos_SingleCyclePixel = xPos_SingleCyclePixel;
      old_yPos_SingleCyclePixel = yPos_SingleCyclePixel;
    }

  
    if (gridTouchX >= 18 && gridTouchY == 12) {
      pl12WaveformAssigned = true;
      selectPage = PLUGIN12_PAGE2;

      Serial.println("drawing next page");
      Plugin12_Page2_Static();
    }

    if (gridTouchX >= 18 && gridTouchY >= 13) {
      clearSingleCycleWaveform();
    }
  }
}

void Plugin12_Page2_Static() {
  //place here the (copied!) shown controls for your plugin
  //if needed draw selecting pages buttons
  //draw_sub_page_buttons(n); //max 4
  clearWorkSpace();
  drawActiveRect(18, 13, 2, 2, true, "clear", ILI9341_RED);
  //Waveform
  //draw_OSC_MOD_Waveform(pl12NR, pl12OSC_MOD, 0, 0, ZERO, OSC_MOD_MAX_WF, "W~F");  //pluginNr, pointerarrayPos, column, row
  draw_OSC_frequency(pl12NR, pl12OSC, 1, 0, ZERO, 15.00, "LFO");       //pluginNr, pointerarrayPos, column, row, max freq
  draw_OSC_amplitude(pl12NR, pl12OSC, 2, 0, ZERO, GAIN_DIV_4, "LVL");  //pluginNr, pointerarrayPos, column, row
  draw_OSC_Waveform(pl12NR, pl12OSC, 3, 0, ZERO, OSC_MAX_WF, "W~F");   //pluginNr, pointerarrayPos, column, row

  draw_SVF_frequency(pl12NR, pl12SVF, 0, 1, ZERO, 127, "Freq");             //MIN: unused MAX: unused
  draw_SVF_resonance(pl12NR, pl12SVF, 1, 1, ZERO, MAX_RESONANCE, "Reso");   //MIN: unused MAX: unused
  draw_SVF_octaveControl(pl12NR, pl12SVF, 2, 1, ZERO, SVF_MAX_OCT, "Swp");  //MIN: unused MAX: amplitud
  draw_SVF_Type(pl12NR, pl12SVF, 3, 1, 0, 2, "");

  draw_ENV_ADSR(pl12NR, pl12ADSR1, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
  draw_ENV_ADSR(pl12NR, pl12ADSR2, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
}
void Plugin12_Page2_Dynamic() {
  change_preset(pl12NR);
  switch (lastPotRow) {
    case 0:
      //Waveform
      //OSC_MOD_Waveform(pl12NR, pl12OSC_MOD, 0, 0, ZERO, OSC_MOD_MAX_WF, "W~F");  //pluginNr, pointerarrayPos, column, row
      OSC_frequency(pl12NR, pl12OSC, 1, 0, ZERO, 15.00, "LFO");       //pluginNr, pointerarrayPos, column, row, max freq
      OSC_amplitude(pl12NR, pl12OSC, 2, 0, ZERO, GAIN_DIV_4, "LVL");  //pluginNr, pointerarrayPos, column, row
      OSC_Waveform(pl12NR, pl12OSC, 3, 0, ZERO, OSC_MAX_WF, "W~F");   //pluginNr, pointerarrayPos, column, row
      break;
    case 1:
      SVF_frequency(pl12NR, pl12SVF, 0, 1, ZERO, 127, "Freq");             //MIN: unused MAX: unused
      SVF_resonance(pl12NR, pl12SVF, 1, 1, ZERO, MAX_RESONANCE, "Reso");   //MIN: unused MAX: unused
      SVF_octaveControl(pl12NR, pl12SVF, 2, 1, ZERO, SVF_MAX_OCT, "Swp");  //MIN: unused MAX: amplitud
      SVF_Type(pl12NR, pl12TYPE, 3, 1, 0, 2, "");                          //MIN: unused MAX: unused
      break;
    case 2:
      ENV_ADSR(pl12NR, pl12ADSR1, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
      ENV_ADSR(pl12NR, pl12ADSR2, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
      break;
  }
  if (button[14]) {
    button[14] = false;
    Serial.println("begin of Wavetable");
    for (int i = 0; i < 256; i++) {
      Serial.println(singleCycleWaveform[i]);
    }
    Serial.println("end of Wavetable");
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
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin12", 11);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin12", 11);
      }
    }
    if (gridTouchX >= 18 && gridTouchY == 13) {
      clearSingleCycleWaveform();
    }
  }
}

void Plugin12_Change() {
  //change_OSC_MOD_Waveform(pl12NR, pl12OSC_MOD, 0, 0, ZERO, OSC_MAX_WF, "W~F");  //pluginNr, pointerarrayPos, column, row
  change_OSC_frequency(pl12NR, pl12OSC, 1, 0, ZERO, 15.00, "LFO");          //pluginNr, pointerarrayPos, column, row, max freq
  change_OSC_amplitude(pl12NR, pl12OSC, 2, 0, ZERO, GAIN_DIV_4, "LVL");     //pluginNr, pointerarrayPos, column, row
  change_OSC_Waveform(pl12NR, pl12OSC, 3, 0, ZERO, OSC_MOD_MAX_WF, "W~F");  //pluginNr, pointerarrayPos, column, row

  change_SVF_frequency(pl12NR, pl12SVF, 0, 1, ZERO, 127, "Freq");             //MIN: unused MAX: unused
  change_SVF_resonance(pl12NR, pl12SVF, 1, 1, ZERO, MAX_RESONANCE, "Reso");   //MIN: unused MAX: unused
  change_SVF_octaveControl(pl12NR, pl12SVF, 2, 1, ZERO, SVF_MAX_OCT, "Swp");  //MIN: unused MAX: amplitud
  change_SVF_Type(pl12NR, pl12SVF, 3, 1, 0, 2, "");

  change_ENV_ADSR(pl12NR, pl12ADSR1, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
  change_ENV_ADSR(pl12NR, pl12ADSR2, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
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
