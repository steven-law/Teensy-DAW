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
  pl8envelope1.decay(500);
  pl8envelope1.sustain(0.8);
  pl8envelope1.release(pl8[pl8presetNr].Env1_Release);

  pl8dc1.amplitude(1);

  pl8envelope2.delay(0);
  pl8envelope2.attack(pl8[pl8presetNr].Env1_Attack);
  pl8envelope2.hold(0);
  pl8envelope2.decay(500);
  pl8envelope2.sustain(0.8);
  pl8envelope2.release(pl8[pl8presetNr].Env1_Release);
  pl8amp.gain(1);
}

//Plugin3_Page_Static(n) to show your control values

void Plugin8_Page_Static(byte Pagenumber) {
  //draw selecting pages buttons
  //draw_sub_page_buttons(2);
  drawNrInRect(18, 1, pl8presetNr, ILI9341_PURPLE);
  if (Pagenumber == 0) {
    drawPot(3, 3, pl8[pl8presetNr].wfSelect_graph, pl8[pl8presetNr].wfSelect, "WForm", trackColor[desired_track]);
    drawPot(15, 3, plugin[3].Volume_graph, plugin[3].Volume_graph, "MIX", trackColor[desired_track]);

    drawPot(3, 7, pl8[pl8presetNr].Filter1_Frequency_graph, pl8[pl8presetNr].Filter1_Frequency, "Freq", trackColor[desired_track]);
    drawPot(7, 7, pl8[pl8presetNr].Filter1_Resonance_graph, pl8[pl8presetNr].Filter1_Resonance_graph, "Reso", trackColor[desired_track]);
    drawPot(11, 7, pl8[pl8presetNr].Filter1_Sweep_graph, pl8[pl8presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_track]);

    drawPot(3, CONTROL_ROW_2, pl8[pl8presetNr].Env1_Attack_graph, pl8[pl8presetNr].Env1_Attack, "Atck", trackColor[desired_track]);
    drawPot(7, CONTROL_ROW_2, pl8[pl8presetNr].Env1_Decay_graph, pl8[pl8presetNr].Env1_Decay, "Dec", trackColor[desired_track]);
    drawPot(11, CONTROL_ROW_2, pl8[pl8presetNr].Env1_Sustain_graph, pl8[pl8presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_track]);
    drawPot(15, CONTROL_ROW_2, pl8[pl8presetNr].Env1_Release_graph, pl8[pl8presetNr].Env1_Release, "Rel", trackColor[desired_track]);
  }
}

