/*Contributing Manual:

Many Thanks to Tristan Rowley, without his immense efforts and time to explain things to me, 
this project would have never reached this amount of functions and still have a more or less readable code. 
For more Informations on him, please take a look at www.github.com/doctea and www.doctea.co.uk!!  
Very Interesting stuff to find and try out!!!

Hello. Here i will show you how to implement new stuff easily.

There are some things left to be made at this point, but feel free to add your features.

toDo´s:
    • add polyphony
    • internal plugins 
    • if in the stepsequencer of a track, i would like to hear the selected clip. when in songmode, only play the arrangment 
    • Adding the audioboard. for teensy 4.1
    • make a PCB 
    • make a housing 
    • implement Record-function


1. 15stepTeensyDAW3.ino :

This is the main sketch. It is easier to look at it in chapters: 
Including all the librarys and the .h file
calibration and customizing
initiate the modules
Place for the PJRC GUItool for the internal plugins (audio Connections)

void loop(), run, the sequencer, reading the inputs. Applying all the controls from the 	startscreen when touched(trackselection, transportcontrol, arrengmenttype).
With each touch on one of the controls we switch all other functions to „false/LOW“ 	so the touches are not misinterpreted. After setting the state the code will open up 	the desired „window“.

Touch XY input is mapped to a grid of x=20, y=15 frames! 		
Each frame has a Frameheight and -width of 16 pixels.     		

void savebutton() if we hit the save button, do all the savings. Right now it saves the clip-array into one big junk of ascii´s, that is read when loading.
void loadbutton() Loading the clips array from the sd card.
void startUpScreen() here are all the graphical elements from the startupscreen 
void showCoordinates() shows the actual touch-coordinates

Head over to Pl31OSC.ino to see how to implement new plugins
*/


#include <Audio.h>
#include <Wire.h>
#include <SerialFlash.h>

#include <ILI9341_t3.h>
#include <font_Arial.h>  // from ILI9341_t3
//#include <ILI9341_t3n.h>
//#include <ILI9341_t3n_font_Arial.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include <SD.h>
#include <TeensyVariablePlayback.h>
//#include "FifteenStep.h"
#include "variables.h"
#include <Bounce2.h>

// WAV files converted to code by wav2sketch
//#include "AudioSampleSnare.h"         // http://www.freesound.org/people/KEVOY/sounds/82583/
//#include "AudioSampleTomtom.h"        // http://www.freesound.org/people/zgump/sounds/86334/
//#include "AudioSampleHihat.h"         // http://www.freesound.org/people/mhc/sounds/102790/
//#include "AudioSampleKick.h"          // http://www.freesound.org/people/DWSD/sounds/171104/
//#include "AudioSampleCashregister.h"  // http://www.freesound.org/people/kiddpark/sounds/201159/
//#include "AudioSampleP2.h"
#include "AudioSamplesTest.h"

//calibration and customizing
//Teensy 3.5 PINOUT
//Pinout for screen
#define TIRQ_PIN 2   //alternate Pins: any digital pin
#define CS_PIN 8     //alternate Pins: any digital pin
#define TFT_DC 15    //alternate Pins 9, 10, 20, 21
#define TFT_CS 10    //alternate Pins 9, 15, 20, 21
#define TFT_RST 255  // 255 = unused, connect to 3.3V
#define TFT_MOSI 11  //shareable
#define TFT_SCLK 13  //shareable
#define TFT_MISO 12  //shareable
//button Pins
#define LEFTBUTTON 30
#define RIGHTBUTTON 28
#define UPBUTTON 27
#define DOWNBUTTON 29
#define STARTBUTTON 26
#define STOPBUTTON 24
#define ENTERBUTTON 25
//Potentiometer Pins
#define POTENTIOMETER_1_PIN 31
#define POTENTIOMETER_2_PIN 32

/*//Teensy 4.1 PINOUT
//Pinout for screen
#define TIRQ_PIN 0   //alternate Pins: any digital pin
#define CS_PIN 1     //alternate Pins: any digital pin
#define TFT_DC 9    //alternate Pins 9, 10, 20, 21
#define TFT_CS 10    //alternate Pins 9, 15, 20, 21
#define TFT_RST 255  // 255 = unused, connect to 3.3V
#define TFT_MOSI 11  //shareable
#define TFT_SCLK 13  //shareable
#define TFT_MISO 12  //shareable

//button Pins
#define ROW_1 41
#define ROW_4 40
#define ROW_3 39
#define ROW_2 38
#define COLUMN_1 37
#define COLUMN_2 36
#define COLUMN_3 35
#define COLUMN_4 34
//Potentiometer Pins
#define POTENTIOMETER_1_PIN 27
#define POTENTIOMETER_1_PIN 26
#define POTENTIOMETER_1_PIN 25
#define POTENTIOMETER_1_PIN 24
*/

//calibrate your Screen
// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 440
#define TS_MINY 300
#define TS_MAXX 3850
#define TS_MAXY 3800

//touchscreen response; to be changed
const long interval = 200;

//pinout for SD CARD
const int chipSelect = BUILTIN_SDCARD;

//initial drumnotes
byte drumnote[12]{ 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47 };

//noteOn velocity for all tracks
#define VELOCITY 96



//individual trackcolors
int trackColor[9]{ 6150246, 8256638, 1095334, 12643941, 2583100, 9365295, 12943157, 5678954, ILI9341_WHITE };
//end of calibration and custumizing

//initiate bounce
Bounce* buttons = new Bounce[NUM_BUTTONS];

//initiate the modules
//FifteenStep seq = FifteenStep(SEQUENCER_MEMORY);                                     //initiate Sequencer
File myFile;                                                                         //initiate SDCard Reader
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);  //initiate TFT-Srceen
XPT2046_Touchscreen ts(CS_PIN);                                                      //initiate Touchscreen






//please use this Audio GUI from Newdigate
//https://newdigate.github.io/teensy-eurorack-audio-gui/


