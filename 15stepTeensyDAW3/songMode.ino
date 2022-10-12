void drawsongmodepageselector() {
  //draw 16 rects of 16x16px in the 13th row
  for (byte pages = 2; pages < 18; pages++) {
    drawActiveSquare(pages, 13, 1, selectPage[pages + 8], "", ILI9341_LIGHTGREY);
    tft.drawRect(STEP_FRAME_W * pages, STEP_FRAME_H * 13, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(STEP_FRAME_W * pages + 3, STEP_FRAME_H * 13 + 4);
    tft.print((pages - 1));
  }
}
void drawarrengmentLines(byte songpageNumber) {
  page_phrase_start = songpageNumber * 16;
  page_phrase_end = (songpageNumber + 1) * 16;

  //draw horizontal song arrangment Lines
  for (byte phrase = page_phrase_start; phrase < page_phrase_end; phrase++) {
    for (byte trackss = 0; trackss < 8; trackss++) {
      if (track[trackss].arrangment1[phrase] > 0) {
        for (int thickness = -8; thickness < 8; thickness++) {
          tft.drawFastHLine((phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2, ((trackss + 1) * TRACK_FRAME_H + thickness) + 4, phraseSegmentLength, trackColor[trackss]);  //(x-start, y, length, color)
          if (track[trackss].arrangment1[phrase] == 0) {
            tft.drawFastHLine((phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2, ((trackss + 1) * TRACK_FRAME_H + thickness) + 4, phraseSegmentLength, ILI9341_DARKGREY);  //(x-start, y, length, color)
          }
        }
        tft.setFont(Arial_10);
        tft.setTextColor(ILI9341_WHITE);
        tft.setCursor((phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2 + 6, (trackss + 1) * TRACK_FRAME_H - 1);
        tft.print(track[trackss].arrangment1[phrase]);
      }
    }
  }
}


void draw_start_of_loop() {
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * 18 + 4, STEP_FRAME_H + 4);
  tft.print("S");
  tft.print(start_of_loop_old);
  tft.drawRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 1, STEP_FRAME_W * 2 - 1, STEP_FRAME_H, ILI9341_WHITE);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * 18 + 4, STEP_FRAME_H + 4);
  tft.print("S");
  tft.print(start_of_loop);
  start_of_loop_old = start_of_loop;
}
void draw_end_of_loop() {
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * 18 + 4, STEP_FRAME_H * 2 + 4);
  tft.print("E");
  tft.print(end_of_loop_old);
  tft.drawRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 2, STEP_FRAME_W * 2 - 1, STEP_FRAME_H, ILI9341_WHITE);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * 18 + 4, STEP_FRAME_H * 2 + 4);
  tft.print("E");
  tft.print(end_of_loop);
  end_of_loop_old = end_of_loop;
}

void gridSongMode(byte songpageNumber) {  //static Display rendering
  page_phrase_start = songpageNumber * 16;
  page_phrase_end = (songpageNumber + 1) * 16;
  clearWorkSpace();
  drawsongmodepageselector();
  drawActiveSquare(18, 3, 2, false, "clear", ILI9341_RED);
  draw_start_of_loop();
  draw_end_of_loop();
  //occationally working on a full arrangment view
  //drawActiveSquare(18, 3, 2, selectPage[10], "zoom", ILI9341_LIGHTGREY);

  //vertical pointer Lines
  int shownLines = 257 / phraseSegmentLength;
  for (int f = 0; f < shownLines; f++) {                                                      //do this for all phrases
    tft.drawFastVLine((f * phraseSegmentLength) + 32, STEP_FRAME_H, STEP_FRAME_H * 12, 360);  //(x, y-start, y-length, color)
    if (f % 4 == 0) {
      tft.drawFastVLine((f * phraseSegmentLength) + 32, STEP_FRAME_H, STEP_FRAME_H * 12, 370);  //(x, y-start, y-length, color)
    }
  }

  if (songpageNumber == 16) {
    //drawarrengmentLinesZoom();
  } else {
    drawarrengmentLines(songpageNumber);
  }
}

void songModePage(byte songpageNumber) {
  page_phrase_start = songpageNumber * 16;
  page_phrase_end = (songpageNumber + 1) * 16;
  //Serial.println("zoom-dynamic");


  if (ts.touched()) {
    int touched_phrase = gridTouchX - 2 + (16 * songpageNumber);
    byte touched_track = trackTouchY;

    if (songpageNumber == 16) {
      //drawarrengmentLinesZoom();
    } else {
      //Clip Selector
      if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && trackTouchY >= 0 && trackTouchY < 8) {
        track[touched_track].arrangment1[touched_phrase] = map(Potentiometer1, 0, 1023, 0, 8);
        //draw horizontal song arrangment Lines
        drawarrengmentLines(songpageNumber);
      }
    }


    //Start of loop
    if (gridTouchX >= 18 && gridTouchY == 1) {
      start_of_loop = map(Potentiometer1, 0, 1023, 0, 254);
      draw_start_of_loop();
    }
    //end of loop
    if (gridTouchX >= 18 && gridTouchY == 2) {
      end_of_loop = map(Potentiometer1, 0, 1023, 1, 255);
      draw_end_of_loop();
    }
    //page selection
    if (gridTouchY == 13) {
      for (int songpages = 0; songpages < 16; songpages++) {
        if (gridTouchX == (songpages + 2)) {
          //phraseSegmentLength = 16;
          select_page(SONGMODE_PAGE_1 + songpages);
          gridSongMode(songpages);
          songModePage(songpages);
        }
      }
    }
    //clear arrangment selection
    if (gridTouchX >= 18) {
      if (gridTouchY == 3 || gridTouchY == 4) {
        for (byte ctrack = 0; ctrack < 8; ctrack++) {
          for (byte cphrase = 0; cphrase < 255; cphrase++) {
            track[ctrack].arrangment1[cphrase] = 0;
          }
        }
      }
    }
    /** //zoom selection
    if (gridTouchX >= 18) {
      if (gridTouchY == 3 || gridTouchY == 4) {
        //phraseSegmentLength = 1;
        select_page(9);
        gridSongMode(16);
        songModePage(16);
      }
    }*/
  }
}