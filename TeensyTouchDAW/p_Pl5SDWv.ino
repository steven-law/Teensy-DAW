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
void Plugin5_Control() {
  switch (lastPotRow) {
    case 0:
      if (oldWave != Potentiometer[0]) {
        oldWave = Potentiometer[0];
        drawPot(0, lastPotRow, plugin[4].preset[plpreset[4]].Pot_Value[0], plugin[4].preset[plpreset[4]].Pot_Value[0], "RAW", trackColor[desired_instrument]);
        pl5enter_was_pushed = false;
        drawActiveRect(CTRL_COL_1, 2, 2, 2, pl5enter_was_pushed, "LOAD", ILI9341_GREEN);
      }
      break;
    case 1:
      StateVar_Filter(2, 0, lastPotRow);
      break;

    case 2:
      ADSR(2, 0, lastPotRow);
      break;
  }
}
void Plugin5_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      plpreset[4] = constrain((plpreset[4] + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[4], ILI9341_PURPLE);
      Plugin5_Page_Static();
    }
  }

  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //Waveform
        Encoder_to_Pot_Value(4, 0, lastPotRow);

        if (button[15]) {
          newdigate::flashloader loader;
          pl5sample = loader.loadSample(RAW_files[plugin[4].preset[plpreset[4]].Pot_Value[0]]);
          pl5enter_was_pushed = true;
          drawActiveRect(CTRL_COL_1, 2, 2, 2, pl5enter_was_pushed, "LOAD", ILI9341_GREEN);
        }
        break;


      case 1:
        Encoder_to_SVF(4, 0, lastPotRow);
        /*
        Encoder_to_Pot_Value(4, 0, lastPotRow);
        Encoder_to_Pot_Value(4, 1, lastPotRow);
        Encoder_to_Pot_Value(4, 2, lastPotRow);
        Encoder_to_Pot_Value_max12(4, 3, lastPotRow);
        */
        break;

      case 2:
        Encoder_to_4x127(4, 0, lastPotRow);  //ADSR
        break;
    }
  }
  TS_Point p = ts.getPoint();
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
    //change preset
    /*if (gridTouchX >= 18 && gridTouchY == 1) {
      drawNrInRect(18, 1, plpreset[4], ILI9341_PURPLE);
      if ((abs(map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1) - plpreset[4]) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        plpreset[4] = map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1);
      }
    }*/

    if (gridTouchY >= 2 && gridTouchY <= 4) {
      lastPotRow = 0;
    }

    if (gridTouchY >= 5 && gridTouchY <= 7) {
      lastPotRow = 1;
    }

    if (gridTouchY >= 8 && gridTouchY <= 10) {
      lastPotRow = 2;
    }
    if (gridTouchY >= 11 && gridTouchY <= 13) {
      lastPotRow = 3;
    }
  }
}
void Plugin5_Page_Static() {
  clearWorkSpace();
  Plugin5_Change();
  //draw selecting pages buttons
  //draw_sub_page_buttons(2);
  drawNrInRect(18, 1, plpreset[4], ILI9341_PURPLE);
  drawPot(0, 0, plugin[4].preset[plpreset[4]].Pot_Value[0], plugin[4].preset[plpreset[4]].Pot_Value[0], "RAW", trackColor[desired_instrument]);
  drawActiveRect(CTRL_COL_1, 2, 2, 2, pl5enter_was_pushed, "LOAD", ILI9341_GREEN);
  //case 1
  drawPot(0, 1, plugin[4].preset[plpreset[4]].Pot_Value[4], note_frequency[plugin[4].preset[plpreset[4]].Pot_Value[4]], "Freq", trackColor[desired_track]);
  drawPot(1, 1, plugin[4].preset[plpreset[4]].Pot_Value[5], plugin[4].preset[plpreset[4]].Pot_Value[5], "Reso", trackColor[desired_track]);
  drawPot(2, 1, plugin[4].preset[plpreset[4]].Pot_Value[6], plugin[4].preset[plpreset[4]].Pot_Value[6], "Swp", trackColor[desired_track]);
  drawPot(3, 1, plugin[4].preset[plpreset[4]].Pot_Value[7] * SVF_TYP, plugin[4].preset[plpreset[4]].Pot_Value[7], "", trackColor[desired_track]);
  drawChar(CTRL_COL_3, 7, filterType[plugin[4].preset[plpreset[4]].Pot_Value[7]], ILI9341_WHITE);
  //case 2
  drawPot(0, 2, plugin[4].preset[plpreset[4]].Pot_Value[8], map(plugin[4].preset[plpreset[4]].Pot_Value[8], 0, 127, 0, ATTACK_TIME), "Atck", trackColor[desired_track]);
  drawPot(1, 2, plugin[4].preset[plpreset[4]].Pot_Value[9], map(plugin[4].preset[plpreset[4]].Pot_Value[9], 0, 127, 0, DECAY_TIME), "Dec", trackColor[desired_track]);
  drawPot(2, 2, plugin[4].preset[plpreset[4]].Pot_Value[10], map(plugin[4].preset[plpreset[4]].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL), "Sus", trackColor[desired_track]);
  drawPot(3, 2, plugin[4].preset[plpreset[4]].Pot_Value[11], map(plugin[4].preset[plpreset[4]].Pot_Value[11], 0, 127, 0, RELEASE_TIME), "Rel", trackColor[desired_track]);
}
void Plugin5_Change() {
  plugin[4].preset[plpreset[4]].Pot_Value[0];
  newdigate::flashloader loader;
  pl5sample = loader.loadSample(RAW_files[plugin[4].preset[plpreset[4]].Pot_Value[0]]);
  pl5filter1.frequency(note_frequency[plugin[4].preset[plpreset[4]].Pot_Value[4]]);
  pl5filter1.resonance(plugin[4].preset[plpreset[4]].Pot_Value[5] / SVF_RES);
  pl5filter1.octaveControl(plugin[4].preset[plpreset[4]].Pot_Value[6] / SVF_SWP);
  selectFilterType(21, plugin[4].preset[plpreset[4]].Pot_Value[7]);

  pl5envelope1.attack(map(plugin[4].preset[plpreset[4]].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl5envelope2.attack(map(plugin[4].preset[plpreset[4]].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl5envelope1.decay(map(plugin[4].preset[plpreset[4]].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl5envelope2.decay(map(plugin[4].preset[plpreset[4]].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl5envelope1.sustain((float)map(plugin[4].preset[plpreset[4]].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL));
  pl5envelope2.sustain((float)map(plugin[4].preset[plpreset[4]].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL));
  pl5envelope1.release(map(plugin[4].preset[plpreset[4]].Pot_Value[11], 0, 127, 0, RELEASE_TIME));
  pl5envelope2.release(map(plugin[4].preset[plpreset[4]].Pot_Value[11], 0, 127, 0, RELEASE_TIME));
}
