int countClock = 0;
int sixteenthClock = 0;
int fourthClock = 0;
int barClock = 0;
int phraseClock = 0;
byte songPositionY = 232;
byte stepPositionY = 236;
byte thickness = 3;

//24ppqn  6ppqn=sixteenthClock  24ppqn=fourthClock  96ppqn=barClock 384ppqn=phraseClock
void myClock() {
  countClock++;

  if (countClock % 6 == 0) {
    sixteenthClock++;

    for (int songPointerThickness = 0; songPointerThickness <= thickness; songPointerThickness++) {
      for (int stepwidth = 0; stepwidth < 16; stepwidth++) {
        tft.drawFastHLine(sixteenthClock * stepwidth + STEP_FRAME_W * 2, stepPositionY + songPointerThickness, STEP_FRAME_W, ILI9341_GREEN);
        tft.drawFastHLine((sixteenthClock - 1) * stepwidth + STEP_FRAME_W * 2, stepPositionY + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);
      }
    }
    for (int songPointerThickness = 0; songPointerThickness <= thickness; songPointerThickness++) {
      if (sixteenthClock == 16) {
        tft.drawFastHLine(STEP_FRAME_W * 13, stepPositionY + songPointerThickness, STEP_FRAME_W * 9, ILI9341_DARKGREY);
        sixteenthClock = 0;
      }
    }
  }


  if (countClock % 24 == 0) {
    fourthClock++;
  }
  if (countClock % 96 == 0) {
    barClock++;
    fourthClock = 0;
    for (int songPointerThickness = 0; songPointerThickness <= thickness; songPointerThickness++) {
      tft.drawPixel(barClock + STEP_FRAME_W * 2, songPositionY + songPointerThickness , ILI9341_GREEN);
    }

  }
  if (countClock % 384 == 0) {
    phraseClock++;
    countClock = 0;
  }
}
void myContinue() {
  countClock = 0;
  sixteenthClock = 0;
  barClock = 0;
  fourthClock = 0;
  phraseClock = 0;
  tft.fillRect(STEP_FRAME_W * 2, songPositionY - 5, STEP_FRAME_W * 16, 20, ILI9341_DARKGREY);
}

void myStop() {
  countClock = 0;
  sixteenthClock = 0;
  barClock = 0;
  fourthClock = 0;
  phraseClock = 0;
  tft.fillRect(STEP_FRAME_W * 2, songPositionY - 5, STEP_FRAME_W * 16, 20, ILI9341_DARKGREY);
}
