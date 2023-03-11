
void Encoder_to_Pot_Value(int plug, int COL, int ROW, int MAX) {
  if (enc_moved[COL]) {
    Potentiometer[COL] = constrain((plugin[plug].preset[plpreset[plug]].Pot_Value[COL + (ROW * 4)] + encoded[COL]), 0, MAX);
  }
}

void Encoder_to_Pot_Value2(int plug, int COL, int ROW, int MAX) {
  if (enc_moved[COL]) {
    Potentiometer[COL] = constrain((plugin[plug].preset[plpreset[plug]].Pot_Value2[COL + (ROW * 4)] + encoded[COL]), 0, MAX);
  }
}

void draw_A(int pluginNr, int des_node, int COL, int ROW, int max_value, const char* function) {
  drawPot(COL, ROW, plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, 0, max_value), function, trackColor[desired_instrument]);
}
void draw_A_mult(int pluginNr, int mult, int COL, int ROW, int max_value, const char* function) {
  drawPot(COL, ROW, plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] * mult, map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, 0, max_value), function, trackColor[desired_instrument]);
}


void Encoder_to_4x127(int plug, int COL, int ROW) {
  Encoder_to_Pot_Value(plug, COL, ROW, MAX_ENC_RANGE);
  Encoder_to_Pot_Value(plug, COL + 1, ROW, MAX_ENC_RANGE);
  Encoder_to_Pot_Value(plug, COL + 2, ROW, MAX_ENC_RANGE);
  Encoder_to_Pot_Value(plug, COL + 3, ROW, MAX_ENC_RANGE);
}
void Encoder2_to_4x127(int plug, int COL, int ROW) {
  Encoder_to_Pot_Value2(plug, COL, ROW, MAX_ENC_RANGE);
  Encoder_to_Pot_Value2(plug, COL + 1, ROW, MAX_ENC_RANGE);
  Encoder_to_Pot_Value2(plug, COL + 2, ROW, MAX_ENC_RANGE);
  Encoder_to_Pot_Value2(plug, COL + 3, ROW, MAX_ENC_RANGE);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//NODE: AudioSynthWaveform
void OSC_Waveform(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, 11);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      OSC[des_node]->begin(Potentiometer[COL]);
      drawPot(COL, ROW, Potentiometer[COL] * 11, Potentiometer[COL], "W~F", trackColor[desired_track]);
    }
  }
}
void OSC_Detune(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      pl10detune = (float)((note_frequency[Potentiometer[COL]-5] * 0.44));
      Serial.print("OSC_Detune:");
      Serial.print(note_frequency[69]);
      Serial.println(pl10detune);
      
      if (Potentiometer[COL] <= 63) {
       // pl10detune = (float)((note_frequency[63 - Potentiometer[COL]] * 4.4));
        drawPot(COL, ROW, Potentiometer[COL], 63 - Potentiometer[COL], "Detune", trackColor[desired_track]);
        Serial.print("OSC_Detune:");
        Serial.println(pl10detune);
      }
      if (Potentiometer[COL] >= 64) {
       // pl10detune = (float)(note_frequency[Potentiometer[COL]-64] * 4.4);
        drawPot(COL, ROW, Potentiometer[COL], Potentiometer[COL]-64, "Detune", trackColor[desired_track]);
        Serial.print("OSC_Detune:");
        Serial.println(pl10detune);
      }
      
    }
  }
}
void OSC_ModRate(int pluginNr, int des_node, int COL, int ROW, float MAX) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      OSC[des_node]->frequency((float)(map(Potentiometer[COL], 0, 127, 0, MAX)));
      drawPot(COL, ROW, Potentiometer[COL], Potentiometer[COL], "ModRate", trackColor[desired_track]);
      Serial.print("OSC_ModRate:");
      Serial.println((float)(map(Potentiometer[COL], 0, 127, 0, MAX)));
    }
  }
}
void OSC_Offset(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      OSC[des_node]->offset((float)(map(Potentiometer[COL], 0, 127, -1, 1)));
      drawPot(COL, ROW, Potentiometer[COL], Potentiometer[COL], "Offset", trackColor[desired_track]);
    }
  }
}
void OSC_PWM(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      OSC[des_node]->pulseWidth((float)(Potentiometer[COL] / 127.00));
      drawPot(COL, ROW, Potentiometer[COL], Potentiometer[COL], "PWM", trackColor[desired_track]);
    }
  }
}
void OSC_LVL(int pluginNr, int des_node, int COL, int ROW, double max) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      OSC[des_node]->amplitude((float)(Potentiometer[COL] / max));
      drawPot(COL, ROW, Potentiometer[COL], Potentiometer[COL], "LVL", trackColor[desired_track]);
      Serial.print("OSC_LVL:");
      Serial.println((float)(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] / max));
    }
  }
}
void draw_OSC_Waveform(int pluginNr, int des_node, int COL, int ROW) {
  draw_A_mult(pluginNr, 10, COL, ROW, 11, "W~F");
}
void draw_OSC_modulation(int pluginNr, int des_node, int COL, int ROW) {
  draw_A(pluginNr, des_node, COL, ROW, MAX_ENC_RANGE, "ModRate");
  draw_A(pluginNr, des_node, COL + 1, ROW, MAX_ENC_RANGE, "LVL");
  draw_A_mult(pluginNr, 10, COL + 2, ROW, 11, "W~F");
}
void draw_OSC_ModRate(int pluginNr, int des_node, int COL, int ROW, int range) {
  draw_A(pluginNr, des_node, COL, ROW, range, "ModRate");
}
void draw_OSC_PWM(int pluginNr, int des_node, int COL, int ROW) {
  draw_A(pluginNr, des_node, COL, ROW, MAX_ENC_RANGE, "PWM");
}
void draw_OSC_LVL(int pluginNr, int des_node, int COL, int ROW) {
  draw_A(pluginNr, des_node, COL, ROW, MAX_ENC_RANGE, "LVL");
}

