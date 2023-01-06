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
            midi01.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
            midi02.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
            midi03.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
            midi04.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
            midi05.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
            midi06.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
            dsend_noteOff[i] = true;
          }
        } else {
          if (dsend_noteOff[i]) {
            usbMIDI.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            MIDI.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            midi01.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            midi02.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            midi03.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            midi04.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            midi05.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
            midi06.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
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
            midi01.sendNoteOn(noteNumber, track[track_number].MIDI_velocity, track[track_number].MIDIchannel);
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
            midi01.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[current - 1] + track[track_number].NoteOffset[phrase], VELOCITYOFF, track[track_number].MIDIchannel);
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