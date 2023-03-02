void Plugin_5_Settings() {


  pl5filter1.frequency(note_frequency[pl5[pl5presetNr].Pot_Value[4]]);
  pl5filter1.resonance(pl5[pl5presetNr].Pot_Value[5] / SVF_RES);
  pl5filter1.octaveControl(pl5[pl5presetNr].Pot_Value[6] / SVF_SWP);

  pl5envelope1.delay(0);
  pl5envelope1.attack(map(pl5[pl5presetNr].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl5envelope1.hold(0);
  pl5envelope1.decay(map(pl5[pl5presetNr].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl5envelope1.sustain(pl5[pl5presetNr].Pot_Value[9] / SUSTAIN_LVL);
  pl5envelope1.release(map(pl5[pl5presetNr].Pot_Value[9], 0, 127, 0, RELEASE_TIME));

  pl5envelope2.delay(0);
  pl5envelope2.attack(map(pl5[pl5presetNr].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl5envelope2.hold(0);
  pl5envelope2.decay(map(pl5[pl5presetNr].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl5envelope2.sustain(pl5[pl5presetNr].Pot_Value[9] / SUSTAIN_LVL);
  pl5envelope2.release(map(pl5[pl5presetNr].Pot_Value[9], 0, 127, 0, RELEASE_TIME));

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
      if (pl5[pl5presetNr].Pot_Value[0] != Potentiometer[0]) {
        pl5[pl5presetNr].Pot_Value[0] = Potentiometer[0];
        drawPot(CTRL_COL_0, CTRL_ROW_0, pl5[pl5presetNr].Pot_Value[0], pl5[pl5presetNr].Pot_Value[0], "RAW", trackColor[desired_instrument]);
        pl5enter_was_pushed = false;
        drawActiveRect(CTRL_COL_1, 2, 2, 2, pl5enter_was_pushed, "LOAD", ILI9341_GREEN);
      }
      break;
    case 1:
      StateVar_Filter(2, 0, CTRL_ROW_1); 
      break;

    case 2:
      ADSR(2, 0, CTRL_ROW_2); 
      break;
  }
}
void Plugin5_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      pl5presetNr = constrain((pl5presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, pl5presetNr, ILI9341_PURPLE);
      Plugin5_Page_Static();
    }
  }

  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        Potentiometer[0] = pl5[pl5presetNr].Pot_Value[0];
        if (enc_moved[0]) {
          Potentiometer[0] = pl5[pl5presetNr].Pot_Value[0];
        }
        if (button[15]) {
          newdigate::flashloader loader;
          pl5sample = loader.loadSample(RAW_files[pl5[pl5presetNr].Pot_Value[0]]);
          pl5enter_was_pushed = true;
          drawActiveRect(CTRL_COL_1, 2, 2, 2, pl5enter_was_pushed, "LOAD", ILI9341_GREEN);
        }
        break;

      case 1:
        //Filter Frequency
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl5[pl5presetNr].Pot_Value[4] + encoded[0]), 0, 127);
          pl5[pl5presetNr].Pot_Value[4] = Potentiometer[0];
        }
        //Resonance
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl5[pl5presetNr].Pot_Value[5] + encoded[1]), 0, 127);
          pl5[pl5presetNr].Pot_Value[5] = Potentiometer[1];
        }
        //Sweep
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((pl5[pl5presetNr].Pot_Value[6] + encoded[2]), 0, 127);
          pl5[pl5presetNr].Pot_Value[6] = Potentiometer[2];
        }
        //Filtertype
        if (enc_moved[3]) {
          Potentiometer[3] = constrain((pl5[pl5presetNr].Pot_Value[7] + encoded[3]), 0, 127);
          pl5[pl5presetNr].Pot_Value[7] = Potentiometer[3] / SVF_TYP;
        }
        break;

      case 2:
        //Attack
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl5[pl5presetNr].Pot_Value[8] + encoded[0]), 0, 127);
          pl5[pl5presetNr].Pot_Value[8] = Potentiometer[0];
        }
        //Decay
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl5[pl5presetNr].Pot_Value[9] + encoded[1]), 0, 127);
          pl5[pl5presetNr].Pot_Value[9] = Potentiometer[1];
        }
        //Sustain
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((pl5[pl5presetNr].Pot_Value[10] + encoded[2]), 0, 127);
          pl5[pl5presetNr].Pot_Value[10] = Potentiometer[2];
        }
        //Release
        if (enc_moved[3]) {
          Potentiometer[3] = constrain((pl5[pl5presetNr].Pot_Value[11] + encoded[3]), 0, 127);
          pl5[pl5presetNr].Pot_Value[11] = Potentiometer[3];
        }
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
      drawNrInRect(18, 1, pl5presetNr, ILI9341_PURPLE);
      if ((abs(map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1) - pl5presetNr) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        pl5presetNr = map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1);
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
  drawNrInRect(18, 1, pl5presetNr, ILI9341_PURPLE);
  drawPot(CTRL_COL_0, CTRL_ROW_0, pl5[pl5presetNr].Pot_Value[0], pl5[pl5presetNr].Pot_Value[0], "RAW", trackColor[desired_instrument]);
  drawActiveRect(CTRL_COL_1, 2, 2, 2, pl5enter_was_pushed, "LOAD", ILI9341_GREEN);
  //case 1
  drawPot(CTRL_COL_0, CTRL_ROW_1, pl5[pl5presetNr].Pot_Value[4], note_frequency[pl5[pl5presetNr].Pot_Value[4]], "Freq", trackColor[desired_track]);
  drawPot(CTRL_COL_1, CTRL_ROW_1, pl5[pl5presetNr].Pot_Value[5], pl5[pl5presetNr].Pot_Value[5], "Reso", trackColor[desired_track]);
  drawPot(CTRL_COL_2, CTRL_ROW_1, pl5[pl5presetNr].Pot_Value[6], pl5[pl5presetNr].Pot_Value[6], "Swp", trackColor[desired_track]);
  drawPot(CTRL_COL_3, CTRL_ROW_1, pl5[pl5presetNr].Pot_Value[7] * SVF_TYP, pl5[pl5presetNr].Pot_Value[7], "", trackColor[desired_track]);
  drawChar(CTRL_COL_3, 7, filterType[pl5[pl5presetNr].Pot_Value[7]], ILI9341_WHITE);
  //case 2
  drawPot(CTRL_COL_0, CTRL_ROW_2, pl5[pl5presetNr].Pot_Value[8], map(pl5[pl5presetNr].Pot_Value[8], 0, 127, 0, ATTACK_TIME), "Atck", trackColor[desired_track]);
  drawPot(CTRL_COL_1, CTRL_ROW_2, pl5[pl5presetNr].Pot_Value[9], map(pl5[pl5presetNr].Pot_Value[9], 0, 127, 0, DECAY_TIME), "Dec", trackColor[desired_track]);
  drawPot(CTRL_COL_2, CTRL_ROW_2, pl5[pl5presetNr].Pot_Value[10], map(pl5[pl5presetNr].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL), "Sus", trackColor[desired_track]);
  drawPot(CTRL_COL_3, CTRL_ROW_2, pl5[pl5presetNr].Pot_Value[11], map(pl5[pl5presetNr].Pot_Value[11], 0, 127, 0, RELEASE_TIME), "Rel", trackColor[desired_track]);
}
void Plugin5_Change() {
  pl5[pl5presetNr].Pot_Value[0];
  newdigate::flashloader loader;
  pl5sample = loader.loadSample(RAW_files[pl5[pl5presetNr].Pot_Value[0]]);
  pl5filter1.frequency(note_frequency[pl5[pl5presetNr].Pot_Value[4]]);
  pl5filter1.resonance(pl5[pl5presetNr].Pot_Value[5] / SVF_RES);
  pl5filter1.octaveControl(pl5[pl5presetNr].Pot_Value[6] / SVF_SWP);
  selectFilterType(21, pl5[pl5presetNr].Pot_Value[7]);

  pl5envelope1.attack(map(pl5[pl5presetNr].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl5envelope2.attack(map(pl5[pl5presetNr].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl5envelope1.decay(map(pl5[pl5presetNr].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl5envelope2.decay(map(pl5[pl5presetNr].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl5envelope1.sustain(map(pl5[pl5presetNr].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL));
  pl5envelope2.sustain(map(pl5[pl5presetNr].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL));
  pl5envelope1.release(map(pl5[pl5presetNr].Pot_Value[11], 0, 127, 0, RELEASE_TIME));
  pl5envelope2.release(map(pl5[pl5presetNr].Pot_Value[11], 0, 127, 0, RELEASE_TIME));
}


