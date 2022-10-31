void drumStepSequencer_Static() {  //static Display rendering
  clearWorkSpace();
  drawStepSequencerStatic(0);
  drawActiveDrumSteps();
}

void drumStepSequencer() {

  //drawActiveDrumSteps();
  for (byte i = 0; i < 7; i++) {
    if (buttons[i].changed()) {
      drawActiveSteps();
    }
  }

  /*
  if (!buttons[6].read()) {
  gridTouchX = map(Potentiometer2, 0, 127, 0, 19);
  gridTouchY = map(Potentiometer1, 0, 127, 0, 19);
  drawCursor();
  }*/
  TS_Point p = ts.getPoint();
  if (ts.touched() || !buttons[6].read()) {
    gridTouchX = map(p.x, TS_MINX, TS_MAXX, 0, 19);
    gridTouchY = map(p.y, TS_MINY, TS_MAXY, 0, 14);
    drawActiveDrumSteps();


    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        saveTrack1();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadTrack1();
      }
    }
    //draw active steps


    //midichannel selection
    //draw MIDIchannel number
    if (gridTouchX >= 18 && gridTouchY == 11) {
      int MIDIChannelAssign = Potentiometer1;
      track[0].MIDIchannel = map(Potentiometer1, 0, 127, 1, MAX_CHANNELS);
      drawMIDIchannel();
    }

    //assign drumnotes on the left
    if (gridTouchX == 1) {
      int noteselector = Potentiometer1;
      for (byte i = 0; i < 12; i++) {
        drumnote[gridTouchY - 1] = map(noteselector, 0, 127, 0, 48);
        tft.fillRect(STEP_FRAME_W, STEP_FRAME_H * i + STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H, trackColor[0]);
        tft.setCursor(18, STEP_FRAME_H * i + 18);
        tft.setFont(Arial_8);
        tft.setTextColor(ILI9341_BLACK);
        tft.setTextSize(1);
        tft.print(drumnote[i]);
      }
    }
    //assign drumsteps on the grid
    //for better behaviour here we wait for "interval, unless it would switch within micrseconds
    if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {
      drawCursor();

      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        int dot_on_X = (gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X;
        int dot_on_Y = (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y;
        ch1tone = (gridTouchY - 1);
        byte step_number = gridTouchX - 2;

        if (!channel1Clip[track[0].clip_selector][ch1tone][step_number]) {
          channel1Clip[track[0].clip_selector][ch1tone][step_number] = true;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, (trackColor[0] + (track[0].clip_selector)) * 20);  //draw the active steps circles
        } else if (channel1Clip[track[0].clip_selector][ch1tone][step_number]) {
          channel1Clip[track[0].clip_selector][ch1tone][step_number] = false;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, ILI9341_DARKGREY);  //draw the inactive steps circles
        }
      }
    }

    //clipselecting
    if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
      track[0].clip_selector = (gridTouchX / 2) - 1;
      clearStepsGrid();
      //draw active steps
      drawActiveDrumSteps();
    }


    //midicc_view
    for (byte midiccSelection = 0; midiccSelection <= 16; midiccSelection++) {
      if (track[0].MIDIchannel == midiccSelection) {
        if (gridTouchX >= 18 && gridTouchY == 12) {
          selectPage = MIDICC_PAGE_1;
          midiCC_view_Static(0, 0);
        }
      }
    }


    //plugin_view
    for (byte pluginSelection = 0; pluginSelection < MAX_PLUGINS; pluginSelection++) {
      if (track[0].MIDIchannel == pluginSelection + 17) {
        if (gridTouchX >= 18 && gridTouchY == 12) {
          selectPage = pluginSelection + 40;
          Plugin_View_Static(0);
        }
      }
    }
  }
}

void drawActiveDrumSteps() {
  for (byte tone = 0; tone < 12; tone++) {
    for (byte steps = 0; steps < STEP_QUANT; steps++) {
      if (channel1Clip[track[0].clip_selector][tone][steps]) {
        tft.fillCircle((steps * STEP_FRAME_W) + DOT_OFFSET_X, ((tone)*STEP_FRAME_H) + DOT_OFFSET_Y, DOT_RADIUS, trackColor[0] + (track[0].clip_selector) * 20);
      }
    }
  }
}

void saveTrack1() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing track1.txt...");
  SD.remove("track1.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening track1.txt...");
  myFile = SD.open("track1.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {



    //save track1
    tft.print("Writing track 1 to track1.txt...");
    for (byte sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (byte snote = 0; snote < 12; snote++) {
        for (byte sstep = 0; sstep < STEP_QUANT; sstep++) {
          myFile.print((char)channel1Clip[sclip][snote][sstep]);
        }
      }
    }


    tft.println("Done");
    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track1.txt");
  }
}
void loadTrack1() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("track1.txt");
  if (myFile) {
    tft.println("opening track1.txt:");

    // read from the file until there's nothing else in it:



    //load track 1
    tft.print("Reading songarrangment from track1.txt...");
    for (byte sclip = 0; sclip < NUM_CLIPS; sclip++) {
      for (byte snote = 0; snote < 12; snote++) {
        for (byte sstep = 0; sstep < STEP_QUANT; sstep++) {
          channel1Clip[sclip][snote][sstep] = myFile.read();
        }
      }
    }
    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track1.txt");
  }
}