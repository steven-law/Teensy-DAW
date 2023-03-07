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
      plpreset[7] = constrain((plpreset[7] + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[7], ILI9341_PURPLE);
      Plugin8_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //Waveform
        OSC_Waveform(7, 2, 0, lastPotRow);
        break;
      case 1:
        Ladder_Filter(7, 0, 0, lastPotRow);
        break;

      case 2:
        ADSR(7, 7, 0, lastPotRow, 0);
        ADSR(7, 5, 0, lastPotRow, 1);
        break;
    }
  }

  TS_Point p = ts.getPoint();
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
  Plugin3_Change();
  drawNrInRect(18, 1, plpreset[7], ILI9341_PURPLE);

  //case 0
  drawPot(0, 0, plugin[7].preset[plpreset[7]].Pot_Value[0] * 10, plugin[7].preset[plpreset[7]].Pot_Value[0], "W~F", trackColor[desired_track]);
  //case 1
  drawPot(0, 1, plugin[7].preset[plpreset[7]].Pot_Value[4], note_frequency[plugin[7].preset[plpreset[7]].Pot_Value[4]], "Freq", trackColor[desired_track]);
  drawPot(1, 1, plugin[7].preset[plpreset[7]].Pot_Value[5], plugin[7].preset[plpreset[7]].Pot_Value[5], "Reso", trackColor[desired_track]);
  drawPot(2, 1, plugin[7].preset[plpreset[7]].Pot_Value[6], plugin[7].preset[plpreset[7]].Pot_Value[6], "Swp", trackColor[desired_track]);

  //case 2
  drawPot(0, 2, plugin[7].preset[plpreset[7]].Pot_Value[8], map(plugin[7].preset[plpreset[7]].Pot_Value[8], 0, 127, 0, ATTACK_TIME), "Atck", trackColor[desired_track]);
  drawPot(1, 2, plugin[7].preset[plpreset[7]].Pot_Value[9], map(plugin[7].preset[plpreset[7]].Pot_Value[9], 0, 127, 0, DECAY_TIME), "Dec", trackColor[desired_track]);
  drawPot(2, 2, plugin[7].preset[plpreset[7]].Pot_Value[10], (float)(plugin[7].preset[plpreset[7]].Pot_Value[10] / SUSTAIN_LVL), "Sus", trackColor[desired_track]);
  drawPot(3, 2, plugin[7].preset[plpreset[7]].Pot_Value[11], map(plugin[7].preset[plpreset[7]].Pot_Value[11], 0, 127, 0, RELEASE_TIME), "Rel", trackColor[desired_track]);
}
void Plugin8_Change() {
  pl8waveform1.begin(plugin[7].preset[plpreset[7]].Pot_Value[0]);
  pl8filter1.frequency(note_frequency[plugin[7].preset[plpreset[7]].Pot_Value[4]]);
  pl8filter1.resonance(plugin[7].preset[plpreset[7]].Pot_Value[5] / SVF_RES);
  pl8filter1.octaveControl(plugin[7].preset[plpreset[7]].Pot_Value[6] / SVF_SWP);

  pl8envelope1.attack(map(plugin[7].preset[plpreset[7]].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl8envelope2.attack(map(plugin[7].preset[plpreset[7]].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl8envelope1.decay(map(plugin[7].preset[plpreset[7]].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl8envelope2.decay(map(plugin[7].preset[plpreset[7]].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl8envelope1.sustain(map(plugin[7].preset[plpreset[7]].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL));
  pl8envelope2.sustain(map(plugin[7].preset[plpreset[7]].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL));
  pl8envelope1.release(map(plugin[7].preset[plpreset[7]].Pot_Value[11], 0, 127, 0, RELEASE_TIME));
  pl8envelope2.release(map(plugin[7].preset[plpreset[7]].Pot_Value[11], 0, 127, 0, RELEASE_TIME));
}
