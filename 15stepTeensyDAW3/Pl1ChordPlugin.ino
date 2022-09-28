//small 4Osc chord synthvoice, select the note-offsets from your played note (equal to set your chord), change gain for the 4 osc´s
//toDo: change waveform, add pw control

void Plugin_1_Settings() {
  waveform1.begin(WAVEFORM_SAWTOOTH);
  waveform1.amplitude(note1_Velo);
  waveform1.frequency(note_frequency[36]);
  waveform1.pulseWidth(0.15);

  waveform2.begin(WAVEFORM_SAWTOOTH);
  waveform2.amplitude(note2_Velo);
  waveform2.frequency(note_frequency[36]);
  waveform2.pulseWidth(0.15);

  waveform3.begin(WAVEFORM_SAWTOOTH);
  waveform3.amplitude(note3_Velo);
  waveform3.frequency(note_frequency[36]);
  waveform3.pulseWidth(0.15);

  waveform4.begin(WAVEFORM_SAWTOOTH);
  waveform4.amplitude(note4_Velo);
  waveform4.frequency(note_frequency[36]);
  waveform4.pulseWidth(0.15);

  mixer1.gain(0, 1);
  mixer1.gain(1, 1);
  mixer1.gain(2, 1);
  mixer1.gain(3, 1);

  filter1.frequency(Filter1_Frequency);
  filter1.resonance(Filter1_Resonance);
  filter1.octaveControl(Filter1_Sweep);

  envelope1.delay(0);
  envelope1.attack(Env1_Attack);
  envelope1.hold(0);
  envelope1.decay(500);
  envelope1.sustain(0.8);
  envelope1.release(Env1_Release);

  dc2.amplitude(1);

  envelope2.delay(0);
  envelope2.attack(Env1_Attack);
  envelope2.hold(0);
  envelope2.decay(500);
  envelope2.sustain(0.8);
  envelope2.release(Env1_Release);

  //bitcrusher1 controlled by startKnob on page 3
  bitcrusher1.bits(16);
  bitcrusher1.sampleRate(44100);

  //delay1 time controlled by stationKnob; feedback controlled by startKnob on page 4
  delay1.delay(0, 3);  //set Delay(OutChannel, saved Samples) (0-7, 3-449*) *maximum

  //filter3 HighPassfilter to get rid of the muddy sound in feedbackloop
  filter3.frequency(200);  //set initial Filter3 freq to 16000Hz
  filter3.resonance(0);    //set Resonance to 0

  //mixer3 for feedback controlled by startKnob on page 4
  mixer3.gain(0, 1);  //setze Mixer2(Kanal, Gain) (0-3, 0-1)
  mixer3.gain(1, 0);

  //mixer5 again just a mixer to pass audio thru
  mixer5.gain(0, 1);
  mixer5.gain(1, 1);
  mixer5.gain(2, 1);
  mixer5.gain(3, 1);
}

