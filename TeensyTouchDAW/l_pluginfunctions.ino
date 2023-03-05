void Encoder_to_Pot_Value(int plug, int COL, int ROW) {

  if (enc_moved[COL]) {
    Potentiometer[COL] = constrain((plugin[plug].preset[plpreset[plug]].Pot_Value[COL + (ROW * 4)] + encoded[COL]), 0, 127);
    plugin[plug].preset[plpreset[plug]].Pot_Value[COL + (ROW * 4)]=Potentiometer[COL];
  }
}

void Encoder_to_Pot_Value2(int plug, int COL, int ROW) {

  if (enc_moved[COL]) {
    Potentiometer[COL] = constrain((plugin[plug].preset[plpreset[plug]].Pot_Value[COL + (ROW * 4)] + encoded[COL]), 0, 127);
    plugin[plug].preset[plpreset[plug]].Pot_Value[COL + (ROW * 4)]=Potentiometer[COL];
  }
}

void Encoder_to_Pot_Value_max12(int plug, int COL, int ROW) {

  if (enc_moved[COL]) {
    Potentiometer[COL] = constrain((plugin[plug].preset[plpreset[plug]].Pot_Value[COL + (ROW * 4)] + encoded[COL]), 0, 11);
    plugin[plug].preset[plpreset[plug]].Pot_Value[COL + (ROW * 4)]=Potentiometer[COL];
  }
}
void Encoder_to_Pot_Value_max2(int plug, int COL, int ROW) {

  if (enc_moved[COL]) {
    Potentiometer[COL] = constrain((plugin[plug].preset[plpreset[plug]].Pot_Value[COL + (ROW * 4)] + encoded[COL]), 0, 2);
    plugin[plug].preset[plpreset[plug]].Pot_Value[COL + (ROW * 4)]=Potentiometer[COL];
  }
}

void Encoder_to_SVF(int plug, int COL, int ROW) {
  Encoder_to_Pot_Value(plug, COL, ROW);
  Encoder_to_Pot_Value(plug, COL + 1, ROW);
  Encoder_to_Pot_Value(plug, COL + 2, ROW);
  Encoder_to_Pot_Value_max2(plug, COL + 3, ROW);
}
void Encoder_to_Ladder(int plug, int COL, int ROW) {
  Encoder_to_Pot_Value(plug, COL, ROW);
  Encoder_to_Pot_Value(plug, COL + 1, ROW);
  Encoder_to_Pot_Value(plug, COL + 2, ROW);
}
void Encoder_to_4x127(int plug, int COL, int ROW) {
  Encoder_to_Pot_Value(plug, COL, ROW);
  Encoder_to_Pot_Value(plug, COL + 1, ROW);
  Encoder_to_Pot_Value(plug, COL + 2, ROW);
  Encoder_to_Pot_Value(plug, COL + 3, ROW);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void envelopeA(int des_env, int cols, int ROW) {
  if (PotValueA != map(Potentiometer[cols], 0, 127, 0, ATTACK_TIME)) {
    PotValueA = map(Potentiometer[cols], 0, 127, 0, ATTACK_TIME);
    ENVELOPE1[des_env]->attack(PotValueA);
    ENVELOPE2[des_env]->attack(PotValueA);
    drawPot(cols, ROW, Potentiometer[cols], PotValueA, "Atck", trackColor[desired_track]);
  }
}

void envelopeD(int des_env, int cols, int ROW) {
  if (PotValueD != map(Potentiometer[cols], 0, 127, 0, DECAY_TIME)) {
    PotValueD = map(Potentiometer[cols], 0, 127, 0, DECAY_TIME);
    ENVELOPE1[des_env]->decay(PotValueD);
    ENVELOPE2[des_env]->decay(PotValueD);
    drawPot_2(cols, ROW, Potentiometer[cols], PotValueD, "Dec", trackColor[desired_track]);
  }
}
void envelopeS(int des_env, int cols, int ROW) {
  if (PotValueS != (float)(Potentiometer[cols] / SUSTAIN_LVL)) {
    PotValueS = (float)(Potentiometer[cols] / SUSTAIN_LVL);
    ENVELOPE1[des_env]->sustain(PotValueS);
    ENVELOPE2[des_env]->sustain(PotValueS);
    drawPot_3(cols, ROW, Potentiometer[cols], Potentiometer[cols], "Sus", trackColor[desired_track]);
  }
}
void envelopeR(int des_env, int cols, int ROW) {
  if (PotValueR != map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME)) {
    PotValueR = map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME);
    ENVELOPE1[des_env]->release(PotValueR);
    ENVELOPE2[des_env]->release(PotValueR);
    drawPot_4(cols, ROW, Potentiometer[cols], PotValueR, "Rel", trackColor[desired_track]);
  }
}
void envelopeH(int des_env, int cols, int ROW) {
  if (PotValueH != map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME)) {
    PotValueH = map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME);
    ENVELOPE1[des_env]->hold(PotValueH);
    ENVELOPE2[des_env]->hold(PotValueH);
    drawPot_3(cols, ROW, Potentiometer[cols], PotValueH, "Hld", trackColor[desired_track]);
  }
}
void ADSR(int des_env, int COL, int ROW) {
  envelopeA(des_env, COL, ROW);
  envelopeD(des_env, COL + 1, ROW);
  envelopeS(des_env, COL + 2, ROW);
  envelopeR(des_env, COL + 3, ROW);
}
void AR(int des_env, int COL, int ROW) {
  envelopeA(des_env, COL, ROW);
  envelopeR(des_env, COL + 1, ROW);
}
void AD(int des_env, int COL, int ROW) {
  envelopeA(des_env, COL, ROW);
  envelopeD(des_env, COL + 1, ROW);
}
void AHR(int des_env, int COL, int ROW) {
  envelopeA(des_env, COL, ROW);
  envelopeH(des_env, COL + 1, ROW);
  envelopeR(des_env, COL + 2, ROW);
}

