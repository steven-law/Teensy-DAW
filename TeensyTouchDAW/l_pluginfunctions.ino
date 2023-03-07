
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


#define MAX_ENC_RANGE 127
void Encoder_to_SVF(int plug, int COL, int ROW) {
  Encoder_to_Pot_Value(plug, COL, ROW, MAX_ENC_RANGE);
  Encoder_to_Pot_Value(plug, COL + 1, ROW, MAX_ENC_RANGE);
  Encoder_to_Pot_Value(plug, COL + 2, ROW, MAX_ENC_RANGE);
  Encoder_to_Pot_Value(plug, COL + 3, ROW, 2);
}
void Encoder_to_Ladder(int plug, int COL, int ROW) {
  Encoder_to_Pot_Value(plug, COL, ROW, MAX_ENC_RANGE);
  Encoder_to_Pot_Value(plug, COL + 1, ROW, MAX_ENC_RANGE);
  Encoder_to_Pot_Value(plug, COL + 2, ROW, MAX_ENC_RANGE);
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
void OSC_Waveform(int pluginNr, int des_node, int cols, int ROW) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, 12);
  int xPos = ((cols + 1) * 4) - 1;
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      OSC[des_node]->begin(Potentiometer[cols]);
      drawPot(cols, ROW, Potentiometer[cols] * 12, Potentiometer[cols], "W~F", trackColor[desired_track]);
      //     drawChar(xPos, ((ROW + 1) * 3) + 1, filterType[Potentiometer[cols]], ILI9341_WHITE);
    }
  }
}
void OSC_ModRate(int pluginNr, int des_node, int cols, int ROW, float MAX) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      OSC[des_node]->frequency((float)(map(Potentiometer[cols], 0, 127, 0, MAX)));
      drawPot(cols, ROW, Potentiometer[cols], Potentiometer[cols], "ModRate", trackColor[desired_track]);
      Serial.print("OSC_ModRate:");
      Serial.println((float)(map(Potentiometer[cols], 0, 127, 0, MAX)));
    }
  }
}
void OSC_Offset(int pluginNr, int des_node, int cols, int ROW) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      OSC[des_node]->offset((float)(map(Potentiometer[cols], 0, 127, -1, 1)));
      drawPot(cols, ROW, Potentiometer[cols], Potentiometer[cols], "Offset", trackColor[desired_track]);
    }
  }
}
void OSC_PWM(int pluginNr, int des_node, int cols, int ROW) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      OSC[des_node]->pulseWidth((float)(Potentiometer[cols] / 127.00));
      drawPot(cols, ROW, Potentiometer[cols], Potentiometer[cols], "PWM", trackColor[desired_track]);
    }
  }
}
void OSC_LVL(int pluginNr, int des_node, int cols, int ROW, double max) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      OSC[des_node]->amplitude((float)(Potentiometer[cols] / max));
      drawPot(cols, ROW, Potentiometer[cols], Potentiometer[cols], "LVL", trackColor[desired_track]);
      Serial.print("OSC_LVL:");
      Serial.println((float)(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] / max));
    }
  }
}

//NODE: AudioSynthWaveformMod
void OSC_MOD_Waveform(int pluginNr, int des_node, int cols, int ROW) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, 12);
  int xPos = ((cols + 1) * 4) - 1;
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      OSC_MOD[des_node]->begin(Potentiometer[cols]);
      drawPot(cols, ROW, Potentiometer[cols] * 12, Potentiometer[cols], "W~F", trackColor[desired_track]);
      //     drawChar(xPos, ((ROW + 1) * 3) + 1, filterType[Potentiometer[cols]], ILI9341_WHITE);
    }
  }
}
void OSC_MOD_ModRate(int pluginNr, int des_node, int cols, int ROW, double MAX) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      OSC_MOD[des_node]->frequency(map(Potentiometer[cols], 0, 127, 0, MAX));
      drawPot(cols, ROW, Potentiometer[cols], Potentiometer[cols], "ModRate", trackColor[desired_track]);
    }
  }
}
void OSC_MOD_Offset(int pluginNr, int des_node, int cols, int ROW) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      OSC_MOD[des_node]->offset((float)(map(Potentiometer[cols], 0, 127, -1, 1)));
      drawPot(cols, ROW, Potentiometer[cols], Potentiometer[cols], "Offset", trackColor[desired_track]);
    }
  }
}
void OSC_MOD_FM(int pluginNr, int des_node, int cols, int ROW) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      OSC_MOD[des_node]->frequencyModulation((float)(map(Potentiometer[cols] ,0, MAX_ENC_RANGE, -1.00, 1.00)));
      drawPot(cols, ROW, Potentiometer[cols], Potentiometer[cols], "FM", trackColor[desired_track]);
      Serial.print("OSC_MOD_FM:");
      Serial.println((float)(map(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] ,0, MAX_ENC_RANGE, -1.00, 1.00)));
    }
  }
}
void OSC_MOD_LVL(int pluginNr, int des_node, int cols, int ROW) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      OSC_MOD[des_node]->amplitude((float)(Potentiometer[cols] / 127.00));
      drawPot(cols, ROW, Potentiometer[cols], Potentiometer[cols], "LVL", trackColor[desired_track]);
      Serial.print("OSC__MOD_LVL:");
      Serial.println((float)(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[1] / 127.00));
    }
  }
}

