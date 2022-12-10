void Plugin_7_Settings() {


  //drum11111111111111111111111111111111111111111111111111111111111111111111111111111111 drum1
  pl7drum1.frequency(20);
  pl7drum1.length(50);
  pl7drum1.pitchMod(2);  //max 2 !!
  pl7drum1.secondMix(0);

  pl7dc1.amplitude(0.06);
  pl7filter1.frequency(2000);
  pl7filter1.resonance(1);

  //hihatCL2222222222222222222222222222222222222222222222222222222222222222222222222222 hatCl

  pl7noise1.amplitude(0.3);

  pl7waveformMod1.begin(WAVEFORM_SQUARE);
  pl7waveformMod1.amplitude(1);
  pl7waveformMod1.frequency(3500);
  pl7waveformMod1.frequencyModulation(1);



  pl7filter2.frequency(200);
  pl7filter2.resonance(3);
  pl7filter2.octaveControl(2);



  pl7envelope1.delay(0);
  pl7envelope1.attack(5);
  pl7envelope1.hold(1);
  pl7envelope1.decay(50);
  pl7envelope1.sustain(0);
  pl7envelope1.release(20);


  //FM33333333333333333333333333333333333333333333333333333333333333333333333333333333  FM

  pl7waveformMod3.frequency(3500);  //Modulator OSC
  pl7waveformMod3.amplitude(1);

  pl7envelope2.delay(0);  //Env Modulator
  pl7envelope2.attack(5);
  pl7envelope2.hold(1);
  pl7envelope2.decay(50);
  pl7envelope2.sustain(0);
  pl7envelope2.release(20);

  pl7waveformMod2.begin(WAVEFORM_SINE);  //Carrier OSC
  pl7waveformMod2.frequency(500);
  pl7waveformMod2.amplitude(1);
  pl7waveformMod2.frequencyModulation(1);  //0 - 12

  pl7envelope3.delay(0);  //Env Carrier
  pl7envelope3.attack(5);
  pl7envelope3.hold(1);
  pl7envelope3.decay(50);
  pl7envelope3.sustain(0);
  pl7envelope3.release(20);

  //noise444444444444444444444444444444444444444444444444444444444444444444444444444444 noise
  pl7noise2.amplitude(1);
  pl7pink1.amplitude(1);
  pl7mixer4.gain(0, 1);
  pl7mixer4.gain(1, 1);

  //pl7biquad1.setBandpass(0, noiseBp1Frequency, noise1Q);
  //pl7biquad1.setBandpass(1, noiseBp2Frequency, noise2Q * 2);

  pl7envelope4.delay(0);  //Env Carrier
  pl7envelope4.attack(5);
  pl7envelope4.hold(1);
  pl7envelope4.decay(50);
  pl7envelope4.sustain(0);
  pl7envelope4.release(20);

  //generalXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX general

  pl7mixer1.gain(0, 1);
  pl7mixer1.gain(1, 1);
  pl7mixer1.gain(2, 1);
  pl7mixer1.gain(3, 1);

  pl7mixer2.gain(0, 1);
  pl7mixer2.gain(1, 1);
  pl7mixer2.gain(2, 1);
  pl7mixer2.gain(3, 1);

  pl7mixer3.gain(0, 1);
  pl7mixer3.gain(1, 1);
  pl7mixer3.gain(2, 1);
  pl7mixer3.gain(3, 1);
  pl7amp.gain(1);
}

