


//this calls the static plugin view for your plugin, it is used when the plugin page is called or if you change presets
// just add your plugin-page static function here
void Plugin_View_Static() {

  if (selectPage == PLUGIN1_PAGE1) {
    Plugin1_Page_Static(0);
  }
  if (selectPage == PLUGIN1_PAGE2) {
    Plugin1_Page_Static(1);
  }


  if (selectPage == PLUGIN2_PAGE1) {
    Plugin2_Page_Static();
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////
  ///////// if we select the pluginpage its PLUGINx_PAGE1 bool gets true and selects the Pluginx_Page_Static once
  ///////// now we see the actual graphs and values, but the programm switches over to Pluginx_Page_Dynamic(),
  ///////// which is called all the time in the loop() function as long PLUGINx_PAGE1 is true, for controlling the parameters
  ////////////////////////////////////////////////////////////////////////////////////////////////
  if (selectPage == PLUGIN3_PAGE1) {
    Plugin3_Page_Static();
  }
  if (selectPage == PLUGIN4_PAGE1) {
    Plugin4_Page_Static();
  }
  if (selectPage == PLUGIN5_PAGE1) {
    Plugin5_Page_Static();
  }
  if (selectPage == PLUGIN6_PAGE1) {
    Plugin6_Page_Static();
  }
  if (selectPage == PLUGIN7_PAGE1) {
    Plugin7_Page_Static(0);
  }
  if (selectPage == PLUGIN7_PAGE2) {
    ////Plugin7_Page_Static(1);
  }

  if (selectPage == PLUGIN8_PAGE1) {
    Plugin8_Page_Static();
  }
  if (selectPage == PLUGIN9_PAGE1) {
    Plugin9_Page_Static();
  }
  if (selectPage == PLUGIN10_PAGE1) {
    Plugin10_Page_Static();
  }
  if (selectPage == PLUGIN11_PAGE1) {
    Plugin11_Page_Static();
  }
  if (selectPage == PLUGIN12_PAGE1) {
    Plugin12_Page_Static();
  }
  if (selectPage == PLUGIN13_PAGE1) {
    Plugin13_Page_Static();
  }
  if (selectPage == PLUGIN14_PAGE1) {
    Plugin14_Page_Static();
  }
  if (selectPage == PLUGIN15_PAGE1) {
    Plugin15_Page_Static();
  }
  if (selectPage == PLUGIN16_PAGE1) {
    Plugin16_Page_Static();
  }
  ///////////////////////////////////////////////////////////////////////
  //NFX
  if (selectPage == NFX1_PAGE1) {
    NoteFX1_Page_Static();
  }
  if (selectPage == NFX2_PAGE1) {
    NoteFX2_Page_Static();
  }
  if (selectPage == NFX3_PAGE1) {
    NoteFX3_Page_Static();
  }
  if (selectPage == NFX4_PAGE1) {
    NoteFX4_Page_Static();
  }
  ////////////////////////////////////////////////////////////////////
  //mixer
  if (selectPage == MIXER_PAGE_1) {
    mixerPage1_Static(0);
  }
  if (selectPage == MIXER_PAGE_2) {
    mixerPage2_Static();
  }
  if (selectPage == MIXER_PAGE_3) {
    mixerPage3_Static();
  }
  ////////////////////////////////////////////////////////////////////
  //FX
  if (selectPage == FX1_PAGE1) {
    FX1reverb_static();
  }
  if (selectPage == FX2_PAGE1) {
    FX2Bitcrush_static();
  }
  if (selectPage == FX3_PAGE1) {
    FX3Delay_static();
  }
  ////////////////////////////////////////////////////////////////////
  //recorder
  if (selectPage == RECORDER_PAGE) {
    recorder_Page_Static();
  }
}
//this calls the dynamic plugin view for your plugin, where your "pots"  (via encoder) of the soundcontrols are assigned and happening
// just add your plugin-page dynamic and Pluginx_Control function here
void Plugin_View_Dynamic() {
  //***********************************************************************************************************************
  // 4) copy one of the plugin Page Views
  //    and change the names according to our variables and functions.
  //    Every page you want to make has to have its own statement
  //    we create:

  //  //setting up the Plugin3 Page1-view
  //    if (selectPage == PLUGIN3_PAGE1) {
  //      Plugin3_Page1_Dynamic();
  //    }

  // after adding the active state statement
  // head over to "midi.ino"
  //look for *****************************************************************************************

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////






  //-----------------------------------------
  //setting up the Plugin1 Page1-view
  if (selectPage == PLUGIN1_PAGE1) {
    Plugin1_Page1_Dynamic();
  }
  //setting up the Plugin1 Page2-view
  if (selectPage == PLUGIN1_PAGE2) {
    Plugin1_Page2_Dynamic();
  }

  //setting up the Plugin2 Page1-view
  if (selectPage == PLUGIN2_PAGE1) {
    Plugin2_Page1_Dynamic();
  }


  /////////////////////////////////////////////////////////////////////////////
  //setting up the Plugin3 Page1-view
  if (selectPage == PLUGIN3_PAGE1) {
    Plugin3_Page1_Dynamic();
  }
  /////////////////////////////////////////////////////////////////////////////


  //setting up the Plugin4 Page1-view
  if (selectPage == PLUGIN4_PAGE1) {
    Plugin4_Page1_Dynamic();
  }

  //setting up the Plugin5 Page1-view
  if (selectPage == PLUGIN5_PAGE1) {
    Plugin5_Page1_Dynamic();
  }
  //setting up the Plugin6 Page1-view
  if (selectPage == PLUGIN6_PAGE1) {
    Plugin6_Page1_Dynamic();
  }
  //setting up thePlugin7 Page1-view
  if (selectPage == PLUGIN7_PAGE1) {
    Plugin7_Page1_Dynamic();
  }
  //setting up thePlugin7 Page2-view
  if (selectPage == PLUGIN7_PAGE2) {
    ////Plugin7_Page2_Dynamic();
  }
  //setting up the Plugin8 Page1-view
  if (selectPage == PLUGIN8_PAGE1) {
    Plugin8_Page1_Dynamic();
  }
  //setting up the Plugin9 Page1-view
  if (selectPage == PLUGIN9_PAGE1) {
    Plugin9_Page1_Dynamic();
  }
  //setting up the Plugin10 Page1-view
  if (selectPage == PLUGIN10_PAGE1) {
    Plugin10_Page1_Dynamic();
  }
  //setting up the Plugin10 Page1-view
  if (selectPage == PLUGIN11_PAGE1) {
    Plugin11_Page1_Dynamic();
  }
  //setting up the Plugin10 Page1-view
  if (selectPage == PLUGIN12_PAGE1) {
    Plugin12_Page1_Dynamic();
  }
  //setting up the Plugin10 Page1-view
  if (selectPage == PLUGIN13_PAGE1) {
    Plugin13_Page1_Dynamic();
  }
  //setting up the Plugin10 Page1-view
  if (selectPage == PLUGIN14_PAGE1) {
    Plugin14_Page1_Dynamic();
  }
  //setting up the Plugin10 Page1-view
  if (selectPage == PLUGIN15_PAGE1) {
    Plugin15_Page1_Dynamic();
  }
  //setting up the Plugin10 Page1-view
  if (selectPage == PLUGIN16_PAGE1) {
    Plugin16_Page1_Dynamic();
  }
  ////////////////////////////////////////////////////////////////////
  //NFX
  //setting up the NoteFX1-view
  if (selectPage == NFX1_PAGE1) {
    NoteFX1_Page1_Dynamic();
    NoteFX1_Control();
  }
  //setting up the NoteFX2-view
  if (selectPage == NFX2_PAGE1) {
    NoteFX2_Page1_Dynamic();
    NoteFX2_Control();
  }
  //setting up the NoteFX3-view
  if (selectPage == NFX3_PAGE1) {
    NoteFX3_Page1_Dynamic();
    NoteFX3_Control();
  }
  //setting up the NoteFX4-view
  if (selectPage == NFX4_PAGE1) {
    NoteFX4_Page1_Dynamic();
    NoteFX4_Control();
  }


  //setting up the StepSequencer-view for #1-8
  for (int i = 0; i < NUM_TRACKS; i++) {
    if (selectPage == i) {
      melodicTickSequencer();
    }
  }
  //setting up the scaleSelector-view
  if (selectPage == SCALESELECT) {
    scaleSelector();
  }

  //setting up the songMode-view1
  for (int pagenr = 0; pagenr < MAX_SONGMODE_PAGES; pagenr++) {
    if (selectPage == pagenr + 10) {
      songModePage(pagenr);
    }
  }

  //setting up the Recorder Page
  if (selectPage == RECORDER_PAGE) {
    recorder_Page1_Dynamic();
  }

  ////////////////////////////////////////////////////////////////////
  //mixer
  //setting up the Mixer Page 1
  if (selectPage == MIXER_PAGE_1) {
    MixerPage1_Dynamic();
  }
  //setting up the Mixer Page 2
  if (selectPage == MIXER_PAGE_2) {
    MixerPage2_Dynamic();
  }
  //setting up the Mixer Page 3
  if (selectPage == MIXER_PAGE_3) {
    MixerPage3_Dynamic();
  }
  ////////////////////////////////////////////////////////////////////
  //FX
  if (selectPage == FX1_PAGE1) {
    FX1reverb_dynamic();
  }
  //setting up the Mixer Page 3
  if (selectPage == FX2_PAGE1) {
    FX2Bitcrush_dynamic();
  }
  if (selectPage == FX3_PAGE1) {
    FX3Delay_dynamic();
  }
  //setting up the Midi cc page
  if (selectPage == MIDICC_PAGE_1) {
    midiCCpage1_Dynamic(desired_track);
  }
}
//here you have to put your NoteOn´s into
void PluginNoteOn() {
  for (int desired_instruments = 0; desired_instruments < 8; desired_instruments++) {

    //send plugin noteOn´s to POLYPHONIC plugins
    for (int polys = 0; polys < MAX_VOICES; polys++) {
      if ((track[desired_instruments].notePlayed[polys] - track[desired_instruments].NoteOffset[phrase]) > VALUE_NOTEOFF) {
        if (track[desired_instruments].notePressed[polys]) {
          if (track[desired_instruments].playNoteOnce[polys]) {
            if (!track[desired_instruments].envActive[polys]) {
              //send midi noteOn´s with channel 1-16
              if (track[desired_instruments].MIDIchannel < 17) {
                track[desired_instruments].playNoteOnce[polys] = false;
                track[desired_instruments].envActive[polys] = true;
                // Serial.printf("Send NoteON: %d, channel: %d, at tick: %d\n", track[desired_instruments].notePlayed[polys], track[desired_instruments].MIDIchannel, master_clock.MIDItick);
                usbMIDI.sendNoteOn(track[desired_instruments].notePlayed[polys], track[desired_instruments].MIDI_velocity[polys], track[desired_instruments].MIDIchannel);
                MIDI.sendNoteOn(track[desired_instruments].notePlayed[polys], track[desired_instruments].MIDI_velocity[polys], track[desired_instruments].MIDIchannel);
                for (int usbs = 0; usbs < 10; usbs++) {
                  if (!launchpad) {
                    usb_midi_devices[usbs]->sendNoteOn(track[desired_instruments].notePlayed[polys], track[desired_instruments].MIDI_velocity[polys], track[desired_instruments].MIDIchannel);
                  }
                }
              }
              //play WAV drumplugin when midichannel = 18
              if (track[desired_instruments].MIDIchannel == 18) {
                sprintf(_pl2Filename, "%s%d.WAV\0", wavKits[polys], plugin[1].preset[plpreset[1]].Pot_Value2[polys]);
                PL2PLAYER[polys]->play(_pl2Filename);
                track[desired_instruments].playNoteOnce[polys] = false;
                track[desired_instruments].envActive[polys] = true;
              }
              //play Memory drumplugin when midichannel = 20
              if (track[desired_instruments].MIDIchannel == 20) {
                if (polys == 0) {
                  playMem1.play(AudioSampleKick);
                  track[desired_instruments].playNoteOnce[0] = false;
                  track[desired_instruments].envActive[0] = true;
                }
                if (polys == 1) {
                  playMem2.play(AudioSampleSnare);
                  track[desired_instruments].playNoteOnce[1] = false;
                  track[desired_instruments].envActive[1] = true;
                }
                if (polys == 2) {
                  playMem3.play(AudioSampleP2);
                  track[desired_instruments].playNoteOnce[2] = false;
                  track[desired_instruments].envActive[2] = true;
                }
                if (polys == 3) {
                  playMem4.play(AudioSampleHihat);
                  track[desired_instruments].playNoteOnce[3] = false;
                  track[desired_instruments].envActive[3] = true;
                }
                if (polys == 4) {
                  playMem5.play(AudioSampleCashregister);
                  track[desired_instruments].playNoteOnce[4] = false;
                  track[desired_instruments].envActive[4] = true;
                }
                if (polys == 5) {
                  playMem6.play(AudioSampleTomtom);
                  track[desired_instruments].playNoteOnce[5] = false;
                  track[desired_instruments].envActive[5] = true;
                }
                if (polys == 6) {
                  playMem7.play(AudioSampleGong);
                  track[desired_instruments].playNoteOnce[6] = false;
                  track[desired_instruments].envActive[6] = true;
                }
                if (polys == 7) {
                  playMem8.play(AudioSamplePongblip);
                  track[desired_instruments].playNoteOnce[7] = false;
                  track[desired_instruments].envActive[7] = true;
                }
                if (polys == 8) {
                  playMem9.play(AudioSampleClap);
                  track[desired_instruments].playNoteOnce[8] = false;
                  track[desired_instruments].envActive[8] = true;
                }
              }
              //play Synthesized drumplugin when midichannel = 23
              if (track[desired_instruments].MIDIchannel == 23) {
                if (polys == 0) {
                  pl7drum1.noteOn();
                  track[desired_instruments].playNoteOnce[0] = false;
                  track[desired_instruments].envActive[0] = true;
                }
                if (polys == 1) {
                  pl7envelope1.noteOn();
                  track[desired_instruments].playNoteOnce[1] = false;
                  track[desired_instruments].envActive[1] = true;
                }
                if (polys == 2) {
                  pl7envelope2.noteOn();
                  pl7envelope3.noteOn();
                  track[desired_instruments].playNoteOnce[2] = false;
                  track[desired_instruments].envActive[2] = true;
                }
                if (polys == 3) {
                  //
                  track[desired_instruments].playNoteOnce[3] = false;
                  track[desired_instruments].envActive[3] = true;
                }
                if (polys == 4) {
                  //
                  track[desired_instruments].playNoteOnce[4] = false;
                  track[desired_instruments].envActive[4] = true;
                }
                if (polys == 5) {
                  //
                  track[desired_instruments].playNoteOnce[5] = false;
                  track[desired_instruments].envActive[5] = true;
                }
                if (polys == 6) {
                  //
                  track[desired_instruments].playNoteOnce[6] = false;
                  track[desired_instruments].envActive[6] = true;
                }
                if (polys == 7) {
                  //
                  track[desired_instruments].playNoteOnce[7] = false;
                  track[desired_instruments].envActive[7] = true;
                }
                if (polys == 8) {
                  //
                  track[desired_instruments].playNoteOnce[8] = false;
                  track[desired_instruments].envActive[8] = true;
                }
              }
              //play RAW drumplugin when midichannel = 27
              if (track[desired_instruments].MIDIchannel == 27) {
                if (polys == 0) {
                  sprintf(_pl11Filename1, "%s%d.RAW\0", wavKits[0], plugin[10].preset[plpreset[10]].Pot_Value2[0]);
                  //playSdRaw1.setPlaybackRate(1);
                  playSdRaw1.play(_pl11Filename1);
                  //sprintf(_pl11Filename, "%s%d.RAW\0", wavKits[polys], plugin[10].preset[plpreset[10]].Pot_Value2[polys]);
                  //PL11PLAYER[polys]->play(_pl11Filename);
                  track[desired_instruments].playNoteOnce[0] = false;
                  track[desired_instruments].envActive[0] = true;
                  Serial.printf("poly=%d, name=%s\n", polys, _pl11Filename1);
                }
                if (polys == 1) {
                  sprintf(_pl11Filename2, "%s%d.RAW\0", wavKits[1], plugin[10].preset[plpreset[10]].Pot_Value2[1]);
                  //playSdRaw2.setPlaybackRate(1);
                  playSdRaw2.play(_pl11Filename2);
                  track[desired_instruments].playNoteOnce[1] = false;
                  track[desired_instruments].envActive[1] = true;
                }
                if (polys == 2) {
                  sprintf(_pl11Filename3, "%s%d.RAW\0", wavKits[2], plugin[10].preset[plpreset[10]].Pot_Value2[2]);
                  //playSdRaw3.setPlaybackRate(1);
                  playSdRaw3.play(_pl11Filename3); //filename, Nr of channels
                  track[desired_instruments].playNoteOnce[2] = false;
                  track[desired_instruments].envActive[2] = true;
                }
                /*
                if (polys == 3) {
                  sprintf(_pl11Filename4, "%s%d.RAW\0", wavKits[3], plugin[10].preset[plpreset[10]].Pot_Value2[3]);
                  playSdRaw4.setPlaybackRate(1);
                  playSdRaw4.playRaw(_pl11Filename4, 1);
                  track[desired_instruments].playNoteOnce[3] = false;
                  track[desired_instruments].envActive[3] = true;
                }
                if (polys == 4) {
                  sprintf(_pl11Filename5, "%s%d.RAW\0", wavKits[4], plugin[10].preset[plpreset[10]].Pot_Value2[4]);
                  playSdRaw5.setPlaybackRate(1);
                  playSdRaw5.playRaw(_pl11Filename5, 1);
                  track[desired_instruments].playNoteOnce[4] = false;
                  track[desired_instruments].envActive[4] = true;
                }
                if (polys == 5) {
                  sprintf(_pl11Filename6, "%s%d.RAW\0", wavKits[5], plugin[10].preset[plpreset[10]].Pot_Value2[5]);
                  playSdRaw6.setPlaybackRate(1);
                  playSdRaw6.playRaw(_pl11Filename6, 1);
                  track[desired_instruments].playNoteOnce[5] = false;
                  track[desired_instruments].envActive[5] = true;
                }
                if (polys == 6) {
                  sprintf(_pl11Filename7, "%s%d.RAW\0", wavKits[6], plugin[10].preset[plpreset[10]].Pot_Value2[6]);
                  playSdRaw7.setPlaybackRate(1);
                  playSdRaw7.playRaw(_pl11Filename7, 1);
                  track[desired_instruments].playNoteOnce[6] = false;
                  track[desired_instruments].envActive[6] = true;
                }
                if (polys == 7) {
                  sprintf(_pl11Filename8, "%s%d.RAW\0", wavKits[7], plugin[10].preset[plpreset[10]].Pot_Value2[7]);
                  playSdRaw8.setPlaybackRate(1);
                  playSdRaw8.playRaw(_pl11Filename8, 1);
                  track[desired_instruments].playNoteOnce[7] = false;
                  track[desired_instruments].envActive[7] = true;
                }
                if (polys == 8) {
                  sprintf(_pl11Filename9, "%s%d.RAW\0", wavKits[8], plugin[10].preset[plpreset[10]].Pot_Value2[8]);
                  playSdRaw9.setPlaybackRate(1);
                  playSdRaw9.playRaw(_pl11Filename9, 1);
                  track[desired_instruments].playNoteOnce[8] = false;
                  track[desired_instruments].envActive[8] = true;
                }
                if (polys == 9) {
                  sprintf(_pl11Filename10, "%s%d.RAW\0", wavKits[9], plugin[10].preset[plpreset[10]].Pot_Value2[9]);
                  playSdRaw10.setPlaybackRate(1);
                  playSdRaw10.playRaw(_pl11Filename10, 1);
                  track[desired_instruments].playNoteOnce[9] = false;
                  track[desired_instruments].envActive[9] = true;
                }
                if (polys == 10) {
                  sprintf(_pl11Filename11, "%s%d.RAW\0", wavKits[10], plugin[10].preset[plpreset[10]].Pot_Value2[10]);
                  playSdRaw11.setPlaybackRate(1);
                  playSdRaw11.playRaw(_pl11Filename11, 1);
                  track[desired_instruments].playNoteOnce[10] = false;
                  track[desired_instruments].envActive[10] = true;
                }
                if (polys == 11) {
                  sprintf(_pl11Filename12, "%s%d.RAW\0", wavKits[11], plugin[10].preset[plpreset[10]].Pot_Value2[11]);
                  playSdRaw12.setPlaybackRate(1);
                  playSdRaw12.playRaw(_pl11Filename12, 1);
                  track[desired_instruments].playNoteOnce[11] = false;
                  track[desired_instruments].envActive[11] = true;
                }
                */
              }
            }
          }
        }
        //Serial.println("");
      }
    }

    //send plugin noteOn´s to MONOPHONIC plugins
    if (track[desired_instruments].notePressed[0]) {
      if (track[desired_instruments].playNoteOnce[0]) {
        if (!track[desired_instruments].envActive[0]) {

          if (track[desired_instruments].MIDIchannel == 17) {
            for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
              int Note2play = track[desired_instruments].notePlayed[0] + map(plugin[pl1NR].preset[track[desired_instruments].Ttrckprst[phrase]].Pot_Value2[MixerColumn], 0, 127, -18, 18);
              int pl1velocity = plugin[pl1NR].preset[track[desired_instruments].Ttrckprst[phrase]].Pot_Value2[MixerColumn + 8];
              OSC_MOD[MixerColumn]->frequency(note_frequency[Note2play] * tuning);
              usbMIDI.sendNoteOn(Note2play, pl1velocity, desired_instruments + 1);
              MIDI.sendNoteOn(Note2play, pl1velocity, desired_instruments + 1);
            }
            envelope1.noteOn();
            envelope2.noteOn();
            track[desired_instruments].playNoteOnce[0] = false;
            track[desired_instruments].envActive[0] = true;
            //Serial.println("crackling");
          }
          if (track[desired_instruments].MIDIchannel == 19) {
            OSC_MOD[4]->frequency(note_frequency[track[desired_instruments].notePlayed[0]] * tuning);
            pl3envelope1.noteOn();
            pl3envelope2.noteOn();
            track[desired_instruments].playNoteOnce[0] = false;
            track[desired_instruments].envActive[0] = true;
          }
          if (track[desired_instruments].MIDIchannel == 21) {

            playSdPitch1.setPlaybackRate(note_frequency[track[desired_instruments].notePlayed[0]]);
            sprintf(_RawFile, "%d.RAW\0", plugin[pl5NR].preset[track[desired_instruments].Ttrckprst[phrase]].Pot_Value[0]);
            playSdPitch1.playRaw(_RawFile, 1);
            pl5envelope1.noteOn();
            pl5envelope2.noteOn();
            track[desired_instruments].playNoteOnce[0] = false;
            track[desired_instruments].envActive[0] = true;
          }
          if (track[desired_instruments].MIDIchannel == 22) {
            playSdPitch2.setPlaybackRate(note_frequency[track[desired_instruments].notePlayed[0]]);
            sprintf(_RawFile2, "%d.RAW\0", plugin[pl6NR].preset[track[desired_instruments].Ttrckprst[phrase]].Pot_Value[0]);
            playSdPitch2.playRaw(_RawFile2, 1);
            pl6envelope1.noteOn();
            pl6envelope2.noteOn();
            track[desired_instruments].playNoteOnce[0] = false;
            track[desired_instruments].envActive[0] = true;
          }
          if (track[desired_instruments].MIDIchannel == 24) {
            pl8waveform1.frequency(note_frequency[track[desired_instruments].notePlayed[0]] * tuning);
            pl8envelope1.noteOn();
            pl8envelope2.noteOn();
            track[desired_instruments].playNoteOnce[0] = false;
            track[desired_instruments].envActive[0] = true;
          }
          if (track[desired_instruments].MIDIchannel == 25) {
            pl9string1.noteOn(note_frequency[track[desired_instruments].notePlayed[0]] * tuning, 1);
            track[desired_instruments].playNoteOnce[0] = false;
            track[desired_instruments].envActive[0] = true;
          }
          if (track[desired_instruments].MIDIchannel == 26) {
            pl10pwm1.frequency((note_frequency[track[desired_instruments].notePlayed[0]] * tuning));
            pl10pwm2.frequency((note_frequency[track[desired_instruments].notePlayed[0]] + detune_mapped) * tuning);
            pl10envelope1.noteOn();
            pl10envelope2.noteOn();
            track[desired_instruments].playNoteOnce[0] = false;
            track[desired_instruments].envActive[0] = true;
          }
        }
      }
    }
  }
}
//here you have to put your NoteOff´s into
void PluginNoteOff() {
  for (int desired_instruments = 0; desired_instruments < 8; desired_instruments++) {
    //send plugin noteOff´s to POLYPHONIC plugins
    for (int polys = 0; polys < MAX_VOICES; polys++) {
      if (track[desired_instruments].envActive[polys]) {
        if (!track[desired_instruments].notePressed[polys]) {
          //send midi noteOff´s with channel 1-16
          if (track[desired_instruments].MIDIchannel < 17) {
            track[desired_instruments].envActive[polys] = false;
            // Serial.printf("Send NoteOFF: %d, channel: %d, at tick: %d\n", track[desired_instruments].notePlayed[polys], track[desired_instruments].MIDIchannel, master_clock.MIDItick);
            usbMIDI.sendNoteOff(track[desired_instruments].notePlayed[polys], VELOCITYOFF, track[desired_instruments].MIDIchannel);
            MIDI.sendNoteOff(track[desired_instruments].notePlayed[polys], VELOCITYOFF, track[desired_instruments].MIDIchannel);
            for (int usbs = 0; usbs < 10; usbs++) {
              if (!launchpad) {
                usb_midi_devices[usbs]->sendNoteOff(track[desired_instruments].notePlayed[polys], VELOCITYOFF, track[desired_instruments].MIDIchannel);
              }
            }
          }
          if (track[desired_instruments].MIDIchannel == 18) {
            track[desired_instruments].envActive[polys] = false;
          }
          if (track[desired_instruments].MIDIchannel == 20) {
            track[desired_instruments].envActive[polys] = false;
          }
          if (track[desired_instruments].MIDIchannel == 23) {
            if (polys == 0) {
              track[desired_instruments].envActive[0] = false;
            }
            if (polys == 1) {
              pl7envelope1.noteOff();
              track[desired_instruments].envActive[1] = false;
            }
            if (polys == 2) {
              pl7envelope2.noteOff();
              pl7envelope3.noteOff();
              track[desired_instruments].envActive[2] = false;
            }
            if (polys == 3) {
              track[desired_instruments].envActive[3] = false;
            }
          }
          if (track[desired_instruments].MIDIchannel == 27) {
            track[desired_instruments].envActive[polys] = false;
          }
        }
      }
    }
    //send plugin noteOff´s to MONOPHONIC plugins
    if (!track[desired_instruments].notePressed[0]) {
      if (track[desired_instruments].envActive[0]) {
        //send plugin noteOff´s to plugins
        if (track[desired_instruments].MIDIchannel == 17) {
          for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
            int Note2play = track[desired_instruments].notePlayed[0] + map(plugin[pl1NR].preset[track[desired_instruments].Ttrckprst[phrase]].Pot_Value2[MixerColumn], 0, 127, -18, 18);
            usbMIDI.sendNoteOff(Note2play, 0, desired_instruments + 1);
            MIDI.sendNoteOff(Note2play, 0, desired_instruments + 1);
          }
          track[desired_instruments].envActive[0] = false;
          envelope1.noteOff();
          envelope2.noteOff();
        }
        if (track[desired_instruments].MIDIchannel == 19) {
          track[desired_instruments].envActive[0] = false;
          pl3envelope1.noteOff();
          pl3envelope2.noteOff();
        }
        if (track[desired_instruments].MIDIchannel == 21) {
          track[desired_instruments].envActive[0] = false;
          pl5envelope1.noteOff();
          pl5envelope2.noteOff();
        }
        if (track[desired_instruments].MIDIchannel == 22) {
          track[desired_instruments].envActive[0] = false;
          pl6envelope1.noteOff();
          pl6envelope2.noteOff();
        }
        if (track[desired_instruments].MIDIchannel == 24) {
          track[desired_instruments].envActive[0] = false;
          pl8envelope1.noteOff();
          pl8envelope2.noteOff();
        }
        if (track[desired_instruments].MIDIchannel == 25) {
          track[desired_instruments].envActive[0] = false;
          pl9string1.noteOff(0);
        }
        if (track[desired_instruments].MIDIchannel == 26) {
          track[desired_instruments].envActive[0] = false;
          pl10envelope1.noteOff();
          pl10envelope2.noteOff();
        }
      }
    }
  }
}


