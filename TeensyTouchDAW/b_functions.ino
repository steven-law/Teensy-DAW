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
    Plugin7_Page_Static(1);
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
    Plugin1_Control();
  }
  //setting up the Plugin1 Page2-view
  if (selectPage == PLUGIN1_PAGE2) {
    Plugin1_Page2_Dynamic();
    Plugin1_Control2();
  }

  //setting up the Plugin2 Page1-view
  if (selectPage == PLUGIN2_PAGE1) {
    Plugin2_Page1_Dynamic();
    Plugin2_Control();
  }


  /////////////////////////////////////////////////////////////////////////////
  //setting up the Plugin3 Page1-view
  if (selectPage == PLUGIN3_PAGE1) {
    Plugin3_Page1_Dynamic();
    Plugin3_Control();
  }
  /////////////////////////////////////////////////////////////////////////////


  //setting up the Plugin4 Page1-view
  if (selectPage == PLUGIN4_PAGE1) {
    Plugin4_Page1_Dynamic();
    Plugin4_Control();
  }

  //setting up the Plugin5 Page1-view
  if (selectPage == PLUGIN5_PAGE1) {
    Plugin5_Page1_Dynamic();
    Plugin5_Control();
  }
  //setting up the Plugin6 Page1-view
  if (selectPage == PLUGIN6_PAGE1) {
    Plugin6_Page1_Dynamic();
    Plugin6_Control();
  }
  //setting up thePlugin7 Page1-view
  if (selectPage == PLUGIN7_PAGE1) {
    Plugin7_Page1_Dynamic();
    Plugin7_Control1();
  }
  //setting up thePlugin7 Page2-view
  if (selectPage == PLUGIN7_PAGE2) {
    Plugin7_Page2_Dynamic();
    Plugin7_Control2();
  }
  //setting up the Plugin8 Page1-view
  if (selectPage == PLUGIN8_PAGE1) {
    Plugin8_Page1_Dynamic();
    Plugin8_Control();
  }
  //setting up the Plugin9 Page1-view
  if (selectPage == PLUGIN9_PAGE1) {
    Plugin9_Page1_Dynamic();
    Plugin9_Control();
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
    NoteFX4_Control();
  }
  //setting up the NoteFX5-view
  if (selectPage == NFX5_PAGE1) {
    NoteFX5_Page1_Dynamic();
    //NoteFX5_Control();
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
    if (track[desired_instruments].notePressed) {
      if (track[desired_instruments].playNoteOnce) {
        if (!track[desired_instruments].envActive) {

          //send midi noteOn´s with channel 1-16
          if (track[desired_instruments].MIDIchannel < 17) {
            usbMIDI.sendNoteOn(track[desired_instruments].notePlayed, track[desired_instruments].MIDI_velocity, track[desired_instruments].MIDIchannel);
            MIDI.sendNoteOn(track[desired_instruments].notePlayed, track[desired_instruments].MIDI_velocity, track[desired_instruments].MIDIchannel);
            for (int usbs = 0; usbs < 10; usbs++) {
              if (!launchpad) {
                usb_midi_devices[usbs]->sendNoteOn(track[desired_instruments].notePlayed, track[desired_instruments].MIDI_velocity, track[desired_instruments].MIDIchannel);
              }
            }
            track[desired_instruments].playNoteOnce = false;
            track[desired_instruments].envActive = true;
          }
          //send plugin noteOn´s to plugins
          if (track[desired_instruments].MIDIchannel == 17) {
            waveform1.frequency(note_frequency[track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[0]]);
            waveform2.frequency(note_frequency[track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[1]]);
            waveform3.frequency(note_frequency[track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[2]]);
            waveform4.frequency(note_frequency[track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[3]]);
            envelope1.noteOn();
            envelope2.noteOn();
            usbMIDI.sendNoteOn(track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[0], pl1[track[desired_instruments].presetNr[phrase]].note_Velo_graph[0], desired_instruments + 1);
            usbMIDI.sendNoteOn(track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[1], pl1[track[desired_instruments].presetNr[phrase]].note_Velo_graph[1], desired_instruments + 1);
            usbMIDI.sendNoteOn(track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[2], pl1[track[desired_instruments].presetNr[phrase]].note_Velo_graph[2], desired_instruments + 1);
            usbMIDI.sendNoteOn(track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[3], pl1[track[desired_instruments].presetNr[phrase]].note_Velo_graph[3], desired_instruments + 1);
            MIDI.sendNoteOn(track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[0], pl1[track[desired_instruments].presetNr[phrase]].note_Velo_graph[0], desired_instruments + 1);
            MIDI.sendNoteOn(track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[1], pl1[track[desired_instruments].presetNr[phrase]].note_Velo_graph[1], desired_instruments + 1);
            MIDI.sendNoteOn(track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[2], pl1[track[desired_instruments].presetNr[phrase]].note_Velo_graph[2], desired_instruments + 1);
            MIDI.sendNoteOn(track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[3], pl1[track[desired_instruments].presetNr[phrase]].note_Velo_graph[3], desired_instruments + 1);
            track[desired_instruments].playNoteOnce = false;
            track[desired_instruments].envActive = true;
            //Serial.println("crackling");
          }
          if (track[desired_instruments].MIDIchannel == 19) {
            pl3waveform1.frequency(note_frequency[track[desired_instruments].notePlayed]);
            pl3envelope1.noteOn();
            pl3envelope2.noteOn();
            track[desired_instruments].playNoteOnce = false;
            track[desired_instruments].envActive = true;
          }
          if (track[desired_instruments].MIDIchannel == 21) {
            double note_ratio = pow(2.0, ((double)(track[desired_instruments].notePlayed - SAMPLE_ROOT) / 12.0));
            playSdPitch1.setPlaybackRate(note_ratio);
            //playSdPitch1.playRaw(RAW_files[pl5[track[desired_track].presetNr[phrase]].selected_file], 1);
            playSdPitch1.playRaw(pl5sample->sampledata, pl5sample->samplesize, 1);
            pl5envelope1.noteOn();
            pl5envelope2.noteOn();
            track[desired_instruments].playNoteOnce = false;
            track[desired_instruments].envActive = true;
            //Serial.println("crackling2");
          }
          if (track[desired_instruments].MIDIchannel == 22) {
            double note_ratio = pow(2.0, ((double)(track[desired_instruments].notePlayed - SAMPLE_ROOT) / 12.0));

            playSdPitch2.setPlaybackRate(note_ratio);
            playSdPitch2.playRaw(RAW_files[pl6[track[desired_instruments].presetNr[phrase]].selected_file], 1);
            pl6envelope1.noteOn();
            pl6envelope2.noteOn();
            track[desired_instruments].playNoteOnce = false;
            track[desired_instruments].envActive = true;
          }
          if (track[desired_instruments].MIDIchannel == 24) {
            pl8waveform1.frequency(note_frequency[track[desired_instruments].notePlayed]);
            pl8envelope1.noteOn();
            pl8envelope2.noteOn();
            track[desired_instruments].playNoteOnce = false;
            track[desired_instruments].envActive = true;
          }
          if (track[desired_instruments].MIDIchannel == 25) {
            pl9string1.noteOn(note_frequency[track[desired_instruments].notePlayed], 1);
            track[desired_instruments].playNoteOnce = false;
            track[desired_instruments].envActive = true;
          }
        }
      }
    }
  }
}
//here you have to put your NoteOn/Off´s into
void PluginNoteOff() {

  for (int desired_instruments = 1; desired_instruments < 8; desired_instruments++) {

    if (!track[desired_instruments].notePressed) {
      if (track[desired_instruments].envActive) {

        //send midi noteOff´s with channel 1-16
        if (track[desired_instruments].MIDIchannel < 17) {
          track[desired_instruments].envActive = false;
          usbMIDI.sendNoteOff(track[desired_instruments].notePlayed, VELOCITYOFF, track[desired_instruments].MIDIchannel);
          MIDI.sendNoteOff(track[desired_instruments].notePlayed, VELOCITYOFF, track[desired_instruments].MIDIchannel);
          for (int usbs = 0; usbs < 10; usbs++) {
            if (!launchpad) {
              usb_midi_devices[usbs]->sendNoteOff(track[desired_instruments].notePlayed, VELOCITYOFF, track[desired_instruments].MIDIchannel);
            }
          }
        }
        //send plugin noteOff´s to plugins
        if (track[desired_instruments].MIDIchannel == 17) {
          track[desired_instruments].envActive = false;
          envelope1.noteOff();
          envelope2.noteOff();
          usbMIDI.sendNoteOff(track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[0], pl1[track[desired_instruments].presetNr[phrase]].note_Velo_graph[0], desired_instruments + 1);
          usbMIDI.sendNoteOff(track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[1], pl1[track[desired_instruments].presetNr[phrase]].note_Velo_graph[1], desired_instruments + 1);
          usbMIDI.sendNoteOff(track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[2], pl1[track[desired_instruments].presetNr[phrase]].note_Velo_graph[2], desired_instruments + 1);
          usbMIDI.sendNoteOff(track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[3], pl1[track[desired_instruments].presetNr[phrase]].note_Velo_graph[3], desired_instruments + 1);
          MIDI.sendNoteOff(track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[0], pl1[track[desired_instruments].presetNr[phrase]].note_Velo_graph[0], desired_instruments + 1);
          MIDI.sendNoteOff(track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[1], pl1[track[desired_instruments].presetNr[phrase]].note_Velo_graph[1], desired_instruments + 1);
          MIDI.sendNoteOff(track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[2], pl1[track[desired_instruments].presetNr[phrase]].note_Velo_graph[2], desired_instruments + 1);
          MIDI.sendNoteOff(track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[3], pl1[track[desired_instruments].presetNr[phrase]].note_Velo_graph[3], desired_instruments + 1);
        }
        if (track[desired_instruments].MIDIchannel == 19) {
          track[desired_instruments].envActive = false;
          pl3envelope1.noteOff();
          pl3envelope2.noteOff();
        }
        if (track[desired_instruments].MIDIchannel == 21) {
          track[desired_instruments].envActive = false;
          pl5envelope1.noteOff();
          pl5envelope2.noteOff();
        }
        if (track[desired_instruments].MIDIchannel == 22) {
          track[desired_instruments].envActive = false;
          pl6envelope1.noteOff();
          pl6envelope2.noteOff();
        }
        if (track[desired_instruments].MIDIchannel == 24) {
          track[desired_instruments].envActive = false;
          pl8envelope1.noteOff();
          pl8envelope2.noteOff();
        }
        if (track[desired_instruments].MIDIchannel == 25) {
          track[desired_instruments].envActive = false;
          pl9string1.noteOff(0);
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
      pl1presetNr = track[instruments].presetNr[phrase];
      Plugin1_Change();
    }
    if (track[instruments].MIDIchannel == 18) {
      pl2presetNr = track[instruments].presetNr[phrase];
      Plugin2_Change();
    }
    if (track[instruments].MIDIchannel == 19) {
      pl3presetNr = track[instruments].presetNr[phrase];
      Plugin3_Change();
    }
    if (track[instruments].MIDIchannel == 20) {
      pl4presetNr = track[instruments].presetNr[phrase];
      Plugin4_Change();
    }
    if (track[instruments].MIDIchannel == 21) {
      pl5presetNr = track[instruments].presetNr[phrase];
      Plugin5_Change();
    }
    if (track[instruments].MIDIchannel == 22) {
      pl6presetNr = track[instruments].presetNr[phrase];
      Plugin6_Change();
    }
    if (track[instruments].MIDIchannel == 23) {
      pl7presetNr = track[instruments].presetNr[phrase];
    }
    if (track[instruments].MIDIchannel == 24) {
      pl8presetNr = track[instruments].presetNr[phrase];
      Plugin8_Change();
    }
    if (track[instruments].MIDIchannel == 25) {
      pl9presetNr = track[instruments].presetNr[phrase];
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
      //NoteFX5_Change();
    }
  }
}

//if you have a filter with multiple outputs like the AudioFilterStateVariable
//this function will switch between the different inputs of the afterwards installed mixer
//add your filtermixer here
void selectFilterType(int pluginchannel, byte mixerchannel) {
  if (pluginchannel == 17) {
    pl1mixer2.gain(0, 0);
    pl1mixer2.gain(1, 0);
    pl1mixer2.gain(2, 0);
    pl1mixer2.gain(mixerchannel, 1);
  }
  if (pluginchannel == 19) {
    pl3mixer1.gain(0, 0);
    pl3mixer1.gain(1, 0);
    pl3mixer1.gain(2, 0);
    pl3mixer1.gain(mixerchannel, 1);
  }
  if (pluginchannel == 21) {
    pl5mixer1.gain(0, 0);
    pl5mixer1.gain(1, 0);
    pl5mixer1.gain(2, 0);
    pl5mixer1.gain(mixerchannel, 1);
  }
  if (pluginchannel == 22) {
    pl6mixer1.gain(0, 0);
    pl6mixer1.gain(1, 0);
    pl6mixer1.gain(2, 0);
    pl6mixer1.gain(mixerchannel, 1);
  }
  if (pluginchannel == 25) {
    pl9mixer1.gain(0, 0);
    pl9mixer1.gain(1, 0);
    pl9mixer1.gain(2, 0);
    pl9mixer1.gain(mixerchannel, 1);
  }
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
        myFile.print((char)pl1[maxpreset].note_Offset_graph[0]);
        myFile.print((char)pl1[maxpreset].note_Offset_graph[1]);
        myFile.print((char)pl1[maxpreset].note_Offset_graph[2]);
        myFile.print((char)pl1[maxpreset].note_Offset_graph[3]);
        myFile.print((char)pl1[maxpreset].wfSelect[0]);
        myFile.print((char)pl1[maxpreset].wfSelect[1]);
        myFile.print((char)pl1[maxpreset].wfSelect[2]);
        myFile.print((char)pl1[maxpreset].wfSelect[3]);
        myFile.print((char)pl1[maxpreset].note_Velo_graph[0]);
        myFile.print((char)pl1[maxpreset].note_Velo_graph[1]);
        myFile.print((char)pl1[maxpreset].note_Velo_graph[2]);
        myFile.print((char)pl1[maxpreset].note_Velo_graph[3]);
        myFile.print((char)pl1[maxpreset].Filter1_Frequency_graph);
        myFile.print((char)pl1[maxpreset].Filter1_Resonance_graph);
        myFile.print((char)pl1[maxpreset].Filter1_Sweep_graph);
        myFile.print((char)pl1[maxpreset].Env1_Attack_graph);
        myFile.print((char)pl1[maxpreset].Env1_Decay_graph);
        myFile.print((char)pl1[maxpreset].Env1_Sustain_graph);
        myFile.print((char)pl1[maxpreset].Env1_Release_graph);
        myFile.print((char)pl1[maxpreset].Filter1_Type_graph);
      }
    }
    if (trackNr == 18) {
      //save plugin 2 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int touchX = 1; touchX < 5; touchX++) {
          myFile.print((char)pl2[maxpreset].Pot_Value_graph[touchX - 1]);
          myFile.print((char)pl2[maxpreset].Pot_Value_graph[touchX + 3]);
          myFile.print((char)pl2[maxpreset].Pot_Value_graph[touchX + 7]);
        }
      }
    }
    if (trackNr == 19) {
      //save plugin 3 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        myFile.print((char)pl3[maxpreset].Filter1_Frequency_graph);
        myFile.print((char)pl3[maxpreset].Filter1_Resonance_graph);
        myFile.print((char)pl3[maxpreset].Filter1_Sweep_graph);
        myFile.print((char)pl3[maxpreset].Env1_Attack_graph);
        myFile.print((char)pl3[maxpreset].Env1_Decay_graph);
        myFile.print((char)pl3[maxpreset].Env1_Sustain_graph);
        myFile.print((char)pl3[maxpreset].Env1_Release_graph);
        myFile.print((char)pl3[maxpreset].wfSelect);
        myFile.print((char)pl3[maxpreset].Filter1_Type);
      }
    }
    if (trackNr == 20) {
      //save plugin 4 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int touchX = 1; touchX < 5; touchX++) {
          myFile.print((char)pl4[maxpreset].Pot_Value_graph[touchX - 1]);
          myFile.print((char)pl4[maxpreset].Pot_Value_graph[touchX + 3]);
          myFile.print((char)pl4[maxpreset].Pot_Value_graph[touchX + 7]);
        }
      }
    }
    if (trackNr == 21) {
      //save plugin 5 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        myFile.print((char)pl5[maxpreset].Filter1_Frequency_graph);
        myFile.print((char)pl5[maxpreset].Filter1_Resonance_graph);
        myFile.print((char)pl5[maxpreset].Filter1_Sweep_graph);
        myFile.print((char)pl5[maxpreset].Env1_Attack_graph);
        myFile.print((char)pl5[maxpreset].Env1_Decay_graph);
        myFile.print((char)pl5[maxpreset].Env1_Sustain_graph);
        myFile.print((char)pl5[maxpreset].Env1_Release_graph);
        myFile.print((char)pl5[maxpreset].selected_file_graph);
        myFile.print((char)pl5[maxpreset].Volume_graph);
        myFile.print((char)pl5[maxpreset].Filter1_Type);
      }
    }
    if (trackNr == 22) {
      //save plugin 6 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        myFile.print((char)pl6[maxpreset].Filter1_Frequency_graph);
        myFile.print((char)pl6[maxpreset].Filter1_Resonance_graph);
        myFile.print((char)pl6[maxpreset].Filter1_Sweep_graph);
        myFile.print((char)pl6[maxpreset].Env1_Attack_graph);
        myFile.print((char)pl6[maxpreset].Env1_Decay_graph);
        myFile.print((char)pl6[maxpreset].Env1_Sustain_graph);
        myFile.print((char)pl6[maxpreset].Env1_Release_graph);
        myFile.print((char)pl6[maxpreset].selected_file_graph);
        myFile.print((char)pl6[maxpreset].Volume_graph);
        myFile.print((char)pl6[maxpreset].Filter1_Type);
      }
    }
    if (trackNr == 24) {
      //save plugin 8 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        myFile.print((char)pl8[maxpreset].Filter1_Frequency_graph);
        myFile.print((char)pl8[maxpreset].Filter1_Resonance_graph);
        myFile.print((char)pl8[maxpreset].Filter1_Sweep_graph);
        myFile.print((char)pl8[maxpreset].Env1_Attack_graph);
        myFile.print((char)pl8[maxpreset].Env1_Decay_graph);
        myFile.print((char)pl8[maxpreset].Env1_Sustain_graph);
        myFile.print((char)pl8[maxpreset].Env1_Release_graph);
        myFile.print((char)pl8[maxpreset].wfSelect);
      }
    }
    if (trackNr == 25) {
      //save plugin 9 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        myFile.print((char)pl9[maxpreset].wah_form_graph);
        myFile.print((char)pl9[maxpreset].wah_rate_graph);
        myFile.print((char)pl9[maxpreset].wah_sweep_graph);
        myFile.print((char)pl9[maxpreset].wah_freq_graph);
        myFile.print((char)pl9[maxpreset].wah_reso_graph);
        myFile.print((char)pl9[maxpreset].wavefold_graph);
        myFile.print((char)pl9[maxpreset].Filter1_Frequency_graph);
        myFile.print((char)pl9[maxpreset].Filter1_Resonance_graph);
        myFile.print((char)pl9[maxpreset].Filter1_Sweep_graph);
        myFile.print((char)pl9[maxpreset].Filter1_Type_graph);
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
        pl1[maxpreset].note_Offset_graph[0] = myFile.read();
        pl1[maxpreset].note_Offset_graph[1] = myFile.read();
        pl1[maxpreset].note_Offset_graph[2] = myFile.read();
        pl1[maxpreset].note_Offset_graph[3] = myFile.read();
        pl1[maxpreset].wfSelect[0] = myFile.read();
        pl1[maxpreset].wfSelect[1] = myFile.read();
        pl1[maxpreset].wfSelect[2] = myFile.read();
        pl1[maxpreset].wfSelect[3] = myFile.read();
        pl1[maxpreset].note_Velo_graph[0] = myFile.read();
        pl1[maxpreset].note_Velo_graph[1] = myFile.read();
        pl1[maxpreset].note_Velo_graph[2] = myFile.read();
        pl1[maxpreset].note_Velo_graph[3] = myFile.read();
        pl1[maxpreset].Filter1_Frequency_graph = myFile.read();
        pl1[maxpreset].Filter1_Resonance_graph = myFile.read();
        pl1[maxpreset].Filter1_Sweep_graph = myFile.read();
        pl1[maxpreset].Env1_Attack_graph = myFile.read();
        pl1[maxpreset].Env1_Decay_graph = myFile.read();
        pl1[maxpreset].Env1_Sustain_graph = myFile.read();
        pl1[maxpreset].Env1_Release_graph = myFile.read();
        pl1[maxpreset].Filter1_Type_graph = myFile.read();
      }
    }
    if (trackNr == 18) {
      //load plugin2 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int touchX = 1; touchX < 5; touchX++) {
          pl2[maxpreset].Pot_Value_graph[touchX - 1] = myFile.read();
          pl2[maxpreset].Pot_Value_graph[touchX + 3] = myFile.read();
          pl2[maxpreset].Pot_Value_graph[touchX + 7] = myFile.read();
        }
      }
    }
    if (trackNr == 19) {
      //load plugin 3 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        pl3[maxpreset].Filter1_Frequency_graph = myFile.read();
        pl3[maxpreset].Filter1_Resonance_graph = myFile.read();
        pl3[maxpreset].Filter1_Sweep_graph = myFile.read();
        pl3[maxpreset].Env1_Attack_graph = myFile.read();
        pl3[maxpreset].Env1_Decay_graph = myFile.read();
        pl3[maxpreset].Env1_Sustain_graph = myFile.read();
        pl3[maxpreset].Env1_Release_graph = myFile.read();
        pl3[maxpreset].wfSelect = myFile.read();
        pl3[maxpreset].Filter1_Type = myFile.read();
      }
    }
    if (trackNr == 20) {
      //load plugin4 variables

      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        for (int touchX = 1; touchX < 5; touchX++) {
          pl4[maxpreset].Pot_Value_graph[touchX - 1] = myFile.read();
          pl4[maxpreset].Pot_Value_graph[touchX + 3] = myFile.read();
          pl4[maxpreset].Pot_Value_graph[touchX + 7] = myFile.read();
        }
      }
    }
    if (trackNr == 21) {
      //load plugin 5 variables
      tft.print("reading plugin 5 from plugin5.txt...");
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        pl5[maxpreset].Filter1_Frequency_graph = myFile.read();
        pl5[maxpreset].Filter1_Resonance_graph = myFile.read();
        pl5[maxpreset].Filter1_Sweep_graph = myFile.read();
        pl5[maxpreset].Env1_Attack_graph = myFile.read();
        pl5[maxpreset].Env1_Decay_graph = myFile.read();
        pl5[maxpreset].Env1_Sustain_graph = myFile.read();
        pl5[maxpreset].Env1_Release_graph = myFile.read();
        pl5[maxpreset].selected_file_graph = myFile.read();
        pl5[maxpreset].Volume_graph = myFile.read();
        pl5[maxpreset].Filter1_Type = myFile.read();
      }
    }
    if (trackNr == 22) {
      //load plugin 6 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        pl6[maxpreset].Filter1_Frequency_graph = myFile.read();
        pl6[maxpreset].Filter1_Resonance_graph = myFile.read();
        pl6[maxpreset].Filter1_Sweep_graph = myFile.read();
        pl6[maxpreset].Env1_Attack_graph = myFile.read();
        pl6[maxpreset].Env1_Decay_graph = myFile.read();
        pl6[maxpreset].Env1_Sustain_graph = myFile.read();
        pl6[maxpreset].Env1_Release_graph = myFile.read();
        pl6[maxpreset].selected_file_graph = myFile.read();
        pl6[maxpreset].Volume_graph = myFile.read();
        pl6[maxpreset].Filter1_Type = myFile.read();
      }
    }
    if (trackNr == 24) {
      //load plugin 8 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        pl8[maxpreset].Filter1_Frequency_graph = myFile.read();
        pl8[maxpreset].Filter1_Resonance_graph = myFile.read();
        pl8[maxpreset].Filter1_Sweep_graph = myFile.read();
        pl8[maxpreset].Env1_Attack_graph = myFile.read();
        pl8[maxpreset].Env1_Decay_graph = myFile.read();
        pl8[maxpreset].Env1_Sustain_graph = myFile.read();
        pl8[maxpreset].Env1_Release_graph = myFile.read();
        pl8[maxpreset].wfSelect = myFile.read();
      }
    }
    if (trackNr == 25) {
      //load plugin 8 variables
      for (int maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
        pl9[maxpreset].wah_form_graph = myFile.read();
        pl9[maxpreset].wah_rate_graph = myFile.read();
        pl9[maxpreset].wah_sweep_graph = myFile.read();
        pl9[maxpreset].wah_freq_graph = myFile.read();
        pl9[maxpreset].wah_reso_graph = myFile.read();
        pl9[maxpreset].wavefold_graph = myFile.read();
        pl9[maxpreset].Filter1_Frequency_graph = myFile.read();
        pl9[maxpreset].Filter1_Resonance_graph = myFile.read();
        pl9[maxpreset].Filter1_Sweep_graph = myFile.read();
        pl9[maxpreset].Filter1_Type_graph = myFile.read();
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
    } else {
      pl7envelope1.noteOff();
    }

    if (drumnotes[2]) {
      drumnotes[2] = false;
      pl7envelope2.noteOn();
      pl7envelope3.noteOn();
    } else {
      pl7envelope2.noteOff();
      pl7envelope3.noteOff();
    }

    if (drumnotes[3]) {
      drumnotes[3] = false;
      //playMem4.play(AudioSampleHihat);
    } else {
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


void envelopeA(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueA != map(Potentiometer[cols], 0, 127, 0, ATTACK_TIME)) {
    PotValueA = map(Potentiometer[cols], 0, 127, 0, ATTACK_TIME);
    ENVELOPE1[des_env]->attack(PotValueA);
    ENVELOPE2[des_env]->attack(PotValueA);
    drawPot(MixerColumnPos, ROW, Potentiometer[cols], PotValueA, "Atck", trackColor[desired_track]);
  }
}
void envelopeD(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueD != map(Potentiometer[cols], 0, 127, 0, DECAY_TIME)) {
    PotValueD = map(Potentiometer[cols], 0, 127, 0, DECAY_TIME);
    ENVELOPE1[des_env]->decay(PotValueD);
    ENVELOPE2[des_env]->decay(PotValueD);
    drawPot_2(MixerColumnPos, ROW, Potentiometer[cols], PotValueD, "Dec", trackColor[desired_track]);
  }
}
void envelopeS(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueS != (float)(Potentiometer[cols] / SUSTAIN_LVL)) {
    PotValueS = (float)(Potentiometer[cols] / SUSTAIN_LVL);
    ENVELOPE1[des_env]->sustain(PotValueS);
    ENVELOPE2[des_env]->sustain(PotValueS);
    drawPot_3(MixerColumnPos, ROW, Potentiometer[cols], Potentiometer[cols], "Sus", trackColor[desired_track]);
  }
}
void envelopeR(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueR != map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME)) {
    PotValueR = map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME);
    ENVELOPE1[des_env]->release(PotValueR);
    ENVELOPE2[des_env]->release(PotValueR);
    drawPot_4(MixerColumnPos, ROW, Potentiometer[cols], PotValueR, "Rel", trackColor[desired_track]);
  }
}
void envelopeH(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueH != map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME)) {
    PotValueH = map(Potentiometer[cols], 0, 127, 0, RELEASE_TIME);
    ENVELOPE1[des_env]->hold(PotValueH);
    ENVELOPE2[des_env]->hold(PotValueH);
    drawPot_3(MixerColumnPos, ROW, Potentiometer[cols], PotValueH, "Hld", trackColor[desired_track]);
  }
}
void ADSR(int des_env, int COL, int ROW) {
  envelopeA(des_env, COL, ROW);
  envelopeD(des_env, COL + 1, ROW);
  envelopeS(des_env, COL + 2, ROW);
  envelopeR(des_env, COL + 3, ROW);
}
void AR(int des_env, int COL, int ROW) {
  envelopeA(des_env, COL, ROW);
  envelopeR(des_env, COL+1, ROW);
}
void AD(int des_env, int COL, int ROW) {
  envelopeA(des_env, COL, ROW);
  envelopeD(des_env, COL+1, ROW);
}
void AHR(int des_env, int COL, int ROW) {
  envelopeA(des_env, COL, ROW);
  envelopeH(des_env, COL+1, ROW);
  envelopeR(des_env, COL+2, ROW);
}

