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
  gridTouchX = map(p.x, 180, 3730, 0, 19);  // mapping the touch coordinates to a grid of 20
  gridTouchY = map(p.y, 260, 3760, 0, 14);  //mapping the touch coordinates to a grid of 15



  for (int tone = 0; tone < 12; tone++) {       //this is actually from the drumsequencer ; 
    for (int step = 0; step < 16; step++) {
      //here is the issue with the octaves, i´m sure. but i cant get a formula to calculate the Y pixel from the note value (should be somthing like notevalue - octaves*12)
      if (channel2loop[tone][step] == HIGH) {   //this is also from the drumsequencer, because we only look if a bool is high. In future i would like to look at a int array if a note is higher than 0
        int on_screen_x = step * STEP_FRAME_W + STEP_FRAME_W * 2 + 8;
        int on_screen_y = tone * STEP_FRAME_H + 24;
        tft.fillCircle( on_screen_x, on_screen_y, 5, trackColor[1]); // circle: x, y, radius, color; after selecting the channel we draw the active steps to the grid, also a relict from the drumsequencer
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
    if (gridTouchX => SEQ_GRID_LEFT && gridTouchX =< SEQ_GRID_RIGHT  && gridTouchY => SEQ_GRID_TOP && gridTouchY =< SEQ_GRID_BOTTOM)  {  //if we touch anything within the Sequencer grid do:
      ch2NoteValue = (gridTouchY - 1) + (ch2Octaves * 12);        //here i let the sketch calculate the note value
      int tone = ch2NoteValue % 12; // which note out of the 12 is it <--   isn´t this just showing us ANY Note whatever the octave settig is?
      int step_number = gridTouchX - 2;
      int on_screen_x = (step_number) * STEP_FRAME_W + STEP_FRAME_W * 2 + 8;
      int on_screen_y = (tone) * STEP_FRAME_H + 24;
      if (channel2loop[tone][step_number] == LOW) {    //we touch a grid, if its low
        channel2loop[tone][step_number] = HIGH;     //make it high
        channel2Clip[ch2Clip][step_number] = ch2NoteValue;  //here i assign the notevalue to the array
        tft.fillCircle( on_screen_x, on_screen_y, 5, trackColor[1]); //draw the active step circles
      }
      else if (channel2loop[tone][step_number] == HIGH) {   //we touch a grid, if its high
        channel2loop[tone][step_number] = LOW;                  //make it Low
        channel2Clip[ch2Clip][step_number] = 0;             // or set to note zero
        tft.fillCircle( on_screen_x, on_screen_y, 5, ILI9341_DARKGREY); //draw the active step circles
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
