//this file contains the neccessary functions to show the 2 main sequencermodes:
//stepsequencer for track 0-7
//ticksequencer for track 0-7

//Notes assigning
void gridStepSequencer() {  //static Display rendering
  clearWorkSpace();

  draw_Notenames();
  drawMelodicControls();
  draw_ClipselectorRow();
  if (allTracks[desired_instrument]->noteInputMode == 0) {
    drawStepSequencerStatic(16);
    drawActivePolySteps();
  } else {
    drawStepSequencerStatic(TICK_PIXEL_WIDTH * TICKS_PER_STEP);
    drawActivePolyPixel();
  }
  if (launchpad) {
    midi01.sendControlChange(0, 0, 1);
    LP_drawStepsequencer();
    LP_drawOctave(3);
    //LP_drawOctave(5);
    midi01.sendNoteOn(LP_grid_notes[31], LP_GREEN, 1);
    midi01.sendNoteOn(LP_grid_notes[24], LP_RED, 1);
  }
}
//"Steps" sets the desired notes steptickwise
void melodicStepSequencer() {
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
      if (enc_moved[1]) {
        allTracks[desired_instrument]->setNoteInputMode(encoded[1]);
        gridStepSequencer();
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

//"Ticks" sets the desired notes miditickwise
void melodicTickSequencer() {

  // int touched_step = gridTouchX - 2;
  int touched_note = gridTouchY - 1;
  allTracks[0]->voiceCount = touched_note;
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
  }

  switch (lastPotRow) {
    case 0:
      //gridTouchX gridTouchY voiceCount midichannel
      //gridTouchX

      if (enc_moved[0]) {
        pixelTouchX = constrain((pixelTouchX + (encoded[0] * TICK_PIXEL_WIDTH)), 0, 320);
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
      if (enc_moved[1]) {
        allTracks[desired_instrument]->setNoteInputMode(encoded[1]);
        gridStepSequencer();
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

    if (pixelTouchX >= 28 && pixelTouchX <= 320 && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {
      if (!touched) {
        //some variables
        int desired_tick = (((pixelTouchX) - (2 * STEP_FRAME_W)) / TICK_PIXEL_WIDTH) + 1;
        int note = touched_note + allTracks[desired_instrument]->shownOctaves * 12;

        //assign notes to voices
        for (int polys = 0; polys < MAX_VOICES; polys++) {
          if (allTracks[desired_instrument]->voiceCount == polys) {
            if (ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[desired_tick].voice[polys] == VALUE_NOTEOFF) {
              for (int touched_ticks = 0; touched_ticks < allTracks[desired_instrument]->stepLenght; touched_ticks++) {
                ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[desired_tick + touched_ticks].voice[polys] = note;
                allTracks[desired_instrument]->setNoteOnToTick(desired_tick + touched_ticks, polys, note);
                drawActivePolyPixelY(desired_tick + touched_ticks);
              }
              touched = true;
            } else if (ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[desired_tick].voice[polys] > VALUE_NOTEOFF) {
              for (int touched_ticks = 0; touched_ticks < allTracks[desired_instrument]->stepLenght; touched_ticks++) {
                ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[desired_tick + touched_ticks].voice[polys] = VALUE_NOTEOFF;
                allTracks[desired_instrument]->setNoteOffToTick(desired_tick + touched_ticks, polys, VALUE_NOTEOFF);
                drawActivePolyPixelY(desired_tick + touched_ticks);
              }
              touched = true;
            }
          }
        }
      }
    }
    touched = true;



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




void Encoder_to_NFX_Value(int plug, int COL, int ROW, int MAX) {
  if (enc_moved[COL]) {
    Potentiometer[COL] = constrain((plugin[plug].preset[plpreset[plug]].Pot_Value[COL + (ROW * 4)] + encoded[COL]), 0, MAX);
  } else if (incomingCC_changed[COL]) {
    Potentiometer[COL] = incomingCC[COL];
    incomingCC_changed[COL] = false;
  }
}
//this section holds the various sequencermodes inside
//grid sequencer
void NoteFX1_Control() {
  switch (lastPotRow) {
    case 0:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX1[NFX1presetNr].Pot_Value[MixerColumn] != Potentiometer[MixerColumn]) {
          NFX1[NFX1presetNr].Pot_Value[MixerColumn] = Potentiometer[MixerColumn];
          drawPotDrum(MixerColumn, lastPotRow, NFX1[NFX1presetNr].Pot_Value[MixerColumn], NFX1[NFX1presetNr].Pot_Value[MixerColumn], drumnote[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 1:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4] != Potentiometer[MixerColumn]) {
          NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4] = Potentiometer[MixerColumn];
          drawPotDrum(MixerColumn, lastPotRow, NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4], NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4], drumnote[MixerColumn + 4], trackColor[desired_instrument]);
        }
      }
      break;

    case 2:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8] != Potentiometer[MixerColumn]) {
          NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8] = Potentiometer[MixerColumn];
          drawPotDrum(MixerColumn, lastPotRow, NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8], NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8], drumnote[MixerColumn + 8], trackColor[desired_instrument]);
        }
      }
      break;
    case 3:
      break;
  }
}
void NoteFX1_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      NFX1presetNr = constrain((NFX1presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, NFX1presetNr, trackColor[desired_instrument]);
      NoteFX1_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX1[NFX1presetNr].Pot_Value[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX1[NFX1presetNr].Pot_Value[MixerColumn] + encoded[MixerColumn]), 0, BEAT_ARRAY_SIZE);
          }
        }
        break;

      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4] + encoded[MixerColumn]), 0, BEAT_ARRAY_SIZE);
          }
        }
        break;

      case 2:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8] + encoded[MixerColumn]), 0, BEAT_ARRAY_SIZE);
          }
        }
        break;

      case 3:
        break;
    }
  }
  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {
    readTouchinput();
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        saveNoteFX("NoteFX1", 0);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadNoteFX("NoteFX1", 0);
      }
    }
  }
}
void NoteFX1_Page_Static() {
  clearWorkSpace();
  NoteFX1_Change();
  drawNrInRect(18, 1, NFX1presetNr, ILI9341_PURPLE);

  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    drawPotDrum(MixerColumn, 0, NFX1[NFX1presetNr].Pot_Value[MixerColumn], NFX1[NFX1presetNr].Pot_Value[MixerColumn], drumnote[MixerColumn], trackColor[desired_instrument]);

    drawPotDrum(MixerColumn, 1, NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4], NFX1[NFX1presetNr].Pot_Value[MixerColumn + 4], drumnote[MixerColumn + 4], trackColor[desired_instrument]);

    drawPotDrum(MixerColumn, 2, NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8], NFX1[NFX1presetNr].Pot_Value[MixerColumn + 8], drumnote[MixerColumn + 8], trackColor[desired_instrument]);
  }
}
void NoteFX1_Change() {
}

