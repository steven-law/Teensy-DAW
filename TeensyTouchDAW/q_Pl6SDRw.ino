void Plugin_6_Settings() {

  pl6envelope1.delay(0);
  pl6envelope1.hold(0);
  pl6envelope2.delay(0);
  pl6envelope2.hold(0);
  pl6filter1.octaveControl(6);

  pl6mixer1.gain(0, 1);
  pl6mixer1.gain(1, 0);
  pl6mixer1.gain(2, 0);
  pl6mixer1.gain(3, 0);

  pl6dc1.amplitude(1);
  pl6amp.gain(1);
  pl6amp2.gain(1);
}

void Plugin6_Page1_Dynamic() {
  change_preset(pl6NR);

  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //Waveform
        Encoder_to_Pot_Value(5, 0, 0, 127);
        if (plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[0] != Potentiometer[0]) {
          plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[0] = Potentiometer[0];
          drawPot(0, lastPotRow, plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[0], plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[0], "RAW", trackColor[desired_instrument]);
        }
        break;
      case 1:
        SVF_frequency(pl6NR, pl6SVF, 0, 1, 0, 127, "Freq");            //MIN: unused MAX: unused
        SVF_resonance(pl6NR, pl6SVF, 1, 1, 0, MAX_RESONANCE, "Reso");  //MIN: unused MAX: unused
        DC_amplitude(pl6NR, pl6DC1, 2, 1, 0, SUSTAIN_LVL, "Swp");      //MIN: unused MAX: amplitude 
        SVF_Type(pl6NR, pl6TYPE, 3, 1, 0, 2, "");                       //MIN: unused MAX: unused
        break;
      case 2:
        ENV_ADSR(pl6NR, pl6ADSR1, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
        ENV_ADSR(pl6NR, pl6ADSR2, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
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

  draw_SVF_frequency(pl6NR, pl6SVF, 0, 1, 0, 127, "Freq");            //MIN: unused MAX: unused
  draw_SVF_resonance(pl6NR, pl6SVF, 1, 1, 0, MAX_RESONANCE, "Reso");  //MIN: unused MAX: unused
  draw_DC_amplitude(pl6NR, pl6DC1, 2, 1, 0, SUSTAIN_LVL, "Swp");      //MIN: unused MAX: amplitude
  draw_SVF_Type(pl6NR, pl6SVF, 3, 1, 0, 2, "");                       //MIN: unused MAX: unused

  draw_ENV_ADSR(pl6NR, pl6ADSR1, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
  draw_ENV_ADSR(pl6NR, pl6ADSR2, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
}
void Plugin6_Change() {

  change_SVF_frequency(pl6NR, pl6SVF, 0, 1, 0, 127, "Freq");            //MIN: unused MAX: unused
  change_SVF_resonance(pl6NR, pl6SVF, 1, 1, 0, MAX_RESONANCE, "Reso");  //MIN: unused MAX: unused
  change_DC_amplitude(pl6NR, pl6DC1, 2, 1, 0, SUSTAIN_LVL, "Swp");      //MIN: unused MAX: amplitude
  change_SVF_Type(pl6NR, pl6SVF, 3, 1, 0, 2, "");                       //MIN: unused MAX: unused

  change_ENV_ADSR(pl6NR, pl6ADSR1, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
  change_ENV_ADSR(pl6NR, pl6ADSR2, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
}
