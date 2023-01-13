//this calls the static plugin view for your plugin, it is used when the plugin page is called or if you change presets
// just add your plugin-page static function here
void Plugin_View_Static(byte desired_instrument) {

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
//this calls the dynamic plugin view for your plugin, where your changes (via encoder) of the soundcontrols are happening
// just add your plugin-page dynamic function here
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
  //setting up the Plugin7 Page1-view
  if (selectPage == PLUGIN7_PAGE1) {
    Plugin7_Page1_Dynamic();
  }
  //setting up the Plugin7 Page2-view
  if (selectPage == PLUGIN7_PAGE2) {
    Plugin7_Page2_Dynamic();
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
    //}
    if (track[instruments].MIDIchannel == 17) {
      pl1presetNr = track[instruments].presetNr[phrase];
      for (byte MixerColumn = 0; MixerColumn < 4; MixerColumn++) {
        pl1[pl1presetNr].note_Offset[MixerColumn];
      }
      waveform1.begin(pl1[pl1presetNr].wfSelect[0]);
      waveform2.begin(pl1[pl1presetNr].wfSelect[1]);
      waveform3.begin(pl1[pl1presetNr].wfSelect[2]);
      waveform4.begin(pl1[pl1presetNr].wfSelect[3]);
      mixer1.gain(0, pl1[pl1presetNr].note_Velo[0]);
      mixer1.gain(1, pl1[pl1presetNr].note_Velo[1]);
      mixer1.gain(2, pl1[pl1presetNr].note_Velo[2]);
      mixer1.gain(3, pl1[pl1presetNr].note_Velo[3]);
      filter1.frequency(pl1[pl1presetNr].Filter1_Frequency);
      filter1.resonance(pl1[pl1presetNr].Filter1_Resonance);
      filter1.octaveControl(pl1[pl1presetNr].Filter1_Sweep);
      selectFilterType(17, pl1[pl1presetNr].Filter1_Type);
      envelope1.attack(pl1[pl1presetNr].Env1_Attack);
      envelope2.attack(pl1[pl1presetNr].Env1_Attack);
      envelope1.decay(pl1[pl1presetNr].Env1_Decay);
      envelope2.decay(pl1[pl1presetNr].Env1_Decay);
      envelope1.sustain(pl1[pl1presetNr].Env1_Sustain);
      envelope2.sustain(pl1[pl1presetNr].Env1_Sustain);
      envelope1.release(pl1[pl1presetNr].Env1_Release);
      envelope2.release(pl1[pl1presetNr].Env1_Release);
    }
    if (track[instruments].MIDIchannel == 18) {
      pl2presetNr = track[instruments].presetNr[phrase];
      for (byte touchX = 1; touchX < 5; touchX++) {
        drummixer1.gain(touchX - 1, pl2[pl2presetNr].Vol[touchX - 1]);
        drummixer2.gain(touchX - 1, pl2[pl2presetNr].Vol[touchX + 3]);
        drummixer3.gain(touchX - 1, pl2[pl2presetNr].Vol[touchX + 7]);
      }
    }
    if (track[instruments].MIDIchannel == 19) {
      pl3presetNr = track[instruments].presetNr[phrase];
      pl3waveform1.begin(pl3[pl3presetNr].wfSelect);
      pl3filter1.frequency(pl3[pl3presetNr].Filter1_Frequency);
      pl3filter1.resonance(pl3[pl3presetNr].Filter1_Resonance);
      pl3filter1.octaveControl(pl3[pl3presetNr].Filter1_Sweep);
      selectFilterType(19, pl3[pl3presetNr].Filter1_Type);
      pl3envelope1.attack(pl3[pl3presetNr].Env1_Attack);
      pl3envelope2.attack(pl3[pl3presetNr].Env1_Attack);
      pl3envelope1.decay(pl3[pl3presetNr].Env1_Decay);
      pl3envelope2.decay(pl3[pl3presetNr].Env1_Decay);
      pl3envelope1.sustain(pl3[pl3presetNr].Env1_Sustain);
      pl3envelope2.sustain(pl3[pl3presetNr].Env1_Sustain);
      pl3envelope1.release(pl3[pl3presetNr].Env1_Release);
      pl3envelope2.release(pl3[pl3presetNr].Env1_Release);
    }
    if (track[instruments].MIDIchannel == 20) {
      pl4presetNr = track[instruments].presetNr[phrase];
      for (byte touchX = 1; touchX < 5; touchX++) {
        pl4drummixer1.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX - 1]);
        pl4drummixer2.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX + 3]);
        pl4drummixer3.gain(touchX - 1, pl4[pl4presetNr].Vol[touchX + 7]);
      }
    }
    if (track[instruments].MIDIchannel == 21) {
      pl5presetNr = track[instruments].presetNr[phrase];
    }
    if (track[instruments].MIDIchannel == 22) {
      pl6presetNr = track[instruments].presetNr[phrase];
    }
    if (track[instruments].MIDIchannel == 23) {
      pl7presetNr = track[instruments].presetNr[phrase];
    }
    if (track[instruments].MIDIchannel == 24) {
      pl8presetNr = track[instruments].presetNr[phrase];
      pl8waveform1.begin(pl8[pl8presetNr].wfSelect);
      pl8filter1.frequency(pl8[pl8presetNr].Filter1_Frequency);
      pl8filter1.resonance(pl8[pl8presetNr].Filter1_Resonance);
      pl8filter1.octaveControl(pl8[pl8presetNr].Filter1_Sweep);
      pl8envelope1.attack(pl8[pl8presetNr].Env1_Attack);
      pl8envelope2.attack(pl8[pl8presetNr].Env1_Attack);
      pl8envelope1.decay(pl8[pl8presetNr].Env1_Decay);
      pl8envelope2.decay(pl8[pl8presetNr].Env1_Decay);
      pl8envelope1.sustain(pl8[pl8presetNr].Env1_Sustain);
      pl8envelope2.sustain(pl8[pl8presetNr].Env1_Sustain);
      pl8envelope1.release(pl8[pl8presetNr].Env1_Release);
      pl8envelope2.release(pl8[pl8presetNr].Env1_Release);
    }
    if (track[instruments].MIDIchannel == 25) {
      pl9presetNr = track[instruments].presetNr[phrase];
    }
  }
}
//if you want your plugin to be played via midi this is your place
//add your noteOn´s (envelope.noteOn´s) here
void myNoteOn(byte channel, byte note, byte velocity) {
  if (midi01.idVendor() == 4661) {

    for (byte songpages = 0; songpages < 16; songpages++) {
      if (selectPage == SONGMODE_PAGE_1 + songpages) {
        LP_songmode(note);
      }
    }
    for (byte gridNotes = 0; gridNotes < 64; gridNotes++) {
      if (note == LP_grid_notes[gridNotes]) {
        LP_grid_bool[gridNotes] = true;
      }
    }
    if (selectPage == 0) {
      for (byte octNotes = 0; octNotes < 12; octNotes++) {
        if (note == LP_octave_notes[octNotes]) {
          LP_octave_bool[octNotes] = true;
        }
      }
    }
    for (int trackss = 1; trackss < 8; trackss++) {
      if (selectPage == trackss) {
        for (byte octNotes = 0; octNotes < 12; octNotes++) {
          if (note == LP_octave_notes_keys[octNotes]) {
            channel = desired_instrument + 1;

            LP_octave_bool_keys[octNotes] = true;
            note = octNotes + (track[desired_instrument].shown_octaves * 12);
          }
        }
      }
    }
    for (byte stepss = 0; stepss < 16; stepss++) {
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


  // When a USB device with multiple virtual cables is used,
  // midi1.getCable() can be used to read which of the virtual
  // MIDI cables received this message.

  if (seq_rec) {
    ctrack[channel - 1].sequence[track[channel - 1].clip_selector].step[tick_16] = note;
  }
  //send midinotes for drumtrack #1
  //play drumplugin when midichannel = 18
  if (track[channel - 1].MIDIchannel == 18) {
    for (int files = 0; files < 12; files++) {
      if (note == (files + 36) || LP_octave_bool[files]) {
        playSdWav1.play(wavKit[files]);
      }
    }
  }
  //play Memory drumplugin when midichannel = 20
  if (track[channel - 1].MIDIchannel == 20) {
    if (note == 36 || LP_octave_bool[0]) {
      playMem1.play(AudioSampleKick);
    }
    if (note == 37 || LP_octave_bool[1]) {
      playMem2.play(AudioSampleSnare);
    }
    if (note == 38 || LP_octave_bool[2]) {
      playMem3.play(AudioSampleP2);
    }
    if (note == 39 || LP_octave_bool[3]) {
      playMem4.play(AudioSampleHihat);
    }
    if (note == 40 || LP_octave_bool[4]) {
      playMem5.play(AudioSampleCashregister);
    }
    if (note == 41 || LP_octave_bool[5]) {
      playMem6.play(AudioSampleTomtom);
    }
    if (note == 42 || LP_octave_bool[6]) {
      playMem6.play(AudioSampleGong);
    }
    if (note == 43 || LP_octave_bool[7]) {
      //playSdWav8.play("P7.WAV");
    }
    if (note == 44 || LP_octave_bool[8]) {
      //playSdWav9.play("P8.WAV");
    }
    if (note == 45 || LP_octave_bool[9]) {
      //playSdWav10.play("P9.WAV");
    }
    if (note == 46 || LP_octave_bool[10]) {
      //playSdWav11.play("P10.WAV");
    }
    if (note == 47 || LP_octave_bool[11]) {
      //playSdWav12.play("P11.WAV");
    }
  }
  //play Memory drumplugin when midichannel = 20
  if (track[channel - 1].MIDIchannel == 23) {
    if (note == 36 || LP_octave_bool[0]) {
      pl7drum1.noteOn();
    }
    if (note == 37 || LP_octave_bool[1]) {
      pl7envelope1.noteOn();
    } else {
      pl7envelope1.noteOff();
    }
    if (note == 38 || LP_octave_bool[2]) {
      pl7envelope2.noteOn();
      pl7envelope3.noteOn();
    } else {
      pl7envelope2.noteOff();
      pl7envelope3.noteOff();
    }
    if (note == 39 || LP_octave_bool[3]) {
      //playMem4.play(AudioSampleHihat);
    }
  }

  if (track[channel - 1].MIDIchannel < 17) {
    usbMIDI.sendNoteOn(note, velocity, track[channel - 1].MIDIchannel);
    MIDI.sendNoteOn(note, velocity, track[channel - 1].MIDIchannel);
    midi01.sendNoteOn(note, velocity, track[channel - 1].MIDIchannel);
    midi02.sendNoteOn(note, velocity, track[channel - 1].MIDIchannel);
    midi03.sendNoteOn(note, velocity, track[channel - 1].MIDIchannel);
    midi04.sendNoteOn(note, velocity, track[channel - 1].MIDIchannel);
    midi05.sendNoteOn(note, velocity, track[channel - 1].MIDIchannel);
    midi06.sendNoteOn(note, velocity, track[channel - 1].MIDIchannel);
  }
  if (track[channel - 1].MIDIchannel == 17) {
    waveform1.frequency(note_frequency[note + pl1[track[desired_track].presetNr[phrase]].note_Offset[0]]);
    waveform2.frequency(note_frequency[note + pl1[track[desired_track].presetNr[phrase]].note_Offset[1]]);
    waveform3.frequency(note_frequency[note + pl1[track[desired_track].presetNr[phrase]].note_Offset[2]]);
    waveform4.frequency(note_frequency[note + pl1[track[desired_track].presetNr[phrase]].note_Offset[3]]);
    envelope1.noteOn();
    envelope2.noteOn();
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
//and your noteOff here
void myNoteOff(byte channel, byte note, byte velocity) {
  if (midi01.idVendor() == 4661) {
    for (byte gridNotes = 0; gridNotes < 64; gridNotes++) {
      if (note == LP_grid_notes[gridNotes]) {
        LP_grid_bool[gridNotes] = false;
      }
    }
    for (byte octNotes = 0; octNotes < 24; octNotes++) {
      if (note == LP_octave_notes[octNotes]) {
        LP_octave_bool[octNotes] = false;
      }
    }
    for (byte stepss = 0; stepss < 16; stepss++) {
      if (note == LP_step_notes[stepss]) {
        LP_step_bool[stepss] = false;
      }
    }
    for (int trackss = 1; trackss < 8; trackss++) {
      if (selectPage == trackss) {
        for (byte octNotes = 0; octNotes < 12; octNotes++) {
          if (note == LP_octave_notes_keys[octNotes]) {
            channel = desired_instrument + 1;

            LP_octave_bool_keys[octNotes] = false;
            note = octNotes + (track[desired_instrument].shown_octaves * 12);
          }
        }
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
  if (track[channel - 1].MIDIchannel < 17) {
    usbMIDI.sendNoteOff(note, velocity, track[channel - 1].MIDIchannel);
    MIDI.sendNoteOff(note, velocity, track[channel - 1].MIDIchannel);
    midi01.sendNoteOff(note, velocity, track[channel - 1].MIDIchannel);
    midi02.sendNoteOff(note, velocity, track[channel - 1].MIDIchannel);
    midi03.sendNoteOff(note, velocity, track[channel - 1].MIDIchannel);
    midi04.sendNoteOff(note, velocity, track[channel - 1].MIDIchannel);
    midi05.sendNoteOff(note, velocity, track[channel - 1].MIDIchannel);
    midi06.sendNoteOff(note, velocity, track[channel - 1].MIDIchannel);
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


//if you want your plugin to be controlled via midi this is your place
//control functions (from your plugin page dynamic) in a bit different way here
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


  //launchpad control up-est row, they send cc´s
  if (midi01.idVendor() == 4661) {
    //cursor left
    if (otherCtrlButtons && control == 104 && value == 127) {
      button[0] = true;
      gridTouchX--;
      drawCursor();
    } else if (otherCtrlButtons && control == 104 && value != 127) {
      button[0] = false;
    }
    //cursor right
    if (otherCtrlButtons && control == 105 && value == 127) {
      button[1] = true;
      gridTouchX++;
      drawCursor();
    } else if (otherCtrlButtons && control == 105 && value != 127) {
      button[1] = false;
    }
    //cursor up
    if (otherCtrlButtons && control == 106 && value == 127) {
      button[2] = true;
      gridTouchY--;
      drawCursor();
    } else if (otherCtrlButtons && control == 106 && value != 127) {
      button[2] = false;
    }
    //cursor down
    if (otherCtrlButtons && control == 107 && value == 127) {
      button[3] = true;
      gridTouchY++;
      drawCursor();
    } else if (otherCtrlButtons && control == 107 && value != 127) {
      button[3] = false;
    }
    //last pot row
    if (otherCtrlButtons && control == 108 && value == 127) {
      button[4] = true;
      lastPotRow++;
      if (lastPotRow == 4) {
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
          for (byte pluginSelection = 0; pluginSelection <= MAX_PLUGINS; pluginSelection++) {
            if (track[desired_instrument].MIDIchannel == pluginSelection) {
              selectPage = MIDICC_PAGE_1;
              midiCC_view_Static(0, desired_track);
            }
            //plugin_1_view
            if (track[desired_instrument].MIDIchannel == pluginSelection + 17) {
              selectPage = pluginSelection + 40;
              Plugin_View_Static(desired_track);
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
      }
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
////////////////////////////////////////////////////
//only subject to change when we have reached the limit of templated plugins (per now there are 9 plugins and 7 templated plugins)
//



//this is the volume used for the automation in songmode
//add your amp.gain() to control the volume
void pluginVolume(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  for (int pluginn = 0; pluginn < 16; pluginn++) {
    if (pluginchannel == pluginn + 17) {
      gainPerBar[pluginn]->gain(volume);
    }
  }
}
//this is the gain used in the mixer view
//add your amp.gain2() to control the gain
void pluginGain(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  for (int pluginn = 0; pluginn < 16; pluginn++) {
    if (pluginchannel == pluginn + 17) {
      gainmax[pluginn]->gain(volume);
    }
  }
}
//this is the dryvolume
//add your mixer&channel to be controlled in mixerpage 2+3
void FXDrypluginVolume(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  if (pluginchannel == 17) {
    mixer5.gain(0, volume);
  }
  if (pluginchannel == 18) {
    mixer5.gain(1, volume);
  }
  if (pluginchannel == 19) {
    mixer5.gain(2, volume);
  }
  if (pluginchannel == 20) {
    mixer5.gain(3, volume);
  }

  if (pluginchannel == 21) {
    mixer6.gain(0, volume);
  }
  if (pluginchannel == 22) {
    mixer6.gain(1, volume);
  }
  if (pluginchannel == 23) {
    mixer6.gain(2, volume);
  }
  if (pluginchannel == 24) {
    mixer6.gain(3, volume);
  }

  if (pluginchannel == 25) {
    mixer10.gain(0, volume);
  }
  if (pluginchannel == 26) {
    mixer10.gain(1, volume);
  }
  if (pluginchannel == 27) {
    mixer10.gain(2, volume);
  }
  if (pluginchannel == 28) {
    mixer10.gain(3, volume);
  }

  if (pluginchannel == 29) {
    drymixer3.gain(0, volume);
  }
  if (pluginchannel == 30) {
    drymixer3.gain(1, volume);
  }
  if (pluginchannel == 31) {
    drymixer3.gain(2, volume);
  }
  if (pluginchannel == 32) {
    drymixer3.gain(3, volume);
  }
}
//this is the FX1volume
//add your mixer&channel to be controlled in mixerpage 2+3
void FX1pluginVolume(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  if (pluginchannel == 17) {
    FX1mixer1.gain(0, volume);
  }
  if (pluginchannel == 18) {
    FX1mixer1.gain(1, volume);
  }
  if (pluginchannel == 19) {
    FX1mixer1.gain(2, volume);
  }
  if (pluginchannel == 20) {
    FX1mixer1.gain(3, volume);
  }

  if (pluginchannel == 21) {
    FX1mixer2.gain(0, volume);
  }
  if (pluginchannel == 22) {
    FX1mixer2.gain(1, volume);
  }
  if (pluginchannel == 23) {
    FX1mixer2.gain(2, volume);
  }
  if (pluginchannel == 24) {
    FX1mixer2.gain(3, volume);
  }

  if (pluginchannel == 25) {
    FX1mixer4.gain(0, volume);
  }
  if (pluginchannel == 26) {
    FX1mixer4.gain(1, volume);
  }
  if (pluginchannel == 27) {
    FX1mixer4.gain(2, volume);
  }
  if (pluginchannel == 28) {
    FX1mixer4.gain(3, volume);
  }

  if (pluginchannel == 29) {
    FX1mixer6.gain(0, volume);
  }
  if (pluginchannel == 30) {
    FX1mixer6.gain(1, volume);
  }
  if (pluginchannel == 31) {
    FX1mixer6.gain(2, volume);
  }
  if (pluginchannel == 32) {
    FX1mixer6.gain(3, volume);
  }
}
//this is the FX2volume
//add your mixer&channel to be controlled in mixerpage 2+3
void FX2pluginVolume(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  if (pluginchannel == 17) {
    FX2mixer1.gain(0, volume);
  }
  if (pluginchannel == 18) {
    FX2mixer1.gain(1, volume);
  }
  if (pluginchannel == 19) {
    FX2mixer1.gain(2, volume);
  }
  if (pluginchannel == 20) {
    FX2mixer1.gain(3, volume);
  }

  if (pluginchannel == 21) {
    FX2mixer2.gain(0, volume);
  }
  if (pluginchannel == 22) {
    FX2mixer2.gain(1, volume);
  }
  if (pluginchannel == 23) {
    FX2mixer2.gain(2, volume);
  }
  if (pluginchannel == 24) {
    FX2mixer2.gain(3, volume);
  }

  if (pluginchannel == 25) {
    FX2mixer4.gain(0, volume);
  }
  if (pluginchannel == 26) {
    FX2mixer4.gain(1, volume);
  }
  if (pluginchannel == 27) {
    FX2mixer4.gain(2, volume);
  }
  if (pluginchannel == 28) {
    FX2mixer4.gain(3, volume);
  }

  if (pluginchannel == 29) {
    FX2mixer6.gain(0, volume);
  }
  if (pluginchannel == 30) {
    FX2mixer6.gain(1, volume);
  }
  if (pluginchannel == 31) {
    FX2mixer6.gain(2, volume);
  }
  if (pluginchannel == 32) {
    FX2mixer6.gain(3, volume);
  }
}
//this is the FX3volume
//add your mixer&channel to be controlled in mixerpage 2+3
void FX3pluginVolume(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  if (pluginchannel == 17) {
    FX3mixer1.gain(0, volume);
  }
  if (pluginchannel == 18) {
    FX3mixer1.gain(1, volume);
  }
  if (pluginchannel == 19) {
    FX3mixer1.gain(2, volume);
  }
  if (pluginchannel == 20) {
    FX3mixer1.gain(3, volume);
  }

  if (pluginchannel == 21) {
    FX3mixer2.gain(0, volume);
  }
  if (pluginchannel == 22) {
    FX3mixer2.gain(1, volume);
  }
  if (pluginchannel == 23) {
    FX3mixer2.gain(2, volume);
  }
  if (pluginchannel == 24) {
    FX3mixer2.gain(3, volume);
  }
  if (pluginchannel == 25) {
    FX3mixer4.gain(0, volume);
  }
  if (pluginchannel == 26) {
    FX3mixer4.gain(1, volume);
  }
  if (pluginchannel == 27) {
    FX3mixer4.gain(2, volume);
  }
  if (pluginchannel == 28) {
    FX3mixer4.gain(3, volume);
  }

  if (pluginchannel == 29) {
    FX3mixer6.gain(0, volume);
  }
  if (pluginchannel == 30) {
    FX3mixer6.gain(1, volume);
  }
  if (pluginchannel == 31) {
    FX3mixer6.gain(2, volume);
  }
  if (pluginchannel == 32) {
    FX3mixer6.gain(3, volume);
  }
}

//end of the plugin-function-nightmare
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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