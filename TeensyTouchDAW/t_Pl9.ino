void Plugin_9_Settings() {
  //place here the Audio settings for your plugin
  pl9bpinput.begin(WAVEFORM_SINE);
  pl9bpinput.frequency(1);
  pl9bpinput.amplitude(1);
  pl9bpfilter.frequency(130);
  pl9bpfilter.resonance(3);
  pl9bpfilter.octaveControl(4);
  pl9filter2.frequency(130);
  pl9filter2.resonance(3);
  pl9filter2.octaveControl(4);
  pl9mixer1.gain(0, 1);
  pl9mixer1.gain(1, 0);
  pl9mixer1.gain(2, 0);
  pl9dc1.amplitude(0.06);

  pl9amp.gain(1);
  pl9amp2.gain(1);
}
void Plugin9_Control() {
  switch (lastPotRow) {
    case 0:


      if (plugin[8].preset[plpreset[8]].Pot_Value[1] != Potentiometer[1]) {
        plugin[8].preset[plpreset[8]].Pot_Value[1] = (Potentiometer[1]);
        pl9bpinput.frequency((float)(plugin[8].preset[plpreset[8]].Pot_Value[1]) / 16.00);
        drawPot(1, lastPotRow, plugin[8].preset[plpreset[8]].Pot_Value[1], plugin[8].preset[plpreset[8]].Pot_Value[1], "Rate", trackColor[desired_track]);
      }
      if (plugin[8].preset[plpreset[8]].Pot_Value[2] != Potentiometer[2]) {
        plugin[8].preset[plpreset[8]].Pot_Value[2] = Potentiometer[2];
        pl9bpfilter.octaveControl((float)(plugin[8].preset[plpreset[8]].Pot_Value[2] / 127.00));
        drawPot(2, lastPotRow, plugin[8].preset[plpreset[8]].Pot_Value[2], plugin[8].preset[plpreset[8]].Pot_Value[2], "Depth", trackColor[desired_track]);
      }

      break;
    case 1:


      break;
    case 2:

      break;
    case 3:

      break;
  }
}
void Plugin9_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      plpreset[8] = constrain((plpreset[8] + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[8], ILI9341_PURPLE);
      //Plugin9_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //wah-wah
        //Waveform
        OSC_Waveform(8, 3, 0, 0);
        //Rate
        OSC_ModRate(8, 3, 1, 0, 15.00);
        //Amount
        OSC_LVL(8, 3, 2, 0, 127.00);
        break;

      case 1:
        StateVar_Frequency(8, 7, 0, 1);
        StateVar_Resonance(8, 7, 0, 2);
        break;
      default:  //next taster push brings us back to page 0
        lastPotRow = 0;
    }
  }

  if (ts.touched() || button[15]) {

    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin9", 25);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin9", 25);
      }
    }
  }
}
void Plugin9_Page_Static() {
  clearWorkSpace();
  Plugin9_Change();
  //place here the (copied!) shown controls for your plugin
  //if needed draw selecting pages buttons
  //draw_sub_page_buttons(n); //max 4
  drawNrInRect(18, 1, plpreset[8], ILI9341_PURPLE);
  //wah-wah
  //Waveform
  draw_OSC_Waveform(8, 3, 0, 0);
  //Rate
  draw_OSC_ModRate(8, 3, 1, 0, 15.00);
  //Amount
  draw_OSC_LVL(8, 3, 2, 0);
  //Filter
  draw_StateVar_Freq_Res(8, 7, 0, 1);
}
void Plugin9_Change() {

  pl9bpinput.begin(plugin[8].preset[plpreset[8]].Pot_Value[0] / 10);
  pl9bpinput.frequency((float)(plugin[8].preset[plpreset[8]].Pot_Value[1]) / 16.00);
  pl9bpfilter.octaveControl((float)(plugin[8].preset[plpreset[8]].Pot_Value[2] / 127.00));

  pl9bpfilter.frequency(plugin[8].preset[plpreset[8]].Pot_Value[4] * 16);
  pl9bpfilter.resonance((float)(plugin[8].preset[plpreset[8]].Pot_Value[5] / 25.40));

  pl9dc1.amplitude((float)((plugin[8].preset[plpreset[8]].Pot_Value[8] / 64.00) + 0.06));
}
