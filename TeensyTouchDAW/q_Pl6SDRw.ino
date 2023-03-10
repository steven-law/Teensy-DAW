void Plugin_6_Settings() {

  pl6envelope1.delay(0);
  pl6envelope1.hold(0);
  pl6envelope2.delay(0);
  pl6envelope2.hold(0);

  pl6mixer1.gain(0, 1);
  pl6mixer1.gain(1, 0);
  pl6mixer1.gain(2, 0);
  pl6mixer1.gain(3, 0);

  pl6dc1.amplitude(1);
  pl6amp.gain(1);
  pl6amp2.gain(1);
}

void Plugin6_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      plpreset[pl6NR] = constrain((plpreset[pl6NR] + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[pl6NR], ILI9341_PURPLE);
      Plugin6_Page_Static();
    }
  }

  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //Waveform
        Encoder_to_Pot_Value(5, 0, lastPotRow, 127);

        if (plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[0] != Potentiometer[0]) {
          plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[0] = Potentiometer[0];
          drawPot(0, lastPotRow, plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[0], plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[0], "RAW", trackColor[desired_instrument]);
        }
        break;
      case 1:
        StateVar_Filter(pl6NR, pl6SVF, 0, lastPotRow);
        break;

      case 2:
        ADSR(pl6NR, pl6ADSR1, 0, lastPotRow);
        ADSR(pl6NR, pl6ADSR2, 0, lastPotRow);
        break;
    }
  }

  if (ts.touched() || button[15]) {


    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin6", 22);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin6", 22);
      }
    }
  }
}
void Plugin6_Page_Static() {
  clearWorkSpace();
  Plugin6_Change();
  drawNrInRect(18, 1, plpreset[pl6NR], ILI9341_PURPLE);
  //case 0
  draw_Raw_File(pl6NR, pl6RAW, 0, 0);
  //case 1
  draw_StateVar_Filter(pl6NR, pl6SVF, 0, 1);
  //case 2
  draw_ADSR(pl6NR, pl6ADSR1, 0, 2);
}
void Plugin6_Change() {
  plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[0];
  pl6filter1.frequency(note_frequency[plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[4]]);
  pl6filter1.resonance(plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[5] / SVF_RES);
  pl6filter1.octaveControl(plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[6] / SVF_SWP);
  selectFilterType(21, plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[7]);

  pl6envelope1.attack(map(plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl6envelope2.attack(map(plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl6envelope1.decay(map(plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl6envelope2.decay(map(plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl6envelope1.sustain(map(plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL));
  pl6envelope2.sustain(map(plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL));
  pl6envelope1.release(map(plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[11], 0, 127, 0, RELEASE_TIME));
  pl6envelope2.release(map(plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[11], 0, 127, 0, RELEASE_TIME));
}
