


void gridSongModePage_1 () {   //static Display rendering
  tft.fillRect(STEP_FRAME_W, STEP_FRAME_H, 15, 192, ILI9341_DARKGREY);
  clearWorkSpace();

  //zooming
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.drawRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 11, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * 18 + 3, STEP_FRAME_H * 11 + 4);
  tft.print("1x");
  tft.drawRect(STEP_FRAME_W * 19, STEP_FRAME_H * 11, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * 19 + 3, STEP_FRAME_H * 11 + 4);
  tft.print("2x");
  tft.drawRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 12, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * 18 + 3, STEP_FRAME_H * 12 + 4);
  tft.print("3x");
  tft.drawRect(STEP_FRAME_W * 19, STEP_FRAME_H * 12, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * 19 + 3, STEP_FRAME_H * 12 + 4);
  tft.print("4x");


  //songlength
  //start of loop
  tft.drawRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 1, STEP_FRAME_W * 2 - 1, STEP_FRAME_H, ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * 18 + 4, STEP_FRAME_H + 4);
  tft.print("S");
  tft.print(start_of_loop + 1);
  //end of loop
  tft.drawRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 2, STEP_FRAME_W * 2 - 1, STEP_FRAME_H, ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * 18 + 4, STEP_FRAME_H * 2 + 4);
  tft.print("E");
  tft.print(end_of_loop + 1);


  //selecting pages
  for (byte pages = 0; pages < 4; pages++) {
    tft.drawRect(STEP_FRAME_W * 18 + 1, ((pages + 1)) * STEP_FRAME_H * 2 + STEP_FRAME_H, STEP_FRAME_W * 2 - 1, STEP_FRAME_H * 2, ILI9341_WHITE);
    tft.setFont(Arial_12);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(STEP_FRAME_W * 18 + 12, ((pages + 1)) * STEP_FRAME_H * 2 + STEP_FRAME_H + 12);
    tft.print(pages + 1);
  }
  //vertical pointer Lines
  int shownLines = 257 / phraseSegmentLength;
  for (int f = 0; f < shownLines; f++) {     //do this for all phrases
    tft.drawFastVLine((f * phraseSegmentLength) + 32, STEP_FRAME_H, STEP_FRAME_H * 12, 360); //(x, y-start, y-length, color)
    if (f % 4 == 0) {
      tft.drawFastVLine((f * phraseSegmentLength) + 32, STEP_FRAME_H, STEP_FRAME_H * 12, 370); //(x, y-start, y-length, color)
    }
    //last vertical gridline
    tft.drawFastVLine(288, STEP_FRAME_H, STEP_FRAME_H * 12, 370); // last vertical line(x, y-start, y-length, color)
  }

}