void NoteFX2_Control() {
  switch (lastPotRow) {
    case 0:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX2[NFX2presetNr].Pot_Value[MixerColumn] != Potentiometer[MixerColumn]) {
          NFX2[NFX2presetNr].Pot_Value[MixerColumn] = Potentiometer[MixerColumn];
          NFX2[NFX2presetNr].Pot_Value[MixerColumn] = NFX2[NFX2presetNr].Pot_Value[MixerColumn];

          drawPot(MixerColumn, lastPotRow, NFX2[NFX2presetNr].Pot_Value[MixerColumn], NFX2[NFX2presetNr].Pot_Value[MixerColumn], NFX2_ROW1[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 1:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4] != Potentiometer[MixerColumn]) {
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4] = Potentiometer[MixerColumn];
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4];

          drawPot(MixerColumn, lastPotRow, NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4], NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4], noteNames[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 2:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8] != Potentiometer[MixerColumn]) {
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8] = Potentiometer[MixerColumn];
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8];

          drawPot(MixerColumn, lastPotRow, NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8], NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8], noteNames[MixerColumn + 4], trackColor[desired_instrument]);
        }
      }
      break;

    case 3:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12] != Potentiometer[MixerColumn]) {
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12] = Potentiometer[MixerColumn];
          NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12];

          drawPot(MixerColumn, lastPotRow, NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12], NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12], noteNames[MixerColumn + 8], trackColor[desired_instrument]);
        }
      }
      break;
  }
}
void NoteFX2_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      NFX2presetNr = constrain((NFX2presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, NFX2presetNr, trackColor[desired_instrument]);
      NoteFX2_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX2[NFX2presetNr].Pot_Value[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX2[NFX2presetNr].Pot_Value[MixerColumn] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 2:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 3:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
    }
  }
  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {
    readTouchinput();
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        saveNoteFX("NoteFX2", 1);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadNoteFX("NoteFX2", 1);
      }
    }
  }
}
void NoteFX2_Page_Static() {
  clearWorkSpace();
  NoteFX2_Change();
  drawNrInRect(18, 1, NFX2presetNr, ILI9341_PURPLE);

  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    drawPot(MixerColumn, 0, NFX2[NFX2presetNr].Pot_Value[MixerColumn], NFX2[NFX2presetNr].Pot_Value[MixerColumn], NFX2_ROW1[MixerColumn], trackColor[desired_instrument]);

    drawPot(MixerColumn, 1, NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4], NFX2[NFX2presetNr].Pot_Value[MixerColumn + 4], noteNames[MixerColumn], trackColor[desired_instrument]);
    drawPot(MixerColumn, 2, NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8], NFX2[NFX2presetNr].Pot_Value[MixerColumn + 8], noteNames[MixerColumn + 4], trackColor[desired_instrument]);

    drawPot(MixerColumn, 3, NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12], NFX2[NFX2presetNr].Pot_Value[MixerColumn + 12], noteNames[MixerColumn + 8], trackColor[desired_instrument]);
  }
}
void NoteFX2_Change() {
}

