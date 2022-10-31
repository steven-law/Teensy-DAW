void Plugin_5_Settings() {


  pl5filter1.frequency(pl5[pl5presetNr].Filter1_Frequency);
  pl5filter1.resonance(pl5[pl5presetNr].Filter1_Resonance);
  pl5filter1.octaveControl(pl5[pl5presetNr].Filter1_Sweep);

  pl5envelope1.delay(0);
  pl5envelope1.attack(pl5[pl5presetNr].Env1_Attack);
  pl5envelope1.hold(0);
  pl5envelope1.decay(500);
  pl5envelope1.sustain(0.8);
  pl5envelope1.release(pl5[pl5presetNr].Env1_Release);

  pl5dc1.amplitude(1);

  pl5envelope2.delay(0);
  pl5envelope2.attack(pl5[pl5presetNr].Env1_Attack);
  pl5envelope2.hold(0);
  pl5envelope2.decay(500);
  pl5envelope2.sustain(0.8);
  pl5envelope2.release(pl5[pl5presetNr].Env1_Release);
  pl5amp.gain(1);
}


void Plugin5_Page_Static(byte Pagenumber) {
  //draw selecting pages buttons
  //draw_sub_page_buttons(2);
  drawNrInRect(18, 1, pl5presetNr, ILI9341_PURPLE);
  drawPot(3, CONTROL_ROW_0, pl5[pl5presetNr].selected_file_graph, pl5[pl5presetNr].selected_file, "WAV", ILI9341_PURPLE);
  drawPot(15, CONTROL_ROW_0, plugin[5].Volume_graph, plugin[5].Volume_graph, "MIX", ILI9341_RED);

  drawPot(3, CONTROL_ROW_1, pl5[pl5presetNr].Filter1_Frequency_graph, pl5[pl5presetNr].Filter1_Frequency, "Frq", ILI9341_BLUE);
  drawPot(7, CONTROL_ROW_1, pl5[pl5presetNr].Filter1_Resonance_graph, pl5[pl5presetNr].Filter1_Resonance_graph, "Res", ILI9341_BLUE);
  drawPot(11, CONTROL_ROW_1, pl5[pl5presetNr].Filter1_Sweep_graph, pl5[pl5presetNr].Filter1_Sweep_graph, "Swp", ILI9341_BLUE);

  drawPot(3, CONTROL_ROW_2, pl5[pl5presetNr].Env1_Attack_graph, pl5[pl5presetNr].Env1_Attack, "Att", ILI9341_BLUE);
  drawPot(7, CONTROL_ROW_2, pl5[pl5presetNr].Env1_Decay_graph, pl5[pl5presetNr].Env1_Decay, "Dec", ILI9341_BLUE);
  drawPot(11, CONTROL_ROW_2, pl5[pl5presetNr].Env1_Sustain_graph, pl5[pl5presetNr].Env1_Sustain_graph, "Sus", ILI9341_BLUE);
  drawPot(15, CONTROL_ROW_2, pl5[pl5presetNr].Env1_Release_graph, pl5[pl5presetNr].Env1_Release, "Rel", ILI9341_BLUE);
}
void Plugin5_Page1_Dynamic() {
    TS_Point p = ts.getPoint();
  if (ts.touched() || !buttons[6].read()) {
    gridTouchX = map(p.x, TS_MINX, TS_MAXX, 0, 19);
    gridTouchY = map(p.y, TS_MINY, TS_MAXY, 0, 14);

    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin5();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin5();
      }
    }
    //change preset
    if (gridTouchX >= 18 && gridTouchY == 1) {
      drawNrInRect(18, 1, pl5presetNr, ILI9341_PURPLE);
      if ((abs(map(Potentiometer1, 0, 127, 0, MAX_PRESETS - 1) - pl5presetNr) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        pl5presetNr = map(Potentiometer1, 0, 127, 0, MAX_PRESETS - 1);
      }
    }

    if (gridTouchY == CONTROL_ROW_0) {

      //WAV select
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, CONTROL_ROW_0, pl5[pl5presetNr].selected_file_graph, pl5[pl5presetNr].selected_file, "WAV", ILI9341_PURPLE);
        if (abs(Potentiometer1 - pl5[pl5presetNr].selected_file_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5[pl5presetNr].selected_file_graph = Potentiometer1;
          pl5[pl5presetNr].selected_file = map(pl5[pl5presetNr].selected_file_graph, 0, 127, 0, MAX_WAV_FILES);
        }
      }
      //Volume
      if (gridTouchX == 15 || gridTouchX == 16) {
        drawPot(15, CONTROL_ROW_0, plugin[5].Volume_graph, plugin[5].Volume_graph, "MIX", ILI9341_RED);
        if (abs(Potentiometer1 - plugin[5].Volume) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          plugin[5].Volume_graph = Potentiometer1;
          plugin[5].Volume = plugin[5].Volume_graph / 100.00;
          mixer6.gain(0, plugin[5].Volume);
        }
      }
    }
    if (gridTouchY == CONTROL_ROW_1) {

      //Filter Frequency
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, CONTROL_ROW_1, pl5[pl5presetNr].Filter1_Frequency_graph, pl5[pl5presetNr].Filter1_Frequency, "Frq", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl5[pl5presetNr].Filter1_Frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5[pl5presetNr].Filter1_Frequency = map(Potentiometer1, 0, 127, 40, 5900.00);
          pl5[pl5presetNr].Filter1_Frequency_graph = Potentiometer1;
          pl5filter1.frequency(pl5[pl5presetNr].Filter1_Frequency);
        }
      }
      //Resonance
      if (gridTouchX == 7 || gridTouchX == 8) {
        drawPot(7, CONTROL_ROW_1, pl5[pl5presetNr].Filter1_Resonance_graph, pl5[pl5presetNr].Filter1_Resonance_graph, "Res", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl5[pl5presetNr].Filter1_Resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5[pl5presetNr].Filter1_Resonance_graph = Potentiometer1;
          pl5[pl5presetNr].Filter1_Resonance = pl5[pl5presetNr].Filter1_Resonance_graph / 25.40;
          pl5filter1.resonance(pl5[pl5presetNr].Filter1_Resonance);
        }
      }
      //Sweep
      if (gridTouchX == 11 || gridTouchX == 12) {
        drawPot(11, CONTROL_ROW_1, pl5[pl5presetNr].Filter1_Sweep_graph, pl5[pl5presetNr].Filter1_Sweep_graph, "Swp", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl5[pl5presetNr].Filter1_Sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5[pl5presetNr].Filter1_Sweep_graph = Potentiometer1;
          pl5[pl5presetNr].Filter1_Sweep = pl5[pl5presetNr].Filter1_Sweep_graph / 18.14;
          pl5filter1.octaveControl(pl5[pl5presetNr].Filter1_Sweep);
        }
      }
    }
    if (gridTouchY == CONTROL_ROW_2) {

      //Attack
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, CONTROL_ROW_2, pl5[pl5presetNr].Env1_Attack_graph, pl5[pl5presetNr].Env1_Attack, "Att", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl5[pl5presetNr].Env1_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5[pl5presetNr].Env1_Attack_graph = Potentiometer1;
          pl5[pl5presetNr].Env1_Attack = map(pl5[pl5presetNr].Env1_Attack_graph, 0, 127, 10, 700);

          pl5envelope1.attack(pl5[pl5presetNr].Env1_Attack);
          pl5envelope2.attack(pl5[pl5presetNr].Env1_Attack);
        }
      }
      //Decay
      if (gridTouchX == 7 || gridTouchX == 8) {
        drawPot(7, CONTROL_ROW_2, pl5[pl5presetNr].Env1_Decay_graph, pl5[pl5presetNr].Env1_Decay, "Dec", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl5[pl5presetNr].Env1_Decay_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5[pl5presetNr].Env1_Decay_graph = Potentiometer1;
          pl5[pl5presetNr].Env1_Decay = map(pl5[pl5presetNr].Env1_Decay_graph, 0, 127, 10, 700);

          pl5envelope1.decay(pl5[pl5presetNr].Env1_Decay);
          pl5envelope2.decay(pl5[pl5presetNr].Env1_Decay);
        }
      }
      //Sustain
      if (gridTouchX == 11 || gridTouchX == 12) {
        drawPot(11, CONTROL_ROW_2, pl5[pl5presetNr].Env1_Sustain_graph, pl5[pl5presetNr].Env1_Sustain_graph, "Sus", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl5[pl5presetNr].Env1_Sustain_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5[pl5presetNr].Env1_Sustain_graph = Potentiometer1;
          pl5[pl5presetNr].Env1_Sustain = pl5[pl5presetNr].Env1_Sustain_graph / 127.00;
          pl5envelope1.sustain(pl5[pl5presetNr].Env1_Sustain);
          pl5envelope2.sustain(pl5[pl5presetNr].Env1_Sustain);
        }
      }
      //Release
      if (gridTouchX == 15 || gridTouchX == 16) {
        drawPot(15, CONTROL_ROW_2, pl5[pl5presetNr].Env1_Release_graph, pl5[pl5presetNr].Env1_Release, "Rel", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl5[pl5presetNr].Env1_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5[pl5presetNr].Env1_Release_graph = Potentiometer1;
          pl5[pl5presetNr].Env1_Release = map(pl5[pl5presetNr].Env1_Release_graph, 0, 127, 180, 1200);
          pl5envelope1.release(pl5[pl5presetNr].Env1_Release);
          pl5envelope2.release(pl5[pl5presetNr].Env1_Release);
        }
      }
    }
  }
}

