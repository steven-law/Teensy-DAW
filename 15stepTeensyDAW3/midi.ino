///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                         SEQUENCER CALLBACKS                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////



void drawbarPosition() {
  for (int songPointerThickness = 0; songPointerThickness <= POSITION_POINTER_THICKNESS; songPointerThickness++) {
    //
    tft.drawPixel(barClock + STEP_FRAME_W * 2, (SONG_POSITION_POINTER_Y + songPointerThickness), ILI9341_GREEN);
    //
    tft.drawFastHLine(pixelbarClock * phraseSegmentLength + STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y + songPointerThickness, phraseSegmentLength, ILI9341_GREEN);
    tft.drawFastHLine((pixelbarClock - 1) * phraseSegmentLength + STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y + songPointerThickness, phraseSegmentLength, ILI9341_DARKGREY);
  }
  if (barClock % 16 == 0) {
    pixelbarClock = 0;
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



// called when the step position changes. both the current
// position and last are passed to the callback
void step(int current, int last) {




  //differnt things happening while the clock is running
  if (current == 0) {
    barClock++;
    pixelbarClock++;
    phrase++;
    drawbarPosition();
    //draw phrasenumber
    tft.fillRect(STEP_FRAME_W * POSITION_BAR_BUTTON + 1, 2, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 3, ILI9341_DARKGREY);
    tft.setTextColor(ILI9341_WHITE);
    tft.setFont(Arial_9);
    tft.setCursor(STEP_FRAME_W * POSITION_BAR_BUTTON + 4, 3);
    tft.print(phrase);


    //assigning the current clip from the arrangment array for each track
    for (int instruments = 0; instruments < 8; instruments++) {
      if (track[instruments].arrangment1[phrase] == 8) {
        track[instruments].clip_songMode = 8;
      }
      track[instruments].clip_songMode = track[instruments].arrangment1[phrase];
    }





    if (barClock == 255) {
      seq.stop();
      seq.panic();
      barClock = 0;
      pixelbarClock = 0;
      phrase = 0;
      tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H * 14, STEP_FRAME_W * 16, STEP_FRAME_H, ILI9341_DARKGREY);
    }
    if (phrase == end_of_loop-1) {
      phrase = -1;
      pixelbarClock = 0;
      barClock = -1;
      //      tft.fillRect(STEP_FRAME_W * 2, STEP_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
      //      tft.fillRect(STEP_FRAME_W * 2, SONG_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
      //      tft.fillRect(STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
    }
  }






  //send midinotes for drumtrack #1
  if (!track[0].solo_mutes_state) {
    if (!track[0].mute_state) {

      for (int i = 0; i < 12; i++) {
        if (channel1Clip[ch1Clip][i][current]) {
          usbMIDI.sendNoteOn(drumnote[i], track[0].velocity_ON, track[0].MIDIchannel);
        } else {
          usbMIDI.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
        }
      }
      //play drumplugin when midichannel = 18
      if (track[0].MIDIchannel == 18) {
        if (channel1Clip[ch1Clip][0][current]) {
          playSdWav1.play("P0.WAV");
        }
        if (channel1Clip[ch1Clip][1][current]) {
          playSdWav2.play("P1.WAV");
        }
        if (channel1Clip[ch1Clip][2][current]) {
          playSdWav3.play("P2.WAV");
        }
        if (channel1Clip[ch1Clip][3][current]) {
          playSdWav4.play("P3.WAV");
        }
        if (channel1Clip[ch1Clip][4][current]) {
          playSdWav5.play("P4.WAV");
        }
        if (channel1Clip[ch1Clip][5][current]) {
          playSdWav6.play("P5.WAV");
        }
        if (channel1Clip[ch1Clip][6][current]) {
          playSdWav7.play("P6.WAV");
        }
        if (channel1Clip[ch1Clip][7][current]) {
          playSdWav8.play("P7.WAV");
        }
        if (channel1Clip[ch1Clip][8][current]) {
          playSdWav9.play("P8.WAV");
        }
        if (channel1Clip[ch1Clip][9][current]) {
          playSdWav10.play("P9.WAV");
        }
        if (channel1Clip[ch1Clip][10][current]) {
          playSdWav11.play("P10.WAV");
        }
        if (channel1Clip[ch1Clip][11][current]) {
          playSdWav12.play("P11.WAV");
        }
      }

      //play Memory drumplugin when midichannel = 20
      if (track[0].MIDIchannel == 20) {
        if (channel1Clip[ch1Clip][0][current]) {
          playMem1.play(AudioSampleKick);
        }
        if (channel1Clip[ch1Clip][1][current]) {
          playMem2.play(AudioSampleSnare);
        }
        if (channel1Clip[ch1Clip][2][current]) {
          playMem3.play(AudioSampleP2);
        }
        if (channel1Clip[ch1Clip][3][current]) {
          playMem4.play(AudioSampleHihat);
        }
        if (channel1Clip[ch1Clip][4][current]) {
          playMem5.play(AudioSampleCashregister);
        }
        if (channel1Clip[ch1Clip][5][current]) {
          playMem6.play(AudioSampleTomtom);
        }
        if (channel1Clip[ch1Clip][6][current]) {
          //playSdWav7.play("P6.WAV");
        }
        if (channel1Clip[ch1Clip][7][current]) {
          //playSdWav8.play("P7.WAV");
        }
        if (channel1Clip[ch1Clip][8][current]) {
          //playSdWav9.play("P8.WAV");
        }
        if (channel1Clip[ch1Clip][9][current]) {
          //playSdWav10.play("P9.WAV");
        }
        if (channel1Clip[ch1Clip][10][current]) {
          //playSdWav11.play("P10.WAV");
        }
        if (channel1Clip[ch1Clip][11][current]) {
          //playSdWav12.play("P11.WAV");
        }
      }
      //play Memory drumplugin when midichannel = 20
      if (track[0].MIDIchannel == 23) {
        if (channel1Clip[ch1Clip][0][current]) {
          pl7drum1.noteOn();
        }
        if (channel1Clip[ch1Clip][1][current]) {
          pl7envelope1.noteOn();
        } else {
          pl7envelope1.noteOff();
        }
        if (channel1Clip[ch1Clip][2][current]) {
          pl7envelope2.noteOn();
          pl7envelope3.noteOn();
        } else {
          pl7envelope2.noteOff();
          pl7envelope3.noteOff();
        }
        if (channel1Clip[ch1Clip][3][current]) {
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
    if (!track[track_number].mute_state) {
      byte noteNumber = ctrack[track_number].sequence[track[track_number].clip_songMode].step[current];
      if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[current] > VALUE_NOTEOFF) {


        if (track[track_number].MIDIchannel < 17) {
          usbMIDI.sendNoteOn(noteNumber, track[track_number].velocity_ON, track[track_number].MIDIchannel);
        }

        if (track[track_number].MIDIchannel == 17) {
          waveform1.frequency(note_frequency[noteNumber + pl1[pl1presetNr].note_Offset[0]]);
          waveform2.frequency(note_frequency[noteNumber + pl1[pl1presetNr].note_Offset[1]]);
          waveform3.frequency(note_frequency[noteNumber + pl1[pl1presetNr].note_Offset[2]]);
          waveform4.frequency(note_frequency[noteNumber + pl1[pl1presetNr].note_Offset[3]]);
          envelope1.noteOn();
          envelope2.noteOn();
        }
        if (track[track_number].MIDIchannel == 19) {
          pl3waveform1.frequency(note_frequency[noteNumber]);
          envelope1.noteOn();
          envelope2.noteOn();
        }
        if (track[track_number].MIDIchannel == 21) {
          double note_ratio = pow(2.0, ((double)(noteNumber - SAMPLE_ROOT) / 12.0));
          playSdPitch1.setPlaybackRate(note_ratio);
          playSdPitch1.playWav(WAV_files[pl5[pl5presetNr].selected_file]);
          pl5envelope1.noteOn();
          pl5envelope2.noteOn();
        }
        if (track[track_number].MIDIchannel == 22) {
          double note_ratio = pow(2.0, ((double)(noteNumber - SAMPLE_ROOT) / 12.0));
          playSdPitch2.setPlaybackRate(note_ratio);
          playSdPitch2.playRaw(RAW_files[pl6[pl6presetNr].selected_raw_file], 1);
          pl6envelope1.noteOn();
          pl6envelope2.noteOn();
        }
        if (track[track_number].MIDIchannel == 24) {
          pl3waveform1.frequency(note_frequency[noteNumber]);
          envelope1.noteOn();
          envelope2.noteOn();
        }
      } else {
        usbMIDI.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[last], VELOCITYOFF, track[track_number].MIDIchannel);
        envelope1.noteOff();
        envelope2.noteOff();
        pl3envelope1.noteOff();
        pl3envelope2.noteOff();
        pl5envelope1.noteOff();
        pl5envelope2.noteOff();
        pl6envelope1.noteOff();
        pl6envelope2.noteOff();
        pl8envelope1.noteOff();
        pl8envelope2.noteOff();
      }
    }
  }


  drawstepPosition(current);

  for (int songPointerThickness = 0; songPointerThickness <= POSITION_POINTER_THICKNESS; songPointerThickness++) {
    if (current == 0) {
      tft.drawFastHLine(STEP_FRAME_W * 17, STEP_POSITION_POINTER_Y + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);
    }
  }


  //usbMIDI.sendControlChange(123, 0, 2);
}




void midiCC_view_Static(byte mixerpage, byte desired_instrument) {
  clearWorkSpace();
  draw_sub_page_buttons(1);
  drawActiveRect(18, 3, 2, 2, track[desired_instrument].sendCC, "Send", ILI9341_LIGHTGREY);

  for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    byte mixerColumnPos = ((MixerColumn + 1) * 4) - 1;
    drawPotCC(mixerColumnPos, 3, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_number_row_1[MixerColumn], trackColor[desired_instrument]);
    drawPotCC(mixerColumnPos, 7, track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);
    drawPotCC(mixerColumnPos, 11, track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_number_row_3[MixerColumn], trackColor[desired_instrument]);
  }
}

void midiCCpage1_Dynamic(byte desired_instrument) {
  if (ts.touched() || !buttons[6].read()) {

    if (gridTouchX >= 18 && gridTouchY == 3 || gridTouchX >= 18 && gridTouchY == 4) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        drawActiveRect(18, 3, 2, 2, track[desired_instrument].sendCC, "Send", ILI9341_LIGHTGREY);
        if (track[desired_instrument].sendCC) {
          track[desired_instrument].sendCC = false;
        } else if (!track[desired_instrument].sendCC) {
          track[desired_instrument].sendCC = true;
        }
      }
    }

    //Row1
    if (gridTouchY == 3) {
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte mixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (gridTouchX == mixerColumnPos || gridTouchX == mixerColumnPos + 1) {
          drawPotCC(mixerColumnPos, 3, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_number_row_1[MixerColumn], trackColor[desired_instrument]);
          usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].MIDIchannel);
          if (abs(Potentiometer1 - track[desired_instrument].midicc_value_row_1[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            track[desired_instrument].midicc_value_row_1[MixerColumn] = Potentiometer1;
          }
        }
      }
    }
    if (gridTouchY == 4) {
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte mixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (gridTouchX == mixerColumnPos || gridTouchX == mixerColumnPos + 1) {
          drawPotCC(mixerColumnPos, 3, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_number_row_1[MixerColumn], trackColor[desired_instrument]);
          if (abs(Potentiometer1 - track[desired_instrument].midicc_number_row_1[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            track[desired_instrument].midicc_number_row_1[MixerColumn] = Potentiometer1;
          }
        }
      }
    }

    //Row2
    if (gridTouchY == 7) {
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte mixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (gridTouchX == mixerColumnPos || gridTouchX == mixerColumnPos + 1) {
          drawPotCC(mixerColumnPos, 7, track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);
          usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].MIDIchannel);

          if (abs(Potentiometer1 - track[desired_instrument].midicc_value_row_2[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            track[desired_instrument].midicc_value_row_2[MixerColumn] = Potentiometer1;
          }
        }
      }
    }
    if (gridTouchY == 8) {
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte mixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (gridTouchX == mixerColumnPos || gridTouchX == mixerColumnPos + 1) {
          drawPotCC(mixerColumnPos, 7, track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);
          if (abs(Potentiometer1 - track[desired_instrument].midicc_number_row_2[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            track[desired_instrument].midicc_number_row_2[MixerColumn] = Potentiometer1;
          }
        }
      }
    }
    //Row3
    if (gridTouchY == 11) {
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte mixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (gridTouchX == mixerColumnPos || gridTouchX == mixerColumnPos + 1) {
          drawPotCC(mixerColumnPos, 11, track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_number_row_3[MixerColumn], trackColor[desired_instrument]);
          usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].MIDIchannel);
          if (abs(Potentiometer1 - track[desired_instrument].midicc_value_row_3[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            track[desired_instrument].midicc_value_row_3[MixerColumn] = Potentiometer1;
          }
        }
      }
    }
    if (gridTouchY == 12) {
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        byte mixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (gridTouchX == mixerColumnPos || gridTouchX == mixerColumnPos + 1) {
          drawPotCC(mixerColumnPos, 11, track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_number_row_3[MixerColumn], trackColor[desired_instrument]);
          if (abs(Potentiometer1 - track[desired_instrument].midicc_number_row_3[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            track[desired_instrument].midicc_number_row_3[MixerColumn] = Potentiometer1;
          }
        }
      }
    }
  }
}