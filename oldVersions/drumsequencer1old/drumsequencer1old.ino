#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include <font_AwesomeF000.h>

#define CS_PIN  8
#define TFT_DC  9
#define TFT_CS 10
// MOSI=11, MISO=12, SCK=13

XPT2046_Touchscreen ts(CS_PIN);
#define TIRQ_PIN  2

ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

unsigned long previousMillis = 0;
const long interval = 200;

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 180
#define TS_MINY 260
#define TS_MAXX 3730
#define TS_MAXY 3800

#define ch2COLOR 1
#define ch3COLOR 2
#define ch4COLOR 3
#define ch5COLOR 4
#define ch6COLOR 5
#define ch7COLOR 6
#define ch8COLOR 7
#define STEP_FRAME_W 16
#define STEP_FRAME_H 16
#define STEP_QUANT 16
#define SEQ_GRID_LEFT 2
#define SEQ_GRID_RIGHT 17
#define SEQ_GRID_TOP 1
#define SEQ_GRID_BOTTOM 12
#define GRID_LENGTH_HOR 256
#define GRID_LENGTH_VERT 192
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
#define MAX_VOICES 4
#define CHORD_QUANT 7
int trackColor[8] {6150246, 3326604, 1095334, 8678659, 6003265, 7678932, 12943157, 8044207};
int step_Frame_X;
int step_Frame_Y;
int touchX;
int touchY;
int gridTouchX;            //decided to handle touchthingys with a grid, so here it is, 20 grids
int gridTouchY;            //decided to handle touchthingys with a grid, so here it is, 15 grids


int sixteenthClock = 0;

bool scaleSelect = LOW;
bool songSelect = LOW;     // a handler to keep the mode active after selecting
bool drumSelect = LOW;     // a handler to keep the mode active after selecting
bool channel2Select = LOW;     // a handler to keep the mode active after selecting
bool channel3Select = LOW;     // a handler to keep the mode active after selecting
bool channel4Select = LOW;     // a handler to keep the mode active after selecting
bool channel5Select = LOW;     // a handler to keep the mode active after selecting
bool channel6Select = LOW;     // a handler to keep the mode active after selecting
bool channel7Select = LOW;     // a handler to keep the mode active after selecting
bool channel8Select = LOW;     // a handler to keep the mode active after selecting
bool chordSelect = LOW;

bool arrangment1[8][51] {
  // 1  5  9 13  17 21 25 29  33 37 41 45  49 53 57 61  65 69 73 77  81 85 89 93  97 101 5  9  13 17 21 25  29 33 37 41  45 49 53 57  61 65 69 73  77 81 85 89  93 97  201
  {1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1,  0}, //channel 1
  {0, 0, 0, 0,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1,  0}, //channel 2
  {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  0, 0, 0, 0,  0, 0,  0}, //channel 3
  {1, 1, 0, 0,  0, 0, 0, 0,  1, 1, 0, 0,  0, 0, 0, 0,  1, 1, 0, 0,  0, 0, 0, 0,  1, 1, 0, 0,  0, 0, 0, 0,  1, 1, 1, 1,  0, 0, 0, 0,  1, 1, 0, 0,  0, 0, 0, 0,  1, 1,  0}, //channel 4
  {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 1, 1,  1, 1, 1, 1,  1, 1, 0, 0,  0, 0, 0, 0,  1, 1, 1, 1,  1, 1, 0, 0,  0, 0, 1, 1,  1, 1, 1, 1,  1, 1,  0}, //channel 5
  {0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1,  0}, //channel 6
  {0, 0, 0, 0,  0, 0, 1, 1,  0, 0, 0, 0,  0, 0, 1, 1,  0, 0, 0, 0,  0, 0, 1, 1,  0, 0, 0, 0,  0, 0, 1, 1,  0, 0, 0, 0,  0, 0, 1, 1,  0, 0, 0, 0,  0, 0, 1, 1,  0, 0,  0}, //channel 7
  {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 1, 1,  1, 1, 1, 1,  1, 1, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 1, 1,  1, 1, 1, 1,  1, 1,  0}, //channel 8
};

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
char* chordNames[CHORD_QUANT] = {"Minor 7th", "Minor 9th", "Major 7th", "Major 9th", "Maus", "HAse", "Hund"};
char* chordNamesShort[CHORD_QUANT] = {"Min7", "Min9", "Maj7", "Maj9", "Ma", "HA", "HU"};
int chordSelected = 0;