void Plugin7_Page_Static(byte Pagenumber) {
  clearWorkSpace();
  //draw selecting pages buttons
  draw_sub_page_buttons(2);
  if (Pagenumber == 0) {
    drawPot(CTRL_COL_0, CTRL_ROW_0, pl7drum1_frequency_graph, pl7drum1_frequency, "1Freq", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_0, pl7drum1_length_graph, pl7drum1_length, "1Decay", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_0, pl7drum1_pitchMod_graph, pl7drum1_pitchMod_graph, "1Sweep", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_0, pl7dc1_amplitude_graph, pl7dc1_amplitude_graph, "1Fold", trackColor[desired_instrument]);

    drawPot(CTRL_COL_0, CTRL_ROW_1, pl7noise1_amplitude_graph, pl7noise1_amplitude_graph, "2Noise", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_1, pl7waveformMod1_begin_graph, pl7waveformMod1_begin, "2W~F", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_1, pl7waveformMod1_frequency_graph, pl7waveformMod1_frequency, "2Freq", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_1, pl7waveformMod1_frequencyModulation_graph, pl7waveformMod1_frequencyModulation_graph, "2N-FM", trackColor[desired_instrument]);

    drawPot(CTRL_COL_0, CTRL_ROW_2, pl7filter2_frequency_graph, pl7filter2_frequency, "2Freq", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_2, pl7filter2_resonance_graph, pl7filter2_resonance_graph, "2Res", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_2, pl7Env1_Attack_graph, pl7Env1_Attack, "2Att", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_2, pl7Env1_Release_graph, pl7Env1_Release, "2Rel", trackColor[desired_instrument]);
  }
  if (Pagenumber == 1) {
    drawPot(CTRL_COL_0, CTRL_ROW_0, pl7_3_waveformMod3_amplitude_graph, pl7_3_waveformMod3_amplitude_rnd, "3M-Le", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_0, pl7_3_waveformMod3_frequency_graph, pl7_3_waveformMod3_frequency, "3M-Fr", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_0, pl7_3_Env2_Attack_graph, pl7_3_Env2_Attack, "3M-At", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_0, pl7_3_Env2_Release_graph, pl7_3_Env2_Release, "3M-Rl", trackColor[desired_instrument]);

    drawPot(CTRL_COL_0, CTRL_ROW_1, pl7_3_waveformMod2_frequencyModulation_graph, pl7_3_waveformMod2_frequencyModulation, "3C-Fr", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_1, pl7_3_waveformMod2_frequency_graph, pl7_3_waveformMod2_frequency, "3C-Fr", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_1, pl7_3_Env3_Attack_graph, pl7_3_Env3_Attack, "3M-At", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_1, pl7_3_Env3_Release_graph, pl7_3_Env3_Release, "3M-Rl", trackColor[desired_instrument]);

    drawPot(CTRL_COL_0, CTRL_ROW_2, pl7filter2_frequency_graph, pl7filter2_frequency, "2Freq", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_2, pl7filter2_resonance_graph, pl7filter2_resonance_graph, "2Res", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_2, pl7Env1_Attack_graph, pl7Env1_Attack, "2Att", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_2, pl7Env1_Release_graph, pl7Env1_Release, "2Rel", trackColor[desired_instrument]);
  }
}


