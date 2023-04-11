
void Encoder_to_Pot_Value(int plug, int COL, int ROW, int MAX) {
  if (enc_moved[COL]) {
    Potentiometer[COL] = constrain((plugin[plug].preset[plpreset[plug]].Pot_Value[COL + (ROW * 4)] + encoded[COL]), 0, MAX);
  } else if (incomingCC_changed[COL]) {
    Potentiometer[COL] = incomingCC[COL];
    incomingCC_changed[COL] = false;
  }
}



void Encoder_to_Pot_Value2(int plug, int COL, int ROW, int MAX) {
  if (enc_moved[COL]) {
    Potentiometer[COL] = constrain((plugin[plug].preset[plpreset[plug]].Pot_Value2[COL + (ROW * 4)] + encoded[COL]), 0, MAX);
  } else if (incomingCC_changed[COL]) {
    Potentiometer[COL] = incomingCC[COL];
    incomingCC_changed[COL] = false;
  }
}
void store_Pot_Value(int pluginNr, int COL, int ROW) {  //MIN: frequency MAX: frequency |range: 0-22000
  int pot_index = COL + (ROW * 4);
  int actual_pot_value = Potentiometer[COL];
  if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_index] != actual_pot_value && abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_index] - actual_pot_value) < POTPICKUP) {
    plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_index] = actual_pot_value;
  }
}

void draw_A(int pluginNr, int des_node, int COL, int ROW, float max_value, const char* function) {
  int pot_index = COL + (ROW * 4);

  if (COL == 0) {
    drawPot(COL, ROW, plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_index], plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_index], function, trackColor[desired_instrument]);
  }
  if (COL == 1) {
    drawPot_2(COL, ROW, plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_index], plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_index], function, trackColor[desired_instrument]);
  }
  if (COL == 2) {
    drawPot_3(COL, ROW, plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_index], plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_index], function, trackColor[desired_instrument]);
  }
  if (COL == 3) {
    drawPot_4(COL, ROW, plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_index], plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_index], function, trackColor[desired_instrument]);
  }
  Serial.print(function);
  Serial.print(": ");
  Serial.println(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_index]);
}

void Encoder2_to_4x127(int plug, int COL, int ROW) {
  Encoder_to_Pot_Value2(plug, COL, ROW, MAX_ENC_RANGE);
  Encoder_to_Pot_Value2(plug, COL + 1, ROW, MAX_ENC_RANGE);
  Encoder_to_Pot_Value2(plug, COL + 2, ROW, MAX_ENC_RANGE);
  Encoder_to_Pot_Value2(plug, COL + 3, ROW, MAX_ENC_RANGE);
}
void Encoder_to_effect_Value(int plug, int COL, int ROW, int MAX) {

  Potentiometer[COL] = constrain((effect[plug].preset[fxpreset[plug]].Pot_Value[COL + (ROW * 4)] + encoded[COL]), 0, MAX);
}
int store_effect_Value(int pluginNr, int COL, int ROW) {  //MIN: frequency MAX: frequency |range: 0-22000
  int pot_index = COL + (ROW * 4);
  int actual_pot_value = Potentiometer[COL];
  if (effect[pluginNr].preset[fxpreset[pluginNr]].Pot_Value[pot_index] != actual_pot_value && abs(effect[pluginNr].preset[fxpreset[pluginNr]].Pot_Value[pot_index] - actual_pot_value) < POTPICKUP) {
    effect[pluginNr].preset[fxpreset[pluginNr]].Pot_Value[pot_index] = actual_pot_value;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//NODE: AudioSynthWaveform
void OSC_Waveform(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: 0 MAX: 13
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX);
    store_Pot_Value(pluginNr, COL, ROW);
    change_OSC_Waveform(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_OSC_Waveform(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_OSC_Waveform(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: 0 MAX: 13
  OSC[des_node]->begin(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)]);
}
void draw_OSC_Waveform(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: 0 MAX: 12
  draw_A(pluginNr, 10, COL, ROW, MAX, text);
}

void OSC_Detune(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 127
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_OSC_Detune(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_OSC_frequency(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_OSC_Detune(int pluginNr, int des_node, int COL, int ROW, float MIN, int MAX, const char* text) {  //MIN: 0 MAX: 127
  int potValue = plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)];
  detune_mapped = (float)((note_frequency[potValue] * 0.01));
}
void draw_OSC_Detune(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 127
  int pot_Index = COL + (ROW * 4);
  if (note_frequency[plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_Index]] <= 63) {
    // detune_mapped = (float)((note_frequency[63 - Potentiometer[COL]] * 4.4));
    drawPot(COL, ROW, note_frequency[plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_Index]], 63 - note_frequency[plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_Index]], text, trackColor[desired_track]);
    Serial.print("OSC_Detune:");
    Serial.println(detune_mapped);
  } else {
    // detune_mapped = (float)(note_frequency[Potentiometer[COL]-64] * 4.4);
    drawPot(COL, ROW, note_frequency[plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_Index]], note_frequency[plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[pot_Index]] - 64, text, trackColor[desired_track]);
    Serial.print("OSC_Detune:");
    Serial.println(detune_mapped);
  }
}

