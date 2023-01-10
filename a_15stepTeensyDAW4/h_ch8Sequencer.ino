void gridStepSequencer(byte desired_instrument) {  //static Display rendering

  clearWorkSpace();
  drawStepSequencerStatic(desired_instrument);
  drawActiveSteps();
  drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
  drawMIDIchannel();
  midi01.sendControlChange(0, 0, 1);
  LP_drawStepsequencer();
  LP_drawOctave(3);
  //LP_drawOctave(5);
  midi01.sendNoteOn(LP_grid_notes[31], LP_GREEN, 1);
  midi01.sendNoteOn(LP_grid_notes[24], LP_RED, 1);
  //draw Octavebuttons
  int leftmost = STEP_FRAME_W * OCTAVE_CHANGE_LEFTMOST;
  int rightmost = STEP_FRAME_W * OCTAVE_CHANGE_RIGHTMOST;
  int UP_topmost = STEP_FRAME_H * OCTAVE_CHANGE_UP_TOPMOST;
  int UP_bottommost = STEP_FRAME_H * OCTAVE_CHANGE_UP_BOTTOMMOST;
  int DOWN_topmost = STEP_FRAME_H * OCTAVE_CHANGE_DOWN_TOPMOST;
  int DOWN_bottommost = STEP_FRAME_H * OCTAVE_CHANGE_DOWN_BOTTOMMOST;
  tft.fillRect(leftmost + 1, STEP_FRAME_H * 2, STEP_FRAME_W * 2, STEP_FRAME_H * 3, ILI9341_DARKGREY);
  tft.fillTriangle(leftmost + 1, UP_bottommost, rightmost, UP_bottommost, leftmost + STEP_FRAME_W, UP_topmost, ILI9341_LIGHTGREY);         //octave arrow up
  tft.fillTriangle(leftmost + 1, DOWN_topmost, rightmost - 2, DOWN_topmost, leftmost + STEP_FRAME_W, DOWN_bottommost, ILI9341_LIGHTGREY);  //x1, y1, x2, y2, x3, y3

  //draw the octave number
  drawOctaveNumber();
}

void melodicStepSequencer(byte desired_instrument) {
  LP_drawclipRow();
  LP_melodicstep();




  if (!button_15) {
    //gridTouchX
    if (enc_moved[0]) {
      gridTouchX = constrain((gridTouchX + encoded[0]), 0, 19);
    }
    //gridTouchY
    if (enc_moved[1]) {
      gridTouchY = constrain((gridTouchY + encoded[1]), 0, 14);
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
      drawActiveSteps();
      drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
    }
  }

  //octaves
  if (button_15) {
    if (enc_moved[0]) {
      track[desired_instrument].shown_octaves = track[desired_instrument].shown_octaves + encoded[0];
      clearStepsGrid();
      drawActiveSteps();
      //draw the octave number
      tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * OCTAVE_CHANGE_TEXT, STEP_FRAME_W * 2, STEP_FRAME_H * 1 + 1, ILI9341_DARKGREY);
      tft.setCursor(STEP_FRAME_W * 18 + 11, STEP_FRAME_H * OCTAVE_CHANGE_TEXT);
      tft.setFont(Arial_16);
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(1);
      tft.print(track[desired_instrument].shown_octaves);
    }
  }





  int touched_step = gridTouchX - 2;
  byte touched_note = gridTouchY - 1;



  TS_Point p = ts.getPoint();
  if (ts.touched() || enter_button) {

    //manually assigning steps to the grid;
    //for better behaviour here we wait for "interval, unless it would switch within micrseconds
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;


      if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {
        track[desired_instrument].tone = touched_note + track[desired_instrument].shown_octaves * 12;
        int dot_on_X = touched_step * STEP_FRAME_W + DOT_OFFSET_X;
        int dot_on_Y = touched_note * STEP_FRAME_H + DOT_OFFSET_Y;
        int notevalue_on_step = ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[touched_step];

        if (notevalue_on_step == VALUE_NOTEOFF) {
          ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[touched_step] = track[desired_instrument].tone;
          clearStepsGridY(touched_step);
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));  //draw the active steps circles

        } else if (notevalue_on_step > VALUE_NOTEOFF) {
          ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[touched_step] = VALUE_NOTEOFF;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, ILI9341_DARKGREY);  //draw the in-active steps circles
        }
      }


      //octave selection
      if (gridTouchX >= OCTAVE_CHANGE_LEFTMOST) {
        if (gridTouchY >= OCTAVE_CHANGE_UP_TOPMOST && gridTouchY < OCTAVE_CHANGE_UP_BOTTOMMOST) {
          track[desired_instrument].shown_octaves--;
          clearStepsGrid();
        }
        if (gridTouchY >= OCTAVE_CHANGE_DOWN_TOPMOST && gridTouchY < OCTAVE_CHANGE_DOWN_BOTTOMMOST) {
          track[desired_instrument].shown_octaves++;
          clearStepsGrid();
        }
        //draw the octave number
        drawOctaveNumber();
      }
    }

    //load and save
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        if (desired_instrument == 1) saveTrack2();
        if (desired_instrument == 2) saveTrack3();
        if (desired_instrument == 3) saveTrack4();
        if (desired_instrument == 4) saveTrack5();
        if (desired_instrument == 5) saveTrack6();
        if (desired_instrument == 6) saveTrack7();
        if (desired_instrument == 7) saveTrack8();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        if (desired_instrument == 1) loadTrack2();
        if (desired_instrument == 2) loadTrack3();
        if (desired_instrument == 3) loadTrack4();
        if (desired_instrument == 4) loadTrack5();
        if (desired_instrument == 5) loadTrack6();
        if (desired_instrument == 6) loadTrack7();
        if (desired_instrument == 7) loadTrack8();
      }
    }
    //clipselecting
    if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
      track[desired_instrument].clip_selector = (gridTouchX / 2) - 1;
      clearStepsGrid();
      drawActiveSteps();
      drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
    }
  }
}

