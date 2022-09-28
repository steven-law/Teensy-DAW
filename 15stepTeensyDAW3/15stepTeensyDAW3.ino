/*Contributing Manual:

Hello. Here i will show you how to implement new stuff easily.

There are some things left to be made at this point, but feel free to add your features, tho.

toDo´s:
    • add polyphony
    • add display stabilty 
    • also how i update my screencontent, deletes are not always shown 
    • internal plugins 
    • if in the stepsequencer of a track, i would like to hear the selected clip. when in songmode, only play the arrangment 
    • Adding the audioboard. for teensy 4.1
    • replace the clip-array with a struct 
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

void savebutton() Initializing the card and if we hit the save button, do all the 	savings. Right now it saves the clip-array into one big junk of ascii´s, that is read 	when loading.
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
#include "FifteenStep.h"
#include "variables.h"

// WAV files converted to code by wav2sketch
#include "AudioSampleSnare.h"         // http://www.freesound.org/people/KEVOY/sounds/82583/
#include "AudioSampleTomtom.h"        // http://www.freesound.org/people/zgump/sounds/86334/
#include "AudioSampleHihat.h"         // http://www.freesound.org/people/mhc/sounds/102790/
#include "AudioSampleKick.h"          // http://www.freesound.org/people/DWSD/sounds/171104/
#include "AudioSampleCashregister.h"  // http://www.freesound.org/people/kiddpark/sounds/201159/
#include "AudioSampleP2.h"

//calibration and customizing
//Pinout for screen
#define TIRQ_PIN 2   //alternate Pins: any digital pin
#define CS_PIN 8     //alternate Pins: any digital pin
#define TFT_DC 15    //alternate Pins 9, 10, 20, 21
#define TFT_CS 10    //alternate Pins 9, 15, 20, 21
#define TFT_RST 255  // 255 = unused, connect to 3.3V
#define TFT_MOSI 11  //shareable
#define TFT_SCLK 13  //shareable
#define TFT_MISO 12  //shareable

//calibrate your Screen
// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 180
#define TS_MINY 260
#define TS_MAXX 3730
#define TS_MAXY 3800

//touchscreen response; to be changed
const long interval = 120;

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



//initiate the modules
FifteenStep seq = FifteenStep(SEQUENCER_MEMORY);                                     //initiate Sequencer
File myFile;                                                                         //initiate SDCard Reader
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);  //initiate TFT-Srceen
XPT2046_Touchscreen ts(CS_PIN);                                                      //initiate Touchscreen



//Place for the Pluginconnections



// GUItool: begin automatically generated code
AudioPlayMemory playMem9;             //xy=65,1075
AudioPlayMemory playMem10;            //xy=70,1106
AudioPlayMemory playMem7;             //xy=75,1005
AudioPlayMemory playMem8;             //xy=75,1042
AudioSynthWaveform waveform3;         //xy=81,176
AudioSynthWaveform waveform1;         //xy=84,80
AudioSynthWaveform waveform2;         //xy=85,129
AudioPlayMemory playMem5;             //xy=85,929
AudioPlayMemory playMem6;             //xy=86,967
AudioSynthWaveformDc dc2;             //xy=90.14286041259766,270.1428737640381
AudioPlayMemory playMem1;             //xy=90,789.0000114440918
AudioPlaySdWav playSdWav12;           //xy=90.65714645385742,740.7142810821533
AudioPlayMemory playMem2;             //xy=91,825
AudioPlaySdWav playSdWav7;            //xy=92.65715026855469,559.7142786979675
AudioSynthWaveform waveform4;         //xy=94,226
AudioPlaySdWav playSdWav9;            //xy=92.65714645385742,631.714280128479
AudioPlaySdWav playSdWav3;            //xy=93.65714645385742,404.71427631378174
AudioPlaySdWav playSdWav10;           //xy=92.65714645385742,665.714280128479
AudioPlaySdWav playSdWav4;            //xy=93.65715026855469,440.71427726745605
AudioPlaySdWav playSdWav11;           //xy=92.65714645385742,704.714280128479
AudioPlaySdWav playSdWav8;            //xy=93.65714645385742,596.7142791748047
AudioPlayMemory playMem11;            //xy=92,1145
AudioPlaySdWav playSdWav2;            //xy=96.65714645385742,367.71427631378174
AudioPlaySdWav playSdWav5;            //xy=96.65714836120605,480.71427726745605
AudioPlaySdWav playSdWav6;            //xy=96.65715026855469,520.7142782211304
AudioPlaySdWav playSdWav1;            //xy=99.85715103149414,328.71427631378174
AudioPlayMemory playMem12;            //xy=97,1183
AudioPlayMemory playMem3;             //xy=100,859
AudioPlayMemory playMem4;             //xy=107,895
AudioEffectEnvelope envelope1;        //xy=232.4285659790039,267.1428518295288
AudioMixer4 mixer1;                   //xy=244,117
AudioSynthWaveformDc pl3dc1;          //xy=280.00000381469727,656.666708946228
AudioMixer4 drummixer1;               //xy=300.8571548461914,352.85713386535645
AudioMixer4 drummixer2;               //xy=302.8571548461914,441.85713386535645
AudioMixer4 drummixer3;               //xy=311.8571548461914,533.8571338653564
AudioMixer4 pl4drummixer1;            //xy=312,806
AudioMixer4 pl4drummixer2;            //xy=314,895
AudioSynthWaveform pl3waveform1;      //xy=317,593.1112384796143
AudioMixer4 pl4drummixer3;            //xy=323,987
AudioFilterStateVariable filter1;     //xy=397.0000114440918,113.42856979370117
AudioEffectEnvelope pl3envelope2;     //xy=423.00000381469727,653.0000095367432
AudioEffectEnvelope envelope2;        //xy=457.7142868041992,162.1428565979004
AudioMixer4 drummixer4;               //xy=485.85716247558594,462.00000762939453
AudioFilterStateVariable pl3filter1;  //xy=504.44439125061035,602.3334541320801
AudioMixer4 pl4drummixer4;            //xy=540.0000076293945,815.1428833007812
AudioEffectBitcrusher bitcrusher1;    //xy=577.7142486572266,111.71430587768555
AudioEffectEnvelope pl3envelope1;     //xy=681.6667098999023,589.3334550857544
AudioEffectDelay delay1;              //xy=726.5713958740234,249.42859268188477
AudioMixer4 mixer3;                   //xy=730.5713958740234,66.42859268188477
AudioFilterStateVariable filter3;     //xy=730.5713958740234,141.42859268188477
AudioMixer4 mixer5;                   //xy=875.1429252624512,468.85719871520996
AudioOutputPT8211 pt8211_1;           //xy=1035.535629272461,470.2500305175781
AudioConnection patchCord1(playMem9, 0, pl4drummixer3, 0);
AudioConnection patchCord2(playMem10, 0, pl4drummixer3, 1);
AudioConnection patchCord3(playMem7, 0, pl4drummixer2, 2);
AudioConnection patchCord4(playMem8, 0, pl4drummixer2, 3);
AudioConnection patchCord5(waveform3, 0, mixer1, 2);
AudioConnection patchCord6(waveform1, 0, mixer1, 0);
AudioConnection patchCord7(waveform2, 0, mixer1, 1);
AudioConnection patchCord8(playMem5, 0, pl4drummixer2, 0);
AudioConnection patchCord9(playMem6, 0, pl4drummixer2, 1);
AudioConnection patchCord10(dc2, envelope1);
AudioConnection patchCord11(playMem1, 0, pl4drummixer1, 0);
AudioConnection patchCord12(playSdWav12, 0, drummixer3, 3);
AudioConnection patchCord13(playMem2, 0, pl4drummixer1, 1);
AudioConnection patchCord14(playSdWav7, 0, drummixer2, 2);
AudioConnection patchCord15(waveform4, 0, mixer1, 3);
AudioConnection patchCord16(playSdWav9, 0, drummixer3, 0);
AudioConnection patchCord17(playSdWav3, 0, drummixer1, 2);
AudioConnection patchCord18(playSdWav10, 0, drummixer3, 1);
AudioConnection patchCord19(playSdWav4, 0, drummixer1, 3);
AudioConnection patchCord20(playSdWav11, 0, drummixer3, 2);
AudioConnection patchCord21(playSdWav8, 0, drummixer2, 3);
AudioConnection patchCord22(playMem11, 0, pl4drummixer3, 2);
AudioConnection patchCord23(playSdWav2, 0, drummixer1, 1);
AudioConnection patchCord24(playSdWav5, 0, drummixer2, 0);
AudioConnection patchCord25(playSdWav6, 0, drummixer2, 1);
AudioConnection patchCord26(playSdWav1, 0, drummixer1, 0);
AudioConnection patchCord27(playMem12, 0, pl4drummixer3, 3);
AudioConnection patchCord28(playMem3, 0, pl4drummixer1, 2);
AudioConnection patchCord29(playMem4, 0, pl4drummixer1, 3);
AudioConnection patchCord30(envelope1, 0, filter1, 1);
AudioConnection patchCord31(mixer1, 0, filter1, 0);
AudioConnection patchCord32(pl3dc1, pl3envelope2);
AudioConnection patchCord33(drummixer1, 0, drummixer4, 0);
AudioConnection patchCord34(drummixer2, 0, drummixer4, 1);
AudioConnection patchCord35(drummixer3, 0, drummixer4, 2);
AudioConnection patchCord36(pl4drummixer1, 0, pl4drummixer4, 0);
AudioConnection patchCord37(pl4drummixer2, 0, pl4drummixer4, 1);
AudioConnection patchCord38(pl3waveform1, 0, pl3filter1, 0);
AudioConnection patchCord39(pl4drummixer3, 0, pl4drummixer4, 2);
AudioConnection patchCord40(filter1, 0, envelope2, 0);
AudioConnection patchCord41(pl3envelope2, 0, pl3filter1, 1);
AudioConnection patchCord42(envelope2, bitcrusher1);
AudioConnection patchCord43(drummixer4, 0, mixer5, 1);
AudioConnection patchCord44(pl3filter1, 0, pl3envelope1, 0);
AudioConnection patchCord45(pl4drummixer4, 0, mixer5, 3);
AudioConnection patchCord46(bitcrusher1, 0, mixer3, 0);
AudioConnection patchCord47(pl3envelope1, 0, mixer5, 2);
AudioConnection patchCord48(delay1, 0, filter3, 0);
AudioConnection patchCord49(mixer3, delay1);
AudioConnection patchCord50(mixer3, 0, mixer5, 0);
AudioConnection patchCord51(filter3, 2, mixer3, 1);
AudioConnection patchCord52(mixer5, 0, pt8211_1, 0);
AudioConnection patchCord53(mixer5, 0, pt8211_1, 1);
// GUItool: end automatically generated code






void setup() {
  Serial.begin(9600);  // set MIDI baud
  AudioMemory(200);

  //initialize SD Card
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // start sequencer and set callbacks
  seq.begin(tempo, steps);
  seq.setStepHandler(step);
  seq.stop();

  /// set the default channel of each track
  track[0].MIDIchannel = 10;
  track[1].MIDIchannel = 2;
  track[2].MIDIchannel = 3;
  track[3].MIDIchannel = 4;
  track[4].MIDIchannel = 5;
  track[5].MIDIchannel = 6;
  track[6].MIDIchannel = 7;
  track[7].MIDIchannel = 8;

  //load the pluginsettings
  Plugin_1_Settings();
  Plugin_2_Settings();
  Plugin_3_Settings();
  Plugin_4_Settings();

  //initialize the TFT- and Touchscreen
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  ts.begin();
  ts.setRotation(1);
  while (!Serial && (millis() <= 1000))
    ;

  //load the startupScreen
  startUpScreen();
}


void loop() {

  usbMIDI.read();
  // this is needed to keep the sequencer
  // running. there are other methods for
  // start, stop, and pausing the steps
  seq.run();

  //read Potentiometer1
  Potentiometer1 = analogRead(A13);
  //Serial.println();
  //always show the coordinates
  showCoordinates();

  TS_Point p = ts.getPoint();
  Serial.println(p.z);
  if (ts.touched()) {
    gridTouchX = map(p.x, 380, 3930, 0, 19);
    gridTouchY = map(p.y, 300, 3800, 0, 14);

    trackTouchY = map(p.y, 700, 3200, 0, 7);
    constrainedtrackTouchY = constrain(trackTouchY, 0, 7);


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
          track[i].clip_songMode = arrangment1[i][0];
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
        tempoSelect = map(Potentiometer1, 0, 1023, 50, 250);
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
        for (byte others = 0; others <= MAX_PAGES; others++) {
          selectPage[others] = LOW;
        }
        selectPage[SCALESELECT] = HIGH;
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
        for (byte others = 0; others <= MAX_PAGES; others++) {
          selectPage[others] = LOW;
        }
        selectPage[SONGMODE_PAGE_1] = HIGH;
        gridSongMode();
      }
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select Drumchannel
      if (trackTouchY == 0) {
        for (byte others = 0; others <= MAX_PAGES; others++) {
          selectPage[others] = LOW;
        }
        selectPage[DRUMTRACK] = HIGH;
        griddrumStepSequencer();
      }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select channel2-8
      for (int tracks = 1; tracks < 8; tracks++) {
        if (trackTouchY == tracks) {
          for (byte others = 0; others <= MAX_PAGES; others++) {
            selectPage[others] = LOW;
          }
          selectPage[tracks] = HIGH;
          gridStepSequencer(tracks);
        }
      }
    }
  }
  //***********************************************************************************************************************
  //9)copy one of the plugin Page Views
  //and change the names according to our variables and functions.
  //Every page you want to make has to have its own statement
  //we create:

  //  //setting up the Plugin3 Page1-view
  //if (selectPage[PLUGIN3_PAGE1] == HIGH) {
  //Plugin3_Page1_Dynamic();
  //}

  // after adding the active state statement
  // now head over to the "midi.ino"
  //look for *****************************************************************************************
  //////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////

  //THIS IS IMPORTANT!!!!!; set your different plugin (or whatever) views in here
  // every view you create has to be set to active here!!!!
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //-----------------------------------------
  //setting up the Plugin1 Page1-view
  if (selectPage[PLUGIN1_PAGE1] == HIGH) {
    Plugin1_Page1_Dynamic();
  }
  //setting up the Plugin1 Page2-view
  if (selectPage[PLUGIN1_PAGE2] == HIGH) {
    Plugin1_Page2_Dynamic();
  }
  //setting up the Plugin2 Page1-view
  if (selectPage[PLUGIN2_PAGE1] == HIGH) {
    Plugin2_Page1_Dynamic();
  }
  //setting up the Plugin3 Page1-view
  if (selectPage[PLUGIN3_PAGE1] == HIGH) {
    Plugin3_Page1_Dynamic();
  }

  if (selectPage[PLUGIN4_PAGE1] == HIGH) {
    Plugin4_Page1_Dynamic();
  }


  //setting up the StepSequencer-view for drumtrack #1
  if (selectPage[DRUMTRACK] == HIGH) {
    drumStepSequencer();
  }
  //setting up the melodicStepSequencer-view for #2-8
  for (int i = 1; i < 8; i++) {
    if (selectPage[i] == HIGH) {
      melodicStepSequencer(i);
    }
  }
  //setting up the scaleSelector-view
  if (selectPage[SCALESELECT] == HIGH) {
    scaleSelector();
  }
  //setting up the songMode-view1
  if (selectPage[SONGMODE_PAGE_1] == HIGH) {
    songModePage(0);
  }
  //setting up the songMode-view2
  if (selectPage[SONGMODE_PAGE_2] == HIGH) {
    songModePage(1);
  }
  //setting up the songMode-view3
  if (selectPage[SONGMODE_PAGE_3] == HIGH) {
    songModePage(2);
  }
  //setting up the songMode-view4
  if (selectPage[SONGMODE_PAGE_4] == HIGH) {
    songModePage(3);
  }
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
    tft.drawFastVLine(step_Frame_X + STEP_FRAME_W * 2, 16, GRID_LENGTH_VERT, ILI9341_WHITE);  //(x, y-start, length, color)
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
    if (scales[scaleSelected][i] == HIGH) {
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
}

void Plugin_View_Static() {
  clearWorkSpace();
  //show pageselector
  for (byte pages = 0; pages < 4; pages++) {
    tft.drawRect(STEP_FRAME_W * 18 + 1, ((pages + 1)) * STEP_FRAME_H * 2 + STEP_FRAME_H, STEP_FRAME_W * 2 - 1, STEP_FRAME_H * 2, ILI9341_WHITE);
    tft.setFont(Arial_12);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(STEP_FRAME_W * 18 + 12, ((pages + 1)) * STEP_FRAME_H * 2 + STEP_FRAME_H + 12);
    tft.print(pages + 1);
  }
}

void drawbarH(byte XPos, byte YPos, byte value_rnd, char* fName, int color) {  //gridPosX, gridPosY, value 0-100, valuename, backgroundcolor of bargraph
  int value_Pix;
  int valueI_Pix;
  value_Pix = map(value_rnd, 0, 100, 0, 32);
  valueI_Pix = 32 - value_Pix;
  tft.drawRect(STEP_FRAME_W * XPos - 1, STEP_FRAME_H * YPos, STEP_FRAME_W * 2 + 3, STEP_FRAME_H, ILI9341_WHITE);
  tft.fillRect(STEP_FRAME_W * XPos + 1, STEP_FRAME_H * YPos + 1, value_Pix, STEP_FRAME_H - 2, color);
  tft.fillRect(STEP_FRAME_W * (XPos + 2) - valueI_Pix + 1, STEP_FRAME_H * YPos + 1, valueI_Pix, STEP_FRAME_H - 2, ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * XPos + 3, STEP_FRAME_H * (YPos - 1) + 4);
  tft.print(fName);
  tft.setCursor(STEP_FRAME_W * XPos + 3, STEP_FRAME_H * YPos + 4);
  tft.print(value_rnd);
}

void drawbarV(byte XPos, byte YPos, byte value_rnd, char* fName, int color) {  //gridPosX, gridPosY, value 0-100, valuename, backgroundcolor of bargraph
  int value_Pix;
  int valueI_Pix;
  value_Pix = map(value_rnd, 0, 100, 0, 32);
  valueI_Pix = 32 - value_Pix;
  tft.drawRect(STEP_FRAME_W * XPos, STEP_FRAME_H * (YPos - 1), STEP_FRAME_W, STEP_FRAME_H * 2, ILI9341_WHITE);
  tft.fillRect(STEP_FRAME_W * XPos + 1, STEP_FRAME_H * (YPos - 1) + 1, STEP_FRAME_W - 2, valueI_Pix - 2, ILI9341_DARKGREY);
  tft.fillRect(STEP_FRAME_W * XPos + 1, STEP_FRAME_H * (YPos + 1) - value_Pix + 1, STEP_FRAME_W - 2, value_Pix - 2, color);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * XPos - 3, STEP_FRAME_H * (YPos + 1) + 4);
  tft.print(fName);
  tft.setCursor(STEP_FRAME_W * XPos + 3, STEP_FRAME_H * YPos + 4);
  tft.print(value_rnd);
}

void drawPot(byte xPos, byte yPos, float fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color
  float circlePos;  
  circlePos = fvalue / 50;

  tft.fillCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 21, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 3, STEP_FRAME_H * (yPos + 1) + 6);
  tft.print(dname);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((3 * circlePos) + 1.37), STEP_FRAME_H * yPos + 16 * sin((3 * circlePos) + 1.37), 4, color);
}

void clearWorkSpace() {                                                                                  //clear the whole grid from Display
  tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H, STEP_FRAME_W * 20, STEP_FRAME_H * 13, ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
  tft.fillRect(STEP_FRAME_W, STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H * 12, ILI9341_DARKGREY);
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