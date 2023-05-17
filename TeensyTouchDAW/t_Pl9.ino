void Plugin_9_Settings() {
  //place here the Audio settings for your plugin
  pl9bpinput.begin(WAVEFORM_SINE);
  pl9bpinput.frequency(1);
  pl9bpinput.amplitude(1);
  pl9bpfilter.frequency(130);
  pl9bpfilter.resonance(3);
  pl9bpfilter.octaveControl(4);

  pl9mixer1.gain(0, 1);
  pl9mixer1.gain(1, 1);
  pl9mixer1.gain(2, 1);
  pl9mixer1.gain(3, 1);

  pl9mixer2.gain(0, 1);
  pl9mixer2.gain(1, 1);
  pl9mixer2.gain(2, 1);
  pl9mixer2.gain(3, 1);

  pl9mixer3.gain(0, 1);
  pl9mixer3.gain(1, 1);
  pl9mixer3.gain(2, 1);
  pl9mixer3.gain(3, 1);

  pl9mixer4.gain(0, 1);
  pl9mixer4.gain(1, 1);
  pl9mixer4.gain(2, 1);
  pl9mixer4.gain(3, 1);

  pl9amp.gain(1);
  pl9amp2.gain(1);
}

void Plugin9_Page1_Dynamic() {
  change_preset(pl9NR);

  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //wah-wah
        //Waveform
        OSC_Waveform(pl9NR, pl9OSC, 0, 0, 0, OSC_MOD_MAX_WF, "W~F");  //MIN: unused MAX: Waveforms |range: 0-13
        //Rate
        OSC_frequency(pl9NR, pl9OSC, 1, 0, 0, 15.00, "LFO");  //MIN: frequency MAX: frequency |range: 0-22000
        //Amount
        OSC_amplitude(pl9NR, pl9OSC, 2, 0, 0, GAIN_DIV_2, "Amnt");  //MIN: unused MAX: amplitude
        break;

      case 1:
        SVF_frequency(pl9NR, pl9SVF, 0, 1, 0, 127, "Freq");               //MIN: unused MAX: unused
        SVF_resonance(pl9NR, pl9SVF, 1, 1, 0, MAX_RESONANCE, "Reso");     //MIN: unused MAX: unused
        SVF_octaveControl(pl9NR, pl9SVF, 2, 1, 0, MAX_RESONANCE, "Swp");  //MIN: unused MAX: unused
        SVF_Type(pl9NR, pl9TYPE, 3, 1, 0, 2, "");                         //MIN: unused MAX: unused
        break;
    }
  }

  if (ts.touched() || button[15]) {

    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin9", 8);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin9", 8);
      }
    }
  }
}
void Plugin9_Page_Static() {
  clearWorkSpace();
  Plugin9_Change();
  drawNrInRect(18, 1, plpreset[pl9NR], ILI9341_PURPLE);
  //Waveform
  draw_OSC_Waveform(pl9NR, pl9OSC, 0, 0, 0, OSC_MOD_MAX_WF, "W~F");      //MIN: unused MAX: Waveforms |range: 0-13
  draw_OSC_frequency(pl9NR, pl9OSC, 1, 0, 0, 15.00, "LFO");  //MIN: frequency MAX: frequency |range: 0-22000
  draw_OSC_amplitude(pl9NR, pl9OSC, 2, 0, 0, GAIN_DIV_2, "Amnt");  //MIN: unused MAX: amplitude

  draw_SVF_frequency(pl9NR, pl9SVF, 0, 1, 0, 127, "Freq");               //MIN: unused MAX: unused
  draw_SVF_resonance(pl9NR, pl9SVF, 1, 1, 0, MAX_RESONANCE, "Reso");     //MIN: unused MAX: unused
  draw_SVF_octaveControl(pl9NR, pl9SVF, 2, 1, 0, MAX_RESONANCE, "Swp");  //MIN: unused MAX: unused
  draw_SVF_Type(pl9NR, pl9TYPE, 3, 1, 0, 2, "");                         //MIN: unused MAX: unused
}
void Plugin9_Change() {

  //Waveform
  change_OSC_Waveform(pl9NR, pl9OSC, 0, 0, 0, 12, "W~F");      //MIN: unused MAX: Waveforms |range: 0-13
  change_OSC_frequency(pl9NR, pl9OSC, 1, 0, 0, 15.00, "LFO");  //MIN: frequency MAX: frequency |range: 0-22000
  change_OSC_amplitude(pl9NR, pl9OSC, 2, 0, 0, GAIN_DIV_2, "Amnt");  //MIN: unused MAX: amplitude

  change_SVF_frequency(pl9NR, pl9SVF, 0, 1, 0, 127, "Freq");               //MIN: unused MAX: unused
  change_SVF_resonance(pl9NR, pl9SVF, 1, 1, 0, 5.00, "Reso");              //MIN: unused MAX: unused
  change_SVF_octaveControl(pl9NR, pl9SVF, 2, 1, 0, MAX_RESONANCE, "Swp");  //MIN: unused MAX: unused
  change_SVF_Type(pl9NR, pl9TYPE, 3, 1, 0, 2, "");                         //MIN: unused MAX: unused
}