void savePlugin5() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing plugin5.txt...");
  SD.remove("plugin5.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening plugin5.txt...");
  myFile = SD.open("plugin5.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    tft.print("Writing plugin 5 to plugin5.txt...");
    //save plugin 5 variables
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      myFile.print((char)pl5[maxpreset].Filter1_Frequency_graph);
      myFile.print((char)pl5[maxpreset].Filter1_Resonance_graph);
      myFile.print((char)pl5[maxpreset].Filter1_Sweep_graph);
      myFile.print((char)pl5[maxpreset].Env1_Attack_graph);
      myFile.print((char)pl5[maxpreset].Env1_Decay_graph);
      myFile.print((char)pl5[maxpreset].Env1_Sustain_graph);
      myFile.print((char)pl5[maxpreset].Env1_Release_graph);
      myFile.print((char)pl5[maxpreset].selected_file_graph);
      myFile.print((char)pl5[maxpreset].Volume_graph);
    }
    tft.println("Done");


    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin5.txt");
  }
}

void loadPlugin5() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("plugin5.txt");
  if (myFile) {
    tft.println("opening plugin5.txt:");


    //load plugin 5 variables
    tft.print("reading plugin 5 from plugin5.txt...");
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      pl5[maxpreset].Filter1_Frequency_graph = myFile.read();
      pl5[maxpreset].Filter1_Resonance_graph = myFile.read();
      pl5[maxpreset].Filter1_Sweep_graph = myFile.read();
      pl5[maxpreset].Env1_Attack_graph = myFile.read();
      pl5[maxpreset].Env1_Decay_graph = myFile.read();
      pl5[maxpreset].Env1_Sustain_graph = myFile.read();
      pl5[maxpreset].Env1_Release_graph = myFile.read();
      pl5[maxpreset].selected_file_graph = myFile.read();
      pl5[maxpreset].Volume_graph = myFile.read();
    }
    tft.println("Done");

    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin5.txt");
  }
}