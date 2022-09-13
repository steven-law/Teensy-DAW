#include <Audio.h>
#include <Wire.h>
#include <SerialFlash.h>
#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include <SD.h>
#include "FifteenStep.h"
#include "variables.h"


//calibration and customizing
//Pinout for screen
#define TIRQ_PIN     2    //alternate Pins: any digital pin
#define CS_PIN       8    //alternate Pins: any digital pin
#define TFT_DC       15   //alternate Pins 9, 10, 20, 21
#define TFT_CS       10   //alternate Pins 9, 15, 20, 21
#define TFT_RST      255  // 255 = unused, connect to 3.3V
#define TFT_MOSI     11   //shareable
#define TFT_SCLK     13   //shareable
#define TFT_MISO     12   //shareable

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

//noteOn velocity for all tracks
#define VELOCITY 96  

// set initial tempo
int tempo = 120;

//individual trackcolors
int trackColor[9] {6150246, 8256638, 1095334, 12643941, 2583100, 9365295, 12943157, 5678954, ILI9341_WHITE};
//end of calibration and custumizing



//initiate the modules
FifteenStep seq = FifteenStep(SEQUENCER_MEMORY);                                         //initiate Sequencer
File myFile;                                                                             //initiate SDCard Reader
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);      //initiate TFT-Srceen
XPT2046_Touchscreen ts(CS_PIN);                                                          //initiate Touchscreen



//Place for the Pluginconnections
// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drum1;          //xy=137.40005493164062,89.00000762939453
AudioMixer4              mixer1;         //xy=355.40000915527344,119.00000381469727
AudioOutputPT8211        pt8211_1;       //xy=662.0000076293945,105.00000190734863
AudioConnection          patchCord1(drum1, 0, mixer1, 0);
AudioConnection          patchCord2(mixer1, 0, pt8211_1, 0);
AudioConnection          patchCord3(mixer1, 0, pt8211_1, 1);
// GUItool: end automatically generated code









void setup() {
  Serial.begin(31250); // set MIDI baud
  AudioMemory(15);
  // start sequencer and set callbacks
  seq.begin(tempo, steps);
  seq.setStepHandler(step);
  seq.stop();

  /// set the default channel of each
  track[0].MIDIchannel = 10;
  track[1].MIDIchannel = 2;
  track[2].MIDIchannel = 3;
  track[3].MIDIchannel = 4;
  track[4].MIDIchannel = 5;
  track[5].MIDIchannel = 6;
  track[6].MIDIchannel = 7;
  track[7].MIDIchannel = 8;

//load the pluginsettings
  drumSettings();
  
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  ts.begin();
  ts.setRotation(3);
  while (!Serial && (millis() <= 1000));
  startUpScreen();

  
}


