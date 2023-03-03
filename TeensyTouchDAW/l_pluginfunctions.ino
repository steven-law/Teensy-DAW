


void envelopeA(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueA != map(Potentiometer[cols], 0, 127, 0, ATTACK_TIME)) {
    PotValueA = map(Potentiometer[cols], 0, 127, 0, ATTACK_TIME);
    ENVELOPE1[des_env]->attack(PotValueA);
    ENVELOPE2[des_env]->attack(PotValueA);
    drawPot(MixerColumnPos, ROW, Potentiometer[cols], PotValueA, "Atck", trackColor[desired_track]);
  }
}

void envelopeD(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueD != map(Potentiometer[cols], 0, 127, 0, DECAY_TIME)) {
    PotValueD = map(Potentiometer[cols], 0, 127, 0, DECAY_TIME);
    ENVELOPE1[des_env]->decay(PotValueD);
    ENVELOPE2[des_env]->decay(PotValueD);
    drawPot_2(MixerColumnPos, ROW, Potentiometer[cols], PotValueD, "Dec", trackColor[desired_track]);
  }
}
void envelopeS(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueS != (float)(Potentiometer[cols] / SUSTAIN_LVL)) {
    PotValueS = (float)(Potentiometer[cols] / SUSTAIN_LVL);
    ENVELOPE1[des_env]->sustain(PotValueS);
    ENVELOPE2[des_env]->sustain(PotValueS);
    drawPot_3(MixerColumnPos, ROW, Potentiometer[cols], Potentiometer[cols], "Sus", trackColor[desired_track]);
  }
}
void envelopeR(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueR != map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME)) {
    PotValueR = map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME);
    ENVELOPE1[des_env]->release(PotValueR);
    ENVELOPE2[des_env]->release(PotValueR);
    drawPot_4(MixerColumnPos, ROW, Potentiometer[cols], PotValueR, "Rel", trackColor[desired_track]);
  }
}
void envelopeH(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueH != map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME)) {
    PotValueH = map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME);
    ENVELOPE1[des_env]->hold(PotValueH);
    ENVELOPE2[des_env]->hold(PotValueH);
    drawPot_3(MixerColumnPos, ROW, Potentiometer[cols], PotValueH, "Hld", trackColor[desired_track]);
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
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueSVF_FREQ != Potentiometer[cols]) {
    PotValueSVF_FREQ = Potentiometer[cols];
    STATEFILTER[des_env]->frequency(note_frequency[Potentiometer[cols]]);
    drawPot(MixerColumnPos, ROW, Potentiometer[cols], note_frequency[PotValueSVF_FREQ], "Freq", trackColor[desired_track]);
  }
}
void StateVar_Resonance(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueSVF_RES != (float)(Potentiometer[cols] / SVF_RES)) {
    PotValueSVF_RES = (float)(Potentiometer[cols] / SVF_RES);
    STATEFILTER[des_env]->resonance(PotValueSVF_RES);
    drawPot_2(MixerColumnPos, ROW, Potentiometer[cols], Potentiometer[cols], "Reso", trackColor[desired_track]);
  }
}
void StateVar_Sweep(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueSVF_SWP != (float)(Potentiometer[cols] / SVF_SWP)) {
    PotValueSVF_SWP = (float)(Potentiometer[cols] / SVF_SWP);
    STATEFILTER[des_env]->octaveControl(PotValueSVF_SWP);
    drawPot_2(MixerColumnPos, ROW, Potentiometer[cols], Potentiometer[cols], "Swp", trackColor[desired_track]);
  }
}
void StateVar_Type(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueSVF_TYP != (float)Potentiometer[cols]) {
    PotValueSVF_TYP = (float)Potentiometer[cols];
    selectFilterType(track[desired_instrument].MIDIchannel, PotValueSVF_TYP);
    drawPot_4(MixerColumnPos, ROW, PotValueSVF_TYP * SVF_TYP, PotValueSVF_TYP, "", trackColor[desired_track]);
    drawChar(MixerColumnPos, ROW + 1, filterType[PotValueSVF_TYP], ILI9341_WHITE);
  }
}


void Ladder_Filter(int des_env, int COL, int ROW) {
  Ladder_Frequency(des_env, COL, ROW);
  Ladder_Resonance(des_env, COL + 1, ROW);
  Ladder_Sweep(des_env, COL + 2, ROW);
}
void Ladder_Frequency(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueLDF_FREQ != Potentiometer[cols]) {
    PotValueLDF_FREQ = Potentiometer[cols];
    LADDERFILTER[des_env]->frequency(note_frequency[Potentiometer[cols]]);
    drawPot(MixerColumnPos, ROW, Potentiometer[cols], note_frequency[Potentiometer[cols]], "Freq", trackColor[desired_track]);
  }
}
void Ladder_Resonance(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueLDF_RES != (float)(Potentiometer[cols] / SVF_RES)) {
    PotValueLDF_RES = (float)(Potentiometer[cols] / SVF_RES);
    LADDERFILTER[des_env]->resonance(PotValueLDF_RES);
    drawPot_2(MixerColumnPos, ROW, Potentiometer[cols], Potentiometer[cols], "Reso", trackColor[desired_track]);
  }
}
void Ladder_Sweep(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueLDF_SWP != (float)(Potentiometer[cols] / SVF_SWP)) {
    PotValueLDF_SWP = (float)(Potentiometer[cols] / SVF_SWP);
    LADDERFILTER[des_env]->octaveControl(PotValueLDF_SWP);
    drawPot_2(MixerColumnPos, ROW, Potentiometer[cols], Potentiometer[cols], "Swp", trackColor[desired_track]);
  }
}

void pl2MIX(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (pl2[pl2presetNr].Pot_Value[cols] != Potentiometer[cols]) {
    pl2[pl2presetNr].Pot_Value[cols] = Potentiometer[cols];
    PL2MIX[ROW]->gain(cols, (float)(pl2[pl2presetNr].Pot_Value[cols] / 127.00));
    drawPot(MixerColumnPos, ROW, Potentiometer[cols], pl2[pl2presetNr].Pot_Value[cols], showVOL[cols], trackColor[desired_instrument]);
  }
}
void pl4MIX(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (pl4[pl2presetNr].Pot_Value[cols] != Potentiometer[cols]) {
    pl4[pl2presetNr].Pot_Value[cols] = Potentiometer[cols];
    PL4MIX[ROW]->gain(cols, (float)(pl4[pl2presetNr].Pot_Value[cols] / 127.00));
    drawPot(MixerColumnPos, ROW, Potentiometer[cols], pl4[pl2presetNr].Pot_Value[cols], showVOL[cols], trackColor[desired_instrument]);
  }
}