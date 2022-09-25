///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                         SEQUENCER CALLBACKS                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////





// called when the step position changes. both the current
// position and last are passed to the callback
void step(int current, int last) {



  //send midinotes for drumtrack #1
  for (int i = 0; i < 12; i++) {
    if (channel1Clip[ch1Clip][i][current] == HIGH) {
      usbMIDI.sendNoteOn(drumnote[i], VELOCITY, track[0].MIDIchannel);
    } else {
      usbMIDI.sendNoteOff(drumnote[i], VELOCITYOFF, track[0].MIDIchannel);
    }
  }
  //play drumplugin when midichannel = 18
  if (track[0].MIDIchannel == 18) {
    if (channel1Clip[ch1Clip][0][current] == HIGH) {
      playSdWav1.play("P0.WAV");
    }
    if (channel1Clip[ch1Clip][1][current] == HIGH) {
      playSdWav2.play("P1.WAV");
    }
    if (channel1Clip[ch1Clip][2][current] == HIGH) {
      playSdWav3.play("P2.WAV");
    }
    if (channel1Clip[ch1Clip][3][current] == HIGH) {
      playSdWav4.play("P3.WAV");
    }
    if (channel1Clip[ch1Clip][4][current] == HIGH) {
      playSdWav5.play("P4.WAV");
    }
    if (channel1Clip[ch1Clip][5][current] == HIGH) {
      playSdWav6.play("P5.WAV");
    }
    if (channel1Clip[ch1Clip][6][current] == HIGH) {
      playSdWav7.play("P6.WAV");
    }
    if (channel1Clip[ch1Clip][7][current] == HIGH) {
      playSdWav8.play("P7.WAV");
    }
    if (channel1Clip[ch1Clip][8][current] == HIGH) {
      playSdWav9.play("P8.WAV");
    }
    if (channel1Clip[ch1Clip][9][current] == HIGH) {
      playSdWav10.play("P9.WAV");
    }
    if (channel1Clip[ch1Clip][10][current] == HIGH) {
      playSdWav11.play("P10.WAV");
    }
    if (channel1Clip[ch1Clip][11][current] == HIGH) {
      playSdWav12.play("P11.WAV");
    }
  }

  //play Memory drumplugin when midichannel = 20
  if (track[0].MIDIchannel == 20) {
    if (channel1Clip[ch1Clip][0][current] == HIGH) {
      playMem1.play(AudioSampleKick);
    }
    if (channel1Clip[ch1Clip][1][current] == HIGH) {
      playMem1.play(AudioSampleSnare);
    }
    if (channel1Clip[ch1Clip][2][current] == HIGH) {
      playMem1.play(AudioSampleP2);
    }
    if (channel1Clip[ch1Clip][3][current] == HIGH) {
      playMem1.play(AudioSampleHihat);
    }
    if (channel1Clip[ch1Clip][4][current] == HIGH) {
      playMem1.play(AudioSampleCashregister);
    }
    if (channel1Clip[ch1Clip][5][current] == HIGH) {
      playMem1.play(AudioSampleTomtom);
    }
    if (channel1Clip[ch1Clip][6][current] == HIGH) {
      //playSdWav7.play("P6.WAV");
    }
    if (channel1Clip[ch1Clip][7][current] == HIGH) {
      //playSdWav8.play("P7.WAV");
    }
    if (channel1Clip[ch1Clip][8][current] == HIGH) {
      //playSdWav9.play("P8.WAV");
    }
    if (channel1Clip[ch1Clip][9][current] == HIGH) {
      //playSdWav10.play("P9.WAV");
    }
    if (channel1Clip[ch1Clip][10][current] == HIGH) {
      //playSdWav11.play("P10.WAV");
    }
    if (channel1Clip[ch1Clip][11][current] == HIGH) {
      //playSdWav12.play("P11.WAV");
    }
  }

  //********************************************************************************
  //track 2-8 are intended to be (monophonic) melodic sequencer
  //in this file we let the 15step sequencer do all the midi and note trigering stuff


  //10) so if you add a melodic plugin its best to add all the noteOn / Off functions here
  //let the plugin only play when the midi channel for a track is set to this plugin
  // do this with:
  //if (track[track_number].MIDIchannel == 17) {}

  //you can calculate the needed frequencys with a formula or use my note_frequency array
  //current notes are stored in a struct with a "step" array
  // call the frequency for your module with:
  //"module".frequency(note_frequency[ctrack[track_number].sequence[track[track_number].clip_songMode].step[current]]);

  //if you select your corresponding midi(plugin-) channel for a track and have set some notes to the grid, you should hear your sequence now. (after uploading up to this stage of course)
  //If you dont hear anything try an other plugin and switch back to yours


  // if you want to change your parameters and you certainly will, head back to your plugin ino file to add graphics and controls.

  //send midinotes for melodic track #2 -8
  for (int track_number = 1; track_number <= 7; track_number++) {
    if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[current] > VALUE_NOTEOFF) {
      usbMIDI.sendNoteOn(ctrack[track_number].sequence[track[track_number].clip_songMode].step[current], VELOCITY, track[track_number].MIDIchannel);
      if (track[track_number].MIDIchannel == 17) {
        waveform1.frequency(note_frequency[ctrack[track_number].sequence[track[track_number].clip_songMode].step[current] + note1_Offset]);
        waveform2.frequency(note_frequency[ctrack[track_number].sequence[track[track_number].clip_songMode].step[current] + note2_Offset]);
        waveform3.frequency(note_frequency[ctrack[track_number].sequence[track[track_number].clip_songMode].step[current] + note3_Offset]);
        waveform4.frequency(note_frequency[ctrack[track_number].sequence[track[track_number].clip_songMode].step[current] + note4_Offset]);
        envelope1.noteOn();
        envelope2.noteOn();
      }
     /* if (track[track_number].MIDIchannel == 19) {
        pl3waveform1.frequency(note_frequency[ctrack[track_number].sequence[track[track_number].clip_songMode].step[current]]);
        pl3envelope1.noteOn();
        pl3envelope2.noteOn();
      }*/
    } else {
      usbMIDI.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[last], VELOCITYOFF, track[track_number].MIDIchannel);
      envelope1.noteOff();
      envelope2.noteOff();
      pl3envelope1.noteOff();
      pl3envelope2.noteOff();
    }
  }




  //draw the songpointer positions
  for (int songPointerThickness = 0; songPointerThickness <= POSITION_POINTER_THICKNESS; songPointerThickness++) {
    for (int stepwidth = 1; stepwidth <= 16; stepwidth++) {
      tft.drawFastHLine(current * stepwidth + STEP_FRAME_W * 2, STEP_POSITION_POINTER_Y + songPointerThickness, STEP_FRAME_W, ILI9341_GREEN);
      tft.drawFastHLine(last * stepwidth + STEP_FRAME_W * 2, STEP_POSITION_POINTER_Y + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);
    }
  }
  for (int songPointerThickness = 0; songPointerThickness <= POSITION_POINTER_THICKNESS; songPointerThickness++) {
    if (current == 0) {
      tft.drawFastHLine(STEP_FRAME_W * 17, STEP_POSITION_POINTER_Y + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);
    }
  }

  //differnt things happening while the clock is running
  if (current == 0) {

    barClock++;
    pixelbarClock++;
    tft.fillRect(STEP_FRAME_W * POSITION_BAR_BUTTON - 1, 2, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 3, ILI9341_DARKGREY);
    tft.setTextColor(ILI9341_WHITE);
    tft.setFont(Arial_9);
    tft.setCursor(STEP_FRAME_W * POSITION_BAR_BUTTON + 2, 3);
    tft.print(barClock + 1);
    for (int songPointerThickness = 0; songPointerThickness <= POSITION_POINTER_THICKNESS; songPointerThickness++) {
      tft.drawPixel(barClock + STEP_FRAME_W * 2, (SONG_POSITION_POINTER_Y + songPointerThickness), ILI9341_GREEN);
      tft.drawFastHLine(pixelbarClock * phraseSegmentLength + STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y + songPointerThickness, phraseSegmentLength, ILI9341_GREEN);
      tft.drawFastHLine((pixelbarClock - 1) * phraseSegmentLength + STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y + songPointerThickness, phraseSegmentLength, ILI9341_DARKGREY);
    }

    if (barClock % 2 == 0) {
      phrase++;
      //Serial.println((clip[8][track[8].clip_songMode][current]));
      //Serial.println(arrangment1[7][phrase]);
      for (int instruments = 0; instruments < 8; instruments++) {
        if (arrangment1[instruments][phrase] == 8) {
          track[instruments].clip_songMode = 8;
        }
        track[instruments].clip_songMode = arrangment1[instruments][phrase];
      }
      if (pixelbarClock == end_of_loop / phraseSegmentLength) {
        pixelbarClock = 0;
        tft.fillRect(STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y, STEP_FRAME_W * 20, 4, ILI9341_DARKGREY);
      }
    }
    if (barClock == 255) {
      seq.stop();
      seq.panic();
      barClock = 0;
      phrase = 0;
      tft.fillRect(STEP_FRAME_W * 2, STEP_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
      tft.fillRect(STEP_FRAME_W * 2, SONG_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
      tft.fillRect(STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
    }
    if (phrase >= end_of_loop) {
      phrase = 0;
      barClock = 0;
      //      tft.fillRect(STEP_FRAME_W * 2, STEP_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
      //      tft.fillRect(STEP_FRAME_W * 2, SONG_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
      //      tft.fillRect(STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
    }
  }
}