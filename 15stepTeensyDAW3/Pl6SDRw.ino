void Plugin_6_Settings() {


  pl6filter1.frequency(pl6[pl6presetNr].Filter1_Frequency);
  pl6filter1.resonance(pl6[pl6presetNr].Filter1_Resonance);
  pl6filter1.octaveControl(pl6[pl6presetNr].Filter1_Sweep);

  pl6envelope1.delay(0);
  pl6envelope1.attack(pl6[pl6presetNr].Env1_Attack);
  pl6envelope1.hold(0);
  pl6envelope1.decay(500);
  pl6envelope1.sustain(0.8);
  pl6envelope1.release(pl6[pl6presetNr].Env1_Release);

  pl6dc1.amplitude(1);

  pl6envelope2.delay(0);
  pl6envelope2.attack(pl6[pl6presetNr].Env1_Attack);
  pl6envelope2.hold(0);
  pl6envelope2.decay(500);
  pl6envelope2.sustain(0.8);
  pl6envelope2.release(pl6[pl6presetNr].Env1_Release);
  pl6amp.gain(1);
}

void Plugin6_Page_Static(byte Pagenumber) {
  //draw selecting pages buttons
  //draw_sub_page_buttons(2);
  drawNrInRect(18, 1, pl6presetNr, ILI9341_PURPLE);
  drawPot(3, CONTROL_ROW_0, pl6[pl6presetNr].selected_file_raw_graph, pl6[pl6presetNr].selected_raw_file, "RAW", ILI9341_BLACK);
  drawPot(15, CONTROL_ROW_0, plugin[6].Volume_graph, plugin[6].Volume_graph, "MIX", ILI9341_RED);

  drawPot(3, CONTROL_ROW_1, pl6[pl6presetNr].Filter1_Frequency_graph, pl6[pl6presetNr].Filter1_Frequency, "Freq", ILI9341_BLUE);
  drawPot(7, CONTROL_ROW_1, pl6[pl6presetNr].Filter1_Resonance_graph, pl6[pl6presetNr].Filter1_Resonance_graph, "Reso", ILI9341_BLUE);
  drawPot(11, CONTROL_ROW_1, pl6[pl6presetNr].Filter1_Sweep_graph, pl6[pl6presetNr].Filter1_Sweep_graph, "Swp", ILI9341_BLUE);

  drawPot(3, CONTROL_ROW_2, pl6[pl6presetNr].Env1_Attack_graph, pl6[pl6presetNr].Env1_Attack, "Atck", ILI9341_BLUE);
  drawPot(7, CONTROL_ROW_2, pl6[pl6presetNr].Env1_Decay_graph, pl6[pl6presetNr].Env1_Decay, "Dec", ILI9341_BLUE);
  drawPot(11, CONTROL_ROW_2, pl6[pl6presetNr].Env1_Sustain_graph, pl6[pl6presetNr].Env1_Sustain_graph, "Sus", ILI9341_BLUE);
  drawPot(15, CONTROL_ROW_2, pl6[pl6presetNr].Env1_Release_graph, pl6[pl6presetNr].Env1_Release, "Rel", ILI9341_BLUE);
}
void Plugin6_Page1_Dynamic() {

  if (ts.touched() || !buttons[6].read()) {

    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin6();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin6();
      }
    }
    //change preset
    if (gridTouchX >= 18 && gridTouchY == 1) {
      drawNrInRect(18, 1, pl6presetNr, ILI9341_PURPLE);
      if ((abs(map(Potentiometer1, 0, 127, 0, MAX_PRESETS - 1) - pl6presetNr) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        pl6presetNr = map(Potentiometer1, 0, 127, 0, MAX_PRESETS - 1);
      }
    }

    if (gridTouchY == CONTROL_ROW_0) {

      //RAW select
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, CONTROL_ROW_0, pl6[pl6presetNr].selected_file_raw_graph, pl6[pl6presetNr].selected_raw_file, "RAW", ILI9341_BLACK);
        if (abs(Potentiometer1 - pl6[pl6presetNr].selected_file_raw_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl6[pl6presetNr].selected_raw_file = map(Potentiometer1, 0, 127, 0, MAX_RAW_FILES);
          pl6[pl6presetNr].selected_file_raw_graph = Potentiometer1;
        }
      }

      //Volume
      if (gridTouchX == 15 || gridTouchX == 16) {
        drawPot(15, CONTROL_ROW_0, plugin[6].Volume_graph, plugin[6].Volume_graph, "MIX", ILI9341_RED);
        if (abs(Potentiometer1 - plugin[6].Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          plugin[6].Volume_graph = Potentiometer1;
          plugin[6].Volume = plugin[6].Volume_graph / 25.40;
          mixer6.gain(1, plugin[6].Volume);
        }
      }
    }
    if (gridTouchY == CONTROL_ROW_1) {

      //Filter Frequency
      if (gridTouchX == 3 || gridTouchX == 4) {
        
        drawPot(3, CONTROL_ROW_1, pl6[pl6presetNr].Filter1_Frequency_graph, pl6[pl6presetNr].Filter1_Frequency, "Freq", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl6[pl6presetNr].Filter1_Frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl6[pl6presetNr].Filter1_Frequency_graph = Potentiometer1;
          pl6[pl6presetNr].Filter1_Frequency = map(pl6[pl6presetNr].Filter1_Frequency_graph, 0, 127, 40, 5900.00);
          pl6filter1.frequency(pl6[pl6presetNr].Filter1_Frequency);
        }
      }
      //Resonance
      if (gridTouchX == 7 || gridTouchX == 8) {
        
        drawPot(7, CONTROL_ROW_1, pl6[pl6presetNr].Filter1_Resonance_graph, pl6[pl6presetNr].Filter1_Resonance_graph, "Reso", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl6[pl6presetNr].Filter1_Resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl6[pl6presetNr].Filter1_Resonance_graph = Potentiometer1;
          pl6[pl6presetNr].Filter1_Resonance = pl6[pl6presetNr].Filter1_Resonance_graph / 25.40; //   127/5
          pl6filter1.resonance(pl6[pl6presetNr].Filter1_Resonance);
        }
      }
      //Sweep
      if (gridTouchX == 11 || gridTouchX == 12) {
        
        drawPot(11, CONTROL_ROW_1, pl6[pl6presetNr].Filter1_Sweep_graph, pl6[pl6presetNr].Filter1_Sweep_graph, "Swp", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl6[pl6presetNr].Filter1_Sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl6[pl6presetNr].Filter1_Sweep_graph = Potentiometer1;
          pl6[pl6presetNr].Filter1_Sweep = pl6[pl6presetNr].Filter1_Sweep_graph / 18.14;  //     127/7
          pl6filter1.octaveControl(pl6[pl6presetNr].Filter1_Sweep);
        }
      }
    }
    if (gridTouchY == CONTROL_ROW_2) {

      //Attack
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, CONTROL_ROW_2, pl6[pl6presetNr].Env1_Attack_graph, pl6[pl6presetNr].Env1_Attack, "Atck", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl6[pl6presetNr].Env1_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl6[pl6presetNr].Env1_Attack_graph = Potentiometer1;
          pl6[pl6presetNr].Env1_Attack = map(pl6[pl6presetNr].Env1_Attack_graph, 0, 127, 10, 700);
          
          pl6envelope1.attack(pl6[pl6presetNr].Env1_Attack);
          pl6envelope2.attack(pl6[pl6presetNr].Env1_Attack);
        }
      }
      //Decay
      if (gridTouchX == 7 || gridTouchX == 8) {
        drawPot(7, CONTROL_ROW_2, pl6[pl6presetNr].Env1_Decay_graph, pl6[pl6presetNr].Env1_Decay, "Dec", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl6[pl6presetNr].Env1_Decay_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl6[pl6presetNr].Env1_Decay = map(Potentiometer1, 0, 127, 10, 700);
          pl6[pl6presetNr].Env1_Decay_graph = Potentiometer1;
          pl6envelope1.decay(pl6[pl6presetNr].Env1_Decay);
          pl6envelope2.decay(pl6[pl6presetNr].Env1_Decay);
        }
      }
      //Sustain
      if (gridTouchX == 11 || gridTouchX == 12) {
        drawPot(11, CONTROL_ROW_2, pl6[pl6presetNr].Env1_Sustain_graph, pl6[pl6presetNr].Env1_Sustain_graph, "Sus", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl6[pl6presetNr].Env1_Sustain_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl6[pl6presetNr].Env1_Sustain_graph = Potentiometer1;
          pl6[pl6presetNr].Env1_Sustain = pl6[pl6presetNr].Env1_Sustain_graph / 100.00;
          pl6envelope1.sustain(pl6[pl6presetNr].Env1_Sustain);
          pl6envelope2.sustain(pl6[pl6presetNr].Env1_Sustain);
        }
      }
      //Release
      if (gridTouchX == 15 || gridTouchX == 16) {
        drawPot(15, CONTROL_ROW_2, pl6[pl6presetNr].Env1_Release_graph, pl6[pl6presetNr].Env1_Release, "Rel", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl6[pl6presetNr].Env1_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl6[pl6presetNr].Env1_Release = map(Potentiometer1, 0, 127, 180, 1200);
          pl6[pl6presetNr].Env1_Release_graph = Potentiometer1;
          pl6envelope1.release(pl6[pl6presetNr].Env1_Release);
          pl6envelope2.release(pl6[pl6presetNr].Env1_Release);
        }
      }
    }
  }
}

