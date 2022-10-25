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
}

void Plugin1_Page_Static(byte Pagenumber) {

  //draw selecting pages buttons
  draw_sub_page_buttons(2);
  drawNrInRect(18, 1, pl1presetNr, ILI9341_PURPLE);
  if (Pagenumber == 0) {
    for (byte voice = 0; voice < 4; voice++) {
      byte voicePos = ((voice + 1) * 4) - 1;
      drawPot(voicePos, CONTROL_ROW_0, pl1[pl1presetNr].note_Offset_graph[voice], pl1[pl1presetNr].note_Offset[voice], "Offset", ILI9341_RED);
      drawPot(voicePos, CONTROL_ROW_1, pl1[pl1presetNr].wfSelect_graph[voice], pl1[pl1presetNr].wfSelect_graph[voice], "W~F", ILI9341_RED);
      drawPot(voicePos, CONTROL_ROW_2, pl1[pl1presetNr].note_Velo_graph[voice], pl1[pl1presetNr].note_Velo_graph[voice], "Vel", ILI9341_RED);
    }
  }
  if (Pagenumber == 1) {
    drawPot(3, CONTROL_ROW_0, pl1[pl1presetNr].Filter1_Frequency_graph, pl1[pl1presetNr].Filter1_Frequency, "Frq", ILI9341_RED);
    drawPot(7, CONTROL_ROW_0, pl1[pl1presetNr].Filter1_Resonance_graph, pl1[pl1presetNr].Filter1_Resonance_graph, "Res", ILI9341_BLUE);
    drawPot(11, CONTROL_ROW_0, pl1[pl1presetNr].Filter1_Sweep_graph, pl1[pl1presetNr].Filter1_Sweep_graph, "Swp", ILI9341_BLUE);

    drawPot(3, CONTROL_ROW_1, pl1[pl1presetNr].Env1_Attack_graph, pl1[pl1presetNr].Env1_Attack, "Att", ILI9341_BLUE);
    drawPot(7, CONTROL_ROW_1, pl1[pl1presetNr].Env1_Release_graph, pl1[pl1presetNr].Env1_Release, "Rel", ILI9341_BLUE);
  }
}

