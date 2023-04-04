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
  if (selectPage == NFX5_PAGE1) {
    NoteFX5_Page_Static();
  }
  if (selectPage == NFX8_PAGE1) {
    NoteFX8_Page_Static();
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
  }
  //setting up the NoteFX5-view
  if (selectPage == NFX5_PAGE1) {
    NoteFX5_Page1_Dynamic();
  }
  if (selectPage == NFX8_PAGE1) {
    NoteFX8_Page1_Dynamic();
  }


  //setting up the StepSequencer-view for drumtrack #1
  if (selectPage == DRUMTRACK) {
    drumStepSequencer();
  }
  //setting up the melodicStepSequencer-view for #2-8
  for (int i = 1; i < 8; i++) {
    if (selectPage == i) {
      melodicStepSequencer(i);
    }
  }
  //setting up the scaleSelector-view
  if (selectPage == SCALESELECT) {
    scaleSelector();
  }

  //setting up the songMode-view1
  for (int pagenr = 0; pagenr < 16; pagenr++) {
    if (selectPage == pagenr + 10) {
      songModePage(pagenr);
    }
  }

  //setting up the Recorder Page
  if (selectPage == RECORDER_PAGE) {
    recorder_Page1_Dynamic();
  }


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
  //setting up the Mixer Page 3
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
  //setting up the Mixer Page 2
  if (selectPage == MIDICC_PAGE_1) {
    midiCCpage1_Dynamic(desired_track);
  }
}
//here you have to put your NoteOn/Off´s into
void PluginNoteOn() {

  for (int desired_instruments = 1; desired_instruments < 8; desired_instruments++) {
    //send midi noteOn´s with channel 1-16
    if (track[desired_instruments].MIDIchannel < 17) {
      for (int polys = 0; polys < MAX_VOICES; polys++) {
        if (ctrack[desired_instruments].sequence[track[desired_instruments].clip_songMode].tick[nfx6_MIDItick].voice[polys] > VALUE_NOTEOFF) {
          if (track[desired_instruments].notePressed[polys]) {
            if (track[desired_instruments].playNoteOnce[polys]) {
              if (!track[desired_instruments].envActive[polys]) {


                track[desired_instruments].playNoteOnce[polys] = false;
                track[desired_instruments].envActive[polys] = true;
                Serial.printf("Note: %d, on at tick: %d\n", track[desired_instruments].notePlayed[polys], nfx6_MIDItick);

                usbMIDI.sendNoteOn(track[desired_instruments].notePlayed[polys], track[desired_instruments].MIDI_velocity, track[desired_instruments].MIDIchannel);
                MIDI.sendNoteOn(track[desired_instruments].notePlayed[polys], track[desired_instruments].MIDI_velocity, track[desired_instruments].MIDIchannel);
                for (int usbs = 0; usbs < 10; usbs++) {
                  if (!launchpad) {
                    usb_midi_devices[usbs]->sendNoteOn(track[desired_instruments].notePlayed[polys], track[desired_instruments].MIDI_velocity, track[desired_instruments].MIDIchannel);
                  }
                }
              }
            }
          }
        }
      }
      //Serial.println("");
    }
    //send plugin noteOn´s to MONOPHONIC plugins
    if (track[desired_instruments].notePressed[0]) {
      if (track[desired_instruments].playNoteOnce[0]) {
        if (!track[desired_instruments].envActive[0]) {
          
          if (track[desired_instruments].MIDIchannel == 17) {
            for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
              int Note2play = track[desired_instruments].notePlayed[0] + map(plugin[pl1NR].preset[track[desired_instruments].Ttrckprst[phrase]].Pot_Value2[MixerColumn], 0, 127, -18, 18);
              int veloCity = plugin[pl1NR].preset[track[desired_instruments].Ttrckprst[phrase]].Pot_Value2[MixerColumn + 8];
              OSC_MOD[MixerColumn]->frequency(note_frequency[Note2play] * tuning);
              usbMIDI.sendNoteOn(Note2play, veloCity, desired_instruments + 1);
              MIDI.sendNoteOn(Note2play, veloCity, desired_instruments + 1);
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
            playSdPitch1.playRaw(RAW_files[plugin[pl5NR].preset[track[desired_instruments].Ttrckprst[phrase]].Pot_Value[0]], 1);
            pl5envelope1.noteOn();
            pl5envelope2.noteOn();
            track[desired_instruments].playNoteOnce[0] = false;
            track[desired_instruments].envActive[0] = true;
          }
          if (track[desired_instruments].MIDIchannel == 22) {


            playSdPitch2.setPlaybackRate(note_frequency[track[desired_instruments].notePlayed[0]]);
            playSdPitch2.playRaw(RAW_files[plugin[pl6NR].preset[track[desired_instruments].Ttrckprst[phrase]].Pot_Value[0]], 1);
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
//here you have to put your NoteOn/Off´s into
void PluginNoteOff() {

  for (int desired_instruments = 1; desired_instruments < 8; desired_instruments++) {
    //send midi noteOff´s with channel 1-16
    if (track[desired_instruments].MIDIchannel < 17) {
      for (int polys = 0; polys < MAX_VOICES; polys++) {
        if (track[desired_instruments].envActive[polys]) {
          if (!track[desired_instruments].notePressed[polys]) {
            track[desired_instruments].envActive[polys] = false;
            Serial.printf("Note: %d, off at tick: %d\n", track[desired_instruments].notePlayed[polys], nfx6_MIDItick);
            usbMIDI.sendNoteOff(track[desired_instruments].notePlayed[polys], VELOCITYOFF, track[desired_instruments].MIDIchannel);
            MIDI.sendNoteOff(track[desired_instruments].notePlayed[polys], VELOCITYOFF, track[desired_instruments].MIDIchannel);
            for (int usbs = 0; usbs < 10; usbs++) {
              if (!launchpad) {
                usb_midi_devices[usbs]->sendNoteOff(track[desired_instruments].notePlayed[polys], VELOCITYOFF, track[desired_instruments].MIDIchannel);
              }
            }
          }
        }
      }
      //Serial.println("");
    }

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
    track[instruments].MIDI_velocity = track[instruments].volume[phrase];
    pluginVolume(track[instruments].MIDIchannel, track[instruments].volume[phrase] / 127.00);

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
    if (track[instruments].seqMode == 1) {
      NFX1presetNr = track[instruments].clip_songMode;
      NoteFX1_Change();
    }
    if (track[instruments].seqMode == 2) {
      NFX2presetNr = track[instruments].clip_songMode;
      NoteFX2_Change();
    }
    if (track[instruments].seqMode == 3) {
      NFX3presetNr = track[instruments].clip_songMode;
      NoteFX3_Change();
    }
    if (track[instruments].seqMode == 4) {
      //NFX4presetNr = track[instruments].clip_songMode;
      //NoteFX4_Change();
    }
    if (track[instruments].seqMode == 5) {
      NFX5presetNr = track[instruments].clip_songMode;
    }
  }
}

//if you have a filter with multiple outputs like the AudioFilterStateVariable
//this function will switch between the different inputs of the afterwards installed mixer
//add your filtermixer here
void selectFilterType(int des_node, byte mixerchannel) {
  FILTERMIXER[des_node]->gain(0, 0);
  FILTERMIXER[des_node]->gain(1, 0);
  FILTERMIXER[des_node]->gain(2, 0);
  FILTERMIXER[des_node]->gain(mixerchannel, 1);
}
void savePlugin(const char* trackname, byte trackNr) {
  sprintf(_trackname, "%s.txt\0", trackname);
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);


  // delete the file:
  tft.print("Removing:");
  tft.print(_trackname);
  SD.remove(_trackname);
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening:");
  tft.print(_trackname);
  myFile = SD.open(_trackname, FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {
    //save tracks
    tft.print("Writing track to:");
    tft.print(_trackname);


    if (trackNr == 17) {
      //save plugin 1 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[0]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[1]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[2]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[3]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[4]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[5]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[6]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[7]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[0]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[1]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[2]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[3]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[0]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[1]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[2]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[4]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[5]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[6]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[7]);
        myFile.print((char)plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[3]);
      }
    }
    if (trackNr == 18) {
      //save plugin 2 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          myFile.print((char)plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn]);
          myFile.print((char)plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn + 4]);
          myFile.print((char)plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn + 8]);
        }
      }
    }
    if (trackNr == 19) {
      //save plugin 3 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        myFile.print((char)plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[4]);
        myFile.print((char)plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[5]);
        myFile.print((char)plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[6]);
        myFile.print((char)plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[8]);
        myFile.print((char)plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[9]);
        myFile.print((char)plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[10]);
        myFile.print((char)plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[11]);
        myFile.print((char)plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[0]);
        myFile.print((char)plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[7]);
      }
    }
    if (trackNr == 20) {
      //save plugin 4 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          myFile.print((char)plugin[3].preset[plpreset[3]].Pot_Value[MixerColumn]);
          myFile.print((char)plugin[3].preset[plpreset[3]].Pot_Value[MixerColumn + 4]);
          myFile.print((char)plugin[3].preset[plpreset[3]].Pot_Value[MixerColumn + 8]);
        }
      }
    }
    if (trackNr == 21) {
      //save plugin 5 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        myFile.print((char)plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[4]);
        myFile.print((char)plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[5]);
        myFile.print((char)plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[6]);
        myFile.print((char)plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[8]);
        myFile.print((char)plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[9]);
        myFile.print((char)plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[10]);
        myFile.print((char)plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[11]);
        myFile.print((char)plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[0]);
        myFile.print((char)plugin[pl5NR].preset[plpreset[pl5NR]].Pot_Value[7]);
      }
    }
    if (trackNr == 22) {
      //save plugin 6 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        myFile.print((char)plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[4]);
        myFile.print((char)plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[5]);
        myFile.print((char)plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[6]);
        myFile.print((char)plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[8]);
        myFile.print((char)plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[9]);
        myFile.print((char)plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[10]);
        myFile.print((char)plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[11]);
        myFile.print((char)plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[0]);
        myFile.print((char)plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[7]);
      }
    }
    if (trackNr == 24) {
      //save plugin 8 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        myFile.print((char)plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[4]);
        myFile.print((char)plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[5]);
        myFile.print((char)plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[6]);
        myFile.print((char)plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[8]);
        myFile.print((char)plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[9]);
        myFile.print((char)plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[10]);
        myFile.print((char)plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[11]);
        myFile.print((char)plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[0]);
      }
    }
    if (trackNr == 25) {
      //save plugin 9 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        myFile.print((char)plugin[8].preset[plpreset[8]].Pot_Value[0]);
        myFile.print((char)plugin[8].preset[plpreset[8]].Pot_Value[1]);
        myFile.print((char)plugin[8].preset[plpreset[8]].Pot_Value[2]);
        myFile.print((char)plugin[8].preset[plpreset[8]].Pot_Value[3]);
        myFile.print((char)plugin[8].preset[plpreset[8]].Pot_Value[4]);
        myFile.print((char)plugin[8].preset[plpreset[8]].Pot_Value[5]);
        myFile.print((char)plugin[8].preset[plpreset[8]].Pot_Value[8]);
        myFile.print((char)plugin[8].preset[plpreset[8]].Pot_Value[9]);
        myFile.print((char)plugin[8].preset[plpreset[8]].Pot_Value[10]);
        myFile.print((char)plugin[8].preset[plpreset[8]].Pot_Value[11]);
      }
    }


    // close the file:
    myFile.close();
    tft.println("Done");

  } else {
    // if the file didn't open, print an error:
    tft.println("error opening:");
    tft.print(_trackname);
  }

  tft.println("Saving done.");
  startUpScreen();
}
void loadPlugin(const char* trackname, int trackNr) {
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
    tft.print("Reading clips from:");
    tft.println(_trackname);

    if (trackNr == 17) {
      //load pl1
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[0] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[1] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[2] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[3] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[4] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[5] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[6] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[7] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[8] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[9] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[10] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[11] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[0] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[1] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[2] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[4] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[5] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[6] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[7] = myFile.read();
        plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[3] = myFile.read();
      }
    }
    if (trackNr == 18) {
      //load plugin2 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn] = myFile.read();
          plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn + 4] = myFile.read();
          plugin[1].preset[plpreset[1]].Pot_Value[MixerColumn + 8] = myFile.read();
        }
      }
    }
    if (trackNr == 19) {
      //load plugin 3 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[4] = myFile.read();
        plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[5] = myFile.read();
        plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[6] = myFile.read();
        plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[8] = myFile.read();
        plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[9] = myFile.read();
        plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[10] = myFile.read();
        plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[11] = myFile.read();
        plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[0] = myFile.read();
        plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[7] = myFile.read();
      }
    }
    if (trackNr == 20) {
      //load plugin4 variables

      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          plugin[3].preset[plpreset[3]].Pot_Value[MixerColumn] = myFile.read();
          plugin[3].preset[plpreset[3]].Pot_Value[MixerColumn + 4] = myFile.read();
          plugin[3].preset[plpreset[3]].Pot_Value[MixerColumn + 8] = myFile.read();
        }
      }
    }
    if (trackNr == 21) {
      //load plugin 5 variables
      tft.print("reading plugin 5 from plugin5.txt...");
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        plugin[pl5NR].preset[maxpreset].Pot_Value[4] = myFile.read();
        plugin[pl5NR].preset[maxpreset].Pot_Value[5] = myFile.read();
        plugin[pl5NR].preset[maxpreset].Pot_Value[6] = myFile.read();
        plugin[pl5NR].preset[maxpreset].Pot_Value[8] = myFile.read();
        plugin[pl5NR].preset[maxpreset].Pot_Value[9] = myFile.read();
        plugin[pl5NR].preset[maxpreset].Pot_Value[10] = myFile.read();
        plugin[pl5NR].preset[maxpreset].Pot_Value[11] = myFile.read();
        plugin[pl5NR].preset[maxpreset].Pot_Value[0] = myFile.read();
        plugin[pl5NR].preset[maxpreset].Pot_Value[7] = myFile.read();
      }
    }
    if (trackNr == 22) {
      //load plugin 6 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[4] = myFile.read();
        plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[5] = myFile.read();
        plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[6] = myFile.read();
        plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[8] = myFile.read();
        plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[9] = myFile.read();
        plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[10] = myFile.read();
        plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[11] = myFile.read();
        plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[0] = myFile.read();
        plugin[pl6NR].preset[plpreset[pl6NR]].Pot_Value[7] = myFile.read();
      }
    }
    if (trackNr == 24) {
      //load plugin 8 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[4] = myFile.read();
        plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[5] = myFile.read();
        plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[6] = myFile.read();
        plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[8] = myFile.read();
        plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[9] = myFile.read();
        plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[10] = myFile.read();
        plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[11] = myFile.read();
        plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[0] = myFile.read();
      }
    }
    if (trackNr == 25) {
      //load plugin 9 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        plugin[8].preset[plpreset[8]].Pot_Value[0] = myFile.read();
        plugin[8].preset[plpreset[8]].Pot_Value[1] = myFile.read();
        plugin[8].preset[plpreset[8]].Pot_Value[2] = myFile.read();
        plugin[8].preset[plpreset[8]].Pot_Value[3] = myFile.read();
        plugin[8].preset[plpreset[8]].Pot_Value[4] = myFile.read();
        plugin[8].preset[plpreset[8]].Pot_Value[5] = myFile.read();
        plugin[8].preset[plpreset[8]].Pot_Value[8] = myFile.read();
        plugin[8].preset[plpreset[8]].Pot_Value[9] = myFile.read();
        plugin[8].preset[plpreset[8]].Pot_Value[10] = myFile.read();
        plugin[8].preset[plpreset[8]].Pot_Value[11] = myFile.read();
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
//end of the plugin-function-nightmare
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////

void saveNoteFX(const char* trackname, byte trackNr) {
  sprintf(_trackname, "%s.txt\0", trackname);
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);


  // delete the file:
  tft.print("Removing:");
  tft.print(_trackname);
  SD.remove(_trackname);
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening:");
  tft.print(_trackname);
  myFile = SD.open(_trackname, FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {
    //save tracks
    tft.print("Writing track to:");
    tft.print(_trackname);

    //save NFX1
    if (trackNr == 0) {
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          myFile.print((char)NFX1[maxpreset].Pot_Value[MixerColumn]);
          myFile.print((char)NFX1[maxpreset].Pot_Value[MixerColumn + 4]);
          myFile.print((char)NFX1[maxpreset].Pot_Value[MixerColumn + 8]);
        }
      }
    }
    if (trackNr == 1) {
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          myFile.print((char)NFX2[maxpreset].Pot_Value[MixerColumn]);
          myFile.print((char)NFX2[maxpreset].Pot_Value[MixerColumn + 4]);
          myFile.print((char)NFX2[maxpreset].Pot_Value[MixerColumn + 8]);
          myFile.print((char)NFX2[maxpreset].Pot_Value[MixerColumn + 12]);
        }
      }
    }
    if (trackNr == 2) {
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          myFile.print((char)NFX3[maxpreset].Pot_Value[MixerColumn]);
          myFile.print((char)NFX3[maxpreset].Pot_Value[MixerColumn + 4]);
          myFile.print((char)NFX3[maxpreset].Pot_Value[MixerColumn + 8]);
          myFile.print((char)NFX3[maxpreset].Pot_Value[MixerColumn + 12]);
        }
      }
    }
    if (trackNr == 3) {
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          myFile.print((char)NFX4[maxpreset].Pot_Value[MixerColumn]);
          myFile.print((char)NFX4[maxpreset].Pot_Value[MixerColumn + 4]);
          myFile.print((char)NFX4[maxpreset].Pot_Value[MixerColumn + 8]);
          myFile.print((char)NFX4[maxpreset].reset[MixerColumn]);
          myFile.print((char)NFX4[maxpreset].reset[MixerColumn + 4]);
          myFile.print((char)NFX4[maxpreset].reset[MixerColumn + 8]);
        }
      }
    }
    if (trackNr == 4) {
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          myFile.print((char)NFX5[maxpreset].Pot_Value[MixerColumn]);
          myFile.print((char)NFX5[maxpreset].Pot_Value[MixerColumn + 4]);
          myFile.print((char)NFX5[maxpreset].Pot_Value[MixerColumn + 8]);
          myFile.print((char)NFX5[maxpreset].repeats[MixerColumn]);
          myFile.print((char)NFX5[maxpreset].repeats[MixerColumn + 4]);
          myFile.print((char)NFX5[maxpreset].repeats[MixerColumn + 8]);
          //        myFile.print((char)NFX5[maxpreset].repeatED[MixerColumn]);
          //       myFile.print((char)NFX5[maxpreset].repeatED[MixerColumn + 4]);
          //     myFile.print((char)NFX5[maxpreset].repeatED[MixerColumn + 8]);
        }
      }
    }
    // close the file:
    myFile.close();
    tft.println("Done");

  } else {
    // if the file didn't open, print an error:
    tft.println("error opening:");
    tft.print(_trackname);
  }

  tft.println("Saving done.");
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
    tft.print("Reading clips from:");
    tft.println(_trackname);

    if (trackNr == 0) {
      //load NFX1
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          NFX1[maxpreset].Pot_Value[MixerColumn] = myFile.read();
          NFX1[maxpreset].Pot_Value[MixerColumn + 4] = myFile.read();
          NFX1[maxpreset].Pot_Value[MixerColumn + 8] = myFile.read();
        }
      }
    }
    if (trackNr == 1) {
      //load NFX2
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          NFX2[maxpreset].Pot_Value[MixerColumn] = myFile.read();
          NFX2[maxpreset].Pot_Value[MixerColumn + 4] = myFile.read();
          NFX2[maxpreset].Pot_Value[MixerColumn + 8] = myFile.read();
          NFX2[maxpreset].Pot_Value[MixerColumn + 12] = myFile.read();
        }
      }
    }
    if (trackNr == 2) {
      //load NFX3
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          NFX3[maxpreset].Pot_Value[MixerColumn] = myFile.read();
          NFX3[maxpreset].Pot_Value[MixerColumn + 4] = myFile.read();
          NFX3[maxpreset].Pot_Value[MixerColumn + 8] = myFile.read();
          NFX3[maxpreset].Pot_Value[MixerColumn + 12] = myFile.read();
        }
      }
    }
    if (trackNr == 3) {
      //load NFX4
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          NFX4[maxpreset].Pot_Value[MixerColumn] = myFile.read();
          NFX4[maxpreset].Pot_Value[MixerColumn + 4] = myFile.read();
          NFX4[maxpreset].Pot_Value[MixerColumn + 8] = myFile.read();
          NFX4[maxpreset].reset[MixerColumn] = myFile.read();
          NFX4[maxpreset].reset[MixerColumn + 4] = myFile.read();
          NFX4[maxpreset].reset[MixerColumn + 8] = myFile.read();
        }
      }
    }
    if (trackNr == 4) {
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
          NFX5[maxpreset].Pot_Value[MixerColumn] = myFile.read();
          NFX5[maxpreset].Pot_Value[MixerColumn + 4] = myFile.read();
          NFX5[maxpreset].Pot_Value[MixerColumn + 8] = myFile.read();
          NFX5[maxpreset].repeats[MixerColumn] = myFile.read();
          NFX5[maxpreset].repeats[MixerColumn + 4] = myFile.read();
          NFX5[maxpreset].repeats[MixerColumn + 8] = myFile.read();
          //       NFX5[maxpreset].repeatED[MixerColumn] = myFile.read();
          //     NFX5[maxpreset].repeatED[MixerColumn + 4] = myFile.read();
          //   NFX5[maxpreset].repeatED[MixerColumn + 8] = myFile.read();
        }
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
void DrumPluginPlay() {

  //play drumplugin when midichannel = 18
  if (track[0].MIDIchannel == 18) {

    if (drumnotes[0]) {
      drumnotes[0] = false;
      playSdWav1.play(wavKit[0]);
    }
    if (drumnotes[1]) {
      drumnotes[1] = false;
      playSdWav2.play(wavKit[1]);
    }
    if (drumnotes[2]) {
      drumnotes[2] = false;
      playSdWav3.play(wavKit[2]);
    }
    if (drumnotes[3]) {
      drumnotes[3] = false;
      playSdWav4.play(wavKit[3]);
    }
    if (drumnotes[4]) {
      drumnotes[4] = false;
      playSdWav5.play(wavKit[4]);
    }
    if (drumnotes[5]) {
      drumnotes[5] = false;
      playSdWav6.play(wavKit[5]);
    }
    if (drumnotes[6]) {
      drumnotes[6] = false;
      playSdWav7.play(wavKit[6]);
    }
    if (drumnotes[7]) {
      drumnotes[7] = false;
      playSdWav8.play(wavKit[7]);
    }
    if (drumnotes[8]) {
      drumnotes[8] = false;
      playSdWav9.play(wavKit[8]);
    }
    if (drumnotes[9]) {
      drumnotes[9] = false;
      playSdWav10.play(wavKit[9]);
    }
    if (drumnotes[10]) {
      drumnotes[10] = false;
      playSdWav11.play(wavKit[10]);
    }
    if (drumnotes[11]) {
      drumnotes[11] = false;
      //playSdWav12.play(wavKit[11]);
    }
  }
  //play Memory drumplugin when midichannel = 20
  if (track[0].MIDIchannel == 20) {
    if (drumnotes[0]) {
      drumnotes[0] = false;
      playMem1.play(AudioSampleKick);
    }
    if (drumnotes[1]) {
      drumnotes[1] = false;
      playMem2.play(AudioSampleSnare);
    }
    if (drumnotes[2]) {
      drumnotes[2] = false;
      playMem3.play(AudioSampleP2);
    }
    if (drumnotes[3]) {
      drumnotes[3] = false;
      playMem4.play(AudioSampleHihat);
    }
    if (drumnotes[4]) {
      drumnotes[4] = false;
      playMem5.play(AudioSampleCashregister);
    }
    if (drumnotes[5]) {
      drumnotes[5] = false;
      playMem6.play(AudioSampleTomtom);
    }
    if (drumnotes[6]) {
      drumnotes[6] = false;
      playMem7.play(AudioSampleGong);
    }
    if (drumnotes[7]) {
      drumnotes[7] = false;
      playMem7.play(AudioSamplePongblip);
    }
    if (drumnotes[8]) {
      drumnotes[8] = false;
      playMem7.play(AudioSampleClap);
    }
    if (drumnotes[9]) {
      drumnotes[9] = false;
      //playSdWav10.play("P9.WAV");
    }
    if (drumnotes[10]) {
      drumnotes[10] = false;
      //playSdWav11.play("P10.WAV");
    }
    if (drumnotes[11]) {
      drumnotes[11] = false;
      //playSdWav12.play("P11.WAV");
    }
  }
  //play Memory drumplugin when midichannel = 20
  if (track[0].MIDIchannel == 23) {

    if (drumnotes[0]) {
      drumnotes[0] = false;
      pl7drum1.noteOn();
    }
    if (drumnotes[1]) {
      drumnotes[1] = false;
      pl7envelope1.noteOn();

      if (track[0].MIDItick >= track[0].stepLength) {
        pl7envelope1.noteOff();
      }
    }
    if (drumnotes[2]) {
      drumnotes[2] = false;
      pl7envelope2.noteOn();
      pl7envelope3.noteOn();

      if (track[0].MIDItick >= track[0].stepLength) {
        pl7envelope2.noteOff();
        pl7envelope3.noteOff();
      }
    }
    if (drumnotes[3]) {
      drumnotes[3] = false;
      //playMem4.play(AudioSampleHihat);

      if (track[0].MIDItick >= track[0].stepLength) {
      }
    }

    if (drumnotes[4]) {
      drumnotes[4] = false;
      //playMem4.play(AudioSampleHihat);
    } else {
    }

    if (drumnotes[5]) {
      drumnotes[5] = false;
      //playMem4.play(AudioSampleHihat);
    }
  }
}
