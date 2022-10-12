/*Contributing Manual:

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
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include <SD.h>
#include <TeensyVariablePlayback.h>
#include "FifteenStep.h"
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
#define TIRQ_PIN 2   //alternate Pins: any digital pin
#define CS_PIN 8     //alternate Pins: any digital pin
#define TFT_DC 15    //alternate Pins 9, 10, 20, 21
#define TFT_CS 10    //alternate Pins 9, 15, 20, 21
#define TFT_RST 255  // 255 = unused, connect to 3.3V
#define TFT_MOSI 11  //shareable
#define TFT_SCLK 13  //shareable
#define TFT_MISO 12  //shareable

//button Pins
#define STARTBUTTON 26
#define STOPBUTTON 24
#define ENTERBUTTON 25
#define LEFTBUTTON 30
#define RIGHTBUTTON 28
#define UPBUTTON 27
#define DOWNBUTTON 29
//Potentiometer Pins
#define POTENTIOMETER_1_PIN 38
*/

//calibrate your Screen
// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 180
#define TS_MINY 260
#define TS_MAXX 3730
#define TS_MAXY 3600

//touchscreen response; to be changed
const long interval = 150;

//pinout for SD CARD
const int chipSelect = BUILTIN_SDCARD;

//initial drumnotes
byte drumnote[12]{ 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47 };

//noteOn velocity for all tracks
#define VELOCITY 96

// set initial tempo
int tempo = 120;

//individual trackcolors
int trackColor[9]{ 6150246, 8256638, 1095334, 12643941, 2583100, 9365295, 12943157, 5678954, ILI9341_WHITE };
//end of calibration and custumizing

//initiate bounce
Bounce* buttons = new Bounce[NUM_BUTTONS];

