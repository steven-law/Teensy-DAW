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
            usbMIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
            MIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
            midi1.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
            midi2.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
            midi3.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
            midi4.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
            midi5.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
            midi6.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
            dsend_noteOff[i] = true;
          }
        } else {
          if (dsend_noteOff[i]) {
            usbMIDI.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            MIDI.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            midi1.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            midi2.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            midi3.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            midi4.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            midi5.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            midi6.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            dsend_noteOff[i] = false;
          }
        }
      }
      //play drumplugin when midichannel = 18
      if (track[0].MIDIchannel == 18) {
        if (channel1Clip[track[0].clip_songMode][0][current]) {
          playSdWav1.play("P0.WAV");
        }
        if (channel1Clip[track[0].clip_songMode][1][current]) {
          playSdWav2.play("P1.WAV");
        }
        if (channel1Clip[track[0].clip_songMode][2][current]) {
          playSdWav3.play("P2.WAV");
        }
        if (channel1Clip[track[0].clip_songMode][3][current]) {
          playSdWav4.play("P3.WAV");
        }
        if (channel1Clip[track[0].clip_songMode][4][current]) {
          playSdWav5.play("P4.WAV");
        }
        if (channel1Clip[track[0].clip_songMode][5][current]) {
          playSdWav6.play("P5.WAV");
        }
        if (channel1Clip[track[0].clip_songMode][6][current]) {
          playSdWav7.play("P6.WAV");
        }
        if (channel1Clip[track[0].clip_songMode][7][current]) {
          playSdWav8.play("P7.WAV");
        }
        if (channel1Clip[track[0].clip_songMode][8][current]) {
          playSdWav9.play("P8.WAV");
        }
        if (channel1Clip[track[0].clip_songMode][9][current]) {
          playSdWav10.play("P9.WAV");
        }
        if (channel1Clip[track[0].clip_songMode][10][current]) {
          playSdWav11.play("P10.WAV");
        }
        if (channel1Clip[track[0].clip_songMode][11][current]) {
          playSdWav12.play("P11.WAV");
        }
      }

      //play Memory drumplugin when midichannel = 20
      if (track[0].MIDIchannel == 20) {
        if (channel1Clip[track[0].clip_songMode][0][current]) {
          playMem1.play(AudioSampleKick);
        }
        if (channel1Clip[track[0].clip_songMode][1][current]) {
          playMem2.play(AudioSampleSnare);
        }
        if (channel1Clip[track[0].clip_songMode][2][current]) {
          playMem3.play(AudioSampleP2);
        }
        if (channel1Clip[track[0].clip_songMode][3][current]) {
          playMem4.play(AudioSampleHihat);
        }
        if (channel1Clip[track[0].clip_songMode][4][current]) {
          playMem5.play(AudioSampleCashregister);
        }
        if (channel1Clip[track[0].clip_songMode][5][current]) {
          playMem6.play(AudioSampleTomtom);
        }
        if (channel1Clip[track[0].clip_songMode][6][current]) {
          playMem6.play(AudioSampleGong);
        }
        if (channel1Clip[track[0].clip_songMode][7][current]) {
          //playSdWav8.play("P7.WAV");
        }
        if (channel1Clip[track[0].clip_songMode][8][current]) {
          //playSdWav9.play("P8.WAV");
        }
        if (channel1Clip[track[0].clip_songMode][9][current]) {
          //playSdWav10.play("P9.WAV");
        }
        if (channel1Clip[track[0].clip_songMode][10][current]) {
          //playSdWav11.play("P10.WAV");
        }
        if (channel1Clip[track[0].clip_songMode][11][current]) {
          //playSdWav12.play("P11.WAV");
        }
      }
      //play Memory drumplugin when midichannel = 20
      if (track[0].MIDIchannel == 23) {
        if (channel1Clip[track[0].clip_songMode][0][current]) {
          pl7drum1.noteOn();
        }
        if (channel1Clip[track[0].clip_songMode][1][current]) {
          pl7envelope1.noteOn();
        } else {
          pl7envelope1.noteOff();
        }
        if (channel1Clip[track[0].clip_songMode][2][current]) {
          pl7envelope2.noteOn();
          pl7envelope3.noteOn();
        } else {
          pl7envelope2.noteOff();
          pl7envelope3.noteOff();
        }
        if (channel1Clip[track[0].clip_songMode][3][current]) {
          //playMem4.play(AudioSampleHihat);
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

        byte noteNumber = ctrack[track_number].sequence[track[track_number].clip_songMode].step[current] + track[track_number].NoteOffset[phrase];
        if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[current] > VALUE_NOTEOFF) {
          if (track[track_number].MIDIchannel < 17) {
            usbMIDI.sendNoteOn(noteNumber, track[track_number].MIDI_velocity, track[track_number].MIDIchannel);
            MIDI.sendNoteOn(noteNumber, track[track_number].MIDI_velocity, track[track_number].MIDIchannel);
            midi1.sendNoteOn(noteNumber, track[track_number].MIDI_velocity, track[track_number].MIDIchannel);
            midi2.sendNoteOn(noteNumber, track[track_number].MIDI_velocity, track[track_number].MIDIchannel);
            midi3.sendNoteOn(noteNumber, track[track_number].MIDI_velocity, track[track_number].MIDIchannel);
            midi4.sendNoteOn(noteNumber, track[track_number].MIDI_velocity, track[track_number].MIDIchannel);
            midi5.sendNoteOn(noteNumber, track[track_number].MIDI_velocity, track[track_number].MIDIchannel);
            midi6.sendNoteOn(noteNumber, track[track_number].MIDI_velocity, track[track_number].MIDIchannel);
          }

          if (track[track_number].MIDIchannel == 17) {
            waveform1.frequency(note_frequency[noteNumber + pl1[track[track_number].presetNr[phrase]].note_Offset[0]]);
            waveform2.frequency(note_frequency[noteNumber + pl1[track[track_number].presetNr[phrase]].note_Offset[1]]);
            waveform3.frequency(note_frequency[noteNumber + pl1[track[track_number].presetNr[phrase]].note_Offset[2]]);
            waveform4.frequency(note_frequency[noteNumber + pl1[track[track_number].presetNr[phrase]].note_Offset[3]]);
            envelope1.noteOn();
            envelope2.noteOn();
          }
          if (track[track_number].MIDIchannel == 19) {
            pl3waveform1.frequency(note_frequency[noteNumber]);
            pl3envelope1.noteOn();
            pl3envelope2.noteOn();
          }
          if (track[track_number].MIDIchannel == 21) {
            double note_ratio = pow(2.0, ((double)(noteNumber - SAMPLE_ROOT) / 12.0));
            playSdPitch1.setPlaybackRate(note_ratio);
            //playSdPitch1.playRaw(RAW_files[pl5[track[desired_track].presetNr[phrase]].selected_file], 1);
            playSdPitch1.playRaw(pl5sample->sampledata, pl5sample->samplesize, 1);
            pl5envelope1.noteOn();
            pl5envelope2.noteOn();
            Serial.println("listen?");
          }
          if (track[track_number].MIDIchannel == 22) {
            double note_ratio = pow(2.0, ((double)(noteNumber - SAMPLE_ROOT) / 12.0));
            playSdPitch2.setPlaybackRate(note_ratio);
            playSdPitch2.playRaw(RAW_files[pl6[track[track_number].presetNr[phrase]].selected_file_raw], 1);
            pl6envelope1.noteOn();
            pl6envelope2.noteOn();
          }
          if (track[track_number].MIDIchannel == 24) {
            pl8waveform1.frequency(note_frequency[noteNumber]);
            pl8envelope1.noteOn();
            pl8envelope2.noteOn();
          }
          if (track[track_number].MIDIchannel == 25) {
            pl9string1.noteOn(note_frequency[noteNumber], 1);
          }
          track[track_number].send_noteOff = true;
        }
        //if (track[track_number].send_noteOff) {
        if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[current - 1] > VALUE_NOTEOFF) {
          if (track[track_number].MIDIchannel < 17) {
            usbMIDI.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[current - 1] + track[track_number].NoteOffset[phrase], VELOCITYOFF, track[track_number].MIDIchannel);
            MIDI.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[current - 1] + track[track_number].NoteOffset[phrase], VELOCITYOFF, track[track_number].MIDIchannel);
            midi1.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[current - 1] + track[track_number].NoteOffset[phrase], VELOCITYOFF, track[track_number].MIDIchannel);
            midi2.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[current - 1] + track[track_number].NoteOffset[phrase], VELOCITYOFF, track[track_number].MIDIchannel);
            midi3.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[current - 1] + track[track_number].NoteOffset[phrase], VELOCITYOFF, track[track_number].MIDIchannel);
            midi4.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[current - 1] + track[track_number].NoteOffset[phrase], VELOCITYOFF, track[track_number].MIDIchannel);
            midi5.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[current - 1] + track[track_number].NoteOffset[phrase], VELOCITYOFF, track[track_number].MIDIchannel);
            midi6.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[current - 1] + track[track_number].NoteOffset[phrase], VELOCITYOFF, track[track_number].MIDIchannel);
          }
          if (track[track_number].MIDIchannel == 17) {
            envelope1.noteOff();
            envelope2.noteOff();
          }
          if (track[track_number].MIDIchannel == 19) {
            pl3envelope1.noteOff();
            pl3envelope2.noteOff();
          }
          if (track[track_number].MIDIchannel == 21) {
            pl5envelope1.noteOff();
            pl5envelope2.noteOff();
          }
          if (track[track_number].MIDIchannel == 22) {
            pl6envelope1.noteOff();
            pl6envelope2.noteOff();
          }
          if (track[track_number].MIDIchannel == 24) {
            pl8envelope1.noteOff();
            pl8envelope2.noteOff();
          }
          if (track[track_number].MIDIchannel == 25) {
            pl9string1.noteOff(VELOCITYOFF);
          }
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
        if (!button_15) {
          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_value_row_1[MixerColumn] = constrain((track[desired_instrument].midicc_value_row_1[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawPotCC(MixerColumnPos, CTRL_ROW_0, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], trackColor[desired_instrument]);
            usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].MIDIchannel);
          }

          /*if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_value_row_1[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_value_row_1[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_value_row_1[MixerColumn] = Potentiometer[MixerColumn];
              drawPotCC(MixerColumnPos, CTRL_ROW_0, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], trackColor[desired_instrument]);
              usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].MIDIchannel);
            }
          }*/
        }
        if (button_15) {
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
        if (!button_15) {

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
        if (button_15) {
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
        if (!button_15) {

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
        if (button_15) {
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
        if (!button_15) {

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
        if (button_15) {

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
  if (ts.touched() || enter_button) {

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

void myNoteOn(byte channel, byte note, byte velocity) {
  // When a USB device with multiple virtual cables is used,
  // midi1.getCable() can be used to read which of the virtual
  // MIDI cables received this message.

  if (seq_rec) {
    ctrack[channel - 1].sequence[track[channel - 1].clip_selector].step[tick_16] = note;

  } else {
    //send midinotes for drumtrack #1

    //play drumplugin when midichannel = 18
    if (track[channel - 1].MIDIchannel == 18) {
      if (note == 36) {
        playSdWav1.play("P0.WAV");
      }
      if (note == 37) {
        playSdWav2.play("P1.WAV");
      }
      if (note == 38) {
        playSdWav3.play("P2.WAV");
      }
      if (note == 39) {
        playSdWav4.play("P3.WAV");
      }
      if (note == 40) {
        playSdWav5.play("P4.WAV");
      }
      if (note == 41) {
        playSdWav6.play("P5.WAV");
      }
      if (note == 42) {
        playSdWav7.play("P6.WAV");
      }
      if (note == 43) {
        playSdWav8.play("P7.WAV");
      }
      if (note == 44) {
        playSdWav9.play("P8.WAV");
      }
      if (note == 45) {
        playSdWav10.play("P9.WAV");
      }
      if (note == 46) {
        playSdWav11.play("P10.WAV");
      }
      if (note == 47) {
        playSdWav12.play("P11.WAV");
      }
    }

    //play Memory drumplugin when midichannel = 20
    if (track[channel - 1].MIDIchannel == 20) {
      if (note == 36) {
        playMem1.play(AudioSampleKick);
      }
      if (note == 37) {
        playMem2.play(AudioSampleSnare);
      }
      if (note == 38) {
        playMem3.play(AudioSampleP2);
      }
      if (note == 39) {
        playMem4.play(AudioSampleHihat);
      }
      if (note == 40) {
        playMem5.play(AudioSampleCashregister);
      }
      if (note == 41) {
        playMem6.play(AudioSampleTomtom);
      }
      if (note == 42) {
        playMem6.play(AudioSampleGong);
      }
      if (note == 43) {
        //playSdWav8.play("P7.WAV");
      }
      if (note == 44) {
        //playSdWav9.play("P8.WAV");
      }
      if (note == 45) {
        //playSdWav10.play("P9.WAV");
      }
      if (note == 46) {
        //playSdWav11.play("P10.WAV");
      }
      if (note == 47) {
        //playSdWav12.play("P11.WAV");
      }
    }
    //play Memory drumplugin when midichannel = 20
    if (track[channel - 1].MIDIchannel == 23) {
      if (note == 36) {
        pl7drum1.noteOn();
      }
      if (note == 37) {
        pl7envelope1.noteOn();
      } else {
        pl7envelope1.noteOff();
      }
      if (note == 38) {
        pl7envelope2.noteOn();
        pl7envelope3.noteOn();
      } else {
        pl7envelope2.noteOff();
        pl7envelope3.noteOff();
      }
      if (note == 39) {
        //playMem4.play(AudioSampleHihat);
      }
    }

    if (track[channel - 1].MIDIchannel < 17) {
      usbMIDI.sendNoteOn(note, velocity, track[channel - 1].MIDIchannel);
      midi1.sendNoteOn(note, velocity, track[channel - 1].MIDIchannel);
      midi2.sendNoteOn(note, velocity, track[channel - 1].MIDIchannel);
      midi3.sendNoteOn(note, velocity, track[channel - 1].MIDIchannel);
      midi4.sendNoteOn(note, velocity, track[channel - 1].MIDIchannel);
      midi5.sendNoteOn(note, velocity, track[channel - 1].MIDIchannel);
      midi6.sendNoteOn(note, velocity, track[channel - 1].MIDIchannel);
    }
    if (track[channel - 1].MIDIchannel == 17) {
      waveform1.frequency(note_frequency[note + pl1[track[desired_track].presetNr[phrase]].note_Offset[0]]);
      waveform2.frequency(note_frequency[note + pl1[track[desired_track].presetNr[phrase]].note_Offset[1]]);
      waveform3.frequency(note_frequency[note + pl1[track[desired_track].presetNr[phrase]].note_Offset[2]]);
      waveform4.frequency(note_frequency[note + pl1[track[desired_track].presetNr[phrase]].note_Offset[3]]);
      envelope1.noteOn();
      envelope2.noteOn();
      Serial.println(note);
    }
    if (track[channel - 1].MIDIchannel == 19) {
      pl3waveform1.frequency(note_frequency[note]);
      pl3envelope1.noteOn();
      pl3envelope2.noteOn();
    }
    if (track[channel - 1].MIDIchannel == 21) {
      double note_ratio = pow(2.0, ((double)(note - SAMPLE_ROOT) / 12.0));
      playSdPitch1.setPlaybackRate(note_ratio);
      //playSdPitch1.playRaw(RAW_files[pl5[track[desired_track].presetNr[phrase]].selected_file], 1);
      playSdPitch1.playRaw(pl5sample->sampledata, pl5sample->samplesize, 1);
      pl5envelope1.noteOn();
      pl5envelope2.noteOn();
      Serial.println("listen?");
    }
    if (track[channel - 1].MIDIchannel == 22) {
      double note_ratio = pow(2.0, ((double)(note - SAMPLE_ROOT) / 12.0));
      playSdPitch2.setPlaybackRate(note_ratio);
      playSdPitch2.playRaw(RAW_files[pl6[track[desired_track].presetNr[phrase]].selected_file_raw], 1);
      pl6envelope1.noteOn();
      pl6envelope2.noteOn();
    }
    if (track[channel - 1].MIDIchannel == 24) {
      pl8waveform1.frequency(note_frequency[note]);
      pl8envelope1.noteOn();
      pl8envelope2.noteOn();
    }
    if (track[channel - 1].MIDIchannel == 25) {
      pl9string1.noteOn(note_frequency[note], 1);
    }
  }
}

void myNoteOff(byte channel, byte note, byte velocity) {
  if (!seq_rec) {
    if (track[channel - 1].MIDIchannel < 17) {
      usbMIDI.sendNoteOff(note, velocity, track[channel - 1].MIDIchannel);
      midi1.sendNoteOff(note, velocity, track[channel - 1].MIDIchannel);
      midi2.sendNoteOff(note, velocity, track[channel - 1].MIDIchannel);
      midi3.sendNoteOff(note, velocity, track[channel - 1].MIDIchannel);
      midi4.sendNoteOff(note, velocity, track[channel - 1].MIDIchannel);
      midi5.sendNoteOff(note, velocity, track[channel - 1].MIDIchannel);
      midi6.sendNoteOff(note, velocity, track[channel - 1].MIDIchannel);
    }
    if (track[channel - 1].MIDIchannel == 17) {
      envelope1.noteOff();
      envelope2.noteOff();
    }
    if (track[channel - 1].MIDIchannel == 19) {
      pl3envelope1.noteOff();
      pl3envelope2.noteOff();
    }
    if (track[channel - 1].MIDIchannel == 21) {
      pl5envelope1.noteOff();
      pl5envelope2.noteOff();
    }
    if (track[channel - 1].MIDIchannel == 22) {
      pl6envelope1.noteOff();
      pl6envelope2.noteOff();
    }
    if (track[channel - 1].MIDIchannel == 24) {
      pl8envelope1.noteOff();
      pl8envelope2.noteOff();
    }
    if (track[channel - 1].MIDIchannel == 25) {
      pl9string1.noteOff(0);
    }
  }
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
  if (selectPage == PLUGIN1_PAGE1) {
    switch (lastPotRow) {
      case 0:
        //1 Row 1 note Offset
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          if (abs(Potentiometer[MixerColumn] - pl1[pl1presetNr].note_Offset_graph[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (Potentiometer[MixerColumn] != pl1[pl1presetNr].note_Offset_graph[MixerColumn]) {
              drawPot(MixerColumnPos, CTRL_ROW_0, pl1[pl1presetNr].note_Offset_graph[MixerColumn], pl1[pl1presetNr].note_Offset[MixerColumn], "Offset", trackColor[desired_instrument]);
              pl1[pl1presetNr].note_Offset_graph[MixerColumn] = Potentiometer[MixerColumn];
              pl1[pl1presetNr].note_Offset[MixerColumn] = map(pl1[pl1presetNr].note_Offset_graph[MixerColumn], 0, 127, -18, 18);
            }
          }
        }
        break;
      case 1:
        //1 Row 2 Waveform
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          if (abs(Potentiometer[MixerColumn] - pl1[pl1presetNr].wfSelect_graph[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (pl1[pl1presetNr].wfSelect_graph[MixerColumn] != Potentiometer[MixerColumn]) {
              drawPot(MixerColumnPos, CTRL_ROW_1, pl1[pl1presetNr].wfSelect_graph[MixerColumn], pl1[pl1presetNr].wfSelect[MixerColumn], "W~F", trackColor[desired_instrument]);
              pl1[pl1presetNr].wfSelect_graph[MixerColumn] = Potentiometer[MixerColumn];
              pl1[pl1presetNr].wfSelect[MixerColumn] = map(pl1[pl1presetNr].wfSelect_graph[MixerColumn], 0, 127, 0, 12);
              waveform1.begin(pl1[pl1presetNr].wfSelect[0]);
              waveform2.begin(pl1[pl1presetNr].wfSelect[1]);
              waveform3.begin(pl1[pl1presetNr].wfSelect[2]);
              waveform4.begin(pl1[pl1presetNr].wfSelect[3]);
            }
          }
        }
        break;
      case 2:
        //1 Row 2 note Velocity
        for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          byte MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
          if (abs(Potentiometer[MixerColumn] - pl1[pl1presetNr].note_Velo_graph[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (pl1[pl1presetNr].note_Velo_graph[MixerColumn] != Potentiometer[MixerColumn]) {
              drawPot(MixerColumnPos, CTRL_ROW_2, pl1[pl1presetNr].note_Velo_graph[MixerColumn], pl1[pl1presetNr].note_Velo_graph[MixerColumn], "Vel", trackColor[desired_instrument]);
              pl1[pl1presetNr].note_Velo_graph[MixerColumn] = Potentiometer[MixerColumn];
              pl1[pl1presetNr].note_Velo[MixerColumn] = pl1[pl1presetNr].note_Velo_graph[MixerColumn] / 127.00;
              mixer1.gain(0, pl1[pl1presetNr].note_Velo[0]);
              mixer1.gain(1, pl1[pl1presetNr].note_Velo[1]);
              mixer1.gain(2, pl1[pl1presetNr].note_Velo[2]);
              mixer1.gain(3, pl1[pl1presetNr].note_Velo[3]);
            }
          }
        }
        break;
    }
  }
  if (selectPage == PLUGIN1_PAGE2) {
    switch (lastPotRow) {
      case 0:
        if (abs(Potentiometer[0] - pl1[pl1presetNr].Filter1_Frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl1[pl1presetNr].Filter1_Frequency_graph != Potentiometer[0]) {
            pl1[pl1presetNr].Filter1_Frequency_graph = Potentiometer[0];
            pl1[pl1presetNr].Filter1_Frequency = note_frequency[pl1[pl1presetNr].Filter1_Frequency_graph];
            filter1.frequency(pl1[pl1presetNr].Filter1_Frequency);
            drawPot(CTRL_COL_0, CTRL_ROW_0, pl1[pl1presetNr].Filter1_Frequency_graph, pl1[pl1presetNr].Filter1_Frequency, "Freq", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[1] - pl1[pl1presetNr].Filter1_Resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl1[pl1presetNr].Filter1_Resonance_graph != Potentiometer[1]) {
            pl1[pl1presetNr].Filter1_Resonance_graph = Potentiometer[1];
            pl1[pl1presetNr].Filter1_Resonance = pl1[pl1presetNr].Filter1_Resonance_graph / 25.40;
            filter1.resonance(pl1[pl1presetNr].Filter1_Resonance);
            drawPot_2(CTRL_COL_1, CTRL_ROW_0, pl1[pl1presetNr].Filter1_Resonance_graph, pl1[pl1presetNr].Filter1_Resonance_graph, "Reso", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[2] - pl1[pl1presetNr].Filter1_Sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl1[pl1presetNr].Filter1_Sweep_graph != Potentiometer[2]) {
            pl1[pl1presetNr].Filter1_Sweep_graph = Potentiometer[2];
            pl1[pl1presetNr].Filter1_Sweep = pl1[pl1presetNr].Filter1_Sweep_graph / 18.14;
            filter1.octaveControl(pl1[pl1presetNr].Filter1_Sweep);
            drawPot_3(CTRL_COL_2, CTRL_ROW_0, pl1[pl1presetNr].Filter1_Sweep_graph, pl1[pl1presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[3] - pl1[pl1presetNr].Filter1_Type_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl1[pl1presetNr].Filter1_Type_graph != Potentiometer[3]) {
            pl1[pl1presetNr].Filter1_Type_graph = Potentiometer[3];
            pl1[pl1presetNr].Filter1_Type = pl1[pl1presetNr].Filter1_Type_graph / 43;
            selectFilterType(17, pl1[pl1presetNr].Filter1_Type);
            drawPot_4(CTRL_COL_3, CTRL_ROW_0, pl1[pl1presetNr].Filter1_Type_graph, pl1[pl1presetNr].Filter1_Type, "", trackColor[desired_track]);
            drawChar(CTRL_COL_3, 4, filterType[pl1[pl1presetNr].Filter1_Type], ILI9341_WHITE);
          }
        }
        break;
      case 1:
        if (abs(Potentiometer[0] - pl1[pl1presetNr].Env1_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl1[pl1presetNr].Env1_Attack_graph != Potentiometer[0]) {
            pl1[pl1presetNr].Env1_Attack_graph = Potentiometer[0];
            pl1[pl1presetNr].Env1_Attack = map(pl1[pl1presetNr].Env1_Attack_graph, 0, 127, 10, 700);
            envelope1.attack(pl1[pl1presetNr].Env1_Attack);
            envelope2.attack(pl1[pl1presetNr].Env1_Attack);
            drawPot(CTRL_COL_0, CTRL_ROW_1, pl1[pl1presetNr].Env1_Attack_graph, pl1[pl1presetNr].Env1_Attack, "Atck", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[1] - pl1[pl1presetNr].Env1_Decay_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl1[pl1presetNr].Env1_Decay_graph != Potentiometer[1]) {
            pl1[pl1presetNr].Env1_Decay_graph = Potentiometer[1];
            pl1[pl1presetNr].Env1_Decay = map(pl1[pl1presetNr].Env1_Decay_graph, 0, 127, 10, 700);
            envelope1.decay(pl1[pl1presetNr].Env1_Decay);
            envelope2.decay(pl1[pl1presetNr].Env1_Decay);
            drawPot_2(CTRL_COL_1, CTRL_ROW_1, pl1[pl1presetNr].Env1_Decay_graph, pl1[pl1presetNr].Env1_Decay, "Dec", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[2] - pl1[pl1presetNr].Env1_Sustain_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl1[pl1presetNr].Env1_Sustain_graph != Potentiometer[2]) {
            pl1[pl1presetNr].Env1_Sustain_graph = Potentiometer[2];
            pl1[pl1presetNr].Env1_Sustain = pl1[pl1presetNr].Env1_Sustain_graph / 127.00;
            envelope1.sustain(pl1[pl1presetNr].Env1_Sustain);
            envelope2.sustain(pl1[pl1presetNr].Env1_Sustain);
            drawPot_3(CTRL_COL_2, CTRL_ROW_1, pl1[pl1presetNr].Env1_Sustain_graph, pl1[pl1presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_track]);
          }
        }
        if (abs(Potentiometer[3] - pl1[pl1presetNr].Env1_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl1[pl1presetNr].Env1_Release_graph != Potentiometer[3]) {
            pl1[pl1presetNr].Env1_Release_graph = Potentiometer[3];
            pl1[pl1presetNr].Env1_Release = map(pl1[pl1presetNr].Env1_Release_graph, 0, 127, 180, 1200);
            envelope1.release(pl1[pl1presetNr].Env1_Release);
            envelope2.release(pl1[pl1presetNr].Env1_Release);
            drawPot_4(CTRL_COL_3, CTRL_ROW_1, pl1[pl1presetNr].Env1_Release_graph, pl1[pl1presetNr].Env1_Release, "Rel", trackColor[desired_track]);
          }
        }
        break;
    }
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
        if (abs(Potentiometer[0] - pl6[pl6presetNr].selected_file_raw_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (pl6[pl6presetNr].selected_file_raw_graph != Potentiometer[0]) {
            pl6[pl6presetNr].selected_file_raw_graph = Potentiometer[0];
            pl6[pl6presetNr].selected_file_raw = map(Potentiometer[0], 0, 127, 0, MAX_RAW_FILES);
            drawPot(CTRL_COL_0, CTRL_ROW_0, pl6[pl6presetNr].selected_file_raw_graph, pl6[pl6presetNr].selected_file_raw, "RAW", ILI9341_BLACK);
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
}

void myClock() {
  MIDItick++;
  usbMIDI.sendRealTime(usbMIDI.Clock);
  msecs = 0;
  if (MIDItick % 6 == 0) {
    tick_16++;
    step(tick_16);
    drawstepPosition(tick_16);
    //draw phrasenumber
    tft.fillRect(STEP_FRAME_W * POSITION_BAR_BUTTON + 1, 2, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 3, ILI9341_DARKGREY);
    tft.setTextColor(ILI9341_WHITE);
    tft.setFont(Arial_9);
    tft.setCursor(STEP_FRAME_W * POSITION_BAR_BUTTON + 4, 3);
    tft.print(phrase + 1);
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