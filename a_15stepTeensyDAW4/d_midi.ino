///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                         SEQUENCER CALLBACKS                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////



void drawbarPosition() {
  //draw phrasenumber
  tft.fillRect(STEP_FRAME_W * POSITION_BAR_BUTTON + 1, 2, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 3, ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_9);
  tft.setCursor(STEP_FRAME_W * POSITION_BAR_BUTTON + 4, 3);
  tft.print(phrase + 1);
  //drawbarPosition
  for (int songPointerThickness = 0; songPointerThickness <= POSITION_POINTER_THICKNESS; songPointerThickness++) {
    tft.drawPixel(phrase + STEP_FRAME_W * 2, (SONG_POSITION_POINTER_Y + songPointerThickness), ILI9341_GREEN);
    tft.drawFastHLine((pixelphrase)*phraseSegmentLength + STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y + songPointerThickness, phraseSegmentLength, ILI9341_GREEN);
    tft.drawFastHLine((pixelphrase - 1) * phraseSegmentLength + STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y + songPointerThickness, phraseSegmentLength, ILI9341_DARKGREY);
  }
  if (phrase % 16 == 0) {
    pixelphrase = 0;
    tft.fillRect(STEP_FRAME_W * 15, GRID_POSITION_POINTER_Y, STEP_FRAME_W * 4, 4, ILI9341_DARKGREY);
    tft.fillRect(STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y, STEP_FRAME_W * 1, 4, ILI9341_GREEN);
  }
}

void drawstepPosition(int current) {
  //draw the songpointer positions
  for (int songPointerThickness = 0; songPointerThickness <= POSITION_POINTER_THICKNESS; songPointerThickness++) {
    for (int stepwidth = 1; stepwidth <= 16; stepwidth++) {
      tft.drawFastHLine(current * stepwidth + STEP_FRAME_W * 2, STEP_POSITION_POINTER_Y + songPointerThickness, STEP_FRAME_W, ILI9341_GREEN);
      tft.drawFastHLine((current - 1) * stepwidth + STEP_FRAME_W * 2, STEP_POSITION_POINTER_Y + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);
    }
    if (current == 0) {
      tft.drawFastHLine(STEP_FRAME_W * 17, STEP_POSITION_POINTER_Y + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);
    }
  }
}

