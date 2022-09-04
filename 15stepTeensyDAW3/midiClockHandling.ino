//int countClock = 0;
//int sixteenthClock = 0;
//int fourthClock = 0;
//int phraseClock = 0;
////byte songPositionY = 232;
////byte stepPositionY = 236;
//byte thickness = 3;
//int bpm = 0;
//byte setNoteOn;
//byte noteOnClock;
//byte zaehler = 0;
//int zeitAlt = 0;
//
////byte velocity = 96;
////24ppqn  6ppqn=sixteenthClock  24ppqn=fourthClock  96ppqn=barClock 384ppqn=phraseClock
//void myClock() {
//  noInterrupts();
//  countClock++;
//  noteOnClock++;
//  if (countClock % 24 == 0) {
//    bpm = ((60000 / (millis() - zeitAlt)));
//    Serial.print(bpm);
//    Serial.println(" BPM");
//    zeitAlt = millis();
//
//    tft.fillRect(STEP_FRAME_W * POSITION_BPM_BUTTON, 3, STEP_FRAME_W * 2 - 3, 10, ILI9341_DARKGREY);
//    tft.setTextColor(ILI9341_WHITE);
//    tft.setFont(Arial_9);
//    tft.setCursor(STEP_FRAME_W * POSITION_BPM_BUTTON + 2, 3);
//    tft.print(bpm);
//
//  }
//
//  if (countClock % 6 == 0) {
//    sixteenthClock++;
//    noteOnClock = 0;
//    for (byte i = 0; i < 127; i++) {
//      if (channel1Clip[ch1Clip][i][sixteenthClock] == HIGH) {
//        usbMIDI.sendNoteOn(i, velocity, 10);
//      }
//
//      if (noteOnClock == 5) {
//        usbMIDI.sendNoteOff(i, velocity, 10);
//      }
//    }
//
//    if (clip[7][ch8songModePlayedClip][sixteenthClock] > VALUE_NOTEOFF) {
//      usbMIDI.sendNoteOn(clip[7][ch8songModePlayedClip][sixteenthClock], velocity, channel8channel);
//    }
//    if (clip[7][ch8songModePlayedClip][sixteenthClock] == VALUE_NOTEOFF) {
//      usbMIDI.sendNoteOff(clip[7][ch8songModePlayedClip][sixteenthClock], velocityOff, channel8channel);
//    }
//
//  }
//
//
//  if (countClock % 24 == 0) {
//    fourthClock++;
//  }
//  if (countClock % 96 == 0) {
//    barClock++;
//    fourthClock = 0;
//
//    pixelbarClock++;
//    tft.fillRect(STEP_FRAME_W * POSITION_BAR_BUTTON - 1, 2, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 3, ILI9341_DARKGREY);
//    tft.setTextColor(ILI9341_WHITE);
//    tft.setFont(Arial_9);
//    tft.setCursor(STEP_FRAME_W * POSITION_BAR_BUTTON + 2, 3);
//    tft.print(barClock + 1);
//    for (int songPointerThickness = 0; songPointerThickness <= thickness; songPointerThickness++) {
//      tft.drawPixel(barClock + STEP_FRAME_W * 2, (songPositionY + songPointerThickness) , ILI9341_GREEN);
//      tft.drawFastHLine(pixelbarClock * PHRASE_SEGMENT_LENGTH + STEP_FRAME_W * 2, gridPositionY + songPointerThickness, PHRASE_SEGMENT_LENGTH, ILI9341_GREEN);
//      tft.drawFastHLine((pixelbarClock - 1) * PHRASE_SEGMENT_LENGTH + STEP_FRAME_W * 2, gridPositionY + songPointerThickness, PHRASE_SEGMENT_LENGTH, ILI9341_DARKGREY);
//    }
//  }
//  if (countClock % 384 == 0) {
//    phraseClock++;
//    countClock = 0;
//  }
//}
//void myContinue() {
//  zaehler = 0;
//  zeitAlt = millis();
//  countClock = 0;
//  sixteenthClock = 0;
//  barClock = 1;
//  fourthClock = 0;
//  phraseClock = 0;
//  tft.fillRect(STEP_FRAME_W * 2, songPositionY - 5, STEP_FRAME_W * 16, 20, ILI9341_DARKGREY);
//}
//
//void myStop() {
//  countClock = 0;
//  sixteenthClock = 0;
//  barClock = 0;
//  fourthClock = 0;
//  phraseClock = 0;
//  tft.fillRect(STEP_FRAME_W * 2, songPositionY - 5, STEP_FRAME_W * 16, 20, ILI9341_DARKGREY);
//}
////int countClock = 0;
////int sixteenthClock = 0;
////int fourthClock = 0;
////int phraseClock = 0;
//////byte songPositionY = 232;
//////byte stepPositionY = 236;
////byte thickness = 3;
////int bpm = 0;
////byte setNoteOn;
////byte noteOnClock;
////byte zaehler = 0;
////int zeitAlt = 0;
////
//////24ppqn  6ppqn=sixteenthClock  24ppqn=fourthClock  96ppqn=barClock 384ppqn=phraseClock
////void myClock() {
////  noInterrupts();
////  countClock++;
////  if (countClock % 24 == 0) {
////    bpm = ((60000 / (millis() - zeitAlt)));
////    Serial.print(bpm);
////    Serial.println(" BPM");
////    zeitAlt = millis();
////
////    tft.fillRect(STEP_FRAME_W * POSITION_BPM_BUTTON, 3, STEP_FRAME_W * 2 - 3, 10, ILI9341_DARKGREY);
////    tft.setTextColor(ILI9341_WHITE);
////    tft.setFont(Arial_9);
////    tft.setCursor(STEP_FRAME_W * POSITION_BPM_BUTTON + 2, 3);
////    tft.print(bpm);
////
////  }
////
////  if (countClock % 6 == 0) {
////    sixteenthClock++;
////    for (int i = 0; i < 127; i++) {
////      if (channel1Clip[ch1songModePlayedClip][i][sixteenthClock] == HIGH) {
////        usbMIDI.sendNoteOn(i, velocity, channel1channel);
////      }
////      if (channel1Clip[ch1songModePlayedClip][i][sixteenthClock + 1] == LOW) {
////        usbMIDI.sendNoteOff(i, velocityOff, channel1channel);
////      }
////    }
////    if (clip[7][ch8songModePlayedClip][sixteenthClock] > VALUE_NOTEOFF) {
////      usbMIDI.sendNoteOn(clip[7][ch8songModePlayedClip][sixteenthClock], velocity, channel8channel);
////    }
////    if (clip[7][ch8songModePlayedClip][sixteenthClock] == VALUE_NOTEOFF) {
////      usbMIDI.sendNoteOff(clip[7][ch8songModePlayedClip][sixteenthClock], velocityOff, channel8channel);
////    }
////
////
////
////    for (int songPointerThickness = 0; songPointerThickness <= thickness; songPointerThickness++) {
////      for (int stepwidth = 1; stepwidth <= 16; stepwidth++) {
////        tft.drawFastHLine(sixteenthClock * stepwidth + STEP_FRAME_W * 2, stepPositionY + songPointerThickness, STEP_FRAME_W, ILI9341_GREEN);
////        tft.drawFastHLine((sixteenthClock - 1) * stepwidth + STEP_FRAME_W * 2, stepPositionY + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);
////      }
////    }
////    for (int songPointerThickness = 0; songPointerThickness <= thickness; songPointerThickness++) {
////      if (sixteenthClock == 0) {
////        tft.drawFastHLine(STEP_FRAME_W * 17, stepPositionY + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);
////
////      }
////    }
////
////  }
////  if (countClock % 96 == 0) {
////    barClock++;
////    pixelbarClock++;
////    tft.fillRect(STEP_FRAME_W * POSITION_BAR_BUTTON - 1, 2, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 3, ILI9341_DARKGREY);
////    tft.setTextColor(ILI9341_WHITE);
////    tft.setFont(Arial_9);
////    tft.setCursor(STEP_FRAME_W * POSITION_BAR_BUTTON + 2, 3);
////    tft.print(barClock + 1);
////    for (int songPointerThickness = 0; songPointerThickness <= thickness; songPointerThickness++) {
////      tft.drawPixel(barClock + STEP_FRAME_W * 2, (songPositionY + songPointerThickness) , ILI9341_GREEN);
////      tft.drawFastHLine(pixelbarClock * PHRASE_SEGMENT_LENGTH + STEP_FRAME_W * 2, gridPositionY + songPointerThickness, PHRASE_SEGMENT_LENGTH, ILI9341_GREEN);
////      tft.drawFastHLine((pixelbarClock - 1) * PHRASE_SEGMENT_LENGTH + STEP_FRAME_W * 2, gridPositionY + songPointerThickness, PHRASE_SEGMENT_LENGTH, ILI9341_DARKGREY);
////    }
////
////    if (barClock % 16 == 0) {
////      phrase++;
////      if (arrangment1[0][phrase] == -1) {
////        ch1songModePlayedClip = 9;
////      }
////      if (arrangment1[7][phrase] == -1) {
////        ch8songModePlayedClip = 9;
////      }
////      ch8songModePlayedClip = arrangment1[7][phrase];
////    }
////
////    if (pixelbarClock == 255 / PHRASE_SEGMENT_LENGTH) {
////      pixelbarClock = 0;
////      tft.fillRect(STEP_FRAME_W * 2, gridPositionY, STEP_FRAME_W * 20, 4, ILI9341_DARKGREY);
////    }
////    if (barClock == 255) {
////      barClock = 0;
////      phrase = 0;
////      tft.fillRect(STEP_FRAME_W * 2, songPositionY, STEP_FRAME_W * 20, 4, ILI9341_DARKGREY);
////    }
////  }
////}
////void myContinue() {
////  zaehler = 0;
////  zeitAlt = millis();
////  countClock = 0;
////  sixteenthClock = 0;
////  barClock = 1;
////  fourthClock = 0;
////  phraseClock = 0;
////  tft.fillRect(STEP_FRAME_W * 2, songPositionY - 5, STEP_FRAME_W * 16, 20, ILI9341_DARKGREY);
////}
////
////void myStop() {
////  countClock = 0;
////  sixteenthClock = 0;
////  barClock = 1;
////  fourthClock = 0;
////  phraseClock = 0;
////  tft.fillRect(STEP_FRAME_W * 2, songPositionY - 5, STEP_FRAME_W * 16, 20, ILI9341_DARKGREY);
////}
