void Plugin_5_Settings() {

  pl5envelope1.delay(0);
  pl5envelope1.hold(0);

  pl5envelope2.delay(0);
  pl5envelope2.hold(0);

  pl5mixer1.gain(0, 1);
  pl5mixer1.gain(1, 0);
  pl5mixer1.gain(2, 0);
  pl5mixer1.gain(3, 0);

  pl5dc1.amplitude(1);
  pl5amp.gain(1);
  pl5amp2.gain(1);
}
void Plugin5_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      plpreset[pl5NR] = constrain((plpreset[pl5NR] + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[pl5NR], ILI9341_PURPLE);
      Plugin5_Page_Static();
    }
  }

  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //Waveform
        Encoder_to_Pot_Value(pl5NR, 0, lastPotRow, MAX_ENC_RANGE);
        if (plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[0] != Potentiometer[0]) {
          plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[0] = Potentiometer[0];
          drawPot(0, lastPotRow, plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[0], plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[0], "RAW", trackColor[desired_instrument]);
        }
        break;
      case 1:
        Ladder_Filter(pl5NR, pl5SVF, 0, lastPotRow);
        break;
      case 2:
        ADSR(pl5NR, pl5ADSR1, 0, lastPotRow);
        ADSR(pl5NR, pl5ADSR2, 0, lastPotRow);
        break;
    }
  }

  if (ts.touched() || button[15]) {


    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin5", 21);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin5", 21);
      }
    }
  }
}
void Plugin5_Page_Static() {
  clearWorkSpace();
  Plugin5_Change();
  drawNrInRect(18, 1, plpreset[pl5NR], ILI9341_PURPLE);
  //case 0
  draw_Raw_File(pl5NR, pl5RAW, 0, 0);  
  //case 1
  draw_StateVar_Filter(pl5NR, pl5SVF, 0, 1);
  //case 2
  draw_ADSR(pl5NR, pl5ADSR1, 0, 2);
}
void Plugin5_Change() {
  plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[0];

  pl5filter1.frequency(note_frequency[plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[4]]);
  pl5filter1.resonance(plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[5] / SVF_RES);
  pl5filter1.octaveControl(plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[6] / SVF_SWP);
  selectFilterType(21, plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[7]);

  pl5envelope1.attack(map(plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl5envelope2.attack(map(plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl5envelope1.decay(map(plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl5envelope2.decay(map(plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl5envelope1.sustain((float)map(plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL));
  pl5envelope2.sustain((float)map(plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL));
  pl5envelope1.release(map(plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[11], 0, 127, 0, RELEASE_TIME));
  pl5envelope2.release(map(plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[11], 0, 127, 0, RELEASE_TIME));
}
