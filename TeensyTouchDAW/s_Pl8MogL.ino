void Plugin_8_Settings() {


  pl8waveform1.amplitude(1);
  pl8waveform1.pulseWidth(0.15);

  pl8envelope1.delay(0);
  pl8envelope1.hold(0);

  pl8envelope2.delay(0);
  pl8envelope2.hold(0);
  filter1.octaveControl(6);
  pl8dc1.amplitude(1);
  pl8amp.gain(1);
  pl8amp2.gain(1);
}
void Plugin8_Page1_Dynamic() {
  change_preset(pl8NR);

  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //Waveform
        OSC_Waveform(pl8NR, pl8OSC, 0, 0, 0, 13, "W~F");  //MIN: unused MAX: Waveforms |range: 0-13
        OSC_PWM(pl8NR, pl8OSC, 1, 0, 0, 127.00, "PW");    //MIN: unused MAX: unused
        break;
      case 1:
        LDF_frequency(pl8NR, pl8LADDER, 0, 1, 0, 127, "Freq");                //MIN: unused MAX: unused
        LDF_resonance(pl8NR, pl8LADDER, 1, 1, 0, MAX_RESONANCE, "Reso");      //MIN: unused MAX: unused
        LDF_octaveControl(pl8NR, pl8LADDER, 2, 1, ZERO, SVF_MAX_OCT, "Swp");  //MIN: unused M
        break;

      case 2:
        ENV_ADSR(pl8NR, pl8ADSR1, 0, 2, ATTACK_TIME, RELEASE_TIME, "");
        ENV_ADSR(pl8NR, pl8ADSR2, 0, 2, ATTACK_TIME, RELEASE_TIME, "");
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
  drawNrInRect(18, 1, plpreset[pl8NR], ILI9341_PURPLE);
  draw_OSC_Waveform(pl8NR, pl8OSC, 0, 0, 0, 13, "W~F");  //MIN: unused MAX: Waveforms |range: 0-13
  draw_OSC_PWM(pl8NR, pl8OSC, 1, 0, 0, 1.00, "PW");      //MIN: unused MAX: unused

  draw_LDF_frequency(pl8NR, pl8LADDER, 0, 1, 0, 127, "Freq");                //MIN: unused MAX: unused
  draw_LDF_resonance(pl8NR, pl8LADDER, 1, 1, 0, MAX_RESONANCE, "Reso");      //MIN: unused MAX: unused
  draw_LDF_octaveControl(pl8NR, pl8LADDER, 2, 1, ZERO, SVF_MAX_OCT, "Swp");  //MIN: unused MAX: amplitud

  draw_ENV_ADSR(pl8NR, pl8ADSR1, 0, 2, ATTACK_TIME, RELEASE_TIME, "");
  draw_ENV_ADSR(pl8NR, pl8ADSR2, 0, 2, ATTACK_TIME, RELEASE_TIME, "");
}
void Plugin8_Change() {
  change_OSC_Waveform(pl8NR, pl8OSC, 0, 0, 0, 13, "W~F");  //MIN: unused MAX: Waveforms |range: 0-13
  change_OSC_PWM(pl8NR, pl8OSC, 1, 0, 0, 1.00, "PW");      //MIN: unused MAX: unused

  change_LDF_frequency(pl8NR, pl8LADDER, 0, 1, 0, 127, "Freq");                //MIN: unused MAX: unused
  change_LDF_resonance(pl8NR, pl8LADDER, 1, 1, 0, MAX_RESONANCE, "Reso");      //MIN: unused MAX: unused
  change_LDF_octaveControl(pl8NR, pl8LADDER, 2, 1, ZERO, SVF_MAX_OCT, "Swp");  //MIN: unused MAX: amplitude

  change_ENV_ADSR(pl8NR, pl8ADSR1, 0, 2, ATTACK_TIME, RELEASE_TIME, "");
  change_ENV_ADSR(pl8NR, pl8ADSR2, 0, 2, ATTACK_TIME, RELEASE_TIME, "");
}