void Plugin1_Page1_Dynamic() {

  if (ts.touched() || !buttons[6].read()) {


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
      drawNrInRect(18, 1, pl1presetNr, ILI9341_PURPLE);
      if ((abs(map(Potentiometer1, 0, 127, 0, MAX_PRESETS - 1) - pl1presetNr) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        pl1presetNr = map(Potentiometer1, 0, 127, 0, MAX_PRESETS - 1);
      }
    }

    if (gridTouchY == CONTROL_ROW_0) {

      //1 Row 1 note Offset

      for (byte voice = 0; voice < 4; voice++) {
        byte voicePos = ((voice + 1) * 4) - 1;
        if (gridTouchX == voicePos || gridTouchX == voicePos + 1) {
          drawPot(voicePos, CONTROL_ROW_0, pl1[pl1presetNr].note_Offset_graph[voice], pl1[pl1presetNr].note_Offset[voice], "Offset", ILI9341_RED);
          if (abs(Potentiometer1 - pl1[pl1presetNr].note_Offset_graph[voice]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl1[pl1presetNr].note_Offset_graph[voice] = Potentiometer1;
            pl1[pl1presetNr].note_Offset[voice] = map(pl1[pl1presetNr].note_Offset_graph[voice], 0, 127, -18, 18);
          }
        }
      }
    }

    if (gridTouchY == CONTROL_ROW_1) {

      //1 Row 2 Waveform

      for (byte voice = 0; voice < 4; voice++) {
        byte voicePos = ((voice + 1) * 4) - 1;
        if (gridTouchX == voicePos || gridTouchX == voicePos + 1) {
          drawPot(voicePos, CONTROL_ROW_1, pl1[pl1presetNr].wfSelect_graph[voice], pl1[pl1presetNr].wfSelect[voice], "W~F", ILI9341_RED);
          if (abs(Potentiometer1 - pl1[pl1presetNr].wfSelect_graph[voice]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl1[pl1presetNr].wfSelect_graph[voice] = Potentiometer1;
            pl1[pl1presetNr].wfSelect[voice] = map(pl1[pl1presetNr].wfSelect_graph[voice], 0, 127, 0, 12);
          }
        }
      }
    }

    if (gridTouchY == CONTROL_ROW_2) {

      //1 Row 2 note Velocity

      for (byte voice = 0; voice < 4; voice++) {
        byte voicePos = ((voice + 1) * 4) - 1;
        if (gridTouchX == voicePos || gridTouchX == voicePos + 1) {
          drawPot(voicePos, CONTROL_ROW_2, pl1[pl1presetNr].note_Velo_graph[voice], pl1[pl1presetNr].note_Velo_graph[voice], "Vel", ILI9341_RED);
          if (abs(Potentiometer1 - pl1[pl1presetNr].note_Velo_graph[voice]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl1[pl1presetNr].note_Velo_graph[voice] = Potentiometer1;
            pl1[pl1presetNr].note_Velo[voice] = pl1[pl1presetNr].note_Velo_graph[voice] / 127.00;
          }
        }
      }
    }





    //page selection
    if (gridTouchX >= 18) {
      //page1
      if (gridTouchY == 3 || gridTouchY == 4) {
        select_page(PLUGIN1_PAGE1);
        Plugin_View_Static(desired_instrument);
      }
      //page2
      if (gridTouchY == 5 || gridTouchY == 6) {
        select_page(PLUGIN1_PAGE2);
        Plugin_View_Static(desired_instrument);
      }
      //page3
      if (gridTouchY == 7 || gridTouchY == 8) {
        select_page(PLUGIN1_PAGE3);
        Plugin_View_Static(desired_instrument);
      }
      //page4
      if (gridTouchY == 9 || gridTouchY == 10) {
        select_page(PLUGIN1_PAGE4);
        Plugin_View_Static(desired_instrument);
      }
    }
  }
}

void Plugin1_Page2_Dynamic() {

  if (ts.touched() || !buttons[6].read()) {

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
      drawNrInRect(18, 1, pl1presetNr, ILI9341_PURPLE);
      if ((abs(map(Potentiometer1, 0, 127, 0, MAX_PRESETS) - pl1presetNr) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        pl1presetNr = map(Potentiometer1, 0, 127, 0, MAX_PRESETS);
      }
    }
    if (gridTouchY == CONTROL_ROW_0) {
      //filter frequency
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, CONTROL_ROW_0, pl1[pl1presetNr].Filter1_Frequency_graph, pl1[pl1presetNr].Filter1_Frequency, "Frq", ILI9341_RED);
        if (abs(Potentiometer1 - pl1[pl1presetNr].Filter1_Frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl1[pl1presetNr].Filter1_Frequency_graph = Potentiometer1;
          pl1[pl1presetNr].Filter1_Frequency = map(pl1[pl1presetNr].Filter1_Frequency_graph, 0, 127, 40, 4000);
          filter1.frequency(pl1[pl1presetNr].Filter1_Frequency);
        }
      }
      //Resonance
      if (gridTouchX == 7 || gridTouchX == 8) {
        drawPot(7, CONTROL_ROW_0, pl1[pl1presetNr].Filter1_Resonance_graph, pl1[pl1presetNr].Filter1_Resonance_graph, "Res", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl1[pl1presetNr].Filter1_Resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl1[pl1presetNr].Filter1_Resonance_graph = Potentiometer1;
          pl1[pl1presetNr].Filter1_Resonance_rnd = map(pl1[pl1presetNr].Filter1_Resonance_graph, 0, 127, 70, 500.00);
          pl1[pl1presetNr].Filter1_Resonance = pl1[pl1presetNr].Filter1_Resonance_rnd / 100.00;
          filter1.resonance(pl1[pl1presetNr].Filter1_Resonance);
        }
      }

      //Sweep
      if (gridTouchX == 11 || gridTouchX == 12) {
        drawPot(11, CONTROL_ROW_0, pl1[pl1presetNr].Filter1_Sweep_graph, pl1[pl1presetNr].Filter1_Sweep_graph, "Swp", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl1[pl1presetNr].Filter1_Sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl1[pl1presetNr].Filter1_Sweep_graph = Potentiometer1;
          pl1[pl1presetNr].Filter1_Sweep_rnd = map(pl1[pl1presetNr].Filter1_Sweep_graph, 0, 127, 0, 700);
          pl1[pl1presetNr].Filter1_Sweep = pl1[pl1presetNr].Filter1_Sweep_rnd / 100.00;
          filter1.octaveControl(pl1[pl1presetNr].Filter1_Sweep);
        }
      }
    }

    if (gridTouchY == CONTROL_ROW_1) {

      //Attack
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, CONTROL_ROW_1, pl1[pl1presetNr].Env1_Attack_graph, pl1[pl1presetNr].Env1_Attack, "Att", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl1[pl1presetNr].Env1_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl1[pl1presetNr].Env1_Attack_graph = Potentiometer1;
          pl1[pl1presetNr].Env1_Attack = map(pl1[pl1presetNr].Env1_Attack_graph, 0, 127, 10, 700);
          envelope1.attack(pl1[pl1presetNr].Env1_Attack);
          envelope2.attack(pl1[pl1presetNr].Env1_Attack);
        }
      }

      //Release
      if (gridTouchX == 7 || gridTouchX == 8) {
        drawPot(7, CONTROL_ROW_1, pl1[pl1presetNr].Env1_Release_graph, pl1[pl1presetNr].Env1_Release, "Rel", ILI9341_BLUE);
        if (abs(Potentiometer1 - pl1[pl1presetNr].Env1_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl1[pl1presetNr].Env1_Release_graph = Potentiometer1;
          pl1[pl1presetNr].Env1_Release = map(pl1[pl1presetNr].Env1_Release_graph, 0, 127, 100, 1200);
          envelope1.release(pl1[pl1presetNr].Env1_Release);
          envelope2.release(pl1[pl1presetNr].Env1_Release);
        }
      }
    }


    //page selection
    if (gridTouchX >= 18) {
      //page1
      if (gridTouchY == 3 || gridTouchY == 4) {
        select_page(PLUGIN1_PAGE1);
        Plugin_View_Static(desired_instrument);
      }
      //page2
      if (gridTouchY == 5 || gridTouchY == 6) {
        select_page(PLUGIN1_PAGE2);
        Plugin_View_Static(desired_instrument);
      }
      //page3
      if (gridTouchY == 7 || gridTouchY == 8) {
        select_page(PLUGIN1_PAGE3);
        Plugin_View_Static(desired_instrument);
      }
      //page4
      if (gridTouchY == 9 || gridTouchY == 10) {
        select_page(PLUGIN1_PAGE4);
        Plugin_View_Static(desired_instrument);
      }
    }
  }
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
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      myFile.print((char)pl1[maxpreset].Filter1_Frequency_graph);
      myFile.print((char)pl1[maxpreset].Filter1_Resonance_graph);
      myFile.print((char)pl1[maxpreset].Filter1_Sweep_graph);
      myFile.print((char)pl1[maxpreset].Env1_Attack_graph);
      myFile.print((char)pl1[maxpreset].Env1_Release_graph);
    }
    myFile.print((char)plugin[1].Volume_graph);
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
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      pl1[maxpreset].Filter1_Frequency_graph = myFile.read();
      pl1[maxpreset].Filter1_Resonance_graph = myFile.read();
      pl1[maxpreset].Filter1_Sweep_graph = myFile.read();
      pl1[maxpreset].Env1_Attack_graph = myFile.read();
      pl1[maxpreset].Env1_Release_graph = myFile.read();
    }
    tft.println("Done");


    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin1.txt");
  }
}