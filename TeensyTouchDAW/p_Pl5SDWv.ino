void Plugin_5_Settings() {

  pl5envelope1.delay(0);
  pl5envelope1.hold(0);

  pl5envelope2.delay(0);
  pl5envelope2.hold(0);
  pl5filter1.octaveControl(6);
  pl5mixer1.gain(0, 1);
  pl5mixer1.gain(1, 0);
  pl5mixer1.gain(2, 0);
  pl5mixer1.gain(3, 0);

  pl5dc1.amplitude(1);
  pl5amp.gain(1);
  pl5amp2.gain(1);
}
void Plugin5_Page1_Dynamic() {
  change_preset(pl5NR);

  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //Waveform 
        Encoder_to_Pot_Value(pl5NR, 0, 0, MAX_ENC_RANGE);
        if (plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[0] != Potentiometer[0]) {
          plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[0] = Potentiometer[0];
          drawPot(0, lastPotRow, plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[0], plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[0], "RAW", trackColor[desired_instrument]);
        }
        break;
      case 1:
        SVF_frequency(pl5NR, pl5SVF, 0, 1, 0, 127, "Freq");            //MIN: unused MAX: unused
        SVF_resonance(pl5NR, pl5SVF, 1, 1, 0, MAX_RESONANCE, "Reso");  //MIN: unused MAX: unused
        DC_amplitude(pl5NR, pl5DC1, 2, 1, 0, SUSTAIN_LVL, "Swp");      //MIN: unused MAX: amplitude
        SVF_Type(pl5NR, pl5TYPE, 3, 1, 0, 2, "");                       //MIN: unused MAX: unused
        break;
      case 2:
        ENV_ADSR(pl5NR, pl5ADSR1, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
        ENV_ADSR(pl5NR, pl5ADSR2, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
        break;
    }
  }

  if (ts.touched() || button[15]) {
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin5", 4);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin5", 4);
      }
    }
  }
}
void Plugin5_Page_Static() {
  clearWorkSpace();
  Plugin5_Change();
  drawNrInRect(18, 1, plpreset[pl5NR], ILI9341_PURPLE);

  draw_Raw_File(pl5NR, pl5RAW, 0, 0);

  draw_SVF_frequency(pl5NR, pl5SVF, 0, 1, 0, 127, "Freq");            //MIN: unused MAX: unused
  draw_SVF_resonance(pl5NR, pl5SVF, 1, 1, 0, MAX_RESONANCE, "Reso");  //MIN: unused MAX: unused
  draw_DC_amplitude(pl5NR, pl5DC1, 2, 1, 0, SUSTAIN_LVL, "Swp");      //MIN: unused MAX: amplitude
  draw_SVF_Type(pl5NR, pl5SVF, 3, 1, 0, 2, "");                       //MIN: unused MAX: unused

  draw_ENV_ADSR(pl5NR, pl5ADSR1, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
  draw_ENV_ADSR(pl5NR, pl5ADSR2, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
}
void Plugin5_Change() {
  change_SVF_frequency(pl5NR, pl5SVF, 0, 1, 0, 127, "Freq");            //MIN: unused MAX: unused
  change_SVF_resonance(pl5NR, pl5SVF, 1, 1, 0, MAX_RESONANCE, "Reso");  //MIN: unused MAX: unused
  change_DC_amplitude(pl5NR, pl5DC1, 2, 1, 0, SUSTAIN_LVL, "Swp");      //MIN: unused MAX: amplitud
  change_SVF_Type(pl5NR, pl5SVF, 3, 1, 0, 2, "");                       //MIN: unused MAX: unused

  change_ENV_ADSR(pl5NR, pl5ADSR1, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
  change_ENV_ADSR(pl5NR, pl5ADSR2, 0, 2, ATTACK_TIME, RELEASE_TIME, "");                //MIN: Attack/Decaytime MAX: Releasetime
}
