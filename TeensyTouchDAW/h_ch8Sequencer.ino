void gridStepSequencer(int desired_instrument) {  //static Display rendering

  clearWorkSpace();
  drawStepSequencerStatic(desired_instrument);
  drawActiveSteps();
  draw_Notenames();
  drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
  drawNrInRect(18, 8, track[desired_instrument].MIDItick_reset, trackColor[desired_instrument]);
  drawNrInRect(18, 7, track[desired_instrument].stepLength, trackColor[desired_instrument]);
  drawMIDIchannel();
  draw_Clipselector();
  draw_SeqMode();
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

void melodicStepSequencer(int desired_instrument) {
  if (launchpad) {
    for (int LPclips = 0; LPclips < 8; LPclips++) {
      if (LP_grid_bool[LPclips]) {
        LP_drawclipRow();
      }
    }
    for (int notes = 0; notes < 12; notes++) {
      for (int steps = 0; steps < 16; steps++) {
        if (LP_octave_bool[notes] || LP_grid_bool[24] || LP_grid_bool[31] || LP_step_bool[steps])
          LP_melodicstep();
      }
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
      drawActiveSteps();
      drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
    }
  }

  //octaves
  if (button[14]) {
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
    //seqMode
    if (enc_moved[1]) {
      track[desired_instrument].seqMode = constrain((track[desired_instrument].seqMode + encoded[1]), 0, MAX_SEQMODES - 1);
      drawChar(18, 9, seqModes[track[desired_instrument].seqMode], trackColor[desired_instrument]);
    }
    //step diviion
    if (enc_moved[2]) {
      track[desired_instrument].MIDItick_reset = constrain((track[desired_instrument].MIDItick_reset + encoded[2]), 0, 97);
      drawNrInRect(18, 8, track[desired_instrument].MIDItick_reset, trackColor[desired_instrument]);
    }
    //step length
    if (enc_moved[3]) {
      track[desired_instrument].stepLength = constrain((track[desired_instrument].stepLength + encoded[3]), 0, (track[desired_instrument].MIDItick_reset - 1));
      drawNrInRect(18, 7, track[desired_instrument].stepLength, trackColor[desired_instrument]);
    }
  }

  int touched_step = gridTouchX - 2;
  int touched_note = gridTouchY - 1;


  if (ts.touched() || button[15]) {
    readTouchinput();
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
        saveTrack(trackNames_long[desired_instrument], desired_instrument);
        saveMIDItrack(trackNames_long[desired_instrument], desired_instrument);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadTrack(trackNames_long[desired_instrument], desired_instrument);
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
  int tone_start = track[desired_instrument].shown_octaves * 12;
  //draw active steps
  for (int steps = 0; steps < STEP_QUANT; steps++) {
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
#define STEP_LENGTH 6
#define NOTE_OFF 0  // presuming you are still using 0 for 'no note'

void saveMIDItrack(const char* track, int trackNr) {
  //sprintf(_trackname, "%s.mid\0", track);
  SmfWriter writer;
  writer.setFilename(track);
  writer.writeHeader();
  //Serial.print("Start saving-> ");
  //writer.addSetTempo(tempo);
  //double microsPerTick = writer.get_microseconds_per_tick();
  int deltaStep = 0;
  for (int sclip = 0; sclip < MAX_CLIPS; sclip++) {
    for (int sstep = 0; sstep < STEP_QUANT; sstep++) {
      if (ctrack[trackNr].sequence[sclip].step[sstep] > 0) {
        writer.addNoteOnEvent(deltaStep, trackNr, ctrack[trackNr].sequence[sclip].step[sstep], 127);
        writer.addNoteOffEvent(4, trackNr, ctrack[trackNr].sequence[sclip].step[sstep]);
        deltaStep = 0;
      }
      if (ctrack[trackNr].sequence[sclip].step[sstep] <= 0) {
        deltaStep = deltaStep + 4;
      }
    }
  }
  writer.flush();
}

void saveTrack(const char* trackname, byte trackNr) {
  sprintf(_trackname, "%s.txt\0", trackname);
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);


  // delete the file:
  tft.print("Removing:");
  tft.print(_trackname);
  SD.remove(_trackname);
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening:");
  tft.print(_trackname);
  myFile = SD.open(_trackname, FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {
    //save tracks
    tft.print("Writing track to:");
    tft.print(_trackname);

    if (trackNr == 0) {
      //save track1
      for (int sclip = 0; sclip < NUM_CLIPS; sclip++) {
        for (int snote = 0; snote < 12; snote++) {
          for (int sstep = 0; sstep < STEP_QUANT; sstep++) {
            int step = channel1Clip[sclip][snote][sstep] + 48;
            myFile.print((char)step);
          }
        }
      }
    }

    if (trackNr > 0) {
      for (int sclip = 0; sclip < NUM_CLIPS; sclip++) {
        for (int sstep = 0; sstep < STEP_QUANT; sstep++) {
          myFile.print((char)ctrack[trackNr].sequence[sclip].step[sstep]);
        }
      }
    }

    // int channel = track[trackNr].MIDIchannel + 48;
    myFile.print((char)track[trackNr].MIDIchannel);

    // close the file:
    myFile.close();
    tft.println("Done");

  } else {
    // if the file didn't open, print an error:
    tft.println("error opening:");
    tft.print(_trackname);
  }

  tft.println("Saving done.");
  startUpScreen();
}

void loadTrack(char* trackname, int trackNr) {
  sprintf(_trackname, "%s.txt\0", trackname);
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open(_trackname);


  if (myFile) {
    tft.println("opening:");
    tft.println(_trackname);

    // read from the file until there's nothing else in it:
    //load track 1
    tft.print("Reading clips from:");
    tft.println(_trackname);

    if (trackNr == 0) {
      for (int sclip = 0; sclip < NUM_CLIPS; sclip++) {
        for (int snote = 0; snote < 12; snote++) {
          for (int sstep = 0; sstep < STEP_QUANT; sstep++) {
            int step;
            step = myFile.read();
            channel1Clip[sclip][snote][sstep] = step - 48;
          }
        }
      }
    }

    if (trackNr > 0) {
      for (int sclip = 0; sclip < NUM_CLIPS; sclip++) {
        for (int sstep = 0; sstep < STEP_QUANT; sstep++) {
          ctrack[trackNr].sequence[sclip].step[sstep] = myFile.read();
        }
      }
    }

    //int channel = track[trackNr].MIDIchannel + 48;
    myFile.print((char)track[trackNr].MIDIchannel);

    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening:");
    tft.println(_trackname);
  }
}