//this function is called for every beatchange for preset/clip/noteoffset/clip change
//add your soundcontrol functions like desired osc frequency etc, so the presetchange can be applied
void beatComponents() {


  for (int instruments = 0; instruments < 8; instruments++) {

    track[instruments].clip_songMode = track[instruments].arrangment1[phrase];


    for (int songpages = 0; songpages < 16; songpages++) {
      if (selectPage == SONGMODE_PAGE_1 + songpages) {
        if (launchpad) {
          for (int notes = 0; notes < 9; notes++) {
            midi01.sendNoteOff(notes + (instruments * 16), 0, 1);
            //Serial.println("doh");
          }

          if (track[instruments].arrangment1[phrase] < MAX_CLIPS) {
            midi01.sendNoteOn(track[instruments].arrangment1[phrase] + (instruments * 16), 60, 1);
            //Serial.println("dah");
          }
        }
      }
    }

    if (track[instruments].MIDIchannel == 17) {
      plpreset[pl1NR] = track[instruments].Ttrckprst[phrase];
      Plugin1_Change();
    }
    if (track[instruments].MIDIchannel == 18) {
      plpreset[1] = track[instruments].Ttrckprst[phrase];
      Plugin2_Change();
    }
    if (track[instruments].MIDIchannel == 19) {
      plpreset[pl3NR] = track[instruments].Ttrckprst[phrase];
      Plugin3_Change();
    }
    if (track[instruments].MIDIchannel == 20) {
      plpreset[3] = track[instruments].Ttrckprst[phrase];
      Plugin4_Change();
    }
    if (track[instruments].MIDIchannel == 21) {
      plpreset[pl5NR] = track[instruments].Ttrckprst[phrase];
      Plugin5_Change();
    }
    if (track[instruments].MIDIchannel == 22) {
      plpreset[pl6NR] = track[instruments].Ttrckprst[phrase];
      Plugin6_Change();
    }
    if (track[instruments].MIDIchannel == 23) {
      plpreset[6] = track[instruments].Ttrckprst[phrase];
    }
    if (track[instruments].MIDIchannel == 24) {
      plpreset[pl8NR] = track[instruments].Ttrckprst[phrase];
      Plugin8_Change();
    }
    if (track[instruments].MIDIchannel == 25) {
      plpreset[8] = track[instruments].Ttrckprst[phrase];
      Plugin9_Change();
    }
    if (track[instruments].MIDIchannel == 27) {
      plpreset[pl11NR] = track[instruments].Ttrckprst[phrase];
      Plugin11_Change();
    }

    if (allTracks[instruments]->seqMode == 1) {
      NFX1presetNr = track[instruments].clip_songMode;
      NoteFX1_Change();
    }
    if (allTracks[instruments]->seqMode == 2) {
      NFX2presetNr = track[instruments].clip_songMode;
      NoteFX2_Change();
    }
    if (allTracks[instruments]->seqMode == 3) {
      NFX3presetNr = track[instruments].clip_songMode;
      NoteFX3_Change();
    }
    if (allTracks[instruments]->seqMode == 4) {
      //NFX4presetNr = track[instruments].clip_songMode;
      //NoteFX4_Change();
    }
  }
}

