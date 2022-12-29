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
  pl7amp2.gain(1);
}

void Plugin7_Page_Static(byte Pagenumber) {
  clearWorkSpace();
  //draw selecting pages buttons
  draw_sub_page_buttons(2);
  drawNrInRect(18, 1, pl7presetNr, ILI9341_PURPLE);
  if (Pagenumber == 0) {
    drawPot(CTRL_COL_0, CTRL_ROW_0, pl7[pl7presetNr]._1_frequency_graph, pl7[pl7presetNr]._1_frequency, "1Freq", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_0, pl7[pl7presetNr]._1_length_graph, pl7[pl7presetNr]._1_length, "1Decay", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_0, pl7[pl7presetNr]._1_pitchMod_graph, pl7[pl7presetNr]._1_pitchMod_graph, "1Sweep", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_0, pl7[pl7presetNr]._1_dc1_wavefold_graph, pl7[pl7presetNr]._1_dc1_wavefold_graph, "1Fold", trackColor[desired_instrument]);

    drawPot(CTRL_COL_0, CTRL_ROW_1, pl7[pl7presetNr]._2_noise1_amp_graph, pl7[pl7presetNr]._2_noise1_amp_graph, "2Noise", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_1, pl7[pl7presetNr]._2_wfMod_begin_graph, pl7[pl7presetNr]._2_wfMod_begin, "2W~F", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_1, pl7[pl7presetNr]._2_wfMod_frequency_graph, pl7[pl7presetNr]._2_wfMod_frequency, "2Freq", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_1, pl7[pl7presetNr]._2_wfMod_frequencyModulation_graph, pl7[pl7presetNr]._2_wfMod_frequencyModulation_graph, "2N-FM", trackColor[desired_instrument]);

    drawPot(CTRL_COL_0, CTRL_ROW_2, pl7[pl7presetNr]._2_filter_frequency_graph, pl7[pl7presetNr]._2_filter_frequency, "2Freq", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_2, pl7[pl7presetNr]._2_filter_resonance_graph, pl7[pl7presetNr]._2_filter_resonance_graph, "2Res", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_2, pl7[pl7presetNr]._2_Env_Attack_graph, pl7[pl7presetNr]._2_Env_Attack, "2Att", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_2, pl7[pl7presetNr]._2_Env_Release_graph, pl7[pl7presetNr]._2_Env_Release, "2Rel", trackColor[desired_instrument]);
  }
  if (Pagenumber == 1) {
    drawPot(CTRL_COL_0, CTRL_ROW_0, pl7[pl7presetNr]._3_waveformMod3_amplitude_graph, pl7[pl7presetNr]._3_waveformMod3_amplitude_rnd, "3M-Le", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_0, pl7[pl7presetNr]._3_waveformMod3_frequency_graph, pl7[pl7presetNr]._3_waveformMod3_frequency, "3M-Fr", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_0, pl7[pl7presetNr]._3_Env2_Attack_graph, pl7[pl7presetNr]._3_Env2_Attack, "3M-At", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_0, pl7[pl7presetNr]._3_Env2_Release_graph, pl7[pl7presetNr]._3_Env2_Release, "3M-Rl", trackColor[desired_instrument]);

    drawPot(CTRL_COL_0, CTRL_ROW_1, pl7[pl7presetNr]._3_waveformMod2_frequencyModulation_graph, pl7[pl7presetNr]._3_waveformMod2_frequencyModulation, "3C-Fr", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_1, pl7[pl7presetNr]._3_waveformMod2_frequency_graph, pl7[pl7presetNr]._3_waveformMod2_frequency, "3C-Fr", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_1, pl7[pl7presetNr]._3_Env3_Attack_graph, pl7[pl7presetNr]._3_Env3_Attack, "3M-At", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_1, pl7[pl7presetNr]._3_Env3_Release_graph, pl7[pl7presetNr]._3_Env3_Release, "3M-Rl", trackColor[desired_instrument]);

    /* 
    drawPot(CTRL_COL_0, CTRL_ROW_2, pl7[pl7presetNr]._2_filter_frequency_graph, pl7[pl7presetNr]._2_filter_frequency, "2Freq", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_2, pl7[pl7presetNr]._2_filter_resonance_graph, pl7[pl7presetNr]._2_filter_resonance_graph, "2Res", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_2, pl7[pl7presetNr]._2_Env_Attack_graph, pl7[pl7presetNr]._2_Env_Attack, "2Att", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_2, pl7[pl7presetNr]._2_Env_Release_graph, pl7[pl7presetNr]._2_Env_Release, "2Rel", trackColor[desired_instrument]);
    */
  }
}