//NODE: AudioSynthWaveformMod
void OSC_MOD_Waveform(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, 11);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      OSC_MOD[des_node]->begin(Potentiometer[COL]);
      drawPot(COL, ROW, Potentiometer[COL] * 11, Potentiometer[COL], "W~F", trackColor[desired_track]);
    }
  }
}
void OSC_MOD_ModRate(int pluginNr, int des_node, int COL, int ROW, double MAX) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      OSC_MOD[des_node]->frequency(map(Potentiometer[COL], 0, 127, 0, MAX));
      drawPot(COL, ROW, Potentiometer[COL], Potentiometer[COL], "ModRate", trackColor[desired_track]);
    }
  }
}
void OSC_MOD_Offset(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      OSC_MOD[des_node]->offset((float)(map(Potentiometer[COL], 0, 127, -1, 1)));
      drawPot(COL, ROW, Potentiometer[COL], Potentiometer[COL], "Offset", trackColor[desired_track]);
    }
  }
}
void OSC_MOD_FM(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      OSC_MOD[des_node]->frequencyModulation((float)(map(Potentiometer[COL], 0, MAX_ENC_RANGE, -1.00, 1.00)));
      drawPot(COL, ROW, Potentiometer[COL], Potentiometer[COL], "FM", trackColor[desired_track]);
      Serial.print("OSC_MOD_FM:");
      Serial.println((float)(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)], 0, MAX_ENC_RANGE, -1.00, 1.00)));
    }
  }
}
void OSC_MOD_LVL(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      OSC_MOD[des_node]->amplitude((float)(Potentiometer[COL] / 127.00));
      drawPot(COL, ROW, Potentiometer[COL], Potentiometer[COL], "LVL", trackColor[desired_track]);
      Serial.print("OSC__MOD_LVL:");
      Serial.println((float)(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] / 127.00));
    }
  }
}
void draw_OSC_MOD_Waveform(int pluginNr, int des_node, int COL, int ROW) {
  draw_A_mult(pluginNr, 10, COL, ROW, 11, "W~F");
}

//NODE: AudioSynthWaveformPWM
void PWM_LVL(int pluginNr, int des_node, int COL, int ROW, double max) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      PWM[des_node]->amplitude((float)(Potentiometer[COL] / max));
      drawPot(COL, ROW, Potentiometer[COL], Potentiometer[COL], "LVL", trackColor[desired_track]);
      Serial.print("PWM_LVL:");
      Serial.println((float)(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] / max));
    }
  }
}
void draw_PWM_LVL(int pluginNr, int des_node, int COL, int ROW) {
  draw_A(pluginNr, des_node, COL, ROW, MAX_ENC_RANGE, "LVL");
}