void OSC_frequency(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: frequency MAX: frequency |range: 0-22000
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_OSC_frequency(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_OSC_frequency(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_OSC_frequency(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: unused MAX: frequency |range: 0-22000
  OSC[des_node]->frequency((float)(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, 127, MIN, MAX)));
}
void draw_OSC_frequency(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: unused MAX: frequency |range: 0-22000

  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}


void OSC_offset(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: -1.00 MAX: 1.00
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_OSC_offset(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_OSC_offset(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_OSC_offset(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: -1.00 MAX: 1.00
  OSC[des_node]->offset((float)(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX)));
}
void draw_OSC_offset(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: -1.00 MAX: 1.00

  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}

void OSC_PWM(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_OSC_PWM(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_OSC_PWM(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_OSC_PWM(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00
  OSC[des_node]->pulseWidth((float)((plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] / MAX)));
}
void draw_OSC_PWM(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00

  draw_A(pluginNr, des_node, COL, ROW, MAX_ENC_RANGE, text);
}


void OSC_amplitude(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_OSC_amplitude(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_OSC_amplitude(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_OSC_amplitude(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00

  OSC[des_node]->amplitude((float)((plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] / MAX)));
}
void draw_OSC_amplitude(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00

  draw_A(pluginNr, des_node, COL, ROW, MAX_ENC_RANGE, text);
}





//NODE: AudioSynthWaveformMod
void OSC_MOD_Waveform(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: Waveforms |range: 0-13
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX);
    store_Pot_Value(pluginNr, COL, ROW);
    change_OSC_MOD_Waveform(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_OSC_MOD_Waveform(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_OSC_MOD_Waveform(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {
  OSC_MOD[des_node]->begin(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)]);
}
void draw_OSC_MOD_Waveform(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: Waveforms |range:0-13
  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}

void OSC_MOD_frequency(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: frequency MAX: frequency |range: 0-22000
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_OSC_MOD_frequency(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_OSC_MOD_frequency(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_OSC_MOD_frequency(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {

  OSC_MOD[des_node]->frequency((float)(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, 127, MIN, MAX)));
}
void draw_OSC_MOD_frequency(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: unused MAX: frequency |range: 0-22000

  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}

void OSC_MOD_offset(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: unused MAX: unused
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_OSC_MOD_offset(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_OSC_MOD_offset(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_OSC_MOD_offset(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {

  OSC_MOD[des_node]->offset((float)(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX)));
}
void draw_OSC_MOD_offset(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {

  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}

void OSC_MOD_FM(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: time MAX: time |range: 0-reasonable
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_OSC_MOD_FM(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_OSC_MOD_FM(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_OSC_MOD_FM(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {

  OSC_MOD[des_node]->frequencyModulation(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX));
}
void draw_OSC_MOD_FM(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: time |range: 0-reasonable

  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}

void OSC_MOD_amplitude(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_OSC_MOD_amplitude(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_OSC_MOD_amplitude(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_OSC_MOD_amplitude(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00

  OSC_MOD[des_node]->amplitude((float)((plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] / MAX)));
}
void draw_OSC_MOD_amplitude(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00

  draw_A(pluginNr, des_node, COL, ROW, MAX_ENC_RANGE, text);
}



//NODE: AudioSynthWaveformPWM
void PWM_amplitude(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  ///MIN: 0 MAX: 1.00
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_PWM_amplitude(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_PWM_amplitude(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_PWM_amplitude(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00

  PWM[des_node]->amplitude((float)((plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] / MAX)));
}
void draw_PWM_amplitude(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00

  draw_A(pluginNr, des_node, COL, ROW, MAX_ENC_RANGE, text);
}


//NODE: AudioSynthSimpleDrum
void OSC_DRUM_frequency(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: time MAX: time |range: 0-reasonable
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_OSC_DRUM_frequency(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_OSC_DRUM_frequency(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_OSC_DRUM_frequency(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {

  DRUM[des_node]->frequency(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX));
}
void draw_OSC_DRUM_frequency(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: time |range: 0-reasonable

  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}

void OSC_DRUM_length(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: time MAX: time |range: 0-reasonable
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_OSC_DRUM_length(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_OSC_DRUM_length(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_OSC_DRUM_length(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {

  DRUM[des_node]->length(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX));
}
void draw_OSC_DRUM_length(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: time |range: 0-reasonable

  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}

void OSC_DRUM_secondMix(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_OSC_DRUM_secondMix(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_OSC_DRUM_secondMix(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_OSC_DRUM_secondMix(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {

  DRUM[des_node]->secondMix((float)(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX)));
}
void draw_OSC_DRUM_secondMix(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: unused MAX: unused

  draw_A(pluginNr, des_node, COL, ROW, MAX_ENC_RANGE, text);
}

void OSC_DRUM_pitchMod(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_OSC_DRUM_pitchMod(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_OSC_DRUM_pitchMod(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_OSC_DRUM_pitchMod(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {

  DRUM[des_node]->pitchMod((float)(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX)));
}
void draw_OSC_DRUM_pitchMod(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: unused MAX: unused

  draw_A(pluginNr, des_node, COL, ROW, MAX_ENC_RANGE, text);
}

//NODE: AudioSynthWaveformDc
void DC_amplitude(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_DC_amplitude(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_DC_amplitude(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_DC_amplitude(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00

  DC[des_node]->amplitude((float)(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] / (MAX_ENC_RANGE / MAX)));
}
void draw_DC_amplitude(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00

  draw_A(pluginNr, des_node, COL, ROW, MAX_ENC_RANGE, text);
}

//NODE: AudioSynthNoiseWhite
void WHITE_amplitude(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);

    change_WHITE_amplitude(pluginNr, des_node, COL, ROW, MIN, MAX, text);

    draw_WHITE_amplitude(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_WHITE_amplitude(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00
  WHITE[des_node]->amplitude((float)(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] / MAX));
}
void draw_WHITE_amplitude(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00

  draw_A(pluginNr, des_node, COL, ROW, MAX_ENC_RANGE, text);
}


//NODE: AudioEffectEnvelope
void ENV_A(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: 0 MAX: 1.00
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_ENV_A(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_ENV_A(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_ENV_A(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {

  ENVELOPE1[des_node]->attack(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX));
}
void draw_ENV_A(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: time |range: 0-reasonable

  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}


void ENV_D(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: time MAX: time |range: 0-reasonable
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_ENV_D(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_ENV_D(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_ENV_D(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {

  ENVELOPE1[des_node]->decay(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX));
}
void draw_ENV_D(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: time |range: 0-reasonable

  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}


void ENV_S(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_ENV_S(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_ENV_S(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_ENV_S(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00
  ENVELOPE1[des_node]->sustain((float)((plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] / MAX)));
}
void draw_ENV_S(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: 0 MAX: 1.00

  draw_A(pluginNr, des_node, COL, ROW, MAX_ENC_RANGE, text);
}


void ENV_R(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: time MAX: time |range: 0-reasonable
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_ENV_R(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_ENV_R(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_ENV_R(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {

  ENVELOPE1[des_node]->release(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX));
}
void draw_ENV_R(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: time |range: 0-reasonable

  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}


void ENV_H(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: time MAX: time |range: 0-reasonable
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_ENV_H(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_ENV_H(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_ENV_H(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {
  ENVELOPE1[des_node]->hold(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX));
}
void draw_ENV_H(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: time |range: 0-reasonable
  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}


void ENV_ADSR(int pluginNr, int des_node, int COL, int ROW, int AttDec, int Rel, const char* text) {  //MIN: Attack/Decaytime MAX: Releasetime
  ENV_A(pluginNr, des_node, COL, ROW, 0, AttDec, "Atck");
  ENV_D(pluginNr, des_node, COL + 1, ROW, 0, AttDec, "Dec");
  ENV_S(pluginNr, des_node, COL + 2, ROW, 0, GAIN_MULT_1, "Sus");
  ENV_R(pluginNr, des_node, COL + 3, ROW, 0, Rel, "Rel");
}
void draw_ENV_ADSR(int pluginNr, int des_node, int COL, int ROW, int AttDec, int Rel, const char* text) {
  draw_ENV_A(pluginNr, des_node, COL, ROW, 0, AttDec, "Atck");
  draw_ENV_D(pluginNr, des_node, COL + 1, ROW, 0, AttDec, "Dec");
  draw_ENV_S(pluginNr, des_node, COL + 2, ROW, 0, GAIN_MULT_1, "Sus");
  draw_ENV_R(pluginNr, des_node, COL + 3, ROW, 0, Rel, "Rel");
}
void change_ENV_ADSR(int pluginNr, int des_node, int COL, int ROW, int AttDec, int Rel, const char* text) {
  change_ENV_A(pluginNr, des_node, COL, ROW, 0, AttDec, "Atck");
  change_ENV_D(pluginNr, des_node, COL + 1, ROW, 0, AttDec, "Dec");
  change_ENV_S(pluginNr, des_node, COL + 2, ROW, 0, GAIN_MULT_1, "Sus");
  change_ENV_R(pluginNr, des_node, COL + 3, ROW, 0, Rel, "Rel");
}





//NODE: AudioFilterStateVariable
void SVF_frequency(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_SVF_frequency(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_SVF_frequency(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_SVF_frequency(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {
  STATEFILTER[des_node]->frequency(note_frequency[plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)]] * tuning);
}
void draw_SVF_frequency(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: unused
  draw_A(pluginNr, des_node, COL, ROW, note_frequency[MAX] * tuning, text);
}


void SVF_resonance(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_SVF_resonance(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_SVF_resonance(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_SVF_resonance(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {

  STATEFILTER[des_node]->resonance((float)(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] / (MAX_ENC_RANGE / MAX)));
}
void draw_SVF_resonance(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: unused MAX: unused

  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}


void SVF_octaveControl(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: time MAX: time |range: 0-reasonable
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_SVF_octaveControl(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_SVF_octaveControl(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_SVF_octaveControl(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {

  STATEFILTER[des_node]->octaveControl(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX));
}
void draw_SVF_octaveControl(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: time |range: 0-reasonable

  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}


void SVF_Type(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: Waveforms |range: 0-13
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_SVF_Type(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_SVF_Type(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_SVF_Type(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {

  selectFilterType(des_node, (map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX)));
}
void draw_SVF_Type(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: unused
  int xPos = ((COL + 1) * 4) - 1;
  int selected_filtertype = (map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX));
  drawChar(xPos, ((ROW + 1) * 3) + 1, filterType[selected_filtertype], ILI9341_WHITE);
  draw_A(pluginNr, des_node, COL, ROW, MAX, "");
}


//NODE: AudioFilterLadder
void LDF_frequency(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_LDF_frequency(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_LDF_frequency(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_LDF_frequency(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {

  LADDERFILTER[des_node]->frequency(note_frequency[plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)]] * tuning);
}
void draw_LDF_frequency(int pluginNr, int des_node, int COL, int ROW, float MIN, int MAX, const char* text) {  //MIN: 0 MAX: 127

  draw_A(pluginNr, des_node, COL, ROW, note_frequency[MAX] * tuning, text);
}


void LDF_resonance(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_LDF_resonance(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_LDF_resonance(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_LDF_resonance(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {

  LADDERFILTER[des_node]->resonance((float)(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] / (MAX_ENC_RANGE / MAX)));
}
void draw_LDF_resonance(int pluginNr, int des_node, int COL, int ROW, float MIN, float MAX, const char* text) {  //MIN: unused MAX: unused

  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}


void LDF_octaveControl(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: time MAX: time |range: 0-reasonable
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_LDF_octaveControl(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_LDF_octaveControl(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_LDF_octaveControl(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {

  LADDERFILTER[des_node]->octaveControl(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX));
}
void draw_LDF_octaveControl(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: time |range: 0-reasonable

  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}



//NODE: AudioEffectBitcrusher
void bitCrush_sampleRate(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_Pot_Value(pluginNr, COL, ROW);
    change_bitCrush_sampleRate(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_bitCrush_sampleRate(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_bitCrush_sampleRate(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {
  BITCRUSHER[des_node]->sampleRate(map(effect[pluginNr].preset[fxpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX));
}
void draw_bitCrush_sampleRate(int pluginNr, int des_node, int COL, int ROW, float MIN, int MAX, const char* text) {  //MIN: 0 MAX: 127
  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}

void bitCrush_bits(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_effect_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_effect_Value(pluginNr, COL, ROW);
    change_bitCrush_bits(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_bitCrush_bits(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_bitCrush_bits(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {
  BITCRUSHER[des_node]->bits(map(effect[pluginNr].preset[fxpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX));
}
void draw_bitCrush_bits(int pluginNr, int des_node, int COL, int ROW, float MIN, int MAX, const char* text) {  //MIN: 0 MAX: 127
  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}

//NODE: AudioEffectReverb
void reverb_reverbTime(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {  //MIN: unused MAX: amplitude |range: 0-127.00(*n) 127.00 = 1.00 amplitude
  if (enc_moved[COL] || incomingCC_changed[COL]) {
    Encoder_to_effect_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
    store_effect_Value(pluginNr, COL, ROW);
    change_reverb_reverbTime(pluginNr, des_node, COL, ROW, MIN, MAX, text);
    draw_reverb_reverbTime(pluginNr, des_node, COL, ROW, MIN, MAX, text);
  }
}
void change_reverb_reverbTime(int pluginNr, int des_node, int COL, int ROW, int MIN, int MAX, const char* text) {
  REVERB[des_node]->reverbTime(map(effect[pluginNr].preset[fxpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, MIN, MAX));
}
void draw_reverb_reverbTime(int pluginNr, int des_node, int COL, int ROW, float MIN, int MAX, const char* text) {  //MIN: 0 MAX: 127
  draw_A(pluginNr, des_node, COL, ROW, MAX, text);
}

void draw_Raw_File(int pluginNr, int des_node, int COL, int ROW) {  //MIN: unused MAX: unused
  draw_A(pluginNr, des_node, COL, ROW, MAX_ENC_RANGE, "RAW");
}
void pl2MIX(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (pl2Pot[COL + (ROW * 4)] != Potentiometer[COL]) {
    pl2Pot[COL + (ROW * 4)] = Potentiometer[COL];
    plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
    PL2MIX[ROW]->gain(COL, (float)(pl2Pot[COL + (ROW * 4)] / 127.00));
    drawPot(COL, ROW, Potentiometer[COL], pl2Pot[COL + (ROW * 4)], showVOL[COL + (ROW * 4)], trackColor[desired_instrument]);
    Serial.println(plugin[1].preset[plpreset[1]].Pot_Value[0]);
  }
}
void pl4MIX(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (pl4Pot[COL + (ROW * 4)] != Potentiometer[COL]) {
    pl4Pot[COL + (ROW * 4)] = Potentiometer[COL];
    plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
    PL4MIX[ROW]->gain(COL, (float)(pl4Pot[COL + (ROW * 4)] / 127.00));
    drawPot(COL, ROW, Potentiometer[COL], pl4Pot[COL + (ROW * 4)], showVOL[COL + (ROW * 4)], trackColor[desired_instrument]);
  }
}