void savePlugin6() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing plugin6.txt...");
  SD.remove("plugin6.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening plugin6.txt...");
  myFile = SD.open("plugin6.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    tft.print("Writing plugin 6 to plugin6.txt...");
    //save plugin 6 variables
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      myFile.print((char)pl6[maxpreset].Filter1_Frequency_graph);
      myFile.print((char)pl6[maxpreset].Filter1_Resonance_graph);
      myFile.print((char)pl6[maxpreset].Filter1_Sweep_graph);
      myFile.print((char)pl6[maxpreset].Env1_Attack_graph);
      myFile.print((char)pl6[maxpreset].Env1_Decay_graph);
      myFile.print((char)pl6[maxpreset].Env1_Sustain_graph);
      myFile.print((char)pl6[maxpreset].Env1_Release_graph);
      myFile.print((char)pl6[maxpreset].selected_file_raw_graph);
      myFile.print((char)pl6[maxpreset].Volume_graph);
    }
    tft.println("Done");

    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin6.txt");
  }
}

void loadPlugin6() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("plugin6.txt");
  if (myFile) {
    tft.println("opening plugin6.txt:");

    // read from the file until there's nothing else in it:
    //load plugin 6 variables
    tft.print("reading plugin 6 from plugin6.txt...");
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      pl6[maxpreset].Filter1_Frequency_graph = myFile.read();
      pl6[maxpreset].Filter1_Resonance_graph = myFile.read();
      pl6[maxpreset].Filter1_Sweep_graph = myFile.read();
      pl6[maxpreset].Env1_Attack_graph = myFile.read();
      pl6[maxpreset].Env1_Decay_graph = myFile.read();
      pl6[maxpreset].Env1_Sustain_graph = myFile.read();
      pl6[maxpreset].Env1_Release_graph = myFile.read();
      pl6[maxpreset].selected_file_raw_graph = myFile.read();
      pl6[maxpreset].Volume_graph = myFile.read();
    }
    tft.println("Done");

    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin6.txt");
  }
}