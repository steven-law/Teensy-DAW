bool debugTime = false;
extern unsigned long _heap_start;
extern unsigned long _heap_end;
extern char *__brkval;
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
#include "c_pluginVariables.h"
#include "Adafruit_Keypad.h"
#include <ResponsiveAnalogRead.h>
#include <USBHost_t36.h>
#include <Encoder.h>
#include <MIDI.h>
#include "v_smfwriter.h"

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
const char keys[ROWS][COLS] = {
  { '0', '1', '2', '3' },
  { '4', '5', '6', '7' },
  { '8', '9', 'A', 'B' },
  { 'C', 'D', 'E', 'F' }
};
const byte rowPins[ROWS] = { 37, 36, 35, 34 };  //connect to the row pinouts of the keypad
const byte colPins[COLS] = { 41, 38, 39, 40 };  //connect to the column pinouts of the keypad

Adafruit_Keypad kpd = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
//Encoder Pins
Encoder Enc1(31, 32);
Encoder Enc2(27, 28);
Encoder Enc3(24, 25);
Encoder Enc4(2, 3);



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
#define MAX_USB_DEVICES 10
#define MIDI_VENDORID_LAUNCHPAD 4661
#define MIDI_PRODUCTID_LAUNCHPAD 54

MIDIDevice *launchpad = nullptr;
MIDIDevice *usb_midi_devices[MAX_USB_DEVICES] = { &midi01, &midi02, &midi03, &midi04, &midi05, &midi06, &midi07, &midi08, &midi09, &midi10 };




