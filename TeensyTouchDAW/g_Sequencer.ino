//this file contains the neccessary functions to show the 2 main sequencermodes:
//stepsequencer for track 0-7
//ticksequencer for track 0-7

//Notes assigning
void gridStepSequencer(int desired_instrument) {  //static Display rendering
  clearWorkSpace();
  drawStepSequencerStatic(16);
  drawActivePolySteps();
  draw_Notenames();
  drawMelodicControls();
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
  //if we press rowButton change the seeable controls
  if (rowButtonpressed) {
    rowButtonpressed = false;
    drawMelodicControls();
    drawOctaveTriangle();
    drawOctaveNumber();
  }
  switch (lastPotRow) {
    case 0:
      //gridTouchX gridTouchY voiceCount midichannel
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
      //step length
      if (enc_moved[3]) {
        allTracks[desired_instrument]->setStepLenght(encoded[3]);
      }

      break;
    case 1:
      //octaves clip clockDivision midichannel
      //octaves
      if (enc_moved[0]) {
        allTracks[desired_instrument]->setShownOctaves(encoded[0]);
        drawActivePolySteps();
        drawOctaveNumber();
        draw_Notenames();
      }
      //clip
      if (enc_moved[1]) {
        allTracks[desired_instrument]->setClipToEdit(encoded[1]);
        drawActivePolySteps();
      }
      //clockDivision
      if (enc_moved[2]) {
        allTracks[desired_instrument]->setClockDivision(encoded[2]);
      }

      //midichannel
      if (enc_moved[3]) {
        track[desired_instrument].MIDIchannel = constrain((track[desired_instrument].MIDIchannel + encoded[3]), 0, MAX_CHANNELS);
        allTracks[desired_instrument]->setMIDIChannel(encoded[3]);
      }

      break;
    case 2:
      //seqMode
      if (enc_moved[0]) {
        allTracks[desired_instrument]->setSeqMode(encoded[0]);
      }

      break;
  }



  int touched_step = gridTouchX - 2;
  int touched_tick = touched_step * 6;
  int touched_note = gridTouchY - 1;

  allTracks[0]->voiceCount = touched_note;



  if (!ts.touched() && !button[15]) {
    touched = false;
  }
  if (ts.touched() || button[15]) {
    if (!touched) {
      if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {

        int note = touched_note + allTracks[desired_instrument]->shownOctaves * 12;

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
        for (int ticks = 0; ticks < TICKS_PER_BAR; ticks++) {
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
  drawMelodicControls();



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





  if (rowButtonpressed) {
    rowButtonpressed = false;
    drawMelodicControls();
    drawOctaveTriangle();
    drawOctaveNumber();
  }

  switch (lastPotRow) {
    case 0:
      //gridTouchX gridTouchY voiceCount midichannel
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
      //step length
      if (enc_moved[3]) {
        allTracks[desired_instrument]->setStepLenght(encoded[3]);
      }
      break;
    case 1:
      //octaves seqMode step diviion step length
      //octaves
      if (enc_moved[0]) {
        allTracks[desired_instrument]->setShownOctaves(encoded[0]);
        drawActivePolyPixel();
        drawOctaveNumber();
        draw_Notenames();
      }
      //clip
      if (enc_moved[1]) {
        allTracks[desired_instrument]->setClipToEdit(encoded[1]);
        drawActivePolyPixel();
      }
      //clockDivision
      if (enc_moved[2]) {
        allTracks[desired_instrument]->setClockDivision(encoded[2]);
      }
      //midichannel
      if (enc_moved[3]) {
        track[desired_instrument].MIDIchannel = constrain((track[desired_instrument].MIDIchannel + encoded[3]), 0, MAX_CHANNELS);
        allTracks[desired_instrument]->setMIDIChannel(encoded[3]);
      }

      break;
    case 2:
      //seqMode
      if (enc_moved[0]) {
        allTracks[desired_instrument]->setSeqMode(encoded[0]);
      }

      break;
  }





  if (!ts.touched() && !button[15]) {
    touched = false;
  }
  if (enc_moved[0]) {
    touched = false;
  }

  if (ts.touched() || button[15]) {

    //clear clip
    if (gridTouchX >= 18 && gridTouchY == 9) {
      for (int tickrs = 0; tickrs < TICKS_PER_BAR; tickrs++) {
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