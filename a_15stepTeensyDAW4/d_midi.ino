///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                         SEQUENCER CALLBACKS                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////



void drawbarPosition() {
  for (int songPointerThickness = 0; songPointerThickness <= POSITION_POINTER_THICKNESS; songPointerThickness++) {
    //
    tft.drawPixel(phrase + STEP_FRAME_W * 2, (SONG_POSITION_POINTER_Y + songPointerThickness), ILI9341_GREEN);
    //
    tft.drawFastHLine((pixelphrase + 1) * phraseSegmentLength + STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y + songPointerThickness, phraseSegmentLength, ILI9341_GREEN);
    tft.drawFastHLine((pixelphrase)*phraseSegmentLength + STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y + songPointerThickness, phraseSegmentLength, ILI9341_DARKGREY);
  }
  if (phrase % 16 == 0) {
    pixelphrase = 0;
    tft.fillRect(STEP_FRAME_W * 15, GRID_POSITION_POINTER_Y, STEP_FRAME_W * 4, 4, ILI9341_DARKGREY);
    tft.fillRect(STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y, STEP_FRAME_W * 1, 4, ILI9341_GREEN);
  }
}

void drawstepPosition(byte current) {
  //draw the songpointer positions
  for (int songPointerThickness = 0; songPointerThickness <= POSITION_POINTER_THICKNESS; songPointerThickness++) {
    for (int stepwidth = 1; stepwidth <= 16; stepwidth++) {
      tft.drawFastHLine(current * stepwidth + STEP_FRAME_W * 2, STEP_POSITION_POINTER_Y + songPointerThickness, STEP_FRAME_W, ILI9341_GREEN);
      tft.drawFastHLine((current - 1) * stepwidth + STEP_FRAME_W * 2, STEP_POSITION_POINTER_Y + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);
    }
  }
}
void drawPhrasenumber() {
  //draw phrasenumber
  tft.fillRect(STEP_FRAME_W * POSITION_BAR_BUTTON + 1, 2, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 3, ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_9);
  tft.setCursor(STEP_FRAME_W * POSITION_BAR_BUTTON + 4, 3);
  tft.print(phrase + 1);
}
void sendClock() {
  if (seq_run) {
    //unsigned long now = micros();  // what's the time?
    // send clock
    //if (now >= _next_clock) {
    if (msecsclock > _clock) {
      //_next_clock = now + _clock;
      MIDItick++;
      noteOff_tick++;
      usbMIDI.sendRealTime(usbMIDI.Clock);
      MIDI.sendClock();
      msecsclock = 0;
      //digitalWrite(22, LOW);

      if (MIDItick % 6 == 0) {
        tick_16++;
        //digitalWrite(22, HIGH);
        noteOff_tick = 0;

        ////tft.updateScreen();
        step(tick_16);
        drawstepPosition(tick_16);
        //draw phrasenumber
        tft.fillRect(STEP_FRAME_W * POSITION_BAR_BUTTON + 1, 2, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 3, ILI9341_DARKGREY);
        tft.setTextColor(ILI9341_WHITE);
        tft.setFont(Arial_9);
        tft.setCursor(STEP_FRAME_W * POSITION_BAR_BUTTON + 4, 3);
        tft.print(phrase + 1);
      }
      if (tick_16 == 0) {
        beatComponents();
      }
      if (tick_16 == 15) {
        tick_16 = -1;
        phrase++;

        pixelphrase++;
        drawbarPosition();
      }
      //differnt things happening while the clock is running
      if (phrase == 255) {
        seq_run = false;
        //seq.stop();
        //seq.panic();
        phrase = -1;
        pixelphrase = -1;
        phrase = 0;
        msecs = 0;
        tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H * 14, STEP_FRAME_W * 16, STEP_FRAME_H, ILI9341_DARKGREY);
      }
      if (phrase == end_of_loop - 1) {
        phrase = start_of_loop;
        pixelphrase = 0;

        //tick_16 = -1;
        msecs = 0;
        tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H * 14, STEP_FRAME_W * 16, STEP_FRAME_H, ILI9341_DARKGREY);
      }
    }
  }
}

void setTempo(int tempo) {
  // midi clock messages should be sent 24 times
  // for every quarter note
  _clock = 60000000L / tempo / 24;

  tft.setCursor(STEP_FRAME_W * POSITION_BPM_BUTTON + 2, 3);
  tft.setFont(Arial_10);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  //if (msecs % 100 == 0) {
  tft.fillRect(STEP_FRAME_W * POSITION_BPM_BUTTON + 2, 1, STEP_FRAME_W * 2 - 4, STEP_FRAME_H - 2, ILI9341_DARKGREY);
  tft.print(tempo);
  // }
}


// called when the step position changes. both the current
// position and last are passed to the callback
void step(int current) {



  //send midinotes for drumtrack #1
  if (!track[0].solo_mutes_state) {
    if (!track[0].mute_state) {
      for (int i = 0; i < 12; i++) {
        if (channel1Clip[track[0].clip_songMode][i][current]) {
          if (!dsend_noteOff[i]) {
            drumnotes[i] = true;
            PluginPlayDrum();
            if (track[0].MIDIchannel < 17) {
              usbMIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
              MIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
              for (int usbs = 0; usbs < 10; usbs++) {
                if (!launchpad) {
                  usb_midi_devices[usbs]->sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                }
              }
            }
            dsend_noteOff[i] = true;
          }
        }
        if (channel1Clip[track[0].clip_songMode][i][current - 1]) {
          PluginPlayDrum();
          if (track[0].MIDIchannel < 17) {
            usbMIDI.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            MIDI.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            for (int usbs = 0; usbs < 10; usbs++) {
              if (!launchpad) {
                usb_midi_devices[usbs]->sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
              }
            }
          }
          dsend_noteOff[i] = false;
        }
      }
    }
  }

  //********************************************************************************
  //track 2-8 are intended to be (monophonic) melodic sequencer
  //in this file we let the 15step sequencer do all the midi and note trigering stuff


  // 5) so if you add a melodic plugin its best to add all the noteOn / Off functions here
  //    let the plugin only play when the midi channel for a track is set to this plugin
  //    do this with:
  //    if (track[track_number].MIDIchannel == Pluginnumber + 16) {}

  //    you can calculate the needed frequencys with this formula
  //    440 * pow(2.0, ((double)(ctrack[track_number].sequence[track[track_number].clip_songMode].step[current] - SAMPLE_ROOT) / 12.0))
  //    or use my note_frequency array
  //    current notes are stored in a struct with a "step" array
  //    call the frequency for your module with:
  //    "module".frequency(note_frequency[ctrack[track_number].sequence[track[track_number].clip_songMode].step[current]]);
  //    call the desired MIDINumber with:
  //    ctrack[track_number].sequence[track[track_number].clip_songMode].step[current]


  // if you want to change your parameters and you certainly will, head back to your plugin ino file to add graphics and controls.

  //send midinotes for melodic track #2 -8
  for (int track_number = 1; track_number <= 7; track_number++) {
    if (!track[track_number].solo_mutes_state) {
      if (!track[track_number].mute_state) {
        track[track_number].notePressed = true;
        track[track_number].notePlayed = ctrack[track_number].sequence[track[track_number].clip_songMode].step[current] + track[track_number].NoteOffset[phrase];

        if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[current] > VALUE_NOTEOFF) {
          if (track[track_number].MIDIchannel < 17) {
            track[track_number].send_noteOff = true;
            usbMIDI.sendNoteOn(track[track_number].notePlayed, track[track_number].MIDI_velocity, track[track_number].MIDIchannel);
            MIDI.sendNoteOn(track[track_number].notePlayed, track[track_number].MIDI_velocity, track[track_number].MIDIchannel);
            for (int usbs = 0; usbs < 10; usbs++) {
              if (!launchpad) {
                usb_midi_devices[usbs]->sendNoteOn(track[track_number].notePlayed, track[track_number].MIDI_velocity, track[track_number].MIDIchannel);
              }
            }
          }
          PluginPlay();
        }
        //if (track[track_number].send_noteOff) {
        if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[current - 1] > VALUE_NOTEOFF) {
          track[track_number].notePressed = false;

          if (track[track_number].MIDIchannel < 17) {
            usbMIDI.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[current - 1] + track[track_number].NoteOffset[phrase], VELOCITYOFF, track[track_number].MIDIchannel);
            MIDI.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[current - 1] + track[track_number].NoteOffset[phrase], VELOCITYOFF, track[track_number].MIDIchannel);
            for (int usbs = 0; usbs < 10; usbs++) {
              if (!launchpad) {
                usb_midi_devices[usbs]->sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[current - 1] + track[track_number].NoteOffset[phrase], VELOCITYOFF, track[track_number].MIDIchannel);
              }
            }
          }
          PluginPlay();
          track[track_number].send_noteOff = false;
          //}
        }
      }
    }
  }
  for (int songPointerThickness = 0; songPointerThickness <= POSITION_POINTER_THICKNESS; songPointerThickness++) {
    if (current == 0) {
      tft.drawFastHLine(STEP_FRAME_W * 17, STEP_POSITION_POINTER_Y + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);
    }
  }
}