//please use this Audio GUI from Newdigate
//https://newdigate.github.io/teensy-eurorack-audio-gui/
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthNoiseWhite pl7noise1;               //xy=60,1544.0000228881836
AudioSynthWaveformDc pl5dc1;                  //xy=61.5,1260
AudioPlayMemory playMem9;                     //xy=62.5,1044
AudioSynthWaveformDc pl6dc1;                  //xy=63.5,1364
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
AudioSynthWaveformSine pl7waveformMod3;       //xy=87,1628.0000247955322
AudioPlayMemory playMem11;                    //xy=89.5,1114
AudioPlaySdWav playSdWav2;                    //xy=93.5,336
AudioPlaySdWav playSdWav5;                    //xy=93.5,449
AudioPlaySdWav playSdWav6;                    //xy=93.5,489
AudioPlaySdWav playSdWav1;                    //xy=96.5,297
AudioPlayMemory playMem12;                    //xy=94.5,1152
AudioPlayMemory playMem3;                     //xy=97.5,828
AudioPlayMemory playMem4;                     //xy=104.5,864
AudioSynthNoiseWhite pl7noise2;               //xy=150,1685.0000247955322
AudioSynthNoisePink pl7pink1;                 //xy=150,1725.0000247955322
AudioSynthWaveformDc pl8dc1;                  //xy=161.50000953674316,1901.0000267028809
AudioPlayArrayResmp playSdPitch1;             //xy=199.5,1206
AudioEffectEnvelope pl5envelope2;             //xy=209.5,1259
AudioPlaySdResmp playSdPitch2;                //xy=209.5,1312
AudioEffectEnvelope pl6envelope2;             //xy=211.5,1363
AudioSynthSimpleDrum pl7drum1;                //xy=216,1465
AudioSynthWaveformModulated pl7waveformMod1;  //xy=223,1546
AudioEffectEnvelope envelope1;                //xy=229.5,236
AudioSynthWaveform pl9bpinput;                //xy=229.50000762939453,2025.0000286102295
AudioSynthKarplusStrong pl9string1;           //xy=233.50000762939453,1974.0000286102295
AudioMixer4 mixer1;                           //xy=241.5,86
AudioEffectEnvelope pl7envelope2;             //xy=267,1626.0000247955322
AudioSynthWaveformDc pl3dc1;                  //xy=292.5,678
AudioMixer4 pl7mixer4;                        //xy=289,1713.0000247955322
AudioMixer4 drummixer1;                       //xy=297.5,321
AudioSynthWaveform pl8waveform1;              //xy=291.50000953674316,1850.0000267028809
AudioMixer4 drummixer2;                       //xy=299.5,410
AudioMixer4 drummixer3;                       //xy=308.5,502
AudioMixer4 pl4drummixer1;                    //xy=309.5,775
AudioFilterStateVariable filter1;             //xy=313.5,164
AudioMixer4 pl4drummixer2;                    //xy=311.5,864
AudioEffectEnvelope pl8envelope2;             //xy=316.50000953674316,1900.0000267028809
AudioMixer4 pl4drummixer3;                    //xy=320.5,956
AudioSynthWaveform pl3waveform1;              //xy=329.5,615
AudioSynthWaveformDc pl9dc1;                  //xy=362,2119
AudioFilterStateVariable pl5filter1;          //xy=373.5,1225
AudioFilterStateVariable pl6filter1;          //xy=375.5,1329
AudioFilterStateVariable pl9bpfilter;         //xy=373.50000762939453,1978.0000286102295
AudioFilterStateVariable pl7filter1;          //xy=386,1465
AudioFilterStateVariable pl7filter2;          //xy=387,1555
AudioSynthWaveformDc pl7dc1;                  //xy=389,1509
AudioMixer4 pl1mixer2;                        //xy=426.5,70
AudioFilterBiquad pl7biquad1;                 //xy=431,1705.0000247955322
AudioEffectEnvelope pl3envelope2;             //xy=435.5,675
AudioFilterStateVariable pl9filter2;          //xy=432.0000305175781,2057.000030517578
AudioSynthWaveformModulated pl7waveformMod2;  //xy=443,1629.0000247955322
AudioMixer4 drummixer4;                       //xy=482.5,431
AudioFilterLadder pl8filter1;                 //xy=482.50000953674316,1863.0000267028809
AudioFilterStateVariable pl3filter1;          //xy=497.5,617
AudioMixer4 pl6mixer1;                        //xy=510.5,1341
AudioMixer4 pl5mixer1;                        //xy=525.5,1126
AudioEffectEnvelope envelope2;                //xy=538.5,136
AudioMixer4 pl4drummixer4;                    //xy=537.5,784
AudioEffectEnvelope pl7envelope1;             //xy=540,1540
AudioEffectWaveFolder pl9wavefolder1;         //xy=548.0000076293945,1957.0000286102295
AudioEffectBitcrusher bitcrusher1;            //xy=574.5,80
AudioMixer4 pl9mixer1;                        //xy=591.5000228881836,2029.0000305175781
AudioEffectWaveFolder pl7wavefolder1;         //xy=594,1457
AudioEffectEnvelope pl7envelope4;             //xy=619,1703.0000247955322
AudioEffectEnvelope pl7envelope3;             //xy=625,1640.0000247955322
AudioEffectEnvelope pl5envelope1;             //xy=629.5,1215
AudioAmplifier pl2amp2;                       //xy=641,439
AudioMixer4 pl3mixer1;                        //xy=642.5,577
AudioEffectEnvelope pl6envelope1;             //xy=642.5,1316
AudioEffectEnvelope pl8envelope1;             //xy=647.5000095367432,1872.0000267028809
AudioAmplifier pl14amp2;                      //xy=650.200008392334,2718.0000381469727
AudioAmplifier pl12amp2;                      //xy=655.0000076293945,2355.0000338554382
AudioAmplifier pl11amp2;                      //xy=657.0000076293945,2236.0000324249268
AudioAmplifier pl16amp2;                      //xy=654.200008392334,2941.00004196167
AudioAmplifier pl13amp2;                      //xy=667.2000122070312,2570.000036239624
AudioAmplifier pl10amp2;                      //xy=673.0000133514404,2153.0000648498535
AudioAmplifier pl15amp2;                      //xy=678.200008392334,2785.0000381469727
AudioAmplifier pl4amp2;                       //xy=689,760
AudioEffectEnvelope pl3envelope1;             //xy=719.5000076293945,629.0000095367432
AudioEffectDelay pl1delay1;                   //xy=723.5,218
AudioMixer4 pl1mixer3;                        //xy=727.5,35
AudioFilterStateVariable pl1filter3;          //xy=727.5,110
AudioAmplifier pl9amp2;                       //xy=732.0000076293945,1951.0000286102295
AudioAmplifier pl8amp2;                       //xy=736.0000247955322,1822.0000534057617
AudioAmplifier pl7amp2;                       //xy=756.0000076293945,1550.0000228881836
AudioMixer4 pl7mixer2;                        //xy=773.5000114440918,1746.0000247955322
AudioAmplifier pl2amp;                        //xy=779.5,441
AudioAmplifier pl6amp2;                       //xy=781,1283
AudioAmplifier pl3amp2;                       //xy=786.0000114440918,580.0000076293945
AudioMixer4 pl7mixer1;                        //xy=788.5000114440918,1644.0000228881836
AudioAmplifier pl5amp2;                       //xy=792,1152
AudioAmplifier pl4amp;                        //xy=803.5000114440918,772.0000114440918
AudioAmplifier pl11amp;                       //xy=804.0000076293945,2238.0000314712524
AudioAmplifier pl10amp;                       //xy=806.0000152587891,2144.000065803528
AudioAmplifier pl16amp;                       //xy=808.1999473571777,2945.00004196167
AudioAmplifier pl12amp;                       //xy=812.0000076293945,2352.0000338554382
AudioAmplifier pl15amp;                       //xy=823.1999626159668,2786.000075340271
AudioAmplifier pl13amp;                       //xy=824.1999664306641,2566.0000705718994
AudioAmplifier pl14amp;                       //xy=825.1999626159668,2706.0000743865967
AudioAmplifier pl8amp;                        //xy=836.5000152587891,1860.0000267028809
AudioAmplifier pl9amp;                        //xy=836.5000076293945,1981.0000286102295
AudioAmplifier pl1amp2;                       //xy=854,92
AudioAmplifier pl7amp;                        //xy=856.5000114440918,1574.0000228881836
AudioAmplifier pl3amp;                        //xy=878.5000114440918,624.0000085830688
AudioAmplifier pl5amp;                        //xy=877.5000114440918,1214.000018119812
AudioAmplifier pl6amp;                        //xy=880.5000114440918,1316.0000190734863
AudioMixer4 pl7mixer3;                        //xy=925.5000152587891,1697.0000247955322
AudioAmplifier pl2FX2;                        //xy=932.0000152587891,443.00000762939453
AudioAmplifier pl2FX3;                        //xy=932.0000152587891,465.00000762939453
AudioAmplifier pl2dry;                        //xy=935,406
AudioAmplifier pl2FX1;                        //xy=936.0000114440918,424.0000057220459
AudioAmplifier pl4FX2;                        //xy=946.0000152587891,775.0000114440918
AudioAmplifier pl4FX3;                        //xy=946.0000152587891,795.0000114440918
AudioAmplifier pl4dry;                        //xy=947,733
AudioAmplifier pl4FX1;                        //xy=947.0000152587891,754.0000114440918
AudioAmplifier pl1amp;                        //xy=971.5,173
AudioAmplifier pl14FX3;                       //xy=961.9999942779541,2727.9999957084656
AudioAmplifier pl14FX2;                       //xy=963.9999904632568,2705.9999957084656
AudioAmplifier pl14dry;                       //xy=966,2668
AudioAmplifier pl8dry;                        //xy=970.0000152587891,1828.0000267028809
AudioAmplifier pl8FX1;                        //xy=970.0000133514404,1850.0000267028809
AudioAmplifier pl10dry;                       //xy=969.0000152587891,2116.000030517578
AudioAmplifier pl14FX1;                       //xy=966.9999923706055,2683.9999957084656
AudioAmplifier pl8FX2;                        //xy=971.0000133514404,1871.0000267028809
AudioAmplifier pl8FX3;                        //xy=971.0000152587891,1894.0000286102295
AudioAmplifier pl10FX1;                       //xy=972.0000152587891,2135.0000324249268
AudioAmplifier pl10FX2;                       //xy=972.0000152587891,2152.0000324249268
AudioAmplifier pl16FX3;                       //xy=968.9999942779541,2974.9999957084656
AudioAmplifier pl10FX3;                       //xy=973.0000152587891,2171.0000324249268
AudioAmplifier pl13FX3;                       //xy=972.0000076293945,2566.0000324249268
AudioAmplifier pl16FX2;                       //xy=970.9999904632568,2952.9999957084656
AudioAmplifier pl13FX2;                       //xy=974.0000038146973,2544.0000324249268
AudioAmplifier pl16dry;                       //xy=973,2915
AudioAmplifier pl9dry;                        //xy=977.0000152587891,1970.0000295639038
AudioAmplifier pl16FX1;                       //xy=973.9999923706055,2930.9999957084656
AudioAmplifier pl9FX1;                        //xy=978.0000152587891,1988.0000295639038
AudioAmplifier pl9FX2;                        //xy=978.0000152587891,2005.0000295639038
AudioAmplifier pl13dry;                       //xy=976.0000133514404,2506.000036716461
AudioAmplifier pl11dry;                       //xy=978.0000114440918,2213.0000352859497
AudioAmplifier pl13FX1;                       //xy=977.0000057220459,2522.0000324249268
AudioAmplifier pl11FX2;                       //xy=980.0000152587891,2247.0000343322754
AudioAmplifier pl11FX3;                       //xy=980.0000114440918,2265.0000343322754
AudioAmplifier pl9FX3;                        //xy=981.0000152587891,2025.0000305175781
AudioAmplifier pl12dry;                       //xy=980.0000152587891,2309.0000343322754
AudioAmplifier pl11FX1;                       //xy=983.0000152587891,2229.000033378601
AudioAmplifier pl15FX3;                       //xy=980.9999942779541,2825.9999957084656
AudioAmplifier pl15FX2;                       //xy=982.9999904632568,2803.9999957084656
AudioAmplifier pl7dry;                        //xy=988.0000152587891,1562.0000228881836
AudioAmplifier pl7FX2;                        //xy=989.0000152587891,1602.0000228881836
AudioAmplifier pl7FX3;                        //xy=989.0000152587891,1625.0000228881836
AudioAmplifier pl15dry;                       //xy=985,2766
AudioAmplifier pl7FX1;                        //xy=990.0000152587891,1582.0000228881836
AudioAmplifier pl15FX1;                       //xy=985.9999923706055,2781.9999957084656
AudioAmplifier pl12FX1;                       //xy=989.0000076293945,2340.0000343322754
AudioAmplifier pl12FX2;                       //xy=991.0000076293945,2357.0000343322754
AudioAmplifier pl3dry;                        //xy=999.0000152587891,601.0000085830688
AudioAmplifier pl3FX1;                        //xy=999.0000152587891,624.0000085830688
AudioAmplifier pl3FX2;                        //xy=999.0000152587891,652.0000095367432
AudioAmplifier pl12FX3;                       //xy=993.0000076293945,2381.000036239624
AudioAmplifier pl3FX3;                        //xy=1001.0000133514404,668.0000095367432
AudioAmplifier pl6FX1;                        //xy=1013.0000152587891,1329.0000195503235
AudioAmplifier pl6dry;                        //xy=1014.0000152587891,1309.0000190734863
AudioAmplifier pl6FX2;                        //xy=1014.0000152587891,1353.0000200271606
AudioAmplifier pl5FX3;                        //xy=1016.0000114440918,1260.000015258789
AudioAmplifier pl6FX3;                        //xy=1016.0000152587891,1377.0000200271606
AudioAmplifier pl5FX1;                        //xy=1017.0000152587891,1218.0000171661377
AudioAmplifier pl5dry;                        //xy=1018.0000152587891,1197.0000171661377
AudioAmplifier pl5FX2;                        //xy=1018.0000152587891,1241.0000171661377
AudioAmplifier pl1FX3;                        //xy=1054,342
AudioAmplifier pl1dry;                        //xy=1064.000015258789,219.00000190734863
AudioAmplifier pl1FX1;                        //xy=1066,257
AudioAmplifier pl1FX2;                        //xy=1071.000015258789,300.0000047683716
AudioMixer4 mixer6;                           //xy=1176.5,1272
AudioMixer4 FX2mixer1;                        //xy=1188.5,694
AudioMixer4 mixer5;                           //xy=1190.5,530
AudioMixer4 FX3mixer2;                        //xy=1187.5,1529
AudioMixer4 FX1mixer1;                        //xy=1191.5,607
AudioMixer4 FX2mixer2;                        //xy=1188.5,1442
AudioMixer4 FX1mixer2;                        //xy=1189.5,1357
AudioMixer4 FX3mixer1;                        //xy=1193.5,781
AudioMixer4 FX2mixer4;                        //xy=1224.5,2159
AudioMixer4 FX1mixer6;                        //xy=1230.2000179290771,2631.0000381469727
AudioMixer4 drymixer3;                        //xy=1231.2000179290771,2545.0000343322754
AudioMixer4 FX3mixer6;                        //xy=1231.2000217437744,2785.0000400543213
AudioMixer4 FX2mixer6;                        //xy=1232.2000217437744,2706.0000381469727
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
AudioMixer4 dlmixer1;                         //xy=2072.5000286102295,948.0000114440918
AudioEffectDelay dldelay1;                    //xy=2074.500030517578,1114.9999542236328
AudioInputI2S i2s2;                           //xy=2240.5000286102295,913.0000114440918
AudioMixer4 mixer9;                           //xy=2270.5000286102295,718.0000114440918
AudioAmplifier amp1;                          //xy=2390.5000286102295,830.0000114440918
AudioMixer4 mixer11;                          //xy=2460.5000286102295,690.0000114440918
AudioRecordQueue queue1;                      //xy=2521.5000286102295,866.0000114440918
AudioAnalyzePeak peak1;                       //xy=2523.5000286102295,913.0000114440918
AudioOutputI2S i2s1;                          //xy=2629.5000286102295,692.0000114440918
AudioConnection patchCord1(pl7noise1, 0, pl7waveformMod1, 0);
AudioConnection patchCord2(pl5dc1, pl5envelope2);
AudioConnection patchCord3(playMem9, 0, pl4drummixer3, 0);
AudioConnection patchCord4(pl6dc1, pl6envelope2);
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
AudioConnection patchCord25(pl7waveformMod3, pl7envelope2);
AudioConnection patchCord26(playMem11, 0, pl4drummixer3, 2);
AudioConnection patchCord27(playSdWav2, 0, drummixer1, 1);
AudioConnection patchCord28(playSdWav5, 0, drummixer2, 0);
AudioConnection patchCord29(playSdWav6, 0, drummixer2, 1);
AudioConnection patchCord30(playSdWav1, 0, drummixer1, 0);
AudioConnection patchCord31(playMem12, 0, pl4drummixer3, 3);
AudioConnection patchCord32(playMem3, 0, pl4drummixer1, 2);
AudioConnection patchCord33(playMem4, 0, pl4drummixer1, 3);
AudioConnection patchCord34(pl7noise2, 0, pl7mixer4, 0);
AudioConnection patchCord35(pl7pink1, 0, pl7mixer4, 1);
AudioConnection patchCord36(pl8dc1, pl8envelope2);
AudioConnection patchCord37(playSdPitch1, 0, pl5filter1, 0);
AudioConnection patchCord38(pl5envelope2, 0, pl5filter1, 1);
AudioConnection patchCord39(playSdPitch2, 0, pl6filter1, 0);
AudioConnection patchCord40(pl6envelope2, 0, pl6filter1, 1);
AudioConnection patchCord41(pl7drum1, 0, pl7filter1, 0);
AudioConnection patchCord42(pl7waveformMod1, 0, pl7filter2, 0);
AudioConnection patchCord43(envelope1, 0, filter1, 1);
AudioConnection patchCord44(pl9bpinput, 0, pl9bpfilter, 1);
AudioConnection patchCord45(pl9string1, 0, pl9bpfilter, 0);
AudioConnection patchCord46(mixer1, 0, filter1, 0);
AudioConnection patchCord47(pl7envelope2, 0, pl7waveformMod2, 0);
AudioConnection patchCord48(pl3dc1, pl3envelope2);
AudioConnection patchCord49(pl7mixer4, pl7biquad1);
AudioConnection patchCord50(drummixer1, 0, drummixer4, 0);
AudioConnection patchCord51(pl8waveform1, 0, pl8filter1, 0);
AudioConnection patchCord52(drummixer2, 0, drummixer4, 1);
AudioConnection patchCord53(drummixer3, 0, drummixer4, 2);
AudioConnection patchCord54(pl4drummixer1, 0, pl4drummixer4, 0);
AudioConnection patchCord55(filter1, 0, pl1mixer2, 0);
AudioConnection patchCord56(filter1, 1, pl1mixer2, 1);
AudioConnection patchCord57(filter1, 2, pl1mixer2, 2);
AudioConnection patchCord58(pl4drummixer2, 0, pl4drummixer4, 1);
AudioConnection patchCord59(pl8envelope2, 0, pl8filter1, 1);
AudioConnection patchCord60(pl4drummixer3, 0, pl4drummixer4, 2);
AudioConnection patchCord61(pl3waveform1, 0, pl3filter1, 0);
AudioConnection patchCord62(pl5filter1, 0, pl5mixer1, 0);
AudioConnection patchCord63(pl5filter1, 1, pl5mixer1, 1);
AudioConnection patchCord64(pl5filter1, 2, pl5mixer1, 2);
AudioConnection patchCord65(pl6filter1, 0, pl6mixer1, 0);
AudioConnection patchCord66(pl6filter1, 1, pl6mixer1, 1);
AudioConnection patchCord67(pl6filter1, 2, pl6mixer1, 2);
AudioConnection patchCord68(pl9bpfilter, 0, pl9mixer1, 0);
AudioConnection patchCord69(pl7filter1, 0, pl7mixer1, 0);
AudioConnection patchCord70(pl7filter2, 0, pl7envelope1, 0);
AudioConnection patchCord71(pl7dc1, 0, pl7wavefolder1, 1);
AudioConnection patchCord72(pl1mixer2, envelope2);
AudioConnection patchCord73(pl7biquad1, pl7envelope4);
AudioConnection patchCord74(pl3envelope2, 0, pl3filter1, 1);
AudioConnection patchCord75(pl7waveformMod2, pl7envelope3);
AudioConnection patchCord76(drummixer4, pl2amp2);
AudioConnection patchCord77(pl8filter1, pl8envelope1);
AudioConnection patchCord78(pl3filter1, 0, pl3mixer1, 0);
AudioConnection patchCord79(pl3filter1, 1, pl3mixer1, 1);
AudioConnection patchCord80(pl3filter1, 2, pl3mixer1, 2);
AudioConnection patchCord81(pl6mixer1, pl6envelope1);
AudioConnection patchCord82(pl5mixer1, pl5envelope1);
AudioConnection patchCord83(envelope2, bitcrusher1);
AudioConnection patchCord84(pl4drummixer4, pl4amp2);
AudioConnection patchCord85(pl7envelope1, 0, pl7mixer1, 1);
AudioConnection patchCord86(bitcrusher1, 0, pl1mixer3, 0);
AudioConnection patchCord87(pl9mixer1, pl9amp2);
AudioConnection patchCord88(pl7envelope4, 0, pl7mixer1, 3);
AudioConnection patchCord89(pl7envelope3, 0, pl7mixer1, 2);
AudioConnection patchCord90(pl5envelope1, pl5amp2);
AudioConnection patchCord91(pl2amp2, pl2amp);
AudioConnection patchCord92(pl3mixer1, pl3envelope1);
AudioConnection patchCord93(pl6envelope1, pl6amp2);
AudioConnection patchCord94(pl8envelope1, pl8amp2);
AudioConnection patchCord95(pl14amp2, pl14amp);
AudioConnection patchCord96(pl12amp2, pl12amp);
AudioConnection patchCord97(pl11amp2, pl11amp);
AudioConnection patchCord98(pl16amp2, pl16amp);
AudioConnection patchCord99(pl13amp2, pl13amp);
AudioConnection patchCord100(pl10amp2, pl10amp);
AudioConnection patchCord101(pl15amp2, pl15amp);
AudioConnection patchCord102(pl4amp2, pl4amp);
AudioConnection patchCord103(pl3envelope1, pl3amp2);
AudioConnection patchCord104(pl1delay1, 0, pl1filter3, 0);
AudioConnection patchCord105(pl1mixer3, pl1delay1);
AudioConnection patchCord106(pl1mixer3, pl1amp2);
AudioConnection patchCord107(pl1filter3, 2, pl1mixer3, 1);
AudioConnection patchCord108(pl9amp2, pl9amp);
AudioConnection patchCord109(pl8amp2, pl8amp);
AudioConnection patchCord110(pl7amp2, pl7amp);
AudioConnection patchCord111(pl7mixer2, 0, pl7mixer3, 1);
AudioConnection patchCord112(pl2amp, pl2FX3);
AudioConnection patchCord113(pl2amp, pl2dry);
AudioConnection patchCord114(pl2amp, pl2FX1);
AudioConnection patchCord115(pl2amp, pl2FX2);
AudioConnection patchCord116(pl6amp2, pl6amp);
AudioConnection patchCord117(pl3amp2, pl3amp);
AudioConnection patchCord118(pl7mixer1, 0, pl7mixer3, 0);
AudioConnection patchCord119(pl5amp2, pl5amp);
AudioConnection patchCord120(pl4amp, pl4dry);
AudioConnection patchCord121(pl4amp, pl4FX1);
AudioConnection patchCord122(pl4amp, pl4FX2);
AudioConnection patchCord123(pl4amp, pl4FX3);
AudioConnection patchCord124(pl11amp, pl11dry);
AudioConnection patchCord125(pl11amp, pl11FX1);
AudioConnection patchCord126(pl11amp, pl11FX2);
AudioConnection patchCord127(pl11amp, pl11FX3);
AudioConnection patchCord128(pl10amp, pl10dry);
AudioConnection patchCord129(pl10amp, pl10FX1);
AudioConnection patchCord130(pl10amp, pl10FX2);
AudioConnection patchCord131(pl10amp, pl10FX3);
AudioConnection patchCord132(pl16amp, pl16dry);
AudioConnection patchCord133(pl16amp, pl16FX1);
AudioConnection patchCord134(pl16amp, pl16FX2);
AudioConnection patchCord135(pl16amp, pl16FX3);
AudioConnection patchCord136(pl12amp, pl12dry);
AudioConnection patchCord137(pl12amp, pl12FX1);
AudioConnection patchCord138(pl12amp, pl12FX2);
AudioConnection patchCord139(pl12amp, pl12FX3);
AudioConnection patchCord140(pl15amp, pl15dry);
AudioConnection patchCord141(pl15amp, pl15FX1);
AudioConnection patchCord142(pl15amp, pl15FX2);
AudioConnection patchCord143(pl15amp, pl15FX3);
AudioConnection patchCord144(pl13amp, pl13FX3);
AudioConnection patchCord145(pl13amp, pl13FX2);
AudioConnection patchCord146(pl13amp, pl13FX1);
AudioConnection patchCord147(pl13amp, pl13dry);
AudioConnection patchCord148(pl14amp, pl14dry);
AudioConnection patchCord149(pl14amp, pl14FX1);
AudioConnection patchCord150(pl14amp, pl14FX2);
AudioConnection patchCord151(pl14amp, pl14FX3);
AudioConnection patchCord152(pl8amp, pl8dry);
AudioConnection patchCord153(pl8amp, pl8FX1);
AudioConnection patchCord154(pl8amp, pl8FX2);
AudioConnection patchCord155(pl8amp, pl8FX3);
AudioConnection patchCord156(pl9amp, pl9dry);
AudioConnection patchCord157(pl9amp, pl9FX1);
AudioConnection patchCord158(pl9amp, pl9FX2);
AudioConnection patchCord159(pl9amp, pl9FX3);
AudioConnection patchCord160(pl1amp2, pl1amp);
AudioConnection patchCord161(pl7amp, pl7dry);
AudioConnection patchCord162(pl7amp, pl7FX1);
AudioConnection patchCord163(pl7amp, pl7FX2);
AudioConnection patchCord164(pl7amp, pl7FX3);
AudioConnection patchCord165(pl3amp, pl3dry);
AudioConnection patchCord166(pl3amp, pl3FX1);
AudioConnection patchCord167(pl3amp, pl3FX2);
AudioConnection patchCord168(pl3amp, pl3FX3);
AudioConnection patchCord169(pl5amp, pl5dry);
AudioConnection patchCord170(pl5amp, pl5FX1);
AudioConnection patchCord171(pl5amp, pl5FX2);
AudioConnection patchCord172(pl5amp, pl5FX3);
AudioConnection patchCord173(pl6amp, pl6dry);
AudioConnection patchCord174(pl6amp, pl6FX1);
AudioConnection patchCord175(pl6amp, pl6FX2);
AudioConnection patchCord176(pl6amp, pl6FX3);
AudioConnection patchCord177(pl7mixer3, pl7amp2);
AudioConnection patchCord178(pl2FX2, 0, FX2mixer1, 1);
AudioConnection patchCord179(pl2FX3, 0, FX3mixer1, 1);
AudioConnection patchCord180(pl2dry, 0, mixer5, 1);
AudioConnection patchCord181(pl2FX1, 0, FX1mixer1, 1);
AudioConnection patchCord182(pl4FX2, 0, FX2mixer1, 3);
AudioConnection patchCord183(pl4FX3, 0, FX3mixer1, 3);
AudioConnection patchCord184(pl4dry, 0, mixer5, 3);
AudioConnection patchCord185(pl4FX1, 0, FX1mixer1, 3);
AudioConnection patchCord186(pl1amp, pl1dry);
AudioConnection patchCord187(pl1amp, pl1FX1);
AudioConnection patchCord188(pl1amp, pl1FX2);
AudioConnection patchCord189(pl1amp, pl1FX3);
AudioConnection patchCord190(pl14FX3, 0, FX3mixer6, 1);
AudioConnection patchCord191(pl14FX2, 0, FX2mixer6, 1);
AudioConnection patchCord192(pl14dry, 0, drymixer3, 1);
AudioConnection patchCord193(pl8dry, 0, mixer6, 3);
AudioConnection patchCord194(pl8FX1, 0, FX1mixer2, 3);
AudioConnection patchCord195(pl10dry, 0, mixer10, 1);
AudioConnection patchCord196(pl14FX1, 0, FX1mixer6, 1);
AudioConnection patchCord197(pl8FX2, 0, FX2mixer2, 3);
AudioConnection patchCord198(pl8FX3, 0, FX3mixer2, 3);
AudioConnection patchCord199(pl10FX1, 0, FX1mixer4, 1);
AudioConnection patchCord200(pl10FX2, 0, FX2mixer4, 1);
AudioConnection patchCord201(pl16FX3, 0, FX3mixer6, 3);
AudioConnection patchCord202(pl10FX3, 0, FX3mixer4, 1);
AudioConnection patchCord203(pl13FX3, 0, FX3mixer6, 0);
AudioConnection patchCord204(pl16FX2, 0, FX2mixer6, 3);
AudioConnection patchCord205(pl13FX2, 0, FX2mixer6, 0);
AudioConnection patchCord206(pl16dry, 0, drymixer3, 3);
AudioConnection patchCord207(pl9dry, 0, mixer10, 0);
AudioConnection patchCord208(pl16FX1, 0, FX1mixer6, 3);
AudioConnection patchCord209(pl9FX1, 0, FX1mixer4, 0);
AudioConnection patchCord210(pl9FX2, 0, FX2mixer4, 0);
AudioConnection patchCord211(pl13dry, 0, drymixer3, 0);
AudioConnection patchCord212(pl11dry, 0, mixer10, 2);
AudioConnection patchCord213(pl13FX1, 0, FX1mixer6, 0);
AudioConnection patchCord214(pl11FX2, 0, FX2mixer4, 2);
AudioConnection patchCord215(pl11FX3, 0, FX3mixer4, 2);
AudioConnection patchCord216(pl9FX3, 0, FX3mixer4, 0);
AudioConnection patchCord217(pl12dry, 0, mixer10, 3);
AudioConnection patchCord218(pl11FX1, 0, FX1mixer4, 2);
AudioConnection patchCord219(pl15FX3, 0, FX3mixer6, 2);
AudioConnection patchCord220(pl15FX2, 0, FX2mixer6, 2);
AudioConnection patchCord221(pl7dry, 0, mixer6, 2);
AudioConnection patchCord222(pl7FX2, 0, FX2mixer2, 2);
AudioConnection patchCord223(pl7FX3, 0, FX3mixer2, 2);
AudioConnection patchCord224(pl15dry, 0, drymixer3, 2);
AudioConnection patchCord225(pl7FX1, 0, FX1mixer2, 2);
AudioConnection patchCord226(pl15FX1, 0, FX1mixer6, 2);
AudioConnection patchCord227(pl12FX1, 0, FX1mixer4, 3);
AudioConnection patchCord228(pl12FX2, 0, FX2mixer4, 3);
AudioConnection patchCord229(pl3dry, 0, mixer5, 2);
AudioConnection patchCord230(pl3FX1, 0, FX1mixer1, 2);
AudioConnection patchCord231(pl3FX2, 0, FX2mixer1, 2);
AudioConnection patchCord232(pl12FX3, 0, FX3mixer4, 3);
AudioConnection patchCord233(pl3FX3, 0, FX3mixer1, 2);
AudioConnection patchCord234(pl6FX1, 0, FX1mixer2, 1);
AudioConnection patchCord235(pl6dry, 0, mixer6, 1);
AudioConnection patchCord236(pl6FX2, 0, FX2mixer2, 1);
AudioConnection patchCord237(pl5FX3, 0, FX3mixer2, 0);
AudioConnection patchCord238(pl6FX3, 0, FX3mixer2, 1);
AudioConnection patchCord239(pl5FX1, 0, FX1mixer2, 0);
AudioConnection patchCord240(pl5dry, 0, mixer6, 0);
AudioConnection patchCord241(pl5FX2, 0, FX2mixer2, 0);
AudioConnection patchCord242(pl1FX3, 0, FX3mixer1, 0);
AudioConnection patchCord243(pl1dry, 0, mixer5, 0);
AudioConnection patchCord244(pl1FX1, 0, FX1mixer1, 0);
AudioConnection patchCord245(pl1FX2, 0, FX2mixer1, 0);
AudioConnection patchCord246(mixer6, 0, drymixer2, 1);
AudioConnection patchCord247(FX2mixer1, 0, FX2mixer3, 0);
AudioConnection patchCord248(mixer5, 0, drymixer2, 0);
AudioConnection patchCord249(FX3mixer2, 0, FX3mixer3, 1);
AudioConnection patchCord250(FX1mixer1, 0, FX1mixer3, 0);
AudioConnection patchCord251(FX2mixer2, 0, FX2mixer3, 1);
AudioConnection patchCord252(FX1mixer2, 0, FX1mixer3, 1);
AudioConnection patchCord253(FX3mixer1, 0, FX3mixer3, 0);
AudioConnection patchCord254(FX2mixer4, 0, FX2mixer3, 2);
AudioConnection patchCord255(FX1mixer6, 0, FX1mixer3, 3);
AudioConnection patchCord256(drymixer3, 0, drymixer2, 3);
AudioConnection patchCord257(FX3mixer6, 0, FX3mixer3, 3);
AudioConnection patchCord258(FX2mixer6, 0, FX2mixer3, 3);
AudioConnection patchCord259(FX3mixer4, 0, FX3mixer3, 2);
AudioConnection patchCord260(FX1mixer4, 0, FX1mixer3, 2);
AudioConnection patchCord261(mixer10, 0, drymixer2, 2);
AudioConnection patchCord262(drymixer2, 0, drymixer1, 0);
AudioConnection patchCord263(FX2mixer3, 0, FX2mixer5, 0);
AudioConnection patchCord264(FX3mixer3, 0, FX3mixer5, 0);
AudioConnection patchCord265(FX1mixer3, 0, FX1mixer5, 0);
AudioConnection patchCord266(FX3mixer5, 0, dlmixer1, 0);
AudioConnection patchCord267(drymixer1, 0, mixer9, 0);
AudioConnection patchCord268(FX1mixer5, reverb1);
AudioConnection patchCord269(FX2mixer5, bitcrusher2);
AudioConnection patchCord270(reverb1, 0, mixer9, 1);
AudioConnection patchCord271(bitcrusher2, 0, mixer9, 2);
AudioConnection patchCord272(dlfilter1, 2, dlmixer1, 1);
AudioConnection patchCord273(dlmixer1, dldelay1);
AudioConnection patchCord274(dlmixer1, 0, mixer9, 3);
AudioConnection patchCord275(dldelay1, 0, dlfilter1, 0);
AudioConnection patchCord276(i2s2, 0, amp1, 0);
AudioConnection patchCord277(mixer9, 0, mixer11, 0);
AudioConnection patchCord278(amp1, 0, mixer11, 1);
AudioConnection patchCord279(amp1, queue1);
AudioConnection patchCord280(amp1, peak1);
AudioConnection patchCord281(mixer11, 0, i2s1, 0);
AudioConnection patchCord282(mixer11, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=2645.5000286102295,809.0000114440918
// GUItool: end automatically generated code






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

AudioEffectEnvelope *ENVELOPE1[5] {&envelope1, &pl3envelope1, &pl5envelope1, &pl6envelope1, &pl8envelope1}; //pl1, pl3, pl5, pl6, pl8
AudioEffectEnvelope *ENVELOPE2[5] {&envelope2, &pl3envelope2, &pl5envelope2, &pl6envelope2, &pl8envelope2}; //pl1, pl3, pl5, pl6, pl8

AudioFilterStateVariable *STATEFILTER[4]{&filter1, &pl3filter1, &pl5filter1, &pl6filter1}; //pl1, pl3, pl5, pl6
AudioFilterLadder *LADDERFILTER[1]{&pl8filter1}; //pl8

AudioMixer4 *PL2MIX[3]{&drummixer1, &drummixer1,&drummixer1};
AudioMixer4 *PL4MIX[3]{&pl4drummixer1, &pl4drummixer1,&pl4drummixer1};


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



  AudioMemory(AUDIO_MEMORYS);
  Serial.print("Initializing AudioMemory = ");
  Serial.println(AUDIO_MEMORYS);
  tft.print("Initializing AudioMemory = ");
  tft.println(AUDIO_MEMORYS);

  //tft.updateScreen();
  delay(100);




  // start sequencer and set callbacks and load big arrays

  Serial.println("Initializing Sequencer");
  tft.println("Initializing Sequencer");
  // Allocate channel1Clip array during runtime

  channel1Clip = new bool **[NUM_CLIPS];
  for (int i = 0; i < NUM_CLIPS; i++) {
    channel1Clip[i] = new bool *[num_voice];
    for (int j = 0; j < num_voice; j++) {
      channel1Clip[i][j] = new bool[STEP_QUANT];
    }
  }
  // fill the array
  for (int i = 0; i < NUM_CLIPS; i++) {
    for (int j = 0; j < num_voice; j++) {
      for (int k = 0; k < STEP_QUANT; k++) {
        channel1Clip[i][j][k] = 0;
      }
    }
  }

  //ratcheting array
  ratchet = new bool **[NUM_CLIPS];
  for (int i = 0; i < NUM_CLIPS; i++) {
    ratchet[i] = new bool *[num_voice];
    for (int j = 0; j < num_voice; j++) {
      ratchet[i][j] = new bool[STEP_QUANT];
    }
  }
  // fill the array
  for (int i = 0; i < NUM_CLIPS; i++) {
    for (int j = 0; j < num_voice; j++) {
      for (int k = 0; k < STEP_QUANT; k++) {
        ratchet[i][j][k] = 0;
      }
    }
  }
  // Allocate dsend_noteOff array during runtime
  dsend_noteOff = new bool[num_voice];
  //tft.updateScreen();
  //allocate tracks
  track = new tracks[NUM_TRACKS];
  //ctrack = new track_t[NUM_TRACKS];
  //allocate plugins
  pl1 = new plugin1[MAX_PRESETS];
  pl2 = new plugin2[MAX_PRESETS];
  pl3 = new plugin3[MAX_PRESETS];
  pl4 = new plugin4[MAX_PRESETS];
  pl5 = new plugin5[MAX_PRESETS];
  pl6 = new plugin6[MAX_PRESETS];
  pl7 = new plugin7[MAX_PRESETS];
  pl8 = new plugin8[MAX_PRESETS];
  pl9 = new plugin9[MAX_PRESETS];
  //allocate NFX1
  NFX1 = new Grids[MAX_PRESETS];
  //allocate NFX2
  NFX2 = new Drops[MAX_PRESETS];
  //allocate NFX3
  NFX3 = new rands[MAX_PRESETS];
  //allocate NFX4
  NFX4 = new PolyR[MAX_PRESETS];
  //allocate NFX5
  NFX5 = new Ratch[MAX_PRESETS];
  //allocate LaunchPad arrays
  LP_grid_notes = new byte[64];
  for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 8; c++) {
      LP_grid_notes[r + (c * 8)] = r + (c * 16);
    }
  }

  LP_step_notes = new byte[16];
  for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 2; c++) {
      LP_step_notes[r + (c * 8)] = (r + 16) + (c * 16);
    }
  }
  note_frequency = new float[128];
  for (int r = 0; r < 128; r++) {
    note_frequency[r] = pow(2.0, ((double)(r - SAMPLE_ROOT) / 12.0)) * 440;
  }
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
  Plugin7_Settings();
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
  FX3Delay_settings();
  clearArrangment();
  Serial.println("Initializing Track- and Pluginsettings");
  tft.println("Initializing Track- and Pluginsettings");
  for (int pluginn = 0; pluginn < MAX_PLUGINS; pluginn++) {
    dryVolume[pluginn]->gain(1);
    FX1Volume[pluginn]->gain(0);
    FX2Volume[pluginn]->gain(0);
    FX3Volume[pluginn]->gain(0);
  }


  //tft.updateScreen();
  delay(100);




  Serial.println("Initializing Buttons");
  tft.println("Initializing Buttons");
  kpd.begin();
  long positionEnc[4] = { -999, -999, -999, -999 };
  pinMode(30, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
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

  for (int pixelX = 0; pixelX < 16; pixelX++) {
    for (int pixelY = 0; pixelY < 16; pixelY++) {
      tftRAM[pixelX][pixelY] = tft.readPixel(pixelX, pixelY);
    }
  }
  bmpDraw("StartUpPic.bmp", 0, 0);
  delay(4000);  //just to look how beautiful this image is
  tft.fillScreen(ILI9341_DARKGREY);
  startUpScreen();
  delay(500);

  drumStepSequencer_Static();
  //tft.updateScreen();
}

