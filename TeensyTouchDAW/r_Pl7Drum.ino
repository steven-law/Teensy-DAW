/*void Plugin7_Settings() {


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
void Plugin7_Control1() {
  switch (lastPotRow) {

    case 0:
      if (plugin[6].preset[plpreset[6]]._1_frequency_graph != Potentiometer[0]) {
        plugin[6].preset[plpreset[6]]._1_frequency_graph = Potentiometer[0];
        plugin[6].preset[plpreset[6]]._1_frequency = map(Potentiometer[0], 0, 127, 20, 460);
        pl7drum1.frequency(plugin[6].preset[plpreset[6]]._1_frequency);
        drawPot(CTRL_COL_0, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._1_frequency_graph, plugin[6].preset[plpreset[6]]._1_frequency, "1Freq", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._1_length_graph != Potentiometer[1]) {
        plugin[6].preset[plpreset[6]]._1_length_graph = Potentiometer[1];
        plugin[6].preset[plpreset[6]]._1_length = plugin[6].preset[plpreset[6]]._1_length_graph * 2;
        pl7drum1.length(plugin[6].preset[plpreset[6]]._1_length);
        drawPot_2(CTRL_COL_1, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._1_length_graph, plugin[6].preset[plpreset[6]]._1_length, "1Decay", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._1_pitchMod_graph != Potentiometer[2]) {
        plugin[6].preset[plpreset[6]]._1_pitchMod_graph = Potentiometer[2];
        plugin[6].preset[plpreset[6]]._1_pitchMod = plugin[6].preset[plpreset[6]]._1_pitchMod_graph / 127.00;
        pl7drum1.pitchMod(plugin[6].preset[plpreset[6]]._1_pitchMod);
        drawPot_3(CTRL_COL_2, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._1_pitchMod_graph, plugin[6].preset[plpreset[6]]._1_pitchMod_graph, "1Sweep", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._1_secondMixgraph != Potentiometer[3]) {
        plugin[6].preset[plpreset[6]]._1_secondMixgraph = Potentiometer[3];
        plugin[6].preset[plpreset[6]]._1_secondMix = plugin[6].preset[plpreset[6]]._1_secondMixgraph / 4.00;
        pl7drum1.secondMix(plugin[6].preset[plpreset[6]]._1_secondMix);
        drawPot_4(CTRL_COL_3, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._1_secondMixgraph, plugin[6].preset[plpreset[6]]._1_secondMixgraph, "1Tom", trackColor[desired_instrument]);
      }
      break;
    case 1:
      /*
      if (plugin[6].preset[plpreset[6]]._1_filter_graph != Potentiometer[0]) {
        plugin[6].preset[plpreset[6]]._1_filter_graph = Potentiometer[0];
        plugin[6].preset[plpreset[6]]._1_filter = map(plugin[6].preset[plpreset[6]]._1_filter_graph, 0, 127, 20, 4600);
        pl7filter1.frequency(plugin[6].preset[plpreset[6]]._1_filter);
        drawPot(CTRL_COL_0, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._1_filter_graph, plugin[6].preset[plpreset[6]]._1_frequency, "1Fltr", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._1_resonance_graph != Potentiometer[1]) {
        plugin[6].preset[plpreset[6]]._1_resonance_graph = Potentiometer[1];
        plugin[6].preset[plpreset[6]]._1_resonance = plugin[6].preset[plpreset[6]]._1_resonance_graph / 127.00;
        pl7filter1.resonance(plugin[6].preset[plpreset[6]]._1_resonance);
        drawPot_2(CTRL_COL_1, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._1_resonance_graph, plugin[6].preset[plpreset[6]]._1_resonance_graph, "1Reso", trackColor[desired_instrument]);
      }
       if (plugin[6].preset[plpreset[6]]._1_pitchMod_graph != Potentiometer[2]) {
        plugin[6].preset[plpreset[6]]._1_pitchMod_graph = Potentiometer[2];
        plugin[6].preset[plpreset[6]]._1_pitchMod = plugin[6].preset[plpreset[6]]._1_pitchMod_graph / 127.00;
        pl7filter1.octaveControl(plugin[6].preset[plpreset[6]]._1_pitchMod);
        drawPot_3(CTRL_COL_2, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._1_pitchMod_graph, plugin[6].preset[plpreset[6]]._1_pitchMod_graph, "1Mod", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._1_dc1_wavefold_graph != Potentiometer[3]) {
        plugin[6].preset[plpreset[6]]._1_dc1_wavefold_graph = Potentiometer[3];
        plugin[6].preset[plpreset[6]]._1_dc1_wavefold = plugin[6].preset[plpreset[6]]._1_dc1_wavefold_graph / 4.00;
        pl7mixer1.gain(0, plugin[6].preset[plpreset[6]]._1_dc1_wavefold);
        drawPot_4(CTRL_COL_3, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._1_dc1_wavefold_graph, plugin[6].preset[plpreset[6]]._1_dc1_wavefold_graph, "1Gain", trackColor[desired_instrument]);
      }
      break;
    case 2:
      if (plugin[6].preset[plpreset[6]]._2_noise1_amp_graph != Potentiometer[0]) {
        plugin[6].preset[plpreset[6]]._2_noise1_amp_graph = Potentiometer[0];
        plugin[6].preset[plpreset[6]]._2_noise1_amp = plugin[6].preset[plpreset[6]]._2_noise1_amp_graph / 127.00;
        pl7noise1.amplitude(plugin[6].preset[plpreset[6]]._2_noise1_amp);
        drawPot(CTRL_COL_0, CTRL_ROW_2, plugin[6].preset[plpreset[6]]._2_noise1_amp_graph, plugin[6].preset[plpreset[6]]._2_noise1_amp_graph, "2Noise", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._2_wfMod_begin_graph != Potentiometer[1]) {
        plugin[6].preset[plpreset[6]]._2_wfMod_begin_graph = Potentiometer[1];
        plugin[6].preset[plpreset[6]]._2_wfMod_begin = map(plugin[6].preset[plpreset[6]]._2_wfMod_begin_graph, 0, 127, 0, 11);
        pl7waveformMod1.begin(plugin[6].preset[plpreset[6]]._2_wfMod_begin);
        drawPot_2(CTRL_COL_1, CTRL_ROW_2, plugin[6].preset[plpreset[6]]._2_wfMod_begin_graph, plugin[6].preset[plpreset[6]]._2_wfMod_begin, "2W~F", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._2_wfMod_frequency_graph != Potentiometer[2]) {
        plugin[6].preset[plpreset[6]]._2_wfMod_frequency_graph = Potentiometer[2];
        plugin[6].preset[plpreset[6]]._2_wfMod_frequency = plugin[6].preset[plpreset[6]]._2_wfMod_frequency_graph * 32;
        pl7waveformMod1.frequency(plugin[6].preset[plpreset[6]]._2_wfMod_frequency);
        drawPot_3(CTRL_COL_2, CTRL_ROW_2, plugin[6].preset[plpreset[6]]._2_wfMod_frequency_graph, plugin[6].preset[plpreset[6]]._2_wfMod_frequency, "2Freq", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._2_wfMod_frequencyModulation_graph != Potentiometer[3]) {
        plugin[6].preset[plpreset[6]]._2_wfMod_frequencyModulation_graph = Potentiometer[3];
        plugin[6].preset[plpreset[6]]._2_wfMod_frequencyModulation = plugin[6].preset[plpreset[6]]._2_wfMod_frequencyModulation_graph / 10.60;
        pl7waveformMod1.frequencyModulation(plugin[6].preset[plpreset[6]]._2_wfMod_frequencyModulation);
        drawPot_4(CTRL_COL_3, CTRL_ROW_2, plugin[6].preset[plpreset[6]]._2_wfMod_frequencyModulation_graph, plugin[6].preset[plpreset[6]]._2_wfMod_frequencyModulation_graph, "2N-FM", trackColor[desired_instrument]);
      }
      break;
    case 3:
      if (plugin[6].preset[plpreset[6]]._2_filter_frequency_graph != Potentiometer[0]) {
        plugin[6].preset[plpreset[6]]._2_filter_frequency_graph = Potentiometer[0];
        plugin[6].preset[plpreset[6]]._2_filter_frequency = map(plugin[6].preset[plpreset[6]]._2_filter_frequency_graph, 0, 127, 40, 5900.00);
        pl7filter2.frequency(plugin[6].preset[plpreset[6]]._2_filter_frequency);
        drawPot(CTRL_COL_0, CTRL_ROW_3, plugin[6].preset[plpreset[6]]._2_filter_frequency_graph, plugin[6].preset[plpreset[6]]._2_filter_frequency, "2Freq", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._2_filter_resonance_graph != Potentiometer[1]) {
        plugin[6].preset[plpreset[6]]._2_filter_resonance_graph = Potentiometer[1];
        plugin[6].preset[plpreset[6]]._2_filter_resonance = plugin[6].preset[plpreset[6]]._2_filter_resonance_graph / 25.40;
        pl7filter2.resonance(plugin[6].preset[plpreset[6]]._2_filter_resonance);
        drawPot_2(CTRL_COL_1, CTRL_ROW_3, plugin[6].preset[plpreset[6]]._2_filter_resonance_graph, plugin[6].preset[plpreset[6]]._2_filter_resonance_graph, "2Res", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._2_Env_Attack_graph != Potentiometer[2]) {
        plugin[6].preset[plpreset[6]]._2_Env_Attack_graph = Potentiometer[2];
        plugin[6].preset[plpreset[6]]._2_Env_Attack = map(plugin[6].preset[plpreset[6]]._2_Env_Attack_graph, 0, 127, 0, 20);
        pl7envelope1.attack(plugin[6].preset[plpreset[6]]._2_Env_Attack);
        //pl7envelope2.attack(plugin[6].preset[plpreset[6]]._2_Env_Attack);
        drawPot_3(CTRL_COL_2, CTRL_ROW_3, plugin[6].preset[plpreset[6]]._2_Env_Attack_graph, plugin[6].preset[plpreset[6]]._2_Env_Attack, "2Att", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._2_Env_Release_graph != Potentiometer[3]) {
        plugin[6].preset[plpreset[6]]._2_Env_Release_graph = Potentiometer[3];
        plugin[6].preset[plpreset[6]]._2_Env_Release = plugin[6].preset[plpreset[6]]._2_Env_Release_graph * 2;
        pl7envelope1.release(plugin[6].preset[plpreset[6]]._2_Env_Release);
        //pl7envelope2.release(plugin[6].preset[plpreset[6]]._2_Env_Release);
        drawPot_4(CTRL_COL_3, CTRL_ROW_3, plugin[6].preset[plpreset[6]]._2_Env_Release_graph, plugin[6].preset[plpreset[6]]._2_Env_Release, "2Rel", trackColor[desired_instrument]);
      }
      break;
  }
}
void Plugin7_Control2() {
  switch (lastPotRow) {
    case 0:
      if (plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_graph != Potentiometer[0]) {
        plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_graph = Potentiometer[0];
        plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude = plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_graph / 127.00;
        pl7waveformMod3.amplitude(plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude);
        drawPot(CTRL_COL_0, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_graph, plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_graph, "3M-Le", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency_graph != Potentiometer[1]) {
        plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency_graph = Potentiometer[1];
        plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency = map(plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency_graph, 0, 127, 80, 999);
        pl7waveformMod3.frequency(plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency);
        drawPot(CTRL_COL_1, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency_graph, plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency_graph, "3M-Fr", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._3_Env2_Attack_graph != Potentiometer[2]) {
        plugin[6].preset[plpreset[6]]._3_Env2_Attack_graph = Potentiometer[2];
        plugin[6].preset[plpreset[6]]._3_Env2_Attack = map(plugin[6].preset[plpreset[6]]._3_Env2_Attack_graph, 0, 127, 0, 100);
        pl7envelope2.attack(plugin[6].preset[plpreset[6]]._3_Env2_Attack);
        drawPot(CTRL_COL_2, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._3_Env2_Attack_graph, plugin[6].preset[plpreset[6]]._3_Env2_Attack, "3M-At", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._3_Env2_Release_graph != Potentiometer[3]) {
        plugin[6].preset[plpreset[6]]._3_Env2_Release_graph = Potentiometer[3];
        plugin[6].preset[plpreset[6]]._3_Env2_Release = map(plugin[6].preset[plpreset[6]]._3_Env2_Release_graph, 0, 127, 20, 800);
        pl7envelope2.release(plugin[6].preset[plpreset[6]]._3_Env2_Release);
        drawPot(CTRL_COL_3, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._3_Env2_Release_graph, plugin[6].preset[plpreset[6]]._3_Env2_Release, "3M-Rl", trackColor[desired_instrument]);
      }
      break;
    case 1:
      if (plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation_graph != Potentiometer[0]) {
        plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation_graph = Potentiometer[0];
        plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation = plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation_graph / 10.60;
        pl7waveformMod2.frequencyModulation(plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation);
        drawPot(CTRL_COL_0, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation_graph, plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation, "3C-Fr", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency_graph != Potentiometer[1]) {
        plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency_graph = Potentiometer[1];
        plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency = map(plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency_graph, 0, 127, 80, 999);
        pl7waveformMod2.frequency(plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency);
        drawPot(CTRL_COL_1, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency_graph, plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency_graph, "3C-Fr", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._3_Env3_Attack_graph != Potentiometer[2]) {
        plugin[6].preset[plpreset[6]]._3_Env3_Attack_graph = Potentiometer[2];
        plugin[6].preset[plpreset[6]]._3_Env3_Attack = map(plugin[6].preset[plpreset[6]]._3_Env3_Attack_graph, 0, 127, 0, 100);
        pl7envelope2.attack(plugin[6].preset[plpreset[6]]._3_Env3_Attack);
        drawPot(CTRL_COL_2, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._3_Env3_Attack_graph, plugin[6].preset[plpreset[6]]._3_Env3_Attack, "3M-At", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._3_Env3_Release_graph != Potentiometer[3]) {
        plugin[6].preset[plpreset[6]]._3_Env3_Release_graph = Potentiometer[3];
        plugin[6].preset[plpreset[6]]._3_Env3_Release = map(plugin[6].preset[plpreset[6]]._3_Env3_Release_graph, 0, 127, 20, 800);
        pl7envelope2.release(plugin[6].preset[plpreset[6]]._3_Env3_Release);
        drawPot(CTRL_COL_3, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._3_Env3_Release_graph, plugin[6].preset[plpreset[6]]._3_Env3_Release, "3M-Rl", trackColor[desired_instrument]);
      }
      break;
    case 2:
      if (plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_graph != Potentiometer[0]) {
        plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_graph = Potentiometer[0];
        plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude = plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_graph / 127.00;
        pl7waveformMod3.amplitude(plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude);
        drawPot(CTRL_COL_0, CTRL_ROW_2, plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_graph, plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_graph, "3M-Le", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency_graph != Potentiometer[1]) {
        plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency_graph = Potentiometer[1];
        plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency = map(plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency_graph, 0, 127, 80, 999);
        pl7waveformMod3.frequency(plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency);
        drawPot(CTRL_COL_1, CTRL_ROW_2, plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency_graph, plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency_graph, "3M-Fr", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._3_Env2_Attack_graph != Potentiometer[2]) {
        plugin[6].preset[plpreset[6]]._3_Env2_Attack_graph = Potentiometer[2];
        plugin[6].preset[plpreset[6]]._3_Env2_Attack = map(plugin[6].preset[plpreset[6]]._3_Env2_Attack_graph, 0, 127, 0, 100);
        pl7envelope2.attack(plugin[6].preset[plpreset[6]]._3_Env2_Attack);
        drawPot(CTRL_COL_2, CTRL_ROW_2, plugin[6].preset[plpreset[6]]._3_Env2_Attack_graph, plugin[6].preset[plpreset[6]]._3_Env2_Attack, "3M-At", trackColor[desired_instrument]);
      }
      if (plugin[6].preset[plpreset[6]]._3_Env2_Release_graph != Potentiometer[3]) {
        plugin[6].preset[plpreset[6]]._3_Env2_Release_graph = Potentiometer[3];
        plugin[6].preset[plpreset[6]]._3_Env2_Release = map(plugin[6].preset[plpreset[6]]._3_Env2_Release_graph, 0, 127, 20, 800);
        pl7envelope2.release(plugin[6].preset[plpreset[6]]._3_Env2_Release);
        drawPot(CTRL_COL_3, CTRL_ROW_2, plugin[6].preset[plpreset[6]]._3_Env2_Release_graph, plugin[6].preset[plpreset[6]]._3_Env2_Release, "3M-Rl", trackColor[desired_instrument]);
      }
      break;
    case 3:
      break;
  }
}
void Plugin7_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      plpreset[6] = constrain((plpreset[6] + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[6], ILI9341_PURPLE);
      //Plugin7_Page_Static(0);
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:

        Potentiometer[0] = plugin[6].preset[plpreset[6]]._1_frequency_graph;
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((plugin[6].preset[plpreset[6]]._1_frequency_graph + encoded[0]), 0, 127);
        }

        //drum length in ms
        Potentiometer[1] = plugin[6].preset[plpreset[6]]._1_length_graph;
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((plugin[6].preset[plpreset[6]]._1_length_graph + encoded[1]), 0, 127);
        }

        Potentiometer[2] = plugin[6].preset[plpreset[6]]._1_pitchMod_graph;
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((plugin[6].preset[plpreset[6]]._1_pitchMod_graph + encoded[2]), 0, 127);
        }

        Potentiometer[3] = plugin[6].preset[plpreset[6]]._1_secondMixgraph;
        if (enc_moved[3]) {
          Potentiometer[3] = constrain((plugin[6].preset[plpreset[6]]._1_secondMixgraph + encoded[3]), 0, 127);
        }



        break;
      case 1:

        Potentiometer[0] = plugin[6].preset[plpreset[6]]._1_filter_graph;
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((plugin[6].preset[plpreset[6]]._1_filter_graph + encoded[0]), 0, 127);
        }

        //drum length in ms
        Potentiometer[1] = plugin[6].preset[plpreset[6]]._1_resonance_graph;
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((plugin[6].preset[plpreset[6]]._1_resonance_graph + encoded[1]), 0, 127);
        }
        /*
        Potentiometer[2] = plugin[6].preset[plpreset[6]]._1_pitchMod_graph;
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((plugin[6].preset[plpreset[6]]._1_pitchMod_graph + encoded[2]), 0, 127);
        }
       
        Potentiometer[3] = plugin[6].preset[plpreset[6]]._1_dc1_wavefold_graph;
        if (enc_moved[3]) {
          Potentiometer[3] = constrain((plugin[6].preset[plpreset[6]]._1_dc1_wavefold_graph + encoded[3]), 0, 127);
        }



        break;
      case 2:

        //noisemod noise level
        Potentiometer[0] = plugin[6].preset[plpreset[6]]._2_noise1_amp_graph;
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((plugin[6].preset[plpreset[6]]._2_noise1_amp_graph + encoded[0]), 0, 127);
        }

        //noisemod modwaveform
        Potentiometer[1] = plugin[6].preset[plpreset[6]]._2_wfMod_begin * 11;
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((plugin[6].preset[plpreset[6]]._2_wfMod_begin + encoded[1]), 0, 12) * 11;
        }

        //noisemod frequency
        Potentiometer[2] = plugin[6].preset[plpreset[6]]._2_wfMod_frequency_graph;
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((plugin[6].preset[plpreset[6]]._2_wfMod_frequency_graph + encoded[2]), 0, 127);
        }

        //noisemod frequencyModulation
        Potentiometer[3] = plugin[6].preset[plpreset[6]]._2_wfMod_frequencyModulation_graph;
        if (enc_moved[3]) {
          Potentiometer[3] = constrain((plugin[6].preset[plpreset[6]]._2_wfMod_frequencyModulation_graph + encoded[3]), 0, 127);
        }



        break;
      case 3:

        //Filter Frequency
        Potentiometer[0] = plugin[6].preset[plpreset[6]]._2_filter_frequency_graph;
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((plugin[6].preset[plpreset[6]]._2_filter_frequency_graph + encoded[0]), 0, 127);
        }

        //Resonance
        Potentiometer[1] = plugin[6].preset[plpreset[6]]._2_filter_resonance_graph;
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((plugin[6].preset[plpreset[6]]._2_filter_resonance_graph + encoded[1]), 0, 127);
        }

        //Attack
        Potentiometer[2] = plugin[6].preset[plpreset[6]]._2_Env_Attack_graph;
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((plugin[6].preset[plpreset[6]]._2_Env_Attack_graph + encoded[2]), 0, 127);
        }

        //Release
        Potentiometer[3] = plugin[6].preset[plpreset[6]]._2_Env_Release_graph;
        if (enc_moved[3]) {
          Potentiometer[3] = constrain((plugin[6].preset[plpreset[6]]._2_Env_Release_graph + encoded[3]), 0, 127);
        }
        break;
    }
  }
  if (ts.touched() || button[15]) {
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
        //Plugin7_Page_Static(0);
        //Plugin7_Page1_Dynamic();
      }
      if (gridTouchY >= 5 && gridTouchY <= 6) {
        selectPage = PLUGIN7_PAGE2;
        //Plugin7_Page_Static(1);
        //Plugin7_Page2_Dynamic();
      }
      /* if (gridTouchY >= 7 && gridTouchY <= 8) {
        selectPage = PLUGIN7_PAGE3);
        //Plugin7_Page_Static(2);
        //Plugin7_Page3_Dynamic();
      }
    }
  }
}
void Plugin7_Page2_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[3]) {
      lastPotRow = 10;
      plpreset[6] = constrain((plpreset[6] + encoded[3]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[6], ILI9341_PURPLE);
      //Plugin7_Page_Static(1);
    }
  }
  switch (lastPotRow) {
    case 0:
      //3 modulator amplitude
      Potentiometer[0] = plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_graph;
      if (enc_moved[0]) {
        Potentiometer[0] = constrain((plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_graph + encoded[0]), 0, 127);
      }
      //3 modulator frequency
      Potentiometer[1] = plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency_graph;
      if (enc_moved[1]) {
        Potentiometer[1] = constrain((plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency_graph + encoded[1]), 0, 127);
      }
      //3 modulator attack
      Potentiometer[2] = plugin[6].preset[plpreset[6]]._3_Env2_Attack_graph;
      if (enc_moved[2]) {
        Potentiometer[2] = constrain((plugin[6].preset[plpreset[6]]._3_Env2_Attack_graph + encoded[2]), 0, 127);
      }
      //3 modulator release
      Potentiometer[3] = plugin[6].preset[plpreset[6]]._3_Env2_Release_graph;
      if (enc_moved[3]) {
        Potentiometer[3] = constrain((plugin[6].preset[plpreset[6]]._3_Env2_Release_graph + encoded[3]), 0, 127);
      }
      break;
    case 1:
      //3 Carrier Frequency Modulation
      Potentiometer[0] = plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation_graph;
      if (enc_moved[0]) {
        Potentiometer[0] = constrain((plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation_graph + encoded[0]), 0, 127);
      }
      //3 carrier frequency
      Potentiometer[1] = plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency_graph;
      if (enc_moved[1]) {
        Potentiometer[1] = constrain((plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency_graph + encoded[1]), 0, 127);
      }
      //3 carrier attack
      Potentiometer[2] = plugin[6].preset[plpreset[6]]._3_Env3_Attack_graph;
      if (enc_moved[2]) {
        Potentiometer[2] = constrain((plugin[6].preset[plpreset[6]]._3_Env3_Attack_graph + encoded[2]), 0, 127);
      }
      //3 carrier release
      Potentiometer[3] = plugin[6].preset[plpreset[6]]._3_Env3_Release_graph;
      if (enc_moved[3]) {
        Potentiometer[3] = constrain((plugin[6].preset[plpreset[6]]._3_Env3_Release_graph + encoded[3]), 0, 127);
      }
      break;
    case 2:
      //4 noise mix
      Potentiometer[0] = plugin[6].preset[plpreset[6]]._2_filter_frequency_graph;
      if (enc_moved[0]) {
        Potentiometer[0] = constrain((plugin[6].preset[plpreset[6]]._2_filter_frequency_graph + encoded[0]), 0, 127);
      }
      //Resonance
      Potentiometer[1] = plugin[6].preset[plpreset[6]]._2_filter_resonance_graph;
      if (enc_moved[1]) {
        Potentiometer[1] = constrain((plugin[6].preset[plpreset[6]]._2_filter_resonance_graph + encoded[1]), 0, 127);
      }
      //Attack
      Potentiometer[2] = plugin[6].preset[plpreset[6]]._2_Env_Attack_graph;
      if (enc_moved[2]) {
        Potentiometer[2] = constrain((plugin[6].preset[plpreset[6]]._2_Env_Attack_graph + encoded[2]), 0, 127);
      }
      //Release
      Potentiometer[3] = plugin[6].preset[plpreset[6]]._2_Env_Release_graph;
      if (enc_moved[3]) {
        Potentiometer[3] = constrain((plugin[6].preset[plpreset[6]]._2_Env_Release_graph + encoded[3]), 0, 127);
      }
      break;
  }

  if (ts.touched() || button[15]) {

    if (gridTouchY == CTRL_ROW_0) {


      //3 modulator amplitude
      /* if (abs(Potentiometer[0] - plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_rnd = map(Potentiometer[0], 0, 127, 0, 100);
          plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude = plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_rnd / 100.00;
          plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_graph = Potentiometer[0];
          pl7waveformMod3.amplitude(plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude);
          drawPot(CTRL_COL_0, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_graph, plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_rnd, "3M-Le", trackColor[desired_instrument]);
        }*/



      //3 modulator frequency
      /* if (gridTouchX == CTRL_COL_1 || gridTouchX == CTRL_COL_1 + 1) {
          drawPot(CTRL_COL_1, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency_graph, plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency, "3M-Fr", trackColor[desired_instrument]);
          if (abs(Potentiometer[0] - plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency = map(Potentiometer[0], 0, 127, 80, 999);
            plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency_graph = Potentiometer[0];
            pl7waveformMod3.frequency(plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency);
          }
        }
        //3 modulator attack

        if (gridTouchX == CTRL_COL_2 || gridTouchX == CTRL_COL_2 + 1) {




          if (abs(Potentiometer[0] - plugin[6].preset[plpreset[6]]._3_Env2_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            plugin[6].preset[plpreset[6]]._3_Env2_Attack = map(Potentiometer[0], 0, 127, 6, 100);
            plugin[6].preset[plpreset[6]]._3_Env2_Attack_graph = map(Potentiometer[0], 0, 127, 0, 800);
            pl7envelope2.attack(plugin[6].preset[plpreset[6]]._3_Env2_Attack);
          }
        }
        //3 modulator release
        if (gridTouchX == CTRL_COL_3 || gridTouchX == CTRL_COL_3 + 1) {



          if (abs(Potentiometer[0] - plugin[6].preset[plpreset[6]]._3_Env2_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            plugin[6].preset[plpreset[6]]._3_Env2_Release_graph = Potentiometer[0];
            plugin[6].preset[plpreset[6]]._3_Env2_Release = map(Potentiometer[0], 0, 127, 20, 800);
            pl7envelope2.release(plugin[6].preset[plpreset[6]]._3_Env2_Release);
          }
        }
        }*/

      /*  if (gridTouchY == CTRL_ROW_1) {

              //3 Carrier Frequency Modulation
              if (gridTouchX == CTRL_COL_1 || gridTouchX == CTRL_COL_1 + 1) {
                drawPot(CTRL_COL_0, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation_graph, plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation, "3C-Fr", trackColor[desired_instrument]);
                if (abs(Potentiometer[0] - plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
                  plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation_rnd = map(Potentiometer[0], 0, 127, 0, 1200);
                  plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation = plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation_rnd / 100.00;
                  pl7waveformMod2.frequencyModulation(plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation);
                }
              }


              //3 carrier frequency
              if (gridTouchX == CTRL_COL_1 || gridTouchX == CTRL_COL_1 + 1) {
                drawPot(CTRL_COL_1, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency_graph, plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency, "3C-Fr", trackColor[desired_instrument]);
                if (abs(Potentiometer[0] - plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
                  plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency = map(Potentiometer[0], 0, 127, 80, 999);
                  plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency_graph = Potentiometer[0];
                  pl7waveformMod2.frequency(plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency);
                }
              }
              //3 carrier attack

              if (gridTouchX == CTRL_COL_2 || gridTouchX == CTRL_COL_2 + 1) {
                drawPot(CTRL_COL_2, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._3_Env3_Attack_graph, plugin[6].preset[plpreset[6]]._3_Env3_Attack, "3M-At", trackColor[desired_instrument]);
                if (abs(Potentiometer[0] - plugin[6].preset[plpreset[6]]._3_Env3_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
                  plugin[6].preset[plpreset[6]]._3_Env3_Attack = map(Potentiometer[0], 0, 127, 6, 100);
                  plugin[6].preset[plpreset[6]]._3_Env3_Attack_graph = map(Potentiometer[0], 0, 127, 0, 800);
                  pl7envelope2.attack(plugin[6].preset[plpreset[6]]._3_Env3_Attack);
                }
              }
              //3 carrier release
              if (gridTouchX == CTRL_COL_3 || gridTouchX == CTRL_COL_3 + 1) {
                drawPot(CTRL_COL_3, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._3_Env3_Release_graph, plugin[6].preset[plpreset[6]]._3_Env3_Release, "3M-Rl", trackColor[desired_instrument]);
                if (abs(Potentiometer[0] - plugin[6].preset[plpreset[6]]._3_Env3_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
                  plugin[6].preset[plpreset[6]]._3_Env3_Release_graph = Potentiometer[0];
                  plugin[6].preset[plpreset[6]]._3_Env3_Release = map(Potentiometer[0], 0, 127, 20, 800);
                  pl7envelope2.release(plugin[6].preset[plpreset[6]]._3_Env3_Release);
                }
              }
            }
            */
      /*  if (gridTouchY == 11) {

          //4 noise mix
          if (gridTouchX == CTRL_COL_0 || gridTouchX == CTRL_COL_0 + 1) {

            if (abs(Potentiometer[0] - plugin[6].preset[plpreset[6]]._2_filter_frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              plugin[6].preset[plpreset[6]]._2_filter_frequency = map(Potentiometer[0], 0, 127, 40, 5900.00);
              plugin[6].preset[plpreset[6]]._2_filter_frequency_graph = Potentiometer[0];
              pl7filter2.frequency(plugin[6].preset[plpreset[6]]._2_filter_frequency);
              drawPot(CTRL_COL_0, 11, plugin[6].preset[plpreset[6]]._2_filter_frequency_graph, plugin[6].preset[plpreset[6]]._2_filter_frequency, "2Freq", trackColor[desired_instrument]);
            }
          }

          //Resonance        
          if (gridTouchX == CTRL_COL_1 || gridTouchX == CTRL_COL_1 + 1) {
            if (abs(Potentiometer[0] - plugin[6].preset[plpreset[6]]._2_filter_resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              plugin[6].preset[plpreset[6]]._2_filter_resonance_rnd = map(Potentiometer[0], 0, 127, 70, 500.00);
              plugin[6].preset[plpreset[6]]._2_filter_resonance = plugin[6].preset[plpreset[6]]._2_filter_resonance_rnd / 100.00;
              plugin[6].preset[plpreset[6]]._2_filter_resonance_graph = Potentiometer[0];
              pl7filter2.resonance(plugin[6].preset[plpreset[6]]._2_filter_resonance);
              drawPot(CTRL_COL_1, 11, plugin[6].preset[plpreset[6]]._2_filter_resonance_graph, plugin[6].preset[plpreset[6]]._2_filter_resonance_graph, "2Res", trackColor[desired_instrument]);
            }
          }
          //Attack

          if (gridTouchX == CTRL_COL_2 || gridTouchX == CTRL_COL_2 + 1) {
            if (abs(Potentiometer[0] - plugin[6].preset[plpreset[6]]._2_Env_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              plugin[6].preset[plpreset[6]]._2_Env_Attack = map(Potentiometer[0], 0, 127, 0, 20);
              plugin[6].preset[plpreset[6]]._2_Env_Attack_graph = Potentiometer[0];
              pl7envelope1.attack(plugin[6].preset[plpreset[6]]._2_Env_Attack);
              drawPot(CTRL_COL_2, 11, plugin[6].preset[plpreset[6]]._2_Env_Attack_graph, plugin[6].preset[plpreset[6]]._2_Env_Attack, "2Att", trackColor[desired_instrument]);
            }
          }
          //Release

          if (gridTouchX == CTRL_COL_3 || gridTouchX == CTRL_COL_3 + 1) {

            if (abs(Potentiometer[0] - plugin[6].preset[plpreset[6]]._2_Env_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
              plugin[6].preset[plpreset[6]]._2_Env_Release = map(Potentiometer[0], 0, 127, 10, 250);
              plugin[6].preset[plpreset[6]]._2_Env_Release_graph = Potentiometer[0];
              pl7envelope1.release(plugin[6].preset[plpreset[6]]._2_Env_Release);
              drawPot(CTRL_COL_3, 11, plugin[6].preset[plpreset[6]]._2_Env_Release_graph, plugin[6].preset[plpreset[6]]._2_Env_Release, "2Rel", trackColor[desired_instrument]);
            }
          }
    }

    if (gridTouchX >= 18) {
      //page selection
      if (gridTouchY >= 3 && gridTouchY <= 4) {
        selectPage = PLUGIN7_PAGE1;
        //Plugin7_Page_Static(0);
        //Plugin7_Page1_Dynamic();
      }
      if (gridTouchY >= 5 && gridTouchY <= 6) {
        selectPage = PLUGIN7_PAGE2;
        //Plugin7_Page_Static(1);
        //Plugin7_Page2_Dynamic();
      }
      /*if (gridTouchY >= 7 && gridTouchY <= 8) {
        selectPage = PLUGIN7_PAGE3;
        //Plugin7_Page_Static(2);
        //Plugin7_Page3_Dynamic();
      }
    }
  }
}
void Plugin7_Page_Static(int Pagenumber) {
  clearWorkSpace();
  //Plugin7_Change();
  //draw selecting pages buttons
  draw_sub_page_buttons(2);
  drawNrInRect(18, 1, plpreset[6], ILI9341_PURPLE);
  if (Pagenumber == 0) {
    drawPot(CTRL_COL_0, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._1_frequency_graph, plugin[6].preset[plpreset[6]]._1_frequency, "1Freq", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._1_length_graph, plugin[6].preset[plpreset[6]]._1_length, "1Decay", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._1_pitchMod_graph, plugin[6].preset[plpreset[6]]._1_pitchMod_graph, "1Sweep", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._1_dc1_wavefold_graph, plugin[6].preset[plpreset[6]]._1_dc1_wavefold_graph, "1Tom", trackColor[desired_instrument]);

    
    drawPot(CTRL_COL_0, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._1_filter_graph, plugin[6].preset[plpreset[6]]._1_frequency, "1Fltr", trackColor[desired_instrument]);
    drawPot_2(CTRL_COL_1, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._1_resonance_graph, plugin[6].preset[plpreset[6]]._1_resonance_graph, "1Reso", trackColor[desired_instrument]);
    drawPot_3(CTRL_COL_2, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._1_pitchMod_graph, plugin[6].preset[plpreset[6]]._1_pitchMod_graph, "1Mod", trackColor[desired_instrument]);
    
    drawPot_4(CTRL_COL_3, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._1_dc1_wavefold_graph, plugin[6].preset[plpreset[6]]._1_dc1_wavefold_graph, "1Gain", trackColor[desired_instrument]);

    drawPot(CTRL_COL_0, CTRL_ROW_2, plugin[6].preset[plpreset[6]]._2_noise1_amp_graph, plugin[6].preset[plpreset[6]]._2_noise1_amp_graph, "2Noise", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_2, plugin[6].preset[plpreset[6]]._2_wfMod_begin_graph, plugin[6].preset[plpreset[6]]._2_wfMod_begin, "2W~F", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_2, plugin[6].preset[plpreset[6]]._2_wfMod_frequency_graph, plugin[6].preset[plpreset[6]]._2_wfMod_frequency, "2Freq", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_2, plugin[6].preset[plpreset[6]]._2_wfMod_frequencyModulation_graph, plugin[6].preset[plpreset[6]]._2_wfMod_frequencyModulation_graph, "2N-FM", trackColor[desired_instrument]);

    drawPot(CTRL_COL_0, CTRL_ROW_3, plugin[6].preset[plpreset[6]]._2_filter_frequency_graph, plugin[6].preset[plpreset[6]]._2_filter_frequency, "2Freq", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_3, plugin[6].preset[plpreset[6]]._2_filter_resonance_graph, plugin[6].preset[plpreset[6]]._2_filter_resonance_graph, "2Res", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_3, plugin[6].preset[plpreset[6]]._2_Env_Attack_graph, plugin[6].preset[plpreset[6]]._2_Env_Attack, "2Att", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_3, plugin[6].preset[plpreset[6]]._2_Env_Release_graph, plugin[6].preset[plpreset[6]]._2_Env_Release, "2Rel", trackColor[desired_instrument]);
  }
  if (Pagenumber == 1) {
    drawPot(CTRL_COL_0, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_graph, plugin[6].preset[plpreset[6]]._3_waveformMod3_amplitude_rnd, "3M-Le", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency_graph, plugin[6].preset[plpreset[6]]._3_waveformMod3_frequency, "3M-Fr", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._3_Env2_Attack_graph, plugin[6].preset[plpreset[6]]._3_Env2_Attack, "3M-At", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_0, plugin[6].preset[plpreset[6]]._3_Env2_Release_graph, plugin[6].preset[plpreset[6]]._3_Env2_Release, "3M-Rl", trackColor[desired_instrument]);

    drawPot(CTRL_COL_0, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation_graph, plugin[6].preset[plpreset[6]]._3_waveformMod2_frequencyModulation, "3C-Fr", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency_graph, plugin[6].preset[plpreset[6]]._3_waveformMod2_frequency, "3C-Fr", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._3_Env3_Attack_graph, plugin[6].preset[plpreset[6]]._3_Env3_Attack, "3M-At", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_1, plugin[6].preset[plpreset[6]]._3_Env3_Release_graph, plugin[6].preset[plpreset[6]]._3_Env3_Release, "3M-Rl", trackColor[desired_instrument]);

    /* 
    drawPot(CTRL_COL_0, CTRL_ROW_2, plugin[6].preset[plpreset[6]]._2_filter_frequency_graph, plugin[6].preset[plpreset[6]]._2_filter_frequency, "2Freq", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_2, plugin[6].preset[plpreset[6]]._2_filter_resonance_graph, plugin[6].preset[plpreset[6]]._2_filter_resonance_graph, "2Res", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_2, plugin[6].preset[plpreset[6]]._2_Env_Attack_graph, plugin[6].preset[plpreset[6]]._2_Env_Attack, "2Att", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_2, plugin[6].preset[plpreset[6]]._2_Env_Release_graph, plugin[6].preset[plpreset[6]]._2_Env_Release, "2Rel", trackColor[desired_instrument]);
    
  }
}
void Plugin7_Change() {}
*/