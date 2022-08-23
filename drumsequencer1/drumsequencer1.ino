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

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 180
#define TS_MINY 260
#define TS_MAXX 3730
#define TS_MAXY 3800

#define STEP_FRAME_W 16
#define STEP_FRAME_H 16
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
#define OCTAVE_CHANGE_CLEAR_RECT_LEFT_TOP
int trackColor[8] {6150246, 3326604, 1095334, 8678659, 6003265, 7678932, 12943157, 8044207};
int step_Frame_X;
int step_Frame_Y;
int touchX;
int touchY;
int gridTouchX;            //decided to handle touchthingys with a grid, so here it is, 20 grids
int gridTouchY;            //decided to handle touchthingys with a grid, so here it is, 15 grids




bool scaleSelect = LOW;
bool songSelect = LOW;     // a handler to keep the mode active after selecting
bool drumSelect = LOW;     // a handler to keep the mode active after selecting
bool channel2Select = LOW;     // a handler to keep the mode active after selecting
bool channel3Select = LOW;     // a handler to keep the mode active after selecting

bool arrangment1[16][51] {
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

//drumchannel
int dClip = 0;         //variable for clipselecting
bool drumbeat[8][12][16] {     //bool array for [clip][instruments][steps]
  { //clip0
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  },
  { //clip1
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}
  },
  { //clip2
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}
  },
  { //clip3
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}
  },
  { //clip4
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}
  },
  { //clip5
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}
  },
  { //clip6
    {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}
  },
  { //clip7
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  },
};

int sixteenthStep;


int fullNotes[8][12] {
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
  {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23},
  {24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35},
  {36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47},
  {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59},
  {60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71},
  {72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83},
  {84, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94}
};

byte ch2NoteValue;

