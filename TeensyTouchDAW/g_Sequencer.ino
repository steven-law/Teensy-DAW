//this file contains the neccessary functions to show the 3 main sequencermodes:
//drumtrack
//stepsequencer for track 2-8
//ticksequencer for track 2-8



//drumnotes assigning
void drumStepSequencer_Static() {  //static Display rendering
  clearWorkSpace();
  drawStepSequencerStatic(16);
  drawActiveDrumSteps();
  draw_Drumnotes();
  allTracks[desired_instrument]->drawClipToEdit();
  allTracks[desired_instrument]->drawSeqMode();
  allTracks[desired_instrument]->drawMIDIChannel();
  allTracks[desired_instrument]->drawStepLenght();
  drawNrInRect(18, 8, allTracks[desired_instrument]->clockDivision, trackColor[desired_instrument]);
  draw_ClipselectorRow();

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
      allTracks[desired_instrument]->setSeqMode(encoded[1]);
    }
    //ClockDivision
    if (enc_moved[2]) {
      allTracks[desired_instrument]->setClockDivision(encoded[2]);
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
      allTracks[desired_instrument]->setMIDIChannel(encoded[2]);
      track[desired_instrument].MIDIchannel = constrain((track[desired_instrument].MIDIchannel + encoded[2]), 0, MAX_CHANNELS);
    }

    //clip
    if (enc_moved[3]) {
      allTracks[desired_instrument]->setClipToEdit(encoded[3]);
      drawActiveDrumSteps();
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
        int note = drumnote[ch1tone];
        int step_number = gridTouchX - 2;

        if (!channel1Clip[allTracks[0]->clipToEdit][ch1tone][step_number]) {
          channel1Clip[allTracks[0]->clipToEdit][ch1tone][step_number] = true;
          touched = true;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, (trackColor[0] + (allTracks[0]->clipToEdit) * 20));  //draw the active steps circles
        } else if (channel1Clip[allTracks[0]->clipToEdit][ch1tone][step_number]) {
          touched = true;
          channel1Clip[allTracks[0]->clipToEdit][ch1tone][step_number] = false;
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
      allTracks[0]->clipToEdit = (gridTouchX / 2) - 1;
      drawActiveDrumSteps();
      allTracks[desired_instrument]->drawClipToEdit();
      midi01.sendNoteOn(allTracks[desired_instrument]->clipToEdit, LP_RED, 1);
    }
  }
}

