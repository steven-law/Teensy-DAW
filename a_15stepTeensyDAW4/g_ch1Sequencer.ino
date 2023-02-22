void drumStepSequencer_Static() {  //static Display rendering
  clearWorkSpace();
  drawStepSequencerStatic(0);
  drawActiveDrumSteps();
  drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));


  midi01.sendControlChange(0, 0, 1);
  LP_drawStepsequencer();
  LP_drawOctave(3);
}

void drumStepSequencer() {
  if (launchpad) {
    for (int LPclips = 0; LPclips < 8; LPclips++) {
      if (LP_grid_bool[LPclips]) {
        LP_drawclipRow();
      }
    }
    for (int notes = 0; notes < 12; notes++) {
      if (LP_octave_bool[notes])
        LP_drumstep();
    }
  }

  //assign drumnotes on the left
  if (button[14]) {
    if (enc_moved[0]) {
      int noteselector = constrain((drumnote[gridTouchY - 1] + encoded[0]), 0, 99);
      for (int i = 0; i < 12; i++) {
        drumnote[gridTouchY - 1] = noteselector;
        tft.fillRect(STEP_FRAME_W, STEP_FRAME_H * i + STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H, trackColor[0]);
        tft.setCursor(18, STEP_FRAME_H * i + 18);
        tft.setFont(Arial_8);
        tft.setTextColor(ILI9341_BLACK);
        tft.setTextSize(1);
        tft.print(drumnote[i]);
      }
    }
    //seqMode
    if (enc_moved[1]) {
      track[desired_instrument].seqMode = constrain((track[desired_instrument].seqMode + encoded[1]), 0, MAX_SEQMODES-1);
      drawChar(18, 9, seqModes[track[desired_instrument].seqMode], trackColor[desired_instrument]);
    }
  }

  if (!button[14]) {
    //gridTouchX
    if (enc_moved[0]) {
      gridTouchX = constrain((gridTouchX + encoded[0]), 0, 19);
      drawCursor();
      showCoordinates();
    }
    //gridTouchY
    if (enc_moved[1]) {
      gridTouchY = constrain((gridTouchY + encoded[1]), 0, 14);
      drawCursor();
      showCoordinates();
    }

    //midichannel
    if (enc_moved[2]) {
      track[desired_instrument].MIDIchannel = constrain((track[desired_instrument].MIDIchannel + encoded[2]), 0, MAX_CHANNELS);
      drawMIDIchannel();
    }

    //clip
    if (enc_moved[3]) {
      track[desired_instrument].clip_selector = constrain((track[desired_instrument].clip_selector + encoded[3]), 0, MAX_CLIPS - 1);
      clearStepsGrid();
      drawActiveDrumSteps();
      drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
    }
  }





  //assign drumsteps on the grid
  //for better behaviour here we wait for "interval, unless it would switch within micrseconds
  //tho, this leads to a drop of the sequencertempo


  if (ts.touched() || button[15]) {




    unsigned long currentMillis = millis();  //worse input haptic, better bpm drop when longpress (-2bpm)
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;


      if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {

        int dot_on_X = (gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X;
        int dot_on_Y = (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y;

        ch1tone = (gridTouchY - 1);
        int step_number = gridTouchX - 2;

        if (!channel1Clip[track[0].clip_selector][ch1tone][step_number]) {
          channel1Clip[track[0].clip_selector][ch1tone][step_number] = true;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, (trackColor[0] + (track[0].clip_selector) * 20));  //draw the active steps circles
        } else if (channel1Clip[track[0].clip_selector][ch1tone][step_number]) {
          channel1Clip[track[0].clip_selector][ch1tone][step_number] = false;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, ILI9341_DARKGREY);  //draw the inactive steps circles
        }
      }
    }


    //load and save
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        saveTrack1();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadTrack1();
      }
    }
    //assign drumnotes on the left


    /*if (gridTouchX == 1) {
      int noteselector = Potentiometer[3];
      for (int i = 0; i < 12; i++) {
        drumnote[gridTouchY - 1] = map(noteselector, 0, 127, 0, 48);
        tft.fillRect(STEP_FRAME_W, STEP_FRAME_H * i + STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H, trackColor[0]);
        tft.setCursor(18, STEP_FRAME_H * i + 18);
        tft.setFont(Arial_8);
        tft.setTextColor(ILI9341_BLACK);
        tft.setTextSize(1);
        tft.print(drumnote[i]);
      }
    }*/
    //clipselecting
    if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
      track[0].clip_selector = (gridTouchX / 2) - 1;
      clearStepsGrid();
      //draw active steps
      drawActiveDrumSteps();
      drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
      midi01.sendNoteOn(track[desired_instrument].clip_selector, LP_RED, 1);
    }
  }
}


void drawActiveDrumSteps() {
  for (int tone = 0; tone < 12; tone++) {
    for (int steps = 0; steps < STEP_QUANT; steps++) {
      if (channel1Clip[track[0].clip_selector][tone][steps]) {
        tft.fillCircle((steps * STEP_FRAME_W) + DOT_OFFSET_X, ((tone)*STEP_FRAME_H) + DOT_OFFSET_Y, DOT_RADIUS, trackColor[0] + ((track[0].clip_selector) * 20));
      }
    }
  }
}

void saveTrack1() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing track1.txt...");
  SD.remove("track1.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening track1.txt...");
  myFile = SD.open("track1.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {



    //save track1
    tft.print("Writing track 1 to track1.txt...");
    for (int sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (int snote = 0; snote < 12; snote++) {
        for (int sstep = 0; sstep < STEP_QUANT; sstep++) {
          int step = channel1Clip[sclip][snote][sstep] + 48;
          myFile.print((char)step);
        }
      }
    }
    int channel = track[0].MIDIchannel + 48;
    myFile.print((char)channel);

    tft.println("Done");
    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track1.txt");
  }
}
void loadTrack1() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("track1.txt");
  if (myFile) {
    tft.println("opening track1.txt:");

    // read from the file until there's nothing else in it:



    //load track 1
    tft.print("Reading songarrangment from track1.txt...");
    for (int sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (int snote = 0; snote < 12; snote++) {
        for (int sstep = 0; sstep < STEP_QUANT; sstep++) {
          int step;
          step = myFile.read();
          channel1Clip[sclip][snote][sstep] = step-48;
        }
      }
    }
    int channel;
    channel = myFile.read();
    track[0].MIDIchannel = channel - 48;
    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track1.txt");
  }
}