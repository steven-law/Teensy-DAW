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

There are allways things left to be made, but feel free to add your features.





1. 15stepTeensyDAW3.ino :

This is the main sketch. It is easier to look at it in chapters: 
Including all the librarys and the .h files
calibration and customizing
initiate the modules
Place for the PJRC GUItool for the internal plugins (audio Connections)-->moved to seperate file

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

//#include "functions.h"

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
#include "b_plugin_Audiopath.h"
#include "b_plugin_Audiopointers.h"

#include "Adafruit_Keypad.h"
#include <ResponsiveAnalogRead.h>
#include <USBHost_t36.h>
#include <Encoder.h>
#include <MIDI.h>
#include "v_smfwriter.h"
//#include "b_display_functions.h"


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


//individual trackcolors
int trackColor[9]{ 6150246, 8256638, 1095334, 12643941, 2583100, 9365295, 12943157, 5678954, ILI9341_WHITE };
//end of calibration and custumizing



//initiate the modules

File myFile;                                                                         //initiate SDCard Reader
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);  //initiate TFT-Srceen
//ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);  //initiate TFT-Srceen
//DMAMEM uint16_t fb1[320 * 240];


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
elapsedMillis msecs;
elapsedMicros msecsclock;






#include "trackfunctions.h"
Clock master_clock;
classForTracks track0;
classForTracks track1;
classForTracks track2;
classForTracks track3;
classForTracks track4;
classForTracks track5;
classForTracks track6;
classForTracks track7;
classForTracks *allTracks[NUM_TRACKS] = { &track0, &track1, &track2, &track3, &track4, &track5, &track6, &track7 };
AudioRecorders AudioRecorder;








void setup() {
  Serial.begin(15200);  // set MIDI baud
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

  //allocate tracks0-7 "array"
  ctrack = calloc(NUM_TRACKS, sizeof(track_t));
  //fill the tracks0-7 "array"
  for (int t = 0; t < NUM_TRACKS; t++) {
    for (int c = 0; c < 8; c++) {
      for (int s = 0; s < TICKS_PER_BAR; s++) {
        for (int v = 0; v < MAX_VOICES; v++) {
          ctrack[t].sequence[c].tick[s].voice[v] = 0;
          ctrack[t].sequence[c].tick[s].velo[v] = 99;
        }
      }
    }
  }
  //allocate tracks
  track = new tracks[NUM_TRACKS];
  //ctrack = new track_t[NUM_TRACKS];
  //allocate plugins
  plugin = new plugin_t[MAX_PLUGINS];
  for (int x = 0; x < NUM_TRACKS; x++) {
    for (int y = 0; y < MAX_PRESETS; y++) {
      for (int z = 0; z < 16; z++) {
        plugin[x].preset[y].Pot_Value[z] = 0;
        plugin[x].preset[y].Pot_Value2[z] = 0;
      }
    }
  }
  //set the singlecyclewaveform to 0
 // for (byte i = 0; i < 256; i++) {
  //  singleCycleWaveform[i] = 0;
  //}
  effect = new effect_t[MAX_EFFECTS];
  //allocate NFX1
  NFX1 = new NFX[MAX_PRESETS];
  //allocate NFX2
  NFX2 = new NFX[MAX_PRESETS];
  //allocate NFX3
  NFX3 = new NFX[MAX_PRESETS];
  //allocate NFX4
  NFX4 = new NFX[MAX_PRESETS];

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

  track0.setup(0, 10);
  track1.setup(1, 2);
  track2.setup(2, 3);
  track3.setup(3, 4);
  track4.setup(4, 5);
  track5.setup(5, 6);
  track6.setup(6, 7);
  track7.setup(7, 8);
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

  gridStepSequencer();
  debug_free_ram();
  //tft.updateScreen();
}



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
  midi07.read();
  midi08.read();
  midi09.read();
  midi10.read();
  detect_and_assign_midi_devices();
  kpd.tick();
  process_clock();


  readMainButtons();
  doMainButtons();
  Plugin_View_Dynamic();

  PluginNoteOn();
  PluginNoteOff();
  readEncoders();

  otherCtrlButtons = (!button[8] && !button[9] && !button[10] && !button[11] && !button[12]);

  //placeholder for debugging
  if (msecs % 500 == 0) {
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
        if (abs(map(Potentiometer[0], 0, 127, 55, 200) - seq_tempo) < 10) {
          seq_tempo = map(Potentiometer[0], 0, 127, 55, 200);
          master_clock.set_tempo(seq_tempo);
        }
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //Scale Select
      /*
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
      */
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
  // tft.updateScreenAsync();
  // tft.waitUpdateAsyncComplete();
}

