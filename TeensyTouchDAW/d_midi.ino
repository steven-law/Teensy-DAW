///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                         SEQUENCER CALLBACKS                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

//this page contains some MIDI related functions, like
//what to do when the clock is
//midicc plugin pages
//start and stop sequencerplaying
//and what happens with incoming midicc   ->needs some love



void process_clock() {


  if (master_clock.process_MIDItick()) {
    seq_MIDItick++;
    //Serial.printf("bar:%d, step:%d, tick:%d\n", master_clock.barTick, master_clock.stepTick, master_clock.MIDItick);

    //clockstuff before we let the notes fly
    //clockdivision
    for (int i = 0; i < NUM_TRACKS; i++) {
      if (seq_MIDItick % allTracks[i]->clockDivision == 0) {
        track[i].MIDItick++;
      }
    }
    //MIDItick_16++, SerialPrints for debugging;
    for (int i = 0; i < NUM_TRACKS; i++) {
      if (track[i].MIDItick % TICKS_PER_STEP == 0) {
        track[i].MIDItick_16++;
        //Serial.printf("Tr= %d, Ti= %d\n", i, track[i].MIDItick_16);
        /*
        for (int polys = polys; polys < MAX_VOICES; polys++) {
          NFX4reset[polys]++;
        }
        */
        if (debugTime) {
          SerialPrintSeq();
        }
      }
    }
    //reset MIDItick every bar
    for (int i = 0; i < NUM_TRACKS; i++) {
      if (track[i].MIDItick == TICKS_PER_BAR) {
        track[i].MIDItick = 0;
        //track[i].MIDItick_16 = 0;  //!!!!try this tomorrow
      }
    }

    //reset MIDItick_16 when NUM_STEPS 16 is reached
    for (int i = 0; i < NUM_TRACKS; i++) {
      if (track[i].MIDItick_16 == NUM_STEPS) {
        track[i].MIDItick_16 = 0;
      }
    }

    //reset barcounter at end of song/loop
    if (phrase == MAX_PHRASES || phrase == master_clock.endOfLoop) {
      //master_clock.set_playing(false);
      phrase = master_clock.startOfLoop - 1;
      seq_MIDItick = 0;
      pixelphrase = 0;
      for (int i = 0; i < NUM_TRACKS; i++) {
        track[i].MIDItick = 0;
        track[i].MIDItick_16 = 0;
      }
      tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H * 14, STEP_FRAME_W * 16, STEP_FRAME_H, ILI9341_DARKGREY);
    }

    //reset steptick every bar
    //beatcomponents
    if (seq_MIDItick % TICKS_PER_BAR == 0) {
      phrase++;
      pixelphrase++;
      seq_MIDItick = 0;
      showSerialonce = true;
      beatComponents();
      if (debugTime) {
        if (showSerialonce) {
          SerialPrintPlugins();
        }
      }
    }
    /*
    //MIDItick_16++, SerialPrints for debugging;
    for (int i = 0; i < NUM_TRACKS; i++) {
      if (track[i].MIDItick % TICKS_PER_STEP == 0) {
        Serial.printf("Phrase:%d, Tr= %d, Ti= %d, St= %d\n", phrase, i, track[i].MIDItick, track[i].MIDItick_16);
      }
    }
    */
    //seqModes note "freeing"
    for (int i = 0; i < NUM_TRACKS; i++) {
      if (!allTracks[i]->muteThruSolo) {
        if (!allTracks[i]->muted) {
          //stepseqeucer for melodic track
          if (allTracks[i]->seqMode == 0) {
            //if the actual step is high, play the notes
            for (int polys = 0; polys < MAX_VOICES; polys++) {
              if (ctrack[i].sequence[track[i].clip_songMode].tick[track[i].MIDItick].voice[polys] > VALUE_NOTEOFF) {
                track[i].playNoteOnce[polys] = true;
                track[i].notePressed[polys] = true;
                track[i].notePlayed[polys] = ctrack[i].sequence[track[i].clip_songMode].tick[track[i].MIDItick].voice[polys] + track[i].NoteOffset[phrase];
                track[i].MIDI_velocity[polys] = allTracks[i]->gainVol * (float)(track[i].volume[phrase] / 127.00) * (float)(ctrack[i].sequence[track[i].clip_songMode].tick[track[i].MIDItick].velo[polys] / 127.00);
                pluginVolume(track[i].MIDIchannel, track[i].MIDI_velocity[polys] / 127.00);
              }
              if (ctrack[i].sequence[track[i].clip_songMode].tick[track[i].MIDItick].voice[polys] == VALUE_NOTEOFF) {
                track[i].notePressed[polys] = false;
              }
            }
          }
          //dropseq
          if (allTracks[i]->seqMode == 1) {

            if (ctrack[i].sequence[track[i].clip_songMode].tick[track[i].MIDItick].voice[0] > VALUE_NOTEOFF) {
              if (track[i].tick_true[0]) {
                track[i].tick_true[0] = false;
                byte maxVal = 0;
                byte maxValIndex;
                byte octave;
                static byte analogReadArray[12];
                //determine the note with the highest "weight"
                for (int d = 0; d < 12; d++) {
                  if (analogReadArray[d] > maxVal) {
                    maxVal = analogReadArray[d];
                    maxValIndex = d;
                  }
                }
                //set an octave range
                octave = random(NFX2[NFX2presetNr].Pot_Value[2], NFX2[NFX2presetNr].Pot_Value[3]);
                //Set the notes free
                track[i].playNoteOnce[0] = true;
                track[i].notePressed[0] = true;
                track[i].notePlayed[0] = (maxValIndex) + (octave * 12) + track[i].NoteOffset[phrase];
                track[i].MIDI_velocity[0] = allTracks[i]->gainVol * (float)(track[i].volume[phrase] / 127.00) * (float)(ctrack[i].sequence[track[i].clip_songMode].tick[track[i].MIDItick].velo[0] / 127.00);
                pluginVolume(track[i].MIDIchannel, track[i].MIDI_velocity[0] / 127.00);
                analogReadArray[maxValIndex] = (analogReadArray[maxValIndex] - NFX2[NFX2presetNr].Pot_Value[0]);
                //if one of the note "weights" has reached the "tide"Pot_Value[1] level, we recall all "weights" from the pot positions
                if (analogReadArray[maxValIndex] <= NFX2[NFX2presetNr].Pot_Value[1]) {
                  for (int d = 0; d < 12; d++) {
                    analogReadArray[d] = NFX2[NFX2presetNr].Pot_Value[d + 4];
                  }
                }
              }
            }

            //NoteOff
            if (ctrack[i].sequence[track[i].clip_songMode].tick[track[i].MIDItick].voice[0] == VALUE_NOTEOFF) {
              track[i].notePressed[0] = false;
              track[i].tick_true[0] = true;
            }
          }
          //random
          if (allTracks[i]->seqMode == 2) {
            //if the actual step is high, play the notes
            if (ctrack[i].sequence[track[i].clip_songMode].tick[track[i].MIDItick].voice[0] > VALUE_NOTEOFF) {
              if (track[i].tick_true[0]) {
                track[i].tick_true[0] = false;
                int NFX3Oct1 = random(NFX3[NFX3presetNr].Pot_Value[2], NFX3[NFX3presetNr].Pot_Value[3]);
                track[i].notePlayed[0] = random(0, 11) + (NFX3Oct1 * 12);
                track[i].MIDI_velocity[0] = allTracks[i]->gainVol * (float)(track[i].volume[phrase] / 127.00) * (float)(random(NFX3[NFX3presetNr].Pot_Value[0], NFX3[NFX3presetNr].Pot_Value[1]) / 127.00);
                pluginVolume(track[i].MIDIchannel, track[i].MIDI_velocity[0] / 127.00);
                track[i].playNoteOnce[0] = true;
                track[i].notePressed[0] = true;
              }
            }
            //NoteOff
            if (ctrack[i].sequence[track[i].clip_songMode].tick[track[i].MIDItick].voice[0] == VALUE_NOTEOFF) {
              track[i].notePressed[0] = false;
              track[i].tick_true[0] = true;
            }
          }
          //Polyrhytm
          if (allTracks[i]->seqMode == 3) {
            for (int polys = 0; polys < MAX_VOICES; polys++) {
              NFX4reset[polys]++;
              if (NFX4reset[polys] >= NFX4[NFX4presetNr].Pot_Value[polys]) {
                NFX4reset[polys] = 0;
              }
              //if the actual step is high, play the notes d
              if (ctrack[i].sequence[track[i].clip_songMode].tick[NFX4reset[polys]].voice[polys] > VALUE_NOTEOFF) {
                track[i].playNoteOnce[polys] = true;
                track[i].notePressed[polys] = true;
                track[i].notePlayed[polys] = ctrack[i].sequence[track[i].clip_songMode].tick[NFX4reset[polys]].voice[polys] + track[i].NoteOffset[phrase];
                track[i].MIDI_velocity[polys] = allTracks[i]->gainVol * (float)(track[i].volume[phrase] / 127.00) * (float)(random(NFX4[track[i].clip_songMode].Pot_Value[12], NFX4[track[i].clip_songMode].Pot_Value[13]) / 127.00);
                pluginVolume(track[i].MIDIchannel, track[i].MIDI_velocity[polys] / 127.00);
              }

              //NoteOff
              if (ctrack[i].sequence[track[i].clip_songMode].tick[NFX4reset[polys]].voice[polys] == VALUE_NOTEOFF) {
                track[i].notePressed[polys] = false;
              }
            }
          }
          //grids
          if (allTracks[i]->seqMode == 4) {
            if (track[i].clip_songMode < 8) {

              for (int polys = 0; polys < MAX_VOICES; polys++) {
                if (track[i].tick_true[polys]) {
                  track[i].tick_true[polys] = false;
                  if (beatArray[NFX1[track[i].clip_songMode].Pot_Value[polys]][track[i].MIDItick_16]) {
                    Serial.printf("Tick16 in grids = %d\n", track[i].MIDItick_16);
                    track[i].playNoteOnce[polys] = true;
                    track[i].notePressed[polys] = true;
                    track[i].notePlayed[polys] = polys + (allTracks[i]->shownOctaves * 12);
                    track[i].MIDI_velocity[polys] = allTracks[i]->gainVol * (float)(track[i].volume[phrase] / 127.00) * (float)(random(NFX1[track[i].clip_songMode].Pot_Value[12], NFX1[track[i].clip_songMode].Pot_Value[13]) / 127.00);
                    pluginVolume(track[i].MIDIchannel, track[i].MIDI_velocity[polys] / 127.00);
                  }
                }
                //NoteOff

                if (!beatArray[NFX1[track[i].clip_songMode].Pot_Value[polys]][track[i].MIDItick_16]) {
                  track[i].notePressed[polys] = false;
                  track[i].tick_true[polys] = true;
                }
              }
            }
          }
        }
      }
    }
    master_clock.drawPositionPointers();
    //Serial.printf("phrase:%d, track-0 MIDItick_16:%d,MIDItick:%d, seq_MIDItick: %d\n", phrase, track[0].MIDItick_16, track[0].MIDItick, seq_MIDItick);
  }
}


