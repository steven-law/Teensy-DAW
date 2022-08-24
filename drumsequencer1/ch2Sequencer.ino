int notesCh2[12] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int ch2Octaves = 3;
//also test for github
byte ch2StepCount;
int ch2Clip = 0;

int channel2Clip[8][16] {
  {0,   1,  2,  3,    4,  0, 15, 16,   36, 18,  0,  0,   56,  0,  0,  0},
  {36,  0,  0,  0,   38,  0,  0,  0,   36,  0,  0,  0,   41,  0,  0,  0},
  {36, 25, 41, 47,   21, 26, 45, 33,   36, 34, 41, 22,   43,  0, 45,  0},
  {36,  0,  0,  0,   38,  0,  0,  0,   36,  0,  0,  0,   41,  0,  0,  0},

  { 1,  0,  0,  0,   38,  0,  0,  0,   36,  0,  0,  0,   41,  0,  0,  0},
  {36,  0,  0,  0,   37,  0,  0,  0,   36,  0,  0,  0,   42,  0,  0,  0},
  {36,  0,  0,  0,   39,  0,  0,  0,   36,  0,  0,  0,   53,  0,  0,  0},
  {36,  0,  0,  0,   60,  0,  0,  0,   36,  0,  0,  0,   43,  0,  0,  0}
};

