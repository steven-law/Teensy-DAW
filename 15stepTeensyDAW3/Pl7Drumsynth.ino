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

  pl7envelope2.delay(0);  //Env Modulator
  pl7envelope2.attack(5);
  pl7envelope2.hold(1);
  pl7envelope2.decay(50);
  pl7envelope2.sustain(0);
  pl7envelope2.release(20);

  //pl7waveformMod3.begin(1, 3500, WAVEFORM_SINE);  //Modulator OSC
  //pl7waveformMod2.begin(1, 3500, WAVEFORM_SINE);  //Carrier OSC
  //pl7waveformMod2.frequencyModulation(1);

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
  //draw selecting pages buttons
  draw_sub_page_buttons(2);

  drawPot(3, 3, pl7drum1_frequency_graph, pl7drum1_frequency, "1Freq", ILI9341_RED);
  drawPot(7, 3, pl7drum1_length_graph, pl7drum1_length, "1Decay", ILI9341_RED);
  drawPot(11, 3, pl7drum1_pitchMod_graph, pl7drum1_pitchMod_rnd, "1Sweep", ILI9341_RED);
  drawPot(15, 3, pl7dc1_amplitude_graph, pl7dc1_amplitude_graph, "1Fold", ILI9341_RED);

  drawPot(3, 7, pl7noise1_amplitude_graph, pl7noise1_amplitude_graph, "2Noise", ILI9341_BLUE);
  drawPot(7, 7, pl7waveformMod1_begin_graph, pl7waveformMod1_begin, "2W~F", ILI9341_BLUE);
  drawPot(11, 7, pl7waveformMod1_frequency_graph, pl7waveformMod1_frequency, "2Freq", ILI9341_BLUE);
  drawPot(15, 7, pl7waveformMod1_frequencyModulation_graph, pl7waveformMod1_frequencyModulation_graph, "2N-FM", ILI9341_BLUE);

  drawPot(3, 11, pl7filter2_frequency_graph, pl7filter2_frequency, "2Freq", ILI9341_BLUE);
  drawPot(7, 11, pl7filter2_resonance_graph, pl7filter2_resonance_graph, "2Res", ILI9341_BLUE);
  drawPot(11, 11, pl7Env1_Attack_graph, pl7Env1_Attack, "2Att", ILI9341_BLUE);
  drawPot(15, 11, pl7Env1_Release_graph, pl7Env1_Release, "2Rel", ILI9341_BLUE);
}