void songModePage() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ts.touched()) {
      TS_Point p = ts.getPoint();

      int touched_phrase = gridTouchX - 2;
      byte touched_track = trackTouchY;

      //song length
      //start of loop
//      if (gridTouchX >= 18 && gridTouchY == 1) {
//        start_of_loop = map(Potentiometer1, 0, 1023, 0, 254);
//        tft.fillRect(STEP_FRAME_W * 18 + 2, STEP_FRAME_H + 1, STEP_FRAME_W * 2 - 3, STEP_FRAME_H - 2, ILI9341_DARKGREY);
//        tft.setFont(Arial_8);
//        tft.setTextColor(ILI9341_WHITE);
//        tft.setCursor(STEP_FRAME_W * 18 + 4, STEP_FRAME_H + 4);
//        tft.print("S");
//        tft.print(start_of_loop+1);
//      }
      //end of loop
      if (gridTouchX >= 18 && gridTouchY == 2) {
        end_of_loop = map(Potentiometer1, 0, 1023, 1, 255);
        tft.fillRect(STEP_FRAME_W * 18 + 2, STEP_FRAME_H*2 + 1, STEP_FRAME_W * 2 - 3, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        tft.setFont(Arial_8);
        tft.setTextColor(ILI9341_WHITE);
        tft.setCursor(STEP_FRAME_W * 18 + 4, STEP_FRAME_H * 2 + 4);
        tft.print("E");
        tft.print(end_of_loop + 1);
      }
      //page selection
      for (byte pages = 0; pages < 4; pages++) {
        if (gridTouchX >= 18 && gridTouchY >= (pages + 2) * 2 && gridTouchY <= ((pages + 1) * 2) + 1) {
          pageNumber = pages;
          clearWorkSpace();
          gridSongModePage_1();
          songModePage();
        }
      }
      //zooming
      if (gridTouchX == 18 && gridTouchY == 11) { //page1
        phraseSegmentLength = 2;
        gridSongModePage_1();
        songModePage();
      }
      if (gridTouchX == 19 && gridTouchY == 11) { //page2
        phraseSegmentLength = 4;
        gridSongModePage_1();
        songModePage();
      }
      if (gridTouchX == 18 && gridTouchY == 12) { //page3
        phraseSegmentLength = 8;
        gridSongModePage_1();
        songModePage();
      }
      if (gridTouchX == 19 && gridTouchY == 12) { //page4
        phraseSegmentLength = 16;
        gridSongModePage_1();
        songModePage();
      }
      //Clip Selector
      if ( phraseSegmentLength == 16) {//only show clipselector when zoom is full in
        tft.drawRect(STEP_FRAME_W * 2, STEP_FRAME_H * 13, STEP_FRAME_W * 2, STEP_FRAME_H, trackColor[touched_track]); //draw a small rect to frame the clip info
        //        tft.fillTriangle(STEP_FRAME_W * 4, STEP_FRAME_H * 14, STEP_FRAME_W * 5, STEP_FRAME_H * 14, STEP_FRAME_W * 4 + 8, STEP_FRAME_H * 13, ILI9341_LIGHTGREY); //draw a triangle to change the clipNr  +1
        //        tft.fillTriangle(STEP_FRAME_W * 5, STEP_FRAME_H * 13, STEP_FRAME_W * 6, STEP_FRAME_H * 13, STEP_FRAME_W * 5 + 8, STEP_FRAME_H * 14, ILI9341_LIGHTGREY); //draw a triangle to change the clipNr  -1


        //if we touch any of the arranger lines the TrackNr and ClipNr are shown in a small rectangle on the bottom
        if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX < SEQ_GRID_RIGHT && trackTouchY >= 0 && trackTouchY < 7) {
          clip_to_change = arrangment1[touched_track][touched_phrase];
          tft.setFont(Arial_8);
          tft.setTextColor(ILI9341_WHITE);

          tft.fillRect(STEP_FRAME_W * 2 + 1, STEP_FRAME_H * 13 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
          tft.setCursor(STEP_FRAME_W * 2 + 2, STEP_FRAME_H * 13 + 4);
          tft.print("T");
          tft.print(touched_track + 1);
          tft.print("-");
          tft.print("C");
          tft.print(arrangment1[touched_track][touched_phrase] + 1);
          int clipassign = Potentiometer1;

          arrangment1[touched_track][touched_phrase] = map(clipassign, 0, 1023, -1, 7);

        }
      }
    }

    //draw horizontal song arrangment Lines
    byte page_start = pageNumber * phraseSegmentLength;
    byte page_end = (pageNumber + 1) * phraseSegmentLength;
    for (byte phrase = page_start ; phrase < page_end * (16 / phraseSegmentLength) ; phrase++) {
      for (byte track = 0 ; track < 8 ; track++) {
        if (arrangment1[track][phrase] >= 0) {
          for (int thickness = -8; thickness < 8; thickness++) {
            tft.drawFastHLine((phrase - pageNumber * 16) * phraseSegmentLength + STEP_FRAME_W * 2, ((track + 1) * TRACK_FRAME_H + thickness) + 4, phraseSegmentLength, trackColor[track]); //(x-start, y, length, color)
          }
          //only show clipnumbers when zoom is full in
          if ( phraseSegmentLength == 16) {
            tft.setFont(Arial_10);
            tft.setTextColor(ILI9341_WHITE);
            tft.setCursor((phrase - pageNumber * 16) * phraseSegmentLength + STEP_FRAME_W * 2 + 6, (track + 1) * TRACK_FRAME_H - 1);
            tft.print(arrangment1[track][phrase] + 1);
          }
        }
      }
    }
  }

}