//initiate the modules
FifteenStep seq = FifteenStep(SEQUENCER_MEMORY);                                     //initiate Sequencer
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
AudioSynthWaveformDc     pl5dc1;         //xy=95,1290
AudioPlayMemory          playMem9;       //xy=96,1074
AudioSynthWaveformDc     pl6dc1;         //xy=97,1394
AudioSynthNoiseWhite     pl7noise1;      //xy=98,1572
AudioPlayMemory          playMem10;      //xy=101,1105
AudioPlayMemory          playMem7;       //xy=106,1004
AudioPlayMemory          playMem8;       //xy=106,1041
AudioSynthWaveform       waveform3;      //xy=112,175
AudioSynthWaveform       waveform1;      //xy=115,79
AudioSynthWaveform       waveform2;      //xy=116,128
AudioPlayMemory          playMem5;       //xy=116,928
AudioPlayMemory          playMem6;       //xy=117,966
AudioSynthWaveformDc     pl1dc1;            //xy=121,269
AudioPlaySdWav           playSdWav12;    //xy=121,739
AudioPlayMemory          playMem1;       //xy=121,788
AudioPlaySdWav           playSdWav7;     //xy=123,558
AudioPlayMemory          playMem2;       //xy=122,824
AudioPlaySdWav           playSdWav9;     //xy=123,630
AudioPlaySdWav           playSdWav3;     //xy=124,403
AudioPlaySdWav           playSdWav10;    //xy=123,664
AudioPlaySdWav           playSdWav4;     //xy=124,439
AudioPlaySdWav           playSdWav11;    //xy=123,703
AudioSynthWaveform       waveform4;      //xy=125,225
AudioPlaySdWav           playSdWav8;     //xy=124,595
AudioPlayMemory          playMem11;      //xy=123,1144
AudioPlaySdWav           playSdWav2;     //xy=127,366
AudioPlaySdWav           playSdWav5;     //xy=127,479
AudioPlaySdWav           playSdWav6;     //xy=127,519
AudioPlaySdWav           playSdWav1;     //xy=130,327
AudioPlayMemory          playMem12;      //xy=128,1182
AudioPlayMemory          playMem3;       //xy=131,858
AudioPlayMemory          playMem4;       //xy=138,894
AudioSynthWaveformSine   pl7waveformMod3; //xy=151,1663
AudioSynthNoiseWhite     pl7noise2;      //xy=202,1715
AudioSynthNoisePink      pl7pink1;       //xy=202,1755
AudioPlaySdResmp         playSdPitch1;   //xy=230,1235
AudioEffectEnvelope      pl5envelope2;   //xy=243,1289
AudioPlaySdResmp         playSdPitch2;   //xy=243.75000762939453,1342.5000400543213
AudioEffectEnvelope      pl6envelope2;   //xy=245,1393
AudioEffectEnvelope      envelope1;      //xy=263,266
AudioMixer4              mixer1;         //xy=275,116
AudioSynthWaveformDc     pl3dc1;         //xy=311,655
AudioSynthSimpleDrum     pl7drum1;       //xy=309,1494
AudioSynthWaveformModulated pl7waveformMod1; //xy=316,1575
AudioEffectEnvelope      pl7envelope2;   //xy=325,1663
AudioMixer4              drummixer1;     //xy=331,351
AudioMixer4              drummixer2;     //xy=333,440
AudioMixer4              drummixer3;     //xy=342,532
AudioMixer4              pl4drummixer1;  //xy=343,805
AudioMixer4              pl7mixer4;      //xy=341,1743
AudioMixer4              pl4drummixer2;  //xy=345,894
AudioSynthWaveform       pl3waveform1;   //xy=348,592
AudioMixer4              pl4drummixer3;  //xy=354,986
AudioFilterStateVariable pl5filter1;     //xy=407,1255
AudioFilterStateVariable pl6filter1;     //xy=409,1359
AudioFilterStateVariable filter1;        //xy=428,112
AudioEffectEnvelope      pl3envelope2;   //xy=454,652
AudioFilterStateVariable pl7filter1;     //xy=479,1494
AudioFilterStateVariable pl7filter2;     //xy=480,1584
AudioSynthWaveformDc     pl7dc1;         //xy=482,1538
AudioEffectEnvelope      envelope2;      //xy=488,161
AudioFilterBiquad        pl7biquad1;     //xy=483,1735
AudioSynthWaveformModulated waveformMod2;   //xy=497,1670
AudioMixer4              drummixer4;     //xy=516,461
AudioFilterStateVariable pl3filter1;     //xy=535,601
AudioMixer4              pl4drummixer4;  //xy=571,814
AudioEffectEnvelope      pl5envelope1;   //xy=572,1243
AudioEffectEnvelope      pl6envelope1;   //xy=574,1346
AudioEffectBitcrusher    pl1bitcrusher1;    //xy=608,110
AudioEffectEnvelope      pl7envelope1;   //xy=633,1569
AudioEffectEnvelope      pl7envelope4;   //xy=671,1733
AudioEffectEnvelope      pl7envelope3;   //xy=677,1670
AudioEffectWaveFolder    pl7wavefolder1; //xy=687,1486
AudioEffectEnvelope      pl3envelope1;   //xy=692,589
AudioEffectDelay         pl1delay1;         //xy=757,248
AudioMixer4              pl1mixer3;         //xy=761,65
AudioFilterStateVariable pl1filter3;        //xy=761,140
AudioAmplifier           pl4amp;           //xy=785.5555458068848,803.3333053588867
AudioAmplifier           pl6amp;           //xy=805.5555686950684,1346.666666984558
AudioAmplifier           pl2amp;           //xy=813.3334121704102,471.1111183166504
AudioAmplifier           pl5amp;           //xy=812.222225189209,1247.777777671814
AudioAmplifier           pl3amp;           //xy=848.8888854980469,584.4444561004639
AudioMixer4              pl7mixer2;      //xy=874,1761
AudioMixer4              pl7mixer1;      //xy=876,1680
AudioAmplifier           pl1amp;           //xy=1005.5557022094727,203.33338356018066
AudioMixer4              pl7mixer3;      //xy=1026,1684
AudioAmplifier           pl7amp;           //xy=1031.111111111111,1598.888888888889
AudioMixer4              mixer6;         //xy=1210.5555515289307,1302.888957977295
AudioMixer4              FX2mixer1; //xy=1222.2220764160156,724.4445400238037
AudioMixer4              mixer5;         //xy=1224.889030456543,560.3333120346069
AudioMixer4              FX3mixer2; //xy=1221.1108474731445,1559.9999542236328
AudioMixer4              FX1mixer1;         //xy=1225.5555992126465,637.777868270874
AudioMixer4              FX2mixer2; //xy=1222.2221145629883,1472.2223320007324
AudioMixer4              FX1mixer2;         //xy=1223.3332786560059,1387.7779483795166
AudioMixer4              FX3mixer1; //xy=1227.7776184082031,811.1111660003662
AudioMixer4              mixer8;         //xy=1610.1111755371094,727.3333377838135
AudioMixer4              FX2mixer3; //xy=1614.444450378418,907.7778148651123
AudioMixer4              FX1mixer3;         //xy=1620.000144958496,824.4444103240967
AudioMixer4              FX3mixer3; //xy=1622.2221641540527,997.7777080535889
AudioEffectReverb        reverb1;        //xy=1784.4446144104004,796.6666393280029
AudioEffectBitcrusher    bitcrusher2;    //xy=1798.8887786865234,864.4444541931152
AudioEffectDelay         dldelay1; //xy=1821.111141204834,1118.8887424468994
AudioFilterStateVariable dlfilter1; //xy=1821.7778205871582,1033.110975265503
AudioMixer4              dlmixer1; //xy=1823.9999961853027,978.1110210418701
AudioMixer4              mixer9;         //xy=2021.1110954284668,748.8889083862305
AudioOutputPT8211        pt8211_1;       //xy=2238.889186859131,756.111083984375
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
AudioConnection          patchCord42(pl3dc1, pl3envelope2);
AudioConnection          patchCord43(pl7drum1, 0, pl7filter1, 0);
AudioConnection          patchCord44(pl7waveformMod1, 0, pl7filter2, 0);
AudioConnection          patchCord45(pl7envelope2, 0, waveformMod2, 0);
AudioConnection          patchCord46(drummixer1, 0, drummixer4, 0);
AudioConnection          patchCord47(drummixer2, 0, drummixer4, 1);
AudioConnection          patchCord48(drummixer3, 0, drummixer4, 2);
AudioConnection          patchCord49(pl4drummixer1, 0, pl4drummixer4, 0);
AudioConnection          patchCord50(pl7mixer4, pl7biquad1);
AudioConnection          patchCord51(pl4drummixer2, 0, pl4drummixer4, 1);
AudioConnection          patchCord52(pl3waveform1, 0, pl3filter1, 0);
AudioConnection          patchCord53(pl4drummixer3, 0, pl4drummixer4, 2);
AudioConnection          patchCord54(pl5filter1, 0, pl5envelope1, 0);
AudioConnection          patchCord55(pl6filter1, 0, pl6envelope1, 0);
AudioConnection          patchCord56(filter1, 0, envelope2, 0);
AudioConnection          patchCord57(pl3envelope2, 0, pl3filter1, 1);
AudioConnection          patchCord58(pl7filter1, 0, pl7wavefolder1, 0);
AudioConnection          patchCord59(pl7filter2, 0, pl7envelope1, 0);
AudioConnection          patchCord60(pl7dc1, 0, pl7wavefolder1, 1);
AudioConnection          patchCord61(envelope2, pl1bitcrusher1);
AudioConnection          patchCord62(pl7biquad1, pl7envelope4);
AudioConnection          patchCord63(waveformMod2, pl7envelope3);
AudioConnection          patchCord64(drummixer4, pl2amp);
AudioConnection          patchCord65(pl3filter1, 0, pl3envelope1, 0);
AudioConnection          patchCord66(pl4drummixer4, pl4amp);
AudioConnection          patchCord67(pl5envelope1, pl5amp);
AudioConnection          patchCord68(pl6envelope1, pl6amp);
AudioConnection          patchCord69(pl1bitcrusher1, 0, pl1mixer3, 0);
AudioConnection          patchCord70(pl7envelope1, 0, pl7mixer1, 1);
AudioConnection          patchCord71(pl7envelope4, 0, pl7mixer1, 3);
AudioConnection          patchCord72(pl7envelope3, 0, pl7mixer1, 2);
AudioConnection          patchCord73(pl7wavefolder1, 0, pl7mixer1, 0);
AudioConnection          patchCord74(pl3envelope1, pl3amp);
AudioConnection          patchCord75(pl1delay1, 0, pl1filter3, 0);
AudioConnection          patchCord76(pl1mixer3, pl1delay1);
AudioConnection          patchCord77(pl1mixer3, pl1amp);
AudioConnection          patchCord78(pl1filter3, 2, pl1mixer3, 1);
AudioConnection          patchCord79(pl4amp, 0, FX1mixer1, 3);
AudioConnection          patchCord80(pl4amp, 0, FX2mixer1, 3);
AudioConnection          patchCord81(pl4amp, 0, FX3mixer1, 3);
AudioConnection          patchCord82(pl4amp, 0, mixer5, 3);
AudioConnection          patchCord83(pl6amp, 0, mixer6, 1);
AudioConnection          patchCord84(pl6amp, 0, FX1mixer2, 1);
AudioConnection          patchCord85(pl6amp, 0, FX2mixer2, 1);
AudioConnection          patchCord86(pl6amp, 0, FX3mixer2, 1);
AudioConnection          patchCord87(pl2amp, 0, mixer5, 1);
AudioConnection          patchCord88(pl2amp, 0, FX1mixer1, 1);
AudioConnection          patchCord89(pl2amp, 0, FX2mixer1, 1);
AudioConnection          patchCord90(pl2amp, 0, FX3mixer1, 1);
AudioConnection          patchCord91(pl5amp, 0, mixer6, 0);
AudioConnection          patchCord92(pl5amp, 0, FX1mixer2, 0);
AudioConnection          patchCord93(pl5amp, 0, FX2mixer2, 0);
AudioConnection          patchCord94(pl5amp, 0, FX3mixer2, 0);
AudioConnection          patchCord95(pl3amp, 0, mixer5, 2);
AudioConnection          patchCord96(pl3amp, 0, FX1mixer1, 2);
AudioConnection          patchCord97(pl3amp, 0, FX2mixer1, 2);
AudioConnection          patchCord98(pl3amp, 0, FX3mixer1, 2);
AudioConnection          patchCord99(pl7mixer2, 0, pl7mixer3, 1);
AudioConnection          patchCord100(pl7mixer1, 0, pl7mixer3, 0);
AudioConnection          patchCord101(pl1amp, 0, mixer5, 0);
AudioConnection          patchCord102(pl1amp, 0, FX1mixer1, 0);
AudioConnection          patchCord103(pl1amp, 0, FX2mixer1, 0);
AudioConnection          patchCord104(pl1amp, 0, FX3mixer1, 0);
AudioConnection          patchCord105(pl7mixer3, pl7amp);
AudioConnection          patchCord106(pl7amp, 0, mixer6, 2);
AudioConnection          patchCord107(pl7amp, 0, FX1mixer2, 2);
AudioConnection          patchCord108(pl7amp, 0, FX2mixer2, 2);
AudioConnection          patchCord109(pl7amp, 0, FX3mixer2, 2);
AudioConnection          patchCord110(mixer6, 0, mixer8, 1);
AudioConnection          patchCord111(FX2mixer1, 0, FX2mixer3, 0);
AudioConnection          patchCord112(mixer5, 0, mixer8, 0);
AudioConnection          patchCord113(FX3mixer2, 0, FX3mixer3, 1);
AudioConnection          patchCord114(FX1mixer1, 0, FX1mixer3, 0);
AudioConnection          patchCord115(FX2mixer2, 0, FX2mixer3, 1);
AudioConnection          patchCord116(FX1mixer2, 0, FX1mixer3, 1);
AudioConnection          patchCord117(FX3mixer1, 0, FX3mixer3, 0);
AudioConnection          patchCord118(mixer8, 0, mixer9, 0);
AudioConnection          patchCord119(FX2mixer3, bitcrusher2);
AudioConnection          patchCord120(FX1mixer3, reverb1);
AudioConnection          patchCord121(FX3mixer3, 0, dlmixer1, 0);
AudioConnection          patchCord122(reverb1, 0, mixer9, 1);
AudioConnection          patchCord123(bitcrusher2, 0, mixer9, 2);
AudioConnection          patchCord124(dldelay1, 0, dlfilter1, 0);
AudioConnection          patchCord125(dlfilter1, 2, dlmixer1, 1);
AudioConnection          patchCord126(dlmixer1, dldelay1);
AudioConnection          patchCord127(dlmixer1, 0, mixer9, 3);
AudioConnection          patchCord128(mixer9, 0, pt8211_1, 0);
AudioConnection          patchCord129(mixer9, 0, pt8211_1, 1);
// GUItool: end automatically generated code



