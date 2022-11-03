void drawsongmodepageselector() {
  //draw 16 rects of 16x16px in the 13th row
  for (byte pages = 2; pages < 18; pages++) {
    drawActiveRect(pages, 13, 1, 1, selectPage == pages + 8, "", ILI9341_LIGHTGREY);
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
      if (track[trackss].arrangment1[phrase] < 8) {
        for (int thickness = -8; thickness < 8; thickness++) {
          tft.drawFastHLine((phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2, ((trackss + 1) * TRACK_FRAME_H + thickness) + 4, phraseSegmentLength, trackColor[trackss]);  //(x-start, y, length, color)
                                                                                                                                                                                                    /* if (track[trackss].arrangment1[phrase] == 8) {
            tft.drawFastHLine((phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2, ((trackss + 1) * TRACK_FRAME_H + thickness) + 4, phraseSegmentLength, ILI9341_DARKGREY);  //(x-start, y, length, color)
          }*/
        }
        tft.setFont(Arial_10);
        tft.setTextColor(ILI9341_WHITE);
        tft.setCursor((phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2 + 6, (trackss + 1) * TRACK_FRAME_H - 1);
        tft.print(track[trackss].arrangment1[phrase]);
      }
    }
  }
}

void drawarrengmentLine(byte songpageNumber, byte touched_track, byte touched_phrase) {
  page_phrase_start = songpageNumber * 16;
  page_phrase_end = (songpageNumber + 1) * 16;

  //draw horizontal song arrangment Lines
  // for (byte phrase = page_phrase_start; phrase < page_phrase_end; phrase++) {
  //for (byte trackss = 0; trackss < 8; trackss++) {
  //if (track[trackss].arrangment1[phrase] < 8) {
  for (int thickness = -8; thickness < 8; thickness++) {
    tft.drawFastHLine((touched_phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2, ((touched_track + 1) * TRACK_FRAME_H + thickness) + 4, phraseSegmentLength, trackColor[touched_track]);  //(x-start, y, length, color)
  }


  tft.setFont(Arial_10);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor((touched_phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2 + 6, (touched_track + 1) * TRACK_FRAME_H - 1);
  tft.print(track[touched_track].arrangment1[touched_phrase]);
  //}
  //}
  //}
}
void clearArrangment() {
  for (byte ctrack = 0; ctrack < 8; ctrack++) {
    for (byte cphrase = 0; cphrase < 255; cphrase++) {
      track[ctrack].arrangment1[cphrase] = 8;
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
  tft.print(start_of_loop+1);
  start_of_loop_old = start_of_loop+1;
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
  drawActiveRect(18, 3, 2, 2, false, "clear", ILI9341_RED);
  draw_start_of_loop();
  draw_end_of_loop();
  //occationally working on a full arrangment view

  //vertical pointer Lines
  int shownLines = 257 / phraseSegmentLength;
  for (int f = 0; f < shownLines; f++) {                                                      //do this for all phrases
    tft.drawFastVLine((f * phraseSegmentLength) + 32, STEP_FRAME_H, STEP_FRAME_H * 12, 360);  //(x, y-start, y-length, color)
    if (f % 4 == 0) {
      tft.drawFastVLine((f * phraseSegmentLength) + 32, STEP_FRAME_H, STEP_FRAME_H * 12, 370);  //(x, y-start, y-length, color)
    }
  }
  drawarrengmentLines(songpageNumber);
}

void songModePage(byte songpageNumber) {
  page_phrase_start = songpageNumber * 16;
  page_phrase_end = (songpageNumber + 1) * 16;


  if (ts.touched() || !buttons[6].read()) {

    int touched_phrase = gridTouchX - 2 + (16 * songpageNumber);
    byte touched_track = trackTouchY;

    //Assigning clips to the arranger
    if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && trackTouchY >= 0 && trackTouchY < 8) {
      track[touched_track].arrangment1[touched_phrase] = map(Potentiometer1, 0, 127, 0, 8);
      //draw horizontal song arrangment Lines
      drawarrengmentLine(songpageNumber, touched_track, touched_phrase);
    }



    //Start of loop
    if (gridTouchX >= 18 && gridTouchY == 1) {
      start_of_loop = map(Potentiometer1, 0, 127, 0, 254);
      draw_start_of_loop();
    }
    //end of loop
    if (gridTouchX >= 18 && gridTouchY == 2) {
      end_of_loop = map(Potentiometer1, 0, 127, 1, 255);
      draw_end_of_loop();
    }
    //page selection
    if (gridTouchY == 13) {
      for (int songpages = 0; songpages < 16; songpages++) {
        if (gridTouchX == (songpages + 2)) {
          //phraseSegmentLength = 16;
          selectPage = SONGMODE_PAGE_1 + songpages;
          gridSongMode(songpages);
          songModePage(songpages);
        }
      }
    }
    //clear arrangment selection
    if (gridTouchX >= 18) {
      if (gridTouchY == 3 || gridTouchY == 4) {
        clearArrangment();
      }
    }
    //save and load
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savebutton();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadbutton();
      }
    }
  }
}



void savebutton() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing project.txt...");
  SD.remove("project.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening project.txt...");
  myFile = SD.open("project.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    //save arrangment
    tft.print("Writing songarrangment to project.txt...");
    for (byte ctrack = 0; ctrack < 8; ctrack++) {
      for (byte cphrase = 0; cphrase < 255; cphrase++) {
        myFile.print((char)track[ctrack].arrangment1[cphrase]);
      }
    }
    tft.println("Done");

    tft.print("Writing track 1 to project.txt...");
    //save plugin 1 variables
    saveTrack1();
    tft.println("Done");

    tft.print("Writing plugin 1 to project.txt...");
    //save plugin 1 variables
    savePlugin1();
    tft.println("Done");

    tft.print("Writing plugin 3 to project.txt...");
    //save plugin 3 variables
    savePlugin3();
    tft.println("Done");

    tft.print("Writing plugin 5 to project.txt...");
    //save plugin 5 variables
    savePlugin5();
    tft.println("Done");

    tft.print("Writing plugin 6 to project.txt...");
    //save plugin 6 variables
    savePlugin6();
    tft.println("Done");

    tft.print("Writing plugin 8 to project.txt...");
    //save plugin 8 variables
    savePlugin8();
    tft.println("Done");

    tft.print("Writing FX 1 to project.txt...");
    //save plugin 8 variables
    saveFX1();
    tft.println("Done");

    tft.print("Writing FX 2 to project.txt...");
    //save plugin 8 variables
    saveFX2();
    tft.println("Done");


    // close the file:
    myFile.close();
    tft.println("Saving done.");




    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening project.txt");
  }
}

void loadbutton() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("project.txt");
  if (myFile) {
    tft.println("opening project.txt:");

    // read from the file until there's nothing else in it:

    //load arrangment
    tft.print("Reading songarrangment from project.txt...");
    for (byte ctrack = 0; ctrack < 8; ctrack++) {
      for (byte cphrase = 0; cphrase < 255; cphrase++) {
        track[ctrack].arrangment1[cphrase] = myFile.read();
      }
    }
    tft.println("Done");

    //load track 1
    tft.print("Reading track1 from project.txt...");
    loadTrack1();
    tft.println("Done");

    //load plugin 1 variables
    tft.print("reading plugin 1 from project.txt...");
    loadPlugin1();
    tft.println("Done");

    //load plugin 3 variables
    tft.print("reading plugin 3 from project.txt...");
    loadPlugin3();
    tft.println("Done");

    //load plugin 5 variables
    tft.print("reading plugin 5 from project.txt...");
    loadPlugin5();
    tft.println("Done");

    //load plugin 6 variables
    tft.print("reading plugin 6 from project.txt...");
    loadPlugin6();
    tft.println("Done");

    //load plugin 8 variables
    tft.print("reading plugin 8 from project.txt...");
    loadPlugin8();
    tft.println("Done");


    //load FX 1 variables
    tft.print("reading FX 1 from project.txt...");
    loadFX1();
    tft.println("Done");

    //load FX 2 variables
    tft.print("reading FX 2 from project.txt...");
    loadFX2();
    tft.println("Done");



    // close the file:
    myFile.close();
    tft.println("Done");

    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening project.txt");
  }
}