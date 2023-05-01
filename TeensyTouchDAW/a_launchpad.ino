//this will probably hold some functions for external controllers
//needs alot of love
//also working on a class for implementing complex controllers

void LP_drawclipRow() {
  /*
  if (launchpad) {

    for (int LPclips = 0; LPclips < 8; LPclips++) {
      if (LP_grid_bool[LPclips]) {
        allTracks[desired_instrument]->clipToEdit = LPclips;
        clearStepsGrid();
        drawActivePolySteps();
        allTracks[desired_instrument]->drawClipToEdit();
      }
      midi01.sendNoteOn(LPclips, LP_RED_DIM, 1);
      midi01.sendNoteOn(allTracks[desired_instrument]->clipToEdit, LP_RED, 1);
    }
  }
  */
}

void LP_songmode(int note) {
  //launchpadcontrols
  if (launchpad) {
    //clipselecting via launchpad mini mk1

    if (seq_rec) {

      for (int instruments = 0; instruments < 8; instruments++) {
        for (int notes = 0; notes < 8; notes++) {


          if (note == notes + (instruments * 16)) {
            if (track[instruments].arrangment1[phraser] == notes) {
              track[instruments].arrangment1[phraser] = 8;
              track[instruments].lastclip = 8;
            } else {
              track[instruments].arrangment1[phraser] = notes;
              track[instruments].lastclip = notes;
            }
            drawarrengmentLine(songpages, instruments, phraser);
            for (int notes = 0; notes < 9; notes++) {
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

void LP_drawOctave(int LP_row) {
  for (int notes = 0; notes < 8; notes++) {
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
  for (int stepss = 0; stepss < 16; stepss++) {
    midi01.sendNoteOn(LP_step_notes[stepss], LP_GREEN_DIM, 1);
  }
}



void LP_melodicstep() {
  /*
  if (millis() % interval == 0) {
    if (LP_grid_bool[24]) {
      allTracks[desired_instrument]->shownOctaves--;
      clearStepsGrid();
      drawActivePolySteps();
    }
    if (LP_grid_bool[31]) {
      allTracks[desired_instrument]->shownOctaves++;
      clearStepsGrid();
      drawActivePolySteps();
    }
  }
  */


  if (millis() % interval == 0) {
    for (int notes = 0; notes < 12; notes++) {
      for (int steps = 0; steps < 16; steps++) {

        int touched_step = LP_step_bool[steps] * steps;
        byte touched_note = LP_octave_bool_keys[notes] * notes;
        int note = touched_note + allTracks[desired_instrument]->shownOctaves * 12;
        int notevalue_on_step = ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[touched_step * 6].voice[0];

        if (!LP_octave_bool_keys[notes]) {
          if (!LP_drawOnce[notes]) {
            LP_drawStepsequencer();
          }
          LP_drawOnce[notes] = true;
        }

        else if (LP_octave_bool_keys[notes]) {
          if (note == ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[steps * 6].voice[0]) {
            //Serial.println("hello");
            midi01.sendNoteOn(LP_step_notes[steps], LP_YELLOW, 1);
          }
          LP_drawOnce[notes] = false;

          if (LP_step_bool[steps]) {

            if (notevalue_on_step == VALUE_NOTEOFF) {
              for (int touched_ticks = 0; touched_ticks <= allTracks[desired_instrument]->stepLenght; touched_ticks++) {
                ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[touched_step + touched_ticks].voice[0] = note;
              }
              //clearStepsGridY(touched_step);
              // tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, trackColor[desired_instrument] + (allTracks[desired_instrument]->clipToEdit * 20));  //draw the active steps circles
              midi01.sendNoteOn(LP_step_notes[steps], LP_YELLOW, 1);
            } else if (notevalue_on_step > VALUE_NOTEOFF) {
              for (int touched_ticks = 0; touched_ticks <= allTracks[desired_instrument]->stepLenght; touched_ticks++) {
                ctrack[desired_instrument].sequence[allTracks[desired_instrument]->clipToEdit].tick[touched_step + touched_ticks].voice[0] = VALUE_NOTEOFF;
                //  tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, ILI9341_DARKGREY);  //draw the in-active steps circles
              }
              midi01.sendNoteOn(LP_step_notes[steps], LP_GREEN_DIM, 1);
            }
            //drawActivePolyStepsY(touched_step);
          }
        }
      }
    }
  }
}

void detect_and_assign_midi_devices() {
  if (launchpad != nullptr && (!launchpad || launchpad->idProduct() != MIDI_PRODUCTID_LAUNCHPAD || launchpad->idProduct() != MIDI_VENDORID_LAUNCHPAD)) {
    // our currently-assigned 'launchpad' device no longer refers to the launchpad - unset it
    launchpad = nullptr;
  }
  for (int i = 0; i < MAX_USB_DEVICES; i++) {
    if (usb_midi_devices[i] && usb_midi_devices[i]->idVendor() == MIDI_VENDORID_LAUNCHPAD && usb_midi_devices[i]->idProduct() == MIDI_PRODUCTID_LAUNCHPAD) {
      // detected launchpad on midi device with index 'i'!
      launchpad = usb_midi_devices[i];  // assign pointer to this device to the 'launchpad' variable
    }
  }
  if (millis() % 1000 == 0) {

    for (int i = 0; i < MAX_USB_DEVICES; i++) {
      const char *name = (const char *)usb_midi_devices[i]->product();
      //uint8_t name
      if (name != nullptr) {
        //Serial.print(i);
        //Serial.print("-");
        //Serial.println(name);
      } else {  //Serial.println("n.C.");
      }
    }
  }
}