void StateVar_Filter(int des_env, int COL, int ROW) {
  StateVar_Frequency(des_env, COL, ROW);
  StateVar_Resonance(des_env, COL + 1, ROW);
  StateVar_Sweep(des_env, COL + 2, ROW);
  StateVar_Type(des_env, COL + 3, ROW);
}
void StateVar_Frequency(int des_env, int cols, int ROW) {
   int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueSVF_FREQ != Potentiometer[cols]) {
    PotValueSVF_FREQ = Potentiometer[cols];
    STATEFILTER[des_env]->frequency(note_frequency[PotValueSVF_FREQ]);
    drawPot(MixerColumnPos, ROW, Potentiometer[cols], note_frequency[PotValueSVF_FREQ], "Freq", trackColor[desired_track]);
  }
}
void StateVar_Resonance(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueSVF_RES != (float)(Potentiometer[cols] / SVF_RES)) {
    PotValueSVF_RES = (float)(Potentiometer[cols] / SVF_RES);
    STATEFILTER[des_env]->resonance(PotValueSVF_RES);
    drawPot_2(MixerColumnPos, ROW, Potentiometer[cols], Potentiometer[cols], "Reso", trackColor[desired_track]);
  }
}
void StateVar_Sweep(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueSVF_SWP != (float)(Potentiometer[cols] / SVF_SWP)) {
    PotValueSVF_SWP = (float)(Potentiometer[cols] / SVF_SWP);
    STATEFILTER[des_env]->octaveControl(PotValueSVF_SWP);
    drawPot_2(MixerColumnPos, ROW, Potentiometer[cols], Potentiometer[cols], "Swp", trackColor[desired_track]);
  }
}
void StateVar_Type(int des_env, int cols, int ROW) {
  int MixerColumnPos = ((cols + 1) * 4) - 1;
  if (PotValueSVF_TYP != (float)Potentiometer[cols] / SVF_TYP) {
    PotValueSVF_TYP = (float)Potentiometer[cols] / SVF_TYP;
    selectFilterType(track[desired_instrument].MIDIchannel, PotValueSVF_TYP);
    drawPot_4(MixerColumnPos, ROW, Potentiometer[cols], PotValueSVF_TYP, "", trackColor[desired_track]);
    drawChar(MixerColumnPos, ROW + 1, filterType[PotValueSVF_TYP], ILI9341_WHITE);
  }
}
//these are some function you might want to use like the drawpot or any of the draw-rect functions