//Place for the Pluginconnections

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     pl5dc1;         //xy=61.5,1260
AudioPlayMemory          playMem9;       //xy=62.5,1044
AudioSynthWaveformDc     pl6dc1;         //xy=63.5,1364
AudioSynthNoiseWhite     pl7noise1;      //xy=64.5,1542
AudioPlayMemory          playMem10;      //xy=67.5,1075
AudioPlayMemory          playMem7;       //xy=72.5,974
AudioPlayMemory          playMem8;       //xy=72.5,1011
AudioSynthWaveform       waveform3;      //xy=78.5,145
AudioSynthWaveform       waveform1;      //xy=81.5,49
AudioSynthWaveform       waveform2;      //xy=82.5,98
AudioPlayMemory          playMem5;       //xy=82.5,898
AudioPlayMemory          playMem6;       //xy=83.5,936
AudioSynthWaveformDc     pl1dc1;         //xy=87.5,239
AudioPlaySdWav           playSdWav12;    //xy=87.5,709
AudioPlayMemory          playMem1;       //xy=87.5,758
AudioPlaySdWav           playSdWav7;     //xy=89.5,528
AudioPlayMemory          playMem2;       //xy=88.5,794
AudioPlaySdWav           playSdWav9;     //xy=89.5,600
AudioPlaySdWav           playSdWav3;     //xy=90.5,373
AudioPlaySdWav           playSdWav10;    //xy=89.5,634
AudioPlaySdWav           playSdWav4;     //xy=90.5,409
AudioPlaySdWav           playSdWav11;    //xy=89.5,673
AudioSynthWaveform       waveform4;      //xy=91.5,195
AudioPlaySdWav           playSdWav8;     //xy=90.5,565
AudioPlayMemory          playMem11;      //xy=89.5,1114
AudioPlaySdWav           playSdWav2;     //xy=93.5,336
AudioPlaySdWav           playSdWav5;     //xy=93.5,449
AudioPlaySdWav           playSdWav6;     //xy=93.5,489
AudioPlaySdWav           playSdWav1;     //xy=96.5,297
AudioPlayMemory          playMem12;      //xy=94.5,1152
AudioPlayMemory          playMem3;       //xy=97.5,828
AudioPlayMemory          playMem4;       //xy=104.5,864
AudioSynthWaveformSine   pl7waveformMod3; //xy=105.5,1628
AudioSynthNoiseWhite     pl7noise2;      //xy=168.5,1685
AudioSynthNoisePink      pl7pink1;       //xy=168.5,1725
AudioPlaySdResmp         playSdPitch1;   //xy=196.5,1205
AudioEffectEnvelope      pl5envelope2;   //xy=209.5,1259
AudioPlaySdResmp         playSdPitch2;   //xy=209.5,1312
AudioEffectEnvelope      pl6envelope2;   //xy=211.5,1363
AudioEffectEnvelope      envelope1;      //xy=229.5,236
AudioMixer4              mixer1;         //xy=241.5,86
AudioSynthSimpleDrum     pl7drum1;       //xy=275.5,1464
AudioSynthWaveformModulated pl7waveformMod1; //xy=282.5,1545
AudioEffectEnvelope      pl7envelope2;   //xy=285.5,1626
AudioSynthWaveformDc     pl3dc1;         //xy=292.5000057220459,678.0000076293945
AudioMixer4              drummixer1;     //xy=297.5,321
AudioMixer4              drummixer2;     //xy=299.5,410
AudioMixer4              drummixer3;     //xy=308.5,502
AudioMixer4              pl4drummixer1;  //xy=309.5,775
AudioMixer4              pl7mixer4;      //xy=307.5,1713
AudioMixer4              pl4drummixer2;  //xy=311.5,864
AudioMixer4              pl4drummixer3;  //xy=320.5,956
AudioSynthWaveform       pl3waveform1;   //xy=329.5000057220459,615.0000076293945
AudioSynthWaveformDc     pl8dc1;         //xy=360.50000762939453,1866.0000286102295
AudioFilterStateVariable pl5filter1;     //xy=373.5,1225
AudioFilterStateVariable pl6filter1;     //xy=375.5,1329
AudioFilterStateVariable filter1;        //xy=394.5,82
AudioEffectEnvelope      pl3envelope2;   //xy=435.5000057220459,675.0000076293945
AudioFilterStateVariable pl7filter1;     //xy=445.5,1464
AudioFilterStateVariable pl7filter2;     //xy=446.5,1554
AudioSynthWaveformDc     pl7dc1;         //xy=448.5,1508
AudioEffectEnvelope      envelope2;      //xy=454.5,131
AudioFilterBiquad        pl7biquad1;     //xy=449.5,1705
AudioSynthWaveformModulated pl7waveformMod2; //xy=461.5,1629
AudioMixer4              drummixer4;     //xy=482.5,431
AudioSynthWaveform       pl8waveform1;   //xy=490.50000762939453,1815.0000276565552
AudioFilterStateVariable pl3filter1;     //xy=516.5000057220459,624.0000076293945
AudioEffectEnvelope      pl8envelope2;   //xy=515.5000076293945,1865.0000276565552
AudioMixer4              pl4drummixer4;  //xy=537.5,784
AudioEffectEnvelope      pl5envelope1;   //xy=538.5,1213
AudioEffectEnvelope      pl6envelope1;   //xy=540.5,1316
AudioEffectBitcrusher    bitcrusher1;    //xy=574.5,80
AudioSynthWaveform       pl9bpinput;      //xy=578.0000076293945,2031.0000305175781
AudioSynthKarplusStrong  pl9string1;        //xy=582.0000076293945,1980.0000295639038
AudioEffectEnvelope      pl7envelope1;   //xy=599.5,1539
AudioEffectEnvelope      pl7envelope4;   //xy=637.5,1703
AudioEffectEnvelope      pl7envelope3;   //xy=643.5,1640
AudioEffectWaveFolder    pl7wavefolder1; //xy=653.5,1456
AudioEffectEnvelope      pl3envelope1;   //xy=673.5000057220459,612.0000076293945
AudioFilterLadder        pl8filter1;     //xy=694.5,1826
AudioEffectDelay         pl1delay1;      //xy=723.5,218
AudioMixer4              pl1mixer3;      //xy=727.5,35
AudioFilterStateVariable pl1filter3;     //xy=727.5,110
AudioFilterStateVariable pl9bpfilter;        //xy=722.0000076293945,1984.0000286102295
AudioSynthWaveformDc     pl9dc1;            //xy=722.0000114440918,2032.0000305175781
AudioAmplifier           pl4amp;         //xy=751.5,773
AudioAmplifier           pl6amp;         //xy=771.5,1316
AudioAmplifier           pl2amp;         //xy=779.5,441
AudioAmplifier           pl5amp;         //xy=778.5,1217
AudioAmplifier           pl3amp;         //xy=829.5000057220459,607.0000076293945
AudioMixer4              pl7mixer2;      //xy=840.5,1731
AudioMixer4              pl7mixer1;      //xy=842.5,1650
AudioEffectEnvelope      pl8envelope1;   //xy=846.5,1837
AudioEffectWaveFolder    pl9wavefolder1;    //xy=885.0000114440918,1982.0000295639038
AudioAmplifier           pl1amp;         //xy=971.5,173
AudioMixer4              pl7mixer3;      //xy=992.5,1654
AudioAmplifier           pl7amp;         //xy=997.5,1568
AudioAmplifier           pl8amp;         //xy=1002.5,1832
AudioAmplifier           pl9amp;           //xy=1064.000015258789,1982.0000305175781
AudioMixer4              mixer6;         //xy=1176.5,1272
AudioMixer4              FX2mixer1;      //xy=1188.5,694
AudioMixer4              mixer5;         //xy=1190.5,530
AudioMixer4              FX3mixer2;      //xy=1187.5,1529
AudioMixer4              FX1mixer1;      //xy=1191.5,607
AudioMixer4              FX2mixer2;      //xy=1188.5,1442
AudioMixer4              FX1mixer2;      //xy=1189.5,1357
AudioMixer4              FX3mixer1;      //xy=1193.5,781
AudioMixer4              FX2mixer4;         //xy=1224,2159
AudioMixer4              FX3mixer4;         //xy=1239,2231
AudioMixer4              FX1mixer4;         //xy=1247,2075
AudioMixer4              mixer10;         //xy=1250.0000190734863,1990.0000305175781
AudioMixer4              mixer8;         //xy=1576.5,697
AudioMixer4              FX2mixer3;      //xy=1580.5,877
AudioMixer4              FX1mixer3;      //xy=1586.5,794
AudioMixer4              FX3mixer3;      //xy=1588.5,967
AudioEffectReverb        reverb1;        //xy=1750.5,766
AudioEffectBitcrusher    bitcrusher2;    //xy=1764.5,834
AudioFilterStateVariable dlfilter1;      //xy=1787.5,1003
AudioEffectDelay         dldelay1;       //xy=1787.5,1088
AudioMixer4              dlmixer1;       //xy=1789.5,948
AudioMixer4              mixer9;         //xy=1987.5,718
AudioOutputPT8211        pt8211_1;       //xy=2204.5,726
AudioConnection          patchCord1(pl5dc1, pl5envelope2);
AudioConnection          patchCord2(playMem9, 0, pl4drummixer3, 0);
AudioConnection          patchCord3(pl6dc1, pl6envelope2);
AudioConnection          patchCord4(pl7noise1, 0, pl7waveformMod1, 0);
AudioConnection          patchCord5(playMem10, 0, pl4drummixer3, 1);
AudioConnection          patchCord6(playMem7, 0, pl4drummixer2, 2);
AudioConnection          patchCord7(playMem8, 0, pl4drummixer2, 3);
AudioConnection          patchCord8(waveform3, 0, mixer1, 2);
AudioConnection          patchCord9(waveform1, 0, mixer1, 0);
AudioConnection          patchCord10(waveform2, 0, mixer1, 1);
AudioConnection          patchCord11(playMem5, 0, pl4drummixer2, 0);
AudioConnection          patchCord12(playMem6, 0, pl4drummixer2, 1);
AudioConnection          patchCord13(pl1dc1, envelope1);
AudioConnection          patchCord14(playSdWav12, 0, drummixer3, 3);
AudioConnection          patchCord15(playMem1, 0, pl4drummixer1, 0);
AudioConnection          patchCord16(playSdWav7, 0, drummixer2, 2);
AudioConnection          patchCord17(playMem2, 0, pl4drummixer1, 1);
AudioConnection          patchCord18(playSdWav9, 0, drummixer3, 0);
AudioConnection          patchCord19(playSdWav3, 0, drummixer1, 2);
AudioConnection          patchCord20(playSdWav10, 0, drummixer3, 1);
AudioConnection          patchCord21(playSdWav4, 0, drummixer1, 3);
AudioConnection          patchCord22(playSdWav11, 0, drummixer3, 2);
AudioConnection          patchCord23(waveform4, 0, mixer1, 3);
AudioConnection          patchCord24(playSdWav8, 0, drummixer2, 3);
AudioConnection          patchCord25(playMem11, 0, pl4drummixer3, 2);
AudioConnection          patchCord26(playSdWav2, 0, drummixer1, 1);
AudioConnection          patchCord27(playSdWav5, 0, drummixer2, 0);
AudioConnection          patchCord28(playSdWav6, 0, drummixer2, 1);
AudioConnection          patchCord29(playSdWav1, 0, drummixer1, 0);
AudioConnection          patchCord30(playMem12, 0, pl4drummixer3, 3);
AudioConnection          patchCord31(playMem3, 0, pl4drummixer1, 2);
AudioConnection          patchCord32(playMem4, 0, pl4drummixer1, 3);
AudioConnection          patchCord33(pl7waveformMod3, pl7envelope2);
AudioConnection          patchCord34(pl7noise2, 0, pl7mixer4, 0);
AudioConnection          patchCord35(pl7pink1, 0, pl7mixer4, 1);
AudioConnection          patchCord36(playSdPitch1, 0, pl5filter1, 0);
AudioConnection          patchCord37(pl5envelope2, 0, pl5filter1, 1);
AudioConnection          patchCord38(playSdPitch2, 0, pl6filter1, 0);
AudioConnection          patchCord39(pl6envelope2, 0, pl6filter1, 1);
AudioConnection          patchCord40(envelope1, 0, filter1, 1);
AudioConnection          patchCord41(mixer1, 0, filter1, 0);
AudioConnection          patchCord42(pl7drum1, 0, pl7filter1, 0);
AudioConnection          patchCord43(pl7waveformMod1, 0, pl7filter2, 0);
AudioConnection          patchCord44(pl7envelope2, 0, pl7waveformMod2, 0);
AudioConnection          patchCord45(pl3dc1, pl3envelope2);
AudioConnection          patchCord46(drummixer1, 0, drummixer4, 0);
AudioConnection          patchCord47(drummixer2, 0, drummixer4, 1);
AudioConnection          patchCord48(drummixer3, 0, drummixer4, 2);
AudioConnection          patchCord49(pl4drummixer1, 0, pl4drummixer4, 0);
AudioConnection          patchCord50(pl7mixer4, pl7biquad1);
AudioConnection          patchCord51(pl4drummixer2, 0, pl4drummixer4, 1);
AudioConnection          patchCord52(pl4drummixer3, 0, pl4drummixer4, 2);
AudioConnection          patchCord53(pl3waveform1, 0, pl3filter1, 0);
AudioConnection          patchCord54(pl8dc1, pl8envelope2);
AudioConnection          patchCord55(pl5filter1, 0, pl5envelope1, 0);
AudioConnection          patchCord56(pl6filter1, 0, pl6envelope1, 0);
AudioConnection          patchCord57(filter1, 0, envelope2, 0);
AudioConnection          patchCord58(pl3envelope2, 0, pl3filter1, 1);
AudioConnection          patchCord59(pl7filter1, 0, pl7wavefolder1, 0);
AudioConnection          patchCord60(pl7filter2, 0, pl7envelope1, 0);
AudioConnection          patchCord61(pl7dc1, 0, pl7wavefolder1, 1);
AudioConnection          patchCord62(envelope2, bitcrusher1);
AudioConnection          patchCord63(pl7biquad1, pl7envelope4);
AudioConnection          patchCord64(pl7waveformMod2, pl7envelope3);
AudioConnection          patchCord65(drummixer4, pl2amp);
AudioConnection          patchCord66(pl8waveform1, 0, pl8filter1, 0);
AudioConnection          patchCord67(pl3filter1, 0, pl3envelope1, 0);
AudioConnection          patchCord68(pl8envelope2, 0, pl8filter1, 1);
AudioConnection          patchCord69(pl4drummixer4, pl4amp);
AudioConnection          patchCord70(pl5envelope1, pl5amp);
AudioConnection          patchCord71(pl6envelope1, pl6amp);
AudioConnection          patchCord72(bitcrusher1, 0, pl1mixer3, 0);
AudioConnection          patchCord73(pl9bpinput, 0, pl9bpfilter, 1);
AudioConnection          patchCord74(pl9string1, 0, pl9bpfilter, 0);
AudioConnection          patchCord75(pl7envelope1, 0, pl7mixer1, 1);
AudioConnection          patchCord76(pl7envelope4, 0, pl7mixer1, 3);
AudioConnection          patchCord77(pl7envelope3, 0, pl7mixer1, 2);
AudioConnection          patchCord78(pl7wavefolder1, 0, pl7mixer1, 0);
AudioConnection          patchCord79(pl3envelope1, pl3amp);
AudioConnection          patchCord80(pl8filter1, pl8envelope1);
AudioConnection          patchCord81(pl1delay1, 0, pl1filter3, 0);
AudioConnection          patchCord82(pl1mixer3, pl1delay1);
AudioConnection          patchCord83(pl1mixer3, pl1amp);
AudioConnection          patchCord84(pl1filter3, 2, pl1mixer3, 1);
AudioConnection          patchCord85(pl9bpfilter, 1, pl9wavefolder1, 0);
AudioConnection          patchCord86(pl9dc1, 0, pl9wavefolder1, 1);
AudioConnection          patchCord87(pl4amp, 0, FX1mixer1, 3);
AudioConnection          patchCord88(pl4amp, 0, FX2mixer1, 3);
AudioConnection          patchCord89(pl4amp, 0, FX3mixer1, 3);
AudioConnection          patchCord90(pl4amp, 0, mixer5, 3);
AudioConnection          patchCord91(pl6amp, 0, mixer6, 1);
AudioConnection          patchCord92(pl6amp, 0, FX1mixer2, 1);
AudioConnection          patchCord93(pl6amp, 0, FX2mixer2, 1);
AudioConnection          patchCord94(pl6amp, 0, FX3mixer2, 1);
AudioConnection          patchCord95(pl2amp, 0, mixer5, 1);
AudioConnection          patchCord96(pl2amp, 0, FX1mixer1, 1);
AudioConnection          patchCord97(pl2amp, 0, FX2mixer1, 1);
AudioConnection          patchCord98(pl2amp, 0, FX3mixer1, 1);
AudioConnection          patchCord99(pl5amp, 0, mixer6, 0);
AudioConnection          patchCord100(pl5amp, 0, FX1mixer2, 0);
AudioConnection          patchCord101(pl5amp, 0, FX2mixer2, 0);
AudioConnection          patchCord102(pl5amp, 0, FX3mixer2, 0);
AudioConnection          patchCord103(pl3amp, 0, mixer5, 2);
AudioConnection          patchCord104(pl3amp, 0, FX1mixer1, 2);
AudioConnection          patchCord105(pl3amp, 0, FX2mixer1, 2);
AudioConnection          patchCord106(pl3amp, 0, FX3mixer1, 2);
AudioConnection          patchCord107(pl7mixer2, 0, pl7mixer3, 1);
AudioConnection          patchCord108(pl7mixer1, 0, pl7mixer3, 0);
AudioConnection          patchCord109(pl8envelope1, pl8amp);
AudioConnection          patchCord110(pl9wavefolder1, pl9amp);
AudioConnection          patchCord111(pl1amp, 0, mixer5, 0);
AudioConnection          patchCord112(pl1amp, 0, FX1mixer1, 0);
AudioConnection          patchCord113(pl1amp, 0, FX2mixer1, 0);
AudioConnection          patchCord114(pl1amp, 0, FX3mixer1, 0);
AudioConnection          patchCord115(pl7mixer3, pl7amp);
AudioConnection          patchCord116(pl7amp, 0, mixer6, 2);
AudioConnection          patchCord117(pl7amp, 0, FX1mixer2, 2);
AudioConnection          patchCord118(pl7amp, 0, FX2mixer2, 2);
AudioConnection          patchCord119(pl7amp, 0, FX3mixer2, 2);
AudioConnection          patchCord120(pl8amp, 0, mixer6, 3);
AudioConnection          patchCord121(pl8amp, 0, FX1mixer2, 3);
AudioConnection          patchCord122(pl8amp, 0, FX2mixer2, 3);
AudioConnection          patchCord123(pl8amp, 0, FX3mixer2, 3);
AudioConnection          patchCord124(pl9amp, 0, mixer10, 0);
AudioConnection          patchCord125(pl9amp, 0, FX1mixer4, 0);
AudioConnection          patchCord126(pl9amp, 0, FX2mixer4, 0);
AudioConnection          patchCord127(pl9amp, 0, FX3mixer4, 0);
AudioConnection          patchCord128(mixer6, 0, mixer8, 1);
AudioConnection          patchCord129(FX2mixer1, 0, FX2mixer3, 0);
AudioConnection          patchCord130(mixer5, 0, mixer8, 0);
AudioConnection          patchCord131(FX3mixer2, 0, FX3mixer3, 1);
AudioConnection          patchCord132(FX1mixer1, 0, FX1mixer3, 0);
AudioConnection          patchCord133(FX2mixer2, 0, FX2mixer3, 1);
AudioConnection          patchCord134(FX1mixer2, 0, FX1mixer3, 1);
AudioConnection          patchCord135(FX3mixer1, 0, FX3mixer3, 0);
AudioConnection          patchCord136(FX2mixer4, 0, FX2mixer3, 2);
AudioConnection          patchCord137(FX3mixer4, 0, FX3mixer3, 2);
AudioConnection          patchCord138(FX1mixer4, 0, FX1mixer3, 2);
AudioConnection          patchCord139(mixer10, 0, mixer8, 2);
AudioConnection          patchCord140(mixer8, 0, mixer9, 0);
AudioConnection          patchCord141(FX2mixer3, bitcrusher2);
AudioConnection          patchCord142(FX1mixer3, reverb1);
AudioConnection          patchCord143(FX3mixer3, 0, dlmixer1, 0);
AudioConnection          patchCord144(reverb1, 0, mixer9, 1);
AudioConnection          patchCord145(bitcrusher2, 0, mixer9, 2);
AudioConnection          patchCord146(dlfilter1, 2, dlmixer1, 1);
AudioConnection          patchCord147(dldelay1, 0, dlfilter1, 0);
AudioConnection          patchCord148(dlmixer1, dldelay1);
AudioConnection          patchCord149(dlmixer1, 0, mixer9, 3);
AudioConnection          patchCord150(mixer9, 0, pt8211_1, 0);
AudioConnection          patchCord151(mixer9, 0, pt8211_1, 1);
// GUItool: end automatically generated code