//end of the plugin-function-nightmare
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////
void selectFilterType(int des_node, byte mixerchannel) {
  FILTERMIXER[des_node]->gain(0, 0);
  FILTERMIXER[des_node]->gain(1, 0);
  FILTERMIXER[des_node]->gain(2, 0);
  FILTERMIXER[des_node]->gain(mixerchannel, 1);
}

/*
void saveMIDItrack(const char* track, int trackNr) {
  //sprintf(_trackname, "%s.mid\0", track);
  SmfWriter writer;
  writer.setFilename(track);
  writer.writeHeader();
  //Serial.print("Start saving-> ");

  int deltaStep = 0;
  for (int sclip = 0; sclip < MAX_CLIPS; sclip++) {
    for (int sstep = 0; sstep < STEP_QUANT; sstep++) {
      if (ctrack[trackNr].sequence[sclip].steps[sstep].voice[0] > 0) {
        writer.addNoteOnEvent(deltaStep, trackNr, ctrack[trackNr].sequence[sclip].steps[sstep].voice[0], 127);
        writer.addNoteOffEvent(4, trackNr, ctrack[trackNr].sequence[sclip].steps[sstep].voice[0]);
        deltaStep = 0;
      }
      if (ctrack[trackNr].sequence[sclip].steps[sstep].voice[0] <= 0) {
        deltaStep = deltaStep + 4;
      }
    }
  }
  writer.flush();
}
*/
void saveTrack(const char* trackname, byte trackNr) {
  sprintf(_trackname, "%s.txt\0", trackname);
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);


  // delete the file:
  tft.printf("Removing:%s", _trackname);
  Serial.printf("Removing:%s", _trackname);
  SD.remove(_trackname);
  tft.println("Done");
  Serial.println("Done");

  // open the file.
  tft.printf("Creating and opening:", _trackname);
  Serial.printf("Creating and opening:", _trackname);
  myFile = SD.open(_trackname, FILE_WRITE);
  tft.println("Done");
  Serial.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {
    //save tracks
    tft.printf("Writing clips to:%s", _trackname);
    Serial.printf("Writing clips to:%s", _trackname);

    for (int sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (int sstep = 0; sstep < TICKS_PER_BAR; sstep++) {
        for (int v = 0; v < MAX_VOICES; v++) {
          myFile.print((char)ctrack[trackNr].sequence[sclip].tick[sstep].voice[v]);
        }
      }
    }


    // int channel = track[trackNr].MIDIchannel + 48;
    myFile.print((char)allTracks[trackNr]->MIDIChannel);
    myFile.print((char)track[trackNr].MIDIchannel);

    // close the file:
    myFile.close();
    tft.println("Done");
    Serial.println("Done");
  } else {
    // if the file didn't open, print an error:
    tft.printf("error opening:%s", _trackname);
    Serial.printf("error opening:%s", _trackname);
  }

  tft.println("Saving done.");
  Serial.println("Saving done.");
  startUpScreen();
}

