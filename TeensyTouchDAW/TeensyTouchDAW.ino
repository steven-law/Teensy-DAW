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
#include "b_variables.h"
#include "b_pluginVariables.h"
#include "b_plugin Audiopath.h"
#include "b_plugin Audiopointers.h"
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





//newdigate::audiosample *pl5sample;



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
  plugin = new plugin_t[MAX_PLUGINS];

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
    note_frequency[r] = pow(2.0, ((double)(r - SAMPLE_ROOT) / 12.0));
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
  //Plugin7_Settings();
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
  delay(400);  //just to look how beautiful this image is
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
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[0]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[1]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[2]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[3]);
  Serial.print("   ");
  Serial.print("W~F: ");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[4]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[5]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[6]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[7]);
  Serial.print("   ");
  Serial.print("Velo: ");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[8]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[9]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[10]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[11]);
  Serial.print("   ");
  Serial.print("Mod: ");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[12]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[13]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[14]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value2[15]);
  Serial.print("     ");
  Serial.print("Filter: ");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[0]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[1]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[2]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[3]);
  Serial.print("   ");
  Serial.print("ADSR: ");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[4]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[5]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[6]);
  Serial.print("-");
  Serial.print(plugin[pl1NR].preset[plpreset[pl1NR]].Pot_Value[7]);

  Serial.println();

  Serial.print("PL2");
  Serial.print("-   ");
  Serial.print(plugin[1].preset[plpreset[1]].Pot_Value[0]);
  Serial.print("-");
  Serial.print(plugin[1].preset[plpreset[1]].Pot_Value[1]);
  Serial.print("-");
  Serial.print(plugin[1].preset[plpreset[1]].Pot_Value[2]);
  Serial.print("-");
  Serial.print(plugin[1].preset[plpreset[1]].Pot_Value[3]);
  Serial.print("  ");
  Serial.print(plugin[1].preset[plpreset[1]].Pot_Value[4]);
  Serial.print("-");
  Serial.print(plugin[1].preset[plpreset[1]].Pot_Value[5]);
  Serial.print("-");
  Serial.print(plugin[1].preset[plpreset[1]].Pot_Value[6]);
  Serial.print("-");
  Serial.print(plugin[1].preset[plpreset[1]].Pot_Value[7]);
  Serial.print("  ");
  Serial.print(plugin[1].preset[plpreset[1]].Pot_Value[8]);
  Serial.print("-");
  Serial.print(plugin[1].preset[plpreset[1]].Pot_Value[9]);
  Serial.print("-");
  Serial.print(plugin[1].preset[plpreset[1]].Pot_Value[10]);
  Serial.print("-");
  Serial.print(plugin[1].preset[plpreset[1]].Pot_Value[11]);
  Serial.println();

  Serial.print("PL3");
  Serial.print("-   ");
  Serial.print("W~F: ");
  Serial.print(plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[0]);
  Serial.print("   ");
  Serial.print("Filter: ");
  Serial.print(plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[4]);
  Serial.print("-");
  Serial.print(plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[5]);
  Serial.print("-");
  Serial.print(plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[6]);
  Serial.print("-");
  Serial.print(plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[7]);
  Serial.print("   ");
  Serial.print("ADSR: ");
  Serial.print(plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[8]);
  Serial.print("-");
  Serial.print(plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[9]);
  Serial.print("-");
  Serial.print(plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[10]);
  Serial.print("-");
  Serial.print(plugin[pl3NR].preset[plpreset[pl3NR]].Pot_Value[11]);
  Serial.println();

  Serial.print("PL4");
  Serial.print("-   ");
  Serial.print(plugin[3].preset[plpreset[3]].Pot_Value[0]);
  Serial.print("-");
  Serial.print(plugin[3].preset[plpreset[3]].Pot_Value[1]);
  Serial.print("-");
  Serial.print(plugin[3].preset[plpreset[3]].Pot_Value[2]);
  Serial.print("-");
  Serial.print(plugin[3].preset[plpreset[3]].Pot_Value[3]);
  Serial.print("  ");
  Serial.print(plugin[3].preset[plpreset[3]].Pot_Value[4]);
  Serial.print("-");
  Serial.print(plugin[3].preset[plpreset[3]].Pot_Value[5]);
  Serial.print("-");
  Serial.print(plugin[3].preset[plpreset[3]].Pot_Value[6]);
  Serial.print("-");
  Serial.print(plugin[3].preset[plpreset[3]].Pot_Value[7]);
  Serial.print("  ");
  Serial.print(plugin[3].preset[plpreset[3]].Pot_Value[8]);
  Serial.print("-");
  Serial.print(plugin[3].preset[plpreset[3]].Pot_Value[9]);
  Serial.print("-");
  Serial.print(plugin[3].preset[plpreset[3]].Pot_Value[10]);
  Serial.print("-");
  Serial.print(plugin[3].preset[plpreset[3]].Pot_Value[11]);
  Serial.println();

  Serial.print("PL8");
  Serial.print("-   ");
  Serial.print("W~F: ");
  Serial.print(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[0]);
  Serial.print("   ");
  Serial.print("Filter: ");
  Serial.print(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[4]);
  Serial.print("-");
  Serial.print(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[5]);
  Serial.print("-");
  Serial.print(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[6]);
  Serial.print("   ");
  Serial.print("ADSR: ");
  Serial.print(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[8]);
  Serial.print("-");
  Serial.print(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[9]);
  Serial.print("-");
  Serial.print(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[10]);
  Serial.print("-");
  Serial.print(plugin[pl8NR].preset[plpreset[pl8NR]].Pot_Value[11]);
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

  //placeholder for debugging
  if (msecs % 100 == 0) {
  }

  if (gridTouchY == 1) trackTouchY = 0;
  if (gridTouchY == 3) trackTouchY = 1;
  if (gridTouchY == 4) trackTouchY = 2;
  if (gridTouchY == 6) trackTouchY = 3;
  if (gridTouchY == 7) trackTouchY = 4;
  if (gridTouchY == 9) trackTouchY = 5;
  if (gridTouchY == 10) trackTouchY = 6;
  if (gridTouchY == 12) trackTouchY = 7;

  if (ts.touched()) {
    readTouchinput();
  }
  if (ts.touched() || button[15]) {

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
        for (int i = 0; i < MAX_SCALES; i++) {
          tft.setCursor(STEP_FRAME_W * 2, STEP_FRAME_H * i + STEP_FRAME_H);
          tft.setFont(Arial_8);
          tft.setTextColor(ILI9341_WHITE);
          tft.setTextSize(1);
          tft.print(scaleNames[i]);
        }
      }
    }

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
      }
      //cursor down
      if (otherCtrlButtons && key.bit.KEY == 66) {  //"B"   66 4th button
        gridTouchY = constrain(gridTouchY + 1, 0, 14);
        drawCursor();
        showCoordinates();
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
void readTouchinput() {
  TS_Point p = ts.getPoint();
  gridTouchX = map(p.x, TS_MINX, TS_MAXX, 0, 19);
  gridTouchY = map(p.y, TS_MINY, TS_MAXY, 0, 14);
  trackTouchY = map(p.y, 800, 3200, 0, 7);
  if (gridTouchY >= 2 && gridTouchY <= 4) {
    lastPotRow = 0;
  }

  if (gridTouchY >= 5 && gridTouchY <= 7) {
    lastPotRow = 1;
  }

  if (gridTouchY >= 8 && gridTouchY <= 10) {
    lastPotRow = 2;
  }
  if (gridTouchY >= 11 && gridTouchY <= 13) {
    lastPotRow = 3;
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
  static byte last_button_X = 0;
  static byte last_button_Y = 0;
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
  tft.drawRect(STEP_FRAME_W * 2, STEP_FRAME_H, STEP_FRAME_W * 16, STEP_FRAME_H * MAX_SCALES, ILI9341_WHITE);  //Xmin, Ymin, Xlength, Ylength, color
}
void scaleSelector() {
  if (millis() % interval == 0) {
    for (int i = 0; i < MAX_SCALES; i++) {
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
    int step_Frame_X = i * STEP_FRAME_W;
    tft.drawFastVLine(step_Frame_X + STEP_FRAME_W * 2, STEP_FRAME_H, GRID_LENGTH_VERT, ILI9341_WHITE);  //(x, y-start, length, color)
    if (i % 4 == 0) {
      tft.drawFastVLine((i * STEP_FRAME_W) + 32, STEP_FRAME_H, STEP_FRAME_H * 12, ILI9341_LIGHTGREY);  //(x, y-start, y-length, color)
    }
  }
  for (int i = 0; i < 13; i++) {  //hor lines
    int step_Frame_Y = i * 16;
    tft.drawFastHLine(STEP_FRAME_W * 2, step_Frame_Y + STEP_FRAME_H, GRID_LENGTH_HOR, ILI9341_WHITE);  //(x-start, y, length, color)
  }
}

void draw_Notenames() {
  for (int n = 0; n < num_voice; n++) {  //hor notes
    if (scales[scaleSelected][n]) {
      tft.fillRect(STEP_FRAME_W, STEP_FRAME_H * n + STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H, trackColor[desired_instrument]);
    }

    tft.setCursor(20, STEP_FRAME_H * n + 20);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(1);
    tft.print(noteNames[n]);
  }
}
void draw_Drumnotes() {
  for (int n = 0; n < num_voice; n++) {  //hor notes
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