void Plugin7_Page1_Dynamic() {


  if (ts.touched() || !buttons[6].read()) {
    if (gridTouchY == 3) {

      //drum1 root frequency
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, 3, pl7drum1_frequency_graph, pl7drum1_frequency, "1Freq", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl7drum1_frequency_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7drum1_frequency = map(Potentiometer1, 0, 1023, 50, 460);
          pl7drum1_frequency_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl7drum1.frequency(pl7drum1_frequency);
        }
      }

      //drum1 lenght
      if (gridTouchX == 7 || gridTouchX == 8) {
        drawPot(7, 3, pl7drum1_length_graph, pl7drum1_length, "1Decay", ILI9341_RED);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl7drum1_length_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7drum1_length = map(Potentiometer1, 0, 1023, 80, 255);
          pl7drum1_length_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl7drum1.length(pl7drum1_length);
        }
      }
      //drum1 PitchMod
      if (gridTouchX == 11 || gridTouchX == 12) {
        drawPot(11, 3, pl7drum1_pitchMod_graph, pl7drum1_pitchMod_rnd, "1Sweep", ILI9341_RED);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl7drum1_pitchMod_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7drum1_pitchMod_rnd = map(Potentiometer1, 0, 1023, 6, 200);
          pl7drum1_pitchMod = pl7drum1_pitchMod_rnd / 100;
          pl7drum1_pitchMod_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl7drum1.pitchMod(pl7drum1_pitchMod);
        }
      }
      //Wavefolder
      if (gridTouchX == 15 || gridTouchX == 16) {
        drawPot(15, 3, pl7dc1_amplitude_graph, pl7dc1_amplitude_graph, "1Fold", ILI9341_RED);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl7dc1_amplitude_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7dc1_amplitude_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl7dc1_amplitude = pl7dc1_amplitude_graph / 100.00;
          pl7dc1.amplitude(pl7dc1_amplitude);
        }
      }
    }
    if (gridTouchY == 7) {

      //noisemod noise level
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, 7, pl7noise1_amplitude_graph, pl7noise1_amplitude_graph, "2Noise", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl7noise1_amplitude_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7drum1_frequency_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl7noise1_amplitude = pl7noise1_amplitude_graph / 100.00;
          pl7noise1.amplitude(pl7noise1_amplitude);
        }
      }

      //noisemod modwaveform
      if (gridTouchX == 7 || gridTouchX == 8) {
        drawPot(7, 7, pl7waveformMod1_begin_graph, pl7waveformMod1_begin, "2W~F", ILI9341_RED);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl7waveformMod1_begin_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7waveformMod1_begin = map(Potentiometer1, 0, 1023, 0, 11);
          pl7waveformMod1_begin_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl7waveformMod1.begin(pl7waveformMod1_begin);
        }
      }
      //noisemod frequency
      if (gridTouchX == 11 || gridTouchX == 12) {
        drawPot(11, 7, pl7waveformMod1_frequency_graph, pl7waveformMod1_frequency, "2Freq", ILI9341_RED);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl7waveformMod1_frequency_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7waveformMod1_frequency = map(Potentiometer1, 0, 1023, 200, 4000);
          pl7waveformMod1_frequency_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl7waveformMod1.frequency(pl7waveformMod1_frequency);
        }
      }
      //noisemod frequencyModulation
      if (gridTouchX == 15 || gridTouchX == 16) {
        drawPot(15, 7, pl7waveformMod1_frequencyModulation_graph, pl7waveformMod1_frequencyModulation_graph, "2N-FM", ILI9341_RED);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl7waveformMod1_frequencyModulation_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7waveformMod1_frequencyModulation_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl7waveformMod1_frequencyModulation_rnd = map(Potentiometer1, 0, 1023, 0, 1200);
          pl7waveformMod1_frequencyModulation = pl7waveformMod1_frequencyModulation_rnd / 100.00;
          pl7waveformMod1.frequencyModulation(pl7waveformMod1_frequencyModulation);
        }
      }
    }
    if (gridTouchY == 11) {

      //Filter Frequency
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, 11, pl7filter2_frequency_graph, pl7filter2_frequency, "2Freq", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl7filter2_frequency_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7filter2_frequency = map(Potentiometer1, 0, 1023, 40, 5900.00);
          pl7filter2_frequency_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl7filter2.frequency(pl7filter2_frequency);
        }
      }
      //Resonance
      if (gridTouchX == 7 || gridTouchX == 8) {
        drawPot(7, 11, pl7filter2_resonance_graph, pl7filter2_resonance_graph, "2Res", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl7filter2_resonance_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7filter2_resonance_rnd = map(Potentiometer1, 0, 1023, 70, 500.00);
          pl7filter2_resonance = pl7filter2_resonance_rnd / 100.00;
          pl7filter2_resonance_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl7filter2.resonance(pl7filter2_resonance);
        }
      }
      //Attack
      if (gridTouchX == 11 || gridTouchX == 12) {
        drawPot(11, 11, pl7Env1_Attack_graph, pl7Env1_Attack, "2Att", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl7Env1_Attack_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7Env1_Attack = map(Potentiometer1, 0, 1023, 0, 20);
          pl7Env1_Attack_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl7envelope1.attack(pl7Env1_Attack);
          //pl7envelope2.attack(pl7Env1_Attack);
        }
      }

      //Release
      if (gridTouchX == 15 || gridTouchX == 16) {
        drawPot(15, 11, pl7Env1_Release_graph, pl7Env1_Release, "2Rel", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl7Env1_Release_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7Env1_Release = map(Potentiometer1, 0, 1023, 10, 250);
          pl7Env1_Release_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl7envelope1.release(pl7Env1_Release);
          //pl7envelope2.release(pl7Env1_Release);
        }
      }
    }
  }
}