void Plugin7_Page1_Dynamic() {

  switch (lastPotRow) {
    case 0:
      if (millis() % 20 > 15) {
        if (abs(Potentiometer[0] - pl7drum1_frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7drum1_frequency_graph != Potentiometer[0]) {
            pl7drum1_frequency_graph = Potentiometer[0];
            pl7drum1_frequency = map(Potentiometer[0], 0, 127, 20, 460);
            pl7drum1.frequency(pl7drum1_frequency);
            drawPot(CTRL_COL_0, CTRL_ROW_0, pl7drum1_frequency_graph, pl7drum1_frequency, "1Freq", trackColor[desired_instrument]);
          }
        }
        //drum length in ms
        if (abs(Potentiometer[1] - pl7drum1_length_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7drum1_length_graph != Potentiometer[1]) {
            pl7drum1_length_graph = Potentiometer[1];
            pl7drum1_length = pl7drum1_length_graph * 2;
            pl7drum1.length(pl7drum1_length);
            drawPot(CTRL_COL_1, CTRL_ROW_0, pl7drum1_length_graph, pl7drum1_length, "1Decay", trackColor[desired_instrument]);
          }
        }
        if (abs(Potentiometer[2] - pl7drum1_pitchMod_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7drum1_pitchMod_graph != Potentiometer[2]) {
            pl7drum1_pitchMod_graph = Potentiometer[2];
            pl7drum1_pitchMod_rnd = map(pl7drum1_pitchMod_graph, 0, 127, 6, 200);
            pl7drum1_pitchMod = pl7drum1_pitchMod_rnd / 100;
            pl7drum1.pitchMod(pl7drum1_pitchMod);
            drawPot(CTRL_COL_2, CTRL_ROW_0, pl7drum1_pitchMod_graph, pl7drum1_pitchMod_graph, "1Sweep", trackColor[desired_instrument]);
          }
        }
        if (abs(Potentiometer[3] - pl7dc1_amplitude_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7dc1_amplitude_graph != Potentiometer[3]) {
            pl7dc1_amplitude_graph = Potentiometer[3];
            pl7dc1_amplitude = pl7dc1_amplitude_graph / 127.00;
            pl7dc1.amplitude(pl7dc1_amplitude);
            drawPot(CTRL_COL_3, CTRL_ROW_0, pl7dc1_amplitude_graph, pl7dc1_amplitude_graph, "1Fold", trackColor[desired_instrument]);
          }
        }
      }
      break;
    case 1:
      if (millis() % 20 > 15) {
        //noisemod noise level
        if (abs(Potentiometer[0] - pl7noise1_amplitude_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7noise1_amplitude_graph != Potentiometer[0]) {
            pl7noise1_amplitude_graph = Potentiometer[0];
            pl7noise1_amplitude = pl7noise1_amplitude_graph / 127.00;
            pl7noise1.amplitude(pl7noise1_amplitude);
            drawPot(CTRL_COL_0, CTRL_ROW_1, pl7noise1_amplitude_graph, pl7noise1_amplitude_graph, "2Noise", trackColor[desired_instrument]);
          }
        }
        //noisemod modwaveform
        if (abs(Potentiometer[1] - pl7waveformMod1_begin_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7waveformMod1_begin_graph != Potentiometer[1]) {
            pl7waveformMod1_begin_graph = Potentiometer[1];
            pl7waveformMod1_begin = map(pl7waveformMod1_begin_graph, 0, 127, 0, 11);
            pl7waveformMod1.begin(pl7waveformMod1_begin);
            drawPot(CTRL_COL_1, CTRL_ROW_1, pl7waveformMod1_begin_graph, pl7waveformMod1_begin, "2W~F", trackColor[desired_instrument]);
          }
        }
        //noisemod frequency
        if (abs(Potentiometer[2] - pl7waveformMod1_frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7waveformMod1_frequency_graph != Potentiometer[2]) {
            pl7waveformMod1_frequency_graph = Potentiometer[2];
            pl7waveformMod1_frequency = pl7waveformMod1_frequency_graph * 32;
            pl7waveformMod1.frequency(pl7waveformMod1_frequency);
            drawPot(CTRL_COL_2, CTRL_ROW_1, pl7waveformMod1_frequency_graph, pl7waveformMod1_frequency, "2Freq", trackColor[desired_instrument]);
          }
        }
        //noisemod frequencyModulation
        if (abs(Potentiometer[3] - pl7waveformMod1_frequencyModulation_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7waveformMod1_frequencyModulation_graph != Potentiometer[3]) {
            pl7waveformMod1_frequencyModulation_graph = Potentiometer[3];
            pl7waveformMod1_frequencyModulation = pl7waveformMod1_frequencyModulation_graph / 10.60;
            pl7waveformMod1.frequencyModulation(pl7waveformMod1_frequencyModulation);
            drawPot(CTRL_COL_3, CTRL_ROW_1, pl7waveformMod1_frequencyModulation_graph, pl7waveformMod1_frequencyModulation_graph, "2N-FM", trackColor[desired_instrument]);
          }
        }
      }
      break;
    case 2:
      if (millis() % 20 > 15) {
        //Filter Frequency
        if (abs(Potentiometer[0] - pl7filter2_frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7filter2_frequency_graph != Potentiometer[0]) {
            pl7filter2_frequency_graph = Potentiometer[0];
            pl7filter2_frequency = map(pl7filter2_frequency_graph, 0, 127, 40, 5900.00);
            pl7filter2.frequency(pl7filter2_frequency);
            drawPot(CTRL_COL_0, CTRL_ROW_2, pl7filter2_frequency_graph, pl7filter2_frequency, "2Freq", trackColor[desired_instrument]);
          }
        }
        //Resonance
        if (abs(Potentiometer[1] - pl7filter2_resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7filter2_resonance_graph != Potentiometer[1]) {
            pl7filter2_resonance_graph = Potentiometer[1];
            pl7filter2_resonance = pl7filter2_resonance_graph / 25.40;
            pl7filter2.resonance(pl7filter2_resonance);
            drawPot(CTRL_COL_1, CTRL_ROW_2, pl7filter2_resonance_graph, pl7filter2_resonance_graph, "2Res", trackColor[desired_instrument]);
          }
        }
        //Attack
        if (abs(Potentiometer[2] - pl7Env1_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7Env1_Attack_graph != Potentiometer[2]) {
            pl7Env1_Attack_graph = Potentiometer[2];
            pl7Env1_Attack = map(pl7Env1_Attack_graph, 0, 127, 0, 20);
            pl7envelope1.attack(pl7Env1_Attack);
            //pl7envelope2.attack(pl7Env1_Attack);
            drawPot(CTRL_COL_2, CTRL_ROW_2, pl7Env1_Attack_graph, pl7Env1_Attack, "2Att", trackColor[desired_instrument]);
          }
        }
        //Release
        if (abs(Potentiometer[3] - pl7Env1_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7Env1_Release_graph != Potentiometer[3]) {
            pl7Env1_Release_graph = Potentiometer[3];
            pl7Env1_Release = pl7Env1_Release_graph * 2;
            pl7envelope1.release(pl7Env1_Release);
            //pl7envelope2.release(pl7Env1_Release);
            drawPot(CTRL_COL_3, CTRL_ROW_2, pl7Env1_Release_graph, pl7Env1_Release, "2Rel", trackColor[desired_instrument]);
          }
        }
      }
      break;
    case 3:
      if (millis() % 20 > 15) {
      }
      break;
  }

  if (ts.touched() || enter_button) {
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

    if (gridTouchX >= 18) {
      //page selection
      if (gridTouchY >= 3 && gridTouchY <= 4) {
        selectPage = PLUGIN7_PAGE1;
        Plugin7_Page_Static(0);
        Plugin7_Page1_Dynamic();
      }
      if (gridTouchY >= 5 && gridTouchY <= 6) {
        selectPage = PLUGIN7_PAGE2;
        Plugin7_Page_Static(1);
        Plugin7_Page2_Dynamic();
      }
      /* if (gridTouchY >= 7 && gridTouchY <= 8) {
        selectPage = PLUGIN7_PAGE3);
        Plugin7_Page_Static(2);
        Plugin7_Page3_Dynamic();
      }*/
    }
  }
}