void sendClock() {
  if (seq_run) {

    if (msecsclock > _clock) {
      MIDItick++;
      for (int i = 0; i < NUM_TRACKS; i++) {
        if (MIDItick % track[i].MIDItick_reset == 0) {
          track[i].MIDItick_16++;
          if (track[i].MIDItick_16 == NUM_STEPS) {
            track[i].MIDItick_16 = 0;
          }
        }
      }
      Serial.println(track[0].MIDItick_16);
      usbMIDI.sendRealTime(usbMIDI.Clock);
      MIDI.sendRealTime(0xF8);
      // MIDI.sendClock();
      msecsclock = 0;
      //digitalWrite(22, LOW);

      if (MIDItick % 6 == 0) {
        tick_16++;
        //digitalWrite(22, HIGH);

        
        if (debugTime) {
          SerialPrintSeq();
        }
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
        drawbarPosition();
        pixelphrase++;
        showSerialonce = true;
      }
      if (tick_16 == -1) {
        beatComponents();
        if (debugTime) {
          if (showSerialonce) {
            SerialPrintPlugins();
          }
        }
      }
      //differnt things happening while the clock is running
      if (phrase == MAX_PHRASES - 1) {
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
void step() {


  //send midinotes for drumtrack #1
  if (!track[0].solo_mutes_state) {
    if (!track[0].mute_state) {

      if (track[0].seqMode == 0) {
        for (int i = 0; i < 12; i++) {
          //if the last step was high, stop the notes
          if (channel1Clip[track[0].clip_songMode][i][track[0].MIDItick_16 - 1]) {
            //drumnotes[i] = false;
            // DrumPluginPlay();
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
          //if the actual step is high, play the notes
          if (channel1Clip[track[0].clip_songMode][i][track[0].MIDItick_16]) {
            if (!dsend_noteOff[i]) {
              drumnotes[i] = true;
              dsend_noteOff[i] = true;
              //DrumPluginPlay();
              if (track[0].MIDIchannel < 17) {
                usbMIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                MIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                for (int usbs = 0; usbs < 10; usbs++) {
                  if (!launchpad) {
                    usb_midi_devices[usbs]->sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                  }
                }
              }
            }
          }
        }
      }
      if (track[0].seqMode == 1) {
        if (track[0].clip_songMode < 8) {
          for (int i = 0; i < 12; i++) {

            if (beatArray[NFX1[track[0].clip_songMode].Pot_Value[i]][track[0].MIDItick_16 - 1]) {
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
            if (beatArray[NFX1[track[0].clip_songMode].Pot_Value[i]][track[0].MIDItick_16]) {
              //if (bitRead(NFX1[NFX1presetNr].Pot_Value[i], clock_count)) {
              clock_count++;
              drumnotes[i] = true;
              dsend_noteOff[i] = true;
              if (track[0].MIDIchannel < 17) {
                usbMIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                MIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                for (int usbs = 0; usbs < 10; usbs++) {
                  if (!launchpad) {
                    usb_midi_devices[usbs]->sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                  }
                }
              }
              if (clock_count == 8) {
                clock_count = 0;
              }
            }
          }
        }
      }
      if (track[0].seqMode == 4) {
        for (int i = 0; i < 12; i++) {
          //if (NFX4[NFX4presetNr].reset[i]<=NFX4[NFX4presetNr].Pot_Value[i])
          NFX4[NFX4presetNr].reset[i]++;

          //Serial.println(NFX4[1].reset[0]);
          if (NFX4[NFX4presetNr].reset[i] >= NFX4[NFX4presetNr].Pot_Value[i]) {
            NFX4[NFX4presetNr].reset[i] = 0;
          }
          if (channel1Clip[track[0].clip_songMode][i][NFX4[NFX4presetNr].reset[i] - 1]) {
            //drumnotes[i] = false;
            // DrumPluginPlay();
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
          //if the actual step is high, play the notes
          if (channel1Clip[track[0].clip_songMode][i][NFX4[NFX4presetNr].reset[i]]) {
            if (!dsend_noteOff[i]) {
              drumnotes[i] = true;
              dsend_noteOff[i] = true;
              //DrumPluginPlay();
              if (track[0].MIDIchannel < 17) {
                usbMIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                MIDI.sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                for (int usbs = 0; usbs < 10; usbs++) {
                  if (!launchpad) {
                    usb_midi_devices[usbs]->sendNoteOn(drumnote[i], track[0].MIDI_velocity, track[0].MIDIchannel);
                  }
                }
              }
            }
          }
        }
      }

      if (track[0].seqMode == 5) {
        if (track[0].clip_songMode < 8) {
        }
      }
    }
  }


  //send midinoteOn/Off´s for melodic track #2 -8
  for (int track_number = 1; track_number <= 7; track_number++) {
    if (!track[track_number].solo_mutes_state) {
      if (!track[track_number].mute_state) {

        if (track[track_number].seqMode == 0) {
          track[track_number].notePlayed = ctrack[track_number].sequence[track[track_number].clip_songMode].step[track[track_number].MIDItick_16] + track[track_number].NoteOffset[phrase];
          track[track_number].notePlayedLast = ctrack[track_number].sequence[track[track_number].clip_songMode].step[track[track_number].MIDItick_16 - 1] + track[track_number].NoteOffset[phrase];

          //if the actual step is high, play the notes
          if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[track[track_number].MIDItick_16] > VALUE_NOTEOFF) {
            track[track_number].playNoteOnce = true;
            track[track_number].notePressed = true;
          }
          //PluginNoteOn();

          //if the last step wass high, stop the notes
          if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[track[track_number].MIDItick_16 - 1] > VALUE_NOTEOFF) {
            track[track_number].notePressed = false;
            //PluginNoteOff();
          }
        }
        if (track[track_number].seqMode == 2) {
          if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[track[track_number].MIDItick_16] > VALUE_NOTEOFF) {
            maxVal = 0;
            if (NFX2[NFX2presetNr].Pot_Value[2] <= NFX2[NFX2presetNr].Pot_Value[3]) {
              for (int i = 0; i < 12; i++) {
                if (analogReadArray[i] > maxVal) {
                  maxVal = analogReadArray[i];
                  maxValIndex = i;
                  cc23 = NFX2[NFX2presetNr].Pot_Value[2];
                  cc24 = NFX2[NFX2presetNr].Pot_Value[3];
                  octave = random(cc23, cc24);
                  track[track_number].notePlayed = (maxValIndex) + (octave * 12) + track[track_number].NoteOffset[phrase];
                  ;
                  track[track_number].notePlayedLast = (maxValIndex) + (octave * 12) + track[track_number].NoteOffset[phrase];
                  ;
                  track[track_number].playNoteOnce = true;
                  track[track_number].notePressed = true;
                }
              }


              if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[track[track_number].MIDItick_16 - 1] > VALUE_NOTEOFF) {
                analogReadArray[maxValIndex] = (analogReadArray[maxValIndex] - NFX2[NFX2presetNr].Pot_Value[0]);
                track[track_number].notePressed = false;
                //PluginNoteOff();
              }
            }
            if (NFX2[NFX2presetNr].Pot_Value[2] > NFX2[NFX2presetNr].Pot_Value[3]) {
              for (int i = 11; i > 0; i--) {
                if (analogReadArray[i] > maxVal) {
                  maxVal = analogReadArray[i];
                  maxValIndex = i;
                  cc23 = NFX2[NFX2presetNr].Pot_Value[2];
                  cc24 = NFX2[NFX2presetNr].Pot_Value[3];
                  octave = random(cc24, cc23);
                  track[track_number].notePlayed = (maxValIndex) + (octave * 12) + track[track_number].NoteOffset[phrase];
                  ;
                  track[track_number].notePlayedLast = (maxValIndex) + (octave * 12) + track[track_number].NoteOffset[phrase];
                  ;
                  track[track_number].playNoteOnce = true;
                  track[track_number].notePressed = true;
                }
              }
            }
          }
          if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[track[track_number].MIDItick_16 - 1] > VALUE_NOTEOFF) {
            analogReadArray[maxValIndex] = (analogReadArray[maxValIndex] - NFX2[NFX2presetNr].Pot_Value[0]);
            track[track_number].notePressed = false;
            //PluginNoteOff();
          }

          if (analogReadArray[maxValIndex] <= NFX2[NFX2presetNr].Pot_Value[1]) {
            for (int i = 0; i < 12; i++) {
              analogReadArray[i] = NFX2[NFX2presetNr].Pot_Value[i + 4];
            }
          }
        }

        if (track[track_number].seqMode == 3) {
          //if the actual step is high, play the notes
          if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[track[track_number].MIDItick_16] > VALUE_NOTEOFF) {
            NFX3[NFX3presetNr].Oct1 = random(NFX3[NFX3presetNr].Pot_Value[2], NFX3[NFX3presetNr].Pot_Value[3]);
            track[track_number].notePlayed = random(0, 11) + (NFX3[NFX3presetNr].Oct1 * 12);
            track[track_number].notePlayedLast = track[track_number].notePlayed;
            track[track_number].playNoteOnce = true;
            track[track_number].notePressed = true;
          }
          //PluginNoteOn();

          //if the last step wass high, stop the notes
          if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[track[track_number].MIDItick_16 - 1] > VALUE_NOTEOFF) {
            track[track_number].notePressed = false;
            //PluginNoteOff();
          }
        }
      }
    }
  }
}

