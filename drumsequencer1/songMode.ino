int PHRASE_SEGMENT_LENGTH = 8;
byte pageNumber = 0;
int arrangment1[8][64] {
  //1 2  3  4   5  6  7  8   9  10 11 12  13 14 15 16  17 18 19 20  21 22 23 24  25 26 27 28  29 30 32 33  34 35 36 37  38 39 40 41  42 43 44 45  46 47 48 49  50 51 52 53  54 55 56 57  58 59 60 61  62 63 64 65  //phrases
  //1 5  9 13   17 21 25 29  33 37 41 45  49 53 57 61  65 69 73 77  81 85 89 93  97 101 5 9   13 17 21 25  29 33 37 41  45 49 53 57  61 65 69 73  77 81 85 89  93 97  201    5  9 13 17  21 25 29 33 237 41 45 49  //bars
  {0, 1, -1, 1,  1, 1, 1, 1,  2, 2, 2, 2,  2, 2, 2, 2,  1, 1, 1, 1,  2, 2, 2, 2,  2, 2, 2, 2,  2, 2, 2, 2,  2, 2, 2, 2,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, -1}, //channel 1
  {0, 0, -1, -1,  3, 1, 1, 1,  3, 1, 1, 1,  3, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, -1}, //channel 2
  {1, -1, -1, -1,  1, -1, -1, -1,  1, -1, -1, -1,  1, -1, -1, -1,  2, 2, -1, -1,  2, 2, -1, -1,  2, 2, -1, -1,  2, 2, -1, -1,  3, 3, 3, -1,  3, 3, 3, -1,  3, 3, 3, -1,  3, 3, 3, -1,  4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4}, //channel 3
  {1, 1, -1, -1, -1, -1, -1, -1,  1, 1, -1, -1, -1, -1, -1, -1,  1, 1, -1, -1, -1, -1, -1, -1,  1, 1, -1, -1, -1, -1, -1, -1,  1, 1, 1, 1, -1, -1, -1, -1,  1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, -1}, //channel 4
  {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1,  1, 1, 1, 1,  1, 1, -1, -1, -1, -1, -1, -1,  1, 1, 1, 1,  1, 1, -1, -1, -1, -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1,  1, 1, 1, -1}, //channel 5
  {0, -1, 1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, -1}, //channel 6
  {0, -1, -1, -1, -1, -1, 1, 1, -1, -1, -1, -1, -1, -1, 1, 1, -1, -1, -1, -1, -1, -1, 1, 1, -1, -1, -1, -1, -1, -1, 1, 1, -1, -1, -1, -1, -1, -1, 1, 1, -1, -1, -1, -1, -1, -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //channel 7
  {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1,  1, 1, 1, 1,  1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1,  1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1}, //channel 8
};

void gridSongModePage_1 () {   //static Display rendering
  tft.fillRect(STEP_FRAME_W, STEP_FRAME_H, 15, 192, ILI9341_DARKGREY);
  clearWorkSpace();
  tft.drawRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H*10, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.drawRect(STEP_FRAME_W * 19, STEP_FRAME_H*10, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);

  tft.drawRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 11, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.drawRect(STEP_FRAME_W * 19, STEP_FRAME_H * 11, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * 18 + 3, STEP_FRAME_H*10 + 4);
  tft.print("1x");
  tft.setCursor(STEP_FRAME_W * 19 + 3, STEP_FRAME_H*10 + 4);
  tft.print("2x");
  tft.setCursor(STEP_FRAME_W * 18 + 3, STEP_FRAME_H * 11 + 4);
  tft.print("3x");
  tft.setCursor(STEP_FRAME_W * 19 + 3, STEP_FRAME_H * 11 + 4);
  tft.print("4x");


  for (byte pages = 0; pages < 4; pages++) {
    tft.drawRect(STEP_FRAME_W * 18 + 1, ((pages + 1)) * STEP_FRAME_H * 2, STEP_FRAME_W * 2 - 1, STEP_FRAME_H * 2, ILI9341_WHITE);
    tft.setFont(Arial_12);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(STEP_FRAME_W * 18 + 12, ((pages + 1)) * STEP_FRAME_H * 2 + 12);
    tft.print(pages + 1);
  }
  int shownLines = 257 / PHRASE_SEGMENT_LENGTH;
  for (int f = 0; f < shownLines; f++) {     //do this for all phrases
    //vertical Line
    tft.drawFastVLine((f * PHRASE_SEGMENT_LENGTH) + 32, STEP_FRAME_H, STEP_FRAME_H * 12, 360); //(x, y-start, y-length, color)
    if (f % 4 == 0) {
      //vertical Line
      tft.drawFastVLine((f * PHRASE_SEGMENT_LENGTH) + 32, STEP_FRAME_H, STEP_FRAME_H * 12, 370); //(x, y-start, y-length, color)
    }
    tft.drawFastVLine(288, STEP_FRAME_H, STEP_FRAME_H * 12, 370); // last vertical line(x, y-start, y-length, color)
  }
}


void songModePage() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ts.touched()) {
      TS_Point p = ts.getPoint();
      gridTouchX = map(p.x, 180, 3730, 0, 19);  // mapping the touch coordinates to a grid of 20
      gridTouchY = map(p.y, 260, 3760, 0, 14);  //mapping the touch coordinates to a grid of 15
      for (byte pages = 0; pages < 4; pages++) {
        if (gridTouchX >= 18 && gridTouchY >= (pages + 1) * 2 && gridTouchY <= ((pages + 1) * 2) + 1) { //page selection
          pageNumber = pages;
          clearWorkSpace();
          gridSongModePage_1();
          songModePage();
        }
      }
      if (gridTouchX == 18 && gridTouchY == 10) { //page
        PHRASE_SEGMENT_LENGTH = 2;
        gridSongModePage_1();
        songModePage();
      }
      if (gridTouchX == 19 && gridTouchY == 10) { //page
        PHRASE_SEGMENT_LENGTH = 4;
        gridSongModePage_1();
        songModePage();
      }
      if (gridTouchX == 18 && gridTouchY == 11) { //page
        PHRASE_SEGMENT_LENGTH = 8;
        gridSongModePage_1();
        songModePage();
      }
      if (gridTouchX == 19 && gridTouchY == 11) { //page
        PHRASE_SEGMENT_LENGTH = 16;
        gridSongModePage_1();
        songModePage();
      }
    }
      byte page_start = pageNumber * PHRASE_SEGMENT_LENGTH;
      byte page_end = (pageNumber + 1) * PHRASE_SEGMENT_LENGTH;
      for (byte phrase = page_start ; phrase < page_end * (16 / PHRASE_SEGMENT_LENGTH) ; phrase++) {
        for (byte track = 0 ; track < 8 ; track++) {
          if (arrangment1[track][phrase] >= 0) {
            for (int thickness = -8; thickness < 8; thickness++) {
              tft.drawFastHLine((phrase - pageNumber * 16) * PHRASE_SEGMENT_LENGTH + STEP_FRAME_W * 2, ((track + 1) * TRACK_FRAME_H + thickness) + 4, PHRASE_SEGMENT_LENGTH, trackColor[track]); //(x-start, y, length, color)
            }
            if ( PHRASE_SEGMENT_LENGTH == 16) {
              tft.setFont(Arial_10);
              tft.setTextColor(ILI9341_WHITE);
              tft.setCursor((phrase - pageNumber * 16) * PHRASE_SEGMENT_LENGTH + STEP_FRAME_W * 2 + 6, (track + 1) * TRACK_FRAME_H - 1);
              tft.print(arrangment1[track][phrase]);
            }
          }
        }
      }
    }
  
}