void midiCC_view_Static(byte mixerpage, byte desired_instrument) {
  clearWorkSpace();


  for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
    drawPotCC(MixerColumnPos, CTRL_ROW_0, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], trackColor[desired_instrument]);
    drawNrInRect(MixerColumnPos, CTRL_ROW_0 + 1, track[desired_instrument].midicc_number_row_1[MixerColumn], trackColor[desired_instrument]);

    drawPotCC(MixerColumnPos, CTRL_ROW_1, track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], trackColor[desired_instrument]);
    drawNrInRect(MixerColumnPos, CTRL_ROW_1 + 1, track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);

    drawPotCC(MixerColumnPos, CTRL_ROW_2, track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], trackColor[desired_instrument]);
    drawNrInRect(MixerColumnPos, CTRL_ROW_2 + 1, track[desired_instrument].midicc_number_row_3[MixerColumn], trackColor[desired_instrument]);

    drawPotCC(MixerColumnPos, CTRL_ROW_3, track[desired_instrument].midicc_value_row_4[MixerColumn], track[desired_instrument].midicc_value_row_4[MixerColumn], trackColor[desired_instrument]);
    drawNrInRect(MixerColumnPos, CTRL_ROW_3 + 1, track[desired_instrument].midicc_number_row_4[MixerColumn], trackColor[desired_instrument]);
  }
}

void midiCCpage1_Dynamic(byte desired_instrument) {
  switch (lastPotRow) {
    case 0:
      //if (msecs % 20 == 0) {
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (!button[14]) {
          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_value_row_1[MixerColumn] = constrain((track[desired_instrument].midicc_value_row_1[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawPotCC(MixerColumnPos, CTRL_ROW_0, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], trackColor[desired_instrument]);
            usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].MIDIchannel);
            MIDI.sendControlChange(track[desired_instrument].midicc_number_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].MIDIchannel);
          }

          /*if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_value_row_1[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_value_row_1[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_value_row_1[MixerColumn] = Potentiometer[MixerColumn];
              drawPotCC(MixerColumnPos, CTRL_ROW_0, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], trackColor[desired_instrument]);
              usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].MIDIchannel);
            }
          }*/
        }
        if (button[14]) {
          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_number_row_1[MixerColumn] = constrain((track[desired_instrument].midicc_number_row_1[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawNrInRect(MixerColumnPos, CTRL_ROW_0 + 1, track[desired_instrument].midicc_number_row_1[MixerColumn], trackColor[desired_instrument]);
          }

          /* if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_number_row_1[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_number_row_1[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_number_row_1[MixerColumn] = Potentiometer[MixerColumn];
              drawNrInRect(MixerColumnPos, CTRL_ROW_0 + 1, track[desired_instrument].midicc_number_row_1[MixerColumn], trackColor[desired_instrument]);
            }
          }*/
        }
      }

      break;
    case 1:

      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (!button[14]) {

          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_value_row_2[MixerColumn] = constrain((track[desired_instrument].midicc_value_row_2[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawPotCC(MixerColumnPos, CTRL_ROW_1, track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], trackColor[desired_instrument]);
            usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].MIDIchannel);
          }

          /* if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_value_row_2[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_value_row_2[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_value_row_2[MixerColumn] = Potentiometer[MixerColumn];
              drawPotCC(MixerColumnPos, CTRL_ROW_1, track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], trackColor[desired_instrument]);
              usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].MIDIchannel);
            }
          }*/
        }
        if (button[14]) {
          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_number_row_2[MixerColumn] = constrain((track[desired_instrument].midicc_number_row_2[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawNrInRect(MixerColumnPos, CTRL_ROW_1 + 1, track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);
          }
          /* if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_number_row_2[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_number_row_2[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_number_row_2[MixerColumn] = Potentiometer[MixerColumn];
              drawNrInRect(MixerColumnPos, CTRL_ROW_1 + 1, track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);
            }
          }*/
        }
      }

      break;
    case 2:

      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (!button[14]) {

          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_value_row_3[MixerColumn] = constrain((track[desired_instrument].midicc_value_row_3[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawPotCC(MixerColumnPos, CTRL_ROW_2, track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], trackColor[desired_instrument]);
            usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].MIDIchannel);
          }


          /* if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_value_row_3[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_value_row_3[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_value_row_3[MixerColumn] = Potentiometer[MixerColumn];
              drawPotCC(MixerColumnPos, CTRL_ROW_2, track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], trackColor[desired_instrument]);
              usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].MIDIchannel);
            }
          }*/
        }
        if (button[14]) {
          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_number_row_3[MixerColumn] = constrain((track[desired_instrument].midicc_number_row_3[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawNrInRect(MixerColumnPos, CTRL_ROW_2 + 1, track[desired_instrument].midicc_number_row_3[MixerColumn], trackColor[desired_instrument]);
          }
          /* if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_number_row_2[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_number_row_2[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_number_row_2[MixerColumn] = Potentiometer[MixerColumn];
              drawNrInRect(MixerColumnPos, CTRL_ROW_2 + 1, track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);
            }
          }*/
        }
      }
      // }

      break;
    case 3:
      // if (msecs % 20 == 0) {
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (!button[14]) {

          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_value_row_4[MixerColumn] = constrain((track[desired_instrument].midicc_value_row_4[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawPotCC(MixerColumnPos, CTRL_ROW_3, track[desired_instrument].midicc_value_row_4[MixerColumn], track[desired_instrument].midicc_value_row_4[MixerColumn], trackColor[desired_instrument]);
            usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_4[MixerColumn], track[desired_instrument].midicc_value_row_4[MixerColumn], track[desired_instrument].MIDIchannel);
          }


          /* if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_value_row_4[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_value_row_4[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_value_row_4[MixerColumn] = Potentiometer[MixerColumn];
              drawPotCC(MixerColumnPos, CTRL_ROW_3, track[desired_instrument].midicc_value_row_4[MixerColumn], track[desired_instrument].midicc_value_row_4[MixerColumn], trackColor[desired_instrument]);
              usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_4[MixerColumn], track[desired_instrument].midicc_value_row_4[MixerColumn], track[desired_instrument].MIDIchannel);
            }
          }*/
        }
        if (button[14]) {

          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_number_row_4[MixerColumn] = constrain((track[desired_instrument].midicc_number_row_4[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawNrInRect(MixerColumnPos, CTRL_ROW_3 + 1, track[desired_instrument].midicc_number_row_4[MixerColumn], trackColor[desired_instrument]);
          }

          /*if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_number_row_2[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_number_row_2[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_number_row_2[MixerColumn] = Potentiometer[MixerColumn];
              drawNrInRect(MixerColumnPos, CTRL_ROW_3 + 1, track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);
            }
          }*/
        }
      }


      break;
  }
  if (ts.touched() || button[15]) {

    if (gridTouchY == 2 || gridTouchY == 3) {
      lastPotRow = 0;
    }

    if (gridTouchY == 5 || gridTouchY == 6) {
      lastPotRow = 1;
    }

    if (gridTouchY == 8 || gridTouchY == 9) {
      lastPotRow = 2;
    }
    if (gridTouchY == 11 || gridTouchY == 12) {
      lastPotRow = 3;
    }
  }
}



void myClock() {
  MIDItick++;
  usbMIDI.sendRealTime(usbMIDI.Clock);
  msecs = 0;
  if (MIDItick % 6 == 0) {
    tick_16++;
    step(tick_16);
    drawstepPosition(tick_16);
    drawPhrasenumber();
  }

  Serial.println("Clock");
}

void myStart() {
  seq_run = true;
  msecs = 0;
  for (byte i = 1; i <= 7; i++) {
    track[i].clip_songMode = track[i].arrangment1[0];
  }
  Serial.println("Start");
}
void myStop() {
  seq_run = false;
  tick_16 = -1;
  phrase = -1;
  pixelphrase = -1;
  phrase = 0;
  msecs = 0;
  tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H * 14, STEP_FRAME_W * 16, STEP_FRAME_H, ILI9341_DARKGREY);

  Serial.println("Stop");
}