//draw sub_pages buttons of a plugin, max 4 -- drawActiveRect is recommended
void draw_sub_page_buttons(int maxpages) {
  for (int pages = 0; pages < maxpages; pages++) {
    tft.drawRect(STEP_FRAME_W * 18 + 1, ((pages + 1)) * STEP_FRAME_H * 2 + STEP_FRAME_H, STEP_FRAME_W * 2 - 1, STEP_FRAME_H * 2, ILI9341_WHITE);
    tft.setFont(Arial_12);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(STEP_FRAME_W * 18 + 12, ((pages + 1)) * STEP_FRAME_H * 2 + STEP_FRAME_H + 12);
    tft.print(pages + 1);
  }
}
//draw a rectangle, if the state is high the rect gets filled
void drawActiveRect(int xPos, byte yPos, byte xsize, byte ysize, bool state, char* name, int color) {
  if (state) {
    tft.fillRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * xsize, STEP_FRAME_W * ysize, color);
    tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * xsize, STEP_FRAME_W * ysize, color);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 3);
    tft.print(name);
  }
  if (!state) {
    tft.fillRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * xsize, STEP_FRAME_W * ysize, ILI9341_DARKGREY);
    tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * xsize, STEP_FRAME_W * ysize, color);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 3);
    tft.print(name);
  }
}

