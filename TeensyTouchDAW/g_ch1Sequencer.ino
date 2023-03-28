void drumStepSequencer_Static() {  //static Display rendering
  clearWorkSpace();
  drawStepSequencerStatic(16);
  drawActiveDrumSteps();
  draw_Drumnotes();
  drawMIDIchannel();
  draw_Clipselector();
  draw_SeqMode();
  drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
  drawNrInRect(18, 8, track[desired_instrument].MIDItick_reset, trackColor[desired_instrument]);

  if (launchpad) {
    midi01.sendControlChange(0, 0, 1);
    LP_drawStepsequencer();
    LP_drawOctave(3);
  }
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
      track[desired_instrument].seqMode = constrain((track[desired_instrument].seqMode + encoded[1]), 0, MAX_SEQMODES - 1);
      drawChar(18, 9, seqModes[track[desired_instrument].seqMode], trackColor[desired_instrument]);
    }
    //step diviion
    if (enc_moved[2]) {
      track[desired_instrument].MIDItick_reset = constrain((track[desired_instrument].MIDItick_reset + encoded[2]), 0, 97);
      drawNrInRect(18, 8, track[desired_instrument].MIDItick_reset, trackColor[desired_instrument]);
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


  static bool touched;
  if (!ts.touched() && !button[15]) {
    touched = false;
  }
  if (ts.touched() || button[15]) {
    if (!touched) {
      if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {

        int dot_on_X = (gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X;
        int dot_on_Y = (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y;

        ch1tone = (gridTouchY - 1);
        int step_number = gridTouchX - 2;

        if (!channel1Clip[track[0].clip_selector][ch1tone][step_number]) {
          channel1Clip[track[0].clip_selector][ch1tone][step_number] = true;
          touched = true;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, (trackColor[0] + (track[0].clip_selector) * 20));  //draw the active steps circles
        } else if (channel1Clip[track[0].clip_selector][ch1tone][step_number]) {
          touched = true;
          channel1Clip[track[0].clip_selector][ch1tone][step_number] = false;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, ILI9341_DARKGREY);  //draw the inactive steps circles
        }
      }
    }


    //load and save
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        saveTrack(trackNames_long[desired_instrument], desired_instrument);
        saveMIDItrackDrum();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadTrack(trackNames_long[desired_instrument], desired_instrument);
      }
    }
    //assign drumnotes on the left

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





void saveMIDItrackDrum() {
  SmfWriter writer;
  writer.setFilename("track1");
  writer.writeHeader();
  //Serial.print("Start saving-> ");
  int deltaStep = 0;
  for (int sclip = 0; sclip < MAX_CLIPS; sclip++) {
    for (int svoice = 0; svoice < num_voice; svoice++) {
      for (int sstep = 0; sstep < STEP_QUANT; sstep++) {
        if (channel1Clip[sclip][svoice][sstep] > 0) {
          writer.addNoteOnEvent(deltaStep, desired_instrument, drumnote[svoice], 127);
          writer.addNoteOffEvent(4, desired_instrument, drumnote[svoice]);
          deltaStep = 0;
        }
        if (channel1Clip[sclip][svoice][sstep] <= 0) {
          deltaStep = deltaStep + 4;
        }
      }
    }
  }
  writer.flush();
}