void StateVar_Filter(int des_env, int COL, int ROW) {
  StateVar_Frequency(des_env, COL, ROW);
  StateVar_Resonance(des_env, COL + 1, ROW);
  StateVar_Sweep(des_env, COL + 2, ROW);
  StateVar_Type(des_env, COL + 3, ROW);
}
void StateVar_Frequency(int des_env, int cols, int ROW) {
  if (PotValueSVF_FREQ != Potentiometer[cols]) {
    PotValueSVF_FREQ = Potentiometer[cols];
    STATEFILTER[des_env]->frequency(note_frequency[Potentiometer[cols]]);
    drawPot(cols, ROW, Potentiometer[cols], note_frequency[PotValueSVF_FREQ], "Freq", trackColor[desired_track]);
  }
}
void StateVar_Resonance(int des_env, int cols, int ROW) {
  if (PotValueSVF_RES != (float)(Potentiometer[cols] / SVF_RES)) {
    PotValueSVF_RES = (float)(Potentiometer[cols] / SVF_RES);
    STATEFILTER[des_env]->resonance(PotValueSVF_RES);
    drawPot_2(cols, ROW, Potentiometer[cols], Potentiometer[cols], "Reso", trackColor[desired_track]);
  }
}
void StateVar_Sweep(int des_env, int cols, int ROW) {
  if (PotValueSVF_SWP != (float)(Potentiometer[cols] / SVF_SWP)) {
    PotValueSVF_SWP = (float)(Potentiometer[cols] / SVF_SWP);
    STATEFILTER[des_env]->octaveControl(PotValueSVF_SWP);
    drawPot_3(cols, ROW, Potentiometer[cols], Potentiometer[cols], "Swp", trackColor[desired_track]);
  }
}
void StateVar_Type(int des_env, int cols, int ROW) {
  int xPos = ((cols + 1) * 4) - 1;
  if (PotValueSVF_TYP != (float)Potentiometer[cols]) {
    PotValueSVF_TYP = (float)Potentiometer[cols];
    selectFilterType(track[desired_instrument].MIDIchannel, PotValueSVF_TYP);
    drawPot_4(cols, ROW, PotValueSVF_TYP * SVF_TYP, PotValueSVF_TYP, "", trackColor[desired_track]);
    drawChar(xPos, ((ROW + 1) * 3) + 1, filterType[PotValueSVF_TYP], ILI9341_WHITE);
  }
}


void Ladder_Filter(int des_env, int COL, int ROW) {
  Ladder_Frequency(des_env, COL, ROW);
  Ladder_Resonance(des_env, COL + 1, ROW);
  Ladder_Sweep(des_env, COL + 2, ROW);
}
void Ladder_Frequency(int des_env, int cols, int ROW) {
  if (PotValueLDF_FREQ != Potentiometer[cols]) {
    PotValueLDF_FREQ = Potentiometer[cols];
    LADDERFILTER[des_env]->frequency(note_frequency[Potentiometer[cols]]);
    drawPot(cols, ROW, Potentiometer[cols], note_frequency[Potentiometer[cols]], "Freq", trackColor[desired_track]);
  }
}
void Ladder_Resonance(int des_env, int cols, int ROW) {
  if (PotValueLDF_RES != (float)(Potentiometer[cols] / SVF_RES)) {
    PotValueLDF_RES = (float)(Potentiometer[cols] / SVF_RES);
    LADDERFILTER[des_env]->resonance(PotValueLDF_RES);
    drawPot_2(cols, ROW, Potentiometer[cols], Potentiometer[cols], "Reso", trackColor[desired_track]);
  }
}
void Ladder_Sweep(int des_env, int cols, int ROW) {
  if (PotValueLDF_SWP != (float)(Potentiometer[cols] / SVF_SWP)) {
    PotValueLDF_SWP = (float)(Potentiometer[cols] / SVF_SWP);
    LADDERFILTER[des_env]->octaveControl(PotValueLDF_SWP);
    drawPot_3(cols, ROW, Potentiometer[cols], Potentiometer[cols], "Swp", trackColor[desired_track]);
  }
}

void pl2MIX(int des_env, int cols, int ROW) {
  if (pl2Pot[cols + (ROW * 4)] != Potentiometer[cols]) {
    pl2Pot[cols + (ROW * 4)] = Potentiometer[cols];
    PL2MIX[ROW]->gain(cols, (float)(pl2Pot[cols + (ROW * 4)] / 127.00));
    drawPot(cols, ROW, Potentiometer[cols], pl2Pot[cols + (ROW * 4)], showVOL[cols + (ROW * 4)], trackColor[desired_instrument]);
    Serial.println(plugin[1].preset[plpreset[1]].Pot_Value[0]);
  }
}
void pl4MIX(int des_env, int cols, int ROW) {
  if (pl4Pot[cols + (ROW * 4)] != Potentiometer[cols]) {
    pl4Pot[cols + (ROW * 4)] = Potentiometer[cols];
    PL4MIX[ROW]->gain(cols, (float)(pl4Pot[cols + (ROW * 4)] / 127.00));
    drawPot(cols, ROW, Potentiometer[cols], pl4Pot[cols + (ROW * 4)], showVOL[cols + (ROW * 4)], trackColor[desired_instrument]);
  }
}