void Plugin7_Page1_Dynamic() {
  //change preset
  if (button_15) {
    if (enc_moved[0]) {
      pl7presetNr = constrain((pl7presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, pl7presetNr, ILI9341_PURPLE);
      Plugin7_Page_Static(0);
    }
  }
  if (!button_15) {
    switch (lastPotRow) {
      case 0:


        if (enc_moved[0]) {
          pl7[pl7presetNr]._1_frequency_graph = constrain((pl7[pl7presetNr]._1_frequency_graph + encoded[0]), 0, 127);
          pl7[pl7presetNr]._1_frequency = map(pl7[pl7presetNr]._1_frequency_graph, 0, 127, 20, 460);
          pl7drum1.frequency(pl7[pl7presetNr]._1_frequency);
          drawPot(CTRL_COL_0, CTRL_ROW_0, pl7[pl7presetNr]._1_frequency_graph, pl7[pl7presetNr]._1_frequency, "1Freq", trackColor[desired_instrument]);
        }

        /* if (abs(Potentiometer[0] - pl7[pl7presetNr]._1_frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (pl7[pl7presetNr]._1_frequency_graph != Potentiometer[0]) {
              pl7[pl7presetNr]._1_frequency_graph = Potentiometer[0];
              pl7[pl7presetNr]._1_frequency = map(Potentiometer[0], 0, 127, 20, 460);
              pl7drum1.frequency(pl7[pl7presetNr]._1_frequency);
              drawPot(CTRL_COL_0, CTRL_ROW_0, pl7[pl7presetNr]._1_frequency_graph, pl7[pl7presetNr]._1_frequency, "1Freq", trackColor[desired_instrument]);
            }
          }*/
        //drum length in ms
        if (enc_moved[1]) {
          pl7[pl7presetNr]._1_length_graph = constrain((pl7[pl7presetNr]._1_length_graph + encoded[1]), 0, 127);
          pl7[pl7presetNr]._1_length = pl7[pl7presetNr]._1_length_graph * 2;
          pl7drum1.length(pl7[pl7presetNr]._1_length);
          drawPot(CTRL_COL_1, CTRL_ROW_0, pl7[pl7presetNr]._1_length_graph, pl7[pl7presetNr]._1_length, "1Decay", trackColor[desired_instrument]);
        }
        /*if (abs(Potentiometer[1] - pl7[pl7presetNr]._1_length_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7[pl7presetNr]._1_length_graph != Potentiometer[1]) {
            pl7[pl7presetNr]._1_length_graph = Potentiometer[1];
            pl7[pl7presetNr]._1_length = pl7[pl7presetNr]._1_length_graph * 2;
            pl7drum1.length(pl7[pl7presetNr]._1_length);
            drawPot(CTRL_COL_1, CTRL_ROW_0, pl7[pl7presetNr]._1_length_graph, pl7[pl7presetNr]._1_length, "1Decay", trackColor[desired_instrument]);
          }
        }*/
        if (enc_moved[2]) {
          pl7[pl7presetNr]._1_pitchMod_graph = constrain((pl7[pl7presetNr]._1_pitchMod_graph + encoded[2]), 0, 127);
          pl7[pl7presetNr]._1_pitchMod_rnd = map(pl7[pl7presetNr]._1_pitchMod_graph, 0, 127, 6, 200);
          pl7[pl7presetNr]._1_pitchMod = pl7[pl7presetNr]._1_pitchMod_rnd / 100;
          pl7drum1.pitchMod(pl7[pl7presetNr]._1_pitchMod);
          drawPot(CTRL_COL_2, CTRL_ROW_0, pl7[pl7presetNr]._1_pitchMod_graph, pl7[pl7presetNr]._1_pitchMod_graph, "1Sweep", trackColor[desired_instrument]);
        }

        /* if (abs(Potentiometer[2] - pl7[pl7presetNr]._1_pitchMod_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7[pl7presetNr]._1_pitchMod_graph != Potentiometer[2]) {
            pl7[pl7presetNr]._1_pitchMod_graph = Potentiometer[2];
            pl7[pl7presetNr]._1_pitchMod_rnd = map(pl7[pl7presetNr]._1_pitchMod_graph, 0, 127, 6, 200);
            pl7[pl7presetNr]._1_pitchMod = pl7[pl7presetNr]._1_pitchMod_rnd / 100;
            pl7drum1.pitchMod(pl7[pl7presetNr]._1_pitchMod);
            drawPot(CTRL_COL_2, CTRL_ROW_0, pl7[pl7presetNr]._1_pitchMod_graph, pl7[pl7presetNr]._1_pitchMod_graph, "1Sweep", trackColor[desired_instrument]);
          }
        }*/
        if (enc_moved[3]) {
          pl7[pl7presetNr]._1_dc1_wavefold_graph = constrain((pl7[pl7presetNr]._1_dc1_wavefold_graph + encoded[3]), 0, 127);
          pl7[pl7presetNr]._1_dc1_wavefold = pl7[pl7presetNr]._1_dc1_wavefold_graph / 127.00;
          pl7dc1.amplitude(pl7[pl7presetNr]._1_dc1_wavefold);
          drawPot(CTRL_COL_3, CTRL_ROW_0, pl7[pl7presetNr]._1_dc1_wavefold_graph, pl7[pl7presetNr]._1_dc1_wavefold_graph, "1Fold", trackColor[desired_instrument]);
        }

        /* if (abs(Potentiometer[3] - pl7[pl7presetNr]._1_dc1_wavefold_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7[pl7presetNr]._1_dc1_wavefold_graph != Potentiometer[3]) {
            pl7[pl7presetNr]._1_dc1_wavefold_graph = Potentiometer[3];
            pl7[pl7presetNr]._1_dc1_wavefold = pl7[pl7presetNr]._1_dc1_wavefold_graph / 127.00;
            pl7dc1.amplitude(pl7[pl7presetNr]._1_dc1_wavefold);
            drawPot(CTRL_COL_3, CTRL_ROW_0, pl7[pl7presetNr]._1_dc1_wavefold_graph, pl7[pl7presetNr]._1_dc1_wavefold_graph, "1Fold", trackColor[desired_instrument]);
          }
        }*/

        break;
      case 1:

        //noisemod noise level
        if (enc_moved[0]) {
          pl7[pl7presetNr]._2_noise1_amp_graph = constrain((pl7[pl7presetNr]._2_noise1_amp_graph + encoded[0]), 0, 127);
          pl7[pl7presetNr]._2_noise1_amp = pl7[pl7presetNr]._2_noise1_amp_graph / 127.00;
          pl7noise1.amplitude(pl7[pl7presetNr]._2_noise1_amp);
          drawPot(CTRL_COL_0, CTRL_ROW_1, pl7[pl7presetNr]._2_noise1_amp_graph, pl7[pl7presetNr]._2_noise1_amp_graph, "2Noise", trackColor[desired_instrument]);
        }

        /* if (abs(Potentiometer[0] - pl7[pl7presetNr]._2_noise1_amp_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7[pl7presetNr]._2_noise1_amp_graph != Potentiometer[0]) {
            pl7[pl7presetNr]._2_noise1_amp_graph = Potentiometer[0];
            pl7[pl7presetNr]._2_noise1_amp = pl7[pl7presetNr]._2_noise1_amp_graph / 127.00;
            pl7noise1.amplitude(pl7[pl7presetNr]._2_noise1_amp);
            drawPot(CTRL_COL_0, CTRL_ROW_1, pl7[pl7presetNr]._2_noise1_amp_graph, pl7[pl7presetNr]._2_noise1_amp_graph, "2Noise", trackColor[desired_instrument]);
          }
        }*/

        //noisemod modwaveform
        if (enc_moved[1]) {
          pl7[pl7presetNr]._2_wfMod_begin = constrain((pl7[pl7presetNr]._2_wfMod_begin + encoded[1]), 0, 12);
          pl7[pl7presetNr]._2_wfMod_begin_graph = pl7[pl7presetNr]._2_wfMod_begin * 10;
          pl7waveformMod1.begin(pl7[pl7presetNr]._2_wfMod_begin);
          drawPot(CTRL_COL_1, CTRL_ROW_1, pl7[pl7presetNr]._2_wfMod_begin_graph, pl7[pl7presetNr]._2_wfMod_begin, "2W~F", trackColor[desired_instrument]);
        }

        /*if (abs(Potentiometer[1] - pl7[pl7presetNr]._2_wfMod_begin_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7[pl7presetNr]._2_wfMod_begin_graph != Potentiometer[1]) {
            pl7[pl7presetNr]._2_wfMod_begin_graph = Potentiometer[1];
            pl7[pl7presetNr]._2_wfMod_begin = map(pl7[pl7presetNr]._2_wfMod_begin_graph, 0, 127, 0, 11);
            pl7waveformMod1.begin(pl7[pl7presetNr]._2_wfMod_begin);
            drawPot(CTRL_COL_1, CTRL_ROW_1, pl7[pl7presetNr]._2_wfMod_begin_graph, pl7[pl7presetNr]._2_wfMod_begin, "2W~F", trackColor[desired_instrument]);
          }
        }*/

        //noisemod frequency
        if (enc_moved[2]) {
          pl7[pl7presetNr]._2_wfMod_frequency_graph = constrain((pl7[pl7presetNr]._2_wfMod_frequency_graph + encoded[2]), 0, 127);
          pl7[pl7presetNr]._2_wfMod_frequency = map(pl7[pl7presetNr]._2_wfMod_frequency_graph, 0, 127, 1, 4064);
          pl7waveformMod1.frequency(pl7[pl7presetNr]._2_wfMod_frequency);
          drawPot(CTRL_COL_2, CTRL_ROW_1, pl7[pl7presetNr]._2_wfMod_frequency_graph, pl7[pl7presetNr]._2_wfMod_frequency, "2Freq", trackColor[desired_instrument]);
        }

        /*if (abs(Potentiometer[2] - pl7[pl7presetNr]._2_wfMod_frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7[pl7presetNr]._2_wfMod_frequency_graph != Potentiometer[2]) {
            pl7[pl7presetNr]._2_wfMod_frequency_graph = Potentiometer[2];
            pl7[pl7presetNr]._2_wfMod_frequency = pl7[pl7presetNr]._2_wfMod_frequency_graph * 32;
            pl7waveformMod1.frequency(pl7[pl7presetNr]._2_wfMod_frequency);
            drawPot(CTRL_COL_2, CTRL_ROW_1, pl7[pl7presetNr]._2_wfMod_frequency_graph, pl7[pl7presetNr]._2_wfMod_frequency, "2Freq", trackColor[desired_instrument]);
          }
        }*/

        //noisemod frequencyModulation
        if (enc_moved[3]) {
          pl7[pl7presetNr]._2_wfMod_frequencyModulation_graph = constrain((pl7[pl7presetNr]._2_wfMod_frequencyModulation_graph + encoded[3]), 0, 127);
          pl7[pl7presetNr]._2_wfMod_frequencyModulation = pl7[pl7presetNr]._2_wfMod_frequencyModulation_graph / 10.60;
          pl7waveformMod1.frequencyModulation(pl7[pl7presetNr]._2_wfMod_frequencyModulation);
          drawPot(CTRL_COL_3, CTRL_ROW_1, pl7[pl7presetNr]._2_wfMod_frequencyModulation_graph, pl7[pl7presetNr]._2_wfMod_frequencyModulation_graph, "2N-FM", trackColor[desired_instrument]);
        }

        /* if (abs(Potentiometer[3] - pl7[pl7presetNr]._2_wfMod_frequencyModulation_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl7[pl7presetNr]._2_wfMod_frequencyModulation_graph != Potentiometer[3]) {
            pl7[pl7presetNr]._2_wfMod_frequencyModulation_graph = Potentiometer[3];
            pl7[pl7presetNr]._2_wfMod_frequencyModulation = pl7[pl7presetNr]._2_wfMod_frequencyModulation_graph / 10.60;
            pl7waveformMod1.frequencyModulation(pl7[pl7presetNr]._2_wfMod_frequencyModulation);
            drawPot(CTRL_COL_3, CTRL_ROW_1, pl7[pl7presetNr]._2_wfMod_frequencyModulation_graph, pl7[pl7presetNr]._2_wfMod_frequencyModulation_graph, "2N-FM", trackColor[desired_instrument]);
          }
        }*/

        break;
      case 2:

        //Filter Frequency
        if (enc_moved[0]) {
          pl7[pl7presetNr]._2_filter_frequency_graph = constrain((pl7[pl7presetNr]._2_filter_frequency_graph + encoded[0]), 0, 127);
          pl7[pl7presetNr]._2_filter_frequency = note_frequency[pl7[pl7presetNr]._2_filter_frequency_graph];
          pl7filter2.frequency(pl7[pl7presetNr]._2_filter_frequency);
          drawPot(CTRL_COL_0, CTRL_ROW_2, pl7[pl7presetNr]._2_filter_frequency_graph, pl7[pl7presetNr]._2_filter_frequency, "2Freq", trackColor[desired_instrument]);
        }

        /*if (abs(Potentiometer[0] - pl7[pl7presetNr]._2_filter_frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        if (pl7[pl7presetNr]._2_filter_frequency_graph != Potentiometer[0]) {
          pl7[pl7presetNr]._2_filter_frequency_graph = Potentiometer[0];
          pl7[pl7presetNr]._2_filter_frequency = map(pl7[pl7presetNr]._2_filter_frequency_graph, 0, 127, 40, 5900.00);
          pl7filter2.frequency(pl7[pl7presetNr]._2_filter_frequency);
          drawPot(CTRL_COL_0, CTRL_ROW_2, pl7[pl7presetNr]._2_filter_frequency_graph, pl7[pl7presetNr]._2_filter_frequency, "2Freq", trackColor[desired_instrument]);
        }
        }*/

        //Resonance
        if (enc_moved[1]) {
          pl7[pl7presetNr]._2_filter_resonance_graph = constrain((pl7[pl7presetNr]._2_filter_resonance_graph + encoded[1]), 0, 127);
          pl7[pl7presetNr]._2_filter_resonance = pl7[pl7presetNr]._2_filter_resonance_graph / 25.40;
          pl7filter2.resonance(pl7[pl7presetNr]._2_filter_resonance);
          drawPot(CTRL_COL_1, CTRL_ROW_2, pl7[pl7presetNr]._2_filter_resonance_graph, pl7[pl7presetNr]._2_filter_resonance_graph, "2Res", trackColor[desired_instrument]);
        }

        /*if (abs(Potentiometer[1] - pl7[pl7presetNr]._2_filter_resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        if (pl7[pl7presetNr]._2_filter_resonance_graph != Potentiometer[1]) {
          pl7[pl7presetNr]._2_filter_resonance_graph = Potentiometer[1];
          pl7[pl7presetNr]._2_filter_resonance = pl7[pl7presetNr]._2_filter_resonance_graph / 25.40;
          pl7filter2.resonance(pl7[pl7presetNr]._2_filter_resonance);
          drawPot(CTRL_COL_1, CTRL_ROW_2, pl7[pl7presetNr]._2_filter_resonance_graph, pl7[pl7presetNr]._2_filter_resonance_graph, "2Res", trackColor[desired_instrument]);
        }
        }*/

        //Attack
        if (enc_moved[2]) {
          pl7[pl7presetNr]._2_Env_Attack_graph = constrain((pl7[pl7presetNr]._2_Env_Attack_graph + encoded[2]), 0, 127);
          pl7[pl7presetNr]._2_Env_Attack = map(pl7[pl7presetNr]._2_Env_Attack_graph, 0, 127, 0, 20);
          pl7envelope1.attack(pl7[pl7presetNr]._2_Env_Attack);
          //pl7envelope2.attack(pl7[pl7presetNr]._2_Env_Attack);
          drawPot(CTRL_COL_2, CTRL_ROW_2, pl7[pl7presetNr]._2_Env_Attack_graph, pl7[pl7presetNr]._2_Env_Attack, "2Att", trackColor[desired_instrument]);
        }
        /*if (abs(Potentiometer[2] - pl7[pl7presetNr]._2_Env_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        if (pl7[pl7presetNr]._2_Env_Attack_graph != Potentiometer[2]) {
          pl7[pl7presetNr]._2_Env_Attack_graph = Potentiometer[2];
          pl7[pl7presetNr]._2_Env_Attack = map(pl7[pl7presetNr]._2_Env_Attack_graph, 0, 127, 0, 20);
          pl7envelope1.attack(pl7[pl7presetNr]._2_Env_Attack);
          //pl7envelope2.attack(pl7[pl7presetNr]._2_Env_Attack);
          drawPot(CTRL_COL_2, CTRL_ROW_2, pl7[pl7presetNr]._2_Env_Attack_graph, pl7[pl7presetNr]._2_Env_Attack, "2Att", trackColor[desired_instrument]);
        }
        }*/

        //Release
        if (enc_moved[3]) {
          pl7[pl7presetNr]._2_Env_Release_graph = constrain((pl7[pl7presetNr]._2_Env_Release_graph + encoded[3]), 0, 127);
          pl7[pl7presetNr]._2_Env_Release = pl7[pl7presetNr]._2_Env_Release_graph * 2;
          pl7envelope1.release(pl7[pl7presetNr]._2_Env_Release);
          //pl7envelope2.release(pl7[pl7presetNr]._2_Env_Release);
          drawPot(CTRL_COL_3, CTRL_ROW_2, pl7[pl7presetNr]._2_Env_Release_graph, pl7[pl7presetNr]._2_Env_Release, "2Rel", trackColor[desired_instrument]);
        }

        /*if (abs(Potentiometer[3] - pl7[pl7presetNr]._2_Env_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        if (pl7[pl7presetNr]._2_Env_Release_graph != Potentiometer[3]) {
          pl7[pl7presetNr]._2_Env_Release_graph = Potentiometer[3];
          pl7[pl7presetNr]._2_Env_Release = pl7[pl7presetNr]._2_Env_Release_graph * 2;
          pl7envelope1.release(pl7[pl7presetNr]._2_Env_Release);
          //pl7envelope2.release(pl7[pl7presetNr]._2_Env_Release);
          drawPot(CTRL_COL_3, CTRL_ROW_2, pl7[pl7presetNr]._2_Env_Release_graph, pl7[pl7presetNr]._2_Env_Release, "2Rel", trackColor[desired_instrument]);
        }
        }*/

        break;
      case 3:
        break;
    }
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
  //change preset
  if (button_15) {
    if (enc_moved[3]) {
      pl7presetNr = constrain((pl7presetNr + encoded[3]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, pl7presetNr, ILI9341_PURPLE);
      Plugin7_Page_Static(1);
    }
  }
  switch (lastPotRow) {
    case 0:
      //3 modulator amplitude
      if (enc_moved[0]) {
        pl7[pl7presetNr]._3_waveformMod3_amplitude_graph = constrain((pl7[pl7presetNr]._3_waveformMod3_amplitude_graph + encoded[0]), 0, 127);
        pl7[pl7presetNr]._3_waveformMod3_amplitude = pl7[pl7presetNr]._3_waveformMod3_amplitude_graph / 127.00;
        pl7waveformMod3.amplitude(pl7[pl7presetNr]._3_waveformMod3_amplitude);
        drawPot(CTRL_COL_0, CTRL_ROW_0, pl7[pl7presetNr]._3_waveformMod3_amplitude_graph, pl7[pl7presetNr]._3_waveformMod3_amplitude_graph, "3M-Le", trackColor[desired_instrument]);
      }
      //3 modulator frequency
      if (enc_moved[1]) {
        pl7[pl7presetNr]._3_waveformMod3_frequency_graph = constrain((pl7[pl7presetNr]._3_waveformMod3_frequency_graph + encoded[1]), 0, 127);
        pl7[pl7presetNr]._3_waveformMod3_frequency = map(pl7[pl7presetNr]._3_waveformMod3_frequency_graph, 0, 127, 80, 999);
        pl7waveformMod3.frequency(pl7[pl7presetNr]._3_waveformMod3_frequency);
        drawPot(CTRL_COL_1, CTRL_ROW_0, pl7[pl7presetNr]._3_waveformMod3_frequency_graph, pl7[pl7presetNr]._3_waveformMod3_frequency_graph, "3M-Fr", trackColor[desired_instrument]);
      }
      //3 modulator attack
      if (enc_moved[2]) {
        pl7[pl7presetNr]._3_Env2_Attack_graph = constrain((pl7[pl7presetNr]._3_Env2_Attack_graph + encoded[2]), 0, 127);
        pl7[pl7presetNr]._3_Env2_Attack = map(pl7[pl7presetNr]._3_Env2_Attack_graph, 0, 127, 6, 100);
        pl7envelope2.attack(pl7[pl7presetNr]._3_Env2_Attack);
        drawPot(CTRL_COL_2, CTRL_ROW_0, pl7[pl7presetNr]._3_Env2_Attack_graph, pl7[pl7presetNr]._3_Env2_Attack, "3M-At", trackColor[desired_instrument]);
      }
      //3 modulator release
      if (enc_moved[3]) {
        pl7[pl7presetNr]._3_Env2_Release_graph = constrain((pl7[pl7presetNr]._3_Env2_Release_graph + encoded[3]), 0, 127);
        pl7[pl7presetNr]._3_Env2_Release = map(pl7[pl7presetNr]._3_Env2_Release_graph, 0, 127, 20, 800);
        pl7envelope2.release(pl7[pl7presetNr]._3_Env2_Release);
        drawPot(CTRL_COL_3, CTRL_ROW_0, pl7[pl7presetNr]._3_Env2_Release_graph, pl7[pl7presetNr]._3_Env2_Release, "3M-Rl", trackColor[desired_instrument]);
      }
      break;
    case 1:
      //3 Carrier Frequency Modulation
      if (enc_moved[0]) {
        pl7[pl7presetNr]._3_waveformMod2_frequencyModulation_graph = constrain((pl7[pl7presetNr]._3_waveformMod2_frequencyModulation_graph + encoded[0]), 0, 127);
        pl7[pl7presetNr]._3_waveformMod2_frequencyModulation = pl7[pl7presetNr]._3_waveformMod2_frequencyModulation_graph / 10.60;
        pl7waveformMod2.frequencyModulation(pl7[pl7presetNr]._3_waveformMod2_frequencyModulation);
        drawPot(CTRL_COL_0, CTRL_ROW_1, pl7[pl7presetNr]._3_waveformMod2_frequencyModulation_graph, pl7[pl7presetNr]._3_waveformMod2_frequencyModulation, "3C-Fr", trackColor[desired_instrument]);
      }
      //3 carrier frequency
      if (enc_moved[1]) {
        pl7[pl7presetNr]._3_waveformMod2_frequency_graph = constrain((pl7[pl7presetNr]._3_waveformMod2_frequency_graph + encoded[1]), 0, 127);
        pl7[pl7presetNr]._3_waveformMod2_frequency = map(pl7[pl7presetNr]._3_waveformMod2_frequency_graph, 0, 127, 80, 999);
        pl7waveformMod2.frequency(pl7[pl7presetNr]._3_waveformMod2_frequency);
        drawPot(CTRL_COL_1, CTRL_ROW_1, pl7[pl7presetNr]._3_waveformMod2_frequency_graph, pl7[pl7presetNr]._3_waveformMod2_frequency_graph, "3C-Fr", trackColor[desired_instrument]);
      }
      //3 carrier attack
      if (enc_moved[2]) {
        pl7[pl7presetNr]._3_Env3_Attack_graph = constrain((pl7[pl7presetNr]._3_Env3_Attack_graph + encoded[2]), 0, 127);
        pl7[pl7presetNr]._3_Env3_Attack = map(Potentiometer[0], 0, 127, 6, 100);
        pl7envelope2.attack(pl7[pl7presetNr]._3_Env3_Attack);
        drawPot(CTRL_COL_2, CTRL_ROW_1, pl7[pl7presetNr]._3_Env3_Attack_graph, pl7[pl7presetNr]._3_Env3_Attack, "3M-At", trackColor[desired_instrument]);
      }
      //3 carrier release
      if (enc_moved[3]) {
        pl7[pl7presetNr]._3_Env3_Release_graph = constrain((pl7[pl7presetNr]._3_Env3_Release_graph + encoded[3]), 0, 127);
        pl7[pl7presetNr]._3_Env3_Release = map(pl7[pl7presetNr]._3_Env3_Release_graph, 0, 127, 20, 800);
        pl7envelope2.release(pl7[pl7presetNr]._3_Env3_Release);
        drawPot(CTRL_COL_3, CTRL_ROW_1, pl7[pl7presetNr]._3_Env3_Release_graph, pl7[pl7presetNr]._3_Env3_Release, "3M-Rl", trackColor[desired_instrument]);
      }
      break;
    case 2:
      //4 noise mix
      if (enc_moved[0]) {
        pl7[pl7presetNr]._2_filter_frequency_graph = constrain((pl7[pl7presetNr]._2_filter_frequency_graph + encoded[0]), 0, 127);
        pl7[pl7presetNr]._2_filter_frequency = note_frequency[pl7[pl7presetNr]._2_filter_frequency_graph];
        pl7filter2.frequency(pl7[pl7presetNr]._2_filter_frequency);
        drawPot(CTRL_COL_0, CTRL_ROW_2, pl7[pl7presetNr]._2_filter_frequency_graph, pl7[pl7presetNr]._2_filter_frequency, "2Freq", trackColor[desired_instrument]);
      }
      //Resonance
      if (enc_moved[1]) {
        pl7[pl7presetNr]._2_filter_resonance_graph = constrain((pl7[pl7presetNr]._2_filter_resonance_graph + encoded[1]), 0, 127);
        pl7[pl7presetNr]._2_filter_resonance = map(pl7[pl7presetNr]._2_filter_resonance_graph, 0, 127, 70, 500.00);
        pl7filter2.resonance(pl7[pl7presetNr]._2_filter_resonance);
        drawPot(CTRL_COL_1, CTRL_ROW_2, pl7[pl7presetNr]._2_filter_resonance_graph, pl7[pl7presetNr]._2_filter_resonance_graph, "2Res", trackColor[desired_instrument]);
      }
      //Attack
      if (enc_moved[2]) {
        pl7[pl7presetNr]._2_Env_Attack_graph = constrain((pl7[pl7presetNr]._2_Env_Attack_graph + encoded[2]), 0, 127);
        pl7[pl7presetNr]._2_Env_Attack = map(pl7[pl7presetNr]._2_Env_Attack_graph, 0, 127, 0, 20);
        pl7envelope1.attack(pl7[pl7presetNr]._2_Env_Attack);
        drawPot(CTRL_COL_2, CTRL_ROW_2, pl7[pl7presetNr]._2_Env_Attack_graph, pl7[pl7presetNr]._2_Env_Attack, "2Att", trackColor[desired_instrument]);
      }
      //Release
      if (enc_moved[3]) {
        pl7[pl7presetNr]._2_Env_Release_graph = constrain((pl7[pl7presetNr]._2_Env_Release_graph + encoded[3]), 0, 127);
        pl7[pl7presetNr]._2_Env_Release = map(pl7[pl7presetNr]._2_Env_Release_graph, 0, 127, 10, 250);
        pl7envelope1.release(pl7[pl7presetNr]._2_Env_Release);
        drawPot(CTRL_COL_3, CTRL_ROW_2, pl7[pl7presetNr]._2_Env_Release_graph, pl7[pl7presetNr]._2_Env_Release, "2Rel", trackColor[desired_instrument]);
      }
      break;
  }

  if (ts.touched() || enter_button) {

    if (gridTouchY == CTRL_ROW_0) {


      //3 modulator amplitude
      /* if (abs(Potentiometer[0] - pl7[pl7presetNr]._3_waveformMod3_amplitude_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7[pl7presetNr]._3_waveformMod3_amplitude_rnd = map(Potentiometer[0], 0, 127, 0, 100);
          pl7[pl7presetNr]._3_waveformMod3_amplitude = pl7[pl7presetNr]._3_waveformMod3_amplitude_rnd / 100.00;
          pl7[pl7presetNr]._3_waveformMod3_amplitude_graph = Potentiometer[0];
          pl7waveformMod3.amplitude(pl7[pl7presetNr]._3_waveformMod3_amplitude);
          drawPot(CTRL_COL_0, CTRL_ROW_0, pl7[pl7presetNr]._3_waveformMod3_amplitude_graph, pl7[pl7presetNr]._3_waveformMod3_amplitude_rnd, "3M-Le", trackColor[desired_instrument]);
        }*/



      //3 modulator frequency
      /* if (gridTouchX == CTRL_COL_1 || gridTouchX == CTRL_COL_1 + 1) {
          drawPot(CTRL_COL_1, CTRL_ROW_0, pl7[pl7presetNr]._3_waveformMod3_frequency_graph, pl7[pl7presetNr]._3_waveformMod3_frequency, "3M-Fr", trackColor[desired_instrument]);
          if (abs(Potentiometer[0] - pl7[pl7presetNr]._3_waveformMod3_frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl7[pl7presetNr]._3_waveformMod3_frequency = map(Potentiometer[0], 0, 127, 80, 999);
            pl7[pl7presetNr]._3_waveformMod3_frequency_graph = Potentiometer[0];
            pl7waveformMod3.frequency(pl7[pl7presetNr]._3_waveformMod3_frequency);
          }
        }
        //3 modulator attack

        if (gridTouchX == CTRL_COL_2 || gridTouchX == CTRL_COL_2 + 1) {




          if (abs(Potentiometer[0] - pl7[pl7presetNr]._3_Env2_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl7[pl7presetNr]._3_Env2_Attack = map(Potentiometer[0], 0, 127, 6, 100);
            pl7[pl7presetNr]._3_Env2_Attack_graph = map(Potentiometer[0], 0, 127, 0, 800);
            pl7envelope2.attack(pl7[pl7presetNr]._3_Env2_Attack);
          }
        }
        //3 modulator release
        if (gridTouchX == CTRL_COL_3 || gridTouchX == CTRL_COL_3 + 1) {



          if (abs(Potentiometer[0] - pl7[pl7presetNr]._3_Env2_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl7[pl7presetNr]._3_Env2_Release_graph = Potentiometer[0];
            pl7[pl7presetNr]._3_Env2_Release = map(Potentiometer[0], 0, 127, 20, 800);
            pl7envelope2.release(pl7[pl7presetNr]._3_Env2_Release);
          }
        }
        }*/

      /*  if (gridTouchY == CTRL_ROW_1) {

              //3 Carrier Frequency Modulation
              if (gridTouchX == CTRL_COL_1 || gridTouchX == CTRL_COL_1 + 1) {
                drawPot(CTRL_COL_0, CTRL_ROW_1, pl7[pl7presetNr]._3_waveformMod2_frequencyModulation_graph, pl7[pl7presetNr]._3_waveformMod2_frequencyModulation, "3C-Fr", trackColor[desired_instrument]);
                if (abs(Potentiometer[0] - pl7[pl7presetNr]._3_waveformMod2_frequencyModulation_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
                  pl7[pl7presetNr]._3_waveformMod2_frequencyModulation_rnd = map(Potentiometer[0], 0, 127, 0, 1200);
                  pl7[pl7presetNr]._3_waveformMod2_frequencyModulation = pl7[pl7presetNr]._3_waveformMod2_frequencyModulation_rnd / 100.00;
                  pl7waveformMod2.frequencyModulation(pl7[pl7presetNr]._3_waveformMod2_frequencyModulation);
                }
              }


              //3 carrier frequency
              if (gridTouchX == CTRL_COL_1 || gridTouchX == CTRL_COL_1 + 1) {
                drawPot(CTRL_COL_1, CTRL_ROW_1, pl7[pl7presetNr]._3_waveformMod2_frequency_graph, pl7[pl7presetNr]._3_waveformMod2_frequency, "3C-Fr", trackColor[desired_instrument]);
                if (abs(Potentiometer[0] - pl7[pl7presetNr]._3_waveformMod2_frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
                  pl7[pl7presetNr]._3_waveformMod2_frequency = map(Potentiometer[0], 0, 127, 80, 999);
                  pl7[pl7presetNr]._3_waveformMod2_frequency_graph = Potentiometer[0];
                  pl7waveformMod2.frequency(pl7[pl7presetNr]._3_waveformMod2_frequency);
                }
              }
              //3 carrier attack

              if (gridTouchX == CTRL_COL_2 || gridTouchX == CTRL_COL_2 + 1) {
                drawPot(CTRL_COL_2, CTRL_ROW_1, pl7[pl7presetNr]._3_Env3_Attack_graph, pl7[pl7presetNr]._3_Env3_Attack, "3M-At", trackColor[desired_instrument]);
                if (abs(Potentiometer[0] - pl7[pl7presetNr]._3_Env3_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
                  pl7[pl7presetNr]._3_Env3_Attack = map(Potentiometer[0], 0, 127, 6, 100);
                  pl7[pl7presetNr]._3_Env3_Attack_graph = map(Potentiometer[0], 0, 127, 0, 800);
                  pl7envelope2.attack(pl7[pl7presetNr]._3_Env3_Attack);
                }
              }
              //3 carrier release
              if (gridTouchX == CTRL_COL_3 || gridTouchX == CTRL_COL_3 + 1) {
                drawPot(CTRL_COL_3, CTRL_ROW_1, pl7[pl7presetNr]._3_Env3_Release_graph, pl7[pl7presetNr]._3_Env3_Release, "3M-Rl", trackColor[desired_instrument]);
                if (abs(Potentiometer[0] - pl7[pl7presetNr]._3_Env3_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
                  pl7[pl7presetNr]._3_Env3_Release_graph = Potentiometer[0];
                  pl7[pl7presetNr]._3_Env3_Release = map(Potentiometer[0], 0, 127, 20, 800);
                  pl7envelope2.release(pl7[pl7presetNr]._3_Env3_Release);
                }
              }
            }
            */
      /*  if (gridTouchY == 11) {

          //4 noise mix
          if (gridTouchX == CTRL_COL_0 || gridTouchX == CTRL_COL_0 + 1) {

            if (abs(Potentiometer[0] - pl7[pl7presetNr]._2_filter_frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              pl7[pl7presetNr]._2_filter_frequency = map(Potentiometer[0], 0, 127, 40, 5900.00);
              pl7[pl7presetNr]._2_filter_frequency_graph = Potentiometer[0];
              pl7filter2.frequency(pl7[pl7presetNr]._2_filter_frequency);
              drawPot(CTRL_COL_0, 11, pl7[pl7presetNr]._2_filter_frequency_graph, pl7[pl7presetNr]._2_filter_frequency, "2Freq", trackColor[desired_instrument]);
            }
          }

          //Resonance        
          if (gridTouchX == CTRL_COL_1 || gridTouchX == CTRL_COL_1 + 1) {
            if (abs(Potentiometer[0] - pl7[pl7presetNr]._2_filter_resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              pl7[pl7presetNr]._2_filter_resonance_rnd = map(Potentiometer[0], 0, 127, 70, 500.00);
              pl7[pl7presetNr]._2_filter_resonance = pl7[pl7presetNr]._2_filter_resonance_rnd / 100.00;
              pl7[pl7presetNr]._2_filter_resonance_graph = Potentiometer[0];
              pl7filter2.resonance(pl7[pl7presetNr]._2_filter_resonance);
              drawPot(CTRL_COL_1, 11, pl7[pl7presetNr]._2_filter_resonance_graph, pl7[pl7presetNr]._2_filter_resonance_graph, "2Res", trackColor[desired_instrument]);
            }
          }
          //Attack

          if (gridTouchX == CTRL_COL_2 || gridTouchX == CTRL_COL_2 + 1) {
            if (abs(Potentiometer[0] - pl7[pl7presetNr]._2_Env_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              pl7[pl7presetNr]._2_Env_Attack = map(Potentiometer[0], 0, 127, 0, 20);
              pl7[pl7presetNr]._2_Env_Attack_graph = Potentiometer[0];
              pl7envelope1.attack(pl7[pl7presetNr]._2_Env_Attack);
              drawPot(CTRL_COL_2, 11, pl7[pl7presetNr]._2_Env_Attack_graph, pl7[pl7presetNr]._2_Env_Attack, "2Att", trackColor[desired_instrument]);
            }
          }
          //Release

          if (gridTouchX == CTRL_COL_3 || gridTouchX == CTRL_COL_3 + 1) {

            if (abs(Potentiometer[0] - pl7[pl7presetNr]._2_Env_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              pl7[pl7presetNr]._2_Env_Release = map(Potentiometer[0], 0, 127, 10, 250);
              pl7[pl7presetNr]._2_Env_Release_graph = Potentiometer[0];
              pl7envelope1.release(pl7[pl7presetNr]._2_Env_Release);
              drawPot(CTRL_COL_3, 11, pl7[pl7presetNr]._2_Env_Release_graph, pl7[pl7presetNr]._2_Env_Release, "2Rel", trackColor[desired_instrument]);
            }
          }*/
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