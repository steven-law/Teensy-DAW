void drumSettings() {
  waveform1.begin(WAVEFORM_SAWTOOTH);
  waveform1.amplitude(1);
  waveform1.frequency(65.41);
  waveform1.pulseWidth(0.15);

  waveform2.begin(WAVEFORM_SAWTOOTH);
  waveform2.amplitude(1);
  waveform2.frequency(65.41);
  waveform2.pulseWidth(0.15);

  waveform3.begin(WAVEFORM_SAWTOOTH);
  waveform3.amplitude(1);
  waveform3.frequency(65.41);
  waveform3.pulseWidth(0.15);

  waveform4.begin(WAVEFORM_SAWTOOTH);
  waveform4.amplitude(1);
  waveform4.frequency(65.41);
  waveform4.pulseWidth(0.15);


  mixer1.gain(0, 1);
  mixer1.gain(1, 0);
  mixer1.gain(2, 0);
  mixer1.gain(3, 0);

  envelope1.delay(0);
  envelope1.attack(Env1_Attack);
  envelope1.hold(0);
  envelope1.decay(500);
  envelope1.sustain(0.8);
  envelope1.release(Env1_Release);

  envelope2.delay(0);
  envelope2.attack(Env1_Attack);
  envelope2.hold(0);
  envelope2.decay(500);
  envelope2.sustain(0.8);
  envelope2.release(Env1_Release);

  dc2.amplitude(1);

  dc3.amplitude(0);
  mixer4.gain(0, 1);
  mixer4.gain(1, 1);


  filter1.frequency(Filter1_Frequency);
  filter1.resonance(Filter1_Reso);       
  filter1.octaveControl(Filter1_Sweep);


  //mixer2 is just there, no need for it actually
  mixer2.gain(0, 1);  //set Mixer2(Channel, Gain) (0-3, 0-1)
  mixer2.gain(1, 1);

  //dc1 for wavefolder input controlled by stationKnob on page 3
  dc1.amplitude(0.05);  //set dc1 for Wavefolder Input

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
  mixer5.gain(0, 0.5);
}


void Plugin_1_View_Static() {
  clearWorkSpace();
  for (int c = 1; c < 6; c++) {
    tft.setCursor(STEP_FRAME_W * c * 3 - 3, STEP_FRAME_H + 3);
    tft.setFont(Arial_10);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(1);
    tft.print(controlNamesRow1[c - 1]);
    tft.drawRect(STEP_FRAME_W * c * 3, STEP_FRAME_H * 2, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);
  }
  Plugin_1_View_Dynamic();
}

void Plugin_1_View_Dynamic() {
  /*tft.setCursor(STEP_FRAME_W * 1 * 3 + 2, STEP_FRAME_H * 2 + 3 + 2);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print(Filter1_Frequency);*/

  tft.setCursor(STEP_FRAME_W * 2 * 3 + 2, STEP_FRAME_H * 2 + 3 + 2);
  tft.print(Filter1_Reso);

  tft.setCursor(STEP_FRAME_W * 3 * 3 + 2, STEP_FRAME_H * 2 + 3 + 2);
  tft.print(Filter1_Sweep);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (ts.touched()) {
      TS_Point p = ts.getPoint();
      gridTouchX = map(p.x, 180, 3730, 0, 19);
      gridTouchY = map(p.y, 260, 3760, 0, 14);
     // if (gridTouchY == 2) {
        if (gridTouchX == 3 && gridTouchY == 2|| gridTouchX == 4 && gridTouchY == 2) {
          //Filter1_Frequency = map(Potentiometer1, 0, 1023, 40, 4000);
          filter1.frequency(map(Potentiometer1, 0, 1023, 40, 4000));

          tft.fillRect(STEP_FRAME_W * 1 * 3 + 1, STEP_FRAME_H * 2 + 3 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H * 2 - 2, ILI9341_DARKGREY);
          tft.setCursor(STEP_FRAME_W * 1 * 3 + 2, STEP_FRAME_H * 2 + 3 + 2);
          tft.setFont(Arial_8);
          tft.setTextColor(ILI9341_WHITE);
          tft.setTextSize(1);
          tft.print(Filter1_Frequency);
          Serial.println(Potentiometer1);
        }
     // }
    }
  }
}