//Melodic notes assigning
void gridStepSequencer(int desired_instrument) {  //static Display rendering

  clearWorkSpace();
  drawStepSequencerStatic(16);
  drawActivePolySteps();
  draw_Notenames();
  drawNrInRect(18, 8, allTracks[desired_instrument]->clockDivision, trackColor[desired_instrument]);
  allTracks[desired_instrument]->drawStepLenght();
  allTracks[desired_instrument]->drawClipToEdit();
  allTracks[desired_instrument]->drawVoiceCount();
  allTracks[desired_instrument]->drawSeqMode();
  allTracks[desired_instrument]->drawMIDIChannel();
  draw_ClipselectorRow();
  drawOctaveTriangle();
  drawOctaveNumber();
  if (launchpad) {
    midi01.sendControlChange(0, 0, 1);
    LP_drawStepsequencer();
    LP_drawOctave(3);
    //LP_drawOctave(5);
    midi01.sendNoteOn(LP_grid_notes[31], LP_GREEN, 1);
    midi01.sendNoteOn(LP_grid_notes[24], LP_RED, 1);
  }
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


  //gridTouchX gridTouchY voiceCount midichannel
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

    //voiceCount
    if (enc_moved[2]) {
      allTracks[desired_instrument]->setVoiceCount(encoded[2]);
    }

    //midichannel
    if (enc_moved[3]) {
      allTracks[desired_instrument]->setMIDIChannel(encoded[3]);
      track[desired_instrument].MIDIchannel = constrain((track[desired_instrument].MIDIchannel + encoded[3]), 0, MAX_CHANNELS);
    }
  }
  if (lastPotRow == 0) {
    //octaves seqMode step diviion step length
    if (button[14]) {
      if (enc_moved[0]) {
        //octaves
        //track[desired_instrument].shown_octaves = track[desired_instrument].shown_octaves + encoded[0];
        allTracks[desired_instrument]->setShownOctaves(encoded[0]);
        clearStepsGrid();
        drawActivePolySteps();
        drawOctaveNumber();
      }
      //seqMode
      if (enc_moved[1]) {
        allTracks[desired_instrument]->setSeqMode(encoded[1]);
      }
      //clockDivision
      if (enc_moved[2]) {
        allTracks[desired_instrument]->setClockDivision(encoded[2]);
      }
      //step length
      if (enc_moved[3]) {
        allTracks[desired_instrument]->setStepLenght(encoded[3]);
      }
    }
  }
  if (lastPotRow == 1) {
    //clip
    if (button[14]) {
      //clip
      if (enc_moved[3]) {
        allTracks[desired_instrument]->setClipToEdit(encoded[3]);
        drawActivePolySteps();
      }
    }
  }


  int touched_step = gridTouchX - 2;
  int touched_tick = touched_step * 6;
  int touched_note = gridTouchY - 1;


  static bool touched;
  if (!ts.touched() && !button[15]) {
    touched = false;
  }
  if (ts.touched() || button[15]) {
    if (!touched) {
      if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {
        int note;
        if (desired_instrument == 0) {
          note = drumnote[touched_note];
        } else {
          note = touched_note + allTracks[desired_instrument]->shownOctaves * 12;
        }

        for (int polys = 0; polys < MAX_VOICES; polys++) {
          if (allTracks[desired_instrument]->voiceCount == polys) {
            if (ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[touched_tick].voice[polys] == VALUE_NOTEOFF) {
              allTracks[desired_instrument]->setNoteOnToStep(touched_tick, polys, note);
              touched = true;
              for (int touched_ticks = 0; touched_ticks < allTracks[desired_instrument]->stepLenght; touched_ticks++) {
                ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[touched_tick + touched_ticks].voice[polys] = note;
              }

            } else if (ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[touched_tick].voice[polys] > VALUE_NOTEOFF) {
              allTracks[desired_instrument]->setNoteOffToStep(touched_tick, polys, VALUE_NOTEOFF);
              touched = true;
              for (int touched_ticks = 0; touched_ticks < allTracks[desired_instrument]->stepLenght; touched_ticks++) {
                ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[touched_tick + touched_ticks].voice[polys] = VALUE_NOTEOFF;
              }
            }
          }
        }
        //Serial.printf("entered note= %d at tick %d\n", note, touched_tick);
        drawActivePolyStepsY(touched_step);
      }
      //debug interrupt if you press the most right area
      if (gridTouchX >= 18) {
        touched = true;
        for (int ticks = 0; ticks < MAX_TICKS; ticks++) {
          Serial.print(ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[ticks].voice[0]);
          Serial.print(",");
          if (ticks == 5 || ticks == 11 || ticks == 17 || ticks == 23 || ticks == 29 || ticks == 35 || ticks == 41 || ticks == 47 || ticks == 53 || ticks == 59 || ticks == 65 || ticks == 71 || ticks == 77 || ticks == 83 || ticks == 89) {
            Serial.println("");
            Serial.print((ticks / 6) + 1);
            Serial.print(":");
          }
        }
        Serial.println("");
      }
      //octave selection
      if (gridTouchX >= OCTAVE_CHANGE_LEFTMOST) {
        if (gridTouchY >= OCTAVE_CHANGE_UP_TOPMOST && gridTouchY < OCTAVE_CHANGE_UP_BOTTOMMOST) {
          allTracks[desired_instrument]->shownOctaves--;
          touched = true;
          clearStepsGrid();
        }
        if (gridTouchY >= OCTAVE_CHANGE_DOWN_TOPMOST && gridTouchY < OCTAVE_CHANGE_DOWN_BOTTOMMOST) {
          allTracks[desired_instrument]->shownOctaves++;
          touched = true;
          clearStepsGrid();
        }
        //draw the octave number
        drawOctaveNumber();
        drawActivePolySteps();
      }
    }

    //load and save
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        saveTrack(trackNames_long[desired_instrument], desired_instrument);
        //saveMIDItrack(trackNames_long[desired_instrument], desired_instrument);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadTrack(trackNames_long[desired_instrument], desired_instrument);
      }
    }
    //clipselecting
    if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
      allTracks[desired_instrument]->clipToEdit = (gridTouchX / 2) - 1;
      clearStepsGrid();
      drawActivePolySteps();
      allTracks[desired_instrument]->drawClipToEdit();
    }
  }
}

