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
      plpreset[5] = constrain((plpreset[5] + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[5], ILI9341_PURPLE);
      Plugin6_Page_Static();
    }
  }

  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //Waveform
        Encoder_to_Pot_Value(5, 0, lastPotRow, 127);
        Potentiometer[0] = plugin[5].preset[plpreset[5]].Pot_Value[0];
        if (plugin[5].preset[plpreset[5]].Pot_Value[0] != Potentiometer[0]) {
          drawPot(0, lastPotRow, plugin[5].preset[plpreset[5]].Pot_Value[0], plugin[5].preset[plpreset[5]].Pot_Value[0], "RAW", trackColor[desired_instrument]);
        }
        break;
      case 1:
        StateVar_Filter(5, 3, 0, lastPotRow);
        break;

      case 2:
        ADSR(5, 3, 0, lastPotRow, 0);
        ADSR(5, 3, 0, lastPotRow, 1);
        break;
    }
  }
  TS_Point p = ts.getPoint();
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
  //draw selecting pages buttons
  //draw_sub_page_buttons(2);
  drawNrInRect(18, 1, plpreset[5], ILI9341_PURPLE);
  drawPot(0, 0, plugin[5].preset[plpreset[5]].Pot_Value[0], plugin[5].preset[plpreset[5]].Pot_Value[0], "RAW", ILI9341_BLACK);
  //case 1
  drawPot(0, 1, plugin[5].preset[plpreset[5]].Pot_Value[4], note_frequency[plugin[5].preset[plpreset[5]].Pot_Value[4]], "Freq", trackColor[desired_track]);
  drawPot(1, 1, plugin[5].preset[plpreset[5]].Pot_Value[5], plugin[5].preset[plpreset[5]].Pot_Value[5], "Reso", trackColor[desired_track]);
  drawPot(2, 1, plugin[5].preset[plpreset[5]].Pot_Value[6], plugin[5].preset[plpreset[5]].Pot_Value[6], "Swp", trackColor[desired_track]);
  drawPot(3, 1, plugin[5].preset[plpreset[5]].Pot_Value[7] * SVF_TYP, plugin[5].preset[plpreset[5]].Pot_Value[7], "", trackColor[desired_track]);
  drawChar(CTRL_COL_3, 7, filterType[plugin[5].preset[plpreset[5]].Pot_Value[7]], ILI9341_WHITE);
  //case 2
  drawPot(0, 2, plugin[5].preset[plpreset[5]].Pot_Value[8], map(plugin[5].preset[plpreset[5]].Pot_Value[8], 0, 127, 0, ATTACK_TIME), "Atck", trackColor[desired_track]);
  drawPot(1, 2, plugin[5].preset[plpreset[5]].Pot_Value[9], map(plugin[5].preset[plpreset[5]].Pot_Value[9], 0, 127, 0, DECAY_TIME), "Dec", trackColor[desired_track]);
  drawPot(2, 2, plugin[5].preset[plpreset[5]].Pot_Value[10], map(plugin[5].preset[plpreset[5]].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL), "Sus", trackColor[desired_track]);
  drawPot(3, 2, plugin[5].preset[plpreset[5]].Pot_Value[11], map(plugin[5].preset[plpreset[5]].Pot_Value[11], 0, 127, 0, RELEASE_TIME), "Rel", trackColor[desired_track]);
}
void Plugin6_Change() {
  plugin[5].preset[plpreset[5]].Pot_Value[0];
  pl6filter1.frequency(note_frequency[plugin[5].preset[plpreset[5]].Pot_Value[4]]);
  pl6filter1.resonance(plugin[5].preset[plpreset[5]].Pot_Value[5] / SVF_RES);
  pl6filter1.octaveControl(plugin[5].preset[plpreset[5]].Pot_Value[6] / SVF_SWP);
  selectFilterType(21, plugin[5].preset[plpreset[5]].Pot_Value[7]);

  pl6envelope1.attack(map(plugin[5].preset[plpreset[5]].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl6envelope2.attack(map(plugin[5].preset[plpreset[5]].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl6envelope1.decay(map(plugin[5].preset[plpreset[5]].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl6envelope2.decay(map(plugin[5].preset[plpreset[5]].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl6envelope1.sustain(map(plugin[5].preset[plpreset[5]].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL));
  pl6envelope2.sustain(map(plugin[5].preset[plpreset[5]].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL));
  pl6envelope1.release(map(plugin[5].preset[plpreset[5]].Pot_Value[11], 0, 127, 0, RELEASE_TIME));
  pl6envelope2.release(map(plugin[5].preset[plpreset[5]].Pot_Value[11], 0, 127, 0, RELEASE_TIME));
}