void Plugin1_Page1_Dynamic() {

  for (int columns = 1; columns < 5; columns++) {
    for (int rows = 1; rows < 6; rows++) {
      tft.drawRect(STEP_FRAME_W * rows * 3, STEP_FRAME_H * columns * 3, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);
    }
  }
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);

  tft.setCursor(STEP_FRAME_W * 3 + 2, STEP_FRAME_H * 2);
  tft.print("note Offset");

  tft.setCursor(STEP_FRAME_W * 3 + 2, STEP_FRAME_H * 3 + 5);
  tft.print(note1_Offset);

  tft.setCursor(STEP_FRAME_W * 6 + 2, STEP_FRAME_H * 3 + 5);
  tft.print(note2_Offset);

  tft.setCursor(STEP_FRAME_W * 9 + 2, STEP_FRAME_H * 3 + 5);
  tft.print(note3_Offset);

  tft.setCursor(STEP_FRAME_W * 12 + 2, STEP_FRAME_H * 3 + 5);
  tft.print(note4_Offset);


  tft.setCursor(STEP_FRAME_W * 3 + 2, STEP_FRAME_H * 5);
  tft.print("note Velocity");

  tft.setCursor(STEP_FRAME_W * 3 + 2, STEP_FRAME_H * 6 + 5);
  tft.print(note1_Velo);

  tft.setCursor(STEP_FRAME_W * 6 + 2, STEP_FRAME_H * 6 + 5);
  tft.print(note2_Velo);

  tft.setCursor(STEP_FRAME_W * 9 + 2, STEP_FRAME_H * 6 + 5);
  tft.print(note3_Velo);

  tft.setCursor(STEP_FRAME_W * 12 + 2, STEP_FRAME_H * 6 + 5);
  tft.print(note4_Velo);

  tft.setCursor(STEP_FRAME_W * 3 + 2, STEP_FRAME_H * 5);
  tft.print("note Velocity");

  tft.setCursor(STEP_FRAME_W * 3 + 2, STEP_FRAME_H * 6 + 5);
  tft.print(note1_Velo);

  tft.setCursor(STEP_FRAME_W * 6 + 2, STEP_FRAME_H * 6 + 5);
  tft.print(note2_Velo);

  tft.setCursor(STEP_FRAME_W * 9 + 2, STEP_FRAME_H * 6 + 5);
  tft.print(note3_Velo);

  tft.setCursor(STEP_FRAME_W * 12 + 2, STEP_FRAME_H * 6 + 5);
  tft.print(note4_Velo);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ts.touched()) {
      tft.setFont(Arial_8);
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(1);

      //page selection
      if (gridTouchX >= 18) {
        //page1
        if (gridTouchY == 3 || gridTouchY == 4) {
          for (byte others = 0; others <= MAX_PAGES; others++) {
            selectPage[others] = LOW;
          }
          selectPage[11] = HIGH;
          Plugin_View_Static();
        }
        //page2
        if (gridTouchY == 5 || gridTouchY == 6) {
          for (byte others = 0; others <= MAX_PAGES; others++) {
            selectPage[others] = LOW;
          }
          selectPage[12] = HIGH;
          Plugin_View_Static();
        }
        //page3
        if (gridTouchY == 7 || gridTouchY == 8) {
          for (byte others = 0; others <= MAX_PAGES; others++) {
            selectPage[others] = LOW;
          }
          selectPage[13] = HIGH;
          Plugin_View_Static();
        }
        //page4
        if (gridTouchY == 9 || gridTouchY == 10) {
          for (byte others = 0; others <= MAX_PAGES; others++) {
            selectPage[others] = LOW;
          }
          selectPage[14] = HIGH;
          Plugin_View_Static();
        }
      }


      if (gridTouchY == 3) {
        //note1_offset
        if (gridTouchX == 3 || gridTouchX == 4) {
          note1_Offset = map(Potentiometer1, 0, 1023, -12, 12);
          tft.fillRect(STEP_FRAME_W * 3 + 1, STEP_FRAME_H * 3 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        }
        //note2_offset
        if (gridTouchX == 6 || gridTouchX == 7) {
          note2_Offset = map(Potentiometer1, 0, 1023, -12, 12);
          tft.fillRect(STEP_FRAME_W * 6 + 1, STEP_FRAME_H * 3 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        }
        //note3_offset
        if (gridTouchX == 9 || gridTouchX == 10) {
          note3_Offset = map(Potentiometer1, 0, 1023, -12, 12);
          tft.fillRect(STEP_FRAME_W * 9 + 1, STEP_FRAME_H * 3 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        }
        //note4_offset
        if (gridTouchX == 12 || gridTouchX == 13) {
          note4_Offset = map(Potentiometer1, 0, 1023, -12, 12);
          tft.fillRect(STEP_FRAME_W * 12 + 1, STEP_FRAME_H * 3 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        }
        //Release
        /*
        if (gridTouchX == 15 || gridTouchX == 16) {
         }*/
      }

      if (gridTouchY == 6) {
        //note1_offset
        if (gridTouchX == 3 || gridTouchX == 4) {
          note1_Velo_rnd = map(Potentiometer1, 0, 1023, 0, 100.00);
          note1_Velo = note1_Velo_rnd / 100.00;
          tft.fillRect(STEP_FRAME_W * 3 + 1, STEP_FRAME_H * 6 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        }
        //note2_offset
        if (gridTouchX == 6 || gridTouchX == 7) {
          note2_Velo_rnd = map(Potentiometer1, 0, 1023, 0, 100.00);
          note2_Velo = note2_Velo_rnd / 100.00;
          tft.fillRect(STEP_FRAME_W * 6 + 1, STEP_FRAME_H * 6 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        }
        //note3_offset
        if (gridTouchX == 9 || gridTouchX == 10) {
          note3_Velo_rnd = map(Potentiometer1, 0, 1023, 0, 100.00);
          note3_Velo = note3_Velo_rnd / 100.00;
          tft.fillRect(STEP_FRAME_W * 9 + 1, STEP_FRAME_H * 6 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        }
        //note4_offset
        if (gridTouchX == 12 || gridTouchX == 13) {
          note4_Velo_rnd = map(Potentiometer1, 0, 1023, 0, 100.00);
          note4_Velo = note4_Velo_rnd / 100.00;
          tft.fillRect(STEP_FRAME_W * 12 + 1, STEP_FRAME_H * 6 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        }
        //Release
        /*
        if (gridTouchX == 15 || gridTouchX == 16) {
         }*/
      }
    }
  }
}

void Plugin1_Page2_Dynamic() {


  tft.setTextSize(1);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);

  tft.setCursor(STEP_FRAME_W * 3, STEP_FRAME_H * 2);
  tft.print("Freq");

  tft.setCursor(STEP_FRAME_W * 6, STEP_FRAME_H * 2);
  tft.print("Res");

  tft.setCursor(STEP_FRAME_W * 9, STEP_FRAME_H * 2);
  tft.print("Swp");

  tft.setCursor(STEP_FRAME_W * 12, STEP_FRAME_H * 2);
  tft.print("Att");

  tft.setCursor(STEP_FRAME_W * 15, STEP_FRAME_H * 2);
  tft.print("Rel");


  tft.setCursor(STEP_FRAME_W * 3 + 2, STEP_FRAME_H * 3 + 5);
  tft.print(Filter1_Frequency);

  tft.setCursor(STEP_FRAME_W * 6 + 2, STEP_FRAME_H * 3 + 5);
  tft.print(Filter1_Resonance);

  tft.setCursor(STEP_FRAME_W * 9 + 2, STEP_FRAME_H * 3 + 5);
  tft.print(Filter1_Sweep);

  tft.setCursor(STEP_FRAME_W * 12 + 2, STEP_FRAME_H * 3 + 5);
  tft.print(Env1_Attack);

  tft.setCursor(STEP_FRAME_W * 15 + 2, STEP_FRAME_H * 3 + 5);
  tft.print(Env1_Release);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ts.touched()) {

      //page selection
      if (gridTouchX >= 18) {
        //page1
        if (gridTouchY == 3 || gridTouchY == 4) {
          for (byte others = 0; others <= MAX_PAGES; others++) {
            selectPage[others] = LOW;
          }
          selectPage[PLUGIN1_PAGE1] = HIGH;
          Plugin_View_Static();
        }
        //page2
        if (gridTouchY == 5 || gridTouchY == 6) {
          for (byte others = 0; others <= MAX_PAGES; others++) {
            selectPage[others] = LOW;
          }
          selectPage[PLUGIN1_PAGE2] = HIGH;
          Plugin_View_Static();
        }
        //page3
        if (gridTouchY == 7 || gridTouchY == 8) {
          for (byte others = 0; others <= MAX_PAGES; others++) {
            selectPage[others] = LOW;
          }
          selectPage[PLUGIN1_PAGE3] = HIGH;
          Plugin_View_Static();
        }
        //page4
        if (gridTouchY == 9 || gridTouchY == 10) {
          for (byte others = 0; others <= MAX_PAGES; others++) {
            selectPage[others] = LOW;
          }
          selectPage[PLUGIN1_PAGE4] = HIGH;
          Plugin_View_Static();
        }
      }

      if (gridTouchY == 3) {
        //filter frequency
        if (gridTouchX == 3 || gridTouchX == 4) {
          Filter1_Frequency = map(Potentiometer1, 0, 1023, 40, 4000);
          filter1.frequency(Filter1_Frequency);
          tft.fillRect(STEP_FRAME_W * 3 + 1, STEP_FRAME_H * 3 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        }
        //Resonance
        if (gridTouchX == 6 || gridTouchX == 7) {
          Filter1_Resonance_rnd = map(Potentiometer1, 0, 1023, 7, 50);
          Filter1_Resonance = Filter1_Resonance_rnd / 10.00;
          filter1.resonance(Filter1_Resonance);
          tft.fillRect(STEP_FRAME_W * 6 + 1, STEP_FRAME_H * 3 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        }
        //Sweep
        if (gridTouchX == 9 || gridTouchX == 10) {
          Filter1_Sweep_rnd = map(Potentiometer1, 0, 1023, 0, 70);
          Filter1_Sweep = Filter1_Sweep_rnd / 10.00;
          filter1.octaveControl(Filter1_Sweep);
          tft.fillRect(STEP_FRAME_W * 9 + 1, STEP_FRAME_H * 3 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        }
        //Attack
        if (gridTouchX == 12 || gridTouchX == 13) {
          Env1_Attack = map(Potentiometer1, 0, 1023, 10, 700);
          envelope1.attack(Env1_Attack);
          envelope2.attack(Env1_Attack);
          tft.fillRect(STEP_FRAME_W * 12 + 1, STEP_FRAME_H * 3 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        }
        //Release
        if (gridTouchX == 15 || gridTouchX == 16) {
          Env1_Release = map(Potentiometer1, 0, 1023, 50, 2000);
          envelope1.release(Env1_Release);
          envelope2.release(Env1_Release);
          tft.fillRect(STEP_FRAME_W * 15 + 1, STEP_FRAME_H * 3 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        }
      }
    }
  }
}