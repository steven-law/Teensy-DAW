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

  filter1.frequency(pl1[pl1presetNr].Filter1_Frequency);
  filter1.resonance(pl1[pl1presetNr].Filter1_Resonance);
  filter1.octaveControl(pl1[pl1presetNr].Filter1_Sweep);

  pl1mixer2.gain(0, 1);
  pl1mixer2.gain(1, 0);
  pl1mixer2.gain(2, 0);
  pl1mixer2.gain(3, 0);

  envelope1.delay(0);
  envelope1.attack(pl1[pl1presetNr].Env1_Attack);
  envelope1.hold(0);
  envelope1.decay(500);
  envelope1.sustain(0.8);
  envelope1.release(pl1[pl1presetNr].Env1_Release);

  pl1dc1.amplitude(1);

  envelope2.delay(0);
  envelope2.attack(pl1[pl1presetNr].Env1_Attack);
  envelope2.hold(0);
  envelope2.decay(500);
  envelope2.sustain(0.8);
  envelope2.release(pl1[pl1presetNr].Env1_Release);

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
      if (pl1[pl1presetNr].Filter1_Frequency_graph != Potentiometer[0]) {
        pl1[pl1presetNr].Filter1_Frequency_graph = Potentiometer[0];
        pl1[pl1presetNr].Filter1_Frequency = note_frequency[pl1[pl1presetNr].Filter1_Frequency_graph];
        filter1.frequency(pl1[pl1presetNr].Filter1_Frequency);
        drawPot(CTRL_COL_0, CTRL_ROW_0, pl1[pl1presetNr].Filter1_Frequency_graph, pl1[pl1presetNr].Filter1_Frequency, "Freq", trackColor[desired_track]);
      }

      if (pl1[pl1presetNr].Filter1_Resonance_graph != Potentiometer[1]) {
        pl1[pl1presetNr].Filter1_Resonance_graph = Potentiometer[1];
        pl1[pl1presetNr].Filter1_Resonance = pl1[pl1presetNr].Filter1_Resonance_graph / 25.40;
        filter1.resonance(pl1[pl1presetNr].Filter1_Resonance);
        drawPot_2(CTRL_COL_1, CTRL_ROW_0, pl1[pl1presetNr].Filter1_Resonance_graph, pl1[pl1presetNr].Filter1_Resonance_graph, "Reso", trackColor[desired_track]);
      }
      if (pl1[pl1presetNr].Filter1_Sweep_graph != Potentiometer[2]) {
        pl1[pl1presetNr].Filter1_Sweep_graph = Potentiometer[2];
        pl1[pl1presetNr].Filter1_Sweep = pl1[pl1presetNr].Filter1_Sweep_graph / 18.14;
        filter1.octaveControl(pl1[pl1presetNr].Filter1_Sweep);
        drawPot_3(CTRL_COL_2, CTRL_ROW_0, pl1[pl1presetNr].Filter1_Sweep_graph, pl1[pl1presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_track]);
      }
      if (pl1[pl1presetNr].Filter1_Type_graph != Potentiometer[3]) {
        pl1[pl1presetNr].Filter1_Type_graph = Potentiometer[3];
        pl1[pl1presetNr].Filter1_Type = pl1[pl1presetNr].Filter1_Type_graph / 43;
        selectFilterType(17, pl1[pl1presetNr].Filter1_Type);
        drawPot_4(CTRL_COL_3, CTRL_ROW_0, pl1[pl1presetNr].Filter1_Type_graph, pl1[pl1presetNr].Filter1_Type, "", trackColor[desired_track]);
        drawChar(CTRL_COL_3, 4, filterType[pl1[pl1presetNr].Filter1_Type], ILI9341_WHITE);
      }

      break;
    case 1:
      if (pl1[pl1presetNr].Env1_Attack_graph != Potentiometer[0]) {
        pl1[pl1presetNr].Env1_Attack_graph = Potentiometer[0];
        pl1[pl1presetNr].Env1_Attack = map(pl1[pl1presetNr].Env1_Attack_graph, 0, 127, 10, 700);
        envelope1.attack(pl1[pl1presetNr].Env1_Attack);
        envelope2.attack(pl1[pl1presetNr].Env1_Attack);
        drawPot(CTRL_COL_0, CTRL_ROW_1, pl1[pl1presetNr].Env1_Attack_graph, pl1[pl1presetNr].Env1_Attack, "Atck", trackColor[desired_track]);
      }
      if (pl1[pl1presetNr].Env1_Decay_graph != Potentiometer[1]) {
        pl1[pl1presetNr].Env1_Decay_graph = Potentiometer[1];
        pl1[pl1presetNr].Env1_Decay = map(pl1[pl1presetNr].Env1_Decay_graph, 0, 127, 10, 700);
        envelope1.decay(pl1[pl1presetNr].Env1_Decay);
        envelope2.decay(pl1[pl1presetNr].Env1_Decay);
        drawPot_2(CTRL_COL_1, CTRL_ROW_1, pl1[pl1presetNr].Env1_Decay_graph, pl1[pl1presetNr].Env1_Decay, "Dec", trackColor[desired_track]);
      }
      if (pl1[pl1presetNr].Env1_Sustain_graph != Potentiometer[2]) {
        pl1[pl1presetNr].Env1_Sustain_graph = Potentiometer[2];
        pl1[pl1presetNr].Env1_Sustain = pl1[pl1presetNr].Env1_Sustain_graph / 127.00;
        envelope1.sustain(pl1[pl1presetNr].Env1_Sustain);
        envelope2.sustain(pl1[pl1presetNr].Env1_Sustain);
        drawPot_3(CTRL_COL_2, CTRL_ROW_1, pl1[pl1presetNr].Env1_Sustain_graph, pl1[pl1presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_track]);
      }
      if (pl1[pl1presetNr].Env1_Release_graph != Potentiometer[3]) {
        pl1[pl1presetNr].Env1_Release_graph = Potentiometer[3];
        pl1[pl1presetNr].Env1_Release = map(pl1[pl1presetNr].Env1_Release_graph, 0, 127, 180, 1200);
        envelope1.release(pl1[pl1presetNr].Env1_Release);
        envelope2.release(pl1[pl1presetNr].Env1_Release);
        drawPot_4(CTRL_COL_3, CTRL_ROW_1, pl1[pl1presetNr].Env1_Release_graph, pl1[pl1presetNr].Env1_Release, "Rel", trackColor[desired_track]);
      }
      break;
  }
}
void Plugin1_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
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
        savePlugin1();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin1();
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
      //page3
      if (gridTouchY == 7 || gridTouchY == 8) {
        selectPage = PLUGIN1_PAGE3;
        Plugin_View_Static();
      }
      //page4
      if (gridTouchY == 9 || gridTouchY == 10) {
        selectPage = PLUGIN1_PAGE4;
        Plugin_View_Static();
      }
    }
  }
}
void Plugin1_Page2_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      pl1presetNr = constrain((pl1presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, pl1presetNr, ILI9341_PURPLE);
      Plugin1_Page_Static(1);
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //Filter Frequency
        Potentiometer[0] = pl1[pl1presetNr].Filter1_Frequency_graph;
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl1[pl1presetNr].Filter1_Frequency_graph + encoded[0]), 0, 127);
        }
        //Resonance
        Potentiometer[1] = pl1[pl1presetNr].Filter1_Resonance_graph;
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl1[pl1presetNr].Filter1_Resonance_graph + encoded[1]), 0, 127);
        }
        //Sweep
        Potentiometer[2] = pl1[pl1presetNr].Filter1_Sweep_graph;
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((pl1[pl1presetNr].Filter1_Sweep_graph + encoded[2]), 0, 127);
        }
        //Filtertype
        Potentiometer[3] = pl1[pl1presetNr].Filter1_Type * 43;
        if (enc_moved[3]) {
          Potentiometer[3] = constrain((pl1[pl1presetNr].Filter1_Type + encoded[3]), 0, 2) * 43;
        }
        break;

      case 1:
        //Attack
        Potentiometer[0] = pl1[pl1presetNr].Env1_Attack_graph;
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl1[pl1presetNr].Env1_Attack_graph + encoded[0]), 0, 127);
        }
        //Decay
        Potentiometer[1] = pl1[pl1presetNr].Env1_Decay_graph;
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl1[pl1presetNr].Env1_Decay_graph + encoded[1]), 0, 127);
        }
        //Sustain
        Potentiometer[2] = pl1[pl1presetNr].Env1_Sustain_graph;
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((pl1[pl1presetNr].Env1_Sustain_graph + encoded[2]), 0, 127);
        }
        //Release
        Potentiometer[3] = pl1[pl1presetNr].Env1_Release_graph;
        if (enc_moved[3]) {
          Potentiometer[3] = constrain((pl1[pl1presetNr].Env1_Release_graph + encoded[3]), 0, 127);
        }
        break;
    }
  }

  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {


    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin1();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin1();
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
      //page3
      if (gridTouchY == 7 || gridTouchY == 8) {
        selectPage = PLUGIN1_PAGE3;
        Plugin_View_Static();
      }
      //page4
      if (gridTouchY == 9 || gridTouchY == 10) {
        selectPage = PLUGIN1_PAGE4;
        Plugin_View_Static();
      }
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
    drawPot(CTRL_COL_0, CTRL_ROW_0, pl1[pl1presetNr].Filter1_Frequency_graph, note_frequency[pl1[pl1presetNr].Filter1_Frequency_graph], "Freq", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_0, pl1[pl1presetNr].Filter1_Resonance_graph, pl1[pl1presetNr].Filter1_Resonance_graph, "Reso", trackColor[desired_instrument]);
    drawPot(CTRL_COL_2, CTRL_ROW_0, pl1[pl1presetNr].Filter1_Sweep_graph, pl1[pl1presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_instrument]);
    drawPot(CTRL_COL_3, CTRL_ROW_0, pl1[pl1presetNr].Filter1_Type_graph, pl1[pl1presetNr].Filter1_Type, "", trackColor[desired_track]);
    drawChar(CTRL_COL_3, 4, filterType[pl1[pl1presetNr].Filter1_Type], ILI9341_WHITE);
    drawPot(CTRL_COL_0, CTRL_ROW_1, pl1[pl1presetNr].Env1_Attack_graph, pl1[pl1presetNr].Env1_Attack, "Atck", trackColor[desired_instrument]);
    drawPot(CTRL_COL_1, CTRL_ROW_1, pl1[pl1presetNr].Env1_Decay_graph, pl1[pl1presetNr].Env1_Decay, "Dec", trackColor[desired_track]);
    drawPot(CTRL_COL_2, CTRL_ROW_1, pl1[pl1presetNr].Env1_Sustain_graph, pl1[pl1presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_track]);
    drawPot(CTRL_COL_3, CTRL_ROW_1, pl1[pl1presetNr].Env1_Release_graph, pl1[pl1presetNr].Env1_Release, "Rel", trackColor[desired_instrument]);
  }
}
void Plugin1_Change() {
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    pl1[pl1presetNr].note_Offset[MixerColumn];
    waveform1.begin(pl1[pl1presetNr].wfSelect[MixerColumn]);
    mixer1.gain(0, pl1[pl1presetNr].note_Velo[MixerColumn]);
  }

  filter1.frequency(pl1[pl1presetNr].Filter1_Frequency);
  filter1.resonance(pl1[pl1presetNr].Filter1_Resonance);
  filter1.octaveControl(pl1[pl1presetNr].Filter1_Sweep);
  selectFilterType(17, pl1[pl1presetNr].Filter1_Type);
  envelope1.attack(pl1[pl1presetNr].Env1_Attack);
  envelope2.attack(pl1[pl1presetNr].Env1_Attack);
  envelope1.decay(pl1[pl1presetNr].Env1_Decay);
  envelope2.decay(pl1[pl1presetNr].Env1_Decay);
  envelope1.sustain(pl1[pl1presetNr].Env1_Sustain);
  envelope2.sustain(pl1[pl1presetNr].Env1_Sustain);
  envelope1.release(pl1[pl1presetNr].Env1_Release);
  envelope2.release(pl1[pl1presetNr].Env1_Release);
}