void setup() {
  Serial.begin(9600);  // set MIDI baud

  //initialize the TFT- and Touchscreen
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  ts.begin();
  ts.setRotation(1);
  while (!Serial && (millis() <= 1000))
    ;
  tft.fillScreen(ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 3);
  Serial.println("Initializing Touchscreen...");
  tft.println("Initializing Touchscreen...");
  delay(100);

  AudioMemory(200);
  Serial.println("Initializing AudioMemory = 200");
  tft.println("Initializing AudioMemory = 200");
  delay(100);



  //initialize SD Card
  Serial.print("Initializing SD card...");
  tft.println("Initializing SD card...");
  delay(100);
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    tft.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  tft.println("initialization done.");
  delay(100);

  // start sequencer and set callbacks
  seq.begin(tempo, steps);
  seq.setStepHandler(step);
  seq.stop();
  Serial.println("Initializing Sequencer");
  tft.println("Initializing Sequencer");
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
  Mixer_Settings();
  FX1reverb_settings();
  FX2Bitcrush_settings();
  Serial.println("Initializing Track- and Pluginsettings");
  tft.println("Initializing Track- and Pluginsettings");
  delay(100);


  //initiate Buttons
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i].attach(BUTTON_PINS[i], INPUT_PULLUP);  //setup the bounce instance for the current button
    buttons[i].interval(100);                         // interval in ms
  }

  Serial.println("Initializing Buttons");
  tft.println("Initializing Buttons");
  delay(100);
  //initiate variablePlayback
  playSdPitch1.enableInterpolation(true);
  playSdPitch2.enableInterpolation(true);
  Serial.println("Initializing VariablePlayback");
  tft.println("Initializing VariablePlayback");
  delay(100);
  Serial.println("Complete...");
  tft.println("Complete...");
  delay(400);
  //load the startupScreen
  startUpScreen();
  delay(500);
  for (int pixelX = 0; pixelX < 16; pixelX++) {
    for (int pixelY = 0; pixelY < 16; pixelY++) {
      tftRAM[pixelX][pixelY] = tft.readPixel(pixelX, pixelY);
    }
  }
}