elapsedMillis msecs;
elapsedMicros msecsclock;
long oldEnc[4] = { -999, -999, -999, -999 };


void SerialPrintSeq() {

  Serial.print(tempo);
  Serial.print("-");
  Serial.print(tick_16);
  Serial.print("-   ");

  for (int i = 0; i < 12; i++) {
    Serial.print(drumnotes[i]);
    Serial.print("-");
  }

  Serial.print("-   ");

  for (int desired_tracks = 1; desired_tracks < 8; desired_tracks++) {
    Serial.print(track[desired_tracks].notePlayed);
    Serial.print("-");
    Serial.print(track[desired_tracks].envActive);
    Serial.print("-   ");
  }
  debug_free_ram();
}
void SerialPrintPlugins() {
  Serial.print("PL1");
  Serial.print("-   ");
  Serial.print("note: ");
  Serial.print(pl1[pl1presetNr].note_Offset_graph[0]);
  Serial.print("-");
  Serial.print(pl1[pl1presetNr].note_Offset_graph[1]);
  Serial.print("-");
  Serial.print(pl1[pl1presetNr].note_Offset_graph[2]);
  Serial.print("-");
  Serial.print(pl1[pl1presetNr].note_Offset_graph[3]);
  Serial.print("   ");
  Serial.print("W~F: ");
  Serial.print(pl1[pl1presetNr].wfSelect[0]);
  Serial.print("-");
  Serial.print(pl1[pl1presetNr].wfSelect[1]);
  Serial.print("-");
  Serial.print(pl1[pl1presetNr].wfSelect[2]);
  Serial.print("-");
  Serial.print(pl1[pl1presetNr].wfSelect[3]);
  Serial.print("   ");
  Serial.print("Velo: ");
  Serial.print(pl1[pl1presetNr].note_Velo_graph[0]);
  Serial.print("-");
  Serial.print(pl1[pl1presetNr].note_Velo_graph[1]);
  Serial.print("-");
  Serial.print(pl1[pl1presetNr].note_Velo_graph[2]);
  Serial.print("-");
  Serial.print(pl1[pl1presetNr].note_Velo_graph[3]);
  Serial.print("     ");
  Serial.print("Filter: ");
  Serial.print(pl1[pl1presetNr].Pot_Value[0]);
  Serial.print("-");
  Serial.print(pl1[pl1presetNr].Pot_Value[1]);
  Serial.print("-");
  Serial.print(pl1[pl1presetNr].Pot_Value[2]);
  Serial.print("-");
  Serial.print(pl1[pl1presetNr].Pot_Value[3]);
  Serial.print("   ");
  Serial.print("ADSR: ");
  Serial.print(pl1[pl1presetNr].Pot_Value[4]);
  Serial.print("-");
  Serial.print(pl1[pl1presetNr].Pot_Value[5]);
  Serial.print("-");
  Serial.print(pl1[pl1presetNr].Pot_Value[6]);
  Serial.print("-");
  Serial.print(pl1[pl1presetNr].Pot_Value[7]);

  Serial.println();

  Serial.print("PL2");
  Serial.print("-   ");
  Serial.print(pl2[pl2presetNr].Pot_Value[0]);
  Serial.print("-");
  Serial.print(pl2[pl2presetNr].Pot_Value[1]);
  Serial.print("-");
  Serial.print(pl2[pl2presetNr].Pot_Value[2]);
  Serial.print("-");
  Serial.print(pl2[pl2presetNr].Pot_Value[3]);
  Serial.print("  ");
  Serial.print(pl2[pl2presetNr].Pot_Value[4]);
  Serial.print("-");
  Serial.print(pl2[pl2presetNr].Pot_Value[5]);
  Serial.print("-");
  Serial.print(pl2[pl2presetNr].Pot_Value[6]);
  Serial.print("-");
  Serial.print(pl2[pl2presetNr].Pot_Value[7]);
  Serial.print("  ");
  Serial.print(pl2[pl2presetNr].Pot_Value[8]);
  Serial.print("-");
  Serial.print(pl2[pl2presetNr].Pot_Value[9]);
  Serial.print("-");
  Serial.print(pl2[pl2presetNr].Pot_Value[10]);
  Serial.print("-");
  Serial.print(pl2[pl2presetNr].Pot_Value[11]);
  Serial.println();

  Serial.print("PL3");
  Serial.print("-   ");
  Serial.print("W~F: ");
  Serial.print(pl3[pl3presetNr].Pot_Value[0]);
  Serial.print("   ");
  Serial.print("Filter: ");
  Serial.print(pl3[pl3presetNr].Pot_Value[4]);
  Serial.print("-");
  Serial.print(pl3[pl3presetNr].Pot_Value[5]);
  Serial.print("-");
  Serial.print(pl3[pl3presetNr].Pot_Value[6]);
  Serial.print("-");
  Serial.print(pl3[pl3presetNr].Pot_Value[7]);
  Serial.print("   ");
  Serial.print("ADSR: ");
  Serial.print(pl3[pl3presetNr].Pot_Value[8]);
  Serial.print("-");
  Serial.print(pl3[pl3presetNr].Pot_Value[9]);
  Serial.print("-");
  Serial.print(pl3[pl3presetNr].Pot_Value[10]);
  Serial.print("-");
  Serial.print(pl3[pl3presetNr].Pot_Value[11]);
  Serial.println();

  Serial.print("PL4");
  Serial.print("-   ");
  Serial.print(pl4[pl4presetNr].Pot_Value_graph[0]);
  Serial.print("-");
  Serial.print(pl4[pl4presetNr].Pot_Value_graph[1]);
  Serial.print("-");
  Serial.print(pl4[pl4presetNr].Pot_Value_graph[2]);
  Serial.print("-");
  Serial.print(pl4[pl4presetNr].Pot_Value_graph[3]);
  Serial.print("  ");
  Serial.print(pl4[pl4presetNr].Pot_Value_graph[4]);
  Serial.print("-");
  Serial.print(pl4[pl4presetNr].Pot_Value_graph[5]);
  Serial.print("-");
  Serial.print(pl4[pl4presetNr].Pot_Value_graph[6]);
  Serial.print("-");
  Serial.print(pl4[pl4presetNr].Pot_Value_graph[7]);
  Serial.print("  ");
  Serial.print(pl4[pl4presetNr].Pot_Value_graph[8]);
  Serial.print("-");
  Serial.print(pl4[pl4presetNr].Pot_Value_graph[9]);
  Serial.print("-");
  Serial.print(pl4[pl4presetNr].Pot_Value_graph[10]);
  Serial.print("-");
  Serial.print(pl4[pl4presetNr].Pot_Value_graph[11]);
  Serial.println();

  Serial.print("PL8");
  Serial.print("-   ");
  Serial.print("W~F: ");
  Serial.print(pl8[pl8presetNr].Pot_Value[0]);
  Serial.print("   ");
  Serial.print("Filter: ");
  Serial.print(pl8[pl8presetNr].Pot_Value[4]);
  Serial.print("-");
  Serial.print(pl8[pl8presetNr].Pot_Value[5]);
  Serial.print("-");
  Serial.print(pl8[pl8presetNr].Pot_Value[6]);
  Serial.print("   ");
  Serial.print("ADSR: ");
  Serial.print(pl8[pl8presetNr].Pot_Value[8]);
  Serial.print("-");
  Serial.print(pl8[pl8presetNr].Pot_Value[9]);
  Serial.print("-");
  Serial.print(pl8[pl8presetNr].Pot_Value[10]);
  Serial.print("-");
  Serial.print(pl8[pl8presetNr].Pot_Value[11]);
  Serial.println();


  showSerialonce = false;
}
int freeRam() {
  return (char *)&_heap_end - __brkval;
}