void midiCC_view_Static(int mixerpage, byte desired_instrument) {
  clearWorkSpace();


  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
    drawPotCC(MixerColumn, 0, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], trackColor[desired_instrument]);
    drawNrInRect(MixerColumnPos, CTRL_ROW_0 + 1, track[desired_instrument].midicc_number_row_1[MixerColumn], trackColor[desired_instrument]);

    drawPotCC(MixerColumn, 1, track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], trackColor[desired_instrument]);
    drawNrInRect(MixerColumnPos, CTRL_ROW_1 + 1, track[desired_instrument].midicc_number_row_2[MixerColumn], trackColor[desired_instrument]);

    drawPotCC(MixerColumn, 2, track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], trackColor[desired_instrument]);
    drawNrInRect(MixerColumnPos, CTRL_ROW_2 + 1, track[desired_instrument].midicc_number_row_3[MixerColumn], trackColor[desired_instrument]);

    drawPotCC(MixerColumn, 3, track[desired_instrument].midicc_value_row_4[MixerColumn], track[desired_instrument].midicc_value_row_4[MixerColumn], trackColor[desired_instrument]);
    drawNrInRect(MixerColumnPos, CTRL_ROW_3 + 1, track[desired_instrument].midicc_number_row_4[MixerColumn], trackColor[desired_instrument]);
  }
}