void loop() {
  //Serial.println("==== start of loop ====");
  usbMIDI.read();
  // this is needed to keep the sequencer
  // running. there are other methods for
  // start, stop, and pausing the steps
  seq.run();


  //read Potentiometer1
  Potentiometer1 = 1023 - analogRead(POTENTIOMETER_1_PIN);
  //unsigned long currentMillis = millis();
  //if (currentMillis - previousMillis >= interval) {
  //  previousMillis = currentMillis;
  //  Serial.println(track[0].solo_state);
  //}

  for (int i = 0; i < NUM_BUTTONS; i++) {
    // Update the Bounce instance :
    buttons[i].update();
  }
  // If it fell, flag the need to toggle the LED
  if (buttons[0].fell()) {
    leftbutton();
  }
  if (buttons[1].fell()) {
    rightbutton();
  }
  if (buttons[2].fell()) {
    upbutton();
  }
  if (buttons[3].fell()) {
    downbutton();
    //something_was_pressed = true;
  }
  if (buttons[4].fell()) {
    seq.start();
    for (int i = 1; i <= 7; i++) {
      track[i].clip_songMode = track[i].arrangment1[0];
    }
  }
  if (buttons[5].fell()) {
    seq.stop();
    seq.panic();
    barClock = 0;
    phrase = -1;
    //clear the songposition pointers
    tft.fillRect(STEP_FRAME_W * 2, STEP_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
    tft.fillRect(STEP_FRAME_W * 2, SONG_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
    tft.fillRect(STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
  }



  //always show the coordinates
  showCoordinates();

  TS_Point p = ts.getPoint();
  if (ts.touched() && !buttons[6].changed()) {
    gridTouchX = map(p.x, 380, 3930, 0, 19);
    gridTouchY = map(p.y, 300, 3800, 0, 14);

    trackTouchY = map(p.y, 700, 3200, 0, 7);
    constrainedtrackTouchY = constrain(trackTouchY, 0, 7);
  }
  if (ts.touched() || !buttons[6].read()) {

    if (gridTouchY == 0) {  //Top Line Edits: Tempo, Play, Stop, Record, Scales, Save, Load, Arrangment select
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savebutton();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadbutton();
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //Play button
      if (gridTouchX == POSITION_PLAY_BUTTON || gridTouchX == POSITION_PLAY_BUTTON + 1) {
        seq.start();
        for (int i = 1; i <= 7; i++) {
          track[i].clip_songMode = track[i].arrangment1[0];
        }
      }

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //Stop button
      if (gridTouchX == POSITION_STOP_BUTTON) {
        seq.stop();
        seq.panic();
        barClock = 0;
        phrase = -1;
        //clear the songposition pointers
        tft.fillRect(STEP_FRAME_W * 2, STEP_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
        tft.fillRect(STEP_FRAME_W * 2, SONG_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
        tft.fillRect(STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
      }

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //arrangmentSelect button ; not used right now
      if (gridTouchX == POSITION_ARR_BUTTON || gridTouchX == POSITION_ARR_BUTTON + 1) {
        arrangmentSelect = map(Potentiometer1, 0, 1023, 0, 7);
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
        tempoSelect = map(Potentiometer1, 0, 1023, 50, 200);
        seq.setTempo(tempoSelect);
        tft.fillRect(STEP_FRAME_W * POSITION_BPM_BUTTON + 2, 1, STEP_FRAME_W * 2 - 4, STEP_FRAME_H - 2, ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
        tft.setCursor(STEP_FRAME_W * POSITION_BPM_BUTTON + 2, 3);
        tft.setFont(Arial_10);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.print(tempoSelect);
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //Scale Select
      if (gridTouchX == POSITION_SCALE_BUTTON || gridTouchX == POSITION_SCALE_BUTTON + 1) {
        select_page(SCALESELECT);
        gridScaleSelector();
        scaleSelector();
        for (int i = 0; i < scalesQuant; i++) {
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
        select_page(10);
        gridSongMode(songpageNumber);
      }
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select Drumchannel
      if (trackTouchY == 0) {
        select_page(DRUMTRACK);
        desired_track = 0;
        griddrumStepSequencer();
      }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select channel2-8
      for (int tracks = 1; tracks < 8; tracks++) {
        if (trackTouchY == tracks) {
          desired_track = tracks;
          select_page(tracks);
          gridStepSequencer(tracks);
        }
      }
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select Mixer
      if (gridTouchY == 13) {
        select_page(MIXER_PAGE_1);
        mixerPage1_Static(0);
      }
    }
  }
  //***********************************************************************************************************************
  //9)copy one of the plugin Page Views
  //and change the names according to our variables and functions.
  //Every page you want to make has to have its own statement
  //we create:

  //  //setting up the Plugin3 Page1-view
  //if (selectPage[PLUGIN3_PAGE1]) {
  //Plugin3_Page1_Dynamic();
  //}

  // after adding the active state statement
  // now head over to the "midi.ino"
  //look for *****************************************************************************************

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //-----------------------------------------
  //setting up the Plugin1 Page1-view
  if (selectPage[PLUGIN1_PAGE1]) {
    Plugin1_Page1_Dynamic();
  }
  //setting up the Plugin1 Page2-view
  if (selectPage[PLUGIN1_PAGE2]) {
    Plugin1_Page2_Dynamic();
  }

  //setting up the Plugin2 Page1-view
  if (selectPage[PLUGIN2_PAGE1]) {
    Plugin2_Page1_Dynamic();
  }


  /////////////////////////////////////////////////////////////////////////////
  //setting up the Plugin3 Page1-view
  if (selectPage[PLUGIN3_PAGE1]) {
    Plugin3_Page1_Dynamic(desired_instrument);
  }
  /////////////////////////////////////////////////////////////////////////////


  //setting up the Plugin4 Page1-view
  if (selectPage[PLUGIN4_PAGE1]) {
    Plugin4_Page1_Dynamic();
  }

  //setting up the Plugin5 Page1-view
  if (selectPage[PLUGIN5_PAGE1]) {
    Plugin5_Page1_Dynamic();
  }
  //setting up the Plugin6 Page1-view
  if (selectPage[PLUGIN6_PAGE1]) {
    Plugin6_Page1_Dynamic();
  }
  //setting up the Plugin7 Page1-view
  if (selectPage[PLUGIN7_PAGE1]) {
    Plugin7_Page1_Dynamic();
  }
  //setting up the Plugin7 Page2-view
  if (selectPage[PLUGIN7_PAGE2]) {
    Plugin7_Page2_Dynamic();
  }
  //setting up the Plugin8 Page1-view
  if (selectPage[PLUGIN8_PAGE1]) {
    Plugin8_Page1_Dynamic();
  }
  //setting up the Plugin9 Page1-view
  if (selectPage[PLUGIN9_PAGE1]) {
    Plugin9_Page1_Dynamic();
  }
  //setting up the Plugin10 Page1-view
  if (selectPage[PLUGIN10_PAGE1]) {
    Plugin10_Page1_Dynamic();
  }



  //setting up the StepSequencer-view for drumtrack #1
  if (selectPage[DRUMTRACK]) {
    drumStepSequencer();
  }
  //setting up the melodicStepSequencer-view for #2-8
  for (int i = 1; i < 8; i++) {
    if (selectPage[i]) {
      melodicStepSequencer(i);
    }
  }
  //setting up the scaleSelector-view
  if (selectPage[SCALESELECT]) {
    scaleSelector();
  }
  //setting up the songmode full zoom-view
  //if (selectPage[9]) {
  //songModePage(16);
   //}
  //setting up the songMode-view1
  for (byte pagenr = 0; pagenr < 16; pagenr++) {
    if (selectPage[pagenr + 10]) {
      songModePage(pagenr);
    }
  }

  //setting up the Mixer Page 1
  if (selectPage[MIXER_PAGE_1]) {
    MixerPage1_Dynamic();
  }
  //setting up the Mixer Page 2
  if (selectPage[MIXER_PAGE_2]) {
    MixerPage2_Dynamic();
  }
  //setting up the Mixer Page 3
  if (selectPage[MIXER_PAGE_3]) {
    MixerPage3_Dynamic();
  }
    //setting up the Mixer Page 3
  if (selectPage[FX1_PAGE1]) {
    FX1reverb_dynamic();
  }
      //setting up the Mixer Page 3
  if (selectPage[FX2_PAGE1]) {
    FX2Bitcrush_dynamic();
  }
  //setting up the Mixer Page 2
  if (selectPage[MIDICC_PAGE_1]) {
    midiCCpage1_Dynamic(desired_track);
  }
  //if (something_was_pressed) {
  //Serial.println("==== end of loop ====");
  //delay(2000);
  //}
}

void leftbutton() {


  for (int pixelX = 0; pixelX < 16; pixelX++) {
    for (int pixelY = 0; pixelY < 16; pixelY++) {
      tft.drawPixel(pixelX + (STEP_FRAME_W * last_button_X), pixelY + (STEP_FRAME_H * last_button_Y), tftRAM[pixelX][pixelY]);
    }
  }
  for (int pixelX = 0; pixelX < 16; pixelX++) {
    for (int pixelY = 0; pixelY < 16; pixelY++) {
      tftRAM[pixelX][pixelY] = tft.readPixel(pixelX + (STEP_FRAME_W * (last_button_X - 1)), pixelY + (STEP_FRAME_H * (last_button_Y)));
    }
  }
  tft.drawRect((STEP_FRAME_W * (last_button_X - 1)) + 1, (STEP_FRAME_H * (last_button_Y)) + 1, 15, 15, ILI9341_WHITE);
  last_button_X -= 1;
  gridTouchX = last_button_X;
  gridTouchY = last_button_Y;
}
void rightbutton() {
  for (int pixelX = 0; pixelX < 16; pixelX++) {
    for (int pixelY = 0; pixelY < 16; pixelY++) {
      tft.drawPixel(pixelX + (STEP_FRAME_W * last_button_X), pixelY + (STEP_FRAME_H * last_button_Y), tftRAM[pixelX][pixelY]);
    }
  }
  for (int pixelX = 0; pixelX < 16; pixelX++) {
    for (int pixelY = 0; pixelY < 16; pixelY++) {
      tftRAM[pixelX][pixelY] = tft.readPixel(pixelX + (STEP_FRAME_W * (last_button_X + 1)), pixelY + (STEP_FRAME_H * (last_button_Y)));
    }
  }
  tft.drawRect((STEP_FRAME_W * (last_button_X + 1)) + 1, (STEP_FRAME_H * (last_button_Y)) + 1, 15, 15, ILI9341_WHITE);
  last_button_X += 1;
  gridTouchX = last_button_X;
  gridTouchY = last_button_Y;
}
void upbutton() {
  //i have pushed the upbutton now:
  //draw the last grid´s pixels
  for (int pixelX = 0; pixelX < 16; pixelX++) {
    for (int pixelY = 0; pixelY < 16; pixelY++) {
      tft.drawPixel(pixelX + (STEP_FRAME_W * last_button_X), pixelY + (STEP_FRAME_H * last_button_Y), tftRAM[pixelX][pixelY]);
    }
  }
  //read the new grid´s pixels
  for (int pixelX = 0; pixelX < 16; pixelX++) {
    for (int pixelY = 0; pixelY < 16; pixelY++) {
      tftRAM[pixelX][pixelY] = tft.readPixel(pixelX + (STEP_FRAME_W * last_button_X), pixelY + (STEP_FRAME_H * (last_button_Y - 1)));
    }
  }
  //draw a rect(marker) to the new grid
  tft.drawRect((STEP_FRAME_W * last_button_X) + 1, (STEP_FRAME_H * (last_button_Y - 1)) + 1, 15, 15, ILI9341_WHITE);
  last_button_Y -= 1;
  gridTouchX = last_button_X;
  gridTouchY = last_button_Y;
}
void downbutton() {
  for (int pixelX = 0; pixelX < 16; pixelX++) {
    for (int pixelY = 0; pixelY < 16; pixelY++) {
      tft.drawPixel(pixelX + (STEP_FRAME_W * last_button_X), pixelY + (STEP_FRAME_H * last_button_Y), tftRAM[pixelX][pixelY]);
    }
  }
  for (int pixelX = 0; pixelX < 16; pixelX++) {
    for (int pixelY = 0; pixelY < 16; pixelY++) {
      tftRAM[pixelX][pixelY] = tft.readPixel(pixelX + (STEP_FRAME_W * last_button_X), pixelY + (STEP_FRAME_H * (last_button_Y + 1)));
    }
  }
  tft.drawRect((STEP_FRAME_W * last_button_X) + 1, (STEP_FRAME_H * (last_button_Y + 1)) + 1, 15, 15, ILI9341_WHITE);
  last_button_Y += 1;
  gridTouchX = last_button_X;
  gridTouchY = last_button_Y;
}

void savebutton() {

  // delete the file:
  Serial.println("Removing test.txt...");
  SD.remove("test.txt");

  // open the file.
  Serial.println("Creating and opening test.txt...");
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    for (byte tracks = 0; tracks < 8; tracks++) {
      for (byte clips = 0; clips < 9; clips++) {
        for (byte steps = 0; steps < 16; steps++) {
          myFile.print((char)clip[tracks][clips][steps]);
        }
      }
    }
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }

    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
void loadbutton() {

  // open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    bool debug_load = true;
    bool loading_error = !myFile.available();
    for (byte tracks = 0; !loading_error && tracks < 8; tracks++) {
      if (debug_load) Serial.printf("Starting read track %i:-\n", tracks);
      for (byte clips = 0; !loading_error && clips < 9; clips++) {
        if (debug_load) Serial.printf("\tStarting read clips %i:-\n", clips);
        for (byte steps = 0; !loading_error && steps < 16; steps++) {
          if (debug_load) Serial.printf("\t\tStarting read step %i:-\n", steps);
          loading_error = !myFile.available();
          if (loading_error) {
            if (debug_load) Serial.printf("Loading error -- wanted to read a byte for clip[%i][%i][%i], but no data available!\n", tracks, clips, steps);
            break;
          }
          clip[tracks][clips][steps] = myFile.read();
          if (debug_load) Serial.printf("\t\t\tRead byte %i\n", clip[tracks][clips][steps]);
        }
      }
    }
    if (loading_error) {
      Serial.println("Encountered error loading data!");
    } else {
      Serial.println("Success, I think?");
    }

    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
void select_page(byte selectedPage) {
  for (byte others = 0; others <= MAX_PAGES; others++) {
    selectPage[others] = LOW;
  }
  selectPage[selectedPage] = HIGH;
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
  for (int otherTracks = 2; otherTracks <= 8; otherTracks++) {
    tft.fillRect(1, TRACK_FRAME_H * otherTracks - 8, 15, TRACK_FRAME_H, trackColor[otherTracks - 1]);  //Xmin, Ymin, Xlength, Ylength, color
    tft.setCursor(4, TRACK_FRAME_H * otherTracks - 2);
    tft.print(otherTracks);
  }
  //Mixer button
  tft.fillRect(1, STEP_FRAME_H * 13, 15, TRACK_FRAME_H, ILI9341_LIGHTGREY);  //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(3, STEP_FRAME_H * 13 + 6);
  tft.print("M");

  //scale Select
  tft.drawRect(STEP_FRAME_W * POSITION_SCALE_BUTTON + 1, 0, STEP_FRAME_W * 2 - 1, STEP_FRAME_H, ILI9341_WHITE);

  //arrangment Select
  tft.drawRect(STEP_FRAME_W * POSITION_ARR_BUTTON + 1, 0, STEP_FRAME_W * 2 - 1, STEP_FRAME_H, ILI9341_WHITE);

  // record button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_RECORD_BUTTON - 2, 0, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.fillCircle(STEP_FRAME_W * POSITION_RECORD_BUTTON + 5, 7, DOT_RADIUS + 1, ILI9341_RED);

  //Play button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_PLAY_BUTTON - 2, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);                                                                  //PLAY RECT FRAME
  tft.fillTriangle(STEP_FRAME_W * POSITION_PLAY_BUTTON + 10, 3, STEP_FRAME_W * POSITION_PLAY_BUTTON + 10, 13, STEP_FRAME_W * POSITION_PLAY_BUTTON + 20, 8, ILI9341_GREEN);  // x1, y1, x2, y2, x3, y3

  //stop button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_STOP_BUTTON - 2, 0, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.fillRect(STEP_FRAME_W * POSITION_STOP_BUTTON + 1, 3, 10, 10, ILI9341_LIGHTGREY);

  //barcounter & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_BAR_BUTTON - 2, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);
  tft.drawRect(STEP_FRAME_W * POSITION_BPM_BUTTON - 2, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);

  //save button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_SAVE_BUTTON - 2, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);
  tft.fillRect(STEP_FRAME_W * POSITION_SAVE_BUTTON - 1, 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_ORANGE);
  tft.setTextColor(ILI9341_BLACK);
  tft.setFont(Arial_9);
  tft.setCursor(STEP_FRAME_W * POSITION_SAVE_BUTTON, 3);
  tft.print("SAV");

  //load button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_LOAD_BUTTON - 2, 0, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.fillRect(STEP_FRAME_W * POSITION_LOAD_BUTTON - 1, 1, STEP_FRAME_W - 2, STEP_FRAME_H - 2, ILI9341_GREENYELLOW);
  tft.setTextColor(ILI9341_BLACK);
  tft.setFont(Arial_9);
  tft.setCursor(STEP_FRAME_W * POSITION_LOAD_BUTTON, 3);
  tft.print("L");
}
void showCoordinates() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    tft.fillRect(20, 0, 50, 13, ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
    tft.setTextColor(ILI9341_GREEN);
    tft.setFont(Arial_10);
    tft.setCursor(20, 3);
    tft.print("X");
    tft.print(gridTouchX);
    tft.setCursor(45, 3);
    tft.print("Y");
    tft.print(gridTouchY);



    //    tft.fillRect(STEP_FRAME_W * POSITION_BPM_BUTTON, 3, STEP_FRAME_W * 2 - 3, 10, ILI9341_DARKGREY);
    //    tft.setTextColor(ILI9341_WHITE);
    //    tft.setFont(Arial_9);
    //    tft.setCursor(STEP_FRAME_W * POSITION_BPM_BUTTON + 2, 3);
    //    tft.print(tempoSelect);
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
    for (int i = 0; i < scalesQuant; i++) {
      tft.setCursor(STEP_FRAME_W * 2, STEP_FRAME_H * i + STEP_FRAME_H);
      tft.setFont(Arial_8);
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(1);
      tft.print(scaleNames[i]);

      if (gridTouchX > 1 && gridTouchX < 15 && gridTouchY == i + 1) {
        scaleSelected = i;
        tft.fillRect(STEP_FRAME_W * POSITION_SCALE_BUTTON + 1, 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
        tft.setCursor(STEP_FRAME_W * POSITION_SCALE_BUTTON + 2, 2);
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
  for (int i = 0; i < 17; i++) {  //vert Lines
    step_Frame_X = i * STEP_FRAME_W;
    tft.drawFastVLine(step_Frame_X + STEP_FRAME_W * 2, STEP_FRAME_H, GRID_LENGTH_VERT, ILI9341_WHITE);  //(x, y-start, length, color)
    if (i % 4 == 0) {
      tft.drawFastVLine((i * STEP_FRAME_W) + 32, STEP_FRAME_H, STEP_FRAME_H * 12, ILI9341_LIGHTGREY);  //(x, y-start, y-length, color)
    }
  }
  for (int i = 0; i < 13; i++) {  //hor lines
    step_Frame_Y = i * 16;
    tft.drawFastHLine(STEP_FRAME_W * 2, step_Frame_Y + STEP_FRAME_H, GRID_LENGTH_HOR, ILI9341_WHITE);  //(x-start, y, length, color)
  }
  //draw Clipselector
  for (int ClipNr = 0; ClipNr < 8; ClipNr++) {
    tft.fillRect(STEP_FRAME_W * 2 * ClipNr + STEP_FRAME_W * 2, STEP_FRAME_H * 13, STEP_FRAME_W * 2, STEP_FRAME_H, trackColor[desired_instrument] + ClipNr * 20);
    tft.setCursor(STEP_FRAME_W * 2 * ClipNr + STEP_FRAME_W * 2 + 2, STEP_FRAME_H * 13 + 4);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(1);
    tft.print("Clip ");
    tft.print(ClipNr + 1);
  }
  for (int i = 0; i < 12; i++) {
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
  tft.fillRect(leftmost + 1, STEP_FRAME_H * 2, STEP_FRAME_W * 2, STEP_FRAME_H * 7, ILI9341_DARKGREY);
  tft.fillTriangle(leftmost + 1, UP_bottommost, rightmost, UP_bottommost, leftmost + STEP_FRAME_W, UP_topmost, ILI9341_LIGHTGREY);         //octave arrow up
  tft.fillTriangle(leftmost + 1, DOWN_topmost, rightmost - 2, DOWN_topmost, leftmost + STEP_FRAME_W, DOWN_bottommost, ILI9341_LIGHTGREY);  //x1, y1, x2, y2, x3, y3
  tft.fillRect(leftmost + 1, UP_bottommost, STEP_FRAME_W * 2, STEP_FRAME_H * 3 + 1, ILI9341_DARKGREY);
  tft.setCursor(leftmost + 12, STEP_FRAME_H * 4 + 8);
  tft.setFont(Arial_16);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);

  //draw Notenames
  for (int n = 0; n < 12; n++) {  //hor notes
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
void drawActiveSteps() {
  byte tone_start = track[desired_instrument].shown_octaves * 12;
  //draw active steps
  for (byte steps = 0; steps < STEP_QUANT; steps++) {
    if (ctrack[desired_track].sequence[track[desired_track].clip_selector].step[steps] > VALUE_NOTEOFF) {
      int dot_on_X = (steps * STEP_FRAME_W) + DOT_OFFSET_X;
      int dot_on_Y = ((ctrack[desired_track].sequence[track[desired_track].clip_selector].step[steps] - tone_start) * STEP_FRAME_H) + DOT_OFFSET_Y;
      tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, trackColor[desired_track] + track[desired_track].clip_selector * 20);
    }
  }
}
void drawActiveDrumSteps() {
  for (byte tone = 0; tone < 12; tone++) {
    for (byte steps = 0; steps < STEP_QUANT; steps++) {
      if (channel1Clip[ch1Clip][tone][steps]) {
        tft.fillCircle((steps * STEP_FRAME_W) + DOT_OFFSET_X, ((tone)*STEP_FRAME_H) + DOT_OFFSET_Y, DOT_RADIUS, trackColor[0] + track[0].clip_selector * 20);
      }
    }
  }
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
  for (int plugintext = 0; plugintext <= 16; plugintext++) {
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
  for (int plugintext = 0; plugintext <= MAX_PLUGINS; plugintext++) {
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
  for (int T = 0; T < 12; T++) {
    for (int S = 0; S < 16; S++) {
      tft.fillCircle(S * STEP_FRAME_W + DOT_OFFSET_X, T * STEP_FRAME_H + 24, DOT_RADIUS, ILI9341_DARKGREY);  // circle: x, y, radius, color
    }
  }
}
void clearStepsGridY() {  // clear all Steps in the same column
  for (int T = 0; T < 12; T++) {

    tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, T * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, ILI9341_DARKGREY);  // circle: x, y, radius, color
  }
}