void gridchannel2Sequencer () {   //static Display rendering
  clearWorkSpace();
  drawMelodicSequencerStatic(ch2COLOR);
  tft.print(ch2Octaves);
}
void channel2Sequencer () {
  TS_Point p = ts.getPoint();
  touchX = map(p.x, 180, 3730, 0, 320);
  touchY = map(p.y, 260, 3760, 0, 240);
  gridTouchX = map(p.x, 180, 3730, 0, 19);  // mapping the touch coordinates to a grid of 20
  gridTouchY = map(p.y, 260, 3760, 0, 14);  //mapping the touch coordinates to a grid of 15

  switch (ch2Octaves) {
    case 0:
      for (int step = 0; step < 16; step++) {
        if (channel2Clip[ch2Clip][step] > OCTAVE0 && channel2Clip[ch2Clip][step] < OCTAVE1) {   //this is also from the drumsequencer, because we only look if a bool is high. In future i would like to look at a int array if a note is higher than 0
          int on_screen_x = step * STEP_FRAME_W + STEP_FRAME_W * 2 + 8;
          int on_screen_y = channel2Clip[ch2Clip][step] * STEP_FRAME_H + DOT_OFFSET_Y;
          tft.fillCircle( on_screen_x, on_screen_y, DOT_RADIUS, trackColor[ch2COLOR]); // circle: x, y, radius, color; after selecting the channel we draw the active steps to the grid, also a relict from the drumsequencer
        }
      }
      break;
    case 1:
      for (int step = 0; step < 16; step++) {
        //here is the issue with the octaves, i´m sure. but i cant get a formula to calculate the Y pixel from the note value (should be somthing like notevalue - octaves*12)
        if (channel2Clip[ch2Clip][step] >= OCTAVE1 && channel2Clip[ch2Clip][step] < OCTAVE2) {   //this is also from the drumsequencer, because we only look if a bool is high. In future i would like to look at a int array if a note is higher than 0
          int on_screen_x = step * STEP_FRAME_W + STEP_FRAME_W * 2 + 8;
          int on_screen_y = (channel2Clip[ch2Clip][step] - 12) * STEP_FRAME_H + DOT_OFFSET_Y;
          tft.fillCircle( on_screen_x, on_screen_y, DOT_RADIUS, trackColor[ch2COLOR]); // circle: x, y, radius, color; after selecting the channel we draw the active steps to the grid, also a relict from the drumsequencer
        }
      }
      break;
    case 2:
      for (int step = 0; step < 16; step++) {
        if (channel2Clip[ch2Clip][step] >= OCTAVE2 && channel2Clip[ch2Clip][step] < OCTAVE3) {   //look at the channel2Clip int array if a note is higher than 0
          int on_screen_x = step * STEP_FRAME_W + STEP_FRAME_W * 2 + 8;
          int on_screen_y = (channel2Clip[ch2Clip][step] - OCTAVE2) * STEP_FRAME_H + DOT_OFFSET_Y;
          tft.fillCircle( on_screen_x, on_screen_y, DOT_RADIUS, trackColor[ch2COLOR]); // circle: x, y, radius, color; after selecting the channel we draw the active steps to the grid
        }
      }
      break;
    case 3:
      for (int step = 0; step < 16; step++) {
        if (channel2Clip[ch2Clip][step] >= OCTAVE3 && channel2Clip[ch2Clip][step] < OCTAVE4) {
          int on_screen_x = step * STEP_FRAME_W + STEP_FRAME_W * 2 + 8;
          int on_screen_y = (channel2Clip[ch2Clip][step] - OCTAVE3) * STEP_FRAME_H + DOT_OFFSET_Y;
          tft.fillCircle( on_screen_x, on_screen_y, DOT_RADIUS, trackColor[ch2COLOR]); // circle: x, y, radius, color; after selecting the channel we draw the active steps to the grid
        }
      }
      break;
    case 4:
      for (int step = 0; step < 16; step++) {
        if (channel2Clip[ch2Clip][step] >= OCTAVE4 && channel2Clip[ch2Clip][step] < OCTAVE5) {
          int on_screen_x = step * STEP_FRAME_W + STEP_FRAME_W * 2 + 8;
          int on_screen_y = (channel2Clip[ch2Clip][step] - OCTAVE4) * STEP_FRAME_H + DOT_OFFSET_Y;
          tft.fillCircle( on_screen_x, on_screen_y, DOT_RADIUS, trackColor[ch2COLOR]); // circle: x, y, radius, color; after selecting the channel we draw the active steps to the grid
        }
      }
      break;
    case 5:
      for (int step = 0; step < 16; step++) {
        if (channel2Clip[ch2Clip][step] >= OCTAVE5 && channel2Clip[ch2Clip][step] < OCTAVE6) {
          int on_screen_x = step * STEP_FRAME_W + STEP_FRAME_W * 2 + 8;
          int on_screen_y = (channel2Clip[ch2Clip][step] - OCTAVE5) * STEP_FRAME_H + DOT_OFFSET_Y;
          tft.fillCircle( on_screen_x, on_screen_y, DOT_RADIUS, trackColor[ch2COLOR]); // circle: x, y, radius, color; after selecting the channel we draw the active steps to the grid
        }
      }
  }



  //octave selection
  if (ts.touched()) {
    if (gridTouchX > OCTAVE_CHANGE_LEFTMOST && gridTouchX < OCTAVE_CHANGE_RIGHTMOST  && gridTouchY > OCTAVE_CHANGE_UP_TOPMOST && gridTouchY < OCTAVE_CHANGE_UP_BOTTOMMOST) {
      ch2Octaves--;
      clearStepsGrid();
    }
    if (gridTouchX > OCTAVE_CHANGE_LEFTMOST && gridTouchX < OCTAVE_CHANGE_RIGHTMOST  && gridTouchY > OCTAVE_CHANGE_DOWN_TOPMOST && gridTouchY < OCTAVE_CHANGE_DOWN_BOTTOMMOST) {
      ch2Octaves++;
      clearStepsGrid();
    }
    //draw the octave number
    tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 4, STEP_FRAME_W * 2, STEP_FRAME_H * 4, ILI9341_DARKGREY);
    tft.setCursor(STEP_FRAME_W * 18 + 12, STEP_FRAME_H * 5 + 8);
    tft.setFont(Arial_16);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(1);
    tft.print(ch2Octaves);

    //gridstep handling, one line under we let the code calculate the notevalue (0-127) from the selected step and selected octave
    if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT  && gridTouchY >= SEQ_GRID_TOP && gridTouchY <= SEQ_GRID_BOTTOM)  {  //if we touch anything within the Sequencer grid do:
      ch2NoteValue = (gridTouchY - 1) + (ch2Octaves * 12);        //here i let the sketch calculate the note value
      int tone = ch2NoteValue % 12; // which note out of the 12 is it <--   isn´t this just showing us ANY Note whatever the octave settig is?
      int step_number = gridTouchX - 2;
      int on_screen_x = (step_number) * STEP_FRAME_W + STEP_FRAME_W * 2 + 8;
      int on_screen_y = (tone) * STEP_FRAME_H + 24;
      //int on_screen_y = (channel2Clip[ch2Clip][step_number] - OCTAVE5) * STEP_FRAME_H + 24;
      if (channel2Clip[ch2Clip][step_number] == 0) {    //we touch a grid, if its low
        channel2Clip[ch2Clip][step_number] = ch2NoteValue;  //here i assign the notevalue to the array
        tft.fillCircle( on_screen_x, on_screen_y, DOT_RADIUS, trackColor[ch2COLOR]); //draw the active step circles
      }
      else if (channel2Clip[ch2Clip][step_number] > 0) {   //we touch a grid, if its high
        channel2Clip[ch2Clip][step_number] = 0;             // or set to note zero
        clearStepsGridY();                                 //and clear all dots in this row
      }
    }
    //clip selection
    if (gridTouchX > 2 && gridTouchX < 18 && gridTouchY == 13) {     //if we touch "line 13" we can select clips
      ch2Clip = (gridTouchX / 2) - 1;
      clearStepsGrid();
    }
  }
  delay(100);
}