void Plugin8_Page1_Dynamic() {



  TS_Point p = ts.getPoint();
  if (ts.touched() || !buttons[6].read()) {
    gridTouchX = map(p.x, TS_MINX, TS_MAXX, 0, 19);
    gridTouchY = map(p.y, TS_MINY, TS_MAXY, 0, 14);

    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin1();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin8();
      }
    }
    //change preset
    if (gridTouchX >= 18 && gridTouchY == 1) {
      drawNrInRect(18, 1, pl8presetNr, ILI9341_PURPLE);
      if ((abs(map(Potentiometer1, 0, 127, 0, MAX_PRESETS - 1) - pl8presetNr) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        pl8presetNr = map(Potentiometer1, 0, 127, 0, MAX_PRESETS - 1);
      }
    }
    if (millis() % 20 > 15) {
      if (gridTouchY == CONTROL_ROW_0) {

        //Waveform
        if (gridTouchX == 3 || gridTouchX == 4) {
          drawPot(3, CONTROL_ROW_0, pl8[pl8presetNr].wfSelect_graph, pl8[pl8presetNr].wfSelect, "WForm", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl8[pl8presetNr].wfSelect_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl8[pl8presetNr].wfSelect_graph = Potentiometer1;
            pl8[pl8presetNr].wfSelect = map(pl8[pl8presetNr].wfSelect_graph, 0, 127, 0, 12);
            pl8waveform1.begin(pl8[pl8presetNr].wfSelect);
          }
        }
        //Volume
        if (gridTouchX == 15 || gridTouchX == 16) {
          drawPot(15, CONTROL_ROW_0, plugin[3].Volume_graph, plugin[3].Volume_graph, "MIX", trackColor[desired_track]);
          if (abs(Potentiometer1 - plugin[3].Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            plugin[3].Volume_graph = Potentiometer1;
            plugin[3].Volume = plugin[3].Volume_graph / 127.00;
            mixer5.gain(2, plugin[3].Volume);
          }
        }
      }

      if (gridTouchY == 7) {

        //Filter Frequency
        if (gridTouchX == 3 || gridTouchX == 4) {
          drawPot(3, CONTROL_ROW_1, pl8[pl8presetNr].Filter1_Frequency_graph, pl8[pl8presetNr].Filter1_Frequency, "Frq", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl8[pl8presetNr].Filter1_Frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl8[pl8presetNr].Filter1_Frequency_graph = Potentiometer1;
            pl8[pl8presetNr].Filter1_Frequency = map(pl8[pl8presetNr].Filter1_Frequency_graph, 0, 127, 40, 5900.00);
            pl8filter1.frequency(pl8[pl8presetNr].Filter1_Frequency);
          }
        }
        //Resonance
        if (gridTouchX == 7 || gridTouchX == 8) {
          drawPot(7, CONTROL_ROW_1, pl8[pl8presetNr].Filter1_Resonance_graph, pl8[pl8presetNr].Filter1_Resonance_graph, "Res", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl8[pl8presetNr].Filter1_Resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl8[pl8presetNr].Filter1_Resonance_graph = Potentiometer1;
            pl8[pl8presetNr].Filter1_Resonance = pl8[pl8presetNr].Filter1_Resonance_graph / 25.40;
            pl8filter1.resonance(pl8[pl8presetNr].Filter1_Resonance);
          }
        }
        //Sweep
        if (gridTouchX == 11 || gridTouchX == 12) {
          drawPot(11, CONTROL_ROW_1, pl8[pl8presetNr].Filter1_Sweep_graph, pl8[pl8presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl8[pl8presetNr].Filter1_Sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl8[pl8presetNr].Filter1_Sweep_graph = Potentiometer1;
            pl8[pl8presetNr].Filter1_Sweep = pl8[pl8presetNr].Filter1_Sweep_graph / 18.14;
            pl8filter1.octaveControl(pl8[pl8presetNr].Filter1_Sweep);
          }
        }
      }

      if (gridTouchY == CONTROL_ROW_2) {

        //Attack
        if (gridTouchX == 3 || gridTouchX == 4) {
          drawPot(3, CONTROL_ROW_2, pl8[pl8presetNr].Env1_Attack_graph, pl8[pl8presetNr].Env1_Attack, "Att", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl8[pl8presetNr].Env1_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl8[pl8presetNr].Env1_Attack_graph = Potentiometer1;
            pl8[pl8presetNr].Env1_Attack = map(pl8[pl8presetNr].Env1_Attack_graph, 0, 127, 10, 700);
            pl8envelope1.attack(pl8[pl8presetNr].Env1_Attack);
            pl8envelope2.attack(pl8[pl8presetNr].Env1_Attack);
          }
        }
        //Decay
        if (gridTouchX == 7 || gridTouchX == 8) {
          drawPot(7, CONTROL_ROW_2, pl8[pl8presetNr].Env1_Decay_graph, pl8[pl8presetNr].Env1_Decay, "Dec", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl8[pl8presetNr].Env1_Decay_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl8[pl8presetNr].Env1_Decay_graph = Potentiometer1;
            pl8[pl8presetNr].Env1_Decay = map(Potentiometer1, 0, 127, 10, 700);

            pl8envelope1.decay(pl8[pl8presetNr].Env1_Decay);
            pl8envelope2.decay(pl8[pl8presetNr].Env1_Decay);
          }
        }
        //Sustain
        if (gridTouchX == 11 || gridTouchX == 12) {
          drawPot(11, CONTROL_ROW_2, pl8[pl8presetNr].Env1_Sustain_graph, pl8[pl8presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl8[pl8presetNr].Env1_Sustain_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl8[pl8presetNr].Env1_Sustain_graph = Potentiometer1;
            pl8[pl8presetNr].Env1_Sustain = pl8[pl8presetNr].Env1_Sustain_graph / 127.00;
            pl8envelope1.sustain(pl8[pl8presetNr].Env1_Sustain);
            pl8envelope2.sustain(pl8[pl8presetNr].Env1_Sustain);
          }
        }
        //Release
        if (gridTouchX == 15 || gridTouchX == 16) {
          drawPot(15, CONTROL_ROW_2, pl8[pl8presetNr].Env1_Release_graph, pl8[pl8presetNr].Env1_Release, "Rel", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl8[pl8presetNr].Env1_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl8[pl8presetNr].Env1_Release_graph = Potentiometer1;
            pl8[pl8presetNr].Env1_Release = map(pl8[pl8presetNr].Env1_Release_graph, 0, 127, 180, 1200);
            pl8envelope1.release(pl8[pl8presetNr].Env1_Release);
            pl8envelope2.release(pl8[pl8presetNr].Env1_Release);
          }
        }
      }
    }
  }
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
      myFile.print((char)pl8[maxpreset].wfSelect_graph);
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
    tft.print("reading plugin 8 from plugin8.txt...");
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      pl8[maxpreset].Filter1_Frequency_graph = myFile.read();
      pl8[maxpreset].Filter1_Resonance_graph = myFile.read();
      pl8[maxpreset].Filter1_Sweep_graph = myFile.read();
      pl8[maxpreset].Env1_Attack_graph = myFile.read();
      pl8[maxpreset].Env1_Decay_graph = myFile.read();
      pl8[maxpreset].Env1_Sustain_graph = myFile.read();
      pl8[maxpreset].Env1_Release_graph = myFile.read();
      pl8[maxpreset].wfSelect_graph = myFile.read();
    }
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin8.txt");
  }
}