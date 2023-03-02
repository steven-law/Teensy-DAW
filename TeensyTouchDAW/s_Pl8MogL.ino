void Plugin_8_Settings() {

  pl8waveform1.begin(WAVEFORM_SAWTOOTH);
  pl8waveform1.amplitude(1);
  pl8waveform1.frequency(note_frequency[36]);
  pl8waveform1.pulseWidth(0.15);

  pl8filter1.frequency(pl8[pl8presetNr].Filter1_Frequency);
  pl8filter1.resonance(pl8[pl8presetNr].Filter1_Resonance);
  pl8filter1.octaveControl(pl8[pl8presetNr].Filter1_Sweep);

  pl8envelope1.delay(0);
  pl8envelope1.attack(pl8[pl8presetNr].Env1_Attack);
  pl8envelope1.hold(0);
  pl8envelope1.decay(pl8[pl8presetNr].Env1_Decay);
  pl8envelope1.sustain(pl8[pl8presetNr].Env1_Sustain);
  pl8envelope1.release(pl8[pl8presetNr].Env1_Release);

  pl8dc1.amplitude(1);

  pl8envelope2.delay(0);
  pl8envelope2.attack(pl8[pl8presetNr].Env1_Attack);
  pl8envelope2.hold(0);
  pl8envelope2.decay(pl8[pl8presetNr].Env1_Decay);
  pl8envelope2.sustain(pl8[pl8presetNr].Env1_Sustain);
  pl8envelope2.release(pl8[pl8presetNr].Env1_Release);
  pl8amp.gain(1);
  pl8amp2.gain(1);
}
void Plugin8_Control() {
  switch (lastPotRow) {
    case 0:
      if (pl8[pl8presetNr].wfSelect_graph != Potentiometer[0]) {
        pl8[pl8presetNr].wfSelect_graph = Potentiometer[0];
        pl8[pl8presetNr].wfSelect = map(pl8[pl8presetNr].wfSelect_graph, 0, 127, 0, 12);
        pl8waveform1.begin(pl8[pl8presetNr].wfSelect);
        drawPot(CTRL_COL_0, CTRL_ROW_0, pl8[pl8presetNr].wfSelect_graph, pl8[pl8presetNr].wfSelect, "WForm", trackColor[desired_track]);
      }
      break;

    case 1:
      if (pl8[pl8presetNr].Filter1_Frequency_graph != Potentiometer[0]) {
        pl8[pl8presetNr].Filter1_Frequency_graph = Potentiometer[0];
        pl8[pl8presetNr].Filter1_Frequency = note_frequency[pl8[pl8presetNr].Filter1_Frequency_graph];
        pl8filter1.frequency(pl8[pl8presetNr].Filter1_Frequency);
        drawPot(CTRL_COL_0, CTRL_ROW_1, pl8[pl8presetNr].Filter1_Frequency_graph, pl8[pl8presetNr].Filter1_Frequency, "Freq", trackColor[desired_track]);
      }

      if (pl8[pl8presetNr].Filter1_Resonance_graph != Potentiometer[1]) {
        pl8[pl8presetNr].Filter1_Resonance_graph = Potentiometer[1];
        pl8[pl8presetNr].Filter1_Resonance = pl8[pl8presetNr].Filter1_Resonance_graph / 25.40;
        pl8filter1.resonance(pl8[pl8presetNr].Filter1_Resonance);
        drawPot_2(CTRL_COL_1, CTRL_ROW_1, pl8[pl8presetNr].Filter1_Resonance_graph, pl8[pl8presetNr].Filter1_Resonance_graph, "Reso", trackColor[desired_track]);
      }
      if (pl8[pl8presetNr].Filter1_Sweep_graph != Potentiometer[2]) {
        pl8[pl8presetNr].Filter1_Sweep_graph = Potentiometer[2];
        pl8[pl8presetNr].Filter1_Sweep = pl8[pl8presetNr].Filter1_Sweep_graph / 18.14;
        pl8filter1.octaveControl(pl8[pl8presetNr].Filter1_Sweep);
        drawPot_3(CTRL_COL_2, CTRL_ROW_1, pl8[pl8presetNr].Filter1_Sweep_graph, pl8[pl8presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_track]);
      }

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
        Potentiometer[0] = pl8[pl8presetNr].wfSelect * 11;
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl8[pl8presetNr].wfSelect + encoded[0]), 0, 12) * 11;
        }
        break;

      case 1:
        //Filter Frequency
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl8[pl8presetNr].Filter1_Frequency_graph + encoded[0]), 0, 127);
          pl8[pl8presetNr].Filter1_Frequency_graph = Potentiometer[0];
        }
        //Resonance
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl8[pl8presetNr].Filter1_Resonance_graph + encoded[1]), 0, 127);
          pl8[pl8presetNr].Filter1_Resonance_graph = Potentiometer[1];
        }
        //Sweep
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((pl8[pl8presetNr].Filter1_Sweep_graph + encoded[2]), 0, 127);
          pl8[pl8presetNr].Filter1_Sweep_graph = Potentiometer[2];
        }

        break;

      case 2:
        //Attack
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl8[pl8presetNr].Env1_Attack_graph + encoded[0]), 0, 127);
          pl8[pl8presetNr].Env1_Attack_graph = Potentiometer[0];
        }
        //Decay
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl8[pl8presetNr].Env1_Decay_graph + encoded[1]), 0, 127);
          pl8[pl8presetNr].Env1_Decay_graph = Potentiometer[1];
        }
        //Sustain
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((pl8[pl8presetNr].Env1_Sustain_graph + encoded[2]), 0, 127);
          pl8[pl8presetNr].Env1_Sustain_graph = Potentiometer[2];
        }
        //Release
        if (enc_moved[3]) {
          Potentiometer[3] = constrain((pl8[pl8presetNr].Env1_Release_graph + encoded[3]), 0, 127);
          pl8[pl8presetNr].Env1_Release_graph = Potentiometer[3];
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
  Plugin8_Change();
  //draw selecting pages buttons
  //draw_sub_page_buttons(2);
  drawNrInRect(18, 1, pl8presetNr, ILI9341_PURPLE);

  pl8waveform1.begin(pl8[pl8presetNr].wfSelect);
  drawPot(CTRL_COL_0, CTRL_ROW_0, pl8[pl8presetNr].wfSelect_graph, pl8[pl8presetNr].wfSelect, "WForm", trackColor[desired_track]);


  drawPot(CTRL_COL_0, CTRL_ROW_1, pl8[pl8presetNr].Filter1_Frequency_graph, note_frequency[pl8[pl8presetNr].Filter1_Frequency_graph], "Freq", trackColor[desired_track]);
  drawPot(CTRL_COL_1, CTRL_ROW_1, pl8[pl8presetNr].Filter1_Resonance_graph, pl8[pl8presetNr].Filter1_Resonance_graph, "Reso", trackColor[desired_track]);
  drawPot(CTRL_COL_2, CTRL_ROW_1, pl8[pl8presetNr].Filter1_Sweep_graph, pl8[pl8presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_track]);

  drawPot(CTRL_COL_0, CTRL_ROW_2, pl8[pl8presetNr].Env1_Attack_graph, pl8[pl8presetNr].Env1_Attack, "Atck", trackColor[desired_track]);
  drawPot(CTRL_COL_1, CTRL_ROW_2, pl8[pl8presetNr].Env1_Decay_graph, pl8[pl8presetNr].Env1_Decay, "Dec", trackColor[desired_track]);
  drawPot(CTRL_COL_2, CTRL_ROW_2, pl8[pl8presetNr].Env1_Sustain_graph, pl8[pl8presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_track]);
  drawPot(CTRL_COL_3, CTRL_ROW_2, pl8[pl8presetNr].Env1_Release_graph, pl8[pl8presetNr].Env1_Release, "Rel", trackColor[desired_track]);
}
void Plugin8_Change() {
  pl8waveform1.begin(pl8[pl8presetNr].wfSelect);
  pl8filter1.frequency(pl8[pl8presetNr].Filter1_Frequency);
  pl8filter1.resonance(pl8[pl8presetNr].Filter1_Resonance);
  pl8filter1.octaveControl(pl8[pl8presetNr].Filter1_Sweep);
  pl8envelope1.attack(pl8[pl8presetNr].Env1_Attack);
  pl8envelope2.attack(pl8[pl8presetNr].Env1_Attack);
  pl8envelope1.decay(pl8[pl8presetNr].Env1_Decay);
  pl8envelope2.decay(pl8[pl8presetNr].Env1_Decay);
  pl8envelope1.sustain(pl8[pl8presetNr].Env1_Sustain);
  pl8envelope2.sustain(pl8[pl8presetNr].Env1_Sustain);
  pl8envelope1.release(pl8[pl8presetNr].Env1_Release);
  pl8envelope2.release(pl8[pl8presetNr].Env1_Release);
}
