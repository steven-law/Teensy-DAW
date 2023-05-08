//pointers for the audio plugins, maybe this will get easier with mannickens audio lib tool


//please use this Audio GUI from Newdigate
//https://newdigate.github.io/teensy-eurorack-audio-gui/

#define pl1NR 0
#define pl3NR 2
#define pl5NR 4
#define pl6NR 5
#define pl7NR 6
#define pl8NR 7
#define pl9NR 8
#define pl10NR 9
#define pl11NR 10

#define fx1NR 0
#define fx2NR 1

#define fx3NR 2
const char *pluginName[MAX_PLUGINS]{ "Chrd", "SDrm", "1OSC", "MDrm", "Raw1", "Raw2", "Drum", "MogL", "Strng", "dtune", "RDrm", "12", "13", "14", "15", "16" };

#define PLUGIN1_PAGE1 40
#define PLUGIN2_PAGE1 41
#define PLUGIN3_PAGE1 42
#define PLUGIN4_PAGE1 43
#define PLUGIN5_PAGE1 44
#define PLUGIN6_PAGE1 45
#define PLUGIN7_PAGE1 46
#define PLUGIN8_PAGE1 47
#define PLUGIN9_PAGE1 48
#define PLUGIN10_PAGE1 49
#define PLUGIN11_PAGE1 50
#define PLUGIN12_PAGE1 51
#define PLUGIN13_PAGE1 52
#define PLUGIN14_PAGE1 53
#define PLUGIN15_PAGE1 54
#define PLUGIN16_PAGE1 55



#define PLUGIN1_PAGE2 60
#define PLUGIN1_PAGE3 61
#define PLUGIN1_PAGE4 62
#define PLUGIN7_PAGE2 63
#define PLUGIN7_PAGE3 64

#define MAX_ENC_RANGE 127
#define ATTACK_TIME 127
#define DECAY_TIME 700
#define SUSTAIN_LVL 127.00
#define RELEASE_TIME 1600
#define SVF_RES 25.40
#define SVF_SWP 18.14
#define SVF_TYP 42
#define MAX_RESONANCE 5

#define ZERO 0.00

#define GAIN_DIV_32 4095
#define GAIN_DIV_16 2047
#define GAIN_DIV_8 1023
#define GAIN_DIV_4 511
#define GAIN_DIV_2 255
#define GAIN_MULT_1 127.00
#define GAIN_MULT_2 64.00
#define GAIN_MULT_4 32.00
#define GAIN_MULT_8 16.00

AudioAmplifier *gainmax[MAX_PLUGINS]{ &pl1amp2, &pl2amp2, &pl3amp2, &pl4amp2, &pl5amp2, &pl6amp2, &pl7amp2, &pl8amp2,
                                      &pl9amp2, &pl10amp2, &pl11amp2, &pl12amp2, &pl13amp2, &pl14amp2, &pl15amp2, &pl16amp2 };
AudioAmplifier *gainPerBar[MAX_PLUGINS]{ &pl1amp, &pl2amp, &pl3amp, &pl4amp, &pl5amp, &pl6amp, &pl7amp, &pl8amp,
                                         &pl9amp, &pl10amp, &pl11amp, &pl12amp, &pl13amp, &pl14amp, &pl15amp, &pl16amp };

AudioAmplifier *dryVolume[MAX_PLUGINS]{ &pl1dry, &pl2dry, &pl3dry, &pl4dry, &pl5dry, &pl6dry, &pl7dry, &pl8dry,
                                        &pl9dry, &pl10dry, &pl11dry, &pl12dry, &pl13dry, &pl14dry, &pl15dry, &pl16dry };
AudioAmplifier *FX1Volume[MAX_PLUGINS]{ &pl1FX1, &pl2FX1, &pl3FX1, &pl4FX1, &pl5FX1, &pl6FX1, &pl7FX1, &pl8FX1,
                                        &pl9FX1, &pl10FX1, &pl11FX1, &pl12FX1, &pl13FX1, &pl14FX1, &pl15FX1, &pl16FX1 };
AudioAmplifier *FX2Volume[MAX_PLUGINS]{ &pl1FX2, &pl2FX2, &pl3FX2, &pl4FX2, &pl5FX2, &pl6FX2, &pl7FX2, &pl8FX2,
                                        &pl9FX2, &pl10FX2, &pl11FX2, &pl12FX2, &pl13FX2, &pl14FX2, &pl15FX2, &pl16FX2 };
AudioAmplifier *FX3Volume[MAX_PLUGINS]{ &pl1FX3, &pl2FX3, &pl3FX3, &pl4FX3, &pl5FX3, &pl6FX3, &pl7FX3, &pl8FX3,
                                        &pl9FX3, &pl10FX3, &pl11FX3, &pl12FX3, &pl13FX3, &pl14FX3, &pl15FX3, &pl16FX3 };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


AudioSynthWaveform *OSC[6]{
  &pl1waveform1,   //0
  &pl3waveform1,   //1
  &pl8waveform1,   //2
  &pl9bpinput,     //3
  &pl10waveform1,  //4
};
#define OSC_MAX_WF 8

#define pl1OSC 0
#define pl3OSC 1
#define pl8OSC 2
#define pl9OSC 3
#define pl10OSC_M 4