void midiCCpage1_Dynamic(int desired_instrument) {
  switch (lastPotRow) {
    case 0:
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (!button[14]) {
          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_value_row_1[MixerColumn] = constrain((track[desired_instrument].midicc_value_row_1[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawPotCC(MixerColumn, lastPotRow, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], trackColor[desired_instrument]);
            usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].MIDIchannel);
            MIDI.sendControlChange(track[desired_instrument].midicc_number_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].MIDIchannel);
          }

          /*if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_value_row_1[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_value_row_1[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_value_row_1[MixerColumn] = Potentiometer[MixerColumn];
              drawPotCC(MixerColumn, 0, track[desired_instrument].midicc_value_row_1[MixerColumn], track[desired_instrument].midicc_value_row_1[MixerColumn], trackColor[desired_instrument]);
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

      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (!button[14]) {

          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_value_row_2[MixerColumn] = constrain((track[desired_instrument].midicc_value_row_2[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawPotCC(MixerColumn, lastPotRow, track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], trackColor[desired_instrument]);
            usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].MIDIchannel);
          }

          /* if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_value_row_2[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_value_row_2[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_value_row_2[MixerColumn] = Potentiometer[MixerColumn];
              drawPotCC(MixerColumn, lastPotRow, track[desired_instrument].midicc_value_row_2[MixerColumn], track[desired_instrument].midicc_value_row_2[MixerColumn], trackColor[desired_instrument]);
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

      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (!button[14]) {

          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_value_row_3[MixerColumn] = constrain((track[desired_instrument].midicc_value_row_3[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawPotCC(MixerColumn, lastPotRow, track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], trackColor[desired_instrument]);
            usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].MIDIchannel);
          }


          /* if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_value_row_3[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_value_row_3[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_value_row_3[MixerColumn] = Potentiometer[MixerColumn];
              drawPotCC(MixerColumn, lastPotRow, track[desired_instrument].midicc_value_row_3[MixerColumn], track[desired_instrument].midicc_value_row_3[MixerColumn], trackColor[desired_instrument]);
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
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
        if (!button[14]) {

          if (enc_moved[MixerColumn]) {
            track[desired_instrument].midicc_value_row_4[MixerColumn] = constrain((track[desired_instrument].midicc_value_row_4[MixerColumn] + encoded[MixerColumn]), 0, 127);
            drawPotCC(MixerColumn, lastPotRow, track[desired_instrument].midicc_value_row_4[MixerColumn], track[desired_instrument].midicc_value_row_4[MixerColumn], trackColor[desired_instrument]);
            usbMIDI.sendControlChange(track[desired_instrument].midicc_number_row_4[MixerColumn], track[desired_instrument].midicc_value_row_4[MixerColumn], track[desired_instrument].MIDIchannel);
          }


          /* if (abs(Potentiometer[MixerColumn] - track[desired_instrument].midicc_value_row_4[MixerColumn]) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            if (track[desired_instrument].midicc_value_row_4[MixerColumn] != Potentiometer[MixerColumn]) {
              track[desired_instrument].midicc_value_row_4[MixerColumn] = Potentiometer[MixerColumn];
              drawPotCC(MixerColumn, lastPotRow, track[desired_instrument].midicc_value_row_4[MixerColumn], track[desired_instrument].midicc_value_row_4[MixerColumn], trackColor[desired_instrument]);
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

void startSeq() {
  master_clock.set_playing(true);
  beatComponents();
  for (int i = 0; i <= 7; i++) {
    track[i].clip_songMode = track[i].arrangment1[master_clock.startOfLoop];
  }
}
void stopSeq() {
  master_clock.set_playing(false);
  phrase = master_clock.startOfLoop - 1;
  pixelphrase = -1;
  seq_MIDItick = -1;
  for (int track_number = 0; track_number < NUM_TRACKS; track_number++) {
    ///////////////////////////////////////////////////////////////track[track_number].MIDItick_16 = -1;
    track[track_number].MIDItick = -1;

    if (track[track_number].MIDIchannel < 17) {
      for (int polys = 0; polys < MAX_VOICES; polys++) {
        usbMIDI.sendNoteOff(track[track_number].notePlayed[polys], VELOCITYOFF, track[track_number].MIDIchannel);
        MIDI.sendNoteOff(track[track_number].notePlayed[polys], VELOCITYOFF, track[track_number].MIDIchannel);
        for (int usbs = 0; usbs < 10; usbs++) {
          //if (!launchpad) {
          usb_midi_devices[usbs]->sendNoteOff(track[track_number].notePlayed[polys], VELOCITYOFF, track[track_number].MIDIchannel);
          // }
        }
      }
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
  }
  tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H * 14, STEP_FRAME_W * 16, STEP_FRAME_H, ILI9341_DARKGREY);
}







void myClock() {

  usbMIDI.sendRealTime(usbMIDI.Clock);
  seq_MIDItick++;
  master_clock.MIDItick++;
  master_clock.drawPositionPointers();
  Serial.println("Clock");
}

void myStart() {
  master_clock.set_playing(true);

  for (int i = 1; i <= 7; i++) {
    track[i].clip_songMode = track[i].arrangment1[0];
  }
  Serial.println("Start");
}
void myStop() {
  master_clock.set_playing(false);
  phrase = -1;
  pixelphrase = -1;
  phrase = 0;

  tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H * 14, STEP_FRAME_W * 16, STEP_FRAME_H, ILI9341_DARKGREY);

  Serial.println("Stop");
}

void myNoteOn(int channel, byte note, byte velocity) {

  if (launchpad) {

    for (int songpages = 0; songpages < 16; songpages++) {
      if (selectPage == SONGMODE_PAGE_1 + songpages) {
        LP_songmode(note);
      }
    }
    for (int gridNotes = 0; gridNotes < 64; gridNotes++) {
      if (note == LP_grid_notes[gridNotes]) {
        LP_grid_bool[gridNotes] = true;
      }
    }



    for (int octNotes = 0; octNotes < 12; octNotes++) {
      if (note == LP_octave_notes[octNotes]) {
        channel = desired_instrument + 1;
        LP_octave_bool_keys[octNotes] = true;
        track[desired_instrument].notePressed[0] = true;
        track[desired_instrument].playNoteOnce[0] = true;
        track[desired_instrument].notePlayed[0] = octNotes + (allTracks[desired_instrument]->shownOctaves * 12);
      }
    }


    for (int stepss = 0; stepss < 16; stepss++) {
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
    }
    // hold for shift button
    if (!button[10] && note == 104) {
      button[14] = true;
    }
    // hold for enter button
    if (!button[10] && note == 120) {
      button[15] = true;
    }
  }

  if (!launchpad) {
    //send midinotes for drumtrack

    LP_octave_bool_keys[0] = true;
    track[channel - 1].notePressed[0] = true;
    track[channel - 1].playNoteOnce[0] = true;
    track[channel - 1].notePlayed[0] = note;
    track[channel - 1].MIDI_velocity[0] = velocity;
    //track[channel - 1].notePlayed[0] = note;

    if (seq_rec) {
      for (int touched_ticks = 0; touched_ticks <= allTracks[desired_instrument]->stepLenght; touched_ticks++) {
        ctrack[channel - 1].sequence[track[channel - 1].clip_songMode].tick[seq_MIDItick].voice[0] = note;
      }
    }
    // When a USB device with multiple virtual cables is used,
    // midi1.getCable() can be used to read which of the virtual
    // MIDI cables received this message.
  }
}

void myNoteOff(int channel, byte note, byte velocity) {
  if (launchpad) {

    for (int gridNotes = 0; gridNotes < 64; gridNotes++) {
      if (note == LP_grid_notes[gridNotes]) {
        LP_grid_bool[gridNotes] = false;
      }
    }

    if (desired_instrument == 0) {
      for (int octNotes = 0; octNotes < 12; octNotes++) {
        if (note == LP_octave_notes[octNotes]) {
          LP_octave_bool[octNotes] = false;
        }
      }
    }

    else {
      for (int octNotes = 0; octNotes < 12; octNotes++) {
        if (note == LP_octave_notes[octNotes]) {
          channel = desired_instrument + 1;
          LP_octave_bool_keys[octNotes] = false;
          track[desired_instrument].notePressed[0] = false;
          track[desired_instrument].notePlayed[0] = octNotes + (allTracks[desired_instrument]->shownOctaves * 12);
          track[desired_instrument].notePlayed[0] = track[desired_instrument].notePlayed[0];
        }
      }
    }

    for (int stepss = 0; stepss < 16; stepss++) {
      if (note == LP_step_notes[stepss]) {
        LP_step_bool[stepss] = false;
      }
    }

    // hold for track button
    if (note == 8) {  //"E"  69
      button[8] = false;
    }
    // hold for plugin button
    if (note == 24) {  //"C"  67
      button[9] = false;
    }
    // hold for Mixer button
    if (note == 40) {  //"4"  52
      button[10] = false;
    }
    // hold for Mixer button
    if (note == 56) {  //"4"  52
      button[11] = false;
    }

    // hold for FX button
    if (note == 72) {  //"8"  56
      button[12] = false;
    }
    // hold for recorder button
    if (note == 88) {
      button[13] = false;
    }
    // hold for shift button
    if (note == 104) {
      button[14] = false;
    }
    // hold for enter button
    if (note == 120) {
      button[15] = false;
    }
  }
  if (!launchpad) {

    LP_octave_bool_keys[0] = false;
    track[channel - 1].notePressed[0] = false;
    track[channel - 1].notePlayed[0] = note;
    //track[channel - 1].MIDI_velocity[0] = velocity;
    //track[channel - 1].notePlayed[0] = note;
  }
}

void myControlChange(int channel, byte control, byte value) {
  if (control == 3) {
    if (Potentiometer[0] != value) {
      incomingCC_changed[0] = true;
    }
    incomingCC[0] = value;
  }
  if (control == 9) {
    if (Potentiometer[1] != value) {
      incomingCC_changed[1] = true;
    }
    incomingCC[1] = value;
  }
  if (control == 14) {
    if (Potentiometer[2] != value) {
      incomingCC_changed[2] = true;
    }
    incomingCC[2] = value;
  }
  if (control == 15) {
    if (Potentiometer[3] != value) {
      incomingCC_changed[3] = true;
    }
    incomingCC[3] = value;
  }




  //launchpad control up-est row, they send cc´s
  if (launchpad) {
    //cursor left
    if (control == 104 && value == 127) {
      button[0] = true;
    }
    //cursor right
    if (otherCtrlButtons && control == 105 && value == 127) {
      button[1] = true;
    }
    //cursor up
    if (otherCtrlButtons && control == 106 && value == 127) {
      button[2] = true;
    }
    //cursor down
    if (otherCtrlButtons && control == 107 && value == 127) {
      button[3] = true;
    }
    //last pot row
    if (otherCtrlButtons && control == 108 && value == 127) {
      button[4] = true;
    }
    //recbutton
    if (otherCtrlButtons && control == 109 && value == 127) {
      button[5] = true;
    }
    //playbutton
    if (otherCtrlButtons && control == 110 && value == 127) {
      button[6] = true;
    }
    //stopbutton
    if (otherCtrlButtons && control == 111 && value == 127) {
      button[7] = true;
    }
  }
}