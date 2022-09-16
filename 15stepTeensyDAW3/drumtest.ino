void drumSettings () {
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

  //mixer1 to controll Waveform1 with stationKnob; Waveform2-4 with startKnob on page 1
  mixer1.gain(0, 1);
  mixer1.gain(1, 0);
  mixer1.gain(2, 0);
  mixer1.gain(3, 0);

  envelope1.delay(0);
  envelope1.attack(200);
  envelope1.hold(0);
  envelope1.decay(500);
  envelope1.sustain(0.8);
  envelope1.release(500);

  envelope2.delay(0);
  envelope2.attack(200);
  envelope2.hold(0);
  envelope2.decay(500);
  envelope2.sustain(0.8);
  envelope2.release(500);

  dc2.amplitude(1);

  dc3.amplitude(0);
  mixer4.gain(0, 1);
  mixer4.gain(1, 1);

  //filter1 is controlled by the stationCV input
  filter1.frequency(260);                                                  //set initial Filter1 freq to 16000Hz
  filter1.resonance(0);                                                      //set Resonance to 0
  filter1.octaveControl(7);

  //filter2 is controlled by the stationKnob on page 0
  // filter2.frequency(16000);                                                  //set initial Filter2 freq to 16000Hz
  // filter2.resonance(0);                                                      //set Resonance to 0

  //mixer2 is just there, no need for it actually
  mixer2.gain(0, 1);                                                         //set Mixer2(Channel, Gain) (0-3, 0-1)
  mixer2.gain(1, 1);

  //dc1 for wavefolder input controlled by stationKnob on page 3
  dc1.amplitude(0.05);                                                       //set dc1 for Wavefolder Input

  //bitcrusher1 controlled by startKnob on page 3
  bitcrusher1.bits(16);
  bitcrusher1.sampleRate(44100);

  //delay1 time controlled by stationKnob; feedback controlled by startKnob on page 4
  delay1.delay(0, 3);                                                        //set Delay(OutChannel, saved Samples) (0-7, 3-449*) *maximum

  //filter3 HighPassfilter to get rid of the muddy sound in feedbackloop
  filter3.frequency(200);                                                   //set initial Filter3 freq to 16000Hz
  filter3.resonance(0);                                                      //set Resonance to 0

  //mixer3 for feedback controlled by startKnob on page 4
  mixer3.gain(0, 1);                                                         //setze Mixer2(Kanal, Gain) (0-3, 0-1)
  mixer3.gain(1, 0);

  //mixer5 again just a mixer to pass audio thru
  mixer5.gain(0, 0.5);
}
