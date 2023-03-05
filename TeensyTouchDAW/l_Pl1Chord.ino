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

 

  pl1mixer2.gain(0, 1);
  pl1mixer2.gain(1, 0);
  pl1mixer2.gain(2, 0);
  pl1mixer2.gain(3, 0);

  envelope1.delay(0);
  envelope1.hold(0);
  envelope1.sustain(0.8);


  pl1dc1.amplitude(1);
  envelope2.delay(0);
  envelope2.hold(0);
  envelope2.sustain(0.8);
 

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
       
        if (plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn] != Potentiometer[MixerColumn]) {
          plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn] = Potentiometer[MixerColumn];
          drawPot(MixerColumn, lastPotRow, plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn], map(plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn], 0, 127, -18, 18), "Offset", trackColor[desired_instrument]);
        }
      }
      break;
    case 1:
      //1 Row 2 Waveform
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
       
        if (plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn + 4] != Potentiometer[MixerColumn]) {
          plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn + 4] = Potentiometer[MixerColumn] / 10;
          drawPot(MixerColumn, lastPotRow, plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn] * 10, map(plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn + 4], 0, 127, 0, 12), "W~F", trackColor[desired_instrument]);
          waveform1.begin(plugin[0].preset[plpreset[0]].Pot_Value2[4]);
          waveform2.begin(plugin[0].preset[plpreset[0]].Pot_Value2[5]);
          waveform3.begin(plugin[0].preset[plpreset[0]].Pot_Value2[6]);
          waveform4.begin(plugin[0].preset[plpreset[0]].Pot_Value2[7]);
        }
      }
      break;
    case 2:
      //1 Row 2 note Velocity
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
       
        if (plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn + 8] != Potentiometer[MixerColumn]) {
          plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn + 8] = Potentiometer[MixerColumn];
          drawPot(MixerColumn, lastPotRow, plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn], plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn + 8], "Vel", trackColor[desired_instrument]);
          mixer1.gain(0, (float)(plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn + 8] / 127.00));
          mixer1.gain(1, (float)(plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn + 8] / 127.00));
          mixer1.gain(2, (float)(plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn + 8] / 127.00));
          mixer1.gain(3, (float)(plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn + 8] / 127.00));
        }
      }
      break;
  }
}
void Plugin1_Control2() {

  switch (lastPotRow) {
    case 0:
      StateVar_Filter(0, 0, lastPotRow);

      break;
    case 1:
      ADSR(1, 0, lastPotRow);
      break;
  }
}
void Plugin1_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      plpreset[0] = constrain((plpreset[0] + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[0], ILI9341_PURPLE);
      Plugin1_Page_Static(0);
    }
  }

  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //1 Row 1 note Offset
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          Encoder_to_4x127(0, MixerColumn, lastPotRow);
        }
        break;
      case 1:
        //1 Row 2 Waveform
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
         Encoder_to_4x127(0, MixerColumn, lastPotRow);
        }
        break;
      case 2:
        //1 Row 2 note Velocity
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          Encoder_to_4x127(0, MixerColumn, lastPotRow);
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
      /* drawNrInRect(18, 1, plpreset[0], ILI9341_PURPLE);
      if ((abs(map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1) - plpreset[0]) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        plpreset[0] = map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1);
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
      plpreset[0] = constrain((plpreset[0] + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[0], ILI9341_PURPLE);
      Plugin1_Page_Static(1);
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        Encoder_to_SVF(0, 0, lastPotRow);
        break;
      case 2:
        Encoder_to_4x127(0, 0, lastPotRow);
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
      /* drawNrInRect(18, 1, plpreset[0], ILI9341_PURPLE);
      if ((abs(map(Potentiometer[0], 0, 127, 0, MAX_PRESETS) - plpreset[0]) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        plpreset[0] = map(Potentiometer[0], 0, 127, 0, MAX_PRESETS);
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
  drawNrInRect(18, 1, plpreset[0], ILI9341_PURPLE);
  if (Pagenumber == 0) {
    for (int voice = 0; voice < 4; voice++) {

      drawPot(voice, 0, plugin[0].preset[plpreset[0]].Pot_Value2[voice], plugin[0].preset[plpreset[0]].Pot_Value2[voice], "Offset", trackColor[desired_instrument]);
      drawPot(voice, 1, plugin[0].preset[plpreset[0]].Pot_Value2[voice], plugin[0].preset[plpreset[0]].Pot_Value2[voice + 4] / 10, "W~F", trackColor[desired_instrument]);
      drawPot(voice, 2, plugin[0].preset[plpreset[0]].Pot_Value2[voice], plugin[0].preset[plpreset[0]].Pot_Value2[voice + 8], "Vel", trackColor[desired_instrument]);
    }
  }
  if (Pagenumber == 1) {
    drawPot(0, 0, plugin[0].preset[plpreset[0]].Pot_Value[0], note_frequency[plugin[0].preset[plpreset[0]].Pot_Value[0]], "Freq", trackColor[desired_instrument]);
    drawPot(1, 0, plugin[0].preset[plpreset[0]].Pot_Value[1], plugin[0].preset[plpreset[0]].Pot_Value[1], "Reso", trackColor[desired_instrument]);
    drawPot(2, 0, plugin[0].preset[plpreset[0]].Pot_Value[2], plugin[0].preset[plpreset[0]].Pot_Value[2], "Swp", trackColor[desired_instrument]);
    drawPot(3, 0, plugin[0].preset[plpreset[0]].Pot_Value[3] * SVF_TYP, plugin[0].preset[plpreset[0]].Pot_Value[3], "", trackColor[desired_track]);
    drawChar(CTRL_COL_3, 4, filterType[plugin[0].preset[plpreset[0]].Pot_Value[3]], ILI9341_WHITE);
    drawPot(0, 1, plugin[0].preset[plpreset[0]].Pot_Value[4], map(plugin[0].preset[plpreset[0]].Pot_Value[4], 0, 127, 0, ATTACK_TIME), "Atck", trackColor[desired_instrument]);
    drawPot(1, 1, plugin[0].preset[plpreset[0]].Pot_Value[5], map(plugin[0].preset[plpreset[0]].Pot_Value[5], 0, 127, 0, DECAY_TIME), "Dec", trackColor[desired_track]);
    drawPot(2, 1, plugin[0].preset[plpreset[0]].Pot_Value[6], plugin[0].preset[plpreset[0]].Pot_Value[6], "Sus", trackColor[desired_track]);
    drawPot(3, 1, plugin[0].preset[plpreset[0]].Pot_Value[7], map(plugin[0].preset[plpreset[0]].Pot_Value[7], 0, 127, 0, RELEASE_TIME), "Rel", trackColor[desired_instrument]);
  }
}
void Plugin1_Change() {
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn];
    waveform1.begin(plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn + 4] / 10);
    mixer1.gain(0, (float)(plugin[0].preset[plpreset[0]].Pot_Value2[MixerColumn + 8] / 127.00));
  }

  filter1.frequency(note_frequency[plugin[0].preset[plpreset[0]].Pot_Value[0]]);
  filter1.resonance((float)(plugin[0].preset[plpreset[0]].Pot_Value[1] / SVF_RES));
  filter1.octaveControl((float)(plugin[0].preset[plpreset[0]].Pot_Value[2] / SVF_SWP));
  selectFilterType(17, plugin[0].preset[plpreset[0]].Pot_Value[3]);
  envelope1.attack(map(plugin[0].preset[plpreset[0]].Pot_Value[4], 0, 127, 0, ATTACK_TIME));
  envelope2.attack(map(plugin[0].preset[plpreset[0]].Pot_Value[4], 0, 127, 0, ATTACK_TIME));
  envelope1.decay(map(plugin[0].preset[plpreset[0]].Pot_Value[5], 0, 127, 0, DECAY_TIME));
  envelope2.decay(map(plugin[0].preset[plpreset[0]].Pot_Value[5], 0, 127, 0, DECAY_TIME));
  envelope1.sustain((float)(plugin[0].preset[plpreset[0]].Pot_Value[6] / SUSTAIN_LVL));
  envelope2.sustain((float)(plugin[0].preset[plpreset[0]].Pot_Value[6] / SUSTAIN_LVL));
  envelope1.release(map(plugin[0].preset[plpreset[0]].Pot_Value[7], 0, 127, 0, RELEASE_TIME));
  envelope2.release(map(plugin[0].preset[plpreset[0]].Pot_Value[7], 0, 127, 0, RELEASE_TIME));
}