void setup() {
  Serial.begin(115200);  // set MIDI baud

  //initialize the TFT- and Touchscreen
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  ts.begin();
  ts.setRotation(1);
  //tft.setFrameBuffer(fb1);
  //tft.useFrameBuffer(true);
  while (!Serial && (millis() <= 1000))
    ;
  tft.fillScreen(ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 3);
  Serial.println("Initializing Touchscreen...");
  tft.println("Initializing Touchscreen...");
  //tft.updateScreen();
  delay(100);

  AudioMemory(200);
  Serial.println("Initializing AudioMemory = 200");
  tft.println("Initializing AudioMemory = 200");
  //tft.updateScreen();
  delay(100);



  //initialize SD Card
  Serial.print("Initializing SD card...");
  tft.println("Initializing SD card...");
  //tft.updateScreen();
  delay(100);
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    tft.println("initialization failed!");
    //tft.updateScreen();
    return;
  }
  Serial.println("initialization done.");
  tft.println("initialization done.");
  //tft.updateScreen();
  delay(100);

  // start sequencer and set callbacks

  Serial.println("Initializing Sequencer");
  tft.println("Initializing Sequencer");
  //tft.updateScreen();
  delay(100);

  /// set the default channel of each track
  track[0].MIDIchannel = 10;
  track[1].MIDIchannel = 2;
  track[2].MIDIchannel = 3;
  track[3].MIDIchannel = 4;
  track[4].MIDIchannel = 5;
  track[5].MIDIchannel = 6;
  track[6].MIDIchannel = 7;
  track[7].MIDIchannel = 8;
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //load the pluginsettings
  Plugin_1_Settings();
  Plugin_2_Settings();
  Plugin_3_Settings();
  Plugin_4_Settings();
  Plugin_5_Settings();
  Plugin_6_Settings();
  Plugin_7_Settings();
  Plugin_8_Settings();
  Plugin_9_Settings();
  Mixer_Settings();
  FX1reverb_settings();
  FX2Bitcrush_settings();
  clearArrangment();
  Serial.println("Initializing Track- and Pluginsettings");
  tft.println("Initializing Track- and Pluginsettings");
  //tft.updateScreen();
  delay(100);


  //initiate Buttons
  for (byte i = 0; i < NUM_BUTTONS; i++) {
    buttons[i].attach(BUTTON_PINS[i], INPUT_PULLUP);  //setup the bounce instance for the current button
    buttons[i].interval(100);                         // interval in ms
  }

  Serial.println("Initializing Buttons");
  tft.println("Initializing Buttons");
  //tft.updateScreen();
  delay(100);
  //initiate variablePlayback
  playSdPitch1.enableInterpolation(true);
  playSdPitch2.enableInterpolation(true);
  Serial.println("Initializing VariablePlayback");
  tft.println("Initializing VariablePlayback");
  //tft.updateScreen();
  delay(100);
  Serial.println("Complete...");
  tft.println("Complete...");
  //tft.updateScreen();
  delay(400);
  //load the startupScreen
  startUpScreen();
  delay(500);
  for (byte pixelX = 0; pixelX < 16; pixelX++) {
    for (byte pixelY = 0; pixelY < 16; pixelY++) {
      tftRAM[pixelX][pixelY] = tft.readPixel(pixelX, pixelY);
    }
  }
  //tft.updateScreen();
}

