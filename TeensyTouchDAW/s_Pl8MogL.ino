void Plugin_8_Settings() {

  pl8waveform1.begin(WAVEFORM_SAWTOOTH);
  pl8waveform1.amplitude(1);
  pl8waveform1.frequency(note_frequency[36]);
  pl8waveform1.pulseWidth(0.15);

  pl8filter1.frequency(note_frequency[pl8[pl8presetNr].Pot_Value[4]]);
  pl8filter1.resonance(pl8[pl8presetNr].Pot_Value[5] / SVF_RES);
  pl8filter1.octaveControl(pl8[pl8presetNr].Pot_Value[6] / SVF_SWP);

  pl8envelope1.delay(0);
  pl8envelope1.attack(map(pl8[pl8presetNr].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl8envelope1.hold(0);
  pl8envelope1.decay(map(pl8[pl8presetNr].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl8envelope1.sustain(pl8[pl8presetNr].Pot_Value[9] / SUSTAIN_LVL);
  pl8envelope1.release(map(pl8[pl8presetNr].Pot_Value[9], 0, 127, 0, RELEASE_TIME));

  pl8envelope2.delay(0);
  pl8envelope2.attack(map(pl8[pl8presetNr].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl8envelope2.hold(0);
  pl8envelope2.decay(map(pl8[pl8presetNr].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl8envelope2.sustain(pl8[pl8presetNr].Pot_Value[9] / SUSTAIN_LVL);
  pl8envelope2.release(map(pl8[pl8presetNr].Pot_Value[9], 0, 127, 0, RELEASE_TIME));

  pl8dc1.amplitude(1);
  pl8amp.gain(1);
  pl8amp2.gain(1);
}
void Plugin8_Control() {
  switch (lastPotRow) {
    case 0:
      if (pl8[pl8presetNr].Pot_Value[0] != Potentiometer[0]) {
        pl8[pl8presetNr].Pot_Value[0] = Potentiometer[0];
        pl8waveform1.begin(pl8[pl8presetNr].Pot_Value[0]);
        drawPot(CTRL_COL_0, CTRL_ROW_0, pl8[pl8presetNr].Pot_Value[0] * 10, pl8[pl8presetNr].Pot_Value[0], "WForm", trackColor[desired_track]);
      }
      break;
    case 1:
      Ladder_Filter(0, 0, CTRL_ROW_1);
      break;
    case 2:
      ADSR(4, 0, CTRL_ROW_2);
      break;
  }
}
void Plugin8_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      pl8presetNr = constrain((pl8presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, pl8presetNr, ILI9341_PURPLE);
      Plugin8_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //Waveform
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl8[pl8presetNr].Pot_Value[0] + encoded[0]), 0, 12);
          pl8[pl8presetNr].Pot_Value[0] = Potentiometer[0];
        }
        break;

      case 1:
        //Filter Frequency
        if (enc_moved[0]) {
          Potentiometer[4] = constrain((pl8[pl8presetNr].Pot_Value[4] + encoded[0]), 0, 127);
          pl8[pl8presetNr].Pot_Value[4] = Potentiometer[0];
        }
        //Resonance
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl8[pl8presetNr].Pot_Value[5] + encoded[1]), 0, 127);
          pl8[pl8presetNr].Pot_Value[5] = Potentiometer[1];
        }
        //Sweep
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((pl8[pl8presetNr].Pot_Value[6] + encoded[2]), 0, 127);
          pl8[pl8presetNr].Pot_Value[6] = Potentiometer[2];
        }

        break;

      case 2:
        //Attack
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl8[pl8presetNr].Pot_Value[8] + encoded[0]), 0, 127);
          pl8[pl8presetNr].Pot_Value[8] = Potentiometer[0];
        }
        //Decay
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl8[pl8presetNr].Pot_Value[9] + encoded[1]), 0, 127);
          pl8[pl8presetNr].Pot_Value[9] = Potentiometer[1];
        }
        //Sustain
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((pl8[pl8presetNr].Pot_Value[10] + encoded[2]), 0, 127);
          pl8[pl8presetNr].Pot_Value[10] = Potentiometer[2];
        }
        //Release
        if (enc_moved[3]) {
          Potentiometer[3] = constrain((pl8[pl8presetNr].Pot_Value[11] + encoded[3]), 0, 127);
          pl8[pl8presetNr].Pot_Value[11] = Potentiometer[3];
        }
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
    //change preset
    //if (gridTouchX >= 18 && gridTouchY == 1) {


    /*drawNrInRect(18, 1, pl8presetNr, ILI9341_PURPLE);
    if ((abs(map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1) - pl8presetNr) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
      pl8presetNr = map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1);
    }*/
    // }

    if (gridTouchY >= 2 && gridTouchY <= 4) {
      lastPotRow = 0;
    }

    if (gridTouchY >= 5 && gridTouchY <= 7) {
      lastPotRow = 1;
    }

    if (gridTouchY >= 8 && gridTouchY <= 10) {
      lastPotRow = 2;
    }
  }
}
void Plugin8_Page_Static() {
  clearWorkSpace();
  Plugin3_Change();
  drawNrInRect(18, 1, pl8presetNr, ILI9341_PURPLE);

  //case 0
  drawPot(CTRL_COL_0, CTRL_ROW_0, pl8[pl8presetNr].Pot_Value[0], pl8[pl8presetNr].Pot_Value[0], "WForm", trackColor[desired_track]);
  //case 1
  drawPot(CTRL_COL_0, CTRL_ROW_1, pl8[pl8presetNr].Pot_Value[4], note_frequency[pl8[pl8presetNr].Pot_Value[4]], "Freq", trackColor[desired_track]);
  drawPot(CTRL_COL_1, CTRL_ROW_1, pl8[pl8presetNr].Pot_Value[5], pl8[pl8presetNr].Pot_Value[5], "Reso", trackColor[desired_track]);
  drawPot(CTRL_COL_2, CTRL_ROW_1, pl8[pl8presetNr].Pot_Value[6], pl8[pl8presetNr].Pot_Value[6], "Swp", trackColor[desired_track]);

  //case 2
  drawPot(CTRL_COL_0, CTRL_ROW_2, pl8[pl8presetNr].Pot_Value[8], map(pl8[pl8presetNr].Pot_Value[8], 0, 127, 0, ATTACK_TIME), "Atck", trackColor[desired_track]);
  drawPot(CTRL_COL_1, CTRL_ROW_2, pl8[pl8presetNr].Pot_Value[9], map(pl8[pl8presetNr].Pot_Value[9], 0, 127, 0, DECAY_TIME), "Dec", trackColor[desired_track]);
  drawPot(CTRL_COL_2, CTRL_ROW_2, pl8[pl8presetNr].Pot_Value[10], map(pl8[pl8presetNr].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL), "Sus", trackColor[desired_track]);
  drawPot(CTRL_COL_3, CTRL_ROW_2, pl8[pl8presetNr].Pot_Value[11], map(pl8[pl8presetNr].Pot_Value[11], 0, 127, 0, RELEASE_TIME), "Rel", trackColor[desired_track]);
}
void Plugin8_Change() {
  pl8waveform1.begin(pl8[pl8presetNr].Pot_Value[0]);
  pl8filter1.frequency(note_frequency[pl8[pl8presetNr].Pot_Value[4]]);
  pl8filter1.resonance(pl8[pl8presetNr].Pot_Value[5] / SVF_RES);
  pl8filter1.octaveControl(pl8[pl8presetNr].Pot_Value[6] / SVF_SWP);

  pl8envelope1.attack(map(pl8[pl8presetNr].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl8envelope2.attack(map(pl8[pl8presetNr].Pot_Value[8], 0, 127, 0, ATTACK_TIME));
  pl8envelope1.decay(map(pl8[pl8presetNr].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl8envelope2.decay(map(pl8[pl8presetNr].Pot_Value[9], 0, 127, 0, DECAY_TIME));
  pl8envelope1.sustain(map(pl8[pl8presetNr].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL));
  pl8envelope2.sustain(map(pl8[pl8presetNr].Pot_Value[10], 0, 127, 0, SUSTAIN_LVL));
  pl8envelope1.release(map(pl8[pl8presetNr].Pot_Value[11], 0, 127, 0, RELEASE_TIME));
  pl8envelope2.release(map(pl8[pl8presetNr].Pot_Value[11], 0, 127, 0, RELEASE_TIME));
}