void myNoteOn(byte channel, byte note, byte velocity) {

  if (launchpad) {

    for (byte songpages = 0; songpages < 16; songpages++) {
      if (selectPage == SONGMODE_PAGE_1 + songpages) {
        if (msecs % 100 == 0) {
          LP_songmode(note);
        }
      }
    }
    for (byte gridNotes = 0; gridNotes < 64; gridNotes++) {
      if (note == LP_grid_notes[gridNotes]) {
        LP_grid_bool[gridNotes] = true;
      }
    }


    if (desired_instrument == 0) {
      for (byte octNotes = 0; octNotes < 12; octNotes++) {
        if (note == LP_octave_notes[octNotes]) {
          LP_octave_bool[octNotes] = true;
          drumnotes[octNotes] = true;
        }
      }
    }
    for (int trackss = 1; trackss < 8; trackss++) {
      if (desired_instrument == trackss) {
        for (byte octNotes = 0; octNotes < 12; octNotes++) {
          if (note == LP_octave_notes_keys[octNotes]) {
            channelPlayed = desired_instrument + 1;
            channel = desired_instrument + 1;
            LP_octave_bool_keys[octNotes] = true;
            track[desired_instrument].notePressed = true;
            track[desired_instrument].notePlayed = octNotes + (track[desired_instrument].shown_octaves * 12);
          }
        }
      }
    }
    for (byte stepss = 0; stepss < 16; stepss++) {
      if (note == LP_step_notes[stepss]) {
        LP_step_bool[stepss] = true;
      }
    }


    // hold for track button
    if (!button[10] && note == 8) {  //"E"  69
      button[8] = true;
    }
    // hold for plugin button
    if (!button[10] && note == 24) {  //"C"  67
      button[9] = true;
    }
    //  hold for Songarranger button
    if (note == 40) {  //"A"  65
      button[10] = true;
    }
    // hold for Mixer button
    if (!button[10] && note == 56) {  //"4"  52
      button[11] = true;
    }
    // hold for FX button
    if (!button[10] && note == 72) {  //"8"  56
      button[12] = true;
    }
    //  hold for recorder button
    if (!button[10] && note == 88) {  //"A"  65
      button[13] = true;
      selectPage = RECORDER_PAGE;
      recorder_Page_Static();
    }
    // hold for shift button
    if (!button[10] && note == 104) {
      button[14] = true;
    }
    // hold for enter button
    if (!button[10] && note == 120) {
      button[15] = true;
    }
  } else if (channel == 1) {
    LP_octave_bool[note - 60] = true;
    for (int files = 0; files < 12; files++) {
      if (note == (files + 60) || LP_octave_bool[files]) {
        drumnotes[files] = true;
      }
    }
  } else {
    LP_octave_bool_keys[0] = true;
    track[channel - 1].notePressed = true;
    track[channel - 1].notePlayed = note;
  }

  // When a USB device with multiple virtual cables is used,
  // midi1.getCable() can be used to read which of the virtual
  // MIDI cables received this message.

  if (seq_rec) {
    ctrack[channel - 1].sequence[track[channel - 1].clip_selector].step[tick_16] = note;
  }
  //send midinotes for drumtrack




  PluginPlay();
}
void myNoteOff(byte channel, byte note, byte velocity) {
  if (launchpad) {

    for (byte gridNotes = 0; gridNotes < 64; gridNotes++) {
      if (note == LP_grid_notes[gridNotes]) {
        LP_grid_bool[gridNotes] = false;
      }
    }

    if (desired_instrument == 0) {
      for (byte octNotes = 0; octNotes < 12; octNotes++) {
        if (note == LP_octave_notes[octNotes]) {
          LP_octave_bool[octNotes] = false;
        }
      }
    }
    for (int trackss = 1; trackss < 8; trackss++) {
      if (desired_instrument == trackss) {
        for (byte octNotes = 0; octNotes < 12; octNotes++) {
          if (note == LP_octave_notes_keys[octNotes]) {
            channel = desired_instrument + 1;
            LP_octave_bool_keys[octNotes] = false;
            track[desired_instrument].notePressed = false;
            track[desired_instrument].notePlayed = octNotes + (track[desired_instrument].shown_octaves * 12);
          }
        }
      }
    }
    for (byte stepss = 0; stepss < 16; stepss++) {
      if (note == LP_step_notes[stepss]) {
        LP_step_bool[stepss] = false;
      }
    }

    // hold for track button
    if (!button[10] && note == 8) {  //"E"  69
      button[8] = false;
    }
    // hold for plugin button
    if (!button[10] && note == 24) {  //"C"  67
      button[9] = false;
    }
    // hold for Mixer button
    if (note == 40) {  //"4"  52
      button[10] = false;
    }
    // hold for Mixer button
    if (!button[10] && note == 56) {  //"4"  52
      button[11] = false;
    }

    // hold for FX button
    if (!button[10] && note == 72) {  //"8"  56
      button[12] = false;
    }
    // hold for recorder button
    if (!button[10] && note == 88) {
      button[13] = false;
    }
    // hold for shift button
    if (!button[10] && note == 104) {
      button[14] = false;
    }
    // hold for enter button
    if (!button[10] && note == 120) {
      button[15] = false;
    }
  } else if (channel == 1) {
    LP_octave_bool[note - 60] = false;
    for (int files = 0; files < 12; files++) {
      if (note == (files + 60) && !LP_octave_bool[files]) {
        drumnotes[files] = false;
      }
    }
  } else {
    LP_octave_bool_keys[0] = false;

    track[channel - 1].notePressed = false;
    track[channel - 1].notePlayed = note;
  }




  PluginPlay();
}
void myControlChange(byte channel, byte control, byte value) {
  if (control == 3) {
    Potentiometer[0] = value;
  }
  if (control == 9) {
    Potentiometer[1] = value;
  }
  if (control == 14) {
    Potentiometer[2] = value;
  }
  if (control == 15) {
    Potentiometer[3] = value;
  }

  if (selectPage == PLUGIN2_PAGE1) {
    switch (lastPotRow) {
      case 0:
        for (byte touchX = 1; touchX < 5; touchX++) {
          if (abs(Potentiometer[touchX - 1] - pl2[pl2presetNr].Vol_rnd[touchX - 1]) < POTPICKUP) {
            if (pl2[pl2presetNr].Vol_rnd[touchX - 1] != Potentiometer[touchX - 1]) {
              drawPot(touchX * 4 - 1, CTRL_ROW_0, pl2[pl2presetNr].Vol_rnd[touchX - 1], pl2[pl2presetNr].Vol_rnd[touchX - 1], showVOL[touchX - 1], trackColor[desired_instrument]);
              pl2[pl2presetNr].Vol_rnd[touchX - 1] = Potentiometer[touchX - 1];
              pl2[pl2presetNr].Vol[touchX - 1] = pl2[pl2presetNr].Vol_rnd[touchX - 1] / 127.00;
              drummixer1.gain(touchX - 1, pl2[pl2presetNr].Vol[touchX - 1]);
            }
          }
        }
        break;
      case 1:
        for (byte touchX = 1; touchX < 5; touchX++) {
          if (abs(Potentiometer[touchX - 1] - pl2[pl2presetNr].Vol_rnd[touchX + 3]) < POTPICKUP) {
            if (pl2[pl2presetNr].Vol_rnd[touchX + 3] != Potentiometer[touchX - 1]) {
              drawPot(touchX * 4 - 1, CTRL_ROW_1, pl2[pl2presetNr].Vol_rnd[touchX + 3], pl2[pl2presetNr].Vol_rnd[touchX + 3], showVOL[touchX + 3], trackColor[desired_instrument]);
              pl2[pl2presetNr].Vol_rnd[touchX + 3] = Potentiometer[touchX - 1];
              pl2[pl2presetNr].Vol[touchX + 3] = pl2[pl2presetNr].Vol_rnd[touchX + 3] / 127.00;
              drummixer2.gain(touchX - 1, pl2[pl2presetNr].Vol[touchX + 3]);
            }
          }
        }
        break;
      case 2:
        for (byte touchX = 1; touchX < 5; touchX++) {
          if (abs(Potentiometer[touchX - 1] - pl2[pl2presetNr].Vol_rnd[touchX + 7]) < POTPICKUP) {
            if (pl2[pl2presetNr].Vol_rnd[touchX + 7] != Potentiometer[touchX - 1]) {
              drawPot(touchX * 4 - 1, CTRL_ROW_2, pl2[pl2presetNr].Vol_rnd[touchX + 7], pl2[pl2presetNr].Vol_rnd[touchX + 7], showVOL[touchX + 7], trackColor[desired_instrument]);
              pl2[pl2presetNr].Vol_rnd[touchX + 7] = Potentiometer[touchX - 1];
              pl2[pl2presetNr].Vol[touchX + 7] = pl2[pl2presetNr].Vol_rnd[touchX + 7] / 127.00;
              drummixer3.gain(touchX - 1, pl2[pl2presetNr].Vol[touchX + 7]);
            }
          }
        }
        break;
    }
  }
  if (selectPage == PLUGIN3_PAGE1) {
    switch (lastPotRow) {
      case 0:
        if (abs(Potentiometer[0] - pl3[pl3presetNr].wfSelect_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl3[pl3presetNr].wfSelect_graph != Potentiometer[0]) {
            pl3[pl3presetNr].wfSelect_graph = Potentiometer[0];
            pl3[pl3presetNr].wfSelect = map(pl3[pl3presetNr].wfSelect_graph, 0, 127, 0, 12);
            pl3waveform1.begin(pl3[pl3presetNr].wfSelect);
            drawPot(CTRL_COL_0, CTRL_ROW_0, pl3[pl3presetNr].wfSelect_graph, pl3[pl3presetNr].wfSelect, "WForm", trackColor[desired_track]);
          }
        }
        break;
      case 1:
        if (abs(Potentiometer[0] - pl3[pl3presetNr].Filter1_Frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl3[pl3presetNr].Filter1_Frequency_graph != Potentiometer[0]) {
            pl3[pl3presetNr].Filter1_Frequency_graph = Potentiometer[0];
            pl3[pl3presetNr].Filter1_Frequency = note_frequency[pl3[pl3presetNr].Filter1_Frequency_graph];
            pl3filter1.frequency(pl3[pl3presetNr].Filter1_Frequency);
            drawPot(CTRL_COL_0, CTRL_ROW_1, pl3[pl3presetNr].Filter1_Frequency_graph, pl3[pl3presetNr].Filter1_Frequency, "Freq", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[1] - pl3[pl3presetNr].Filter1_Resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl3[pl3presetNr].Filter1_Resonance_graph != Potentiometer[1]) {
            pl3[pl3presetNr].Filter1_Resonance_graph = Potentiometer[1];
            pl3[pl3presetNr].Filter1_Resonance = pl3[pl3presetNr].Filter1_Resonance_graph / 25.40;
            pl3filter1.resonance(pl3[pl3presetNr].Filter1_Resonance);
            drawPot_2(CTRL_COL_1, CTRL_ROW_1, pl3[pl3presetNr].Filter1_Resonance_graph, pl3[pl3presetNr].Filter1_Resonance_graph, "Reso", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[2] - pl3[pl3presetNr].Filter1_Sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl3[pl3presetNr].Filter1_Sweep_graph != Potentiometer[2]) {
            pl3[pl3presetNr].Filter1_Sweep_graph = Potentiometer[2];
            pl3[pl3presetNr].Filter1_Sweep = pl3[pl3presetNr].Filter1_Sweep_graph / 18.14;
            pl3filter1.octaveControl(pl3[pl3presetNr].Filter1_Sweep);
            drawPot_3(CTRL_COL_2, CTRL_ROW_1, pl3[pl3presetNr].Filter1_Sweep_graph, pl3[pl3presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[3] - pl3[pl3presetNr].Filter1_Type_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl3[pl3presetNr].Filter1_Type_graph != Potentiometer[3]) {
            pl3[pl3presetNr].Filter1_Type_graph = Potentiometer[3];
            pl3[pl3presetNr].Filter1_Type = pl3[pl3presetNr].Filter1_Type_graph / 43;
            selectFilterType(19, pl3[pl3presetNr].Filter1_Type);
            drawPot_4(CTRL_COL_3, CTRL_ROW_1, pl3[pl3presetNr].Filter1_Type_graph, pl3[pl3presetNr].Filter1_Type, "", trackColor[desired_track]);
            drawChar(CTRL_COL_3, 7, filterType[pl3[pl3presetNr].Filter1_Type], ILI9341_WHITE);
          }
        }
        break;
      case 2:
        if (abs(Potentiometer[0] - pl3[pl3presetNr].Env1_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl3[pl3presetNr].Env1_Attack_graph != Potentiometer[0]) {
            pl3[pl3presetNr].Env1_Attack_graph = Potentiometer[0];
            pl3[pl3presetNr].Env1_Attack = map(pl3[pl3presetNr].Env1_Attack_graph, 0, 127, 10, 700);
            pl3envelope1.attack(pl3[pl3presetNr].Env1_Attack);
            pl3envelope2.attack(pl3[pl3presetNr].Env1_Attack);
            drawPot(CTRL_COL_0, CTRL_ROW_2, pl3[pl3presetNr].Env1_Attack_graph, pl3[pl3presetNr].Env1_Attack, "Atck", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[1] - pl3[pl3presetNr].Env1_Decay_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl3[pl3presetNr].Env1_Decay_graph != Potentiometer[1]) {
            pl3[pl3presetNr].Env1_Decay_graph = Potentiometer[1];
            pl3[pl3presetNr].Env1_Decay = map(pl3[pl3presetNr].Env1_Decay_graph, 0, 127, 10, 700);
            pl3envelope1.decay(pl3[pl3presetNr].Env1_Decay);
            pl3envelope2.decay(pl3[pl3presetNr].Env1_Decay);
            drawPot_2(CTRL_COL_1, CTRL_ROW_2, pl3[pl3presetNr].Env1_Decay_graph, pl3[pl3presetNr].Env1_Decay, "Dec", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[2] - pl3[pl3presetNr].Env1_Sustain_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl3[pl3presetNr].Env1_Sustain_graph != Potentiometer[2]) {
            pl3[pl3presetNr].Env1_Sustain_graph = Potentiometer[2];
            pl3[pl3presetNr].Env1_Sustain = pl3[pl3presetNr].Env1_Sustain_graph / 127.00;
            pl3envelope1.sustain(pl3[pl3presetNr].Env1_Sustain);
            pl3envelope2.sustain(pl3[pl3presetNr].Env1_Sustain);
            drawPot_3(CTRL_COL_2, CTRL_ROW_2, pl3[pl3presetNr].Env1_Sustain_graph, pl3[pl3presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[3] - pl3[pl3presetNr].Env1_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl3[pl3presetNr].Env1_Release_graph != Potentiometer[3]) {
            pl3[pl3presetNr].Env1_Release_graph = Potentiometer[3];
            pl3[pl3presetNr].Env1_Release = map(pl3[pl3presetNr].Env1_Release_graph, 0, 127, 180, 1200);
            pl3envelope1.release(pl3[pl3presetNr].Env1_Release);
            pl3envelope2.release(pl3[pl3presetNr].Env1_Release);
            drawPot_4(CTRL_COL_3, CTRL_ROW_2, pl3[pl3presetNr].Env1_Release_graph, pl3[pl3presetNr].Env1_Release, "Rel", trackColor[desired_track]);
          }
        }
        break;
    }
  }
  if (selectPage == PLUGIN4_PAGE1) {
    switch (lastPotRow) {
      case 0:
        for (byte touchX = 1; touchX < 5; touchX++) {
          if (abs(Potentiometer[touchX - 1] - pl4[pl4presetNr].Vol_rnd[touchX - 1]) < POTPICKUP) {
            if (pl4[pl4presetNr].Vol_rnd[touchX - 1] != Potentiometer[touchX - 1]) {
              drawPot(touchX * 4 - 1, CTRL_ROW_0, pl4[pl4presetNr].Vol_rnd[touchX - 1], pl4[pl4presetNr].Vol_rnd[touchX - 1], showVOL[touchX - 1], trackColor[desired_instrument]);
              pl4[pl4presetNr].Vol_rnd[touchX - 1] = Potentiometer[touchX - 1];
              pl4[pl4presetNr].Vol[touchX - 1] = pl4[pl4presetNr].Vol_rnd[touchX - 1] / 127.00;
              drummixer1.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX - 1]);
            }
          }
        }
        break;
      case 1:
        for (byte touchX = 1; touchX < 5; touchX++) {
          if (abs(Potentiometer[touchX - 1] - pl4[pl4presetNr].Vol_rnd[touchX + 3]) < POTPICKUP) {
            if (pl4[pl4presetNr].Vol_rnd[touchX + 3] != Potentiometer[touchX - 1]) {
              drawPot(touchX * 4 - 1, CTRL_ROW_1, pl4[pl4presetNr].Vol_rnd[touchX + 3], pl4[pl4presetNr].Vol_rnd[touchX + 3], showVOL[touchX + 3], trackColor[desired_instrument]);
              pl4[pl4presetNr].Vol_rnd[touchX + 3] = Potentiometer[touchX - 1];
              pl4[pl4presetNr].Vol[touchX + 3] = pl4[pl4presetNr].Vol_rnd[touchX + 3] / 127.00;
              drummixer2.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX + 3]);
            }
          }
        }
        break;
      case 2:
        for (byte touchX = 1; touchX < 5; touchX++) {
          if (abs(Potentiometer[touchX - 1] - pl4[pl4presetNr].Vol_rnd[touchX + 7]) < POTPICKUP) {
            if (pl4[pl4presetNr].Vol_rnd[touchX + 7] != Potentiometer[touchX - 1]) {
              drawPot(touchX * 4 - 1, CTRL_ROW_2, pl4[pl4presetNr].Vol_rnd[touchX + 7], pl4[pl4presetNr].Vol_rnd[touchX + 7], showVOL[touchX + 7], trackColor[desired_instrument]);
              pl4[pl4presetNr].Vol_rnd[touchX + 7] = Potentiometer[touchX - 1];
              pl4[pl4presetNr].Vol[touchX + 7] = pl4[pl4presetNr].Vol_rnd[touchX + 7] / 127.00;
              drummixer3.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX + 7]);
            }
          }
        }
        break;
    }
  }
  if (selectPage == PLUGIN5_PAGE1) {
    switch (lastPotRow) {
      case 0:
        if (abs(Potentiometer[0] - pl5[pl5presetNr].selected_file_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl5[pl5presetNr].selected_file_graph != Potentiometer[0]) {
            pl5[pl5presetNr].selected_file_graph = Potentiometer[0];
            pl5[pl5presetNr].selected_file = map(pl5[pl5presetNr].selected_file_graph, 0, 127, 0, MAX_RAW_FILES);
            drawPot(CTRL_COL_0, CTRL_ROW_0, pl5[pl5presetNr].selected_file_graph, pl5[pl5presetNr].selected_file, "RAW", trackColor[desired_instrument]);
            pl5enter_was_pushed = false;
            drawActiveRect(CTRL_COL_1, 2, 2, 2, pl5enter_was_pushed, "LOAD", ILI9341_GREEN);
          }
        }
        break;
      case 1:
        if (abs(Potentiometer[0] - pl5[pl5presetNr].Filter1_Frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl5[pl5presetNr].Filter1_Frequency_graph != Potentiometer[0]) {
            pl5[pl5presetNr].Filter1_Frequency_graph = Potentiometer[0];
            pl5[pl5presetNr].Filter1_Frequency = note_frequency[pl5[pl5presetNr].Filter1_Frequency_graph];
            pl5filter1.frequency(pl5[pl5presetNr].Filter1_Frequency);
            drawPot(CTRL_COL_0, CTRL_ROW_1, pl5[pl5presetNr].Filter1_Frequency_graph, pl5[pl5presetNr].Filter1_Frequency, "Freq", trackColor[desired_instrument]);
          }
        }
        if (abs(Potentiometer[1] - pl5[pl5presetNr].Filter1_Resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl5[pl5presetNr].Filter1_Resonance_graph != Potentiometer[1]) {
            pl5[pl5presetNr].Filter1_Resonance_graph = Potentiometer[1];
            pl5[pl5presetNr].Filter1_Resonance = pl5[pl5presetNr].Filter1_Resonance_graph / 25.40;
            pl5filter1.resonance(pl5[pl5presetNr].Filter1_Resonance);
            drawPot_2(CTRL_COL_1, CTRL_ROW_1, pl5[pl5presetNr].Filter1_Resonance_graph, pl5[pl5presetNr].Filter1_Resonance_graph, "Reso", trackColor[desired_instrument]);
          }
        }
        if (abs(Potentiometer[2] - pl5[pl5presetNr].Filter1_Sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl5[pl5presetNr].Filter1_Sweep_graph != Potentiometer[2]) {
            pl5[pl5presetNr].Filter1_Sweep_graph = Potentiometer[2];
            pl5[pl5presetNr].Filter1_Sweep = pl5[pl5presetNr].Filter1_Sweep_graph / 18.14;
            pl5filter1.octaveControl(pl5[pl5presetNr].Filter1_Sweep);
            drawPot_3(CTRL_COL_2, CTRL_ROW_1, pl5[pl5presetNr].Filter1_Sweep_graph, pl5[pl5presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_instrument]);
          }
        }

        if (abs(Potentiometer[3] - pl5[pl5presetNr].Filter1_Type_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl5[pl5presetNr].Filter1_Type_graph != Potentiometer[3]) {
            pl5[pl5presetNr].Filter1_Type_graph = Potentiometer[3];
            pl5[pl5presetNr].Filter1_Type = pl5[pl5presetNr].Filter1_Type_graph / 43;
            selectFilterType(21, pl5[pl5presetNr].Filter1_Type);
            drawPot_4(CTRL_COL_3, CTRL_ROW_1, pl5[pl5presetNr].Filter1_Type_graph, pl5[pl5presetNr].Filter1_Type, "", trackColor[desired_track]);
            drawChar(CTRL_COL_3, 7, filterType[pl5[pl5presetNr].Filter1_Type], ILI9341_WHITE);
          }
        }
        break;
      case 2:
        if (abs(Potentiometer[0] - pl5[pl5presetNr].Env1_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl5[pl5presetNr].Env1_Attack_graph != Potentiometer[0]) {
            pl5[pl5presetNr].Env1_Attack_graph = Potentiometer[0];
            pl5[pl5presetNr].Env1_Attack = map(pl5[pl5presetNr].Env1_Attack_graph, 0, 127, 10, 700);
            pl5envelope1.attack(pl5[pl5presetNr].Env1_Attack);
            pl5envelope2.attack(pl5[pl5presetNr].Env1_Attack);
            drawPot(3, CTRL_ROW_2, pl5[pl5presetNr].Env1_Attack_graph, pl5[pl5presetNr].Env1_Attack, "Atck", trackColor[desired_instrument]);
          }
        }
        if (abs(Potentiometer[1] - pl5[pl5presetNr].Env1_Decay_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl5[pl5presetNr].Env1_Decay_graph != Potentiometer[1]) {
            pl5[pl5presetNr].Env1_Decay_graph = Potentiometer[1];
            pl5[pl5presetNr].Env1_Decay = map(pl5[pl5presetNr].Env1_Decay_graph, 0, 127, 10, 700);
            pl5envelope1.decay(pl5[pl5presetNr].Env1_Decay);
            pl5envelope2.decay(pl5[pl5presetNr].Env1_Decay);
            drawPot_2(7, CTRL_ROW_2, pl5[pl5presetNr].Env1_Decay_graph, pl5[pl5presetNr].Env1_Decay, "Dec", trackColor[desired_instrument]);
          }
        }
        if (abs(Potentiometer[2] - pl5[pl5presetNr].Env1_Sustain_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl5[pl5presetNr].Env1_Sustain_graph != Potentiometer[2]) {
            pl5[pl5presetNr].Env1_Sustain_graph = Potentiometer[2];
            pl5[pl5presetNr].Env1_Sustain = pl5[pl5presetNr].Env1_Sustain_graph / 127.00;
            pl5envelope1.sustain(pl5[pl5presetNr].Env1_Sustain);
            pl5envelope2.sustain(pl5[pl5presetNr].Env1_Sustain);
            drawPot_3(11, CTRL_ROW_2, pl5[pl5presetNr].Env1_Sustain_graph, pl5[pl5presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_instrument]);
          }
        }
        if (abs(Potentiometer[3] - pl5[pl5presetNr].Env1_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl5[pl5presetNr].Env1_Release_graph != Potentiometer[3]) {
            pl5[pl5presetNr].Env1_Release_graph = Potentiometer[3];
            pl5[pl5presetNr].Env1_Release = map(pl5[pl5presetNr].Env1_Release_graph, 0, 127, 180, 1200);
            pl5envelope1.release(pl5[pl5presetNr].Env1_Release);
            pl5envelope2.release(pl5[pl5presetNr].Env1_Release);
            drawPot_4(15, CTRL_ROW_2, pl5[pl5presetNr].Env1_Release_graph, pl5[pl5presetNr].Env1_Release, "Rel", trackColor[desired_instrument]);
          }
        }
        break;
    }
  }
  if (selectPage == PLUGIN6_PAGE1) {
    switch (lastPotRow) {
      case 0:
        if (abs(Potentiometer[0] - pl6[pl6presetNr].selected_file_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl6[pl6presetNr].selected_file_graph != Potentiometer[0]) {
            pl6[pl6presetNr].selected_file_graph = Potentiometer[0];
            pl6[pl6presetNr].selected_file = map(Potentiometer[0], 0, 127, 0, MAX_RAW_FILES);
            drawPot(CTRL_COL_0, CTRL_ROW_0, pl6[pl6presetNr].selected_file_graph, pl6[pl6presetNr].selected_file, "RAW", ILI9341_BLACK);
          }
        }
        break;
      case 1:
        if (abs(Potentiometer[0] - pl6[pl6presetNr].Filter1_Frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl6[pl6presetNr].Filter1_Frequency_graph != Potentiometer[0]) {
            pl6[pl6presetNr].Filter1_Frequency_graph = Potentiometer[0];
            pl6[pl6presetNr].Filter1_Frequency = note_frequency[pl6[pl6presetNr].Filter1_Frequency_graph];
            pl6filter1.frequency(pl6[pl6presetNr].Filter1_Frequency);
            drawPot(CTRL_COL_0, CTRL_ROW_1, pl6[pl6presetNr].Filter1_Frequency_graph, pl6[pl6presetNr].Filter1_Frequency, "Freq", trackColor[desired_instrument]);
          }
        }
        if (abs(Potentiometer[1] - pl6[pl6presetNr].Filter1_Resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl6[pl6presetNr].Filter1_Resonance_graph != Potentiometer[1]) {
            pl6[pl6presetNr].Filter1_Resonance_graph = Potentiometer[1];
            pl6[pl6presetNr].Filter1_Resonance = pl6[pl6presetNr].Filter1_Resonance_graph / 25.40;
            pl6filter1.resonance(pl6[pl6presetNr].Filter1_Resonance);
            drawPot_2(CTRL_COL_1, CTRL_ROW_1, pl6[pl6presetNr].Filter1_Resonance_graph, pl6[pl6presetNr].Filter1_Resonance_graph, "Reso", trackColor[desired_instrument]);
          }
        }
        if (abs(Potentiometer[2] - pl6[pl6presetNr].Filter1_Sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl6[pl6presetNr].Filter1_Sweep_graph != Potentiometer[2]) {
            pl6[pl6presetNr].Filter1_Sweep_graph = Potentiometer[2];
            pl6[pl6presetNr].Filter1_Sweep = pl6[pl6presetNr].Filter1_Sweep_graph / 18.14;
            pl6filter1.octaveControl(pl6[pl6presetNr].Filter1_Sweep);
            drawPot_3(CTRL_COL_2, CTRL_ROW_1, pl6[pl6presetNr].Filter1_Sweep_graph, pl6[pl6presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_instrument]);
          }
        }
        if (abs(Potentiometer[3] - pl6[pl6presetNr].Filter1_Type_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl6[pl6presetNr].Filter1_Type_graph != Potentiometer[3]) {
            pl6[pl6presetNr].Filter1_Type_graph = Potentiometer[3];
            pl6[pl6presetNr].Filter1_Type = pl6[pl6presetNr].Filter1_Type_graph / 43;
            selectFilterType(21, pl6[pl6presetNr].Filter1_Type);
            drawPot_4(CTRL_COL_3, CTRL_ROW_1, pl6[pl6presetNr].Filter1_Type_graph, pl6[pl6presetNr].Filter1_Type, "", trackColor[desired_track]);
            drawChar(CTRL_COL_3, 7, filterType[pl6[pl6presetNr].Filter1_Type], ILI9341_WHITE);
          }
        }
        break;
      case 2:
        if (abs(Potentiometer[0] - pl6[pl6presetNr].Env1_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl6[pl6presetNr].Env1_Attack_graph != Potentiometer[0]) {
            pl6[pl6presetNr].Env1_Attack_graph = Potentiometer[0];
            pl6[pl6presetNr].Env1_Attack = map(pl6[pl6presetNr].Env1_Attack_graph, 0, 127, 10, 700);
            pl6envelope1.attack(pl6[pl6presetNr].Env1_Attack);
            pl6envelope2.attack(pl6[pl6presetNr].Env1_Attack);
            drawPot(3, CTRL_ROW_2, pl6[pl6presetNr].Env1_Attack_graph, pl6[pl6presetNr].Env1_Attack, "Atck", trackColor[desired_instrument]);
          }
        }
        if (abs(Potentiometer[1] - pl6[pl6presetNr].Env1_Decay_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl6[pl6presetNr].Env1_Decay_graph != Potentiometer[1]) {
            pl6[pl6presetNr].Env1_Decay_graph = Potentiometer[1];
            pl6[pl6presetNr].Env1_Decay = map(pl6[pl6presetNr].Env1_Decay_graph, 0, 127, 10, 700);
            pl6envelope1.decay(pl6[pl6presetNr].Env1_Decay);
            pl6envelope2.decay(pl6[pl6presetNr].Env1_Decay);
            drawPot_2(7, CTRL_ROW_2, pl6[pl6presetNr].Env1_Decay_graph, pl6[pl6presetNr].Env1_Decay, "Dec", trackColor[desired_instrument]);
          }
        }
        if (abs(Potentiometer[2] - pl6[pl6presetNr].Env1_Sustain_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl6[pl6presetNr].Env1_Sustain_graph != Potentiometer[2]) {
            pl6[pl6presetNr].Env1_Sustain_graph = Potentiometer[2];
            pl6[pl6presetNr].Env1_Sustain = pl6[pl6presetNr].Env1_Sustain_graph / 127.00;
            pl6envelope1.sustain(pl6[pl6presetNr].Env1_Sustain);
            pl6envelope2.sustain(pl6[pl6presetNr].Env1_Sustain);
            drawPot_3(11, CTRL_ROW_2, pl6[pl6presetNr].Env1_Sustain_graph, pl6[pl6presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_instrument]);
          }
        }
        if (abs(Potentiometer[3] - pl6[pl6presetNr].Env1_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl6[pl6presetNr].Env1_Release_graph != Potentiometer[3]) {
            pl6[pl6presetNr].Env1_Release_graph = Potentiometer[3];
            pl6[pl6presetNr].Env1_Release = map(pl6[pl6presetNr].Env1_Release_graph, 0, 127, 180, 1200);
            pl6envelope1.release(pl6[pl6presetNr].Env1_Release);
            pl6envelope2.release(pl6[pl6presetNr].Env1_Release);
            drawPot_4(15, CTRL_ROW_2, pl6[pl6presetNr].Env1_Release_graph, pl6[pl6presetNr].Env1_Release, "Rel", trackColor[desired_instrument]);
          }
        }
        break;
    }
  }
  if (selectPage == PLUGIN8_PAGE1) {
    switch (lastPotRow) {
      case 0:
        if (pl8[pl8presetNr].wfSelect_graph != Potentiometer[0]) {
          pl8[pl8presetNr].wfSelect_graph = Potentiometer[0];
          pl8[pl8presetNr].wfSelect = map(pl8[pl8presetNr].wfSelect_graph, 0, 127, 0, 12);
          pl8waveform1.begin(pl8[pl8presetNr].wfSelect);
          drawPot(CTRL_COL_0, CTRL_ROW_0, pl8[pl8presetNr].wfSelect_graph, pl8[pl8presetNr].wfSelect, "WForm", trackColor[desired_track]);
        }
        break;
      case 1:
        if (abs(Potentiometer[0] - pl8[pl8presetNr].Filter1_Frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl8[pl8presetNr].Filter1_Frequency_graph != Potentiometer[0]) {
            pl8[pl8presetNr].Filter1_Frequency_graph = Potentiometer[0];
            pl8[pl8presetNr].Filter1_Frequency = note_frequency[pl8[pl8presetNr].Filter1_Frequency_graph];
            pl8filter1.frequency(pl8[pl8presetNr].Filter1_Frequency);
            drawPot(CTRL_COL_0, CTRL_ROW_1, pl8[pl8presetNr].Filter1_Frequency_graph, pl8[pl8presetNr].Filter1_Frequency, "Freq", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[1] - pl8[pl8presetNr].Filter1_Resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl8[pl8presetNr].Filter1_Resonance_graph != Potentiometer[1]) {
            pl8[pl8presetNr].Filter1_Resonance_graph = Potentiometer[1];
            pl8[pl8presetNr].Filter1_Resonance = pl8[pl8presetNr].Filter1_Resonance_graph / 25.40;
            pl8filter1.resonance(pl8[pl8presetNr].Filter1_Resonance);
            drawPot_2(CTRL_COL_1, CTRL_ROW_1, pl8[pl8presetNr].Filter1_Resonance_graph, pl8[pl8presetNr].Filter1_Resonance_graph, "Reso", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[2] - pl8[pl8presetNr].Filter1_Sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl8[pl8presetNr].Filter1_Sweep_graph != Potentiometer[2]) {
            pl8[pl8presetNr].Filter1_Sweep_graph = Potentiometer[2];
            pl8[pl8presetNr].Filter1_Sweep = pl8[pl8presetNr].Filter1_Sweep_graph / 18.14;
            pl8filter1.octaveControl(pl8[pl8presetNr].Filter1_Sweep);
            drawPot_3(CTRL_COL_2, CTRL_ROW_1, pl8[pl8presetNr].Filter1_Sweep_graph, pl8[pl8presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_track]);
          }
        }
        break;
      case 2:
        if (abs(Potentiometer[0] - pl8[pl8presetNr].Env1_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl8[pl8presetNr].Env1_Attack_graph != Potentiometer[0]) {
            pl8[pl8presetNr].Env1_Attack_graph = Potentiometer[0];
            pl8[pl8presetNr].Env1_Attack = map(pl8[pl8presetNr].Env1_Attack_graph, 0, 127, 10, 700);
            pl8envelope1.attack(pl8[pl8presetNr].Env1_Attack);
            pl8envelope2.attack(pl8[pl8presetNr].Env1_Attack);
            drawPot(CTRL_COL_0, CTRL_ROW_2, pl8[pl8presetNr].Env1_Attack_graph, pl8[pl8presetNr].Env1_Attack, "Atck", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[1] - pl8[pl8presetNr].Env1_Decay_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl8[pl8presetNr].Env1_Decay_graph != Potentiometer[1]) {
            pl8[pl8presetNr].Env1_Decay_graph = Potentiometer[1];
            pl8[pl8presetNr].Env1_Decay = map(pl8[pl8presetNr].Env1_Decay_graph, 0, 127, 10, 700);
            pl8envelope1.decay(pl8[pl8presetNr].Env1_Decay);
            pl8envelope2.decay(pl8[pl8presetNr].Env1_Decay);
            drawPot_2(CTRL_COL_1, CTRL_ROW_2, pl8[pl8presetNr].Env1_Decay_graph, pl8[pl8presetNr].Env1_Decay, "Dec", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[2] - pl8[pl8presetNr].Env1_Sustain_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl8[pl8presetNr].Env1_Sustain_graph != Potentiometer[2]) {
            pl8[pl8presetNr].Env1_Sustain_graph = Potentiometer[2];
            pl8[pl8presetNr].Env1_Sustain = pl8[pl8presetNr].Env1_Sustain_graph / 127.00;
            pl8envelope1.sustain(pl8[pl8presetNr].Env1_Sustain);
            pl8envelope2.sustain(pl8[pl8presetNr].Env1_Sustain);
            drawPot_3(CTRL_COL_2, CTRL_ROW_2, pl8[pl8presetNr].Env1_Sustain_graph, pl8[pl8presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[3] - pl8[pl8presetNr].Env1_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl8[pl8presetNr].Env1_Release_graph != Potentiometer[3]) {
            pl8[pl8presetNr].Env1_Release_graph = Potentiometer[3];
            pl8[pl8presetNr].Env1_Release = map(pl8[pl8presetNr].Env1_Release_graph, 0, 127, 180, 1200);
            pl8envelope1.release(pl8[pl8presetNr].Env1_Release);
            pl8envelope2.release(pl8[pl8presetNr].Env1_Release);
            drawPot_4(CTRL_COL_3, CTRL_ROW_2, pl8[pl8presetNr].Env1_Release_graph, pl8[pl8presetNr].Env1_Release, "Rel", trackColor[desired_track]);
          }
        }
        break;
    }
  }
  if (selectPage == PLUGIN9_PAGE1) {
    switch (lastPotRow) {
      case 0:
        if (abs(Potentiometer[0] - pl9[pl9presetNr].wah_form_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].wah_form_graph != Potentiometer[0]) {
            pl9[pl9presetNr].wah_form_graph = Potentiometer[0];
            pl9[pl9presetNr].wah_form = pl9[pl9presetNr].wah_form_graph / 10;
            pl9bpinput.begin(pl9[pl9presetNr].wah_form);
            drawPot(CTRL_COL_0, CTRL_ROW_0, pl9[pl9presetNr].wah_form_graph, pl9[pl9presetNr].wah_form, "WForm", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[1] - pl9[pl9presetNr].wah_rate_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].wah_rate_graph != Potentiometer[1]) {
            pl9[pl9presetNr].wah_rate_graph = Potentiometer[1];
            pl9[pl9presetNr].wah_rate = pl9[pl9presetNr].wah_rate_graph / 16.00;
            pl9bpinput.frequency(pl9[pl9presetNr].wah_rate);
            drawPot_2(CTRL_COL_1, CTRL_ROW_0, pl9[pl9presetNr].wah_rate_graph, pl9[pl9presetNr].wah_rate, "Rate", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[2] - pl9[pl9presetNr].wah_sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].wah_sweep_graph != Potentiometer[2]) {
            pl9[pl9presetNr].wah_sweep_graph = Potentiometer[2];
            pl9[pl9presetNr].wah_sweep = pl9[pl9presetNr].wah_sweep_graph / 18.30;
            pl9bpfilter.octaveControl(pl9[pl9presetNr].wah_sweep);
            drawPot_3(CTRL_COL_2, CTRL_ROW_0, pl9[pl9presetNr].wah_sweep_graph, pl9[pl9presetNr].wah_sweep_graph, "Depth", trackColor[desired_track]);
          }
        }
        break;
      case 1:
        if (abs(Potentiometer[0] - pl9[pl9presetNr].wah_freq_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].wah_freq_graph != Potentiometer[0]) {
            pl9[pl9presetNr].wah_freq_graph = Potentiometer[0];
            pl9[pl9presetNr].wah_freq = map(pl9[pl9presetNr].wah_freq_graph, 0, 127, 20, 2000);
            pl9bpfilter.frequency(pl9[pl9presetNr].wah_freq);
            drawPot(CTRL_COL_0, CTRL_ROW_1, pl9[pl9presetNr].wah_freq_graph, pl9[pl9presetNr].wah_freq_graph, "Freq", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[1] - pl9[pl9presetNr].wah_reso_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].wah_reso_graph != Potentiometer[1]) {
            pl9[pl9presetNr].wah_reso_graph = Potentiometer[1];
            pl9[pl9presetNr].wah_reso = pl9[pl9presetNr].wah_reso_graph / 25.40;
            pl9bpfilter.resonance(pl9[pl9presetNr].wah_reso);
            drawPot_2(CTRL_COL_1, CTRL_ROW_1, pl9[pl9presetNr].wah_reso_graph, pl9[pl9presetNr].wah_reso_graph, "Reso", trackColor[desired_track]);
          }
        }
        break;
      case 2:
        if (abs(Potentiometer[0] - pl9[pl9presetNr].wavefold_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].wavefold_graph != Potentiometer[0]) {
            pl9[pl9presetNr].wavefold_graph = Potentiometer[0];
            pl9[pl9presetNr].wavefold = (pl9[pl9presetNr].wavefold_graph / 64.00) + 0.06;
            pl9dc1.amplitude(pl9[pl9presetNr].wavefold);
            drawPot(CTRL_COL_0, CTRL_ROW_2, pl9[pl9presetNr].wavefold_graph, pl9[pl9presetNr].wavefold_graph, "WFold", trackColor[desired_track]);
          }
        }
        break;
      case 3:
        if (abs(Potentiometer[0] - pl9[pl9presetNr].Filter1_Frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].Filter1_Frequency_graph != Potentiometer[0]) {
            pl9[pl9presetNr].Filter1_Frequency_graph = Potentiometer[0];
            pl9[pl9presetNr].Filter1_Frequency = note_frequency[pl9[pl9presetNr].Filter1_Frequency_graph];
            pl9filter2.frequency(pl9[pl9presetNr].Filter1_Frequency);
            drawPot(CTRL_COL_0, CTRL_ROW_3, pl9[pl9presetNr].Filter1_Frequency_graph, pl9[pl9presetNr].Filter1_Frequency, "Freq", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[1] - pl9[pl9presetNr].Filter1_Resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].Filter1_Resonance_graph != Potentiometer[1]) {
            pl9[pl9presetNr].Filter1_Resonance_graph = Potentiometer[1];
            pl9[pl9presetNr].Filter1_Resonance = pl9[pl9presetNr].Filter1_Resonance_graph / 25.40;
            pl9filter2.resonance(pl9[pl9presetNr].Filter1_Resonance);
            drawPot_2(CTRL_COL_1, CTRL_ROW_3, pl9[pl9presetNr].Filter1_Resonance_graph, pl9[pl9presetNr].Filter1_Resonance_graph, "Reso", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[2] - pl9[pl9presetNr].Filter1_Sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].Filter1_Sweep_graph != Potentiometer[2]) {
            pl9[pl9presetNr].Filter1_Sweep_graph = Potentiometer[2];
            pl9[pl9presetNr].Filter1_Sweep = pl9[pl9presetNr].Filter1_Sweep_graph / 18.14;
            pl9filter2.octaveControl(pl9[pl9presetNr].Filter1_Sweep);
            drawPot_3(CTRL_COL_2, CTRL_ROW_3, pl9[pl9presetNr].Filter1_Sweep_graph, pl9[pl9presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[3] - pl9[pl9presetNr].Filter1_Type_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl9[pl9presetNr].Filter1_Type_graph != Potentiometer[3]) {
            pl9[pl9presetNr].Filter1_Type_graph = Potentiometer[3];
            pl9[pl9presetNr].Filter1_Type = pl9[pl9presetNr].Filter1_Type_graph / 43;
            selectFilterType(25, pl9[pl1presetNr].Filter1_Type);
            drawPot_4(CTRL_COL_3, CTRL_ROW_3, pl9[pl9presetNr].Filter1_Type_graph, pl9[pl9presetNr].Filter1_Type, "", trackColor[desired_track]);
            drawChar(CTRL_COL_3, 13, filterType[pl9[pl9presetNr].Filter1_Type], ILI9341_WHITE);
          }
        }
        break;
    }
  }


  //launchpad control up-est row, they send cc´s
  if (launchpad) {
    //cursor left
    if (otherCtrlButtons && control == 104 && value == 127) {
      button[0] = true;
      gridTouchX--;
      drawCursor();
    } else if (otherCtrlButtons && control == 104 && value != 127) {
      button[0] = false;
    }
    //cursor right
    if (otherCtrlButtons && control == 105 && value == 127) {
      button[1] = true;
      gridTouchX++;
      drawCursor();
    } else if (otherCtrlButtons && control == 105 && value != 127) {
      button[1] = false;
    }
    //cursor up
    if (otherCtrlButtons && control == 106 && value == 127) {
      button[2] = true;
      gridTouchY--;
      drawCursor();
    } else if (otherCtrlButtons && control == 106 && value != 127) {
      button[2] = false;
    }
    //cursor down
    if (otherCtrlButtons && control == 107 && value == 127) {
      button[3] = true;
      gridTouchY++;
      drawCursor();
    } else if (otherCtrlButtons && control == 107 && value != 127) {
      button[3] = false;
    }
    //last pot row
    if (otherCtrlButtons && control == 108 && value == 127) {
      button[4] = true;
      lastPotRow++;
      if (lastPotRow == 4) {
        lastPotRow = 0;
      }
    } else if (otherCtrlButtons && control == 108 && value != 127) {
      button[4] = false;
    }
    //recbutton
    if (otherCtrlButtons && control == 109 && value == 127) {
      button[5] = true;
      if (seq_rec == false) {
        seq_rec = true;
        tft.fillCircle(STEP_FRAME_W * POSITION_RECORD_BUTTON + 7, 7, DOT_RADIUS + 1, ILI9341_RED);
        if (selectPage == RECORDER_PAGE) {
          startRecording();
          drawActiveRect(CTRL_COL_1, CTRL_ROW_1, 2, 1, audio_rec_rec, "Rec", ILI9341_ORANGE);
        }
      } else {
        seq_rec = false;
        tft.fillCircle(STEP_FRAME_W * POSITION_RECORD_BUTTON + 7, 7, DOT_RADIUS + 1, ILI9341_LIGHTGREY);
        if (selectPage == RECORDER_PAGE) {
          stopRecording();
          drawActiveRect(CTRL_COL_1, CTRL_ROW_1, 2, 2, audio_rec_rec, "Rec", ILI9341_GREEN);
        }
      }
    } else if (otherCtrlButtons && control == 109 && value != 127) {
      button[5] = false;
    }
    //playbutton
    if (otherCtrlButtons && control == 110 && value == 127) {
      button[6] = true;
      startSeq();
    } else if (otherCtrlButtons && control == 110 && value != 127) {
      button[6] = false;
    }
    //stopbutton
    if (otherCtrlButtons && control == 111 && value == 127) {
      button[7] = true;
      stopSeq();
    } else if (otherCtrlButtons && control == 111 && value != 127) {
      button[7] = false;
    }


    //select tracks
    if (button[8]) {                         //9th button
      if (control == 104 && value == 127) {  //"D"  68  1st button
        selectPage = DRUMTRACK;
        desired_instrument = 0;
        desired_track = 0;
        drumStepSequencer_Static();
      }
      for (int controlss = 1; controlss < 8; controlss++) {
        //select melodic track 2
        if (control == controlss + 104 && value == 127) {  //"F"  70 2nd button
          selectPage = controlss;
          desired_instrument = controlss;
          desired_track = controlss;
          gridStepSequencer(controlss);
        }
      }
    }

    //plugin selection
    if (button[9]) {
      for (int controlss = 0; controlss < 8; controlss++) {
        if (control == controlss + 104 && value == 127) {  //"D"  68  1st button
          desired_track = controlss;
          desired_instrument = controlss;
          //midicc_view
          for (byte pluginSelection = 0; pluginSelection <= MAX_PLUGINS; pluginSelection++) {
            if (track[desired_instrument].MIDIchannel == pluginSelection) {
              selectPage = MIDICC_PAGE_1;
              midiCC_view_Static(0, desired_track);
            }
            //plugin_1_view
            if (track[desired_instrument].MIDIchannel == pluginSelection + 17) {
              selectPage = pluginSelection + 40;
              Plugin_View_Static();
            }
          }
        }
      }
    }

    //  select Mixer
    if (button[11]) {                        //"8"  56
      if (control == 104 && value == 127) {  //"D"  68
        selectPage = MIXER_PAGE_1;
        mixerPage1_Static(0);
      }
      //select melodic track 2
      if (control == 105 && value == 127) {  //"F"  70
        selectPage = MIXER_PAGE_2;
        mixerPage2_Static();
      }
      //select melodic track 3
      if (control == 106 && value == 127) {  //"9"  57
        selectPage = MIXER_PAGE_3;
        mixerPage3_Static();
      }
    }
    //FX Selection
    if (button[12]) {
      if (control == 104 && value == 127) {
        selectPage = FX1_PAGE1;
        FX1reverb_static();
      }
      if (control == 105 && value == 127) {
        selectPage = FX2_PAGE1;
        FX2Bitcrush_static();
      }
      if (control == 106 && value == 127) {
        //delay
      }
    }
  }
}