void Plugin7_Page2_Dynamic() {
  /*
  
  if (ts.touched() || !buttons[6].read()) {


    if (gridTouchY == 3) {

      //drum1 root frequency
      if (gridTouchX == 3 || gridTouchX == 4) {
        
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl7drum1_frequency_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7drum1_frequency = map(Potentiometer1, 0, 1023, 50, 460);
          pl7drum1_frequency_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl7drum1.frequency(pl7drum1_frequency);
          
        }
      }

      //drum1 lenght
      if (gridTouchX == 7 || gridTouchX == 8) {
        drawPot(7, 3, pl7drum1_length_graph, pl7drum1_length, "Dec", ILI9341_RED);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl7drum1_length_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7drum1_length = map(Potentiometer1, 0, 1023, 80, 255);
          pl7drum1_length_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl7drum1.length(pl7drum1_length);
          
        }
      }
      //drum1 PitchMod
      if (gridTouchX == 11 || gridTouchX == 12) {
        drawPot(11, 3, pl7drum1_pitchMod_graph, pl7drum1_pitchMod_rnd, "Swp", ILI9341_RED);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl7drum1_pitchMod_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl7drum1_pitchMod_rnd = map(Potentiometer1, 0, 1023, 6, 200);
          pl7drum1_pitchMod = pl7drum1_pitchMod_rnd / 100;
          pl7drum1_pitchMod_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl7drum1.pitchMod(pl7drum1_pitchMod);
          
        }
      }
      //Mix Volume
      if (gridTouchX == 15 || gridTouchX == 16) {
        drawPot(15, 3, plugin[7].Volume_graph, plugin[7].Volume_rnd, "MIX", ILI9341_RED);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - plugin[7].Volume_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          plugin[7].Volume_rnd = map(Potentiometer1, 0, 1023, 0, 500);
          plugin[7].Volume = plugin[7].Volume_rnd / 100.00;
          plugin[7].Volume_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl7mixer1.gain(0, plugin[7].Volume);
          
        }
      }
    }

    if (gridTouchY == 7) {

      //1
      if (gridTouchX == 3 || gridTouchX == 4) {
        dvalue = map(Potentiometer1, 0, 1023, 0, 12);
        fvalue = map(Potentiometer1, 0, 1023, 0, 100);

        drawPot(3, 7, fvalue, dvalue, "dname", ILI9341_BLUE);
      }
      //2
      if (gridTouchX == 7 || gridTouchX == 8) {
        dvalue = map(Potentiometer1, 0, 1023, 0, 12);
        fvalue = map(Potentiometer1, 0, 1023, 0, 100);

        drawPot(7, 7, fvalue, dvalue, "dname", ILI9341_BLUE);
      }
      //3
      if (gridTouchX == 11 || gridTouchX == 12) {
        dvalue = map(Potentiometer1, 0, 1023, 0, 12);
        fvalue = map(Potentiometer1, 0, 1023, 0, 100);

        drawPot(11, 7, fvalue, dvalue, "dname", ILI9341_BLUE);
      }
      //4
      if (gridTouchX == 15 || gridTouchX == 16) {
        dvalue = map(Potentiometer1, 0, 1023, 0, 12);
        fvalue = map(Potentiometer1, 0, 1023, 0, 100);

        drawPot(15, 7, fvalue, dvalue, "dname", ILI9341_RED);
      }
    }

    if (gridTouchY == 11) {

      //1
      if (gridTouchX == 3 || gridTouchX == 4) {
        dvalue = map(Potentiometer1, 0, 1023, 0, 12);
        fvalue = map(Potentiometer1, 0, 1023, 0, 100);

        drawPot(3, 11, fvalue, dvalue, "dname", ILI9341_BLUE);
      }
      //2
      if (gridTouchX == 7 || gridTouchX == 8) {
        dvalue = map(Potentiometer1, 0, 1023, 0, 12);
        fvalue = map(Potentiometer1, 0, 1023, 0, 100);

        drawPot(7, 11, fvalue, dvalue, "dname", ILI9341_BLUE);
      }
      //3
      if (gridTouchX == 11 || gridTouchX == 12) {
        dvalue = map(Potentiometer1, 0, 1023, 0, 12);
        fvalue = map(Potentiometer1, 0, 1023, 0, 100);

        drawPot(11, 11, fvalue, dvalue, "dname", ILI9341_BLUE);
      }
      //4
      if (gridTouchX == 15 || gridTouchX == 16) {
        dvalue = map(Potentiometer1, 0, 1023, 0, 12);
        fvalue = map(Potentiometer1, 0, 1023, 0, 100);

        drawPot(15, 11, fvalue, dvalue, "dname", ILI9341_BLUE);
      }
    }
  }*/
}