void loop() {

  usbMIDI.read();
  // this is needed to keep the sequencer
  // running. there are other methods for
  // start, stop, and pausing the steps
  seq.run();
  Potentiometer1 = analogRead(A13);

  showCoordinates ();
  TS_Point p = ts.getPoint();
  if (ts.touched()) {
    gridTouchX = map(p.x, 180, 3730, 0, 19);
    gridTouchY = map(p.y, 260, 3760, 0, 14);
    trackTouchY = map(p.y, 620, 3120, 0, 7);
    constrainedtrackTouchY = constrain(trackTouchY, 0, 7);
    //    Serial.print(p.y);
    //    Serial.print("--");
    //    Serial.print(trackTouchY);
    //    Serial.print("--");
    //    Serial.println(constrainedtrackTouchY);
    //    Serial.println(analogRead(A1));

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
        tft.fillRect(STEP_FRAME_W * 2, STEP_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
        tft.fillRect(STEP_FRAME_W * 2, SONG_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
        tft.fillRect(STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y, STEP_FRAME_W * 16, 4, ILI9341_DARKGREY);
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //arrangmentSelect button
      if (gridTouchX == POSITION_ARR_BUTTON || gridTouchX == POSITION_ARR_BUTTON + 1) {
        arrangmentSelect = map(Potentiometer1, 0, 1023, 0, 7);
        tft.fillRect(STEP_FRAME_W * POSITION_ARR_BUTTON + 2, 1, STEP_FRAME_W * 2 - 3 , STEP_FRAME_H - 2, ILI9341_DARKGREY); //Xmin, Ymin, Xlength, Ylength, color
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
        tft.fillRect(STEP_FRAME_W * POSITION_BPM_BUTTON + 2, 1, STEP_FRAME_W * 2 - 4 , STEP_FRAME_H - 2, ILI9341_DARKGREY); //Xmin, Ymin, Xlength, Ylength, color
        tft.setCursor(STEP_FRAME_W * POSITION_BPM_BUTTON + 2, 3);
        tft.setFont(Arial_10);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.print(tempoSelect);
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //Scale Select
      if (gridTouchX == POSITION_SCALE_BUTTON || gridTouchX == POSITION_SCALE_BUTTON + 1) {
        scaleSelect = HIGH;
        track[1].select = LOW;
        track[7].select = LOW;
        track[3].select = LOW;
        track[5].select = LOW;
        track[4].select = LOW;
        track[2].select = LOW;
        track[6].select = LOW;

        songSelectPage_1 = LOW;
        songSelectPage_2 = LOW;
        channel1Select = LOW;
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
    if (gridTouchX == 0) {  //Songmode- and Trackselection
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select Songarranger and make some static graphics
      if (gridTouchY == 0) {
        songSelectPage_1 = HIGH;
        songSelectPage_2 = LOW;
        track[1].select = LOW;
        track[7].select = LOW;
        track[3].select = LOW;
        track[5].select = LOW;
        track[4].select = LOW;
        track[2].select = LOW;
        track[6].select = LOW;
        scaleSelect = LOW;
        channel1Select = LOW;
        gridSongModePage_1();
      }
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select Drumchannel and make some static graphics
      if (trackTouchY == 0) {
        channel1Select = HIGH;
        track[1].select = LOW;
        track[7].select = LOW;
        track[3].select = LOW;
        track[5].select = LOW;
        track[4].select = LOW;
        track[2].select = LOW;
        track[6].select = LOW;
        scaleSelect = LOW;
        songSelectPage_1 = LOW;
        songSelectPage_2 = LOW;
        griddrumStepSequencer();
      }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select channel2 and make some static graphics
      if (trackTouchY == 1) {
        track[1].select = HIGH;
        track[7].select = LOW;
        track[3].select = LOW;
        track[5].select = LOW;
        track[4].select = LOW;
        track[2].select = LOW;
        track[6].select = LOW;
        scaleSelect = LOW;
        songSelectPage_1 = LOW;
        songSelectPage_2 = LOW;
        channel1Select = LOW;
        gridStepSequencer(1);
      }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select channel3 and make some static graphics
      if (trackTouchY == 2) {
        track[2].select = HIGH;
        track[7].select = LOW;
        track[3].select = LOW;
        track[5].select = LOW;
        track[4].select = LOW;
        track[6].select = LOW;
        track[1].select = LOW;
        scaleSelect = LOW;
        songSelectPage_1 = LOW;
        songSelectPage_2 = LOW;
        channel1Select = LOW;
        gridStepSequencer(2);
      }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select channel4 and make some static graphics
      if (trackTouchY == 3) {
        track[3].select = HIGH;
        track[7].select = LOW;
        track[6].select = LOW;
        track[5].select = LOW;
        track[4].select = LOW;
        track[2].select = LOW;
        track[1].select = LOW;
        scaleSelect = LOW;
        songSelectPage_1 = LOW;
        songSelectPage_2 = LOW;
        channel1Select = LOW;
        gridStepSequencer(3);
      }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select channel5 and make some static graphics
      if (trackTouchY == 4) {
        track[4].select = HIGH;
        track[7].select = LOW;
        track[6].select = LOW;
        track[5].select = LOW;
        track[3].select = LOW;
        track[2].select = LOW;
        track[1].select = LOW;
        scaleSelect = LOW;
        songSelectPage_1 = LOW;
        songSelectPage_2 = LOW;
        channel1Select = LOW;
        gridStepSequencer(4);
      }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select channel6 and make some static graphics
      if (trackTouchY == 5) {
        track[5].select = HIGH;
        track[7].select = LOW;
        track[6].select = LOW;
        track[3].select = LOW;
        track[4].select = LOW;
        track[2].select = LOW;
        track[1].select = LOW;
        scaleSelect = LOW;
        songSelectPage_1 = LOW;
        songSelectPage_2 = LOW;
        channel1Select = LOW;
        gridStepSequencer(5);
      }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select channel7 and make some static graphics
      if (trackTouchY == 6) {
        track[6].select = HIGH;
        track[7].select = LOW;
        track[3].select = LOW;
        track[5].select = LOW;
        track[4].select = LOW;
        track[2].select = LOW;
        track[1].select = LOW;
        scaleSelect = LOW;
        songSelectPage_1 = LOW;
        songSelectPage_2 = LOW;
        channel1Select = LOW;
        gridStepSequencer(6);
      }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //  select channel8 and make some static graphics
      if (trackTouchY == 7) {
        track[7].select = HIGH;
        track[3].select = LOW;
        track[6].select = LOW;
        track[5].select = LOW;
        track[4].select = LOW;
        track[2].select = LOW;
        track[1].select = LOW;
        scaleSelect = LOW;
        songSelectPage_1 = LOW;
        songSelectPage_2 = LOW;
        channel1Select = LOW;
        gridStepSequencer(7);
      }
    }
  }
  //setting up the scaleSelector-view
  if (scaleSelect == HIGH) {
    scaleSelector();
  }
  //setting up the songMode-view
  if (songSelectPage_1 == HIGH) {
    songModePage();
  }

  //setting up the melodicStepSequencer-view for drumtrack #1
  if (channel1Select == HIGH) {
    drumStepSequencer();
  }

  //setting up the melodicStepSequencer-view for #2-8
  for (int i = 1; i < 8; i++) {
    if (track[i].select) {
      melodicStepSequencer(i);
    }
  }
}

void savebutton () {
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

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
  }
  else {
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
  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
void loadbutton () {
  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    bool debug_load = true;
    bool loading_error = !myFile.available();
    for (byte tracks = 0;  !loading_error && tracks < 8; tracks++) {
      if (debug_load) Serial.printf("Starting read track %i:-\n", tracks);
      for (byte clips = 0;  !loading_error && clips < 9; clips++) {
        if (debug_load) Serial.printf("\tStarting read clips %i:-\n", clips);
        for (byte steps = 0;  !loading_error && steps < 16; steps++) {
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
  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void startUpScreen () {   //static Display rendering
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
    tft.fillRect(1, TRACK_FRAME_H * otherTracks - 8, 15, TRACK_FRAME_H, trackColor[otherTracks - 1]); //Xmin, Ymin, Xlength, Ylength, color
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
  tft.drawRect(STEP_FRAME_W * POSITION_PLAY_BUTTON - 2, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE); //PLAY RECT FRAME
  tft.fillTriangle(STEP_FRAME_W * POSITION_PLAY_BUTTON + 10, 3, STEP_FRAME_W * POSITION_PLAY_BUTTON + 10, 13, STEP_FRAME_W * POSITION_PLAY_BUTTON + 20, 8, ILI9341_GREEN); // x1, y1, x2, y2, x3, y3

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
void showCoordinates () {
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

void gridScaleSelector () {   //static Display rendering
  clearWorkSpace();
  tft.drawRect(STEP_FRAME_W * 2, STEP_FRAME_H, STEP_FRAME_W * 16 , STEP_FRAME_H * 12, ILI9341_WHITE); //Xmin, Ymin, Xlength, Ylength, color
}
void scaleSelector () {
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
        tft.fillRect(STEP_FRAME_W * POSITION_SCALE_BUTTON + 1, 1, STEP_FRAME_W * 2 - 2 , STEP_FRAME_H - 2, ILI9341_DARKGREY); //Xmin, Ymin, Xlength, Ylength, color
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
  for (int i = 0; i < 17; i++) {   //vert Lines
    step_Frame_X = i * STEP_FRAME_W;
    tft.drawFastVLine(step_Frame_X + STEP_FRAME_W * 2, 16, GRID_LENGTH_VERT, ILI9341_WHITE); //(x, y-start, length, color)
  }
  for (int i = 0; i < 13; i++) {   //hor lines
    step_Frame_Y = i * 16;
    tft.drawFastHLine(STEP_FRAME_W * 2, step_Frame_Y + STEP_FRAME_H, GRID_LENGTH_HOR, ILI9341_WHITE); //(x-start, y, length, color)
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
  tft.fillTriangle(leftmost + 1, UP_bottommost,  rightmost, UP_bottommost,  leftmost + STEP_FRAME_W , UP_topmost, ILI9341_LIGHTGREY);  //octave arrow up
  tft.fillTriangle(leftmost + 1, DOWN_topmost, rightmost - 2, DOWN_topmost, leftmost + STEP_FRAME_W , DOWN_bottommost, ILI9341_LIGHTGREY);  //x1, y1, x2, y2, x3, y3
  tft.fillRect(leftmost + 1, UP_bottommost, STEP_FRAME_W * 2, STEP_FRAME_H * 3+1, ILI9341_DARKGREY);
  tft.setCursor(leftmost + 12, STEP_FRAME_H * 4 + 8);
  tft.setFont(Arial_16);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);

  //draw Notenames
  for (int n = 0; n < 12; n++) {   //hor notes
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
}

void clearWorkSpace () {    //clear the whole grid from Display
  tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H, STEP_FRAME_W * 20 , STEP_FRAME_H * 13, ILI9341_DARKGREY); //Xmin, Ymin, Xlength, Ylength, color
  tft.fillRect(STEP_FRAME_W, STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H * 12, ILI9341_DARKGREY);
}
void clearStepsGrid () {   // clear all Steps from Display
  for (int T = 0; T < 12; T++) {
    for (int S = 0; S < 16; S++) {
      tft.fillCircle(S * STEP_FRAME_W + DOT_OFFSET_X, T * STEP_FRAME_H + 24, DOT_RADIUS, ILI9341_DARKGREY); // circle: x, y, radius, color
    }
  }
}
void clearStepsGridY () {  // clear all Steps in the same column
  for (int T = 0; T < 12; T++) {

    tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, T * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, ILI9341_DARKGREY); // circle: x, y, radius, color
  }
}
