//small 4Osc chord synthvoice, select the note-offsets from your played note (equal to set your chord), change gain for the 4 osc´s
//toDo: change waveform, add pw control

void Plugin_1_Settings() {
  waveform1.begin(WAVEFORM_SAWTOOTH);
  waveform1.amplitude(1);
  waveform1.frequency(note_frequency[36]);
  waveform1.pulseWidth(0.15);

  waveform2.begin(WAVEFORM_SAWTOOTH);
  waveform2.amplitude(1);
  waveform2.frequency(note_frequency[36]);
  waveform2.pulseWidth(0.15);

  waveform3.begin(WAVEFORM_SAWTOOTH);
  waveform3.amplitude(1);
  waveform3.frequency(note_frequency[36]);
  waveform3.pulseWidth(0.15);

  waveform4.begin(WAVEFORM_SAWTOOTH);
  waveform4.amplitude(1);
  waveform4.frequency(note_frequency[36]);
  waveform4.pulseWidth(0.15);

  mixer1.gain(0, 1);
  mixer1.gain(1, 1);
  mixer1.gain(2, 1);
  mixer1.gain(3, 1);

  filter1.frequency(note_frequency[pl1[pl1presetNr].Pot_Value[0]]);
  filter1.resonance((float)pl1[pl1presetNr].Pot_Value[1] / SVF_RES);
  filter1.octaveControl((float)(pl1[pl1presetNr].Pot_Value[1] / SVF_SWP));

  pl1mixer2.gain(0, 1);
  pl1mixer2.gain(1, 0);
  pl1mixer2.gain(2, 0);
  pl1mixer2.gain(3, 0);

  envelope1.delay(0);
  envelope1.attack(map(pl1[pl1presetNr].Pot_Value[4], 0, 127, 0, ATTACK_TIME));
  envelope1.hold(0);
  envelope1.decay(map(pl1[pl1presetNr].Pot_Value[5], 0, 127, 0, DECAY_TIME));
  envelope1.sustain(0.8);
  envelope1.release(map(pl1[pl1presetNr].Pot_Value[6], 0, 127, 0, RELEASE_TIME));

  pl1dc1.amplitude(1);

  envelope2.delay(0);
  envelope2.attack(map(pl1[pl1presetNr].Pot_Value[4], 0, 127, 0, ATTACK_TIME));
  envelope2.hold(0);
  envelope2.decay(map(pl1[pl1presetNr].Pot_Value[5], 0, 127, 0, DECAY_TIME));
  envelope2.sustain(0.8);
  envelope2.release(map(pl1[pl1presetNr].Pot_Value[6], 0, 127, 0, RELEASE_TIME));

  //bitcrusher1 controlled by startKnob on page 3
  bitcrusher1.bits(16);
  bitcrusher1.sampleRate(44100);

  //delay1 time controlled by stationKnob; feedback controlled by startKnob on page 4
  pl1delay1.delay(0, 3);  //set Delay(OutChannel, saved Samples) (0-7, 3-449*) *maximum

  //filter3 HighPassfilter to get rid of the muddy sound in feedbackloop
  pl1filter3.frequency(200);  //set initial Filter3 freq to 16000Hz
  pl1filter3.resonance(0);    //set Resonance to 0

  //mixer3 for feedback controlled by startKnob on page 4
  pl1mixer3.gain(0, 1);  //setze Mixer2(Kanal, Gain) (0-3, 0-1)
  pl1mixer3.gain(1, 0);

  pl1amp.gain(1);
  pl1amp2.gain(1);
}
void Plugin1_Control() {


  switch (lastPotRow) {
    case 0:
      //1 Row 1 note Offset
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (pl1[pl1presetNr].note_Offset_graph[MixerColumn] != Potentiometer[MixerColumn]) {
          pl1[pl1presetNr].note_Offset_graph[MixerColumn] = Potentiometer[MixerColumn];
          pl1[pl1presetNr].note_Offset[MixerColumn] = map(pl1[pl1presetNr].note_Offset_graph[MixerColumn], 0, 127, -18, 18);
          drawPot(MixerColumnPos, CTRL_ROW_0, pl1[pl1presetNr].note_Offset_graph[MixerColumn], pl1[pl1presetNr].note_Offset[MixerColumn], "Offset", trackColor[desired_instrument]);
        }
      }
      break;
    case 1:
      //1 Row 2 Waveform
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (pl1[pl1presetNr].wfSelect_graph[MixerColumn] != Potentiometer[MixerColumn]) {
          pl1[pl1presetNr].wfSelect_graph[MixerColumn] = Potentiometer[MixerColumn];
          pl1[pl1presetNr].wfSelect[MixerColumn] = map(pl1[pl1presetNr].wfSelect_graph[MixerColumn], 0, 127, 0, 12);
          drawPot(MixerColumnPos, CTRL_ROW_1, pl1[pl1presetNr].wfSelect_graph[MixerColumn], pl1[pl1presetNr].wfSelect[MixerColumn], "W~F", trackColor[desired_instrument]);
          waveform1.begin(pl1[pl1presetNr].wfSelect[0]);
          waveform2.begin(pl1[pl1presetNr].wfSelect[1]);
          waveform3.begin(pl1[pl1presetNr].wfSelect[2]);
          waveform4.begin(pl1[pl1presetNr].wfSelect[3]);
        }
      }
      break;
    case 2:
      //1 Row 2 note Velocity
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (pl1[pl1presetNr].note_Velo_graph[MixerColumn] != Potentiometer[MixerColumn]) {
          pl1[pl1presetNr].note_Velo_graph[MixerColumn] = Potentiometer[MixerColumn];
          pl1[pl1presetNr].note_Velo[MixerColumn] = pl1[pl1presetNr].note_Velo_graph[MixerColumn] / 127.00;
          drawPot(MixerColumnPos, CTRL_ROW_2, pl1[pl1presetNr].note_Velo_graph[MixerColumn], pl1[pl1presetNr].note_Velo_graph[MixerColumn], "Vel", trackColor[desired_instrument]);
          mixer1.gain(0, pl1[pl1presetNr].note_Velo[0]);
          mixer1.gain(1, pl1[pl1presetNr].note_Velo[1]);
          mixer1.gain(2, pl1[pl1presetNr].note_Velo[2]);
          mixer1.gain(3, pl1[pl1presetNr].note_Velo[3]);
        }
      }
      break;
  }
}
void Plugin1_Control2() {

  switch (lastPotRow) {
    case 0:
      StateVar_Filter(0, 0, CTRL_ROW_1);

      break;
    case 1:
      ADSR(1, 0, CTRL_ROW_2);
      break;
  }
}
void Plugin1_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      pl1presetNr = constrain((pl1presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, pl1presetNr, ILI9341_PURPLE);
      Plugin1_Page_Static(0);
    }
  }

  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //1 Row 1 note Offset
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = pl1[pl1presetNr].note_Offset_graph[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((pl1[pl1presetNr].note_Offset_graph[MixerColumn] + (encoded[MixerColumn] * 2)), 0, 127);
          }
        }
        break;
      case 1:
        //1 Row 2 Waveform
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = pl1[pl1presetNr].wfSelect[MixerColumn] * 11;
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((pl1[pl1presetNr].wfSelect[MixerColumn] + encoded[MixerColumn]), 0, 12) * 11;
          }
        }
        break;
      case 2:
        //1 Row 2 note Velocity
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          Potentiometer[MixerColumn] = pl1[pl1presetNr].note_Velo_graph[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((pl1[pl1presetNr].note_Velo_graph[MixerColumn] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
    }
  }
  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {

    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin1", 17);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin1", 17);
      }
    }
    //change preset
    if (gridTouchX >= 18 && gridTouchY == 1) {
      /* drawNrInRect(18, 1, pl1presetNr, ILI9341_PURPLE);
      if ((abs(map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1) - pl1presetNr) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        pl1presetNr = map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1);
      }*/
    }
    if (gridTouchY >= 2 && gridTouchY <= 4) {
      lastPotRow = 0;
    }

    if (gridTouchY >= 5 && gridTouchY <= 7) {
      lastPotRow = 1;
    }

    if (gridTouchY >= 8 && gridTouchY <= 10) {
      lastPotRow = 2;
    }




    //page selection
    if (gridTouchX >= 18) {
      //page1
      if (gridTouchY == 3 || gridTouchY == 4) {
        selectPage = PLUGIN1_PAGE1;
        Plugin_View_Static();
      }
      //page2
      if (gridTouchY == 5 || gridTouchY == 6) {
        selectPage = PLUGIN1_PAGE2;
        Plugin_View_Static();
      }
      /*
      //page3
      if (gridTouchY == 7 || gridTouchY == 8) {
        selectPage = PLUGIN1_PAGE3;
        Plugin_View_Static();
      }
      //page4
      if (gridTouchY == 9 || gridTouchY == 10) {
        selectPage = PLUGIN1_PAGE4;
        Plugin_View_Static();
      }*/
    }
  }
}
void Plugin1_Page2_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      pl1presetNr = constrain((pl1presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, pl1presetNr, ILI9341_PURPLE);
      Plugin1_Page_Static(1);
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //Filter Frequency

        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl1[pl1presetNr].Pot_Value[0] + encoded[0]), 0, 127);
          pl1[pl1presetNr].Pot_Value[0] = Potentiometer[0];
        }
        //Resonance

        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl1[pl1presetNr].Pot_Value[1] + encoded[1]), 0, 127);
          pl1[pl1presetNr].Pot_Value[1] = Potentiometer[1];
        }
        //Sweep

        if (enc_moved[2]) {
          Potentiometer[2] = constrain((pl1[pl1presetNr].Pot_Value[2] + encoded[2]), 0, 127);
          pl1[pl1presetNr].Pot_Value[2] = Potentiometer[2];
        }
        //Filtertype
        if (enc_moved[3]) {
          Potentiometer[3] = constrain((pl3[pl3presetNr].Pot_Value[4] + encoded[3]), 0, 2);
          pl3[pl3presetNr].Pot_Value[4] = Potentiometer[3];
        }
        break;

      case 1:
        //Attack
        Potentiometer[0] = pl1[pl1presetNr].Pot_Value[4];
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl1[pl1presetNr].Pot_Value[4] + encoded[0]), 0, 127);
        }
        //Decay
        Potentiometer[1] = pl1[pl1presetNr].Pot_Value[5];
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl1[pl1presetNr].Pot_Value[5] + encoded[1]), 0, 127);
        }
        //Sustain
        Potentiometer[2] = pl1[pl1presetNr].Pot_Value[6];
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((pl1[pl1presetNr].Pot_Value[6] + encoded[2]), 0, 127);
        }
        //Release
        Potentiometer[3] = pl1[pl1presetNr].Pot_Value[7];
        if (enc_moved[3]) {
          Potentiometer[3] = constrain((pl1[pl1presetNr].Pot_Value[7] + encoded[3]), 0, 127);
        }
        break;
    }
  }

  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {


    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin1", 17);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin1", 17);
      }
    }
    //change preset
    if (gridTouchX >= 18 && gridTouchY == 1) {
      /* drawNrInRect(18, 1, pl1presetNr, ILI9341_PURPLE);
      if ((abs(map(Potentiometer[0], 0, 127, 0, MAX_PRESETS) - pl1presetNr) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        pl1presetNr = map(Potentiometer[0], 0, 127, 0, MAX_PRESETS);
      }*/
    }
    if (gridTouchY >= 2 && gridTouchY <= 4) {
      lastPotRow = 0;
    }

    if (gridTouchY >= 5 && gridTouchY <= 7) {
      lastPotRow = 1;
    }



    //page selection
    if (gridTouchX >= 18) {
      //page1
      if (gridTouchY == 3 || gridTouchY == 4) {
        selectPage = PLUGIN1_PAGE1;
        Plugin_View_Static();
      }
      //page2
      if (gridTouchY == 5 || gridTouchY == 6) {
        selectPage = PLUGIN1_PAGE2;
        Plugin_View_Static();
      }
      /*
      //page3
      if (gridTouchY == 7 || gridTouchY == 8) {
        selectPage = PLUGIN1_PAGE3;
        Plugin_View_Static();
      }
      //page4
      if (gridTouchY == 9 || gridTouchY == 10) {
        selectPage = PLUGIN1_PAGE4;
        Plugin_View_Static();
      }*/
    }
  }
}
void Plugin1_Page_Static(int Pagenumber) {
  clearWorkSpace();
  Plugin1_Change();
  //draw selecting pages buttons
  draw_sub_page_buttons(2);
  drawNrInRect(18, 1, pl1presetNr, ILI9341_PURPLE);
  if (Pagenumber == 0) {
    for (int voice = 0; voice < 4; voice++) {
      byte voicePos = ((voice + 1) * 4) - 1;
      drawPot(voicePos, CTRL_ROW_0, pl1[pl1presetNr].note_Offset_graph[voice], pl1[pl1presetNr].note_Offset[voice], "Offset", trackColor[desired_instrument]);
      drawPot(voicePos, CTRL_ROW_1, pl1[pl1presetNr].wfSelect_graph[voice], pl1[pl1presetNr].wfSelect[voice], "W~F", trackColor[desired_instrument]);
      drawPot(voicePos, CTRL_ROW_2, pl1[pl1presetNr].note_Velo_graph[voice], pl1[pl1presetNr].note_Velo_graph[voice], "Vel", trackColor[desired_instrument]);
    }
  }
  if (Pagenumber == 1) {
    drawPot(CTRL_COL_0, CTRL_ROW_0, pl1[pl1presetNr].Pot_Value[0], note_frequency[pl1[pl1presetNr].Pot_Value[0]], "Freq", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_0, pl1[pl1presetNr].Pot_Value[1], pl1[pl1presetNr].Pot_Value[1], "Reso", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_0, pl1[pl1presetNr].Pot_Value[2], pl1[pl1presetNr].Pot_Value[2], "Swp", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_0, pl1[pl1presetNr].Pot_Value[3] * SVF_TYP, pl1[pl1presetNr].Pot_Value[3], "", trackColor[desired_track]);
    drawChar(CTRL_COL_3, 4, filterType[pl1[pl1presetNr].Pot_Value[3]], ILI9341_WHITE);
    drawPot(CTRL_COL_0, CTRL_ROW_1, pl1[pl1presetNr].Pot_Value[4], map(pl1[pl1presetNr].Pot_Value[4], 0, 127, 0, ATTACK_TIME), "Atck", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_1, pl1[pl1presetNr].Pot_Value[5], map(pl1[pl1presetNr].Pot_Value[5], 0, 127, 0, DECAY_TIME), "Dec", trackColor[desired_track]);
    drawPot(CTRL_COL_2, CTRL_ROW_1, pl1[pl1presetNr].Pot_Value[6], pl1[pl1presetNr].Pot_Value[6], "Sus", trackColor[desired_track]);
    drawPot(CTRL_COL_3, CTRL_ROW_1, pl1[pl1presetNr].Pot_Value[7], map(pl1[pl1presetNr].Pot_Value[6], 0, 127, 0, RELEASE_TIME), "Rel", trackColor[desired_instrument]);
  }
}
void Plugin1_Change() {
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    pl1[pl1presetNr].note_Offset[MixerColumn];
    waveform1.begin(pl1[pl1presetNr].wfSelect[MixerColumn]);
    mixer1.gain(0, pl1[pl1presetNr].note_Velo[MixerColumn]);
  }

  filter1.frequency(note_frequency[pl1[pl1presetNr].Pot_Value[0]]);
  filter1.resonance((float)(pl1[pl1presetNr].Pot_Value[1] / SVF_RES));
  filter1.octaveControl((float)(pl1[pl1presetNr].Pot_Value[2] / SVF_SWP));
  selectFilterType(17, pl1[pl1presetNr].Pot_Value[3]);
  envelope1.attack(map(pl1[pl1presetNr].Pot_Value[4], 0, 127, 0, ATTACK_TIME));
  envelope2.attack(map(pl1[pl1presetNr].Pot_Value[4], 0, 127, 0, ATTACK_TIME));
  envelope1.decay(map(pl1[pl1presetNr].Pot_Value[5], 0, 127, 0, DECAY_TIME));
  envelope2.decay(map(pl1[pl1presetNr].Pot_Value[5], 0, 127, 0, DECAY_TIME));
  envelope1.sustain((float)(pl1[pl1presetNr].Pot_Value[6] / SUSTAIN_LVL));
  envelope2.sustain((float)(pl1[pl1presetNr].Pot_Value[6] / SUSTAIN_LVL));
  envelope1.release(map(pl1[pl1presetNr].Pot_Value[6], 0, 127, 0, RELEASE_TIME));
  envelope2.release(map(pl1[pl1presetNr].Pot_Value[6], 0, 127, 0, RELEASE_TIME));
}