void savePlugin1() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing plugin1.txt...");
  SD.remove("plugin1.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening plugin1.txt...");
  myFile = SD.open("plugin1.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    tft.print("Writing plugin 1 to plugin1.txt...");
    //save plugin 1 variables
    for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      myFile.print((char)pl1[maxpreset].note_Offset_graph[0]);
      myFile.print((char)pl1[maxpreset].note_Offset_graph[1]);
      myFile.print((char)pl1[maxpreset].note_Offset_graph[2]);
      myFile.print((char)pl1[maxpreset].note_Offset_graph[3]);
      myFile.print((char)pl1[maxpreset].wfSelect[0]);
      myFile.print((char)pl1[maxpreset].wfSelect[1]);
      myFile.print((char)pl1[maxpreset].wfSelect[2]);
      myFile.print((char)pl1[maxpreset].wfSelect[3]);
      myFile.print((char)pl1[maxpreset].note_Velo_graph[0]);
      myFile.print((char)pl1[maxpreset].note_Velo_graph[1]);
      myFile.print((char)pl1[maxpreset].note_Velo_graph[2]);
      myFile.print((char)pl1[maxpreset].note_Velo_graph[3]);
      myFile.print((char)pl1[maxpreset].Filter1_Frequency_graph);
      myFile.print((char)pl1[maxpreset].Filter1_Resonance_graph);
      myFile.print((char)pl1[maxpreset].Filter1_Sweep_graph);
      myFile.print((char)pl1[maxpreset].Env1_Attack_graph);
      myFile.print((char)pl1[maxpreset].Env1_Decay_graph);
      myFile.print((char)pl1[maxpreset].Env1_Sustain_graph);
      myFile.print((char)pl1[maxpreset].Env1_Release_graph);
      myFile.print((char)pl1[maxpreset].Filter1_Type_graph);
    }

    tft.println("Done");
    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin1.txt");
  }
}
void loadPlugin1() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("plugin1.txt");
  if (myFile) {
    tft.println("opening plugin1.txt:");

    //load plugin 1 variables
    tft.print("reading plugin 1 from plugin1.txt...");
    for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      pl1[maxpreset].note_Offset_graph[0] = myFile.read();
      pl1[maxpreset].note_Offset_graph[1] = myFile.read();
      pl1[maxpreset].note_Offset_graph[2] = myFile.read();
      pl1[maxpreset].note_Offset_graph[3] = myFile.read();
      pl1[maxpreset].wfSelect[0] = myFile.read();
      pl1[maxpreset].wfSelect[1] = myFile.read();
      pl1[maxpreset].wfSelect[2] = myFile.read();
      pl1[maxpreset].wfSelect[3] = myFile.read();
      pl1[maxpreset].note_Velo_graph[0] = myFile.read();
      pl1[maxpreset].note_Velo_graph[1] = myFile.read();
      pl1[maxpreset].note_Velo_graph[2] = myFile.read();
      pl1[maxpreset].note_Velo_graph[3] = myFile.read();
      pl1[maxpreset].Filter1_Frequency_graph = myFile.read();
      pl1[maxpreset].Filter1_Resonance_graph = myFile.read();
      pl1[maxpreset].Filter1_Sweep_graph = myFile.read();
      pl1[maxpreset].Env1_Attack_graph = myFile.read();
      pl1[maxpreset].Env1_Decay_graph = myFile.read();
      pl1[maxpreset].Env1_Sustain_graph = myFile.read();
      pl1[maxpreset].Env1_Release_graph = myFile.read();
      pl1[maxpreset].Filter1_Type_graph = myFile.read();
    }

    tft.println("Done");


    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin1.txt");
  }

  // execute changes
  for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
    for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
      pl1[maxpreset].note_Offset[MixerColumn] = map(pl1[maxpreset].note_Offset_graph[MixerColumn], 0, 127, -32, 32);
      pl1[maxpreset].note_Velo[MixerColumn] = pl1[maxpreset].note_Velo_graph[MixerColumn] / 127.00;
      pl1[maxpreset].wfSelect_graph[MixerColumn] = pl1[maxpreset].wfSelect[MixerColumn] * 10;
    }

    pl1[maxpreset].Filter1_Frequency = note_frequency[pl1[maxpreset].Filter1_Frequency_graph];
    pl1[maxpreset].Filter1_Resonance = pl1[maxpreset].Filter1_Resonance_graph / 25.40;
    pl1[maxpreset].Filter1_Sweep = pl1[maxpreset].Filter1_Sweep_graph / 18.14;
    pl1[maxpreset].Filter1_Type = pl1[maxpreset].Filter1_Type_graph / 43;
    pl1[maxpreset].Env1_Attack = map(pl1[maxpreset].Env1_Attack_graph, 0, 127, 10, 700);
    pl1[maxpreset].Env1_Decay = map(pl1[maxpreset].Env1_Decay_graph, 0, 127, 10, 700);
    pl1[maxpreset].Env1_Sustain = pl1[maxpreset].Env1_Sustain_graph / 127.00;
    pl1[maxpreset].Env1_Release = map(pl1[maxpreset].Env1_Release_graph, 0, 127, 180, 1200);
  }
}