void Plugin7_Page2_Dynamic() {

  if (ts.touched() || enter_button) {
    if (msecs % 20 == 0) {
      if (gridTouchY == CTRL_ROW_0) {

        //3 modulator amplitude
        drawPot(CTRL_COL_0, CTRL_ROW_0, pl7_3_waveformMod3_amplitude_graph, pl7_3_waveformMod3_amplitude_rnd, "3M-Le", trackColor[desired_instrument]);
        if (abs(Potentiometer[0] - pl7_3_waveformMod3_amplitude_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7_3_waveformMod3_amplitude_rnd = map(Potentiometer[0], 0, 127, 0, 100);
          pl7_3_waveformMod3_amplitude = pl7_3_waveformMod3_amplitude_rnd / 100.00;
          pl7_3_waveformMod3_amplitude_graph = Potentiometer[0];
          pl7waveformMod3.amplitude(pl7_3_waveformMod3_amplitude);
        }


        //3 modulator frequency
        if (gridTouchX == CTRL_COL_1 || gridTouchX == CTRL_COL_1 + 1) {
          drawPot(CTRL_COL_1, CTRL_ROW_0, pl7_3_waveformMod3_frequency_graph, pl7_3_waveformMod3_frequency, "3M-Fr", trackColor[desired_instrument]);
          if (abs(Potentiometer[0] - pl7_3_waveformMod3_frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl7_3_waveformMod3_frequency = map(Potentiometer[0], 0, 127, 80, 999);
            pl7_3_waveformMod3_frequency_graph = Potentiometer[0];
            pl7waveformMod3.frequency(pl7_3_waveformMod3_frequency);
          }
        }
        //3 modulator attack
        if (gridTouchX == CTRL_COL_2 || gridTouchX == CTRL_COL_2 + 1) {
          drawPot(CTRL_COL_2, CTRL_ROW_0, pl7_3_Env2_Attack_graph, pl7_3_Env2_Attack, "3M-At", trackColor[desired_instrument]);
          if (abs(Potentiometer[0] - pl7_3_Env2_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl7_3_Env2_Attack = map(Potentiometer[0], 0, 127, 6, 100);
            pl7_3_Env2_Attack_graph = map(Potentiometer[0], 0, 127, 0, 800);
            pl7envelope2.attack(pl7_3_Env2_Attack);
          }
        }
        //3 modulator release
        if (gridTouchX == CTRL_COL_3 || gridTouchX == CTRL_COL_3 + 1) {
          drawPot(CTRL_COL_3, CTRL_ROW_0, pl7_3_Env2_Release_graph, pl7_3_Env2_Release, "3M-Rl", trackColor[desired_instrument]);
          if (abs(Potentiometer[0] - pl7_3_Env2_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl7_3_Env2_Release_graph = Potentiometer[0];
            pl7_3_Env2_Release = map(Potentiometer[0], 0, 127, 20, 800);
            pl7envelope2.release(pl7_3_Env2_Release);
          }
        }
      }
      if (gridTouchY == CTRL_ROW_1) {

        //3 Carrier Frequency Modulation
        if (gridTouchX == CTRL_COL_1 || gridTouchX == CTRL_COL_1 + 1) {
          drawPot(CTRL_COL_0, CTRL_ROW_1, pl7_3_waveformMod2_frequencyModulation_graph, pl7_3_waveformMod2_frequencyModulation, "3C-Fr", trackColor[desired_instrument]);
          if (abs(Potentiometer[0] - pl7_3_waveformMod2_frequencyModulation_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl7_3_waveformMod2_frequencyModulation_rnd = map(Potentiometer[0], 0, 127, 0, 1200);
            pl7_3_waveformMod2_frequencyModulation = pl7_3_waveformMod2_frequencyModulation_rnd / 100.00;
            pl7waveformMod2.frequencyModulation(pl7_3_waveformMod2_frequencyModulation);
          }
        }

        //3 carrier frequency
        if (gridTouchX == CTRL_COL_1 || gridTouchX == CTRL_COL_1 + 1) {
          drawPot(CTRL_COL_1, CTRL_ROW_1, pl7_3_waveformMod2_frequency_graph, pl7_3_waveformMod2_frequency, "3C-Fr", trackColor[desired_instrument]);
          if (abs(Potentiometer[0] - pl7_3_waveformMod2_frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl7_3_waveformMod2_frequency = map(Potentiometer[0], 0, 127, 80, 999);
            pl7_3_waveformMod2_frequency_graph = Potentiometer[0];
            pl7waveformMod2.frequency(pl7_3_waveformMod2_frequency);
          }
        }
        //3 carrier attack
        if (gridTouchX == CTRL_COL_2 || gridTouchX == CTRL_COL_2 + 1) {
          drawPot(CTRL_COL_2, CTRL_ROW_1, pl7_3_Env3_Attack_graph, pl7_3_Env3_Attack, "3M-At", trackColor[desired_instrument]);
          if (abs(Potentiometer[0] - pl7_3_Env3_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl7_3_Env3_Attack = map(Potentiometer[0], 0, 127, 6, 100);
            pl7_3_Env3_Attack_graph = map(Potentiometer[0], 0, 127, 0, 800);
            pl7envelope2.attack(pl7_3_Env3_Attack);
          }
        }
        //3 carrier release
        if (gridTouchX == CTRL_COL_3 || gridTouchX == CTRL_COL_3 + 1) {
          drawPot(CTRL_COL_3, CTRL_ROW_1, pl7_3_Env3_Release_graph, pl7_3_Env3_Release, "3M-Rl", trackColor[desired_instrument]);
          if (abs(Potentiometer[0] - pl7_3_Env3_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl7_3_Env3_Release_graph = Potentiometer[0];
            pl7_3_Env3_Release = map(Potentiometer[0], 0, 127, 20, 800);
            pl7envelope2.release(pl7_3_Env3_Release);
          }
        }
      }
      if (gridTouchY == 11) {

        //4 noise mix
        if (gridTouchX == CTRL_COL_0 || gridTouchX == CTRL_COL_0 + 1) {
          drawPot(CTRL_COL_0, 11, pl7filter2_frequency_graph, pl7filter2_frequency, "2Freq", trackColor[desired_instrument]);
          if (abs(Potentiometer[0] - pl7filter2_frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl7filter2_frequency = map(Potentiometer[0], 0, 127, 40, 5900.00);
            pl7filter2_frequency_graph = Potentiometer[0];
            pl7filter2.frequency(pl7filter2_frequency);
          }
        }
        //Resonance
        if (gridTouchX == CTRL_COL_1 || gridTouchX == CTRL_COL_1 + 1) {
          drawPot(CTRL_COL_1, 11, pl7filter2_resonance_graph, pl7filter2_resonance_graph, "2Res", trackColor[desired_instrument]);
          if (abs(Potentiometer[0] - pl7filter2_resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl7filter2_resonance_rnd = map(Potentiometer[0], 0, 127, 70, 500.00);
            pl7filter2_resonance = pl7filter2_resonance_rnd / 100.00;
            pl7filter2_resonance_graph = Potentiometer[0];
            pl7filter2.resonance(pl7filter2_resonance);
          }
        }
        //Attack
        if (gridTouchX == CTRL_COL_2 || gridTouchX == CTRL_COL_2 + 1) {
          drawPot(CTRL_COL_2, 11, pl7Env1_Attack_graph, pl7Env1_Attack, "2Att", trackColor[desired_instrument]);
          if (abs(Potentiometer[0] - pl7Env1_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl7Env1_Attack = map(Potentiometer[0], 0, 127, 0, 20);
            pl7Env1_Attack_graph = Potentiometer[0];
            pl7envelope1.attack(pl7Env1_Attack);
            //pl7envelope2.attack(pl7Env1_Attack);
          }
        }

        //Release
        if (gridTouchX == CTRL_COL_3 || gridTouchX == CTRL_COL_3 + 1) {
          drawPot(CTRL_COL_3, 11, pl7Env1_Release_graph, pl7Env1_Release, "2Rel", trackColor[desired_instrument]);
          if (abs(Potentiometer[0] - pl7Env1_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl7Env1_Release = map(Potentiometer[0], 0, 127, 10, 250);
            pl7Env1_Release_graph = Potentiometer[0];
            pl7envelope1.release(pl7Env1_Release);
            //pl7envelope2.release(pl7Env1_Release);
          }
        }
      }
    }
    if (gridTouchX >= 18) {
      //page selection
      if (gridTouchY >= 3 && gridTouchY <= 4) {
        selectPage = PLUGIN7_PAGE1;
        Plugin7_Page_Static(0);
        Plugin7_Page1_Dynamic();
      }
      if (gridTouchY >= 5 && gridTouchY <= 6) {
        selectPage = PLUGIN7_PAGE2;
        Plugin7_Page_Static(1);
        Plugin7_Page2_Dynamic();
      }
      /*if (gridTouchY >= 7 && gridTouchY <= 8) {
        selectPage = PLUGIN7_PAGE3;
        Plugin7_Page_Static(2);
        Plugin7_Page3_Dynamic();
      }*/
    }
  }
}