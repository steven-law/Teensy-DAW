int notesCh2[12] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int ch2Octaves = 3;

byte ch2StepCount;
int ch2Clip = 0;

bool channel2loop[12][16] {
  {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
int channel2Clip[8][16] {
  {36, 0, 0, 0, 38, 0, 0, 0, 36, 0, 0, 0, 41, 0, 0, 0},
  {36, 0, 41, 0, 43, 0, 45, 0, 36, 0, 41, 0, 43, 0, 45, 0},
};

void gridchannel2Sequencer () {   //static Display rendering
  clearWorkSpace();
  drawOctavesbuttons();
  tft.print(ch2Octaves);
  drawSequencerGrid();
  drawColors(1);
  drawNoteNames();
}
void channel2Sequencer () {
  TS_Point p = ts.getPoint();
  touchX = map(p.x, 180, 3730, 0, 320);
  touchY = map(p.y, 260, 3760, 0, 240);
  gridTouchX = map(p.x, 180, 3730, 0, 19);
  gridTouchY = map(p.y, 260, 3760, 0, 14);



  //  for (int T = 0; T < 12; T++) {
  for (int S = 0; S < 16; S++) {
    //here is the issue with the octaves, i´m sure. but i cant get a formula to calculate the Y pixel from the note value (should be somthing like notevalue - octaves*12)
    if (channel2Clip[ch2Clip][S] > 0) {
      tft.fillCircle(S * STEP_FRAME_W + DOT_OFFSET_X, (ch2NoteValue - (ch2Octaves * 12)) * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, trackColor[1]); // circle: x, y, radius, color
    }
    //   }
  }




  if (ts.touched()) {
    if (gridTouchX > 17 && gridTouchX < 20  && gridTouchY > 1 && gridTouchY < 4) {
      ch2Octaves--;
      clearStepsGrid();
    }
    if (gridTouchX > 17 && gridTouchX < 20  && gridTouchY > 7 && gridTouchY < 10) {
      ch2Octaves++;
      clearStepsGrid();
    }
    tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 4, STEP_FRAME_W * 2, STEP_FRAME_H * 4, ILI9341_DARKGREY);
    tft.setCursor(STEP_FRAME_W * 18 + 12, STEP_FRAME_H * 5 + 8);
    tft.setFont(Arial_16);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(1);
    tft.print(ch2Octaves);

    if (gridTouchX > 1 && gridTouchX < 18  && gridTouchY > 0 && gridTouchY < 13) {
      ch2NoteValue = (gridTouchY - 1) + (ch2Octaves * 12);        //here i let the sketch calculate the note value
      if (channel2loop[gridTouchY - 1][gridTouchX - 2] == LOW) {
        channel2loop[gridTouchY - 1][gridTouchX - 2] = HIGH;
        channel2Clip[ch2Clip][gridTouchX - 2] = ch2NoteValue;  //here i assign them to the array
        clearStepsGridY();
        tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, trackColor[1]); //draw the active step circles
      }
      else if (channel2loop[gridTouchY - 1][gridTouchX - 2] == HIGH) {
        channel2loop[gridTouchY - 1][gridTouchX - 2] = LOW;
        channel2Clip[ch2Clip][gridTouchX - 2] = 0;
        tft.fillCircle((gridTouchX - 2) * STEP_FRAME_W + DOT_OFFSET_X, (gridTouchY - 1) * STEP_FRAME_H + DOT_OFFSET_Y, DOT_RADIUS, ILI9341_DARKGREY); //draw the active step circles
      }
    }
    if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
      ch2Clip = (gridTouchX / 2) - 1;
      clearStepsGrid();
    }
  }
  delay(100);
}