void NoteFX3_Control() {
  switch (lastPotRow) {
    case 0:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX3[NFX3presetNr].Pot_Value[MixerColumn] != Potentiometer[MixerColumn]) {
          NFX3[NFX3presetNr].Pot_Value[MixerColumn] = Potentiometer[MixerColumn];
          NFX3[NFX3presetNr].Pot_Value[MixerColumn] = NFX3[NFX3presetNr].Pot_Value[MixerColumn];

          drawPot(MixerColumn, lastPotRow, NFX3[NFX3presetNr].Pot_Value[MixerColumn], NFX3[NFX3presetNr].Pot_Value[MixerColumn], NFX3_ROW1[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 1:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4] != Potentiometer[MixerColumn]) {
          NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4] = Potentiometer[MixerColumn];
          NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4] = NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4];

          drawPot(MixerColumn, lastPotRow, NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4], NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 2:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8] != Potentiometer[MixerColumn]) {
          NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8] = Potentiometer[MixerColumn];
          NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8] = NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8];

          drawPot(MixerColumn, lastPotRow, NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8], NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;

    case 3:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

        if (NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12] != Potentiometer[MixerColumn]) {
          NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12] = Potentiometer[MixerColumn];
          NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12] = NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12];

          drawPot(MixerColumn, lastPotRow, NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12], NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
        }
      }
      break;
  }
}
void NoteFX3_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      NFX3presetNr = constrain((NFX3presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, NFX3presetNr, trackColor[desired_instrument]);
      NoteFX3_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX3[NFX3presetNr].Pot_Value[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX3[NFX3presetNr].Pot_Value[MixerColumn] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 2:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
      case 3:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12] + encoded[MixerColumn]), 0, 127);
          }
        }
        break;
    }
  }
  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {
    readTouchinput();
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        saveNoteFX("NoteFX3", 2);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadNoteFX("NoteFX3", 2);
      }
    }
  }
}
void NoteFX3_Page_Static() {
  clearWorkSpace();
  NoteFX3_Change();
  drawNrInRect(18, 1, NFX3presetNr, ILI9341_PURPLE);

  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    drawPot(MixerColumn, 0, NFX3[NFX3presetNr].Pot_Value[MixerColumn], NFX3[NFX3presetNr].Pot_Value[MixerColumn], NFX3_ROW1[MixerColumn], trackColor[desired_instrument]);
    drawPot(MixerColumn, 1, NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4], NFX3[NFX3presetNr].Pot_Value[MixerColumn + 4], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
    drawPot(MixerColumn, 2, NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8], NFX3[NFX3presetNr].Pot_Value[MixerColumn + 8], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
    drawPot(MixerColumn, 3, NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12], NFX3[NFX3presetNr].Pot_Value[MixerColumn + 12], NFX3_ROW2[MixerColumn], trackColor[desired_instrument]);
  }
}
void NoteFX3_Change() {
}

void NoteFX4_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
      NFX4presetNr = constrain((NFX4presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, NFX4presetNr, trackColor[desired_instrument]);
      NoteFX4_Page_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX4[NFX4presetNr].Pot_Value[MixerColumn];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn] + encoded[MixerColumn]), 0, NUM_STEPS);
            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn] + encoded[MixerColumn]), 0, NUM_STEPS - 1);
          }
        }
        break;

      case 1:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX4[NFX4presetNr].Pot_Value[MixerColumn + 4];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn + 4] + encoded[MixerColumn]), 0, NUM_STEPS);
            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn + 4] + encoded[MixerColumn]), 0, NUM_STEPS - 1);
          }
        }
        break;

      case 2:
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {

          Potentiometer[MixerColumn] = NFX4[NFX4presetNr].Pot_Value[MixerColumn + 8];
          if (enc_moved[MixerColumn]) {
            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn + 8] + encoded[MixerColumn]), 0, NUM_STEPS);
            Potentiometer[MixerColumn] = constrain((NFX4[NFX4presetNr].Pot_Value[MixerColumn + 8] + encoded[MixerColumn]), 0, NUM_STEPS - 1);
          }
        }
        break;

      case 3:
        break;
    }
  }
  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {
    readTouchinput();
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        saveNoteFX("NoteFX4", 3);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadNoteFX("NoteFX4", 3);
      }
    }
  }
}
void NoteFX4_Page_Static() {
  clearWorkSpace();
  NoteFX4_Change();
  drawNrInRect(18, 1, NFX4presetNr, ILI9341_PURPLE);
  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    drawPotDrum(MixerColumn, 0, NFX4[NFX4presetNr].Pot_Value[MixerColumn], NFX4[NFX4presetNr].Pot_Value[MixerColumn], drumnote[MixerColumn], trackColor[desired_instrument]);
    drawPotDrum(MixerColumn, 1, NFX4[NFX4presetNr].Pot_Value[MixerColumn + 4], NFX4[NFX4presetNr].Pot_Value[MixerColumn + 4], drumnote[MixerColumn + 4], trackColor[desired_instrument]);
    drawPotDrum(MixerColumn, 2, NFX4[NFX4presetNr].Pot_Value[MixerColumn + 8], NFX4[NFX4presetNr].Pot_Value[MixerColumn + 8], drumnote[MixerColumn + 8], trackColor[desired_instrument]);
  }
}
void NoteFX4_Change() {
}