void drawPot(int xPos, byte yPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

  circlePos = fvalue / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.setCursor(STEP_FRAME_W * xPos, STEP_FRAME_H * (yPos + 1) + 3);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos) + 2.25), 4, color);
  circlePos_old = circlePos;
  dvalue_old = dvalue;
}
void drawPotDrum(int xPos, byte yPos, byte fvalue, int dvalue, byte dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

  circlePos = fvalue / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.setCursor(STEP_FRAME_W * xPos, STEP_FRAME_H * (yPos + 1) + 3);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos) + 2.25), 4, color);
  circlePos_old = circlePos;
  dvalue_old = dvalue;
}
void drawPot(int xPos, byte yPos, byte fvalue, char* dvalue_char, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

  circlePos = fvalue / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old_char);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_char);
  tft.setCursor(STEP_FRAME_W * xPos, STEP_FRAME_H * (yPos + 1) + 3);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos) + 2.25), 4, color);
  circlePos_old = circlePos;
  dvalue_old_char = dvalue_char;
}
void drawPot_2(int xPos, byte yPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

  circlePos_2 = fvalue / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old_2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.setCursor(STEP_FRAME_W * xPos, STEP_FRAME_H * (yPos + 1) + 3);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old_2) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old_2) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_2) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_2) + 2.25), 4, color);
  circlePos_old_2 = circlePos_2;
  dvalue_old_2 = dvalue;
}
void drawPot_3(int xPos, byte yPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

  circlePos_3 = fvalue / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old_3);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.setCursor(STEP_FRAME_W * xPos, STEP_FRAME_H * (yPos + 1) + 3);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old_3) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old_3) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_3) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_3) + 2.25), 4, color);
  circlePos_old_3 = circlePos_3;
  dvalue_old_3 = dvalue;
}
void drawPot_4(int xPos, byte yPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

  circlePos_4 = fvalue / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old_4);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.setCursor(STEP_FRAME_W * xPos, STEP_FRAME_H * (yPos + 1) + 3);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old_4) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old_4) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_4) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_4) + 2.25), 4, color);
  circlePos_old_4 = circlePos_4;
  dvalue_old_4 = dvalue;
}
void drawPotCC(int xPos, byte yPos, byte fvaluecc, byte dvaluecc, int color) {  //xposition, yposition, value 1-127, value to draw, name to draw, color

  circlePoscc = fvaluecc / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_oldcc);


  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvaluecc);


  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_oldcc) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_oldcc) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePoscc) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePoscc) + 2.25), 4, color);
  circlePos_oldcc = circlePoscc;
  dvalue_oldcc = dvaluecc;
}