void loadTrack(char* trackname, int trackNr) {
  sprintf(_trackname, "%s.txt\0", trackname);
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  tft.printf("opening:%s...", _trackname);
  Serial.printf("opening:%s...", _trackname);
  myFile = SD.open(_trackname);
  tft.println("Done");
  Serial.println("Done");

  if (myFile) {


    // read from the file until there's nothing else in it:
    //load track 1
    tft.printf("Reading clips from:%s...", _trackname);
    Serial.printf("Reading clips from:%s...", _trackname);


    for (int sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (int sstep = 0; sstep < TICKS_PER_BAR; sstep++) {
        for (int v = 0; v < MAX_VOICES; v++) {
          ctrack[trackNr].sequence[sclip].tick[sstep].voice[v] = myFile.read();
        }
      }
    }

    //int channel = track[trackNr].MIDIchannel + 48;
    allTracks[trackNr]->MIDIChannel = myFile.read();
    track[trackNr].MIDIchannel = myFile.read();

    tft.println("Done");
    Serial.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.printf("error opening:%s\n", _trackname);
    Serial.printf("error opening:%s\n", _trackname);
  }
}

void savePlugin(const char* trackname, byte trackNr) {
  sprintf(_trackname, "%s.txt\0", trackname);
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);


  // delete the file:
  tft.printf("Removing:%s", _trackname);
  Serial.printf("Removing:%s", _trackname);
  SD.remove(_trackname);
  tft.println("Done");
  Serial.println("Done");

  // open the file.
  tft.printf("Creating and opening:%s", _trackname);
  Serial.printf("Creating and opening:%s", _trackname);
  myFile = SD.open(_trackname, FILE_WRITE);
  tft.println("Done");
  Serial.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {
    //save tracks
    tft.printf("Writing plugin to:%s", _trackname);
    Serial.printf("Writing plugin to:%s", _trackname);


    for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      for (int pots = 0; pots < 16; pots++) {
        //save plugin 1 variables
        myFile.print((char)plugin[trackNr].preset[maxpreset].Pot_Value2[pots]);
        Serial.printf("Value2: plugin:%d; preset:%d; pot:%d, value:%d\n", trackNr, maxpreset, pots, plugin[trackNr].preset[maxpreset].Pot_Value2[pots]);
        myFile.print((char)plugin[trackNr].preset[maxpreset].Pot_Value[pots]);
        Serial.printf("Value1: plugin:%d; preset:%d; pot:%d, value:%d\n", trackNr, maxpreset, pots, plugin[trackNr].preset[maxpreset].Pot_Value[pots]);
      }
    }



    // close the file:
    myFile.close();
    tft.println("Done");
    Serial.println("Done");

  } else {
    // if the file didn't open, print an error:
    tft.printf("error opening:%s\n", _trackname);
    Serial.printf("error opening:%s\n", _trackname);
  }

  tft.println("Saving done.");
  Serial.println("Saving Done");
  startUpScreen();
}
void loadPlugin(const char* trackname, int trackNr) {
  sprintf(_trackname, "%s.txt\0", trackname);
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  tft.printf("opening:%s", _trackname);
  Serial.printf("opening:%s", _trackname);
  myFile = SD.open(_trackname);
  tft.println("Done");
  Serial.println("Done");

  if (myFile) {


    // read from the file until there's nothing else in it:
    //load track 1
    tft.printf("Reading plugin from:%s", _trackname);
    Serial.printf("Reading plugin from:%s", _trackname);


    for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      for (int pots = 0; pots < 16; pots++) {
        plugin[trackNr].preset[maxpreset].Pot_Value2[pots] = myFile.read();
        Serial.printf("Value2: plugin:%d; preset:%d; pot:%d, value:%d\n", trackNr, maxpreset, pots, plugin[trackNr].preset[maxpreset].Pot_Value2[pots]);
        plugin[trackNr].preset[maxpreset].Pot_Value[pots] = myFile.read();
        Serial.printf("Value1: plugin:%d; preset:%d; pot:%d, value:%d\n", trackNr, maxpreset, pots, plugin[trackNr].preset[maxpreset].Pot_Value[pots]);
      }
    }


    tft.println("Done");
    Serial.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.printf("error opening:%s\n", _trackname);
    Serial.printf("error opening:%s\n", _trackname);
  }
}
void saveNoteFX(const char* trackname, byte trackNr) {
  sprintf(_trackname, "%s.txt\0", trackname);
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);


  // delete the file:
  tft.printf("Removing:%s", _trackname);
  Serial.printf("Removing:%s", _trackname);
  SD.remove(_trackname);
  tft.println("Done");
  Serial.println("Done");

  // open the file.
  tft.printf("Creating and opening:%s", _trackname);
  Serial.printf("Creating and opening:%s", _trackname);
  myFile = SD.open(_trackname, FILE_WRITE);
  tft.println("Done");
  Serial.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {
    //save tracks
    tft.printf("Writing NFX to:%s", _trackname);
    Serial.printf("Writing NFX to:%s", _trackname);

    //save NFX1
    for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      for (int pots = 0; pots < 16; pots++) {
        myFile.print((char)NFX1[maxpreset].Pot_Value[pots]);
        myFile.print((char)NFX2[maxpreset].Pot_Value[pots]);
        myFile.print((char)NFX3[maxpreset].Pot_Value[pots]);
        myFile.print((char)NFX4[maxpreset].Pot_Value[pots]);
      }
    }

    // close the file:
    myFile.close();
    tft.println("Done");
    Serial.println("Done");

  } else {
    // if the file didn't open, print an error:
    tft.printf("error opening:%s\n", _trackname);
    Serial.printf("error opening:%s\n", _trackname);
  }

  tft.println("Saving done.");
  Serial.println("Saving done.");
  startUpScreen();
}
void loadNoteFX(const char* trackname, int trackNr) {
  sprintf(_trackname, "%s.txt\0", trackname);
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open(_trackname);


  if (myFile) {
    tft.println("opening:");
    tft.println(_trackname);

    // read from the file until there's nothing else in it:
    //load track 1
    tft.print("Reading NFX from:");
    tft.println(_trackname);


    //load NFX1
    for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      for (int MixerColumn = 0; MixerColumn < 16; MixerColumn++) {
        NFX1[maxpreset].Pot_Value[MixerColumn] = myFile.read();
        NFX2[maxpreset].Pot_Value[MixerColumn] = myFile.read();
        NFX3[maxpreset].Pot_Value[MixerColumn] = myFile.read();
        NFX4[maxpreset].Pot_Value[MixerColumn] = myFile.read();
      }
    }




    //int channel = track[trackNr].MIDIchannel + 48;
    myFile.print((char)track[trackNr].MIDIchannel);

    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening:");
    tft.println(_trackname);
  }
}
void change_preset(int plNR) {
  //change preset
  if (button[14]) {                                                                   //press shift
    if (enc_moved[0]) {                                                               // and move the first encoder
      lastPotRow = 10;                                                                //set lastPotRow to "undefined", probably not neccessary anymore since the potvalue only gets changed when we are close to the last pos
      tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);                                  //clear the lastpotrow indicator, also probably not neccessary anymore
      plpreset[plNR] = constrain((plpreset[plNR] + encoded[0]), 0, MAX_PRESETS - 1);  // with every movement of the encoder we change the preset by -+1
      drawNrInRect(18, 1, plpreset[plNR], ILI9341_PURPLE);                            //show the new presetnr
      Plugin_View_Static();                                                           //show the actual potpositions
    }
  }
}
