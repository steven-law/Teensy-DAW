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
    Plugin2_Page_Static(0);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////
  ///////// if we select the pluginpage its PLUGINx_PAGE1 bool gets true and selects the Pluginx_Page_Static once
  ///////// now we see the actual graphs and values, but the programm switches over to Pluginx_Page_Dynamic(),
  ///////// which is called all the time in the loop() function as long PLUGINx_PAGE1 is true, for controlling the parameters
  ////////////////////////////////////////////////////////////////////////////////////////////////
  if (selectPage == PLUGIN3_PAGE1) {
    Plugin3_Page_Static(0);
  }
  if (selectPage == PLUGIN4_PAGE1) {
    Plugin4_Page_Static(0);
  }
  if (selectPage == PLUGIN5_PAGE1) {
    Plugin5_Page_Static(0);
  }
  if (selectPage == PLUGIN6_PAGE1) {
    Plugin6_Page_Static(0);
  }
  if (selectPage == PLUGIN7_PAGE1) {
    Plugin7_Page_Static(0);
  }
  if (selectPage == PLUGIN7_PAGE2) {
    Plugin7_Page_Static(1);
  }

  if (selectPage == PLUGIN8_PAGE1) {
    Plugin8_Page_Static(0);
  }
  if (selectPage == PLUGIN9_PAGE1) {
    Plugin9_Page_Static(0);
  }
  if (selectPage == PLUGIN10_PAGE1) {
    Plugin10_Page_Static(0);
  }
  if (selectPage == PLUGIN11_PAGE1) {
    Plugin11_Page_Static(0);
  }
  if (selectPage == PLUGIN12_PAGE1) {
    Plugin12_Page_Static(0);
  }
  if (selectPage == PLUGIN13_PAGE1) {
    Plugin13_Page_Static(0);
  }
  if (selectPage == PLUGIN14_PAGE1) {
    Plugin14_Page_Static(0);
  }
  if (selectPage == PLUGIN15_PAGE1) {
    Plugin15_Page_Static(0);
  }
  if (selectPage == PLUGIN16_PAGE1) {
    Plugin16_Page_Static(0);
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





  readMainButtons();
  //-----------------------------------------
  //setting up the Plugin1 Page1-view
  if (selectPage == PLUGIN1_PAGE1) {
    Plugin1_Page1_Dynamic();
    Plugin1_Control();
  }
  //setting up the Plugin1 Page2-view
  if (selectPage == PLUGIN1_PAGE2) {
    Plugin1_Page2_Dynamic();
    Plugin1_Control();
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
  //setting up the Plugin7 Page1-view
  if (selectPage == PLUGIN7_PAGE1) {
    Plugin7_Page1_Dynamic();
    Plugin7_Control1();
  }
  //setting up the Plugin7 Page2-view
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



  //setting up the StepSequencer-view for drumtrack #1
  if (selectPage == DRUMTRACK) {
    drumStepSequencer();
  }
  //setting up the melodicStepSequencer-view for #2-8
  for (byte i = 1; i < 8; i++) {
    if (selectPage == i) {
      melodicStepSequencer(i);
    }
  }
  //setting up the scaleSelector-view
  if (selectPage == SCALESELECT) {
    scaleSelector();
  }

  //setting up the songMode-view1
  for (byte pagenr = 0; pagenr < 16; pagenr++) {
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
  //setting up the Mixer Page 2
  if (selectPage == MIDICC_PAGE_1) {
    midiCCpage1_Dynamic(desired_track);
  }
}
//here you have to put your NoteOn/Off´s into
void PluginPlay() {
  //play drumplugin when midichannel = 18
  for (int desired_instruments = 0; desired_instruments < 8; desired_instruments++) {
    if (track[0].MIDIchannel == 18) {
      for (int files = 0; files < 12; files++) {
        if (drumnotes[files]) {
          drumnotes[files] = false;
          playSdWav1.play(wavKit[files]);
        }
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
        playMem6.play(AudioSampleGong);
      }
      if (drumnotes[7]) {
        drumnotes[7] = false;
        //playSdWav8.play("P7.WAV");
      }
      if (drumnotes[8]) {
        drumnotes[8] = false;
        //playSdWav9.play("P8.WAV");
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
      } else {
      }
    }



    if (track[desired_instruments].notePressed) {

      if (track[desired_instruments].MIDIchannel == 17) {
        waveform1.frequency(note_frequency[track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[0]]);
        waveform2.frequency(note_frequency[track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[1]]);
        waveform3.frequency(note_frequency[track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[2]]);
        waveform4.frequency(note_frequency[track[desired_instruments].notePlayed + pl1[track[desired_instruments].presetNr[phrase]].note_Offset[3]]);
        envelope1.noteOn();
        envelope2.noteOn();
      }

      if (track[desired_instruments].MIDIchannel == 19) {
        pl3waveform1.frequency(note_frequency[track[desired_instruments].notePlayed]);
        pl3envelope1.noteOn();
        pl3envelope2.noteOn();
      }
      if (track[desired_instruments].MIDIchannel == 21) {
        double note_ratio = pow(2.0, ((double)(track[desired_instruments].notePlayed - SAMPLE_ROOT) / 12.0));
        playSdPitch1.setPlaybackRate(note_ratio);
        //playSdPitch1.playRaw(RAW_files[pl5[track[desired_track].presetNr[phrase]].selected_file], 1);
        playSdPitch1.playRaw(pl5sample->sampledata, pl5sample->samplesize, 1);
        pl5envelope1.noteOn();
        pl5envelope2.noteOn();
        Serial.println("listen?");
      }
      if (track[desired_instruments].MIDIchannel == 22) {
        double note_ratio = pow(2.0, ((double)(track[desired_instruments].notePlayed - SAMPLE_ROOT) / 12.0));
        playSdPitch2.setPlaybackRate(note_ratio);
        playSdPitch2.playRaw(RAW_files[pl6[track[desired_instruments].presetNr[phrase]].selected_file], 1);
        pl6envelope1.noteOn();
        pl6envelope2.noteOn();
      }
      if (track[desired_instruments].MIDIchannel == 24) {
        pl8waveform1.frequency(note_frequency[track[desired_instruments].notePlayed]);
        pl8envelope1.noteOn();
        pl8envelope2.noteOn();
      }
      if (track[desired_instruments].MIDIchannel == 25) {
        pl9string1.noteOn(note_frequency[track[desired_instruments].notePlayed], 1);
      }
    }



    if (!track[desired_instruments].notePressed) {

      if (track[desired_instruments].MIDIchannel == 17) {
        envelope1.noteOff();
        envelope2.noteOff();
      }
      if (track[desired_instruments].MIDIchannel == 19) {
        pl3envelope1.noteOff();
        pl3envelope2.noteOff();
      }
      if (track[desired_instruments].MIDIchannel == 21) {
        pl5envelope1.noteOff();
        pl5envelope2.noteOff();
      }
      if (track[desired_instruments].MIDIchannel == 22) {
        pl6envelope1.noteOff();
        pl6envelope2.noteOff();
      }
      if (track[desired_instruments].MIDIchannel == 24) {
        pl8envelope1.noteOff();
        pl8envelope2.noteOff();
      }
      if (track[desired_instruments].MIDIchannel == 25) {
        pl9string1.noteOff(0);
      }
    }
  }
}

//this function is called for every beatchange for preset/clip/noteoffset/clip change
//add your soundcontrol functions like desired osc frequency etc, so the presetchange can be applied
void beatComponents() {
  for (byte instruments = 0; instruments < 8; instruments++) {
    track[instruments].clip_songMode = track[instruments].arrangment1[phrase];
    track[instruments].MIDI_velocity = track[instruments].volume[phrase];
    pluginVolume(track[instruments].MIDIchannel, track[instruments].volume[phrase] / 127.00);

    for (byte songpages = 0; songpages < 16; songpages++) {
      if (selectPage == SONGMODE_PAGE_1 + songpages) {
        if (midi01.idVendor() == 4661) {
          for (byte notes = 0; notes < 9; notes++) {
            midi01.sendNoteOff(notes + (instruments * 16), 0, 1);
          }

          if (track[instruments].arrangment1[phrase] < MAX_CLIPS) {
            midi01.sendNoteOn(track[instruments].arrangment1[phrase] + (instruments * 16), 60, 1);
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
  }
}

//if you have a filter with multiple outputs like the AudioFilterStateVariable
//this function will switch between the different inputs of the afterwards installed mixer
//add your filtermixer here
void selectFilterType(byte pluginchannel, byte mixerchannel) {
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

//end of the plugin-function-nightmare
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////








//these are some function you might want to use like the drawpot or any of the draw-rect functions

//draw sub_pages buttons of a plugin, max 4 -- drawActiveRect is recommended
void draw_sub_page_buttons(byte maxpages) {
  for (byte pages = 0; pages < maxpages; pages++) {
    tft.drawRect(STEP_FRAME_W * 18 + 1, ((pages + 1)) * STEP_FRAME_H * 2 + STEP_FRAME_H, STEP_FRAME_W * 2 - 1, STEP_FRAME_H * 2, ILI9341_WHITE);
    tft.setFont(Arial_12);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(STEP_FRAME_W * 18 + 12, ((pages + 1)) * STEP_FRAME_H * 2 + STEP_FRAME_H + 12);
    tft.print(pages + 1);
  }
}
//draw a rectangle, if the state is high the rect gets filled
void drawActiveRect(byte xPos, byte yPos, byte xsize, byte ysize, bool state, char* name, int color) {
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

void drawPot(byte xPos, byte yPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

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
void drawPot(byte xPos, byte yPos, byte fvalue, char* dvalue_char, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

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
void drawPot_2(byte xPos, byte yPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

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
void drawPot_3(byte xPos, byte yPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

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
void drawPot_4(byte xPos, byte yPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

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
void drawPotCC(byte xPos, byte yPos, byte fvaluecc, byte dvaluecc, int color) {  //xposition, yposition, value 1-127, value to draw, name to draw, color

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

//draws a number into a rect of 2x1grids  drawActiveRect is recommended
void drawNrInRect(byte xPos, byte yPos, byte dvalue, int color) {
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
void drawNrInRect2(byte xPos, byte yPos, byte dvalue, int color) {
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
//draws a number into a rect of 2x1grids  drawActiveRect is recommended
void drawChar(byte xPos, byte yPos, char* dvalue_char, int color) {
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