void setup() {
  Serial.begin(38400);
//  usbMIDI.setHandleClock(myClock);
//  usbMIDI.setHandleContinue(myContinue);
//  usbMIDI.setHandleStop(myStop);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  ts.begin();
  ts.setRotation(3);
  while (!Serial && (millis() <= 1000));

  startUpScreen();
}



void loop() {
//  usbMIDI.read();

  unsigned long currentMillis = millis();
  showCoordinates ();
boolean istouched = ts.touched();
  TS_Point p = ts.getPoint();
  if (ts.touched()) {
    touchX = map(p.x, 180, 3730, 0, 320);
    touchY = map(p.y, 260, 3760, 0, 240);
    gridTouchX = map(p.x, 180, 3730, 0, 19);
    gridTouchY = map(p.y, 260, 3760, 0, 14);


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Scale Select
    if (gridTouchX >= 18 && gridTouchY == 0) {
      songSelect = LOW;
      drumSelect = LOW;
      channel2Select = LOW;
      channel3Select = LOW;
      channel4Select = LOW;
      channel5Select = LOW;
      channel6Select = LOW;
      channel7Select = LOW;
      channel8Select = LOW;
      scaleSelect = HIGH;
      chordSelect = LOW;
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
      songSelect = HIGH;
      drumSelect = LOW;
      channel2Select = LOW;
      channel3Select = LOW;
      channel4Select = LOW;
      channel5Select = LOW;
      channel6Select = LOW;
      channel7Select = LOW;
      channel8Select = LOW;
      scaleSelect = LOW;
      chordSelect = LOW;
      gridSongMode();
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select Drumchannel and make some static graphics
    if (gridTouchX == 0 && gridTouchY == 1) {
      songSelect = LOW;
      drumSelect = HIGH;
      channel2Select = LOW;
      channel3Select = LOW;
      channel4Select = LOW;
      channel5Select = LOW;
      channel6Select = LOW;
      channel7Select = LOW;
      channel8Select = LOW;
      scaleSelect = LOW;
      chordSelect = LOW;
      gridDrumSequencer();
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select channel2 and make some static graphics
    if (gridTouchX == 0 && gridTouchY == 2) {
      songSelect = LOW;
      drumSelect = LOW;
      channel2Select = HIGH;
      channel3Select = LOW;
      channel4Select = LOW;
      channel5Select = LOW;
      channel6Select = LOW;
      channel7Select = LOW;
      channel8Select = LOW;
      scaleSelect = LOW;
      chordSelect = LOW;
      gridchannel2Sequencer();
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select channel3 and make some static graphics
    if (gridTouchX == 0 && gridTouchY == 3) {
      songSelect = LOW;
      drumSelect = LOW;
      channel2Select = LOW;
      channel3Select = HIGH;
      channel4Select = LOW;
      channel5Select = LOW;
      channel6Select = LOW;
      channel7Select = LOW;
      channel8Select = LOW;
      scaleSelect = LOW;
      chordSelect = LOW;
      gridchannel3Sequencer();
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select channel4 and make some static graphics
    if (gridTouchX == 0 && gridTouchY == 4) {
      songSelect = LOW;
      drumSelect = LOW;
      channel2Select = LOW;
      channel3Select = LOW;
      channel4Select = HIGH;
      channel5Select = LOW;
      channel6Select = LOW;
      channel7Select = LOW;
      channel8Select = LOW;
      scaleSelect = LOW;
      chordSelect = LOW;
      gridchannel4Sequencer();
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select channel5 and make some static graphics
    if (gridTouchX == 0 && gridTouchY == 5) {
      songSelect = LOW;
      drumSelect = LOW;
      channel2Select = LOW;
      channel3Select = LOW;
      channel4Select = LOW;
      channel5Select = HIGH;
      channel6Select = LOW;
      channel7Select = LOW;
      channel8Select = LOW;
      scaleSelect = LOW;
      chordSelect = LOW;
      gridchannel5Sequencer();
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select channel6 and make some static graphics
    if (gridTouchX == 0 && gridTouchY == 6) {
      songSelect = LOW;
      drumSelect = LOW;
      channel2Select = LOW;
      channel3Select = LOW;
      channel4Select = LOW;
      channel5Select = LOW;
      channel6Select = HIGH;
      channel7Select = LOW;
      channel8Select = LOW;
      scaleSelect = LOW;
      chordSelect = LOW;
      gridchannel6Sequencer();
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select channel7 and make some static graphics
    if (gridTouchX == 0 && gridTouchY == 7) {
      songSelect = LOW;
      drumSelect = LOW;
      channel2Select = LOW;
      channel3Select = LOW;
      channel4Select = LOW;
      channel5Select = LOW;
      channel6Select = LOW;
      channel7Select = HIGH;
      channel8Select = LOW;
      scaleSelect = LOW;
      chordSelect = LOW;
      gridchannel7Sequencer();
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select channel8 and make some static graphics
    if (gridTouchX == 0 && gridTouchY == 8) {
      songSelect = LOW;
      drumSelect = LOW;
      channel2Select = LOW;
      channel3Select = LOW;
      channel4Select = LOW;
      channel5Select = LOW;
      channel6Select = LOW;
      channel7Select = LOW;
      channel8Select = HIGH;
      scaleSelect = LOW;
      chordSelect = LOW;
      gridchannel8Sequencer();
    }
  }
  if (scaleSelect == HIGH) {
    scaleSelector();
  }
  if (chordSelect == HIGH) {
    chordSelector();
  }
  if (songSelect == HIGH) {
    songMode();
  }

  if (drumSelect == HIGH) {
    drumSequencer();
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
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_9);
  tft.drawRect(STEP_FRAME_W * 10 - 2, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * 10 + 2, 3);
  tft.print("128");

  tft.setTextColor(ILI9341_BLACK);
  tft.fillRect(1, 1, 15, 16, ILI9341_MAGENTA);  //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(4, 3);
  tft.print("S");
  tft.fillRect(1, STEP_FRAME_H, 15, STEP_FRAME_H, trackColor[0]);  //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(4, 18);
  tft.print("D");
  tft.fillRect(1, STEP_FRAME_H * 2, 15, STEP_FRAME_H, trackColor[1]); //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(4, 34);
  tft.print("M");
  tft.fillRect(1, STEP_FRAME_H * 3, 15, STEP_FRAME_H, trackColor[2]); //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(4, 50);
  tft.print("C");
  tft.fillRect(1, STEP_FRAME_H * 4, 15, STEP_FRAME_H, trackColor[3]); //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(4, 66);
  tft.print("4");
  tft.fillRect(1, STEP_FRAME_H * 5, 15, STEP_FRAME_H, trackColor[4]); //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(4, 82);
  tft.print("5");
  tft.fillRect(1, STEP_FRAME_H * 6, 15, STEP_FRAME_H, trackColor[5]); //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(4, 98);
  tft.print("6");
  tft.fillRect(1, STEP_FRAME_H * 7, 15, STEP_FRAME_H, trackColor[6]); //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(4, 114);
  tft.print("7");
  tft.fillRect(1, STEP_FRAME_H * 8, 15, STEP_FRAME_H, trackColor[7]); //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(4, 130);
  tft.print("8");
  tft.drawRect(STEP_FRAME_W * 18, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);
  tft.drawRect(STEP_FRAME_W * 8 - 2, 0, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.setTextColor(ILI9341_GREEN);
  tft.setFont(AwesomeF000_10);
  tft.setCursor(STEP_FRAME_W * 8, 1);
  tft.print("K");
  tft.drawRect(STEP_FRAME_W * 9 - 2, 0, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(STEP_FRAME_W * 9, 1);
  tft.print("M");
  tft.drawRect(STEP_FRAME_W * 7 - 2, 0, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.fillCircle(STEP_FRAME_W * 7 + 5, 7, DOT_RADIUS + 1, ILI9341_RED); // circle: x, y, radius, color

}
void showCoordinates () {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 50) {
    previousMillis = currentMillis;
    tft.fillRect(20, 0, 80, 13, ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
    tft.setTextColor(ILI9341_GREEN);
    tft.setFont(Arial_10);
    tft.setCursor(20, 3);
    tft.print("X");
    tft.print(gridTouchX);
    tft.setCursor(50, 3);
    tft.print("Y");
    tft.print(gridTouchY);
    tft.setCursor(80, 3);
    tft.print(sixteenthClock);
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

void chordSelector () {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    for (int i = 0; i < CHORD_QUANT; i++) {
      tft.setCursor(STEP_FRAME_W * 2, STEP_FRAME_H * i + STEP_FRAME_H);
      tft.setFont(Arial_8);
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(1);
      tft.print(chordNames[i]);

      if (gridTouchX > 1 && gridTouchX < 15 && gridTouchY == i + 1) {
        chordSelected = i;
        tft.drawRect(STEP_FRAME_W * 18, STEP_FRAME_H, STEP_FRAME_W * 2 , STEP_FRAME_H, ILI9341_WHITE); //Xmin, Ymin, Xlength, Ylength, color
        tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H + 1, STEP_FRAME_W * 2 - 2 , STEP_FRAME_H - 2, ILI9341_DARKGREY); //Xmin, Ymin, Xlength, Ylength, color
        tft.setCursor(STEP_FRAME_W * 18 + 2, STEP_FRAME_H + 2);
        tft.setFont(Arial_8);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.print(chordNamesShort[chordSelected]);
      }
    }
  }
}

void gridSongMode () {   //static Display rendering
  tft.fillRect(STEP_FRAME_W, STEP_FRAME_H, STEP_FRAME_W * 19, STEP_FRAME_H * 13, ILI9341_DARKGREY);
  clearWorkSpace();
  for (int f = 0; f < 27; f++) {     //do this for all phrases
    //vertical Line
    tft.drawFastVLine((f * 8) + 32, 16, 128, 360); //(x, y-start, length, color)
    if (f % 4 == 0) {
      //vertical Line
      tft.drawFastVLine((f * 8) + 32, 16, 128, 370); //(x, y-start, length, color)
    }
  }
}
void songMode() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    for (int16_t i = 1; i < 9; i++) {   //do this for all channels
      for (int f = 0; f < 52; f++) {     //do this for all phrases
        // arrangment lines
        if (arrangment1[i - 1][f] == HIGH) {
          for (int w = -4; w < 4; w++) {
            tft.drawFastHLine(f * 4 + 32, (i * 16 + w) + 8, 4, trackColor[i - 1]); //(x-start, y, length, color)
          }
        }
      }
    }
  }
}



void drawMelodicSequencerStatic(int color) {
  //draw the Main Grid
  for (int i = 0; i <= STEP_QUANT; i++) {   //vert Lines
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
void drawDrumSequencerStatic (int color) {
  tft.fillRect(STEP_FRAME_W, STEP_FRAME_H, 15, 192, trackColor[color]);
  //draw main Grid
  for (int i = 0; i <= STEP_QUANT; i++) {   //vert Lines
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
  //draw active steps
  for (int i = 0; i < 12; i++) {
    if (scales[scaleSelected][i] == HIGH) {
      tft.fillRect(STEP_FRAME_W, STEP_FRAME_H * i + STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H, trackColor[color]);
    }
  }
}

void clearWorkSpace () {    //clear the whole grid from Display
  tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H, STEP_FRAME_W * 20 , STEP_FRAME_H * 13, ILI9341_DARKGREY); //Xmin, Ymin, Xlength, Ylength, color
  tft.fillRect(STEP_FRAME_W, STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H * 12, ILI9341_DARKGREY);
}
void clearStepsGrid () {   // clear all Steps from Display
  for (int T = 0; T < 12; T++) {
    for (int S = 0; S < STEP_QUANT; S++) {
      tft.fillCircle(S * STEP_FRAME_W + DOT_OFFSET_X, T * STEP_FRAME_H + 24, DOT_RADIUS, ILI9341_DARKGREY); // circle: x, y, radius, color
    }
  }
}
void clearStepsGridY () {
  for (int T = 0; T < 12; T++) {

    tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, T * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, ILI9341_DARKGREY); // circle: x, y, radius, color
  }
}