//Ticks sets the desired notes miditickwise
void NoteFX8_Page_Static() {  //static Display rendering

  clearWorkSpace();
  draw_Notenames();
  drawOctaveTriangle();
  drawOctaveNumber();
  drawStepSequencerStatic(12);
  clearPixelGrid();
  drawActivePolyPixel();
  allTracks[desired_instrument]->drawStepLenght();
  allTracks[desired_instrument]->drawClipToEdit();
  allTracks[desired_instrument]->drawVoiceCount();
  allTracks[desired_instrument]->drawSeqMode();
  allTracks[desired_instrument]->drawMIDIChannel();



  /*
  if (launchpad) {
    midi01.sendControlChange(0, 0, 1);
    LP_drawStepsequencer();
    LP_drawOctave(3);
    //LP_drawOctave(5);
    midi01.sendNoteOn(LP_grid_notes[31], LP_GREEN, 1);
    midi01.sendNoteOn(LP_grid_notes[24], LP_RED, 1);
  }*/
}
void NoteFX8_Page1_Dynamic() {

  // int touched_step = gridTouchX - 2;
  int touched_note = gridTouchY - 1;
  /*
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
    */
  if (!button[14]) {
    //gridTouchX
    if (enc_moved[0]) {
      pixelTouchX = constrain((pixelTouchX + (encoded[0] * 2)), 0, 320);
      drawCursorPixel();
      showCoordinates();
      gridTouchX = (pixelTouchX + 7) / 16;
    }
    //gridTouchY
    if (enc_moved[1]) {
      gridTouchY = constrain((gridTouchY + encoded[1]), 0, 14);
      drawCursorPixel();
      showCoordinates();
    }


    //voiceCount
    if (enc_moved[2]) {
      allTracks[desired_instrument]->setVoiceCount(encoded[2]);
    }

    //clip
    if (enc_moved[3]) {
      allTracks[desired_instrument]->clipToEdit = constrain((allTracks[desired_instrument]->clipToEdit + encoded[3]), 0, MAX_CLIPS - 1);
      allTracks[desired_instrument]->setClipToEdit(encoded[3]);
      drawActivePolyPixel();
      drawNrInRect(18, 1, allTracks[desired_instrument]->clipToEdit, trackColor[desired_instrument] + (allTracks[desired_instrument]->clipToEdit * 20));
    }
  }

  //octaves
  if (button[14]) {
    if (enc_moved[0]) {
      //track[desired_instrument].shown_octaves = track[desired_instrument].shown_octaves + encoded[0];
      allTracks[desired_instrument]->setShownOctaves(encoded[0]);
      drawActivePolyPixel();
      drawOctaveNumber();
    }
    //seqMode
    if (enc_moved[1]) {
      allTracks[desired_instrument]->setSeqMode(encoded[1]);
    }
    //clockDivision
    if (enc_moved[2]) {
      allTracks[desired_instrument]->setClockDivision(encoded[2]);
    }
    //step length
    if (enc_moved[3]) {
      allTracks[desired_instrument]->setStepLenght(encoded[3]);
    }
  }




  static bool touched;
  if (!ts.touched() && !button[15]) {
    
    touched = false;
  }
  if (enc_moved[0]) {
    touched = false;
  }
  if (ts.touched() || button[15]) {

    //clear clip
    if (gridTouchX >= 18 && gridTouchY == 9) {
      for (int tickrs = 0; tickrs < MAX_TICKS; tickrs++) {
        for (int polys = 0; polys < MAX_VOICES; polys++) {
          ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[tickrs].voice[polys] = VALUE_NOTEOFF;
        }
        allTracks[desired_instrument]->voiceCount = 0;
      }
      drawActivePolyPixel();
    }

    if (pixelTouchX >= 30 && pixelTouchX <= 220 && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {
      if (!touched) {
        //some variables
        int desired_tick = ((pixelTouchX + 2) - (2 * STEP_FRAME_W)) / 2;
        int note = touched_note + allTracks[desired_instrument]->shownOctaves * 12;

        //assign notes to voices
        for (int polys = 0; polys < MAX_VOICES; polys++) {
          if (allTracks[desired_instrument]->voiceCount == polys) {
            if (ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[desired_tick].voice[polys] == VALUE_NOTEOFF) {
              allTracks[desired_instrument]->setNoteOnToTick(desired_tick, polys, note);
              touched = true;
              ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[desired_tick].voice[polys] = note;
            } else if (ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[desired_tick].voice[polys] > VALUE_NOTEOFF) {
              allTracks[desired_instrument]->setNoteOffToTick(desired_tick, polys, VALUE_NOTEOFF);
              touched = true;
              ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[desired_tick].voice[polys] = VALUE_NOTEOFF;
            }
          }
        }
        drawActivePolyPixelY(desired_tick);
      }

      touched = true;
      //octave selection
      if (gridTouchX >= OCTAVE_CHANGE_LEFTMOST) {
        if (gridTouchY >= OCTAVE_CHANGE_UP_TOPMOST && gridTouchY < OCTAVE_CHANGE_UP_BOTTOMMOST) {
          allTracks[desired_instrument]->shownOctaves--;
        }
        if (gridTouchY >= OCTAVE_CHANGE_DOWN_TOPMOST && gridTouchY < OCTAVE_CHANGE_DOWN_BOTTOMMOST) {
          allTracks[desired_instrument]->shownOctaves++;
        }
        clearPixelGrid();
        //draw the octave number
        drawOctaveNumber();
        drawActivePolyPixel();
      }


      //load and save
      if (gridTouchY == 0) {
        //Save button
        if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
          touched = true;
          saveTrack(trackNames_long[desired_instrument], desired_instrument);
          //saveMIDItrack(trackNames_long[desired_instrument], desired_instrument);
        }
        //Load button
        if (gridTouchX == POSITION_LOAD_BUTTON) {
          touched = true;
          loadTrack(trackNames_long[desired_instrument], desired_instrument);
        }
      }
      //clipselecting
      if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
        touched = true;
        allTracks[desired_instrument]->clipToEdit = (gridTouchX / 2) - 1;
        clearPixelGrid();
        drawActivePolyPixel();
        drawNrInRect(18, 1, allTracks[desired_instrument]->clipToEdit, trackColor[desired_instrument] + (allTracks[desired_instrument]->clipToEdit * 20));
      }
    }
  }
}