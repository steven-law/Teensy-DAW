#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3
#include <XPT2046_Touchscreen.h>
#include <SPI.h>

#define CS_PIN  8
#define TFT_DC  9
#define TFT_CS 10
// MOSI=11, MISO=12, SCK=13

XPT2046_Touchscreen ts(CS_PIN);
#define TIRQ_PIN  2

ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

unsigned long previousMillis = 0;
const long interval = 200;
int barClock = 0;


// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 180
#define TS_MINY 260
#define TS_MAXX 3730
#define TS_MAXY 3800

#define ch1COLOR 0
#define ch2COLOR 1
#define ch3COLOR 2
#define ch4COLOR 3
#define ch5COLOR 4
#define ch6COLOR 5
#define ch7COLOR 6
#define ch8COLOR 7
#define STEP_QUANT 16
#define STEP_FRAME_W 16
#define STEP_FRAME_H 16
#define TRACK_FRAME_H 24
#define SEQ_GRID_LEFT 2
#define SEQ_GRID_RIGHT 17
#define SEQ_GRID_TOP 1
#define SEQ_GRID_BOTTOM 12
#define GRID_LENGTH_HOR 256
#define GRID_LENGTH_VERT 192
#define POSITION_SCALE_BUTTON 18
#define POSITION_LOAD_BUTTON 15
#define POSITION_SAVE_BUTTON 13
#define POSITION_BPM_BUTTON 11
#define POSITION_STOP_BUTTON 10
#define POSITION_PLAY_BUTTON 8
#define POSITION_RECORD_BUTTON 7
#define POSITION_BAR_BUTTON 5
#define DOT_OFFSET_X 40  //STEP_FRAME_W * 2 + 8
#define DOT_OFFSET_Y 24  //STEP_FRAME_H + 8
#define DOT_RADIUS 5
#define OCTAVE_CHANGE_LEFTMOST 17
#define OCTAVE_CHANGE_RIGHTMOST 20
#define OCTAVE_CHANGE_UP_TOPMOST 1
#define OCTAVE_CHANGE_UP_BOTTOMMOST 4
#define OCTAVE_CHANGE_DOWN_TOPMOST 7
#define OCTAVE_CHANGE_DOWN_BOTTOMMOST 10
#define OCTAVE0 0
#define OCTAVE1 12
#define OCTAVE2 24
#define OCTAVE3 36
#define OCTAVE4 48
#define OCTAVE5 60
#define OCTAVE6 72
#define OCTAVE7 84
#define CHORD_QUANT 7


int trackColor[8] {6150246, 3326604, 1095334, 8678659, 6003265, 7678932, 12943157, 8044207};
int step_Frame_X;
int step_Frame_Y;
int gridTouchX;            //decided to handle touchthingys with a grid, so here it is, 20 grids
int gridTouchY;            //decided to handle touchthingys with a grid, so here it is, 15 grids
int trackTouchY;



bool scaleSelect = LOW;
bool songSelectPage_1 = LOW;     // a handler to keep the mode active after selecting
bool songSelectPage_2 = LOW;     // a handler to keep the mode active after selecting
bool songSelectPage_3 = LOW;     // a handler to keep the mode active after selecting
bool songSelectPage_4 = LOW;     // a handler to keep the mode active after selecting
bool channel1Select = LOW;     // a handler to keep the mode active after selecting
bool channel2Select = LOW;     // a handler to keep the mode active after selecting
bool channel3Select = LOW;     // a handler to keep the mode active after selecting
bool channel4Select = LOW;     // a handler to keep the mode active after selecting
bool channel5Select = LOW;     // a handler to keep the mode active after selecting
bool channel6Select = LOW;     // a handler to keep the mode active after selecting
bool channel7Select = LOW;     // a handler to keep the mode active after selecting
bool channel8Select = LOW;
bool chordSelect = LOW;



//Scales
const int scalesQuant = 9;     //how many scales do we have
int scaleSelected = 0;         //variable for scale selecting
char* noteNames[12] =          //notenames that are printed on the left
{"C", "C#", "D", "D#",  "E",  "F", "F#", "G", "G#", "A", "A#", "B"};
int scales[scalesQuant][12] {  //bool array for greying out notes that are not in the scale
  {1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1},  //Chromatic
  {1, 0, 1, 0, 1, 1,  0, 1, 0, 1, 0, 1},  //Major
  {1, 0, 1, 1, 0, 1,  0, 1, 1, 0, 1, 0},  //Natural Minor
  {1, 0, 1, 1, 0, 1,  0, 1, 1, 0, 0, 1},  //Harmonic Minor
  {1, 0, 1, 1, 0, 1,  0, 1, 0, 1, 0, 1},  //Melodic Minor
  {1, 0, 1, 1, 0, 1,  0, 1, 0, 1, 1, 0},  //Dorian
  {1, 0, 1, 0, 1, 1,  0, 1, 0, 1, 1, 0},  //Mixolydian
  {1, 1, 0, 1, 0, 1,  0, 1, 1, 0, 1, 0},  //Phrygian
  {0, 0, 1, 0, 1, 0,  1, 1, 0, 1, 0, 1}   //Lydian
};
char* scaleNames[scalesQuant] = {"Chromatic", "Major", "Natural Minor", "Harmonic Minor", "Melodic Minor", "Dorian", "Mixolydian", "Phrygian", "Lydian"}; // Scale Names for selecting
char* scaleNamesShort[scalesQuant] = {"Chrom", "Major", "NatMi", "HarMi", "MelMi", "Dor", "Mixol", "Phryg", "Lyd"}; // Scale Names for selecting