void debug_free_ram() {
  Serial.printf(F("debug_free_ram: %i\n"), freeRam());
}
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
  midi07.read();
  midi08.read();
  midi09.read();
  midi10.read();
  detect_and_assign_midi_devices();
  kpd.tick();
  sendClock();
  step();

  readMainButtons();
  readEncoders();
  Plugin_View_Dynamic();
  DrumPluginPlay();
  PluginNoteOn();
  PluginNoteOff();

  otherCtrlButtons = (!button[8] && !button[9] && !button[10] && !button[11] && !button[12]);
  /* if (digitalRead(5)) {
    tick_16++;
  }*/

  //assigning the current clip/noteoffset/presets/Volume from the arrangment array for each track
  if (seq_run) {
  }

  if (msecs % 100 == 0) {
    //Serial.print(Potentiometer[0]);
    //Serial.print("-");
    //Serial.println(pl1[0].note_Offset[0]);
  }


  TS_Point p = ts.getPoint();
  if (ts.touched()) {
    gridTouchX = map(p.x, TS_MINX, TS_MAXX, 0, 19);
    gridTouchY = map(p.y, TS_MINY, TS_MAXY, 0, 14);
    trackTouchY = map(p.y, 800, 3200, 0, 7);
  }
  if (gridTouchY == 1) trackTouchY = 0;
  if (gridTouchY == 3) trackTouchY = 1;
  if (gridTouchY == 4) trackTouchY = 2;
  if (gridTouchY == 6) trackTouchY = 3;
  if (gridTouchY == 7) trackTouchY = 4;
  if (gridTouchY == 9) trackTouchY = 5;
  if (gridTouchY == 10) trackTouchY = 6;
  if (gridTouchY == 12) trackTouchY = 7;

  if (ts.touched() || button[15]) {
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
        selectPage = 10;
        gridSongMode(songpageNumber);
      }
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // assign trackcolours
      for (int tracks = 0; tracks < 4; tracks++) {
        tft.setFont(Arial_9);
        tft.setTextColor(ILI9341_BLACK);
        if (trackTouchY == tracks) {

          if (enc_moved[0]) {
            trackColor[tracks] = constrain((trackColor[tracks] + (encoded[0])), 0, 16777215);
            if (tracks == 0) {
              //Drumtrack button
              tft.fillRect(1, STEP_FRAME_H, 15, TRACK_FRAME_H, trackColor[0]);  //Xmin, Ymin, Xlength, Ylength, color
              tft.setCursor(4, TRACK_FRAME_H);
              tft.print("D");
            } else {
              //other tracks buttons

              tft.fillRect(1, TRACK_FRAME_H * (tracks + 1) - 8, 15, TRACK_FRAME_H, trackColor[tracks]);  //Xmin, Ymin, Xlength, Ylength, color
              tft.setCursor(4, TRACK_FRAME_H * (tracks + 1));
              tft.print(tracks + 1);
            }
          }
        }
        if (trackTouchY == tracks + 4) {

          if (enc_moved[0]) {
            trackColor[tracks + 4] = constrain((trackColor[tracks + 4] + (encoded[0])), 0, 16777215);

            //other tracks buttons

            tft.fillRect(1, TRACK_FRAME_H * ((tracks + 1) + 4) - 8, 15, TRACK_FRAME_H, trackColor[tracks + 4]);  //Xmin, Ymin, Xlength, Ylength, color
            tft.setCursor(4, TRACK_FRAME_H * ((tracks + 1) + 4));
            tft.print(tracks + 5);
          }
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
        gridTouchX = constrain(gridTouchX - 1, 0, 19);
        drawCursor();
        showCoordinates();
      }
      //cursor right
      if (otherCtrlButtons && key.bit.KEY == 70) {  //"F"  70 2nd button
        gridTouchX = constrain(gridTouchX + 1, 0, 19);
        drawCursor();
        showCoordinates();
      }
      //cursor up
      if (otherCtrlButtons && key.bit.KEY == 57) {  //"9"   57 3rd button
        gridTouchY = constrain(gridTouchY - 1, 0, 14);
        drawCursor();
        showCoordinates();
        //something_was_pressed = true;
      }
      //cursor down
      if (otherCtrlButtons && key.bit.KEY == 66) {  //"B"   66 4th button
        gridTouchY = constrain(gridTouchY + 1, 0, 14);
        drawCursor();
        showCoordinates();
        //something_was_pressed = true;
      }
      //last-pot-row
      if (otherCtrlButtons && key.bit.KEY == 55) {  //"B"   66 5th button
        lastPotRow++;

        if (lastPotRow >= 4) {
          lastPotRow = 0;
        }

        if (lastPotRow >= 4) {
          tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
        }
        tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
        tft.fillRect(70, lastPotRow * 4, 10, 3, ILI9341_RED);
      }

      //recbutton
      if (otherCtrlButtons && key.bit.KEY == 53) {  //"5" 53
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
      if (otherCtrlButtons && key.bit.KEY == 51) {  //"3" 51
        startSeq();
      }
      //stopbutton
      if (otherCtrlButtons && key.bit.KEY == 49) {  //"1" 49
        stopSeq();
      }


      //select tracks
      if (button[8]) {            //9th button
        if (key.bit.KEY == 68) {  //"D"  68  1st button
          selectPage = DRUMTRACK;
          desired_instrument = 0;
          desired_track = 0;
          drumStepSequencer_Static();
        }
        //select melodic track 2
        if (key.bit.KEY == 70) {  //"F"  70 2nd button
          selectPage = 1;
          desired_instrument = 1;
          desired_track = 1;
          gridStepSequencer(1);
        }
        //select melodic track 3
        if (key.bit.KEY == 57) {  //"9"  57 3rd button
          selectPage = 2;
          desired_instrument = 2;
          desired_track = 2;
          gridStepSequencer(2);
        }
        //select melodic track 4
        if (key.bit.KEY == 66) {  //"B"  66 4th button
          selectPage = 3;
          desired_instrument = 3;
          desired_track = 3;
          gridStepSequencer(3);
        }
        //select melodic track 5
        if (key.bit.KEY == 55) {  //"7"  55 5th button
          selectPage = 4;
          desired_instrument = 4;
          desired_track = 4;
          gridStepSequencer(4);
        }
        //select melodic track 6
        if (key.bit.KEY == 53) {  //"5"  53 6th button
          selectPage = 5;
          desired_instrument = 5;
          desired_track = 5;
          gridStepSequencer(5);
        }
        //select melodic track 7
        if (key.bit.KEY == 51) {  //"3"  51 7th button
          selectPage = 6;
          desired_instrument = 6;
          desired_track = 6;
          gridStepSequencer(6);
        }
        //select melodic track 8
        if (key.bit.KEY == 49) {  //"1"  49 8th button
          selectPage = 7;
          desired_instrument = 7;
          desired_track = 7;
          gridStepSequencer(7);
        }
      }
      //plugin selection
      if (button[9]) {
        if (key.bit.KEY == 68) {  //"D"  68  1st button
          desired_track = 0;
          desired_instrument = 0;
          //midicc_view
          for (int pluginSelection = 0; pluginSelection <= MAX_PLUGINS; pluginSelection++) {
            if (track[desired_instrument].MIDIchannel == pluginSelection) {
              selectPage = MIDICC_PAGE_1;
              midiCC_view_Static(0, desired_track);
            }
            //plugin_1_view
            if (track[desired_instrument].MIDIchannel == pluginSelection + 17) {
              selectPage = pluginSelection + 40;
              Plugin_View_Static();
            }
          }
        }
        if (key.bit.KEY == 70) {
          desired_track = 1;
          desired_instrument = 1;
          //midicc_view
          for (int pluginSelection = 0; pluginSelection <= MAX_PLUGINS; pluginSelection++) {
            if (track[desired_instrument].MIDIchannel == pluginSelection) {
              selectPage = MIDICC_PAGE_1;
              midiCC_view_Static(0, desired_track);
            }
            //plugin_1_view
            if (track[desired_instrument].MIDIchannel == pluginSelection + 17) {
              selectPage = pluginSelection + 40;
              Plugin_View_Static();
            }
          }
        }
        if (key.bit.KEY == 57) {
          desired_track = 2;
          desired_instrument = 2;
          //midicc_view
          for (int pluginSelection = 0; pluginSelection <= MAX_PLUGINS; pluginSelection++) {
            if (track[desired_instrument].MIDIchannel == pluginSelection) {
              selectPage = MIDICC_PAGE_1;
              midiCC_view_Static(0, desired_track);
            }
            //plugin_1_view
            if (track[desired_instrument].MIDIchannel == pluginSelection + 17) {
              selectPage = pluginSelection + 40;
              Plugin_View_Static();
            }
          }
        }
        if (key.bit.KEY == 66) {
          desired_track = 3;
          desired_instrument = 3;
          //midicc_view
          for (int pluginSelection = 0; pluginSelection <= MAX_PLUGINS; pluginSelection++) {
            if (track[desired_instrument].MIDIchannel == pluginSelection) {
              selectPage = MIDICC_PAGE_1;
              midiCC_view_Static(0, desired_track);
            }
            //plugin_1_view
            if (track[desired_instrument].MIDIchannel == pluginSelection + 17) {
              selectPage = pluginSelection + 40;
              Plugin_View_Static();
            }
          }
        }
        if (key.bit.KEY == 55) {
          desired_track = 4;
          desired_instrument = 4;
          //midicc_view
          for (int pluginSelection = 0; pluginSelection <= MAX_PLUGINS; pluginSelection++) {
            if (track[desired_instrument].MIDIchannel == pluginSelection) {
              selectPage = MIDICC_PAGE_1;
              midiCC_view_Static(0, desired_track);
            }
            //plugin_1_view
            if (track[desired_instrument].MIDIchannel == pluginSelection + 17) {
              selectPage = pluginSelection + 40;
              Plugin_View_Static();
            }
          }
        }
        if (key.bit.KEY == 53) {
          desired_track = 5;
          desired_instrument = 5;
          //midicc_view
          for (int pluginSelection = 0; pluginSelection <= MAX_PLUGINS; pluginSelection++) {
            if (track[desired_instrument].MIDIchannel == pluginSelection) {
              selectPage = MIDICC_PAGE_1;
              midiCC_view_Static(0, desired_track);
            }
            //plugin_1_view
            if (track[desired_instrument].MIDIchannel == pluginSelection + 17) {
              selectPage = pluginSelection + 40;
              Plugin_View_Static();
            }
          }
        }
        if (key.bit.KEY == 51) {
          desired_track = 6;
          desired_instrument = 6;
          //midicc_view
          for (int pluginSelection = 0; pluginSelection <= MAX_PLUGINS; pluginSelection++) {
            if (track[desired_instrument].MIDIchannel == pluginSelection) {
              selectPage = MIDICC_PAGE_1;
              midiCC_view_Static(0, desired_track);
            }
            //plugin_1_view
            if (track[desired_instrument].MIDIchannel == pluginSelection + 17) {
              selectPage = pluginSelection + 40;
              Plugin_View_Static();
            }
          }
        }
        if (key.bit.KEY == 49) {
          desired_track = 7;
          desired_instrument = 7;
          //midicc_view
          for (int pluginSelection = 0; pluginSelection <= MAX_PLUGINS; pluginSelection++) {
            if (track[desired_instrument].MIDIchannel == pluginSelection) {
              selectPage = MIDICC_PAGE_1;
              midiCC_view_Static(0, desired_track);
            }
            //plugin_1_view
            if (track[desired_instrument].MIDIchannel == pluginSelection + 17) {
              selectPage = pluginSelection + 40;
              Plugin_View_Static();
            }
          }
        }
      }
      //  select Songarranger page 11 & button[10]
      if (key.bit.KEY == 65) {  //"A"  65
        button[10] = true;
        selectPage = SONGMODE_PAGE_11;
        gridSongMode(10);
      }
      if (button[10]) {  //"A"  65
        if (key.bit.KEY == 68) {
          selectPage = SONGMODE_PAGE_1;
          gridSongMode(0);
          songModePage(0);
        }
        if (key.bit.KEY == 70) {
          selectPage = SONGMODE_PAGE_2;
          gridSongMode(1);
          songModePage(1);
        }
        if (key.bit.KEY == 57) {
          selectPage = SONGMODE_PAGE_3;
          gridSongMode(2);
          songModePage(2);
        }
        if (key.bit.KEY == 66) {
          selectPage = SONGMODE_PAGE_4;
          gridSongMode(3);
          songModePage(3);
        }
        if (key.bit.KEY == 55) {
          selectPage = SONGMODE_PAGE_5;
          gridSongMode(4);
          songModePage(4);
        }
        if (key.bit.KEY == 53) {
          selectPage = SONGMODE_PAGE_6;
          gridSongMode(5);
          songModePage(5);
        }
        if (key.bit.KEY == 51) {
          selectPage = SONGMODE_PAGE_7;
          gridSongMode(6);
          songModePage(6);
        }
        if (key.bit.KEY == 49) {
          selectPage = SONGMODE_PAGE_8;
          gridSongMode(7);
          songModePage(7);
        }
        if (key.bit.KEY == 69) {
          selectPage = SONGMODE_PAGE_9;
          gridSongMode(8);
          songModePage(8);
        }
        if (key.bit.KEY == 67) {
          selectPage = SONGMODE_PAGE_10;
          gridSongMode(9);
          songModePage(9);
        }
        if (key.bit.KEY == 56) {
          selectPage = SONGMODE_PAGE_12;
          gridSongMode(11);
          songModePage(11);
        }
        if (key.bit.KEY == 52) {
          selectPage = SONGMODE_PAGE_13;
          gridSongMode(12);
          songModePage(12);
        }
        if (key.bit.KEY == 54) {
          selectPage = SONGMODE_PAGE_14;
          gridSongMode(13);
          songModePage(13);
        }
        if (key.bit.KEY == 50) {
          selectPage = SONGMODE_PAGE_15;
          gridSongMode(14);
          songModePage(14);
        }
        if (key.bit.KEY == 48) {
          selectPage = SONGMODE_PAGE_16;
          gridSongMode(15);
          songModePage(15);
        }
      }
      //  select Mixer
      if (button[11]) {           //"8"  56
        if (key.bit.KEY == 68) {  //"D"  68
          selectPage = MIXER_PAGE_1;
          mixerPage1_Static(0);
        }
        //select melodic track 2
        if (key.bit.KEY == 70) {  //"F"  70
          selectPage = MIXER_PAGE_2;
          mixerPage2_Static();
        }
        //select melodic track 3
        if (key.bit.KEY == 57) {  //"9"  57
          selectPage = MIXER_PAGE_3;
          mixerPage3_Static();
        }
      }
      //FX Selection
      if (button[12]) {
        if (key.bit.KEY == 68) {
          selectPage = FX1_PAGE1;
          FX1reverb_static();
        }
        if (key.bit.KEY == 70) {
          selectPage = FX2_PAGE1;
          FX2Bitcrush_static();
        }
        if (key.bit.KEY == 57) {
          //delay
          selectPage = FX3_PAGE1;
          FX3Delay_static();
        }
        if (key.bit.KEY == 55) {
          if (track[desired_instrument].seqMode == 1) {
            selectPage = NFX1_PAGE1;
            NoteFX1_Page_Static();
          }
          if (track[desired_instrument].seqMode == 2) {
            selectPage = NFX2_PAGE1;
            NoteFX2_Page_Static();
          }
          if (track[desired_instrument].seqMode == 3) {
            selectPage = NFX3_PAGE1;
            NoteFX3_Page_Static();
          }
          if (track[desired_instrument].seqMode == 4) {
            selectPage = NFX4_PAGE1;
            NoteFX4_Page_Static();
          }
          if (track[desired_instrument].seqMode == 5) {
            selectPage = NFX5_PAGE1;
            NoteFX5_Page_Static();
          }
        }
      }
      //recorder
      if (!button[10] && key.bit.KEY == 54) {  // 14th button
        selectPage = RECORDER_PAGE;
        recorder_Page_Static();
      }




      // hold for track button
      if (!button[10] && key.bit.KEY == 69) {  //"E"  69
        button[8] = true;
      }
      // hold for plugin button
      if (!button[10] && key.bit.KEY == 67) {  //"C"  67
        button[9] = true;
      }
      // hold for Mixer button
      if (!button[10] && key.bit.KEY == 56) {  //"4"  52
        button[11] = true;
      }
      // hold for FX button
      if (!button[10] && key.bit.KEY == 52) {  //"8"  56
        button[12] = true;
      }
      // hold for cursor via pot
      if (!button[10] && key.bit.KEY == 54) {
        button[13] = true;
      }
      // hold for cursor via pot
      if (!button[10] && key.bit.KEY == 50) {
        button[14] = true;
      }
      // hold for enter button
      if (!button[10] && key.bit.KEY == 48) {
        button[15] = true;
      }
    } else if (key.bit.EVENT == KEY_JUST_RELEASED) {
      //tft.updateScreen();
      // release for track button
      if (key.bit.KEY == 69) {  //"E"  69
        button[8] = false;
      }
      // release for plugin button
      if (key.bit.KEY == 67) {  //"C"  67
        button[9] = false;
      }
      // release for arranger button
      if (key.bit.KEY == 65) {  //"A"  65
        button[10] = false;
      }
      // hold for mixer button
      if (key.bit.KEY == 56) {  //"8"  56
        button[11] = false;
      }
      // release for FX button
      if (key.bit.KEY == 52) {  //"4"  52
        button[12] = false;
      }
      // rel for cursor via pot
      if (!button[10] && key.bit.KEY == 54) {
        button[13] = false;
      }
      //release for cursor via pot
      if (key.bit.KEY == 50) {
        button[14] = false;
      }
      //release for enter button
      if (key.bit.KEY == 48) {
        button[15] = false;
      }
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
  if (!digitalRead(30)) {
    enc_button[0] = true;
  } else {
    enc_button[0] = false;
  }
  if (!digitalRead(29)) {
    enc_button[1] = true;
  } else {
    enc_button[1] = false;
  }
  if (!digitalRead(26)) {
    enc_button[2] = true;
  } else {
    enc_button[2] = false;
  }
  if (!digitalRead(4)) {
    enc_button[3] = true;
  } else {
    enc_button[3] = false;
  }
  for (int encoders = 0; encoders < 4; encoders++) {
    if (enc_button[encoders]) {
      if (newEnc[encoders] > oldEnc[encoders]) {
        enc_moved[encoders] = true;
        encoded[encoders] = 8;
        oldEnc[encoders] = newEnc[encoders];
      }
      if (newEnc[encoders] < oldEnc[encoders]) {
        enc_moved[encoders] = true;
        encoded[encoders] = -8;
        oldEnc[encoders] = newEnc[encoders];
      }
    } else {
      if (newEnc[encoders] > oldEnc[encoders]) {
        enc_moved[encoders] = true;
        encoded[encoders] = 1;
        oldEnc[encoders] = newEnc[encoders];
      }
      if (newEnc[encoders] < oldEnc[encoders]) {
        enc_moved[encoders] = true;
        encoded[encoders] = -1;
        oldEnc[encoders] = newEnc[encoders];
      }
    }
  }
}

void drawCursor() {

  for (int pixel = 0; pixel < 16; pixel++) {
    tft.drawPixel(pixel + (STEP_FRAME_W * last_button_X), (STEP_FRAME_H * last_button_Y) + 1, tftRAM[0][pixel]);
    tft.drawPixel(pixel + (STEP_FRAME_W * last_button_X), (STEP_FRAME_H * last_button_Y) + 15, tftRAM[1][pixel]);
    tft.drawPixel((STEP_FRAME_W * last_button_X) + 1, pixel + (STEP_FRAME_H * last_button_Y), tftRAM[2][pixel]);
    tft.drawPixel((STEP_FRAME_W * last_button_X) + 15, pixel + (STEP_FRAME_H * last_button_Y), tftRAM[3][pixel]);
  }


  for (int pixel = 0; pixel < 16; pixel++) {
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
    for (int i = 0; i < scalesQuant; i++) {
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
}

void draw_Notenames() {
  for (int n = 0; n < 12; n++) {  //hor notes
    if (scales[scaleSelected][n]) {
      tft.fillRect(STEP_FRAME_W, STEP_FRAME_H * n + STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H, trackColor[desired_instrument]);
    }

    tft.setCursor(18, STEP_FRAME_H * n + 18);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(1);
    tft.print(noteNames[n]);
  }
}
void draw_Drumnotes() {
  for (int n = 0; n < 12; n++) {  //hor notes
    tft.fillRect(STEP_FRAME_W, STEP_FRAME_H * n + STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H, trackColor[desired_instrument]);
    tft.setCursor(18, STEP_FRAME_H * n + 18);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(1);
    tft.print(drumnote[n]);
  }
}

void draw_Clipselector() {
  for (int ClipNr = 0; ClipNr < 8; ClipNr++) {
    tft.fillRect(STEP_FRAME_W * 2 * ClipNr + STEP_FRAME_W * 2, STEP_FRAME_H * 13, STEP_FRAME_W * 2, STEP_FRAME_H, trackColor[desired_instrument] + (ClipNr * 20));
    tft.setCursor(STEP_FRAME_W * 2 * ClipNr + STEP_FRAME_W * 2 + 2, STEP_FRAME_H * 13 + 4);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(1);
    tft.print("Clip ");
    tft.print(ClipNr);
  }
}
void draw_SeqMode() {
  drawChar(18, 9, seqModes[track[desired_instrument].seqMode], trackColor[desired_instrument]);
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
  //MIDIChannel assign button
  tft.setCursor(STEP_FRAME_W * 18 + 2, STEP_FRAME_H * 10 + 2);
  tft.setFont(Arial_8);
  tft.setTextColor(trackColor[desired_instrument]);
  tft.setTextSize(1);
  tft.print("MCh:");
  tft.drawRect(STEP_FRAME_W * 18, STEP_FRAME_H * 11, STEP_FRAME_W * 2, STEP_FRAME_H, trackColor[desired_instrument]);
  //show midichannel
  tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 11 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * 18 + 8, STEP_FRAME_H * 11 + 3);
  tft.setFont(Arial_10);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print(track[desired_track].MIDIchannel);
  tft.drawRect(STEP_FRAME_W * 18, STEP_FRAME_H * 12, STEP_FRAME_W * 2, STEP_FRAME_H, trackColor[desired_instrument]);
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
  for (int plugintext = 0; plugintext < MAX_PLUGINS; plugintext++) {
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
void clearStepsGridY(int X_Axis) {  // clear all Steps in the same column
  for (int T = 0; T < 12; T++) {

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