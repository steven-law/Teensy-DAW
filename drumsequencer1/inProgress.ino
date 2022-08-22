int notesCh2[12] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int ch2Octaves = 3;
//also test for github
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
  drawMelodicSequencerStatic(1);
  tft.print(ch2Octaves);
}
void channel2Sequencer () {
  TS_Point p = ts.getPoint();
  touchX = map(p.x, 180, 3730, 0, 320);
  touchY = map(p.y, 260, 3760, 0, 240);
  gridTouchX = map(p.x, 180, 3730, 0, 19);
  gridTouchY = map(p.y, 260, 3760, 0, 14);



  for (int tone = 0; tone < 12; tone++) {
    for (int step = 0; step < 16; step++) {
      //here is the issue with the octaves, i´m sure. but i cant get a formula to calculate the Y pixel from the note value (should be somthing like notevalue - octaves*12)
      if (channel2loop[tone][step] == HIGH) {
        int on_screen_x = step * STEP_FRAME_W + STEP_FRAME_W * 2 + 8;
        int on_screen_y = tone * STEP_FRAME_H + 24;
        tft.fillCircle( on_screen_x, on_screen_y, 5, trackColor[1]); // circle: x, y, radius, color
      }
    }
  }



  if (ts.touched()) {
    if (gridTouchX > OCTAVE_CHANGE_LEFTMOST && gridTouchX < OCTAVE_CHANGE_RIGHTMOST  && gridTouchY > OCTAVE_CHANGE_UP_TOPMOST && gridTouchY < OCTAVE_CHANGE_UP_BOTTOMMOST) {
      ch2Octaves--;
      clearStepsGrid();
    }
    if (gridTouchX > OCTAVE_CHANGE_LEFTMOST && gridTouchX < OCTAVE_CHANGE_RIGHTMOST  && gridTouchY > OCTAVE_CHANGE_DOWN_TOPMOST && gridTouchY < OCTAVE_CHANGE_DOWN_BOTTOMMOST) {
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
      int tone = ch2NoteValue % 12; // which note out of the 12 is it
      int step_number = gridTouchX - 2;
      int on_screen_x = (step_number) * STEP_FRAME_W + STEP_FRAME_W * 2 + 8;
      int on_screen_y = (tone) * STEP_FRAME_H + 24;
      if (channel2loop[tone][step_number] == LOW) {
        channel2loop[tone][step_number] = HIGH;
        channel2Clip[ch2Clip][step_number] = ch2NoteValue;  //here i assign them to the array
        tft.fillCircle( on_screen_x, on_screen_y, 5, trackColor[1]); //draw the active step circles
      }
      else if (channel2loop[tone][step_number] == HIGH) {
        channel2loop[tone][step_number] = LOW;
        channel2Clip[ch2Clip][step_number] = 0;
        tft.fillCircle( on_screen_x, on_screen_y, 5, ILI9341_DARKGREY); //draw the active step circles
      }
    }
    if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {
      ch2Clip = (gridTouchX / 2) - 1;
      clearStepsGrid();
    }
  }
  delay(100);
}