int notesCh3[12] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int octavesCh3 = 3;
bool channel3loop[12][16] {
  {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};


void setup() {
  Serial.begin(38400);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  ts.begin();
  ts.setRotation(3);
  while (!Serial && (millis() <= 1000));

  startUpScreen();
}

boolean wastouched = true;


void loop() {
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
      scaleSelect = HIGH;
      songSelect = LOW;
      drumSelect = LOW;
      channel2Select = LOW;
      channel3Select = LOW;
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
      scaleSelect = LOW;
      drumSelect = LOW;
      channel2Select = LOW;
      channel3Select = LOW;
      gridSongMode();
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select Drumchannel and make some static graphics
    if (gridTouchX == 0 && gridTouchY == 1) {
      drumSelect = HIGH;
      scaleSelect = LOW;
      songSelect = LOW;
      channel2Select = LOW;
      channel3Select = LOW;
      gridDrumSequencer();
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select channel2 and make some static graphics
    if (gridTouchX == 0 && gridTouchY == 2) {
      channel2Select = HIGH;
      channel3Select = LOW;
      scaleSelect = LOW;
      songSelect = LOW;
      drumSelect = LOW;
      gridchannel2Sequencer();
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  select channel2 and make some static graphics
    if (gridTouchX == 0 && gridTouchY == 3) {
      channel3Select = HIGH;
      channel2Select = LOW;
      scaleSelect = LOW;
      songSelect = LOW;
      drumSelect = LOW;
      gridchannel3Sequencer();
    }
  }
  if (scaleSelect == HIGH) {
    scaleSelector();
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

}



void startUpScreen () {   //static Display rendering
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_BLACK);
  tft.setFont(Arial_9);
  tft.fillRect(1, 1, 15, 16, ILI9341_MAGENTA);  //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(4, 3);
  tft.print("S");
  tft.fillRect(1, STEP_FRAME_H, 15, STEP_FRAME_H, trackColor[0]);  //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(4, 18);
  tft.print("D");
  tft.fillRect(1, STEP_FRAME_H * 2, 15, STEP_FRAME_H, trackColor[1]); //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(4, 34);
  tft.print("2");
  tft.fillRect(1, STEP_FRAME_H * 3, 15, STEP_FRAME_H, trackColor[2]); //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(4, 50);
  tft.print("3");
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

}
void showCoordinates () {
  tft.fillRect(0, 230, 320, 10, ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
  tft.setTextColor(ILI9341_GREEN);
  tft.setFont(Arial_10);
  tft.setCursor(20, 230);
  tft.print("X = ");
  tft.print(gridTouchX);
  tft.setCursor(60, 230);
  tft.print("Y = ");
  tft.print(gridTouchY);
  tft.print("  note = ");
  tft.print(ch2NoteValue);
  delay(100);
}

void gridScaleSelector () {   //static Display rendering
  clearWorkSpace();
  tft.drawRect(STEP_FRAME_W * 2, STEP_FRAME_H, STEP_FRAME_W * 16 , STEP_FRAME_H * 12, ILI9341_WHITE); //Xmin, Ymin, Xlength, Ylength, color
}
void scaleSelector () {
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
      //      scaleSelect = LOW;
      //      delay(100);
      //      tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H, STEP_FRAME_W * 20 , STEP_FRAME_H * 14, ILI9341_DARKGREY); //Xmin, Ymin, Xlength, Ylength, color
      //            gridSongMode();
      //            songSelect = HIGH;
      //      startUpScreen();
    }
  }
  delay(100);
}

void gridSongMode () {   //static Display rendering
  tft.fillRect(STEP_FRAME_W, STEP_FRAME_H, 15, 192, ILI9341_DARKGREY);
  clearWorkSpace();
  //      for (int16_t i = 1; i < 9; i++) {   //do this for all channels
  for (int f = 0; f < 27; f++) {     //do this for all phrases
    //vertical Line
    tft.drawFastVLine((f * 8) + 32, 16, 128, 360); //(x, y-start, length, color)
    if (f % 4 == 0) {
      //vertical Line
      tft.drawFastVLine((f * 8) + 32, 16, 128, 370); //(x, y-start, length, color)
      //      tft.setCursor((f * 8) + 10, 175);
      //      tft.setFont(Arial_8);
      //      tft.setTextColor(ILI9341_WHITE);
      //      tft.setTextSize(1);
      //      tft.print((f * 8));
    }
  }
}
void songMode() {
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
  delay(100);
}

void gridDrumSequencer () {   //static Display rendering
  clearWorkSpace();
  drawDrumSequencerStatic(0);
  for (int i = 1; i < 13; i++) {
    tft.setCursor(18, STEP_FRAME_H * i + 2);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(1);
    tft.print(i);
  }
}
void drumSequencer() {
  TS_Point p = ts.getPoint();
  touchX = map(p.x, 180, 3730, 0, 320);
  touchY = map(p.y, 260, 3760, 0, 240);
  gridTouchX = map(p.x, 180, 3730, 0, 19);
  gridTouchY = map(p.y, 260, 3760, 0, 14);
  for (int T = 0; T < 12; T++) {
    for (int S = 0; S < 16; S++) {
      if (drumbeat[dClip][T][S] == HIGH) {
        tft.fillCircle(S * STEP_FRAME_W + DOT_OFFSET_X, T * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, trackColor[0]); // circle: x, y, radius, color
      }
    }
  }
  if (ts.touched()) {
    if (gridTouchX => SEQ_GRID_LEFT && gridTouchX =< SEQ_GRID_RIGHT  && gridTouchY => SEQ_GRID_TOP && gridTouchY =< SEQ_GRID_BOTTOM) {
      if (drumbeat[dClip][gridTouchY - 1][gridTouchX - 2] == LOW) {
        drumbeat[dClip][gridTouchY - 1][gridTouchX - 2] = HIGH;
        tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, trackColor[0]); //draw the active step circles
      }
      else if (drumbeat[dClip][gridTouchY - 1][gridTouchX - 2] == HIGH) {
        drumbeat[dClip][gridTouchY - 1][gridTouchX - 2] = LOW;
        tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, ILI9341_DARKGREY); //draw the active step circles
      }
    }
    if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
      dClip = (gridTouchX / 2) - 1;
      clearStepsGrid();
    }
  }
  delay(100);
}


