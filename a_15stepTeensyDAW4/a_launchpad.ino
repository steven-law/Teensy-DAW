void LP_drawclipRow() {
  if (midi01.idVendor() == 4661) {

    for (byte LPclips = 0; LPclips < 8; LPclips++) {
      if (LP_grid_bool[LPclips]) {
        track[desired_instrument].clip_selector = LPclips;
        clearStepsGrid();
        if (selectPage == 0) {
          drawActiveDrumSteps();
        }
        if (selectPage > 0 && selectPage < 8) {
          drawActiveSteps();
        }
        drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
      }
      midi01.sendNoteOn(LPclips, LP_RED_DIM, 1);
      midi01.sendNoteOn(track[desired_instrument].clip_selector, LP_RED, 1);
    }
  }
}

void LP_songmode(byte note) {
  //launchpadcontrols
  if (midi01.idVendor() == 4661) {
    //clipselecting via launchpad mini mk1

    if (seq_rec) {
      
      for (byte instruments = 0; instruments < 8; instruments++) {
        for (byte notes = 0; notes < 8; notes++) {


          if (note == notes + (instruments * 16)) {
            if (track[instruments].arrangment1[phraser] == notes) {
              track[instruments].arrangment1[phraser] = 8;
              track[instruments].lastclip = 8;
            } else {
              track[instruments].arrangment1[phraser] = notes;
              track[instruments].lastclip = notes;
            }
            drawarrengmentLine(songpages, instruments, phraser);
            for (byte notes = 0; notes < 9; notes++) {
              midi01.sendNoteOff(notes + (instruments * 16), 0, 1);
            }
            if (track[instruments].arrangment1[phraser] < MAX_CLIPS) {
              midi01.sendNoteOn(track[instruments].arrangment1[phraser] + (instruments * 16), 60, 1);
            }
          }
        }
      }
    }
  }
}

void LP_drawOctave(byte LP_row) {
  for (byte notes = 0; notes < 8; notes++) {
    byte drawnote = notes + ((LP_row + 1) * 16);
    midi01.sendNoteOn(drawnote, LP_AMBER_DIM, 1);
  }
  midi01.sendNoteOn(1 + (LP_row * 16), LP_AMBER_DIM, 1);
  midi01.sendNoteOn(2 + (LP_row * 16), LP_AMBER_DIM, 1);
  midi01.sendNoteOn(4 + (LP_row * 16), LP_AMBER_DIM, 1);
  midi01.sendNoteOn(5 + (LP_row * 16), LP_AMBER_DIM, 1);
  midi01.sendNoteOn(6 + (LP_row * 16), LP_AMBER_DIM, 1);
}

void LP_drawStepsequencer() {
  for (byte stepss = 0; stepss < 16; stepss++) {
    midi01.sendNoteOn(LP_step_notes[stepss], LP_GREEN_DIM, 1);
  }
}

void LP_drumstep() {
  unsigned long currentMillis2 = millis();  //worse input haptic, better bpm drop when longpress (-2bpm)
  if (currentMillis2 - previousMillis2 >= interval) {
    previousMillis2 = currentMillis2;
    for (byte notes = 0; notes < 12; notes++) {
      for (byte steps = 0; steps < 16; steps++) {

        int dot_on_X = (steps)*STEP_FRAME_W + DOT_OFFSET_X;
        int dot_on_Y = (notes)*STEP_FRAME_H + DOT_OFFSET_Y;


        if (!LP_octave_bool[notes]) {  //if (function_to_find_out_if_button_is_held()) {
          if (!LP_drawOnce[notes]) {
            // control is held now, but it wasnt before -- clear screen
            LP_drawStepsequencer();
          }
          LP_drawOnce[notes] = true;
        }
        // control was released - do something if needed when control is released?


        else if (LP_octave_bool[notes]) {
          LP_drawOnce[notes] = false;
          //  if (LP_drawOnce) {
          //    LP_drawStepsequencer();
          //    LP_drawOnce = false;
          //  }
          if (channel1Clip[track[0].clip_selector][notes][steps]) {
            midi01.sendNoteOn(LP_step_notes[steps], LP_YELLOW, 1);
          }


          if (LP_step_bool[steps]) {
            if (!channel1Clip[track[0].clip_selector][notes][steps]) {
              channel1Clip[track[0].clip_selector][notes][steps] = true;
              tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, (trackColor[0] + (track[0].clip_selector) * 20));  //draw the active steps circles
              midi01.sendNoteOn(LP_step_notes[steps], LP_YELLOW, 1);
            } else if (channel1Clip[track[0].clip_selector][notes][steps]) {
              channel1Clip[track[0].clip_selector][notes][steps] = false;
              tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, ILI9341_DARKGREY);  //draw the inactive steps circles
              midi01.sendNoteOn(LP_step_notes[steps], LP_GREEN_DIM, 1);
            }
          }
        }
      }
    }
  }
}

void LP_melodicstep() {
  if (msecs % 200 == 0) {
    if (LP_grid_bool[24]) {
      track[desired_instrument].shown_octaves--;
      clearStepsGrid();
      drawOctaveNumber();
      drawActiveSteps();
    }
    if (LP_grid_bool[31]) {
      track[desired_instrument].shown_octaves++;
      clearStepsGrid();
      drawOctaveNumber();
      drawActiveSteps();
    }
  }

  unsigned long currentMillis2 = millis();  //worse input haptic, better bpm drop when longpress (-2bpm)
  if (currentMillis2 - previousMillis2 >= interval) {
    previousMillis2 = currentMillis2;

    for (byte notes = 0; notes < 12; notes++) {
      for (byte steps = 0; steps < 16; steps++) {


        int touched_step = LP_step_bool[steps] * steps;
        byte touched_note = LP_octave_bool_keys[notes] * notes;
        track[desired_instrument].tone = touched_note + track[desired_instrument].shown_octaves * 12;
        int dot_on_X = touched_step * STEP_FRAME_W + DOT_OFFSET_X;
        int dot_on_Y = touched_note * STEP_FRAME_H + DOT_OFFSET_Y;
        int notevalue_on_step = ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[touched_step];

        if (!LP_octave_bool_keys[notes]) {  //if (function_to_find_out_if_button_is_held()) {
          if (!LP_drawOnce[notes]) {
            // control is held now, but it wasnt before -- clear screen
            LP_drawStepsequencer();
          }
          LP_drawOnce[notes] = true;
        }
        // control was released - do something if needed when control is released?


        else if (LP_octave_bool_keys[notes]) {
          if (track[desired_instrument].tone == ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[steps]) {
            Serial.println("hello");

            midi01.sendNoteOn(LP_step_notes[steps], LP_YELLOW, 1);
          }
          LP_drawOnce[notes] = false;


          if (LP_step_bool[steps]) {

            if (notevalue_on_step == VALUE_NOTEOFF) {
              ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[touched_step] = track[desired_instrument].tone;
              clearStepsGridY(touched_step);
              tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));  //draw the active steps circles
              midi01.sendNoteOn(LP_step_notes[steps], LP_YELLOW, 1);
            } else if (notevalue_on_step > VALUE_NOTEOFF) {
              ctrack[desired_instrument].sequence[track[desired_instrument].clip_selector].step[touched_step] = VALUE_NOTEOFF;
              tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, ILI9341_DARKGREY);  //draw the in-active steps circles
              midi01.sendNoteOn(LP_step_notes[steps], LP_GREEN_DIM, 1);
            }
          }
        }
      }
    }
  }
}