//NODE: AudioEffectEnvelope
void envelopeA(int pluginNr, int des_node, int cols, int ROW, int num) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      if (num == 0) {
        ENVELOPE1[des_node]->attack(map(Potentiometer[cols], 0, 127, 0, ATTACK_TIME));
      }
      if (num == 1) {
        ENVELOPE1[des_node]->attack(map(Potentiometer[cols], 0, 127, 0, ATTACK_TIME));
      }
      drawPot(cols, ROW, Potentiometer[cols], map(Potentiometer[cols], 0, 127, 0, ATTACK_TIME), "Atck", trackColor[desired_track]);
    }
  }
}
void envelopeD(int pluginNr, int des_node, int cols, int ROW, int num) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      if (num == 0) {
        ENVELOPE1[des_node]->decay(map(Potentiometer[cols], 0, 127, 0, DECAY_TIME));
      }
      if (num == 1) {
        ENVELOPE2[des_node]->decay(map(Potentiometer[cols], 0, 127, 0, DECAY_TIME));
      }
      drawPot_2(cols, ROW, Potentiometer[cols], map(Potentiometer[cols], 0, 127, 0, DECAY_TIME), "Dec", trackColor[desired_track]);
    }
  }
}
void envelopeS(int pluginNr, int des_node, int cols, int ROW, int num) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      if (num == 0) {
        ENVELOPE1[des_node]->sustain((float)(Potentiometer[cols] / SUSTAIN_LVL));
      }
      if (num == 1) {
        ENVELOPE2[des_node]->sustain((float)(Potentiometer[cols] / SUSTAIN_LVL));
      }
      drawPot_3(cols, ROW, Potentiometer[cols], Potentiometer[cols], "Sus", trackColor[desired_track]);
    }
  }
}
void envelopeR(int pluginNr, int des_node, int cols, int ROW, int num) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      if (num == 0) {
        ENVELOPE1[des_node]->release(map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME));
      }
      if (num == 1) {
        ENVELOPE2[des_node]->release(map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME));
      }
      drawPot_4(cols, ROW, Potentiometer[cols], map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME), "Rel", trackColor[desired_track]);
    }
  }
}
void envelopeH(int pluginNr, int des_node, int cols, int ROW, int num) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      if (num == 0) {
        ENVELOPE1[des_node]->hold(map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME));
      }
      if (num == 0) {
        ENVELOPE2[des_node]->hold(map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME));
      }
      drawPot_3(cols, ROW, Potentiometer[cols], map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME), "Hld", trackColor[desired_track]);
    }
  }
}
void ADSR(int pluginNr, int des_node, int COL, int ROW, int num) {
  envelopeA(pluginNr, des_node, COL, ROW, num);
  envelopeD(pluginNr, des_node, COL + 1, ROW, num);
  envelopeS(pluginNr, des_node, COL + 2, ROW, num);
  envelopeR(pluginNr, des_node, COL + 3, ROW, num);
}
void AR(int pluginNr, int des_node, int COL, int ROW, int num) {
  envelopeA(pluginNr, des_node, COL, ROW, num);
  envelopeR(pluginNr, des_node, COL + 1, ROW, num);
}
void AD(int pluginNr, int des_node, int COL, int ROW, int num) {
  envelopeA(pluginNr, des_node, COL, ROW, num);
  envelopeD(pluginNr, des_node, COL + 1, ROW, num);
}
void AHR(int pluginNr, int des_node, int COL, int ROW, int num) {
  envelopeA(pluginNr, des_node, COL, ROW, num);
  envelopeH(pluginNr, des_node, COL + 1, ROW, num);
  envelopeR(pluginNr, des_node, COL + 2, ROW, num);
}

