void Plugin_8_Settings() {


  pl8waveform1.amplitude(1);
  pl8waveform1.pulseWidth(0.15);

  pl8envelope1.delay(0);
  pl8envelope1.hold(0);

  pl8envelope2.delay(0);
  pl8envelope2.hold(0);

  pl8dc1.amplitude(1);
  pl8amp.gain(1);
  pl8amp2.gain(1);
}
void Plugin8_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      plpreset[pl8NR] = constrain((plpreset[pl8NR] + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[pl8NR], ILI9341_PURPLE);
      Plugin8_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //Waveform
        OSC_Waveform(pl8NR, pl8OSC, 0, 0);
        OSC_PWM(pl8NR, pl8OSC, 1, 0);
        break;
      case 1:
        Ladder_Filter(pl8NR, pl8LADDER, 0, 1);
        break;

      case 2:
        ADSR(pl8NR, pl8ADSR1, 0, 2);
        ADSR(pl8NR, pl8ADSR2, 0, 2);
        break;
    }
  }


  if (ts.touched() || button[15]) {


    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin8", 24);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin8", 24);
      }
    }
  }
}
void Plugin8_Page_Static() {
  clearWorkSpace();
  Plugin8_Change();
  drawNrInRect(18, 1, plpreset[pl8NR], ILI9341_PURPLE);
  //case 0
  draw_OSC_Waveform(pl8NR, pl8OSC, 0, 0);  //pluginNr, pointerarrayPos, column, row
  draw_OSC_PWM(pl8NR, pl8OSC, 1, 0);       //pluginNr, pointerarrayPos, column, row
    //case 1
  draw_Ladder_Filter(pl8NR, pl8LADDER, 0, 1);  //pluginNr, pointerarrayPos, column, row
  //case 2
  draw_ADSR(pl8NR, pl8ADSR1, 0, 2);  //pluginNr, pointerarrayPos, column, row
}
void Plugin8_Change() {
  pl8waveform1.begin(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[0]);
  pl8filter1.frequency(note_frequency[plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[4]]* tuning);
  pl8filter1.resonance(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[5] / SVF_RES);
  pl8filter1.octaveControl(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[6] / SVF_SWP);

  pl8envelope1.attack(map(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl8envelope2.attack(map(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl8envelope1.decay(map(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl8envelope2.decay(map(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl8envelope1.sustain(map(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL));
  pl8envelope2.sustain(map(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL));
  pl8envelope1.release(map(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[11], 0, 127, 0, RELEASE_TIME));
  pl8envelope2.release(map(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[11], 0, 127, 0, RELEASE_TIME));
}