void gridchannel3Sequencer () {   //static Display rendering
  clearWorkSpace();
  drawMelodicSequencerStatic(2);
  tft.print(octavesCh3);
  //test Github test
}
void channel3Sequencer () {


  TS_Point p = ts.getPoint();
  touchX = map(p.x, 180, 3730, 0, 320);
  touchY = map(p.y, 260, 3760, 0, 240);
  gridTouchX = map(p.x, 180, 3730, 0, 19);
  gridTouchY = map(p.y, 260, 3760, 0, 14);
  for (int T = 0; T < 12; T++) {
    for (int S = 0; S < 16; S++) {

      if (channel3loop[T][S] == HIGH) {
        tft.fillCircle(S * STEP_FRAME_W + DOT_OFFSET_X, T * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, trackColor[2]); // circle: x, y, radius, color
      }
    }
  }



  if (ts.touched()) {
    if (gridTouchX > OCTAVE_CHANGE_LEFTMOST && gridTouchX < OCTAVE_CHANGE_RIGHTMOST  && gridTouchY > OCTAVE_CHANGE_UP_TOPMOST && gridTouchY < OCTAVE_CHANGE_UP_BOTTOMMOST) {
      octavesCh3--;
    }
    if (gridTouchX > OCTAVE_CHANGE_LEFTMOST && gridTouchX < OCTAVE_CHANGE_RIGHTMOST  && gridTouchY > OCTAVE_CHANGE_DOWN_TOPMOST && gridTouchY < OCTAVE_CHANGE_DOWN_BOTTOMMOST) {
      octavesCh3++;
    }
    tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 4, STEP_FRAME_W * 2, STEP_FRAME_H * 4, ILI9341_DARKGREY);
    tft.setCursor(STEP_FRAME_W * 18 + 12, STEP_FRAME_H * 5 + 8);
    tft.setFont(Arial_16);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(1);
    tft.print(octavesCh3);

    if (gridTouchX > 1 && gridTouchX < 18  && gridTouchY > 0 && gridTouchY < 13) {
      if (channel3loop[gridTouchY - 1][gridTouchX - 2] == LOW) {
        channel3loop[gridTouchY - 1][gridTouchX - 2] = HIGH;
        tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, trackColor[2]); //draw the active step circles
      }
      else if (channel3loop[gridTouchY - 1][gridTouchX - 2] == HIGH) {
        channel3loop[gridTouchY - 1][gridTouchX - 2] = LOW;
        tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, ILI9341_DARKGREY); //draw the active step circles
      }
    }
  }
  delay(100);
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
  tft.fillRect(STEP_FRAME_W * 18, STEP_FRAME_H * 2, STEP_FRAME_W * 2, STEP_FRAME_H * 8, ILI9341_DARKGREY);
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
  //draw active steps
  for (int i = 0; i < 12; i++) {
    if (scales[scaleSelected][i] == HIGH) {
      tft.fillRect(STEP_FRAME_W, STEP_FRAME_H * i + STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H, trackColor[color]);
    }
  }
}

void clearWorkSpace () {    //clear the whole grid from Display
  tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H, STEP_FRAME_W * 20 , STEP_FRAME_H * 14, ILI9341_DARKGREY); //Xmin, Ymin, Xlength, Ylength, color
  tft.fillRect(STEP_FRAME_W, STEP_FRAME_H, 15, STEP_FRAME_H * 12, ILI9341_DARKGREY);
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

    tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, T * STEP_FRAME_H + 24, DOT_RADIUS, ILI9341_DARKGREY); // circle: x, y, radius, color
  }
}