//NODE: AudioFilterStateVariable
void StateVar_Filter(int pluginNr, int des_node, int COL, int ROW) {
  StateVar_Frequency(pluginNr, des_node, COL, ROW);
  StateVar_Resonance(pluginNr, des_node, COL + 1, ROW);
  StateVar_Sweep(pluginNr, des_node, COL + 2, ROW);
  StateVar_Type(pluginNr, des_node, COL + 3, ROW);
}
void StateVar_Frequency(int pluginNr, int des_node, int cols, int ROW) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      STATEFILTER[des_node]->frequency(note_frequency[Potentiometer[cols]]);
      drawPot(cols, ROW, Potentiometer[cols], note_frequency[Potentiometer[cols]], "Freq", trackColor[desired_track]);
    }
  }
}
void StateVar_Resonance(int pluginNr, int des_node, int cols, int ROW) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      STATEFILTER[des_node]->resonance((float)(Potentiometer[cols] / SVF_RES));
      drawPot_2(cols, ROW, Potentiometer[cols], Potentiometer[cols], "Reso", trackColor[desired_track]);
    }
  }
}
void StateVar_Sweep(int pluginNr, int des_node, int cols, int ROW) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      STATEFILTER[des_node]->octaveControl((float)(Potentiometer[cols] / SVF_SWP));
      drawPot_3(cols, ROW, Potentiometer[cols], Potentiometer[cols], "Swp", trackColor[desired_track]);
    }
  }
}
void StateVar_Type(int pluginNr, int des_node, int cols, int ROW) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, 2);
  int xPos = ((cols + 1) * 4) - 1;
  if (abs(plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] - Potentiometer[cols]) < POTPICKUP) {
    if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
      plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
      selectFilterType(track[desired_instrument].MIDIchannel, Potentiometer[cols]);
      drawPot_4(cols, ROW, Potentiometer[cols] * SVF_TYP, Potentiometer[cols], "", trackColor[desired_track]);
      drawChar(xPos, ((ROW + 1) * 3) + 1, filterType[Potentiometer[cols]], ILI9341_WHITE);
    }
  }
}

//NODE: AudioFilterLadder
void Ladder_Filter(int pluginNr, int des_node, int COL, int ROW) {
  Ladder_Frequency(pluginNr, des_node, COL, ROW);
  Ladder_Resonance(pluginNr, des_node, COL + 1, ROW);
  Ladder_Sweep(pluginNr, des_node, COL + 2, ROW);
}
void Ladder_Frequency(int pluginNr, int des_node, int cols, int ROW) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
    plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
    LADDERFILTER[des_node]->frequency(note_frequency[Potentiometer[cols]]);
    drawPot(cols, ROW, Potentiometer[cols], note_frequency[Potentiometer[cols]], "Freq", trackColor[desired_track]);
  }
}
void Ladder_Resonance(int pluginNr, int des_node, int cols, int ROW) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
    plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
    LADDERFILTER[des_node]->resonance((float)(Potentiometer[cols] / SVF_RES));
    drawPot_2(cols, ROW, Potentiometer[cols], Potentiometer[cols], "Reso", trackColor[desired_track]);
  }
}
void Ladder_Sweep(int pluginNr, int des_node, int cols, int ROW) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] != Potentiometer[cols]) {
    plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
    LADDERFILTER[des_node]->octaveControl((float)(Potentiometer[cols] / SVF_SWP));
    drawPot_3(cols, ROW, Potentiometer[cols], Potentiometer[cols], "Swp", trackColor[desired_track]);
  }
}

void pl2MIX(int pluginNr, int des_node, int cols, int ROW) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (pl2Pot[cols + (ROW * 4)] != Potentiometer[cols]) {
    pl2Pot[cols + (ROW * 4)] = Potentiometer[cols];
    plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
    PL2MIX[ROW]->gain(cols, (float)(pl2Pot[cols + (ROW * 4)] / 127.00));
    drawPot(cols, ROW, Potentiometer[cols], pl2Pot[cols + (ROW * 4)], showVOL[cols + (ROW * 4)], trackColor[desired_instrument]);
    Serial.println(plugin[1].preset[plpreset[1]].Pot_Value[0]);
  }
}
void pl4MIX(int pluginNr, int des_node, int cols, int ROW) {
  Encoder_to_Pot_Value(pluginNr, cols, ROW, MAX_ENC_RANGE);
  if (pl4Pot[cols + (ROW * 4)] != Potentiometer[cols]) {
    pl4Pot[cols + (ROW * 4)] = Potentiometer[cols];
    plugin[pluginNr].preset[plpreset[pluginNr]].Pot_Value[cols + (ROW * 4)] = Potentiometer[cols];
    PL4MIX[ROW]->gain(cols, (float)(pl4Pot[cols + (ROW * 4)] / 127.00));
    drawPot(cols, ROW, Potentiometer[cols], pl4Pot[cols + (ROW * 4)], showVOL[cols + (ROW * 4)], trackColor[desired_instrument]);
  }
}