//NODE: AudioSynthWaveformDc
void DC_LVL(int pluginNr, int des_node, int COL, int ROW, double max) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      DC[des_node]->amplitude((float)(Potentiometer[COL] / max));
      drawPot(COL, ROW, Potentiometer[COL], Potentiometer[COL], "LVL", trackColor[desired_track]);
      Serial.print("DC_LVL:");
      Serial.println((float)(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] / max));
    }
  }
}
void draw_DC_LVL(int pluginNr, int des_node, int COL, int ROW) {
  draw_A(pluginNr, des_node, COL, ROW, MAX_ENC_RANGE, "LVL");
}

//NODE: AudioSynthSimpleDrum
void OSC_DRUM_frequency(int pluginNr, int des_node, int COL, int ROW, double MAX) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      DRUM[des_node]->frequency(map(Potentiometer[COL], 0, 127, 0, MAX));
      drawPot(COL, ROW, Potentiometer[COL], Potentiometer[COL], "Freq", trackColor[desired_track]);
    }
  }
}
void OSC_DRUM_length(int pluginNr, int des_node, int COL, int ROW, double MAX) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      DRUM[des_node]->length(map(Potentiometer[COL], 0, 127, 0, MAX));
      drawPot(COL, ROW, Potentiometer[COL], Potentiometer[COL], "Dec", trackColor[desired_track]);
    }
  }
}
void OSC_DRUM_secondMix(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      DRUM[des_node]->secondMix((float)(Potentiometer[COL] / 127.00));
      drawPot(COL, ROW, Potentiometer[COL], Potentiometer[COL], "Sec", trackColor[desired_track]);
      Serial.print("OSC_DRUM_secondMix:");
      Serial.println((float)(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[1] / 127.00));
    }
  }
}
void OSC_DRUM_PitchMod(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      DRUM[des_node]->pitchMod((float)(Potentiometer[COL] / 127.00));
      drawPot(COL, ROW, Potentiometer[COL], Potentiometer[COL], "Swp", trackColor[desired_track]);
      Serial.print("OSC_DRUM_PitchMod:");
      Serial.println((float)(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[1] / 127.00));
    }
  }
}
void OSC_DRUM(int pluginNr, int des_node, int COL, int ROW) {
  OSC_DRUM_frequency(pluginNr, des_node, COL, ROW, 800);
  OSC_DRUM_length(pluginNr, des_node, COL + 1, ROW, 600);
  OSC_DRUM_PitchMod(pluginNr, des_node, COL + 2, ROW);
  OSC_DRUM_secondMix(pluginNr, des_node, COL + 3, ROW);
}
void draw_OSC_DRUM(int pluginNr, int des_node, int COL, int ROW) {
  draw_A(pluginNr, des_node, COL, ROW, 800, "Freq");
  draw_A(pluginNr, des_node, COL + 1, ROW, 600, "Dec");
  draw_A(pluginNr, des_node, COL + 2, ROW, MAX_ENC_RANGE, "Swp");
  draw_A(pluginNr, des_node, COL + 3, ROW, MAX_ENC_RANGE, "Sec");
}

//NODE: AudioSynthNoiseWhite
void WHITE_LVL(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      WHITE[des_node]->amplitude((float)(Potentiometer[COL] / 127.00));
      drawPot(COL, ROW, Potentiometer[COL], Potentiometer[COL], "LVL", trackColor[desired_track]);
      Serial.print("WHITE_LVL:");
      Serial.println((float)(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[1] / 127.00));
    }
  }
}
void draw_WHITE_LVL(int pluginNr, int des_node, int COL, int ROW) {
  draw_A(pluginNr, des_node, COL, ROW, MAX_ENC_RANGE, "LVL");
}