void setup() {
  Serial.begin(38400);
  usbMIDI.setHandleClock(myClock);
  usbMIDI.setHandleContinue(myContinue);
  usbMIDI.setHandleStop(myStop);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  ts.begin();
  ts.setRotation(3);
  while (!Serial && (millis() <= 1000));
  startUpScreen();
}


void loop() {
  noInterrupts();
  usbMIDI.read();


  interrupts();
  showCoordinates ();
  TS_Point p = ts.getPoint();
  if (ts.touched()) {
    gridTouchX = map(p.x, 180, 3730, 0, 19);
    gridTouchY = map(p.y, 260, 3760, 0, 14);
    trackTouchY = map(p.y, 630, 3290, 1, 8);


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Scale Select
    if (gridTouchX >= 18 && gridTouchY == 0) {
      scaleSelect = HIGH;
      channel2Select = LOW;
      channel8Select = LOW;
      channel4Select = LOW;
      channel6Select = LOW;
      channel5Select = LOW;
      channel3Select = LOW;
      channel7Select = LOW;

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

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select Songarranger and make some static graphics
    if (gridTouchX == 0 && gridTouchY == 0) {
      songSelectPage_1 = HIGH;
      songSelectPage_2 = LOW;
      channel2Select = LOW;
      channel8Select = LOW;
      channel4Select = LOW;
      channel6Select = LOW;
      channel5Select = LOW;
      channel3Select = LOW;
      channel7Select = LOW;
      scaleSelect = LOW;
      channel1Select = LOW;
      gridSongModePage_1();
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select Drumchannel and make some static graphics
    if (gridTouchX == 0 && trackTouchY == 1) {
      channel1Select = HIGH;
      channel2Select = LOW;
      channel8Select = LOW;
      channel4Select = LOW;
      channel6Select = LOW;
      channel5Select = LOW;
      channel3Select = LOW;
      channel7Select = LOW;
      scaleSelect = LOW;
      songSelectPage_1 = LOW;
      songSelectPage_2 = LOW;
      gridchannel1Sequencer();
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select channel2 and make some static graphics
    if (gridTouchX == 0 && trackTouchY == 2) {
      channel2Select = HIGH;
      channel8Select = LOW;
      channel4Select = LOW;
      channel6Select = LOW;
      channel5Select = LOW;
      channel3Select = LOW;
      channel7Select = LOW;
      scaleSelect = LOW;
      songSelectPage_1 = LOW;
      songSelectPage_2 = LOW;
      channel1Select = LOW;
      gridchannel2Sequencer();
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select channel3 and make some static graphics
    if (gridTouchX == 0 && trackTouchY == 3) {
      channel3Select = HIGH;
      channel8Select = LOW;
      channel4Select = LOW;
      channel6Select = LOW;
      channel5Select = LOW;
      channel7Select = LOW;
      channel2Select = LOW;
      scaleSelect = LOW;
      songSelectPage_1 = LOW;
      songSelectPage_2 = LOW;
      channel1Select = LOW;
      gridchannel3Sequencer();
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select channel4 and make some static graphics
    if (gridTouchX == 0 && trackTouchY == 4) {
      channel4Select = HIGH;
      channel8Select = LOW;
      channel7Select = LOW;
      channel6Select = LOW;
      channel5Select = LOW;
      channel3Select = LOW;
      channel2Select = LOW;
      scaleSelect = LOW;
      songSelectPage_1 = LOW;
      songSelectPage_2 = LOW;
      channel1Select = LOW;
      gridchannel4Sequencer();
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select channel5 and make some static graphics
    if (gridTouchX == 0 && trackTouchY == 5) {
      channel5Select = HIGH;
      channel8Select = LOW;
      channel7Select = LOW;
      channel6Select = LOW;
      channel4Select = LOW;
      channel3Select = LOW;
      channel2Select = LOW;
      scaleSelect = LOW;
      songSelectPage_1 = LOW;
      songSelectPage_2 = LOW;
      channel1Select = LOW;
      gridchannel5Sequencer();
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select channel6 and make some static graphics
    if (gridTouchX == 0 && trackTouchY == 6) {
      channel6Select = HIGH;
      channel8Select = LOW;
      channel7Select = LOW;
      channel4Select = LOW;
      channel5Select = LOW;
      channel3Select = LOW;
      channel2Select = LOW;
      scaleSelect = LOW;
      songSelectPage_1 = LOW;
      songSelectPage_2 = LOW;
      channel1Select = LOW;
      gridchannel6Sequencer();
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select channel7 and make some static graphics
    if (gridTouchX == 0 && trackTouchY == 7) {
      channel7Select = HIGH;
      channel8Select = LOW;
      channel4Select = LOW;
      channel6Select = LOW;
      channel5Select = LOW;
      channel3Select = LOW;
      channel2Select = LOW;
      scaleSelect = LOW;
      songSelectPage_1 = LOW;
      songSelectPage_2 = LOW;
      channel1Select = LOW;
      gridchannel7Sequencer();
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select channel8 and make some static graphics
    if (gridTouchX == 0 && trackTouchY == 8) {
      channel8Select = HIGH;
      channel4Select = LOW;
      channel7Select = LOW;
      channel6Select = LOW;
      channel5Select = LOW;
      channel3Select = LOW;
      channel2Select = LOW;
      scaleSelect = LOW;
      songSelectPage_1 = LOW;
      songSelectPage_2 = LOW;
      channel1Select = LOW;
      gridchannel8Sequencer();
    }
  }
  if (scaleSelect == HIGH) {
    scaleSelector();
  }
  if (songSelectPage_1 == HIGH) {
    songModePage();
  }
  //    if (songSelectPage_1 == HIGH) {
  //      songModePage_1();
  //    }
  //    if (songSelectPage_2 == HIGH) {
  //      songModePage_2();
  //    }
  //    if (songSelectPage_3 == HIGH) {
  //      songModePage_3();
  //    }
  //      if (songSelectPage_4 == HIGH) {
  //      songModePage_4();
  //    }

  if (channel1Select == HIGH) {
    channel1Sequencer();
  }

  if (channel2Select == HIGH) {
    channel2Sequencer();
  }

  if (channel3Select == HIGH) {
    channel3Sequencer();
  }
  if (channel4Select == HIGH) {
    channel4Sequencer();
  }
  if (channel5Select == HIGH) {
    channel5Sequencer();
  }
  if (channel6Select == HIGH) {
    channel6Sequencer();
  }
  if (channel7Select == HIGH) {
    channel7Sequencer();
  }
  if (channel8Select == HIGH) {
    channel8Sequencer();
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
  tft.drawRect(STEP_FRAME_W * POSITION_SCALE_BUTTON, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);

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

    tft.fillRect(STEP_FRAME_W * POSITION_BAR_BUTTON - 1, 2, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 3, ILI9341_DARKGREY);
    tft.setTextColor(ILI9341_WHITE);
    tft.setFont(Arial_9);
    tft.setCursor(STEP_FRAME_W * POSITION_BAR_BUTTON + 2, 3);
    tft.print(barClock);
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
        tft.fillRect(STEP_FRAME_W * 18 + 1, 1, STEP_FRAME_W * 2 - 2 , STEP_FRAME_H - 2, ILI9341_DARKGREY); //Xmin, Ymin, Xlength, Ylength, color
        tft.setCursor(STEP_FRAME_W * 18 + 2, 2);
        tft.setFont(Arial_8);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.print(scaleNamesShort[scaleSelected]);
      }
    }
  }
}

void drawMelodicSequencerStatic(int color) {
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
    tft.fillRect(STEP_FRAME_W * 2 * ClipNr + STEP_FRAME_W * 2, STEP_FRAME_H * 13, STEP_FRAME_W * 2, STEP_FRAME_H, trackColor[color] + ClipNr * 20);
    tft.setCursor(STEP_FRAME_W * 2 * ClipNr + STEP_FRAME_W * 2 + 2, STEP_FRAME_H * 13 + 4);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(1);
    tft.print("Clip ");
    tft.print(ClipNr + 1);
  }
  for (int i = 0; i < 12; i++) {
    if (scales[scaleSelected][i] == HIGH) {
      tft.fillRect(STEP_FRAME_W, STEP_FRAME_H * i + STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H, trackColor[color]);
    }
  }
  //draw Octavebuttons
  tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 2, STEP_FRAME_W * 2, STEP_FRAME_H * 8, ILI9341_DARKGREY);
  tft.fillTriangle(STEP_FRAME_W * 18, STEP_FRAME_H * 4, STEP_FRAME_W * 20, STEP_FRAME_H * 4, STEP_FRAME_W * 19, STEP_FRAME_H * 2, ILI9341_LIGHTGREY);  //x1, y1, x2, y2, x3, y3
  tft.fillTriangle(STEP_FRAME_W * 18, STEP_FRAME_H * 8, STEP_FRAME_W * 20, STEP_FRAME_H * 8, STEP_FRAME_W * 19, STEP_FRAME_H * 10, ILI9341_LIGHTGREY);  //x1, y1, x2, y2, x3, y3
  tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 4, STEP_FRAME_W * 2, STEP_FRAME_H * 4, ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * 18 + 12, STEP_FRAME_H * 5 + 8);
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
void clearStepsGridY () {
  for (int T = 0; T < 12; T++) {

    tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, T * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, ILI9341_DARKGREY); // circle: x, y, radius, color
  }
}