void drawActiveSteps() {
  byte tone_start = track[desired_instrument].shown_octaves * 12;
  //draw active steps
  for (byte steps = 0; steps < STEP_QUANT; steps++) {
    int dot_on_X = (steps * STEP_FRAME_W) + DOT_OFFSET_X;
    int dot_on_Y = ((ctrack[desired_track].sequence[track[desired_track].clip_selector].step[steps] - tone_start) * STEP_FRAME_H) + DOT_OFFSET_Y;
    if (ctrack[desired_track].sequence[track[desired_track].clip_selector].step[steps] > VALUE_NOTEOFF) {
      tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, trackColor[desired_track] + (track[desired_track].clip_selector * 20));
    }
    if (ctrack[desired_track].sequence[track[desired_track].clip_selector].step[steps] == VALUE_NOTEOFF) {
      tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, ILI9341_DARKGREY);
    }
  }
}

void saveTrack2() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing track2.txt...");
  SD.remove("track2.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening track2.txt...");
  myFile = SD.open("track2.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {



    //save track2
    tft.print("Writing track2 to track2.txt...");
    for (byte sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (byte sstep = 0; sstep < STEP_QUANT; sstep++) {
        myFile.print((char)ctrack[1].sequence[sclip].step[sstep]);
      }
    }
    myFile.print((char)track[1].MIDIchannel);


    tft.println("Done");
    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track2.txt");
  }
}
void loadTrack2() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("track2.txt");
  if (myFile) {
    tft.println("opening track2.txt:");

    // read from the file until there's nothing else in it:



    //load track 1
    tft.print("Reading clips from track2.txt...");
    for (byte sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (byte sstep = 0; sstep < STEP_QUANT; sstep++) {
        ctrack[1].sequence[sclip].step[sstep] = myFile.read();
      }
    }
    track[1].MIDIchannel = myFile.read();
    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track2.txt");
  }
}
void saveTrack3() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing track3.txt...");
  SD.remove("track3.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening track3.txt...");
  myFile = SD.open("track3.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {



    //save track3
    tft.print("Writing track3 to track3.txt...");
    for (byte sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (byte sstep = 0; sstep < STEP_QUANT; sstep++) {
        myFile.print((char)ctrack[2].sequence[sclip].step[sstep]);
      }
    }
    myFile.print((char)track[2].MIDIchannel);

    tft.println("Done");
    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track3.txt");
  }
}
void loadTrack3() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("track3.txt");
  if (myFile) {
    tft.println("opening track3.txt:");

    // read from the file until there's nothing else in it:



    //load track 1
    tft.print("Reading clips from track3.txt...");
    for (byte sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (byte sstep = 0; sstep < STEP_QUANT; sstep++) {
        ctrack[2].sequence[sclip].step[sstep] = myFile.read();
      }
    }
    track[2].MIDIchannel = myFile.read();
    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track3.txt");
  }
}
void saveTrack4() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing track4.txt...");
  SD.remove("track4.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening track4.txt...");
  myFile = SD.open("track4.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {



    //save track4
    tft.print("Writing track4 to track4.txt...");
    for (byte sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (byte sstep = 0; sstep < STEP_QUANT; sstep++) {
        myFile.print((char)ctrack[3].sequence[sclip].step[sstep]);
      }
    }
    myFile.print((char)track[3].MIDIchannel);

    tft.println("Done");
    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track4.txt");
  }
}
void loadTrack4() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("track4.txt");
  if (myFile) {
    tft.println("opening track4.txt:");

    // read from the file until there's nothing else in it:



    //load track 1
    tft.print("Reading clips from track4.txt...");
    for (byte sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (byte sstep = 0; sstep < STEP_QUANT; sstep++) {
        ctrack[3].sequence[sclip].step[sstep] = myFile.read();
      }
    }
    track[3].MIDIchannel = myFile.read();
    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track4.txt");
  }
}
void saveTrack5() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing track5.txt...");
  SD.remove("track5.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening track5.txt...");
  myFile = SD.open("track5.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {



    //save track5
    tft.print("Writing track5 to track5.txt...");
    for (byte sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (byte sstep = 0; sstep < STEP_QUANT; sstep++) {
        myFile.print((char)ctrack[4].sequence[sclip].step[sstep]);
      }
    }
    myFile.print((char)track[4].MIDIchannel);

    tft.println("Done");
    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track5.txt");
  }
}
void loadTrack5() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("track5.txt");
  if (myFile) {
    tft.println("opening track5.txt:");

    // read from the file until there's nothing else in it:



    //load track 1
    tft.print("Reading clips from track5.txt...");
    for (byte sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (byte sstep = 0; sstep < STEP_QUANT; sstep++) {
        ctrack[4].sequence[sclip].step[sstep] = myFile.read();
      }
    }
    track[4].MIDIchannel = myFile.read();
    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track5.txt");
  }
}
void saveTrack6() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing track6.txt...");
  SD.remove("track6.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening track6.txt...");
  myFile = SD.open("track6.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {



    //save track6
    tft.print("Writing track6 to track6.txt...");
    for (byte sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (byte sstep = 0; sstep < STEP_QUANT; sstep++) {
        myFile.print((char)ctrack[5].sequence[sclip].step[sstep]);
      }
    }
    myFile.print((char)track[5].MIDIchannel);

    tft.println("Done");
    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track6.txt");
  }
}
void loadTrack6() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("track6.txt");
  if (myFile) {
    tft.println("opening track6.txt:");

    // read from the file until there's nothing else in it:



    //load track 1
    tft.print("Reading clips from track6.txt...");
    for (byte sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (byte sstep = 0; sstep < STEP_QUANT; sstep++) {
        ctrack[5].sequence[sclip].step[sstep] = myFile.read();
      }
    }
    track[5].MIDIchannel = myFile.read();
    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track6.txt");
  }
}
void saveTrack7() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing track7.txt...");
  SD.remove("track7.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening track7.txt...");
  myFile = SD.open("track7.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {



    //save track7
    tft.print("Writing track7 to track7.txt...");
    for (byte sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (byte sstep = 0; sstep < STEP_QUANT; sstep++) {
        myFile.print((char)ctrack[6].sequence[sclip].step[sstep]);
      }
    }
    myFile.print((char)track[6].MIDIchannel);

    tft.println("Done");
    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track7.txt");
  }
}
void loadTrack7() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("track7.txt");
  if (myFile) {
    tft.println("opening track7.txt:");

    // read from the file until there's nothing else in it:



    //load track 1
    tft.print("Reading clips from track7.txt...");
    for (byte sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (byte sstep = 0; sstep < STEP_QUANT; sstep++) {
        ctrack[6].sequence[sclip].step[sstep] = myFile.read();
      }
    }
    track[6].MIDIchannel = myFile.read();
    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track7.txt");
  }
}
void saveTrack8() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing track8.txt...");
  SD.remove("track8.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening track8.txt...");
  myFile = SD.open("track8.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {



    //save track8
    tft.print("Writing track8 to track8.txt...");
    for (byte sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (byte sstep = 0; sstep < STEP_QUANT; sstep++) {
        myFile.print((char)ctrack[7].sequence[sclip].step[sstep]);
      }
    }
    myFile.print((char)track[7].MIDIchannel);

    tft.println("Done");
    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track8.txt");
  }
}
void loadTrack8() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("track8.txt");
  if (myFile) {
    tft.println("opening track8.txt:");

    // read from the file until there's nothing else in it:



    //load track 8
    tft.print("Reading clips from track8.txt...");
    for (byte sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (byte sstep = 0; sstep < STEP_QUANT; sstep++) {
        ctrack[7].sequence[sclip].step[sstep] = myFile.read();
      }
    }
    track[7].MIDIchannel = myFile.read();
    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track8.txt");
  }
}