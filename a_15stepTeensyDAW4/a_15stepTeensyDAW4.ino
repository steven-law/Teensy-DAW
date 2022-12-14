/*Contributing Manual:

Many Thanks to Tristan Rowley, without his immense efforts and time to explain things to me, 
this project would have never reached this amount of functions and still have a more or less readable code. 
For more Informations on him, please take a look at www.github.com/doctea and www.doctea.co.uk!!  
Very Interesting stuff to find and try out!!!

Hello. Here i will show you how to implement new stuff easily.

There are some things left to be made at this point, but feel free to add your features.

toDo´s:
    • add polyphony
    • if in the stepsequencer of a track, i would like to hear the selected clip. when in songmode, only play the arrangment 
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
//#include "ili9341_t3n_font_Arial.h"
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include <SD.h>
#include <TeensyVariablePlayback.h>
#include "flashloader.h"
#include "c_variables.h"
#include "Adafruit_Keypad.h"
#include <ResponsiveAnalogRead.h>
#include <USBHost_t36.h>
#include <Encoder.h>
#include <MIDI.h>

// WAV files converted to code by wav2sketch
//#include "AudioSampleSnare.h"         // http://www.freesound.org/people/KEVOY/sounds/82583/
//#include "AudioSampleTomtom.h"        // http://www.freesound.org/people/zgump/sounds/86334/
//#include "AudioSampleHihat.h"         // http://www.freesound.org/people/mhc/sounds/102790/
//#include "AudioSampleKick.h"          // http://www.freesound.org/people/DWSD/sounds/171104/
//#include "AudioSampleCashregister.h"  // http://www.freesound.org/people/kiddpark/sounds/201159/
//#include "AudioSampleP2.h"
#include "AudioSamplesTest.h"



//Teensy 4.1 PINOUT
//Pinout for screen
#define TIRQ_PIN 15  //alternate Pins: any digital pin
#define CS_PIN 14    //alternate Pins: any digital pin
#define TFT_DC 9     //alternate Pins 9, 10, 20, 21
#define TFT_CS 10    //alternate Pins 9, 15, 20, 21
#define TFT_RST 255  // 255 = unused, connect to 3.3V
#define TFT_MOSI 11  //shareable
#define TFT_SCLK 13  //shareable
#define TFT_MISO 12  //shareable

//button Pins
const byte ROWS = 4;  //four rows
const byte COLS = 4;  //four columns
//define the cymbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  { '0', '1', '2', '3' },
  { '4', '5', '6', '7' },
  { '8', '9', 'A', 'B' },
  { 'C', 'D', 'E', 'F' }
};
byte rowPins[ROWS] = { 37, 36, 35, 34 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 41, 38, 39, 40 };  //connect to the column pinouts of the keypad

Adafruit_Keypad kpd = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
//Encoder Pins
Encoder Enc1(31, 32);
Encoder Enc2(27, 28);
Encoder Enc3(24, 25);
Encoder Enc4(2, 3);

//Potentiometer Pins
//#define POTENTIOMETER_1_PIN 255
#define POTENTIOMETER_2_PIN 255
#define POTENTIOMETER_3_PIN 255
#define POTENTIOMETER_4_PIN 255


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



//initiate the modules

File myFile;                                                                         //initiate SDCard Reader
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);  //initiate TFT-Srceen
//ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);  //initiate TFT-Srceen
XPT2046_Touchscreen ts(CS_PIN);  //initiate Touchscreen
USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
USBHub hub3(myusb);
USBHub hub4(myusb);
MIDIDevice midi01(myusb);
MIDIDevice midi02(myusb);
MIDIDevice midi03(myusb);
MIDIDevice midi04(myusb);
MIDIDevice midi05(myusb);
MIDIDevice midi06(myusb);
MIDIDevice midi07(myusb);
MIDIDevice midi08(myusb);
MIDIDevice midi09(myusb);
MIDIDevice midi10(myusb);

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);





//please use this Audio GUI from Newdigate
//https://newdigate.github.io/teensy-eurorack-audio-gui/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc pl5dc1;                  //xy=61.5,1260
AudioPlayMemory playMem9;                     //xy=62.5,1044
AudioSynthWaveformDc pl6dc1;                  //xy=63.5,1364
AudioSynthNoiseWhite pl7noise1;               //xy=64.5,1542
AudioPlayMemory playMem10;                    //xy=67.5,1075
AudioPlayMemory playMem7;                     //xy=72.5,974
AudioPlayMemory playMem8;                     //xy=72.5,1011
AudioSynthWaveform waveform1;                 //xy=78.5,45
AudioSynthWaveform waveform3;                 //xy=78.5,145
AudioSynthWaveform waveform2;                 //xy=82.5,98
AudioPlayMemory playMem5;                     //xy=82.5,898
AudioPlayMemory playMem6;                     //xy=83.5,936
AudioSynthWaveformDc pl1dc1;                  //xy=87.5,239
AudioPlaySdWav playSdWav12;                   //xy=87.5,709
AudioPlayMemory playMem1;                     //xy=87.5,758
AudioPlaySdWav playSdWav7;                    //xy=89.5,528
AudioPlayMemory playMem2;                     //xy=88.5,794
AudioPlaySdWav playSdWav9;                    //xy=89.5,600
AudioPlaySdWav playSdWav3;                    //xy=90.5,373
AudioPlaySdWav playSdWav10;                   //xy=89.5,634
AudioPlaySdWav playSdWav4;                    //xy=90.5,409
AudioPlaySdWav playSdWav11;                   //xy=89.5,673
AudioSynthWaveform waveform4;                 //xy=91.5,195
AudioPlaySdWav playSdWav8;                    //xy=90.5,565
AudioPlayMemory playMem11;                    //xy=89.5,1114
AudioPlaySdWav playSdWav2;                    //xy=93.5,336
AudioPlaySdWav playSdWav5;                    //xy=93.5,449
AudioPlaySdWav playSdWav6;                    //xy=93.5,489
AudioPlaySdWav playSdWav1;                    //xy=96.5,297
AudioPlayMemory playMem12;                    //xy=94.5,1152
AudioPlayMemory playMem3;                     //xy=97.5,828
AudioPlayMemory playMem4;                     //xy=104.5,864
AudioSynthWaveformSine pl7waveformMod3;       //xy=105.5,1628
AudioSynthNoiseWhite pl7noise2;               //xy=168.5,1685
AudioSynthNoisePink pl7pink1;                 //xy=168.5,1725
AudioPlayArrayResmp playSdPitch1;             //xy=199.5,1206
AudioEffectEnvelope pl5envelope2;             //xy=209.5,1259
AudioPlaySdResmp playSdPitch2;                //xy=209.5,1312
AudioEffectEnvelope pl6envelope2;             //xy=211.5,1363
AudioEffectEnvelope envelope1;                //xy=229.5,236
AudioMixer4 mixer1;                           //xy=241.5,86
AudioSynthSimpleDrum pl7drum1;                //xy=275.5,1464
AudioSynthWaveformModulated pl7waveformMod1;  //xy=282.5,1545
AudioEffectEnvelope pl7envelope2;             //xy=285.5,1626
AudioSynthWaveformDc pl3dc1;                  //xy=292.5,678
AudioMixer4 drummixer1;                       //xy=297.5,321
AudioMixer4 drummixer2;                       //xy=299.5,410
AudioMixer4 drummixer3;                       //xy=308.5,502
AudioMixer4 pl4drummixer1;                    //xy=309.5,775
AudioFilterStateVariable filter1;             //xy=313.5,164
AudioMixer4 pl7mixer4;                        //xy=307.5,1713
AudioMixer4 pl4drummixer2;                    //xy=311.5,864
AudioMixer4 pl4drummixer3;                    //xy=320.5,956
AudioSynthWaveform pl3waveform1;              //xy=329.5,615
AudioSynthWaveformDc pl8dc1;                  //xy=360.5,1866
AudioFilterStateVariable pl5filter1;          //xy=373.5,1225
AudioFilterStateVariable pl6filter1;          //xy=375.5,1329
AudioMixer4 pl1mixer2;                        //xy=426.5,70
AudioEffectEnvelope pl3envelope2;             //xy=435.5,675
AudioFilterStateVariable pl7filter1;          //xy=445.5,1464
AudioFilterStateVariable pl7filter2;          //xy=446.5,1554
AudioSynthWaveformDc pl7dc1;                  //xy=448.5,1508
AudioFilterBiquad pl7biquad1;                 //xy=449.5,1705
AudioSynthWaveform pl9bpinput;                //xy=457.5,2026
AudioSynthWaveformModulated pl7waveformMod2;  //xy=461.5,1629
AudioSynthKarplusStrong pl9string1;           //xy=461.5,1975
AudioMixer4 drummixer4;                       //xy=482.5,431
AudioSynthWaveform pl8waveform1;              //xy=490.5,1815
AudioFilterStateVariable pl3filter1;          //xy=497.5,617
AudioMixer4 pl6mixer1;                        //xy=510.5,1341
AudioEffectEnvelope pl8envelope2;             //xy=515.5,1865
AudioMixer4 pl5mixer1;                        //xy=525.5,1126
AudioEffectEnvelope envelope2;                //xy=538.5,136
AudioMixer4 pl4drummixer4;                    //xy=537.5,784
AudioEffectBitcrusher bitcrusher1;            //xy=574.5,80
AudioEffectEnvelope pl7envelope1;             //xy=599.5,1539
AudioFilterStateVariable pl9bpfilter;         //xy=601.5,1979
AudioSynthWaveformDc pl9dc1;                  //xy=601.5,2027
AudioEffectEnvelope pl5envelope1;             //xy=629.5,1215
AudioAmplifier pl2amp2;                       //xy=641,439
AudioEffectEnvelope pl7envelope4;             //xy=637.5,1703
AudioMixer4 pl3mixer1;                        //xy=642.5,577
AudioEffectEnvelope pl6envelope1;             //xy=642.5,1316
AudioEffectEnvelope pl7envelope3;             //xy=643.5,1640
AudioEffectWaveFolder pl7wavefolder1;         //xy=653.5,1456
AudioFilterLadder pl8filter1;                 //xy=681.5,1828
AudioAmplifier pl4amp2;                       //xy=689,760
AudioEffectEnvelope pl3envelope1;             //xy=719.5,639
AudioEffectDelay pl1delay1;                   //xy=723.5,218
AudioMixer4 pl1mixer3;                        //xy=727.5,35
AudioFilterStateVariable pl1filter3;          //xy=727.5,110
AudioEffectWaveFolder pl9wavefolder1;         //xy=771.5,1984
AudioAmplifier pl2amp;                        //xy=779.5,441
AudioAmplifier pl6amp2;                       //xy=781,1283
AudioAmplifier pl5amp2;                       //xy=792,1152
AudioAmplifier pl4amp;                        //xy=803.5000114440918,772.0000114440918
AudioAmplifier pl3amp2;                       //xy=824,559
AudioFilterStateVariable pl9filter2;          //xy=828.5,2056
AudioMixer4 pl7mixer2;                        //xy=840.5,1731
AudioMixer4 pl7mixer1;                        //xy=842.5,1650
AudioEffectEnvelope pl8envelope1;             //xy=846.5,1837
AudioAmplifier pl1amp2;                       //xy=854,92
AudioAmplifier pl5amp;                        //xy=877.5000114440918,1214.000018119812
AudioAmplifier pl6amp;                        //xy=880.5000114440918,1316.0000190734863
AudioAmplifier pl14amp2;                      //xy=879.2000122070312,2439
AudioAmplifier pl12amp2;                      //xy=883,2279
AudioAmplifier pl11amp2;                      //xy=887.0000152587891,2224.000033378601
AudioAmplifier pl16amp2;                      //xy=892.2000274658203,2573.0000381469727
AudioAmplifier pl13amp2;                      //xy=898.2000122070312,2376
AudioAmplifier pl7amp2;                       //xy=903,1560
AudioAmplifier pl3amp;                        //xy=909.5000114440918,604.0000095367432
AudioAmplifier pl10amp2;                      //xy=907.0000133514404,2158.000030517578
AudioAmplifier pl15amp2;                      //xy=907.2000122070312,2506
AudioAmplifier pl9amp2;                       //xy=960,1952
AudioAmplifier pl8amp2;                       //xy=961,1784
AudioAmplifier pl1amp;                        //xy=971.5,173
AudioMixer4 pl9mixer1;                        //xy=966.5,2046
AudioMixer4 pl7mixer3;                        //xy=992.5,1654
AudioAmplifier pl7amp;                        //xy=1029.5000133514404,1565.0000228881836
AudioAmplifier pl11amp;                       //xy=1034.000015258789,2226.0000324249268
AudioAmplifier pl10amp;                       //xy=1040.000015258789,2149.0000314712524
AudioAmplifier pl12amp;                       //xy=1040,2276
AudioAmplifier pl16amp;                       //xy=1046.199966430664,2577.0000381469727
AudioAmplifier pl15amp;                       //xy=1052.199966430664,2507.0000371932983
AudioAmplifier pl8amp;                        //xy=1056.500015258789,1833.0000267028809
AudioAmplifier pl14amp;                       //xy=1054.199966430664,2427.000036239624
AudioAmplifier pl13amp;                       //xy=1055.199966430664,2372.0000343322754
AudioAmplifier pl9amp;                        //xy=1064.5,1982
AudioMixer4 mixer6;                           //xy=1176.5,1272
AudioMixer4 FX2mixer1;                        //xy=1188.5,694
AudioMixer4 mixer5;                           //xy=1190.5,530
AudioMixer4 FX3mixer2;                        //xy=1187.5,1529
AudioMixer4 FX1mixer1;                        //xy=1191.5,607
AudioMixer4 FX2mixer2;                        //xy=1188.5,1442
AudioMixer4 FX1mixer2;                        //xy=1189.5,1357
AudioMixer4 FX3mixer1;                        //xy=1193.5,781
AudioMixer4 FX2mixer4;                        //xy=1224.5,2159
AudioMixer4 FX1mixer6;                        //xy=1232.199966430664,2470.0000381469727
AudioMixer4 drymixer3;                        //xy=1233.199966430664,2384.0000343322754
AudioMixer4 FX3mixer6;                        //xy=1233.1999702453613,2624.0000400543213
AudioMixer4 FX2mixer6;                        //xy=1234.1999702453613,2545.0000381469727
AudioMixer4 FX3mixer4;                        //xy=1239.5,2231
AudioMixer4 FX1mixer4;                        //xy=1247.5,2075
AudioMixer4 mixer10;                          //xy=1250.5,1990
AudioMixer4 drymixer2;                        //xy=1576.5,697
AudioMixer4 FX2mixer3;                        //xy=1580.5,877
AudioMixer4 FX3mixer3;                        //xy=1582.5000228881836,966.0000152587891
AudioMixer4 FX1mixer3;                        //xy=1586.5,794
AudioMixer4 FX3mixer5;                        //xy=1833.199951171875,975
AudioMixer4 drymixer1;                        //xy=1847,698
AudioMixer4 FX1mixer5;                        //xy=1851.199951171875,804
AudioMixer4 FX2mixer5;                        //xy=1854.199951171875,887
AudioEffectReverb reverb1;                    //xy=2033.5000286102295,766.0000114440918
AudioEffectBitcrusher bitcrusher2;            //xy=2047.5000286102295,834.0000114440918
AudioFilterStateVariable dlfilter1;           //xy=2070.5000286102295,1003.0000114440918
AudioEffectDelay dldelay1;                    //xy=2070.5000286102295,1088.0000114440918
AudioMixer4 dlmixer1;                         //xy=2072.5000286102295,948.0000114440918
AudioInputI2S i2s2;                           //xy=2240.5000286102295,913.0000114440918
AudioMixer4 mixer9;                           //xy=2270.5000286102295,718.0000114440918
AudioAmplifier amp1;                          //xy=2390.5000286102295,830.0000114440918
AudioMixer4 mixer11;                          //xy=2460.5000286102295,690.0000114440918
AudioRecordQueue queue1;                      //xy=2521.5000286102295,866.0000114440918
AudioAnalyzePeak peak1;                       //xy=2523.5000286102295,913.0000114440918
AudioOutputI2S i2s1;                          //xy=2629.5000286102295,692.0000114440918
AudioConnection patchCord1(pl5dc1, pl5envelope2);
AudioConnection patchCord2(playMem9, 0, pl4drummixer3, 0);
AudioConnection patchCord3(pl6dc1, pl6envelope2);
AudioConnection patchCord4(pl7noise1, 0, pl7waveformMod1, 0);
AudioConnection patchCord5(playMem10, 0, pl4drummixer3, 1);
AudioConnection patchCord6(playMem7, 0, pl4drummixer2, 2);
AudioConnection patchCord7(playMem8, 0, pl4drummixer2, 3);
AudioConnection patchCord8(waveform1, 0, mixer1, 0);
AudioConnection patchCord9(waveform3, 0, mixer1, 2);
AudioConnection patchCord10(waveform2, 0, mixer1, 1);
AudioConnection patchCord11(playMem5, 0, pl4drummixer2, 0);
AudioConnection patchCord12(playMem6, 0, pl4drummixer2, 1);
AudioConnection patchCord13(pl1dc1, envelope1);
AudioConnection patchCord14(playSdWav12, 0, drummixer3, 3);
AudioConnection patchCord15(playMem1, 0, pl4drummixer1, 0);
AudioConnection patchCord16(playSdWav7, 0, drummixer2, 2);
AudioConnection patchCord17(playMem2, 0, pl4drummixer1, 1);
AudioConnection patchCord18(playSdWav9, 0, drummixer3, 0);
AudioConnection patchCord19(playSdWav3, 0, drummixer1, 2);
AudioConnection patchCord20(playSdWav10, 0, drummixer3, 1);
AudioConnection patchCord21(playSdWav4, 0, drummixer1, 3);
AudioConnection patchCord22(playSdWav11, 0, drummixer3, 2);
AudioConnection patchCord23(waveform4, 0, mixer1, 3);
AudioConnection patchCord24(playSdWav8, 0, drummixer2, 3);
AudioConnection patchCord25(playMem11, 0, pl4drummixer3, 2);
AudioConnection patchCord26(playSdWav2, 0, drummixer1, 1);
AudioConnection patchCord27(playSdWav5, 0, drummixer2, 0);
AudioConnection patchCord28(playSdWav6, 0, drummixer2, 1);
AudioConnection patchCord29(playSdWav1, 0, drummixer1, 0);
AudioConnection patchCord30(playMem12, 0, pl4drummixer3, 3);
AudioConnection patchCord31(playMem3, 0, pl4drummixer1, 2);
AudioConnection patchCord32(playMem4, 0, pl4drummixer1, 3);
AudioConnection patchCord33(pl7waveformMod3, pl7envelope2);
AudioConnection patchCord34(pl7noise2, 0, pl7mixer4, 0);
AudioConnection patchCord35(pl7pink1, 0, pl7mixer4, 1);
AudioConnection patchCord36(playSdPitch1, 0, pl5filter1, 0);
AudioConnection patchCord37(pl5envelope2, 0, pl5filter1, 1);
AudioConnection patchCord38(playSdPitch2, 0, pl6filter1, 0);
AudioConnection patchCord39(pl6envelope2, 0, pl6filter1, 1);
AudioConnection patchCord40(envelope1, 0, filter1, 1);
AudioConnection patchCord41(mixer1, 0, filter1, 0);
AudioConnection patchCord42(pl7drum1, 0, pl7filter1, 0);
AudioConnection patchCord43(pl7waveformMod1, 0, pl7filter2, 0);
AudioConnection patchCord44(pl7envelope2, 0, pl7waveformMod2, 0);
AudioConnection patchCord45(pl3dc1, pl3envelope2);
AudioConnection patchCord46(drummixer1, 0, drummixer4, 0);
AudioConnection patchCord47(drummixer2, 0, drummixer4, 1);
AudioConnection patchCord48(drummixer3, 0, drummixer4, 2);
AudioConnection patchCord49(pl4drummixer1, 0, pl4drummixer4, 0);
AudioConnection patchCord50(filter1, 0, pl1mixer2, 0);
AudioConnection patchCord51(filter1, 1, pl1mixer2, 1);
AudioConnection patchCord52(filter1, 2, pl1mixer2, 2);
AudioConnection patchCord53(pl7mixer4, pl7biquad1);
AudioConnection patchCord54(pl4drummixer2, 0, pl4drummixer4, 1);
AudioConnection patchCord55(pl4drummixer3, 0, pl4drummixer4, 2);
AudioConnection patchCord56(pl3waveform1, 0, pl3filter1, 0);
AudioConnection patchCord57(pl8dc1, pl8envelope2);
AudioConnection patchCord58(pl5filter1, 0, pl5mixer1, 0);
AudioConnection patchCord59(pl5filter1, 1, pl5mixer1, 1);
AudioConnection patchCord60(pl5filter1, 2, pl5mixer1, 2);
AudioConnection patchCord61(pl6filter1, 0, pl6mixer1, 0);
AudioConnection patchCord62(pl6filter1, 1, pl6mixer1, 1);
AudioConnection patchCord63(pl6filter1, 2, pl6mixer1, 2);
AudioConnection patchCord64(pl1mixer2, envelope2);
AudioConnection patchCord65(pl3envelope2, 0, pl3filter1, 1);
AudioConnection patchCord66(pl7filter1, 0, pl7wavefolder1, 0);
AudioConnection patchCord67(pl7filter2, 0, pl7envelope1, 0);
AudioConnection patchCord68(pl7dc1, 0, pl7wavefolder1, 1);
AudioConnection patchCord69(pl7biquad1, pl7envelope4);
AudioConnection patchCord70(pl9bpinput, 0, pl9bpfilter, 1);
AudioConnection patchCord71(pl7waveformMod2, pl7envelope3);
AudioConnection patchCord72(pl9string1, 0, pl9bpfilter, 0);
AudioConnection patchCord73(drummixer4, pl2amp2);
AudioConnection patchCord74(pl8waveform1, 0, pl8filter1, 0);
AudioConnection patchCord75(pl3filter1, 0, pl3mixer1, 0);
AudioConnection patchCord76(pl3filter1, 1, pl3mixer1, 1);
AudioConnection patchCord77(pl3filter1, 2, pl3mixer1, 2);
AudioConnection patchCord78(pl6mixer1, pl6envelope1);
AudioConnection patchCord79(pl8envelope2, 0, pl8filter1, 1);
AudioConnection patchCord80(pl5mixer1, pl5envelope1);
AudioConnection patchCord81(envelope2, bitcrusher1);
AudioConnection patchCord82(pl4drummixer4, pl4amp2);
AudioConnection patchCord83(bitcrusher1, 0, pl1mixer3, 0);
AudioConnection patchCord84(pl7envelope1, 0, pl7mixer1, 1);
AudioConnection patchCord85(pl9bpfilter, 1, pl9wavefolder1, 0);
AudioConnection patchCord86(pl9dc1, 0, pl9wavefolder1, 1);
AudioConnection patchCord87(pl5envelope1, pl5amp2);
AudioConnection patchCord88(pl2amp2, pl2amp);
AudioConnection patchCord89(pl7envelope4, 0, pl7mixer1, 3);
AudioConnection patchCord90(pl3mixer1, pl3envelope1);
AudioConnection patchCord91(pl6envelope1, pl6amp2);
AudioConnection patchCord92(pl7envelope3, 0, pl7mixer1, 2);
AudioConnection patchCord93(pl7wavefolder1, 0, pl7mixer1, 0);
AudioConnection patchCord94(pl8filter1, pl8envelope1);
AudioConnection patchCord95(pl4amp2, pl4amp);
AudioConnection patchCord96(pl3envelope1, pl3amp2);
AudioConnection patchCord97(pl1delay1, 0, pl1filter3, 0);
AudioConnection patchCord98(pl1mixer3, pl1delay1);
AudioConnection patchCord99(pl1mixer3, pl1amp2);
AudioConnection patchCord100(pl1filter3, 2, pl1mixer3, 1);
AudioConnection patchCord101(pl9wavefolder1, 0, pl9filter2, 0);
AudioConnection patchCord102(pl2amp, 0, mixer5, 1);
AudioConnection patchCord103(pl2amp, 0, FX1mixer1, 1);
AudioConnection patchCord104(pl2amp, 0, FX2mixer1, 1);
AudioConnection patchCord105(pl2amp, 0, FX3mixer1, 1);
AudioConnection patchCord106(pl6amp2, pl6amp);
AudioConnection patchCord107(pl5amp2, pl5amp);
AudioConnection patchCord108(pl4amp, 0, FX1mixer1, 3);
AudioConnection patchCord109(pl4amp, 0, FX2mixer1, 3);
AudioConnection patchCord110(pl4amp, 0, FX3mixer1, 3);
AudioConnection patchCord111(pl4amp, 0, mixer5, 3);
AudioConnection patchCord112(pl3amp2, pl3amp);
AudioConnection patchCord113(pl9filter2, 0, pl9mixer1, 0);
AudioConnection patchCord114(pl9filter2, 1, pl9mixer1, 1);
AudioConnection patchCord115(pl9filter2, 2, pl9mixer1, 2);
AudioConnection patchCord116(pl7mixer2, 0, pl7mixer3, 1);
AudioConnection patchCord117(pl7mixer1, 0, pl7mixer3, 0);
AudioConnection patchCord118(pl8envelope1, pl8amp2);
AudioConnection patchCord119(pl1amp2, pl1amp);
AudioConnection patchCord120(pl5amp, 0, mixer6, 0);
AudioConnection patchCord121(pl5amp, 0, FX1mixer2, 0);
AudioConnection patchCord122(pl5amp, 0, FX2mixer2, 0);
AudioConnection patchCord123(pl5amp, 0, FX3mixer2, 0);
AudioConnection patchCord124(pl6amp, 0, mixer6, 1);
AudioConnection patchCord125(pl6amp, 0, FX1mixer2, 1);
AudioConnection patchCord126(pl6amp, 0, FX2mixer2, 1);
AudioConnection patchCord127(pl6amp, 0, FX3mixer2, 1);
AudioConnection patchCord128(pl14amp2, pl14amp);
AudioConnection patchCord129(pl12amp2, pl12amp);
AudioConnection patchCord130(pl11amp2, pl11amp);
AudioConnection patchCord131(pl16amp2, pl16amp);
AudioConnection patchCord132(pl13amp2, pl13amp);
AudioConnection patchCord133(pl7amp2, pl7amp);
AudioConnection patchCord134(pl3amp, 0, mixer5, 2);
AudioConnection patchCord135(pl3amp, 0, FX1mixer1, 2);
AudioConnection patchCord136(pl3amp, 0, FX2mixer1, 2);
AudioConnection patchCord137(pl3amp, 0, FX3mixer1, 2);
AudioConnection patchCord138(pl10amp2, pl10amp);
AudioConnection patchCord139(pl15amp2, pl15amp);
AudioConnection patchCord140(pl9amp2, pl9amp);
AudioConnection patchCord141(pl8amp2, pl8amp);
AudioConnection patchCord142(pl1amp, 0, mixer5, 0);
AudioConnection patchCord143(pl1amp, 0, FX1mixer1, 0);
AudioConnection patchCord144(pl1amp, 0, FX2mixer1, 0);
AudioConnection patchCord145(pl1amp, 0, FX3mixer1, 0);
AudioConnection patchCord146(pl9mixer1, pl9amp2);
AudioConnection patchCord147(pl7mixer3, pl7amp2);
AudioConnection patchCord148(pl7amp, 0, mixer6, 2);
AudioConnection patchCord149(pl7amp, 0, FX1mixer2, 2);
AudioConnection patchCord150(pl7amp, 0, FX2mixer2, 2);
AudioConnection patchCord151(pl7amp, 0, FX3mixer2, 2);
AudioConnection patchCord152(pl11amp, 0, mixer10, 2);
AudioConnection patchCord153(pl11amp, 0, FX1mixer4, 2);
AudioConnection patchCord154(pl11amp, 0, FX2mixer4, 2);
AudioConnection patchCord155(pl11amp, 0, FX3mixer4, 2);
AudioConnection patchCord156(pl10amp, 0, mixer10, 1);
AudioConnection patchCord157(pl10amp, 0, FX1mixer4, 1);
AudioConnection patchCord158(pl10amp, 0, FX2mixer4, 1);
AudioConnection patchCord159(pl10amp, 0, FX3mixer4, 1);
AudioConnection patchCord160(pl12amp, 0, mixer10, 3);
AudioConnection patchCord161(pl12amp, 0, FX1mixer4, 3);
AudioConnection patchCord162(pl12amp, 0, FX2mixer4, 3);
AudioConnection patchCord163(pl12amp, 0, FX3mixer4, 3);
AudioConnection patchCord164(pl16amp, 0, FX3mixer6, 3);
AudioConnection patchCord165(pl16amp, 0, FX2mixer6, 3);
AudioConnection patchCord166(pl16amp, 0, FX1mixer6, 3);
AudioConnection patchCord167(pl16amp, 0, drymixer3, 3);
AudioConnection patchCord168(pl15amp, 0, drymixer3, 2);
AudioConnection patchCord169(pl15amp, 0, FX1mixer6, 2);
AudioConnection patchCord170(pl15amp, 0, FX2mixer6, 2);
AudioConnection patchCord171(pl15amp, 0, FX3mixer6, 2);
AudioConnection patchCord172(pl8amp, 0, mixer6, 3);
AudioConnection patchCord173(pl8amp, 0, FX1mixer2, 3);
AudioConnection patchCord174(pl8amp, 0, FX2mixer2, 3);
AudioConnection patchCord175(pl8amp, 0, FX3mixer2, 3);
AudioConnection patchCord176(pl14amp, 0, drymixer3, 1);
AudioConnection patchCord177(pl14amp, 0, FX1mixer6, 1);
AudioConnection patchCord178(pl14amp, 0, FX2mixer6, 1);
AudioConnection patchCord179(pl14amp, 0, FX3mixer6, 1);
AudioConnection patchCord180(pl13amp, 0, drymixer3, 0);
AudioConnection patchCord181(pl13amp, 0, FX1mixer6, 0);
AudioConnection patchCord182(pl13amp, 0, FX2mixer6, 0);
AudioConnection patchCord183(pl13amp, 0, FX3mixer6, 0);
AudioConnection patchCord184(pl9amp, 0, mixer10, 0);
AudioConnection patchCord185(pl9amp, 0, FX1mixer4, 0);
AudioConnection patchCord186(pl9amp, 0, FX2mixer4, 0);
AudioConnection patchCord187(pl9amp, 0, FX3mixer4, 0);
AudioConnection patchCord188(mixer6, 0, drymixer2, 1);
AudioConnection patchCord189(FX2mixer1, 0, FX2mixer3, 0);
AudioConnection patchCord190(mixer5, 0, drymixer2, 0);
AudioConnection patchCord191(FX3mixer2, 0, FX3mixer3, 1);
AudioConnection patchCord192(FX1mixer1, 0, FX1mixer3, 0);
AudioConnection patchCord193(FX2mixer2, 0, FX2mixer3, 1);
AudioConnection patchCord194(FX1mixer2, 0, FX1mixer3, 1);
AudioConnection patchCord195(FX3mixer1, 0, FX3mixer3, 0);
AudioConnection patchCord196(FX2mixer4, 0, FX2mixer3, 2);
AudioConnection patchCord197(FX1mixer6, 0, FX1mixer5, 1);
AudioConnection patchCord198(FX1mixer6, 0, FX2mixer5, 1);
AudioConnection patchCord199(drymixer3, 0, drymixer1, 1);
AudioConnection patchCord200(FX3mixer6, 0, FX3mixer5, 1);
AudioConnection patchCord201(FX3mixer4, 0, FX3mixer3, 2);
AudioConnection patchCord202(FX1mixer4, 0, FX1mixer3, 2);
AudioConnection patchCord203(mixer10, 0, drymixer2, 2);
AudioConnection patchCord204(drymixer2, 0, drymixer1, 0);
AudioConnection patchCord205(FX2mixer3, 0, FX2mixer5, 0);
AudioConnection patchCord206(FX3mixer3, 0, FX3mixer5, 0);
AudioConnection patchCord207(FX1mixer3, 0, FX1mixer5, 0);
AudioConnection patchCord208(FX3mixer5, 0, dlmixer1, 0);
AudioConnection patchCord209(drymixer1, 0, mixer9, 0);
AudioConnection patchCord210(FX1mixer5, reverb1);
AudioConnection patchCord211(FX2mixer5, bitcrusher2);
AudioConnection patchCord212(reverb1, 0, mixer9, 1);
AudioConnection patchCord213(bitcrusher2, 0, mixer9, 2);
AudioConnection patchCord214(dlfilter1, 2, dlmixer1, 1);
AudioConnection patchCord215(dldelay1, 0, dlfilter1, 0);
AudioConnection patchCord216(dlmixer1, dldelay1);
AudioConnection patchCord217(dlmixer1, 0, mixer9, 3);
AudioConnection patchCord218(i2s2, 0, amp1, 0);
AudioConnection patchCord219(mixer9, 0, mixer11, 0);
AudioConnection patchCord220(amp1, 0, mixer11, 1);
AudioConnection patchCord221(amp1, queue1);
AudioConnection patchCord222(amp1, peak1);
AudioConnection patchCord223(mixer11, 0, i2s1, 0);
AudioConnection patchCord224(mixer11, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=2645.5000286102295,809.0000114440918
// GUItool: end automatically generated code






newdigate::audiosample *pl5sample;

void setup() {
  Serial.begin(9600);  // set MIDI baud

  //initialize the TFT- and Touchscreen
  tft.begin();
  tft.setRotation(3);
  ts.begin();
  ts.setRotation(1);
  //tft.setFrameBuffer(fb1);
  //tft.useFrameBuffer(true);
  while (!Serial && (millis() <= 1000))
    ;
  tft.fillScreen(ILI9341_BLACK);  //Xmin, Ymin, Xlength, Ylength, color
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 3);
  Serial.println("Initializing Touchscreen...");
  tft.println("Initializing Touchscreen...");
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



  AudioMemory(200);
  Serial.println("Initializing AudioMemory = 200");
  tft.println("Initializing AudioMemory = 200");

  //tft.updateScreen();
  delay(100);




  // start sequencer and set callbacks

  Serial.println("Initializing Sequencer");
  tft.println("Initializing Sequencer");
  //tft.updateScreen();
  delay(100);


  //start usbhost
  Serial.println("Initializing USB Host");
  tft.println("Initializing USB Host");
  myusb.begin();
  midi01.setHandleNoteOn(myNoteOn);
  midi01.setHandleNoteOff(myNoteOff);
  midi01.setHandleControlChange(myControlChange);
  midi02.setHandleNoteOn(myNoteOn);
  midi02.setHandleNoteOff(myNoteOff);
  midi02.setHandleControlChange(myControlChange);
  midi03.setHandleNoteOn(myNoteOn);
  midi03.setHandleNoteOff(myNoteOff);
  midi03.setHandleControlChange(myControlChange);
  midi04.setHandleNoteOn(myNoteOn);
  midi04.setHandleNoteOff(myNoteOff);
  midi04.setHandleControlChange(myControlChange);
  midi05.setHandleNoteOn(myNoteOn);
  midi05.setHandleNoteOff(myNoteOff);
  midi05.setHandleControlChange(myControlChange);
  midi06.setHandleNoteOn(myNoteOn);
  midi06.setHandleNoteOff(myNoteOff);
  midi06.setHandleControlChange(myControlChange);

  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleControlChange(myControlChange);
  //usbMIDI.setHandleClock(myClock);
  //usbMIDI.setHandleStart(myStart);
  //usbMIDI.setHandleStop(myStop);
  MIDI.begin();
  pinMode(22, OUTPUT);
  //tft.updateScreen();
  delay(100);

  /// set the default channel of each track
  track[0].MIDIchannel = 9;
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
  Plugin_10_Settings();
  Plugin_11_Settings();
  Plugin_12_Settings();
  Plugin_13_Settings();
  Plugin_14_Settings();
  Plugin_15_Settings();
  Plugin_16_Settings();
  Mixer_Settings();
  FX1reverb_settings();
  FX2Bitcrush_settings();
  clearArrangment();
  Serial.println("Initializing Track- and Pluginsettings");
  tft.println("Initializing Track- and Pluginsettings");


  //tft.updateScreen();
  delay(100);




  Serial.println("Initializing Buttons");
  tft.println("Initializing Buttons");
  kpd.begin();
  long positionEnc[4] = { -999, -999, -999, -999 };
  //tft.updateScreen();
  delay(100);


  //initiate variablePlayback
  playSdPitch1.enableInterpolation(true);
  newdigate::flashloader loader;
  pl5sample = loader.loadSample("0.RAW");
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

  for (byte pixelX = 0; pixelX < 16; pixelX++) {
    for (byte pixelY = 0; pixelY < 16; pixelY++) {
      tftRAM[pixelX][pixelY] = tft.readPixel(pixelX, pixelY);
    }
  }
  bmpDraw("StartUpPic.bmp", 0, 0);
  delay(4000);
  tft.fillScreen(ILI9341_DARKGREY);
  startUpScreen();
  delay(500);

  drumStepSequencer_Static();
  //tft.updateScreen();
}

elapsedMillis msecs;
elapsedMicros msecsclock;
long oldEnc[4] = { -999, -999, -999, -999 };

void loop() {
  //Serial.println("==== start of loop ====");
  usbMIDI.read();
  myusb.Task();
  midi01.read();
  midi02.read();
  midi03.read();
  midi04.read();
  midi05.read();
  midi06.read();
  kpd.tick();
  sendClock();
  readMainButtons();
  doMainButtons();
  readEncoders();
  Plugin_View_Dynamic();
  otherCtrlButtons = (!button[8] && !button[9] && !button[10] && !button[11] && !button[12]);
  /* if (digitalRead(5)) {
    tick_16++;
  }*/

  //assigning the current clip/noteoffset/presets/Volume from the arrangment array for each track
  if (seq_run) {
    beatComponents();
  }

  if (msecs % 100 == 0) {
    //Serial.print(LP_octave_bool[0]);
    //Serial.print("-");
    Serial.println(button[8]);
    tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
    tft.fillRect(70, lastPotRow * 4, 10, 3, ILI9341_RED);
    drawCursor();
    showCoordinates();
  }


  TS_Point p = ts.getPoint();
  if (ts.touched()) {
    gridTouchX = map(p.x, TS_MINX, TS_MAXX, 0, 19);
    gridTouchY = map(p.y, TS_MINY, TS_MAXY, 0, 14);
    trackTouchY = map(p.y, 800, 3200, 0, 7);
  }


  if (ts.touched() || enter_button) {
    int start_at = millis();

    if (gridTouchY == 0) {  //Top Line Edits: Tempo, Play, Stop, Record, Scales, Arrangment select

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //Play button
      if (gridTouchX == POSITION_PLAY_BUTTON || gridTouchX == POSITION_PLAY_BUTTON + 1) {
        startSeq();
      }

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //Stop button
      if (gridTouchX == POSITION_STOP_BUTTON) {
        stopSeq();
      }

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //arrangmentSelect button ; not used right now
      if (gridTouchX == POSITION_ARR_BUTTON || gridTouchX == POSITION_ARR_BUTTON + 1) {
        arrangmentSelect = map(Potentiometer[3], 0, 127, 0, 7);
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
        if (abs(map(Potentiometer[0], 0, 127, 55, 200) - tempo) < 10) {
          tempo = map(Potentiometer[0], 0, 127, 55, 200);
          setTempo(tempo);
        }
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
    //tft.updateScreen();
  }

  //if (something_was_pressed) {
  //Serial.println("==== end of loop ====");
  //delay(2000);
  //}
  //Serial.printf("processing touch took %i millis!", millis () - start_at);
}


void readMainButtons() {

  while (kpd.available()) {
    keypadEvent key = kpd.read();
    if (key.bit.EVENT == KEY_JUST_PRESSED) {
      //tft.updateScreen();
      //cursor
      //curser left
      if (otherCtrlButtons && key.bit.KEY == 68) {  //"D" 68 1st button
        button[0] = true;
      }
      //cursor right
      if (otherCtrlButtons && key.bit.KEY == 70) {  //"F"  70 2nd button
        button[1] = true;
      }
      //cursor up
      if (otherCtrlButtons && key.bit.KEY == 57) {  //"9"   57 3rd button
        button[2] = true;
      }
      //cursor down
      if (otherCtrlButtons && key.bit.KEY == 66) {  //"B"   66 4th button
        button[3] = true;
      }
      //last-pot-row
      if (otherCtrlButtons && key.bit.KEY == 55) {  //"B"   66 5th button
        button[4] = true;
      }
      //stopbutton
      if (otherCtrlButtons && key.bit.KEY == 53) {  //"1" 49
        button[5] = true;
      }
      //playbutton
      if (otherCtrlButtons && key.bit.KEY == 51) {  //"3" 51
        button[6] = true;
      }
      //stopbutton
      if (otherCtrlButtons && key.bit.KEY == 49) {  //"1" 49
        button[7] = true;
      }


      // hold for track button
      if (!button[10] && key.bit.KEY == 69) {  //"E"  69
        button[8] = true;
      }
      // hold for plugin button
      if (!button[10] && key.bit.KEY == 67) {  //"C"  67
        button[9] = true;
      }
      //  select Songarranger page 11 & button[10]
      if (key.bit.KEY == 65) {  //"A"  65
        button[10] = true;
      }
      // hold for Mixer button
      if (!button[10] && key.bit.KEY == 56) {  //"4"  52
        button[11] = true;
      }
      // hold for FX button
      if (!button[10] && key.bit.KEY == 52) {  //"8"  56
        button[12] = true;
      }
      //recorder
      if (!button[10] && key.bit.KEY == 54) {  // 14th button
        button[13] = true;
      }
      // hold for cursor via pot
      if (!button[10] && key.bit.KEY == 50) {
        button[14] = true;
      }
      // hold for enter button
      if (!button[10] && key.bit.KEY == 48) {
        enter_button = true;
      }
    }
    // if the buttons whre released
    if (key.bit.EVENT == KEY_JUST_RELEASED) {

      if (key.bit.KEY == 68) {  //"D" 68 1st button
        button[0] = false;
        gridTouchX--;
        drawCursor();
      }
      //cursor right
      if (key.bit.KEY == 70) {  //"F"  70 2nd button
        button[1] = false;
        gridTouchX++;
      drawCursor();
      }
      //cursor up
      if (key.bit.KEY == 57) {  //"9"   57 3rd button
        button[2] = false;
        gridTouchY--;
      drawCursor();
      }
      //cursor down
      if (key.bit.KEY == 66) {  //"B"   66 4th button
        button[3] = false;
        gridTouchY++;
      drawCursor();
      }
      //last-pot-row
      if (key.bit.KEY == 55) {  //"B"   66 5th button
        button[4] = false;
      }
      //stopbutton
      if (key.bit.KEY == 53) {  //"1" 49
        button[5] = false;
      }
      //playbutton
      if (key.bit.KEY == 51) {  //"3" 51
        button[6] = false;
      }
      //stopbutton
      if (key.bit.KEY == 49) {  //"1" 49
        button[7] = false;
      }


      // hold for track button
      if (key.bit.KEY == 69) {  //"E"  69
        button[8] = false;
      }
      // hold for plugin button
      if (key.bit.KEY == 67) {  //"C"  67
        button[9] = false;
      }
      //  select Songarranger page 11 & button[10]
      if (key.bit.KEY == 65) {  //"A"  65
        button[10] = false;
      }
      // hold for Mixer button
      if (key.bit.KEY == 56) {  //"4"  52
        button[11] = false;
      }
      // hold for FX button
      if (key.bit.KEY == 52) {  //"8"  56
        button[12] = false;
      }
      //recorder
      if (key.bit.KEY == 54) {  // 14th button
        button[13] = false;
      }
      // hold for cursor via pot
      if (key.bit.KEY == 50) {
        button[14] = false;
      }
      // hold for enter button
      if (key.bit.KEY == 48) {
        enter_button = false;
      }
    }
  }
}

void doMainButtons() {

  unsigned long currentMillis3 = millis();  //worse input haptic, better bpm drop when longpress (-2bpm)
  if (currentMillis3 - previousMillis3 >= interval) {
    previousMillis3 = currentMillis3;


    //tft.updateScreen();
    //cursor
    //curser left
    if (otherCtrlButtons && button[0]) {  //"D" 68 1st button
      gridTouchX--;
      drawCursor();
    }
    //cursor right
    if (otherCtrlButtons && button[1]) {  //"F"  70 2nd button
      gridTouchX++;
      drawCursor();
    }
    //cursor up
    if (otherCtrlButtons && button[2]) {  //"9"   57 3rd button
      gridTouchY--;
      drawCursor();
      //something_was_pressed = true;
    }
    //cursor down
    if (otherCtrlButtons && button[3]) {  //"B"   66 4th button
      gridTouchY++;
      drawCursor();
      //something_was_pressed = true;
    }
    //last-pot-row
    if (otherCtrlButtons && button[4]) {  //"B"   66 5th button
      lastPotRow++;
      if (lastPotRow == 4) {
        lastPotRow = 0;
      }

      //something_was_pressed = true;
    }
    //recbutton
    if (otherCtrlButtons && button[5]) {  //"5" 53
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
    }
    //playbutton
    if (otherCtrlButtons && button[6]) {  //"3" 51
      startSeq();
    }
    //stopbutton
    if (otherCtrlButtons && button[7]) {  //"1" 49
      stopSeq();
    }
    //select tracks
    if (!button[10] && button[8]) {  //9th button
      if (button[0]) {               //"D"  68  1st button
        selectPage = DRUMTRACK;
        desired_instrument = 0;
        desired_track = 0;
        drumStepSequencer_Static();
      }
      
      //select melodic track 2
      if (button[1]) {  //"F"  70 2nd button
        selectPage = 1;
        desired_instrument = 1;
        desired_track = 1;
        gridStepSequencer(1);
      }
      //select melodic track 3
      if (button[2]) {  //"9"  57 3rd button
        selectPage = 2;
        desired_instrument = 2;
        desired_track = 2;
        gridStepSequencer(2);
      }
      //select melodic track 4
      if (button[3]) {  //"B"  66 4th button
        selectPage = 3;
        desired_instrument = 3;
        desired_track = 3;
        gridStepSequencer(3);
      }
      //select melodic track 5
      if (button[4]) {  //"7"  55 5th button
        selectPage = 4;
        desired_instrument = 4;
        desired_track = 4;
        gridStepSequencer(4);
      }
      //select melodic track 6
      if (button[5]) {  //"5"  53 6th button
        selectPage = 5;
        desired_instrument = 5;
        desired_track = 5;
        gridStepSequencer(5);
      }
      //select melodic track 7
      if (button[6]) {  //"3"  51 7th button
        selectPage = 6;
        desired_instrument = 6;
        desired_track = 6;
        gridStepSequencer(6);
      }
      //select melodic track 8
      if (button[7]) {  //"1"  49 8th button
        selectPage = 7;
        desired_instrument = 7;
        desired_track = 7;
        gridStepSequencer(7);
      }
    }
    //plugin selection
    if (!button[10] && button[9]) {
      if (button[0]) {  //"D"  68  1st button
        desired_track = 0;
        desired_instrument = 0;
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
      if (button[1]) {
        desired_track = 1;
        desired_instrument = 1;
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
      if (button[2]) {
        desired_track = 2;
        desired_instrument = 2;
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
      if (button[3]) {
        desired_track = 3;
        desired_instrument = 3;
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
      if (button[4]) {
        desired_track = 4;
        desired_instrument = 4;
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
      if (button[5]) {
        desired_track = 5;
        desired_instrument = 5;
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
      if (button[6]) {
        desired_track = 6;
        desired_instrument = 6;
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
      if (button[7]) {
        desired_track = 7;
        desired_instrument = 7;
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
    //  select Songarranger page 11 & button[10]
    if (button[10]) {
      selectPage = SONGMODE_PAGE_11;
      gridSongMode(10);
      if (button[0]) {
        selectPage = SONGMODE_PAGE_1;
        gridSongMode(0);
        songModePage(0);
      }
      if (button[1]) {
        selectPage = SONGMODE_PAGE_2;
        gridSongMode(1);
        songModePage(1);
      }
      if (button[2]) {
        selectPage = SONGMODE_PAGE_3;
        gridSongMode(2);
        songModePage(2);
      }
      if (button[3]) {
        selectPage = SONGMODE_PAGE_4;
        gridSongMode(3);
        songModePage(3);
      }
      if (button[4]) {
        selectPage = SONGMODE_PAGE_5;
        gridSongMode(4);
        songModePage(4);
      }
      if (button[5]) {
        selectPage = SONGMODE_PAGE_6;
        gridSongMode(5);
        songModePage(5);
      }
      if (button[6]) {
        selectPage = SONGMODE_PAGE_7;
        gridSongMode(6);
        songModePage(6);
      }
      if (button[7]) {
        selectPage = SONGMODE_PAGE_8;
        gridSongMode(7);
        songModePage(7);
      }
      if (button[8]) {
        selectPage = SONGMODE_PAGE_9;
        gridSongMode(8);
        songModePage(8);
      }
      if (button[9]) {
        selectPage = SONGMODE_PAGE_10;
        gridSongMode(9);
        songModePage(9);
      }
      if (button[11]) {
        selectPage = SONGMODE_PAGE_12;
        gridSongMode(11);
        songModePage(11);
      }
      if (button[12]) {
        selectPage = SONGMODE_PAGE_13;
        gridSongMode(12);
        songModePage(12);
      }
      if (button[13]) {
        selectPage = SONGMODE_PAGE_14;
        gridSongMode(13);
        songModePage(13);
      }
      if (button[14]) {
        selectPage = SONGMODE_PAGE_15;
        gridSongMode(14);
        songModePage(14);
      }
      if (enter_button) {
        selectPage = SONGMODE_PAGE_16;
        gridSongMode(15);
        songModePage(15);
      }
    }
    //  select Mixer
    if (!button[10] && button[11]) {  //"8"  56
      if (button[0]) {                //"D"  68
        selectPage = MIXER_PAGE_1;
        mixerPage1_Static(0);
      }
      //select melodic track 2
      if (button[1]) {  //"F"  70
        selectPage = MIXER_PAGE_2;
        mixerPage2_Static();
      }
      //select melodic track 3
      if (button[2]) {  //"9"  57
        selectPage = MIXER_PAGE_3;
        mixerPage3_Static();
      }
    }
    //FX Selection
    if (!button[10] && button[12]) {
      if (button[0]) {
        selectPage = FX1_PAGE1;
        FX1reverb_static();
      }
      if (button[1]) {
        selectPage = FX2_PAGE1;
        FX2Bitcrush_static();
      }
      if (button[2]) {
        //delay
      }
    }
    //recorder
    if (!button[10] && button[13]) {  // 14th button
      selectPage = RECORDER_PAGE;
      recorder_Page_Static();
    }
  }
}
void readEncoders() {
  encoded[0] = 0;
  encoded[1] = 0;
  encoded[2] = 0;
  encoded[3] = 0;
  long newEnc[4];
  enc_moved[0] = 0;
  enc_moved[1] = 0;
  enc_moved[2] = 0;
  enc_moved[3] = 0;
  newEnc[0] = Enc1.read() / 4;
  newEnc[1] = Enc2.read() / 4;
  newEnc[2] = Enc3.read() / 4;
  newEnc[3] = Enc4.read() / 4;
  if (newEnc[0] > oldEnc[0]) {
    enc_moved[0] = true;
    encoded[0] = 1;
    oldEnc[0] = newEnc[0];
  }
  if (newEnc[0] < oldEnc[0]) {
    enc_moved[0] = true;
    encoded[0] = -1;
    oldEnc[0] = newEnc[0];
  }
  if (newEnc[1] > oldEnc[1]) {
    enc_moved[1] = true;
    encoded[1] = 1;
    oldEnc[1] = newEnc[1];
  }
  if (newEnc[1] < oldEnc[1]) {
    enc_moved[1] = true;
    encoded[1] = -1;
    oldEnc[1] = newEnc[1];
  }
  if (newEnc[2] > oldEnc[2]) {
    enc_moved[2] = true;
    encoded[2] = 1;
    oldEnc[2] = newEnc[2];
  }
  if (newEnc[2] < oldEnc[2]) {
    enc_moved[2] = true;
    encoded[2] = -1;
    oldEnc[2] = newEnc[2];
  }
  if (newEnc[3] > oldEnc[3]) {
    enc_moved[3] = true;
    encoded[3] = 1;
    oldEnc[3] = newEnc[3];
  }
  if (newEnc[3] < oldEnc[3]) {
    enc_moved[3] = true;
    encoded[3] = -1;
    oldEnc[3] = newEnc[3];
  }
}
void startSeq() {
  phrase = start_of_loop;
  seq_run = true;
  msecs = 0;
  for (byte i = 1; i <= 7; i++) {
    track[i].clip_songMode = track[i].arrangment1[start_of_loop];
  }
}
void stopSeq() {
  seq_run = false;
  tick_16 = -1;
  phrase = start_of_loop - 1;
  pixelphrase = -1;
  phrase = 0;
  msecs = 0;
  //if (track[track_number].send_noteOff) {
  //if (ctrack[track_number].sequence[track[track_number].clip_songMode].step[current-1] > VALUE_NOTEOFF) {
  for (int track_number = 1; track_number <= 7; track_number++) {
    if (track[track_number].MIDIchannel < 17) {
      usbMIDI.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[tick_16] + track[track_number].NoteOffset[phrase], VELOCITYOFF, track[track_number].MIDIchannel);
      MIDI.sendNoteOff(ctrack[track_number].sequence[track[track_number].clip_songMode].step[tick_16] + track[track_number].NoteOffset[phrase], VELOCITYOFF, track[track_number].MIDIchannel);
    }
    if (track[track_number].MIDIchannel == 17) {
      envelope1.noteOff();
      envelope2.noteOff();
    }
    if (track[track_number].MIDIchannel == 19) {
      pl3envelope1.noteOff();
      pl3envelope2.noteOff();
    }
    if (track[track_number].MIDIchannel == 21) {
      pl5envelope1.noteOff();
      pl5envelope2.noteOff();
    }
    if (track[track_number].MIDIchannel == 22) {
      pl6envelope1.noteOff();
      pl6envelope2.noteOff();
    }
    if (track[track_number].MIDIchannel == 24) {
      pl8envelope1.noteOff();
      pl8envelope2.noteOff();
    }
    if (track[track_number].MIDIchannel == 25) {
      pl9string1.noteOff(VELOCITYOFF);
    }
  }
  tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H * 14, STEP_FRAME_W * 16, STEP_FRAME_H, ILI9341_DARKGREY);
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
  tft.fillCircle(STEP_FRAME_W * POSITION_RECORD_BUTTON + 7, 7, DOT_RADIUS + 1, ILI9341_LIGHTGREY);

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
    tft.fillRect(STEP_FRAME_W * 2 * ClipNr + STEP_FRAME_W * 2, STEP_FRAME_H * 13, STEP_FRAME_W * 2, STEP_FRAME_H, trackColor[desired_instrument] + (ClipNr * 20));
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

void drawOctaveNumber() {
  //draw the octave number
  tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * OCTAVE_CHANGE_TEXT, STEP_FRAME_W * 2, STEP_FRAME_H * 1 + 1, ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * 18 + 11, STEP_FRAME_H * OCTAVE_CHANGE_TEXT);
  tft.setFont(Arial_16);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print(track[desired_instrument].shown_octaves);
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
void clearStepsGridY(byte X_Axis) {  // clear all Steps in the same column
  for (byte T = 0; T < 12; T++) {

    tft.fillCircle((X_Axis)*STEP_FRAME_W + DOT_OFFSET_X, T * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, ILI9341_DARKGREY);  // circle: x, y, radius, color
  }
}



#define BUFFPIXEL 80


//===========================================================
// Try Draw using writeRect
void bmpDraw(const char *filename, uint8_t x, uint16_t y) {

  File bmpFile;
  int bmpWidth, bmpHeight;              // W+H in pixels
  uint8_t bmpDepth;                     // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;              // Start of image data in file
  uint32_t rowSize;                     // Not always = bmpWidth; may have padding
  uint8_t sdbuffer[3 * BUFFPIXEL];      // pixel buffer (R+G+B per pixel)
  uint16_t buffidx = sizeof(sdbuffer);  // Current position in sdbuffer
  boolean goodBmp = false;              // Set to true on valid header parse
  boolean flip = true;                  // BMP is stored bottom-to-top
  int w, h, row, col;
  uint8_t r, g, b;
  uint32_t pos = 0, startTime = millis();

  uint16_t awColors[320];  // hold colors for one row at a time...

  if ((x >= tft.width()) || (y >= tft.height())) return;

  Serial.println();
  Serial.print(F("Loading image '"));
  Serial.print(filename);
  Serial.println('\'');

  // Open requested file on SD card
  if (!(bmpFile = SD.open(filename))) {
    Serial.print(F("File not found"));
    return;
  }

  // Parse BMP header
  if (read16(bmpFile) == 0x4D42) {  // BMP signature
    Serial.print(F("File size: "));
    Serial.println(read32(bmpFile));
    (void)read32(bmpFile);             // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile);  // Start of image data
    Serial.print(F("Image Offset: "));
    Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print(F("Header size: "));
    Serial.println(read32(bmpFile));
    bmpWidth = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if (read16(bmpFile) == 1) {    // # planes -- must be '1'
      bmpDepth = read16(bmpFile);  // bits per pixel
      Serial.print(F("Bit Depth: "));
      Serial.println(bmpDepth);
      if ((bmpDepth == 24) && (read32(bmpFile) == 0)) {  // 0 = uncompressed

        goodBmp = true;  // Supported BMP format -- proceed!
        Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if (bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if ((x + w - 1) >= tft.width()) w = tft.width() - x;
        if ((y + h - 1) >= tft.height()) h = tft.height() - y;

        for (row = 0; row < h; row++) {  // For each scanline...

          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if (flip)  // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else  // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if (bmpFile.position() != pos) {  // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer);  // Force buffer reload
          }

          for (col = 0; col < w; col++) {  // For each pixel...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) {  // Indeed
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0;  // Set index to beginning
            }

            // Convert pixel from BMP to TFT format, push to display
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            awColors[col] = tft.color565(r, g, b);
          }  // end pixel
          tft.writeRect(0, row, w, 1, awColors);
        }  // end scanline
        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      }  // end goodBmp
    }
  }

  bmpFile.close();
  if (!goodBmp) Serial.println(F("BMP format not recognized."));
}



// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File &f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read();  // LSB
  ((uint8_t *)&result)[1] = f.read();  // MSB
  return result;
}

uint32_t read32(File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read();  // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read();  // MSB
  return result;
}