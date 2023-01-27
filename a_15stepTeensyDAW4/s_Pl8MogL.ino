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
      if (pl8[pl8presetNr].Env1_Attack_graph != Potentiometer[0]) {
        pl8[pl8presetNr].Env1_Attack_graph = Potentiometer[0];
        pl8[pl8presetNr].Env1_Attack = map(pl8[pl8presetNr].Env1_Attack_graph, 0, 127, 10, 700);
        pl8envelope1.attack(pl8[pl8presetNr].Env1_Attack);
        pl8envelope2.attack(pl8[pl8presetNr].Env1_Attack);
        drawPot(CTRL_COL_0, CTRL_ROW_2, pl8[pl8presetNr].Env1_Attack_graph, pl8[pl8presetNr].Env1_Attack, "Atck", trackColor[desired_track]);
      }
      if (pl8[pl8presetNr].Env1_Decay_graph != Potentiometer[1]) {
        pl8[pl8presetNr].Env1_Decay_graph = Potentiometer[1];
        pl8[pl8presetNr].Env1_Decay = map(pl8[pl8presetNr].Env1_Decay_graph, 0, 127, 10, 700);
        pl8envelope1.decay(pl8[pl8presetNr].Env1_Decay);
        pl8envelope2.decay(pl8[pl8presetNr].Env1_Decay);
        drawPot_2(CTRL_COL_1, CTRL_ROW_2, pl8[pl8presetNr].Env1_Decay_graph, pl8[pl8presetNr].Env1_Decay, "Dec", trackColor[desired_track]);
      }
      if (pl8[pl8presetNr].Env1_Sustain_graph != Potentiometer[2]) {
        pl8[pl8presetNr].Env1_Sustain_graph = Potentiometer[2];
        pl8[pl8presetNr].Env1_Sustain = pl8[pl8presetNr].Env1_Sustain_graph / 127.00;
        pl8envelope1.sustain(pl8[pl8presetNr].Env1_Sustain);
        pl8envelope2.sustain(pl8[pl8presetNr].Env1_Sustain);
        drawPot_3(CTRL_COL_2, CTRL_ROW_2, pl8[pl8presetNr].Env1_Sustain_graph, pl8[pl8presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_track]);
      }
      if (pl8[pl8presetNr].Env1_Release_graph != Potentiometer[3]) {
        pl8[pl8presetNr].Env1_Release_graph = Potentiometer[3];
        pl8[pl8presetNr].Env1_Release = map(pl8[pl8presetNr].Env1_Release_graph, 0, 127, 180, 1200);
        pl8envelope1.release(pl8[pl8presetNr].Env1_Release);
        pl8envelope2.release(pl8[pl8presetNr].Env1_Release);
        drawPot_4(CTRL_COL_3, CTRL_ROW_2, pl8[pl8presetNr].Env1_Release_graph, pl8[pl8presetNr].Env1_Release, "Rel", trackColor[desired_track]);
      }
      break;
  }
}
void Plugin8_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      pl8presetNr = constrain((pl8presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, pl8presetNr, ILI9341_PURPLE);
      Plugin8_Page_Static(0);
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
        Potentiometer[0] = pl8[pl8presetNr].Filter1_Frequency_graph;
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl8[pl8presetNr].Filter1_Frequency_graph + encoded[0]), 0, 127);
        }
        //Resonance
        Potentiometer[1] = pl8[pl8presetNr].Filter1_Resonance_graph;
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl8[pl8presetNr].Filter1_Resonance_graph + encoded[1]), 0, 127);
        }
        //Sweep
        Potentiometer[2] = pl8[pl8presetNr].Filter1_Sweep_graph;
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((pl8[pl8presetNr].Filter1_Sweep_graph + encoded[2]), 0, 127);
        }

        break;

      case 2:
        //Attack
        Potentiometer[0] = pl8[pl8presetNr].Env1_Attack_graph;
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl8[pl8presetNr].Env1_Attack_graph + encoded[0]), 0, 127);
        }
        //Decay
        Potentiometer[1] = pl8[pl8presetNr].Env1_Decay_graph;
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl8[pl8presetNr].Env1_Decay_graph + encoded[1]), 0, 127);
        }
        //Sustain
        Potentiometer[2] = pl8[pl8presetNr].Env1_Sustain_graph;
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((pl8[pl8presetNr].Env1_Sustain_graph + encoded[2]), 0, 127);
        }
        //Release
        Potentiometer[3] = pl8[pl8presetNr].Env1_Release_graph;
        if (enc_moved[3]) {
          Potentiometer[3] = constrain((pl8[pl8presetNr].Env1_Release_graph + encoded[3]), 0, 127);
        }
        break;
    }
  }

  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {


    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin8();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin8();
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
void Plugin8_Page_Static(byte Pagenumber) {
  clearWorkSpace();
  Plugin8_Change();
  //draw selecting pages buttons
  //draw_sub_page_buttons(2);
  drawNrInRect(18, 1, pl8presetNr, ILI9341_PURPLE);
  if (Pagenumber == 0) {
    pl8waveform1.begin(pl8[pl8presetNr].wfSelect);
    drawPot(CTRL_COL_0, CTRL_ROW_0, pl8[pl8presetNr].wfSelect_graph, pl8[pl8presetNr].wfSelect, "WForm", trackColor[desired_track]);

    pl8filter1.frequency(pl8[pl8presetNr].Filter1_Frequency);
    drawPot(CTRL_COL_0, CTRL_ROW_1, pl8[pl8presetNr].Filter1_Frequency_graph, note_frequency[pl8[pl8presetNr].Filter1_Frequency_graph], "Freq", trackColor[desired_track]);
    pl8filter1.resonance(pl8[pl8presetNr].Filter1_Resonance);
    drawPot(CTRL_COL_1, CTRL_ROW_1, pl8[pl8presetNr].Filter1_Resonance_graph, pl8[pl8presetNr].Filter1_Resonance_graph, "Reso", trackColor[desired_track]);
    pl8filter1.octaveControl(pl8[pl8presetNr].Filter1_Sweep);
    drawPot(CTRL_COL_2, CTRL_ROW_1, pl8[pl8presetNr].Filter1_Sweep_graph, pl8[pl8presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_track]);

    pl8envelope1.attack(pl8[pl8presetNr].Env1_Attack);
    pl8envelope2.attack(pl8[pl8presetNr].Env1_Attack);
    drawPot(CTRL_COL_0, CTRL_ROW_2, pl8[pl8presetNr].Env1_Attack_graph, pl8[pl8presetNr].Env1_Attack, "Atck", trackColor[desired_track]);
    pl8envelope1.decay(pl8[pl8presetNr].Env1_Decay);
    pl8envelope2.decay(pl8[pl8presetNr].Env1_Decay);
    drawPot(CTRL_COL_1, CTRL_ROW_2, pl8[pl8presetNr].Env1_Decay_graph, pl8[pl8presetNr].Env1_Decay, "Dec", trackColor[desired_track]);
    pl8envelope1.sustain(pl8[pl8presetNr].Env1_Sustain);
    pl8envelope2.sustain(pl8[pl8presetNr].Env1_Sustain);
    drawPot(CTRL_COL_2, CTRL_ROW_2, pl8[pl8presetNr].Env1_Sustain_graph, pl8[pl8presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_track]);
    pl8envelope1.release(pl8[pl8presetNr].Env1_Release);
    pl8envelope2.release(pl8[pl8presetNr].Env1_Release);
    drawPot(CTRL_COL_3, CTRL_ROW_2, pl8[pl8presetNr].Env1_Release_graph, pl8[pl8presetNr].Env1_Release, "Rel", trackColor[desired_track]);
  }
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

void savePlugin8() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing plugin8.txt...");
  SD.remove("plugin8.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening plugin8.txt...");
  myFile = SD.open("plugin8.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    tft.print("Writing plugin 8 to plugin8.txt...");
    //save plugin 8 variables
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      myFile.print((char)pl8[maxpreset].Filter1_Frequency_graph);
      myFile.print((char)pl8[maxpreset].Filter1_Resonance_graph);
      myFile.print((char)pl8[maxpreset].Filter1_Sweep_graph);
      myFile.print((char)pl8[maxpreset].Env1_Attack_graph);
      myFile.print((char)pl8[maxpreset].Env1_Decay_graph);
      myFile.print((char)pl8[maxpreset].Env1_Sustain_graph);
      myFile.print((char)pl8[maxpreset].Env1_Release_graph);
      myFile.print((char)pl8[maxpreset].wfSelect);
    }

    tft.println("Done");
    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin8.txt");
  }
}
void loadPlugin8() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("plugin8.txt");
  if (myFile) {
    tft.println("opening plugin8.txt:");

    // read from the file until there's nothing else in it:

    //load plugin 8 variables
    tft.print("reading plugin8 from plugin8.txt...");
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      pl8[maxpreset].Filter1_Frequency_graph = myFile.read();
      pl8[maxpreset].Filter1_Resonance_graph = myFile.read();
      pl8[maxpreset].Filter1_Sweep_graph = myFile.read();
      pl8[maxpreset].Env1_Attack_graph = myFile.read();
      pl8[maxpreset].Env1_Decay_graph = myFile.read();
      pl8[maxpreset].Env1_Sustain_graph = myFile.read();
      pl8[maxpreset].Env1_Release_graph = myFile.read();
      pl8[maxpreset].wfSelect = myFile.read();
    }

    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin8.txt");
  }

  for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
    pl8[maxpreset].wfSelect_graph = pl8[maxpreset].wfSelect * 10;
    pl8[maxpreset].Filter1_Frequency = note_frequency[pl8[maxpreset].Filter1_Frequency_graph];
    pl8[maxpreset].Filter1_Resonance = pl8[maxpreset].Filter1_Resonance_graph / 25.40;
    pl8[maxpreset].Filter1_Sweep = pl8[maxpreset].Filter1_Sweep_graph / 18.14;
    pl8[maxpreset].Env1_Attack = map(pl8[maxpreset].Env1_Attack_graph, 0, 127, 10, 700);
    pl8[maxpreset].Env1_Decay = map(pl8[maxpreset].Env1_Decay_graph, 0, 127, 10, 700);
    pl8[maxpreset].Env1_Sustain = pl8[maxpreset].Env1_Sustain_graph / 127.00;
    pl8[maxpreset].Env1_Release = map(pl8[maxpreset].Env1_Release_graph, 0, 127, 180, 1200);
  }
}