//NODE: AudioEffectEnvelope
void envelopeA(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      ENVELOPE1[des_node]->attack(map(Potentiometer[COL], 0, 127, 0, ATTACK_TIME));
      drawPot(COL, ROW, Potentiometer[COL], map(Potentiometer[COL], 0, 127, 0, ATTACK_TIME), "Atck", trackColor[desired_track]);
    }
  }
}
void envelopeD(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      ENVELOPE1[des_node]->decay(map(Potentiometer[COL], 0, 127, 0, DECAY_TIME));
      drawPot_2(COL, ROW, Potentiometer[COL], map(Potentiometer[COL], 0, 127, 0, DECAY_TIME), "Dec", trackColor[desired_track]);
    }
  }
}
void envelopeS(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      ENVELOPE1[des_node]->sustain((float)(Potentiometer[COL] / SUSTAIN_LVL));
      drawPot_3(COL, ROW, Potentiometer[COL], Potentiometer[COL], "Sus", trackColor[desired_track]);
    }
  }
}
void envelopeR(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      ENVELOPE1[des_node]->release(map(Potentiometer[COL], 0, 127, 0, RELEASE_TIME));
      drawPot_4(COL, ROW, Potentiometer[COL], map(Potentiometer[COL], 0, 127, 0, RELEASE_TIME), "Rel", trackColor[desired_track]);
    }
  }
}
void envelopeH(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      ENVELOPE1[des_node]->hold(map(Potentiometer[COL], 0, 127, 0, RELEASE_TIME));
      drawPot_3(COL, ROW, Potentiometer[COL], map(Potentiometer[COL], 0, 127, 0, RELEASE_TIME), "Hld", trackColor[desired_track]);
    }
  }
}
void ADSR(int pluginNr, int des_node, int COL, int ROW) {
  envelopeA(pluginNr, des_node, COL, ROW);
  envelopeD(pluginNr, des_node, COL + 1, ROW);
  envelopeS(pluginNr, des_node, COL + 2, ROW);
  envelopeR(pluginNr, des_node, COL + 3, ROW);
}
void AR(int pluginNr, int des_node, int COL, int ROW) {
  envelopeA(pluginNr, des_node, COL, ROW);
  envelopeR(pluginNr, des_node, COL + 1, ROW);
}
void AD(int pluginNr, int des_node, int COL, int ROW) {
  envelopeA(pluginNr, des_node, COL, ROW);
  envelopeD(pluginNr, des_node, COL + 1, ROW);
}
void AHR(int pluginNr, int des_node, int COL, int ROW) {
  envelopeA(pluginNr, des_node, COL, ROW);
  envelopeH(pluginNr, des_node, COL + 1, ROW);
  envelopeR(pluginNr, des_node, COL + 2, ROW);
}
void draw_ADSR(int pluginNr, int des_node, int COL, int ROW) {
  draw_A(pluginNr, des_node, COL, ROW, ATTACK_TIME, "Atck");
  draw_A(pluginNr, des_node, COL + 1, ROW, DECAY_TIME, "Dec");
  draw_A(pluginNr, des_node, COL + 2, ROW, MAX_ENC_RANGE, "Sus");
  draw_A(pluginNr, des_node, COL + 3, ROW, RELEASE_TIME, "Rel");
}
void draw_AHR(int pluginNr, int des_node, int COL, int ROW) {
  draw_A(pluginNr, des_node, COL, ROW, ATTACK_TIME, "Atck");
  draw_A(pluginNr, des_node, COL + 1, ROW, DECAY_TIME, "Hld");
  draw_A(pluginNr, des_node, COL + 2, ROW, RELEASE_TIME, "Rel");
}
void draw_AR(int pluginNr, int des_node, int COL, int ROW) {
  draw_A(pluginNr, des_node, COL, ROW, ATTACK_TIME, "Atck");
  draw_A(pluginNr, des_node, COL + 1, ROW, RELEASE_TIME, "Rel");
}





