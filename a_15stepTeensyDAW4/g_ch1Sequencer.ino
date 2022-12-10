void drumStepSequencer_Static() {  //static Display rendering
  clearWorkSpace();
  drawStepSequencerStatic(0);
  drawActiveDrumSteps();
  drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
}

void drumStepSequencer() {

  // if (msecs % 20 == 0) {
  //midichannel
  if (abs(map(Potentiometer[2], 0, 127, 1, MAX_CHANNELS) - track[0].MIDIchannel) < 2) {
    if (track[0].MIDIchannel != map(Potentiometer[2], 0, 127, 1, MAX_CHANNELS)) {
      track[0].MIDIchannel = map(Potentiometer[2], 0, 127, 1, MAX_CHANNELS);
      drawMIDIchannel();
    }
  }
  //clip
  if (abs(map(Potentiometer[3], 0, 127, 0, 7) - track[desired_instrument].clip_selector) < 2) {
    if (track[desired_instrument].clip_selector != map(Potentiometer[3], 0, 127, 0, 7)) {
      track[desired_instrument].clip_selector = map(Potentiometer[3], 0, 127, 0, 7);
      clearStepsGrid();
      drawActiveDrumSteps();
      drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
    }
  }
  // }



  //assign drumsteps on the grid
  //for better behaviour here we wait for "interval, unless it would switch within micrseconds
  //tho, this leads to a drop of the sequencertempo

  TS_Point p = ts.getPoint();
  if (ts.touched() || enter_button) {
    gridTouchX = map(p.x, TS_MINX, TS_MAXX, 0, 19);
    gridTouchY = map(p.y, TS_MINY, TS_MAXY, 0, 14);
    


    unsigned long currentMillis = millis();  //worse input haptic, better bpm drop when longpress (-2bpm)
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;


      if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM) {

        int dot_on_X = (gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X;
        int dot_on_Y = (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y;
        ch1tone = (gridTouchY - 1);
        byte step_number = gridTouchX - 2;

        if (!channel1Clip[track[0].clip_selector][ch1tone][step_number]) {

          channel1Clip[track[0].clip_selector][ch1tone][step_number] = true;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, (trackColor[0] + (track[0].clip_selector) * 20));  //draw the active steps circles

        } else if (channel1Clip[track[0].clip_selector][ch1tone][step_number]) {
          channel1Clip[track[0].clip_selector][ch1tone][step_number] = false;
          tft.fillCircle(dot_on_X, dot_on_Y, DOT_RADIUS, ILI9341_DARKGREY);  //draw the inactive steps circles
        }
      }
    }

    //load and save
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
    //assign drumnotes on the left
    if (gridTouchX == 1) {
      int noteselector = Potentiometer[3];
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
    //clipselecting
    if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
      track[0].clip_selector = (gridTouchX / 2) - 1;
      clearStepsGrid();
      //draw active steps
      drawActiveDrumSteps();
      drawNrInRect(18, 1, track[desired_instrument].clip_selector, trackColor[desired_instrument] + (track[desired_instrument].clip_selector * 20));
    }
  }
}


void drawActiveDrumSteps() {
  for (byte tone = 0; tone < 12; tone++) {
    for (byte steps = 0; steps < STEP_QUANT; steps++) {
      if (channel1Clip[track[0].clip_selector][tone][steps]) {
        tft.fillCircle((steps * STEP_FRAME_W) + DOT_OFFSET_X, ((tone)*STEP_FRAME_H) + DOT_OFFSET_Y, DOT_RADIUS, trackColor[0] + ((track[0].clip_selector) * 20));
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
    myFile.print((char)track[0].MIDIchannel);

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
    track[0].MIDIchannel = myFile.read();
    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening track1.txt");
  }
}