//this file contains several display functions, they will be moved somewhere else probably

//general stuff
void drawCursor() {
  static byte last_button_X = 0;
  static byte last_button_Y = 0;
  for (int pixel = 0; pixel < 16; pixel++) {
    tft.drawPixel(pixel + (STEP_FRAME_W * last_button_X), (STEP_FRAME_H * last_button_Y) + 1, tftRAM[0][pixel]);
    tft.drawPixel(pixel + (STEP_FRAME_W * last_button_X), (STEP_FRAME_H * last_button_Y) + 15, tftRAM[1][pixel]);
    tft.drawPixel((STEP_FRAME_W * last_button_X) + 1, pixel + (STEP_FRAME_H * last_button_Y), tftRAM[2][pixel]);
    tft.drawPixel((STEP_FRAME_W * last_button_X) + 15, pixel + (STEP_FRAME_H * last_button_Y), tftRAM[3][pixel]);
  }


  for (int pixel = 0; pixel < 16; pixel++) {
    tftRAM[0][pixel] = tft.readPixel(pixel + (STEP_FRAME_W * gridTouchX), (STEP_FRAME_H * gridTouchY) + 1);
    tftRAM[1][pixel] = tft.readPixel(pixel + (STEP_FRAME_W * gridTouchX), (STEP_FRAME_H * gridTouchY) + 15);
    tftRAM[2][pixel] = tft.readPixel((STEP_FRAME_W * gridTouchX) + 1, pixel + (STEP_FRAME_H * gridTouchY));
    tftRAM[3][pixel] = tft.readPixel((STEP_FRAME_W * gridTouchX) + 15, pixel + (STEP_FRAME_H * gridTouchY));
  }

  tft.drawRect((STEP_FRAME_W * gridTouchX) + 1, (STEP_FRAME_H * gridTouchY) + 1, STEP_FRAME_W - 1, STEP_FRAME_H - 1, ILI9341_WHITE);
  last_button_X = gridTouchX;
  last_button_Y = gridTouchY;
}
void drawCursorPixel() {
  static int last_button_X = 0;
  static int last_button_Y = 0;
  for (int pixel = 0; pixel < 16; pixel++) {
    tft.drawPixel(pixel + (last_button_X), (STEP_FRAME_H * last_button_Y) + 1, tftRAM[0][pixel]);
    tft.drawPixel(pixel + (last_button_X), (STEP_FRAME_H * last_button_Y) + 15, tftRAM[1][pixel]);
    tft.drawPixel((last_button_X) + 1, pixel + (STEP_FRAME_H * last_button_Y), tftRAM[2][pixel]);
    tft.drawPixel((last_button_X) + 15, pixel + (STEP_FRAME_H * last_button_Y), tftRAM[3][pixel]);
  }


  for (int pixel = 0; pixel < 16; pixel++) {
    tftRAM[0][pixel] = tft.readPixel(pixel + (STEP_FRAME_W * pixelTouchX), (STEP_FRAME_H * gridTouchY) + 1);
    tftRAM[1][pixel] = tft.readPixel(pixel + (STEP_FRAME_W * pixelTouchX), (STEP_FRAME_H * gridTouchY) + 15);
    tftRAM[2][pixel] = tft.readPixel((pixelTouchX) + 1, pixel + (STEP_FRAME_H * gridTouchY));
    tftRAM[3][pixel] = tft.readPixel((pixelTouchX) + 15, pixel + (STEP_FRAME_H * gridTouchY));
  }

  tft.drawRect((pixelTouchX) + 1, (STEP_FRAME_H * gridTouchY) + 1, STEP_FRAME_W - 1, STEP_FRAME_H - 1, ILI9341_WHITE);
  last_button_X = pixelTouchX;
  last_button_Y = gridTouchY;
}
void startUpScreen() {  //static Display rendering
  tft.fillScreen(ILI9341_DARKGREY);

  tft.setFont(Arial_9);

  //songmode button
  tft.setTextColor(ILI9341_BLACK);
  tft.fillRect(1, 1, 15, 16, ILI9341_MAGENTA);  //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(4, 3);
  tft.print("S");

  //other tracks buttons
  for (int otherTracks = 0; otherTracks < 8; otherTracks++) {
    allTracks[otherTracks]->drawLeftNavigator(otherTracks);
  }

  //Mixer button
  tft.fillRect(1, STEP_FRAME_H * 13, 15, TRACK_FRAME_H, ILI9341_LIGHTGREY);  //Xmin, Ymin, Xlength, Ylength, color
  tft.setCursor(3, STEP_FRAME_H * 13 + 6);
  tft.print("M");

  //scale Select
  // tft.drawRect(STEP_FRAME_W * POSITION_SCALE_BUTTON, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);

  //arrangment Select
  // tft.drawRect(STEP_FRAME_W * POSITION_ARR_BUTTON, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);

  // record button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_RECORD_BUTTON, 0, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.fillCircle(STEP_FRAME_W * POSITION_RECORD_BUTTON + 7, 7, DOT_RADIUS + 1, ILI9341_LIGHTGREY);

  //Play button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_PLAY_BUTTON, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);                                                                      //PLAY RECT FRAME
  tft.fillTriangle(STEP_FRAME_W * POSITION_PLAY_BUTTON + 12, 3, STEP_FRAME_W * POSITION_PLAY_BUTTON + 12, 13, STEP_FRAME_W * POSITION_PLAY_BUTTON + 22, 8, ILI9341_GREEN);  // x1, y1, x2, y2, x3, y3

  //stop button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_STOP_BUTTON, 0, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.fillRect(STEP_FRAME_W * POSITION_STOP_BUTTON + 3, 3, 10, 10, ILI9341_LIGHTGREY);

  //barcounter & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_BAR_BUTTON, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);

  //tempo button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_BPM_BUTTON, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);

  //save button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_SAVE_BUTTON, 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);
  tft.fillRect(STEP_FRAME_W * POSITION_SAVE_BUTTON + 1, 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_ORANGE);
  tft.setTextColor(ILI9341_BLACK);
  tft.setFont(Arial_9);
  tft.setCursor(STEP_FRAME_W * POSITION_SAVE_BUTTON + 2, 3);
  tft.print("SAV");

  //load button & Rectangle
  tft.drawRect(STEP_FRAME_W * POSITION_LOAD_BUTTON, 0, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
  tft.fillRect(STEP_FRAME_W * POSITION_LOAD_BUTTON + 1, 1, STEP_FRAME_W - 2, STEP_FRAME_H - 2, ILI9341_GREENYELLOW);
  tft.setTextColor(ILI9341_BLACK);
  tft.setFont(Arial_9);
  tft.setCursor(STEP_FRAME_W * POSITION_LOAD_BUTTON + 4, 3);
  tft.print("L");
}
void clearWorkSpace() {                                                                                  //clear the whole grid from Display
  tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H, STEP_FRAME_W * 20, STEP_FRAME_H * 13, ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
  tft.fillRect(STEP_FRAME_W, STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H * 12, ILI9341_DARKGREY);
}
void showCoordinates() {
  tft.fillRect(20, 0, 50, 13, ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
  tft.setTextColor(ILI9341_BLUE);
  tft.setFont(Arial_10);
  tft.setCursor(20, 3);
  tft.print("X");
  tft.print(gridTouchX);
  tft.setTextColor(ILI9341_RED);
  tft.setCursor(45, 3);
  tft.print("Y");
  tft.print(gridTouchY);
}
void drawLastPotRow() {
  if (lastPotRow >= 4) {
    lastPotRow = 0;
  }
  if (lastPotRow >= 4) {
    tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
  }
  tft.fillRect(70, 0, 10, 16, ILI9341_DARKGREY);
  tft.fillRect(70, lastPotRow * 4, 10, 3, ILI9341_RED);
}




//===========================================================
// Try Draw using writeRect
#define BUFFPIXEL 80
void bmpDraw(const char* filename, uint8_t x, uint16_t y) {

  File bmpFile;
  int bmpWidth, bmpHeight;              // W+H in pixels
  uint8_t bmpDepth;                     // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;              // Start of image data in file
  uint32_t rowSize;                     // Not always = bmpWidth; may have padding
  uint8_t sdbuffer[3 * BUFFPIXEL];      // pixel buffer (R+G+B per pixel)
  uint16_t buffidx = sizeof(sdbuffer);  // Current position in sdbuffer
  boolean goodBmp = false;              // Set to true on valid header parse
  boolean flip = true;                  // BMP is stored bottom-to-top
  int w, h, row, col;
  uint8_t r, g, b;
  uint32_t pos = 0, startTime = millis();

  uint16_t awColors[320];  // hold colors for one row at a time...

  if ((x >= tft.width()) || (y >= tft.height())) return;

  Serial.println();
  Serial.print(F("Loading image '"));
  Serial.print(filename);
  Serial.println('\'');

  // Open requested file on SD card
  if (!(bmpFile = SD.open(filename))) {
    Serial.print(F("File not found"));
    return;
  }

  // Parse BMP header
  if (read16(bmpFile) == 0x4D42) {  // BMP signature
    Serial.print(F("File size: "));
    Serial.println(read32(bmpFile));
    (void)read32(bmpFile);             // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile);  // Start of image data
    Serial.print(F("Image Offset: "));
    Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print(F("Header size: "));
    Serial.println(read32(bmpFile));
    bmpWidth = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if (read16(bmpFile) == 1) {    // # planes -- must be '1'
      bmpDepth = read16(bmpFile);  // bits per pixel
      Serial.print(F("Bit Depth: "));
      Serial.println(bmpDepth);
      if ((bmpDepth == 24) && (read32(bmpFile) == 0)) {  // 0 = uncompressed

        goodBmp = true;  // Supported BMP format -- proceed!
        Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if (bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if ((x + w - 1) >= tft.width()) w = tft.width() - x;
        if ((y + h - 1) >= tft.height()) h = tft.height() - y;

        for (row = 0; row < h; row++) {  // For each scanline...

          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if (flip)  // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else  // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if (bmpFile.position() != pos) {  // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer);  // Force buffer reload
          }

          for (col = 0; col < w; col++) {  // For each pixel...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) {  // Indeed
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0;  // Set index to beginning
            }

            // Convert pixel from BMP to TFT format, push to display
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            awColors[col] = tft.color565(r, g, b);
          }  // end pixel
          tft.writeRect(0, row, w, 1, awColors);
        }  // end scanline
        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      }  // end goodBmp
    }
  }

  bmpFile.close();
  if (!goodBmp) Serial.println(F("BMP format not recognized."));
}


//scale selector
void gridScaleSelector() {  //static Display rendering
  clearWorkSpace();
  tft.drawRect(STEP_FRAME_W * 2, STEP_FRAME_H, STEP_FRAME_W * 16, STEP_FRAME_H * MAX_SCALES, ILI9341_WHITE);  //Xmin, Ymin, Xlength, Ylength, color
}
void scaleSelector() {
  if (millis() % interval == 0) {
    for (int i = 0; i < MAX_SCALES; i++) {
      tft.setCursor(STEP_FRAME_W * 2, STEP_FRAME_H * i + STEP_FRAME_H);
      tft.setFont(Arial_8);
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(1);
      tft.print(scaleNames[i]);

      if (gridTouchX > 1 && gridTouchX < 15 && gridTouchY == i + 1) {
        scaleSelected = i;
        tft.fillRect(STEP_FRAME_W * POSITION_SCALE_BUTTON + 1, 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
        tft.setCursor(STEP_FRAME_W * POSITION_SCALE_BUTTON + 2, 4);
        tft.setFont(Arial_8);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.print(scaleNamesShort[scaleSelected]);
      }
    }
  }
}
//soongmode stuff
void drawsongmodepageselector() {
  //draw 16 rects of 16x16px in the 13th row
  for (int pages = 2; pages < 18; pages++) {
    drawActiveRect(pages, 13, 1, 1, selectPage == pages + 8, "", ILI9341_LIGHTGREY);
    tft.drawRect(STEP_FRAME_W * pages, STEP_FRAME_H * 13, STEP_FRAME_W, STEP_FRAME_H, ILI9341_WHITE);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(STEP_FRAME_W * pages + 3, STEP_FRAME_H * 13 + 4);
    tft.print((pages - 1));
  }
  tft.fillRect(STEP_FRAME_W * 18, STEP_FRAME_H * 13, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_RED);
  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(STEP_FRAME_W * 18 + 3, STEP_FRAME_H * 13 + 4);
  tft.print("Clear");
}
void drawarrengmentLines(int songpageNumber) {
  page_phrase_start = songpageNumber * 16;
  page_phrase_end = (songpageNumber + 1) * 16;

  //draw horizontal song arrangment Lines
  for (int phrasers = page_phrase_start; phrasers < page_phrase_end; phrasers++) {
    for (int trackss = 0; trackss < 8; trackss++) {
      drawarrengmentLine(songpageNumber, trackss, phrasers);
    }
  }
}
void drawarrengmentLine(int songpageNumber, byte trackTouchY, byte touched_phrase) {
  page_phrase_start = songpageNumber * 16;
  page_phrase_end = (songpageNumber + 1) * 16;
  //draw horizontal song arrangment Lines
  //for clip 8
  if (track[trackTouchY].arrangment1[touched_phrase] == 8) {
    for (int thickness = -8; thickness < 8; thickness++) {
      tft.drawFastHLine(((touched_phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2) + 1, ((trackTouchY + 1) * TRACK_FRAME_H + thickness) + 4, phraseSegmentLength - 1, ILI9341_DARKGREY);  //(x-start, y, length, color)
    }

    //draw clipnumber
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_DARKGREY);
    tft.setCursor((touched_phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2 + 1, (trackTouchY + 1) * TRACK_FRAME_H - 4);
    tft.print(track[trackTouchY].arrangment1[touched_phrase]);

    //draw noteOffset
    tft.setCursor((touched_phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2 + 6, (trackTouchY + 1) * TRACK_FRAME_H + 4);
    if (track[trackTouchY].NoteOffset[touched_phrase] < 0) {
      tft.setTextColor(ILI9341_DARKGREY);
      tft.setCursor((touched_phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2 + 2, (trackTouchY + 1) * TRACK_FRAME_H + 4);
      tft.print("-");
    } else {
      tft.setTextColor(ILI9341_DARKGREY);
      tft.setCursor((touched_phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2 + 2, (trackTouchY + 1) * TRACK_FRAME_H + 4);
      tft.print("-");
    }
    tft.setTextColor(ILI9341_DARKGREY);
    tft.print(abs(track[trackTouchY].NoteOffset[touched_phrase]));
  } else {
    //for other clips
    for (int thickness = -8; thickness < 8; thickness++) {
      tft.drawFastHLine(((touched_phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2) + 1, ((trackTouchY + 1) * TRACK_FRAME_H + thickness) + 4, phraseSegmentLength - 1, trackColor[trackTouchY] + (track[trackTouchY].arrangment1[touched_phrase] * 20));  //(x-start, y, length, color)
    }
    //draw clipnumber
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor((touched_phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2 + 1, (trackTouchY + 1) * TRACK_FRAME_H - 4);
    tft.print(track[trackTouchY].arrangment1[touched_phrase]);
    //draw noteOffset
    tft.setCursor((touched_phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2 + 6, (trackTouchY + 1) * TRACK_FRAME_H + 4);
    if (track[trackTouchY].NoteOffset[touched_phrase] < 0) {
      tft.setTextColor(ILI9341_BLACK);
      tft.setCursor((touched_phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2 + 2, (trackTouchY + 1) * TRACK_FRAME_H + 4);
      tft.print("-");
    } else {
      tft.setTextColor(trackColor[trackTouchY] + (track[trackTouchY].arrangment1[touched_phrase] * 20));
      tft.setCursor((touched_phrase - (16 * songpageNumber)) * phraseSegmentLength + STEP_FRAME_W * 2 + 2, (trackTouchY + 1) * TRACK_FRAME_H + 4);
      tft.print("-");
    }
    tft.setTextColor(ILI9341_BLACK);
    tft.print(abs(track[trackTouchY].NoteOffset[touched_phrase]));
  }
}
void clearArrangment() {
  for (int ctrack = 0; ctrack < 8; ctrack++) {
    for (int cphrase = 0; cphrase < MAX_PHRASES - 1; cphrase++) {
      track[ctrack].arrangment1[cphrase] = 8;
      track[ctrack].NoteOffset[cphrase] = 0;
      track[ctrack].Ttrckprst[cphrase] = 0;
      track[ctrack].volume[cphrase] = 99;
    }
  }
}




//step sequencer stuff
void drawStepSequencerStatic(int stepWidth) {
  //draw the Main Grid
  for (int i = 0; i < 17; i++) {  //vert Lines
    int step_Frame_X = i * stepWidth;
    tft.drawFastVLine(step_Frame_X + STEP_FRAME_W * 2, STEP_FRAME_H, GRID_LENGTH_VERT, ILI9341_WHITE);  //(x, y-start, length, color)
    if (i % 4 == 0) {
      tft.drawFastVLine((i * stepWidth) + 32, STEP_FRAME_H, STEP_FRAME_H * 12, ILI9341_LIGHTGREY);  //(x, y-start, y-length, color)
    }
  }
  for (int i = 0; i < 13; i++) {  //hor lines
    int step_Frame_Y = i * 16;
    tft.drawFastHLine(STEP_FRAME_W * 2, step_Frame_Y + STEP_FRAME_H, NUM_STEPS * stepWidth, ILI9341_WHITE);  //(x-start, y, length, color)
  }
}
void draw_Notenames() {
  for (int n = 0; n < MAX_VOICES; n++) {  //hor notes
    if (scales[scaleSelected][n]) {
      tft.fillRect(STEP_FRAME_W, STEP_FRAME_H * n + STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H, trackColor[desired_instrument]);
    }

    tft.setCursor(20, STEP_FRAME_H * n + 20);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(1);
    if (desired_instrument == 0) {
      tft.print(n + allTracks[desired_instrument]->shownOctaves * 12);
    } else {
      tft.print(noteNames[n]);
    }
  }
}
void drawMelodicControls() {
  switch (lastPotRow) {
    case 0:
      showCoordinates();
      allTracks[desired_instrument]->drawStepLenght();
      allTracks[desired_instrument]->drawVoiceCount();

      break;
    case 1:
      allTracks[desired_instrument]->drawShownOctave();
      allTracks[desired_instrument]->drawClipToEdit();
      allTracks[desired_instrument]->drawClockDivision();
      allTracks[desired_instrument]->drawMIDIChannel();
      break;
    case 2:
      allTracks[desired_instrument]->drawSeqMode();
      allTracks[desired_instrument]->drawSeqVelocity();
      drawChar(18, 0, "", ILI9341_WHITE);
      break;
  }
}
#define TICK_PIXEL_WIDTH 3

void drawActivePolyPixel() {  //draw steps for the melodic tracks 2-8
  clearPixelGrid();
  int tone_start = allTracks[desired_instrument]->shownOctaves * 12;

  //draw active steps
  for (int steps = 0; steps < TICKS_PER_BAR; steps++) {
    for (int polys = 0; polys < MAX_VOICES; polys++) {
      int dot_on_X = (steps * TICK_PIXEL_WIDTH) + 32;
      int dot_on_Y = ((ctrack[desired_track].sequence[allTracks[desired_instrument]->clipToEdit].tick[steps].voice[polys] - tone_start) * STEP_FRAME_H) + PIX_OFFSET_Y;
      int vol_graph = ((ctrack[desired_track].sequence[allTracks[desired_instrument]->clipToEdit].tick[steps].velo[polys] / 10) + 1);
      int vol_graph_center = 6 - (vol_graph / 2);

      if (ctrack[desired_track].sequence[allTracks[desired_instrument]->clipToEdit].tick[steps].voice[polys] > VALUE_NOTEOFF) {
        for (int h = 0; h < TICK_PIXEL_WIDTH; h++) {
          //for (int w = -4; w < 5; w++) {
          tft.drawFastVLine(dot_on_X + h, dot_on_Y + vol_graph_center, vol_graph, trackColor[desired_track] + (allTracks[desired_instrument]->clipToEdit * 20));
          //tft.drawPixel(dot_on_X + h, dot_on_Y, trackColor[desired_track] + (allTracks[desired_instrument]->clipToEdit * 20));
          //}
        }
        Serial.printf("Shown: VoiceCount = %d, Tick = %d, Note%d\n",
                      polys,
                      steps,
                      ctrack[desired_track].sequence[allTracks[desired_instrument]->clipToEdit].tick[steps].voice[polys]);
      }
    }
  }
  Serial.println("polysteps drawn");
}



void drawActivePolyPixelY(int X_Axis) {

  int tone_start = allTracks[desired_instrument]->shownOctaves * 12;
  int dot_on_X = (X_Axis * TICK_PIXEL_WIDTH) + 32;
  clearPixelGridY(dot_on_X);
  //draw active steps
  for (int polys = 0; polys < MAX_VOICES; polys++) {
    int dot_on_Y = ((ctrack[desired_track].sequence[allTracks[desired_instrument]->clipToEdit].tick[X_Axis].voice[polys] - tone_start) * STEP_FRAME_H) + PIX_OFFSET_Y;
    int vol_graph = ((ctrack[desired_track].sequence[allTracks[desired_instrument]->clipToEdit].tick[X_Axis].velo[polys] / 10) + 1);
    int vol_graph_center = 6 - (vol_graph / 2);

    if (ctrack[desired_track].sequence[allTracks[desired_instrument]->clipToEdit].tick[X_Axis].voice[polys] > VALUE_NOTEOFF) {
      for (int h = 0; h < TICK_PIXEL_WIDTH; h++) {
        tft.drawFastVLine(dot_on_X + h, dot_on_Y + vol_graph_center, vol_graph, trackColor[desired_track] + (allTracks[desired_instrument]->clipToEdit * 20));
        // tft.drawPixel(dot_on_X + h, dot_on_Y + w, trackColor[desired_track] + (allTracks[desired_instrument]->clipToEdit * 20));
      }
      Serial.printf("Drawing: VoiceCount = %d, Tick = %d, Note%d, vol_graph =%d\n",
                    polys,
                    X_Axis,
                    ctrack[desired_track].sequence[allTracks[desired_instrument]->clipToEdit].tick[X_Axis].voice[polys],
                    vol_graph);
    }
  }

  Serial.println("polytick drawn");
}
void clearPixelGrid() {  // clear all Steppixels from Display
  for (int T = 0; T < 12; T++) {
    for (int S = 0; S < TICKS_PER_BAR; S++) {
      for (int w = -5; w < 6; w++) {
        tft.drawPixel(S * TICK_PIXEL_WIDTH + 32, T * STEP_FRAME_H + DOT_OFFSET_Y + w, ILI9341_DARKGREY);  // circle: x, y, radius, color
        tft.drawPixel((S * TICK_PIXEL_WIDTH) + 1 + 32, T * STEP_FRAME_H + DOT_OFFSET_Y + w, ILI9341_DARKGREY);
        tft.drawPixel((S * TICK_PIXEL_WIDTH) + 2 + 32, T * STEP_FRAME_H + DOT_OFFSET_Y + w, ILI9341_DARKGREY);
      }
    }
  }
}
void clearPixelGridY(int X_Axis) {  // clear all Steppixels in the same column
  for (int T = 0; T < 12; T++) {
    for (int h = 0; h < TICK_PIXEL_WIDTH; h++) {
      for (int w = -5; w < 6; w++) {
        tft.drawPixel((X_Axis + h), (T * STEP_FRAME_H) + w + DOT_OFFSET_Y, ILI9341_DARKGREY);  // circle: x, y, radius, color
      }
    }
  }
}
void draw_ClipselectorRow() {
  for (int ClipNr = 0; ClipNr < 8; ClipNr++) {
    tft.fillRect(STEP_FRAME_W * 2 * ClipNr + STEP_FRAME_W * 2, STEP_FRAME_H * 13, STEP_FRAME_W * 2, STEP_FRAME_H, trackColor[desired_instrument] + (ClipNr * 20));
    tft.setCursor(STEP_FRAME_W * 2 * ClipNr + STEP_FRAME_W * 2 + 2, STEP_FRAME_H * 13 + 4);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(1);
    tft.print("Clip ");
    tft.print(ClipNr);
  }
  tft.fillRect(STEP_FRAME_W * 2 * 8 + STEP_FRAME_W * 2, STEP_FRAME_H * 13, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_RED);
  tft.setCursor(STEP_FRAME_W * 2 * 8 + STEP_FRAME_W * 2 + 2, STEP_FRAME_H * 13 + 4);
  tft.print("Clear");
}


//draw sub_pages buttons of a plugin, max 4 -- drawActiveRect is recommended
void draw_sub_page_buttons(int maxpages) {
  for (int pages = 0; pages < maxpages; pages++) {
    tft.drawRect(STEP_FRAME_W * 18 + 1, ((pages + 1)) * STEP_FRAME_H * 2 + STEP_FRAME_H, STEP_FRAME_W * 2 - 1, STEP_FRAME_H * 2, ILI9341_WHITE);
    tft.setFont(Arial_12);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(STEP_FRAME_W * 18 + 12, ((pages + 1)) * STEP_FRAME_H * 2 + STEP_FRAME_H + 12);
    tft.print(pages + 1);
  }
}
void drawPotDrum(int XPos, byte YPos, byte fvalue, int dvalue, byte dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color
                                                                                         //drawPot Variables
  static float circlePos;
  static float circlePos_old;
  static int dvalue_old;
  int yPos = (YPos + 1) * 3;
  int xPos = ((XPos + 1) * 4) - 1;
  circlePos = fvalue / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.setCursor(STEP_FRAME_W * xPos, STEP_FRAME_H * (yPos + 1) + 3);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos) + 2.25), 4, color);
  circlePos_old = circlePos;
  dvalue_old = dvalue;
}
void drawPotCC(int XPos, byte YPos, byte fvaluecc, byte dvaluecc, int color) {  //xposition, yposition, value 1-127, value to draw, name to draw, color
  //drawPotcc Variables
  static float circlePoscc;
  static float circlePos_oldcc;
  static int dvalue_oldcc;
  static int dname_oldcc;
  int yPos = (YPos + 1) * 3;
  int xPos = ((XPos + 1) * 4) - 1;
  circlePoscc = fvaluecc / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_oldcc);


  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvaluecc);


  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_oldcc) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_oldcc) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePoscc) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePoscc) + 2.25), 4, color);
  circlePos_oldcc = circlePoscc;
  dvalue_oldcc = dvaluecc;
}