//NODE: AudioFilterStateVariable
void StateVar_Filter(int pluginNr, int des_node, int COL, int ROW) {
  StateVar_Frequency(pluginNr, des_node, COL, ROW);
  StateVar_Resonance(pluginNr, des_node, COL + 1, ROW);
  StateVar_Sweep(pluginNr, des_node, COL + 2, ROW);
  StateVar_Type(pluginNr, des_node, COL + 3, ROW);
}
void StateVar_Freq_Res(int pluginNr, int des_node, int COL, int ROW) {
  StateVar_Frequency(pluginNr, des_node, COL, ROW);
  StateVar_Resonance(pluginNr, des_node, COL + 1, ROW);
}
void StateVar_Frequency(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      STATEFILTER[des_node]->frequency(note_frequency[Potentiometer[COL]] * tuning);
      drawPot(COL, ROW, Potentiometer[COL], note_frequency[Potentiometer[COL]] * tuning, "Freq", trackColor[desired_track]);
    }
  }
}
void StateVar_Resonance(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      STATEFILTER[des_node]->resonance((float)(Potentiometer[COL] / SVF_RES));
      drawPot_2(COL, ROW, Potentiometer[COL], Potentiometer[COL], "Reso", trackColor[desired_track]);
    }
  }
}
void StateVar_Sweep(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      STATEFILTER[des_node]->octaveControl((float)(Potentiometer[COL] / SVF_SWP));
      drawPot_3(COL, ROW, Potentiometer[COL], Potentiometer[COL], "Swp", trackColor[desired_track]);
    }
  }
}
void StateVar_Type(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, 2);
  int xPos = ((COL + 1) * 4) - 1;
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] - Potentiometer[COL]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
      selectFilterType(track[desired_instrument].MIDIchannel, Potentiometer[COL]);
      drawPot_4(COL, ROW, Potentiometer[COL] * SVF_TYP, Potentiometer[COL], "", trackColor[desired_track]);
      drawChar(xPos, ((ROW + 1) * 3) + 1, filterType[Potentiometer[COL]], ILI9341_WHITE);
    }
  }
}
void draw_StateVar_Filter(int pluginNr, int des_node, int COL, int ROW) {
  int xPos = ((COL + 4) * 4) - 1;
  draw_A(pluginNr, des_node, COL, ROW, note_frequency[127] * tuning, "Freq");
  draw_A(pluginNr, des_node, COL + 1, ROW, ATTACK_TIME, "Reso");
  draw_A(pluginNr, des_node, COL + 2, ROW, MAX_ENC_RANGE, "Swp");
  draw_A_mult(pluginNr, SVF_TYP, COL + 3, ROW, 2, "");
  drawChar(xPos, ((ROW + 1) * 3) + 1, filterType[plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)]], ILI9341_WHITE);
}
void draw_StateVar_Freq_Res(int pluginNr, int des_node, int COL, int ROW) {
  int xPos = ((COL + 1) * 4) - 1;
  draw_A(pluginNr, des_node, COL, ROW, note_frequency[127] * tuning, "Freq");
  draw_A(pluginNr, des_node, COL + 1, ROW, ATTACK_TIME, "Reso");
}

//NODE: AudioFilterLadder
void Ladder_Filter(int pluginNr, int des_node, int COL, int ROW) {
  Ladder_Frequency(pluginNr, des_node, COL, ROW);
  Ladder_Resonance(pluginNr, des_node, COL + 1, ROW);
  Ladder_Sweep(pluginNr, des_node, COL + 2, ROW);
}
void Ladder_Frequency(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
    plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
    LADDERFILTER[des_node]->frequency(note_frequency[Potentiometer[COL]] * tuning);
    drawPot(COL, ROW, Potentiometer[COL], note_frequency[Potentiometer[COL]] * tuning, "Freq", trackColor[desired_track]);
  }
}
void Ladder_Resonance(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
    plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
    LADDERFILTER[des_node]->resonance((float)(Potentiometer[COL] / SVF_RES));
    drawPot_2(COL, ROW, Potentiometer[COL], Potentiometer[COL], "Reso", trackColor[desired_track]);
  }
}
void Ladder_Sweep(int pluginNr, int des_node, int COL, int ROW) {
  Encoder_to_Pot_Value(pluginNr, COL, ROW, MAX_ENC_RANGE);
  if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] != Potentiometer[COL]) {
    plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[COL + (ROW * 4)] = Potentiometer[COL];
    LADDERFILTER[des_node]->octaveControl((float)(Potentiometer[COL] / SVF_SWP));
    drawPot_3(COL, ROW, Potentiometer[COL], Potentiometer[COL], "Swp", trackColor[desired_track]);
  }
}
void draw_Ladder_Filter(int pluginNr, int des_node, int COL, int ROW) {
  draw_A(pluginNr, des_node, COL, ROW, note_frequency[127] * tuning, "Freq");
  draw_A(pluginNr, des_node, COL + 1, ROW, ATTACK_TIME, "Reso");
  draw_A(pluginNr, des_node, COL + 2, ROW, SUSTAIN_LVL, "Swp");
}

void draw_Raw_File(int pluginNr, int des_node, int COL, int ROW) {
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