//draws a number into a rect of 2x1grids
void drawNrInRect(int xPos, byte yPos, byte dvalue, int color) {
  tft.setFont(Arial_8);
  tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * 2, STEP_FRAME_H, color);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 4);
  tft.print(dvalue_old);
  tft.setTextColor(color);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 4);
  tft.print(dvalue);
  dvalue_old = dvalue;
}
void drawNrInRect2(int xPos, byte yPos, byte dvalue, int color) {
  tft.setFont(Arial_8);
  tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * 2, STEP_FRAME_H, color);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 4);
  tft.print(dvalue_old2);
  tft.setTextColor(color);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 4);
  tft.print(dvalue);
  dvalue_old2 = dvalue;
}
//draws a number into a rect of 2x1grids
void drawChar(int xPos, byte yPos, char* dvalue_char, int color) {
  tft.setFont(Arial_8);
  //tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * 2, STEP_FRAME_H, color);
  tft.fillRect(STEP_FRAME_W * xPos + 1, STEP_FRAME_H * yPos + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
  tft.setTextColor(color);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 4);
  tft.print(dvalue_char);
  dvalue_old_char = dvalue_char;
}





void clearWorkSpace() {                                                                                  //clear the whole grid from Display
  tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H, STEP_FRAME_W * 20, STEP_FRAME_H * 13, ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
  tft.fillRect(STEP_FRAME_W, STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H * 12, ILI9341_DARKGREY);
}