void midiCC_view_Static(int mixerpage, byte desired_instrument) {
  clearWorkSpace();


  for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
    int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
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

void midiCCpage1_Dynamic(int desired_instrument) {
  switch (lastPotRow) {
    case 0:
      //if (msecs % 20 == 0) {
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
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

      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
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

      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
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
      for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        int MixerColumnPos = ((MixerColumn + 1) * 4) - 1;
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
    
    drawstepPosition(tick_16);
    drawbarPosition();
  }

  Serial.println("Clock");
}

void myStart() {
  seq_run = true;
  msecs = 0;
  for (int i = 1; i <= 7; i++) {
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

void myNoteOn(int channel, byte note, byte velocity) {

  if (launchpad) {

    for (int songpages = 0; songpages < 16; songpages++) {
      if (selectPage == SONGMODE_PAGE_1 + songpages) {
        if (msecs % 100 == 0) {
          LP_songmode(note);
        }
      }
    }
    for (int gridNotes = 0; gridNotes < 64; gridNotes++) {
      if (note == LP_grid_notes[gridNotes]) {
        LP_grid_bool[gridNotes] = true;
      }
    }


    if (desired_instrument == 0) {
      for (int octNotes = 0; octNotes < 12; octNotes++) {
        if (note == LP_octave_notes[octNotes]) {
          LP_octave_bool[octNotes] = true;
          drumnotes[octNotes] = true;
        }
      }
    }

    else {
      for (int octNotes = 0; octNotes < 12; octNotes++) {
        if (note == LP_octave_notes[octNotes]) {
          channelPlayed = desired_instrument + 1;
          channel = desired_instrument + 1;
          LP_octave_bool_keys[octNotes] = true;
          track[desired_instrument].notePressed = true;
          track[desired_instrument].playNoteOnce = true;
          track[desired_instrument].notePlayed = octNotes + (track[desired_instrument].shown_octaves * 12);
          track[desired_instrument].notePlayedLast = track[desired_instrument].notePlayed;
        }
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
  }

  if (!launchpad) {
    //send midinotes for drumtrack
    if (channel == 1) {
      LP_octave_bool[note - 60] = true;
      for (int files = 0; files < 12; files++) {
        if (note == (files + 60) || LP_octave_bool[files]) {
          drumnotes[files] = true;
        }
      }
    } else {
      LP_octave_bool_keys[0] = true;
      track[channel - 1].notePressed = true;
      track[channel - 1].playNoteOnce = true;
      track[channel - 1].notePlayed = note;
      track[channel - 1].notePlayedLast = note;
    }
    if (seq_rec) {
      ctrack[channel - 1].sequence[track[channel - 1].clip_selector].step[tick_16] = note;
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
          track[desired_instrument].notePressed = false;
          track[desired_instrument].notePlayed = octNotes + (track[desired_instrument].shown_octaves * 12);
          track[desired_instrument].notePlayedLast = track[desired_instrument].notePlayed;
        }
      }
    }

    for (int stepss = 0; stepss < 16; stepss++) {
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
  }
  if (!launchpad) {
    if (channel == 1) {
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
      track[channel - 1].notePlayedLast = note;
    }
  }
}

void myControlChange(int channel, byte control, byte value) {
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




  //launchpad control up-est row, they send cc´s
  if (launchpad) {
    //cursor left
    if (otherCtrlButtons && control == 104 && value == 127) {
      button[0] = true;
      gridTouchX = constrain(gridTouchX - 1, 0, 19);
      drawCursor();
      showCoordinates();
    } else if (otherCtrlButtons && control == 104 && value != 127) {
      button[0] = false;
    }
    //cursor right
    if (otherCtrlButtons && control == 105 && value == 127) {
      button[1] = true;
      gridTouchX = constrain(gridTouchX + 1, 0, 19);
      drawCursor();
      showCoordinates();
    } else if (otherCtrlButtons && control == 105 && value != 127) {
      button[1] = false;
    }
    //cursor up
    if (otherCtrlButtons && control == 106 && value == 127) {
      button[2] = true;
      gridTouchY = constrain(gridTouchY - 1, 0, 14);
      drawCursor();
      showCoordinates();
    } else if (otherCtrlButtons && control == 106 && value != 127) {
      button[2] = false;
    }
    //cursor down
    if (otherCtrlButtons && control == 107 && value == 127) {
      button[3] = true;
      gridTouchY = constrain(gridTouchY + 1, 0, 14);
      drawCursor();
      showCoordinates();
    } else if (otherCtrlButtons && control == 107 && value != 127) {
      button[3] = false;
    }
    //last pot row
    if (otherCtrlButtons && control == 108 && value == 127) {
      button[4] = true;
      lastPotRow++;
      if (lastPotRow >= 4) {
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
          for (int pluginSelection = 0; pluginSelection <= MAX_PLUGINS; pluginSelection++) {
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
        selectPage = FX3_PAGE1;
        FX3Delay_static();
      }
      if (control == 108 && value == 127) {
        if (track[desired_instrument].seqMode == 1) {
          selectPage = NFX1_PAGE1;
          NoteFX1_Page_Static();
        }
        if (track[desired_instrument].seqMode == 2) {
          selectPage = NFX2_PAGE1;
          NoteFX2_Page_Static();
        }
        if (track[desired_instrument].seqMode == 3) {
          selectPage = NFX3_PAGE1;
          NoteFX3_Page_Static();
        }
        if (track[desired_instrument].seqMode == 4) {
          selectPage = NFX4_PAGE1;
          NoteFX4_Page_Static();
        }
        if (track[desired_instrument].seqMode == 5) {
          selectPage = NFX5_PAGE1;
          //NoteFX5_Page_Static();
        }
      }
    }
  }
}