//function to what to read when buttons are pressed, this needs to be changed!!
void readMainButtons() {

  while (kpd.available()) {
    keypadEvent key = kpd.read();
    if (key.bit.EVENT == KEY_JUST_PRESSED) {
      //tft.updateScreen();
      //cursor
      //curser left
      if (key.bit.KEY == BUTTON0) {  //"D" 68 1st button
        button[0] = true;
      }

      //cursor right
      if (key.bit.KEY == BUTTON1) {  //"F"  70 2nd button
        button[1] = true;
      }
      //cursor up
      if (key.bit.KEY == BUTTON2) {  //"9"   57 3rd button
        button[2] = true;
      }
      //cursor down
      if (key.bit.KEY == BUTTON3) {  //"B"   66 4th button
        button[3] = true;
      }
      //last-pot-row
      if (key.bit.KEY == BUTTON4) {  //"B"   66 5th button
        button[4] = true;
      }

      //recbutton
      if (key.bit.KEY == BUTTON5) {  //"5" 53
        button[5] = true;
      }

      //playbutton
      if (key.bit.KEY == BUTTON6) {  //"3" 51
        button[6] = true;
      }
      //stopbutton
      if (key.bit.KEY == BUTTON7) {  //"1" 49
        button[7] = true;
      }
      // hold for track button
      if (key.bit.KEY == BUTTON8) {  //"E"  69
        button[8] = true;
      }
      // hold for plugin button
      if (key.bit.KEY == BUTTON9) {  //"C"  67
        button[9] = true;
      }
      // hold for plugin button
      if (key.bit.KEY == BUTTON10) {  //"C"  67
        button[10] = true;
      }
      // hold for Mixer button
      if (key.bit.KEY == BUTTON11) {  //"4"  52
        button[11] = true;
      }
      // hold for FX button
      if (key.bit.KEY == BUTTON12) {  //"8"  56
        button[12] = true;
      }
      // hold for cursor via pot
      if (key.bit.KEY == BUTTON13) {
        button[13] = true;
      }
      // hold for cursor via pot
      if (key.bit.KEY == BUTTON14) {
        button[14] = true;
      }
      // hold for enter button
      if (key.bit.KEY == BUTTON15) {
        button[15] = true;
      }
    } else if (key.bit.EVENT == KEY_JUST_RELEASED) {

      if (key.bit.KEY == BUTTON0) {  //"E"  69
        button[0] = false;
      }
      if (key.bit.KEY == BUTTON1) {  //"E"  69
        button[1] = false;
      }
      if (key.bit.KEY == BUTTON2) {  //"E"  69
        button[2] = false;
      }
      if (key.bit.KEY == BUTTON3) {  //"E"  69
        button[3] = false;
      }
      if (key.bit.KEY == BUTTON4) {  //"E"  69
        button[4] = false;
      }
      if (key.bit.KEY == BUTTON5) {  //"E"  69
        button[5] = false;
      }
      if (key.bit.KEY == BUTTON6) {  //"E"  69
        button[6] = false;
      }
      if (key.bit.KEY == BUTTON7) {  //"E"  69
        button[7] = false;
      }


      // release for track button
      if (key.bit.KEY == BUTTON8) {  //"E"  69
        button[8] = false;
      }
      // release for plugin button
      if (key.bit.KEY == BUTTON9) {  //"C"  67
        button[9] = false;
      }
      // release for arranger button
      if (key.bit.KEY == BUTTON10) {  //"A"  65
        button[10] = false;
      }
      // hold for mixer button
      if (key.bit.KEY == BUTTON11) {  //"8"  56
        button[11] = false;
      }
      // release for FX button
      if (key.bit.KEY == BUTTON12) {  //"4"  52
        button[12] = false;
      }
      // rel for cursor via pot
      if (key.bit.KEY == BUTTON13) {
        button[13] = false;
      }
      //release for cursor via pot
      if (key.bit.KEY == BUTTON14) {
        button[14] = false;
      }
      //release for enter button
      if (key.bit.KEY == BUTTON15) {
        button[15] = false;
      }
    }
  }
}
void doMainButtons() {
  //top row buttons
  if (otherCtrlButtons) {
    //curser left
    if (button[0]) {
      button[0] = false;
      if (selectPage == NFX8_PAGE1) {
        pixelTouchX = constrain((pixelTouchX - 2), 0, 320);
        drawCursorPixel();
      } else {
        gridTouchX = constrain(gridTouchX - 1, 0, 19);
        drawCursor();
      }
      //showCoordinates();
    }
    //cursor right
    if (button[1]) {
      button[1] = false;
      if (selectPage == NFX8_PAGE1) {
        pixelTouchX = constrain((pixelTouchX + 2), 0, 320);
        drawCursorPixel();
      } else {
        gridTouchX = constrain(gridTouchX + 1, 0, 19);
        drawCursor();
      }
      //showCoordinates();
    }
    //cursor up
    if (button[2]) {
      button[2] = false;
      if (selectPage == NFX8_PAGE1) {
        drawCursorPixel();
      } else {
        gridTouchY = constrain(gridTouchY - 1, 0, 14);
        drawCursor();
      }
      //showCoordinates();
    }
    //cursor down
    if (button[3]) {
      button[3] = false;
      if (selectPage == NFX8_PAGE1) {
        drawCursorPixel();
      } else {
        gridTouchY = constrain(gridTouchY + 1, 0, 14);
        drawCursor();
      }
      //showCoordinates();
    }
    //last-pot-row
    if (button[4]) {
      button[4] = false;
      lastPotRow++;
      rowButtonpressed = true;
      drawLastPotRow();
    }
    //recbutton
    if (button[5]) {
      button[5] = false;
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
    if (button[6]) {
      startSeq();
      button[6] = false;
    }
    //stopbutton
    if (button[7]) {
      stopSeq();
      button[7] = false;
    }
  }
  //  select Songarranger page 11 & button[10]
  if (button[10]) {  //"A"  65
    for (int i = 0; i < MAX_SONGMODE_PAGES; i++) {
      if (i != 10) {
        if (button[i]) {
          button[i] = false;
          selectPage = i + 10;
          gridSongMode(i);
          songModePage(i);
        }
      }
    }
  }
  //bottom row buttons
  if (!button[10]) {
    //select tracks
    if (button[8]) {  //9th button
      seq_rec = false;
      tft.fillCircle(STEP_FRAME_W * POSITION_RECORD_BUTTON + 7, 7, DOT_RADIUS + 1, ILI9341_LIGHTGREY);
      for (int i = 0; i < NUM_TRACKS; i++) {
        //select melodic track 2-8
        if (button[i]) {
          button[i] = false;
          selectPage = i;
          desired_instrument = i;  //desired_instrument=desired_track
          desired_track = i;
          gridStepSequencer();
        }
      }
    }
    //plugin selection
    if (button[9]) {
      seq_rec = false;
      tft.fillCircle(STEP_FRAME_W * POSITION_RECORD_BUTTON + 7, 7, DOT_RADIUS + 1, ILI9341_LIGHTGREY);
      for (int i = 0; i < NUM_TRACKS; i++) {
        if (button[i]) {  //"D"  68  1st button
          button[i] = false;
          desired_track = i;
          desired_instrument = i;
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
    }
    //  select Mixerpage1
    if (button[11]) {
      seq_rec = false;
      tft.fillCircle(STEP_FRAME_W * POSITION_RECORD_BUTTON + 7, 7, DOT_RADIUS + 1, ILI9341_LIGHTGREY);
      if (button[0]) {
        selectPage = MIXER_PAGE_1;
        button[0] = false;
        Plugin_View_Static();
      }
      //select mixrpage2
      if (button[1]) {
        selectPage = MIXER_PAGE_2;
        button[1] = false;
        Plugin_View_Static();
      }
      //select Mixerpage1
      if (button[2]) {  //"9"  57
        selectPage = MIXER_PAGE_3;
        button[3] = false;
        Plugin_View_Static();
      }
    }
    //FX Selection
    if (button[12]) {
      seq_rec = false;
      tft.fillCircle(STEP_FRAME_W * POSITION_RECORD_BUTTON + 7, 7, DOT_RADIUS + 1, ILI9341_LIGHTGREY);
      //reverb
      if (button[0]) {
        selectPage = FX1_PAGE1;
        button[0] = false;
        Plugin_View_Static();
      }
      //bitcrusher
      if (button[1]) {
        selectPage = FX2_PAGE1;
        button[1] = false;
        Plugin_View_Static();
      }
      //delay
      if (button[2]) {
        selectPage = FX3_PAGE1;
        button[2] = false;
        Plugin_View_Static();
      }
      //NoteFX
      if (button[4]) {
        button[4] = false;

        if (allTracks[desired_instrument]->seqMode == 1) {
          selectPage = NFX2_PAGE1;  //dropseq
        }
        if (allTracks[desired_instrument]->seqMode == 2) {
          selectPage = NFX3_PAGE1;  //random
        }
        if (allTracks[desired_instrument]->seqMode == 3) {
          selectPage = NFX4_PAGE1;  //polyRhythm
        }
        if (allTracks[desired_instrument]->seqMode == 4) {
          selectPage = NFX1_PAGE1;  //grids
        }
        Plugin_View_Static();
      }
    }
    //Audiorecorder
    if (button[13]) {  // 14th button
      selectPage = RECORDER_PAGE;
      seq_rec = false;
      tft.fillCircle(STEP_FRAME_W * POSITION_RECORD_BUTTON + 7, 7, DOT_RADIUS + 1, ILI9341_LIGHTGREY);
      button[13] = false;
      Plugin_View_Static();
    }
  }
  if (button[14] && button[15]) {
    button[15] = false;
    seq_rec = false;
    tft.fillCircle(STEP_FRAME_W * POSITION_RECORD_BUTTON + 7, 7, DOT_RADIUS + 1, ILI9341_LIGHTGREY);
    Serial.println("debugging:");
    Serial.println("arrangment1:");
    for (int t = 0; t < NUM_TRACKS; t++) {
      for (int s = 0; s < MAX_PHRASES - 2; s++) {
        if (track[t].arrangment1[s] == 8) {
          Serial.print(".");
        } else {
          Serial.print(track[t].arrangment1[s]);
        }
      }
      Serial.println("");
    }
    Serial.println("");
    Serial.println("clips:");

    for (int t = 0; t < NUM_TRACKS; t++) {
      Serial.printf("track:%d\n", t);
      for (int c = 0; c < 8; c++) {
        Serial.printf("clip:%d\n", c);
        for (int v = 0; v < MAX_VOICES; v++) {
          for (int s = 0; s < TICKS_PER_BAR; s++) {
            if (ctrack[t].sequence[c].tick[s].voice[v] == 0) {
              Serial.print("..");
            } else {
              Serial.print(ctrack[t].sequence[c].tick[s].voice[v]);
            }
            Serial.print("-");
          }
          Serial.println("");
        }
        Serial.println("");
        Serial.println("");
      }
    }
    Serial.println("");
    Serial.println("");

    Serial.println("plugins:");
    //SerialPrintPlugins();
    Serial.println("Free RAM:");
    debug_free_ram();
    // print a summary of the current & maximum usage
    Serial.print("CPU: ");

    Serial.print(AudioProcessorUsage());
    Serial.print(",");
    Serial.print(AudioProcessorUsageMax());
    Serial.print("    ");
    Serial.print("Memory: ");
    Serial.print(AudioMemoryUsage());
    Serial.print(",");
    Serial.print(AudioMemoryUsageMax());
    Serial.println();
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
  drawLastPotRow();
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