elapsedMicros msecs;



void loop() {
  //Serial.println("==== start of loop ====");
  usbMIDI.read();
  sendClock();
  //read Potentiometer1
  Potentiometer1 = 127 - map(analogRead(POTENTIOMETER_1_PIN), 0, 1023, 0, 127);
  Potentiometer2 = 127 - map(analogRead(POTENTIOMETER_2_PIN), 0, 1023, 0, 127);
  //assigning the current clip from the arrangment array for each track
  for (byte instruments = 0; instruments < 8; instruments++) {
    track[instruments].clip_songMode = track[instruments].arrangment1[phrase];
  }
  /*unsigned long currentMillis_2 = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Serial.println(digitalRead(2));
    //Potentiometer1 = 127 - map(analogRead(POTENTIOMETER_1_PIN), 0, 1023, 0, 127);
    //Potentiometer2 = 127 - map(analogRead(POTENTIOMETER_2_PIN), 0, 1023, 0, 127);
  }*/

  for (byte i = 0; i < NUM_BUTTONS; i++) {
    // Update the Bounce instance :
    buttons[i].update();
  }
  // If it fell, flag the need to toggle the LED
  if (buttons[0].fell()) {
    gridTouchX--;
    drawCursor();
  }
  if (buttons[1].fell()) {
    gridTouchX++;
    drawCursor();
  }
  if (buttons[2].fell()) {
    gridTouchY--;
    drawCursor();
  }
  if (buttons[3].fell()) {
    gridTouchY++;
    drawCursor();
    //something_was_pressed = true;
  }
  if (buttons[4].fell()) {
    seq_run = true;
    msecs = 0;
    //seq.start();

    for (byte i = 1; i <= 7; i++) {
      track[i].clip_songMode = track[i].arrangment1[0];
    }
  }
  if (buttons[5].fell()) {
    seq_run = false;
    phrase = -1;
    pixelphrase = -1;
    phrase = 0;
    msecs = 0;
    tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H * 14, STEP_FRAME_W * 16, STEP_FRAME_H, ILI9341_DARKGREY);
  }



  //always show the coordinates
  showCoordinates();

  TS_Point p = ts.getPoint();
  if (ts.touched() && !buttons[6].changed()) {
    gridTouchX = map(p.x, TS_MINX, TS_MAXX, 0, 19);
    gridTouchY = map(p.y, TS_MINY, TS_MAXY, 0, 14);
    trackTouchY = map(p.y, 800, 3200, 0, 7);
  }
  if (ts.touched() || !buttons[6].read()) {
    int start_at = millis();



    if (gridTouchY == 0) {  //Top Line Edits: Tempo, Play, Stop, Record, Scales, Arrangment select

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //Play button
      if (gridTouchX == POSITION_PLAY_BUTTON || gridTouchX == POSITION_PLAY_BUTTON + 1) {
        seq_run = true;
        msecs = 0;
        //seq.start();
        for (byte i = 1; i <= 7; i++) {
          track[i].clip_songMode = track[i].arrangment1[0];
        }
      }

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //Stop button
      if (gridTouchX == POSITION_STOP_BUTTON) {
        seq_run = false;
        phrase = -1;
        pixelphrase = -1;
        phrase = 0;
        msecs = 0;
        tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H * 14, STEP_FRAME_W * 16, STEP_FRAME_H, ILI9341_DARKGREY);
      }

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //arrangmentSelect button ; not used right now
      if (gridTouchX == POSITION_ARR_BUTTON || gridTouchX == POSITION_ARR_BUTTON + 1) {
        arrangmentSelect = map(Potentiometer1, 0, 127, 0, 7);
        tft.fillRect(STEP_FRAME_W * POSITION_ARR_BUTTON + 2, 1, STEP_FRAME_W * 2 - 3, STEP_FRAME_H - 2, ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
        tft.setCursor(STEP_FRAME_W * POSITION_ARR_BUTTON + 3, 4);
        tft.setFont(Arial_8);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.print("Arr:");
        tft.print(arrangmentSelect + 1);
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //TempoSelect button
      if (gridTouchX == POSITION_BPM_BUTTON || gridTouchX == POSITION_BPM_BUTTON + 1) {
        tempo = map(Potentiometer1, 0, 127, 55, 200);
        setTempo(tempo);
        //tempoSelect = map(Potentiometer1, 0, 127, 55, 200);
        //seq.setTempo(tempoSelect);
        tft.fillRect(STEP_FRAME_W * POSITION_BPM_BUTTON + 2, 1, STEP_FRAME_W * 2 - 4, STEP_FRAME_H - 2, ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
        tft.setCursor(STEP_FRAME_W * POSITION_BPM_BUTTON + 2, 3);
        tft.setFont(Arial_10);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.print(tempo);
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //Scale Select
      if (gridTouchX == POSITION_SCALE_BUTTON || gridTouchX == POSITION_SCALE_BUTTON + 1) {
        selectPage = SCALESELECT;
        gridScaleSelector();
        scaleSelector();
        for (byte i = 0; i < scalesQuant; i++) {
          tft.setCursor(STEP_FRAME_W * 2, STEP_FRAME_H * i + STEP_FRAME_H);
          tft.setFont(Arial_8);
          tft.setTextColor(ILI9341_WHITE);
          tft.setTextSize(1);
          tft.print(scaleNames[i]);
        }
      }
    }
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    //add your plugin- bool´s to the selectPage array
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////

    if (gridTouchX == 0) {  //Songmode- and Trackselection
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select Songarranger
      if (gridTouchY == 0) {
        selectPage = 10;
        gridSongMode(songpageNumber);
      }
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select Drumchannel
      if (trackTouchY == 0) {
        selectPage = DRUMTRACK;
        desired_instrument = 0;
        desired_track = 0;
        drumStepSequencer_Static();
      }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select channel2-8
      for (byte tracks = 1; tracks < 8; tracks++) {
        if (trackTouchY == tracks) {
          desired_instrument = tracks;
          desired_track = tracks;
          selectPage = tracks;
          gridStepSequencer(tracks);
        }
      }
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select Mixer
      if (gridTouchY == 13) {
        selectPage = MIXER_PAGE_1;
        mixerPage1_Static(0);
      }
    }
  }
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
    Plugin3_Page1_Dynamic(desired_instrument);
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
  //if (something_was_pressed) {
  //Serial.println("==== end of loop ====");
  //delay(2000);
  //}
  //Serial.printf("processing touch took %i millis!", millis () - start_at);
}



void drawCursor() {

  for (byte pixel = 0; pixel < 16; pixel++) {
    tft.drawPixel(pixel + (STEP_FRAME_W * last_button_X), (STEP_FRAME_H * last_button_Y) + 1, tftRAM[0][pixel]);
    tft.drawPixel(pixel + (STEP_FRAME_W * last_button_X), (STEP_FRAME_H * last_button_Y) + 15, tftRAM[1][pixel]);
    tft.drawPixel((STEP_FRAME_W * last_button_X) + 1, pixel + (STEP_FRAME_H * last_button_Y), tftRAM[2][pixel]);
    tft.drawPixel((STEP_FRAME_W * last_button_X) + 15, pixel + (STEP_FRAME_H * last_button_Y), tftRAM[3][pixel]);
  }


  for (byte pixel = 0; pixel < 16; pixel++) {
    tftRAM[0][pixel] = tft.readPixel(pixel + (STEP_FRAME_W * gridTouchX), (STEP_FRAME_H * gridTouchY) + 1);
    tftRAM[1][pixel] = tft.readPixel(pixel + (STEP_FRAME_W * gridTouchX), (STEP_FRAME_H * gridTouchY) + 15);
    tftRAM[2][pixel] = tft.readPixel((STEP_FRAME_W * gridTouchX) + 1, pixel + (STEP_FRAME_H * gridTouchY));
    tftRAM[3][pixel] = tft.readPixel((STEP_FRAME_W * gridTouchX) + 15, pixel + (STEP_FRAME_H * gridTouchY));
  }

  tft.drawRect((STEP_FRAME_W * gridTouchX) + 1, (STEP_FRAME_H * gridTouchY) + 1, STEP_FRAME_W - 1, STEP_FRAME_H - 1, ILI9341_WHITE);
  last_button_X = gridTouchX;
  last_button_Y = gridTouchY;
}




void startUpScreen() {  //static Display rendering
  tft.fillScreen(ILI9341_DARKGREY);

  tft.setFont(Arial_9);

  //songmode button
  tft.setTextColor(ILI9341_BLACK);
  tft.fillRect(1, 1, 15, 16, ILI9341_MAGENTA);  //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(4, 3);
  tft.print("S");

  //Drumtrack button
  tft.fillRect(1, STEP_FRAME_H, 15, TRACK_FRAME_H, trackColor[0]);  //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(4, TRACK_FRAME_H);
  tft.print("D");

  //other tracks buttons
  for (byte otherTracks = 2; otherTracks <= 8; otherTracks++) {
    tft.fillRect(1, TRACK_FRAME_H * otherTracks - 8, 15, TRACK_FRAME_H, trackColor[otherTracks - 1]);  //Xmin, Ymin, Xlength, Ylength, color
    tft.setCursor(4, TRACK_FRAME_H * otherTracks - 2);
    tft.print(otherTracks);
  }
  //Mixer button
  tft.fillRect(1, STEP_FRAME_H * 13, 15, TRACK_FRAME_H, ILI9341_LIGHTGREY);  //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(3, STEP_FRAME_H * 13 + 6);
  tft.print("M");

  //scale Select
  tft.drawRect(STEP_FRAME_W * POSITION_SCALE_BUTTON, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);

  //arrangment Select
  tft.drawRect(STEP_FRAME_W * POSITION_ARR_BUTTON, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);

  // record button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_RECORD_BUTTON, 0, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.fillCircle(STEP_FRAME_W * POSITION_RECORD_BUTTON + 7, 7, DOT_RADIUS + 1, ILI9341_RED);

  //Play button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_PLAY_BUTTON, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);                                                                      //PLAY RECT FRAME
  tft.fillTriangle(STEP_FRAME_W * POSITION_PLAY_BUTTON + 12, 3, STEP_FRAME_W * POSITION_PLAY_BUTTON + 12, 13, STEP_FRAME_W * POSITION_PLAY_BUTTON + 22, 8, ILI9341_GREEN);  // x1, y1, x2, y2, x3, y3

  //stop button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_STOP_BUTTON, 0, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.fillRect(STEP_FRAME_W * POSITION_STOP_BUTTON + 3, 3, 10, 10, ILI9341_LIGHTGREY);

  //barcounter & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_BAR_BUTTON, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);

  //tempo button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_BPM_BUTTON, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);

  //save button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_SAVE_BUTTON, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);
  tft.fillRect(STEP_FRAME_W * POSITION_SAVE_BUTTON + 1, 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_ORANGE);
  tft.setTextColor(ILI9341_BLACK);
  tft.setFont(Arial_9);
  tft.setCursor(STEP_FRAME_W * POSITION_SAVE_BUTTON + 2, 3);
  tft.print("SAV");

  //load button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_LOAD_BUTTON, 0, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.fillRect(STEP_FRAME_W * POSITION_LOAD_BUTTON + 1, 1, STEP_FRAME_W - 2, STEP_FRAME_H - 2, ILI9341_GREENYELLOW);
  tft.setTextColor(ILI9341_BLACK);
  tft.setFont(Arial_9);
  tft.setCursor(STEP_FRAME_W * POSITION_LOAD_BUTTON + 4, 3);
  tft.print("L");
}
void showCoordinates() {
  if (millis() % 100 == 0) {
    tft.fillRect(20, 0, 50, 13, ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
    tft.setTextColor(ILI9341_GREEN);
    tft.setFont(Arial_10);
    tft.setCursor(20, 3);
    tft.print("X");
    tft.print(gridTouchX);
    tft.setCursor(45, 3);
    tft.print("Y");
    tft.print(gridTouchY);
  }
}

void gridScaleSelector() {  //static Display rendering
  clearWorkSpace();
  tft.drawRect(STEP_FRAME_W * 2, STEP_FRAME_H, STEP_FRAME_W * 16, STEP_FRAME_H * 12, ILI9341_WHITE);  //Xmin, Ymin, Xlength, Ylength, color
}
void scaleSelector() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    for (byte i = 0; i < scalesQuant; i++) {
      tft.setCursor(STEP_FRAME_W * 2, STEP_FRAME_H * i + STEP_FRAME_H);
      tft.setFont(Arial_8);
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(1);
      tft.print(scaleNames[i]);

      if (gridTouchX > 1 && gridTouchX < 15 && gridTouchY == i + 1) {
        scaleSelected = i;
        tft.fillRect(STEP_FRAME_W * POSITION_SCALE_BUTTON + 1, 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
        tft.setCursor(STEP_FRAME_W * POSITION_SCALE_BUTTON + 2, 4);
        tft.setFont(Arial_8);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.print(scaleNamesShort[scaleSelected]);
      }
    }
  }
}

void drawStepSequencerStatic(int desired_instrument) {
  //draw the Main Grid
  for (byte i = 0; i < 17; i++) {  //vert Lines
    step_Frame_X = i * STEP_FRAME_W;
    tft.drawFastVLine(step_Frame_X + STEP_FRAME_W * 2, STEP_FRAME_H, GRID_LENGTH_VERT, ILI9341_WHITE);  //(x, y-start, length, color)
    if (i % 4 == 0) {
      tft.drawFastVLine((i * STEP_FRAME_W) + 32, STEP_FRAME_H, STEP_FRAME_H * 12, ILI9341_LIGHTGREY);  //(x, y-start, y-length, color)
    }
  }
  for (byte i = 0; i < 13; i++) {  //hor lines
    step_Frame_Y = i * 16;
    tft.drawFastHLine(STEP_FRAME_W * 2, step_Frame_Y + STEP_FRAME_H, GRID_LENGTH_HOR, ILI9341_WHITE);  //(x-start, y, length, color)
  }
  //draw Clipselector
  for (byte ClipNr = 0; ClipNr < 8; ClipNr++) {
    tft.fillRect(STEP_FRAME_W * 2 * ClipNr + STEP_FRAME_W * 2, STEP_FRAME_H * 13, STEP_FRAME_W * 2, STEP_FRAME_H, trackColor[desired_instrument] + ClipNr * 20);
    tft.setCursor(STEP_FRAME_W * 2 * ClipNr + STEP_FRAME_W * 2 + 2, STEP_FRAME_H * 13 + 4);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(1);
    tft.print("Clip ");
    tft.print(ClipNr);
  }
  for (byte i = 0; i < 12; i++) {
    if (scales[scaleSelected][i]) {
      tft.fillRect(STEP_FRAME_W, STEP_FRAME_H * i + STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H, trackColor[desired_instrument]);
    }
  }

  //draw Octavebuttons
  int leftmost = STEP_FRAME_W * OCTAVE_CHANGE_LEFTMOST;
  int rightmost = STEP_FRAME_W * OCTAVE_CHANGE_RIGHTMOST;
  int UP_topmost = STEP_FRAME_H * OCTAVE_CHANGE_UP_TOPMOST;
  int UP_bottommost = STEP_FRAME_H * OCTAVE_CHANGE_UP_BOTTOMMOST;
  int DOWN_topmost = STEP_FRAME_H * OCTAVE_CHANGE_DOWN_TOPMOST;
  int DOWN_bottommost = STEP_FRAME_H * OCTAVE_CHANGE_DOWN_BOTTOMMOST;
  //Octaverect
  tft.drawRect(leftmost + 1, STEP_FRAME_H, STEP_FRAME_W * 2 - 1, STEP_FRAME_H, ILI9341_WHITE);
  tft.setCursor(leftmost + 4, STEP_FRAME_H * 1 + 4);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print("Oct:");
  //Octavenumber
  tft.fillRect(leftmost + 1, STEP_FRAME_H * 2, STEP_FRAME_W * 2, STEP_FRAME_H * 3, ILI9341_DARKGREY);
  tft.fillTriangle(leftmost + 1, UP_bottommost, rightmost, UP_bottommost, leftmost + STEP_FRAME_W, UP_topmost, ILI9341_LIGHTGREY);         //octave arrow up
  tft.fillTriangle(leftmost + 1, DOWN_topmost, rightmost - 2, DOWN_topmost, leftmost + STEP_FRAME_W, DOWN_bottommost, ILI9341_LIGHTGREY);  //x1, y1, x2, y2, x3, y3
  tft.fillRect(leftmost + 1, UP_bottommost, STEP_FRAME_W * 2, STEP_FRAME_H * 1 + 1, ILI9341_DARKGREY);
  tft.setCursor(leftmost + 12, STEP_FRAME_H * OCTAVE_CHANGE_TEXT + 8);
  tft.setFont(Arial_16);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);


  //draw Notenames
  for (byte n = 0; n < 12; n++) {  //hor notes
    tft.setCursor(18, STEP_FRAME_H * n + 18);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(1);
    tft.print(noteNames[n]);
  }
  //MIDIChannel assign button
  tft.setCursor(STEP_FRAME_W * 18 + 2, STEP_FRAME_H * 10 + 2);
  tft.setFont(Arial_8);
  tft.setTextColor(trackColor[desired_instrument]);
  tft.setTextSize(1);
  tft.print("MCh:");
  tft.drawRect(STEP_FRAME_W * 18, STEP_FRAME_H * 11, STEP_FRAME_W * 2, STEP_FRAME_H, trackColor[desired_instrument]);

  //Pluginbutton
  tft.drawRect(STEP_FRAME_W * 18, STEP_FRAME_H * 12, STEP_FRAME_W * 2, STEP_FRAME_H, trackColor[desired_instrument]);
  drawActiveSteps();
  drawMIDIchannel();
}


void drawMIDIchannel() {
  //show midichannel
  tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 11 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * 18 + 8, STEP_FRAME_H * 11 + 3);
  tft.setFont(Arial_10);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print(track[desired_track].MIDIchannel);
  //draw MidiCC
  for (byte plugintext = 0; plugintext <= 16; plugintext++) {
    if (track[desired_instrument].MIDIchannel == plugintext) {
      tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 12 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
      tft.setCursor(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 12 + 5);
      tft.setFont(Arial_8);
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(1);
      tft.print("CC");
    }
  }
  //draw Plugin
  for (byte plugintext = 0; plugintext < MAX_PLUGINS; plugintext++) {
    if (track[desired_track].MIDIchannel == plugintext + 17) {
      tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 12 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
      tft.setCursor(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 12 + 5);
      tft.setFont(Arial_8);
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(1);
      tft.print(pluginName[plugintext]);
    }
  }
}

void clearStepsGrid() {  // clear all Steps from Display
  for (byte T = 0; T < 12; T++) {
    for (byte S = 0; S < 16; S++) {
      tft.fillCircle(S * STEP_FRAME_W + DOT_OFFSET_X, T * STEP_FRAME_H + 24, DOT_RADIUS, ILI9341_DARKGREY);  // circle: x, y, radius, color
    }
  }
}
void clearStepsGridY() {  // clear all Steps in the same column
  for (byte T = 0; T < 12; T++) {

    tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, T * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, ILI9341_DARKGREY);  // circle: x, y, radius, color
  }
}