AudioSynthWaveformModulated *OSC_MOD[7]{
  &pl1waveformMod1, &pl1waveformMod2, &pl1waveformMod3, &pl1waveformMod4,  //0,1,2,3
  &pl3waveformMod1,                                                        //4
  &pl7waveformMod1, &pl7waveformMod2                                       //5,6
};
#define OSC_MOD_MAX_WF 12
#define pl1OSC_MOD0 0
#define pl1OSC_MOD1 1
#define pl1OSC_MOD2 2
#define pl1OSC_MOD3 3
#define pl3OSC_MOD 4
#define pl7OSC1 5
#define pl7OSC2 6
AudioSynthWaveformPWM *PWM[2]{
  &pl10pwm1, &pl10pwm2  //0,1
};
#define pl10PWM1 0
#define pl10PWM2 1

AudioSynthWaveformDc *DC[8]{
  &pl1dc1,                      //0
  &pl3dc1,                      //1
  &pl5dc1,                      //2
  &pl6dc1,                      //3
  &pl8dc1,                      //4
  &pl10dc1, &pl10dc2, &pl10dc3  //5,6,7
};
#define pl1DC1 0
#define pl3DC1 1
#define pl5DC1 2
#define pl6DC1 3
#define pl8DC1 4
#define pl10DC1 5
#define pl10DC2 6
#define pl10DC3 7

AudioSynthSimpleDrum *DRUM[1]{
  &pl7drum1  //0
};
#define pl7DRUM 0

AudioSynthNoiseWhite *WHITE[3]{
  &pl7noise1, &pl7noise2,  //0,1
  &pl10noise1              //2
};
#define pl7WHITE1 0
#define pl7WHITE2 1
#define pl10WHITE 2

AudioPlaySdWav *PL2PLAYER[12]{
  &playSdWav1, &playSdWav2, &playSdWav3, &playSdWav4,
  &playSdWav5, &playSdWav6, &playSdWav7, &playSdWav8,
  &playSdWav9, &playSdWav10, &playSdWav11, &playSdWav12
};

AudioPlaySdRaw *PL11PLAYER[12]{
  &playSdRaw1, &playSdRaw2, &playSdRaw3, &playSdRaw4,
  &playSdRaw5, &playSdRaw6, &playSdRaw7, &playSdRaw8,
  &playSdRaw9, &playSdRaw10, &playSdRaw11, &playSdRaw12
};
/*
AudioPlayMemory *PL4PLAYER[12]{
  &playMem1, &playMem2, &playMem3, &playMem4,
  &playMem5, &playMem6, &playMem7, &playMem8,
  &playMem9, &playMem10, &playMem11, &playMem12
};
*/



AudioEffectEnvelope *ENVELOPE1[16]{
  &envelope1, &envelope2,         //0,1
  &pl3envelope1, &pl3envelope2,   //2,3
  &pl5envelope1, &pl5envelope2,   //4,5
  &pl6envelope1, &pl6envelope2,   //6,7
  &pl7envelope1, &pl7envelope2,   //8,9
  &pl7envelope3, &pl7envelope4,   //10,11
  &pl8envelope1, &pl8envelope2,   //12,13
  &pl10envelope1, &pl10envelope2  //14,15
};
#define pl1ADSR1 0
#define pl1ADSR2 1
#define pl3ADSR1 2
#define pl3ADSR2 3
#define pl5ADSR1 4
#define pl5ADSR2 5
#define pl6ADSR1 6
#define pl6ADSR2 7
#define pl7ADSR1 8
#define pl7ADSR2 9
#define pl7ADSR3 10
#define pl7ADSR4 11
#define pl8ADSR1 12
#define pl8ADSR2 13
#define pl10ADSR1 14
#define pl10ADSR2 15

AudioFilterStateVariable *STATEFILTER[8]{
  &filter1,                  //0
  &pl3filter1,               //1
  &pl5filter1,               //2
  &pl6filter1,               //3
  &pl7filter1, &pl7filter2,  //3,4
  &pl9bpfilter,              //6
  &pl10filter1               //7
};
#define SVF_MAX_OCT 12
#define pl1SVF 0
#define pl3SVF 1
#define pl5SVF 2
#define pl6SVF 3
#define pl7SVF1 4
#define pl7SVF2 5
#define pl9SVF 6
#define pl10SVF 7
AudioFilterLadder *LADDERFILTER[1]{ &pl8filter1 };  //pl8
#define pl8LADDER 0


AudioPlaySdResmp *RAWPLAY[2]{ &playSdPitch1, &playSdPitch2 };
#define pl5RAW 0
#define pl6RAW 1


AudioMixer4 *FILTERMIXER[6]{
  &pl1mixer2,  //0
  &pl3mixer1,  //1
  &pl5mixer1,  //2
  &pl6mixer1,  //3
  &pl9mixer1,  //4
  &pl10mixer2  //5
};
#define pl1TYPE 0
#define pl3TYPE 1
#define pl5TYPE 2
#define pl6TYPE 3
#define pl9TYPE 4
#define pl10TYPE 5

AudioEffectBitcrusher *BITCRUSHER[1]{ &bitcrusher2 };
#define FX2BITCRUSH 0

AudioEffectReverb *REVERB[1]{ &reverb1 };
#define FX1REVERB 0

AudioMixer4 *PL2MIX[3]{ &drummixer1, &drummixer1, &drummixer1 };
AudioMixer4 *PL4MIX[3]{ &pl4drummixer1, &pl4drummixer1, &pl4drummixer1 };
AudioMixer4 *PL11MIX[3]{ &pl11drummixer1, &pl11drummixer1, &pl11drummixer1 };
