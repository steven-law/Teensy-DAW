
void Plugin_View_Static(byte desired_instrument) {
  clearWorkSpace();
  if (selectPage[PLUGIN1_PAGE1]) {
    Plugin1_Page_Static(0);
  }
  if (selectPage[PLUGIN1_PAGE2]) {
    Plugin1_Page_Static(1);
  }


  if (selectPage[PLUGIN2_PAGE1]) {
    Plugin2_Page_Static(0);
  }
  if (selectPage[PLUGIN3_PAGE1]) {
    Plugin3_Page_Static(0, desired_instrument);
  }
  if (selectPage[PLUGIN4_PAGE1]) {
    Plugin4_Page_Static(0);
  }
  if (selectPage[PLUGIN5_PAGE1]) {
    Plugin5_Page_Static(0);
  }
  if (selectPage[PLUGIN6_PAGE1]) {
    Plugin6_Page_Static(0);
  }
  if (selectPage[PLUGIN7_PAGE1]) {
    Plugin7_Page_Static(0);
  }
  if (selectPage[PLUGIN8_PAGE1]) {
    Plugin8_Page_Static(0);
  }
  if (selectPage[PLUGIN9_PAGE1]) {
    Plugin9_Page_Static(0);
  }
  if (selectPage[PLUGIN10_PAGE1]) {
    Plugin10_Page_Static(0);
  }
  
}


//draw sub_pages buttons of a plugin, max 4 -- drawActiveSquare is recommended
void draw_sub_page_buttons(byte maxpages) {
  for (byte pages = 0; pages < maxpages; pages++) {
    tft.drawRect(STEP_FRAME_W * 18 + 1, ((pages + 1)) * STEP_FRAME_H * 2 + STEP_FRAME_H, STEP_FRAME_W * 2 - 1, STEP_FRAME_H * 2, ILI9341_WHITE);
    tft.setFont(Arial_12);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(STEP_FRAME_W * 18 + 12, ((pages + 1)) * STEP_FRAME_H * 2 + STEP_FRAME_H + 12);
    tft.print(pages + 1);
  }
}
//draw a square, if the state is high the rect gets filled
void drawActiveSquare(byte xPos, byte yPos, byte size, bool state, char* name, int color) {
  if (state) {
    tft.fillRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * size, STEP_FRAME_W * size, color);
    tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * size, STEP_FRAME_W * size, color);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 3);
    tft.print(name);
  }
  if (!state) {
    tft.fillRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * size, STEP_FRAME_W * size, ILI9341_DARKGREY);
    tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * size, STEP_FRAME_W * size, color);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 3);
    tft.print(name);
  }
}

void drawbarH(byte XPos, byte YPos, byte value_rnd, char* fName, int color) {  //gridPosX, gridPosY, value 0-100, valuename, backgroundcolor of bargraph
  int value_Pix;
  int valueI_Pix;
  value_Pix = map(value_rnd, 0, 100, 0, 32);
  valueI_Pix = 32 - value_Pix;
  tft.drawRect(STEP_FRAME_W * XPos - 1, STEP_FRAME_H * YPos, STEP_FRAME_W * 2 + 3, STEP_FRAME_H, ILI9341_WHITE);
  tft.fillRect(STEP_FRAME_W * XPos + 1, STEP_FRAME_H * YPos + 1, value_Pix, STEP_FRAME_H - 2, color);
  tft.fillRect(STEP_FRAME_W * (XPos + 2) - valueI_Pix + 1, STEP_FRAME_H * YPos + 1, valueI_Pix, STEP_FRAME_H - 2, ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * XPos + 3, STEP_FRAME_H * (YPos - 1) + 4);
  tft.print(fName);
  tft.setCursor(STEP_FRAME_W * XPos + 3, STEP_FRAME_H * YPos + 4);
  tft.print(value_rnd);
}
void drawbarV(byte XPos, byte YPos, byte value_rnd, char* fName, int color) {  //gridPosX, gridPosY, value 0-100, valuename, backgroundcolor of bargraph
  int value_Pix;
  int valueI_Pix;
  value_Pix = map(value_rnd, 0, 100, 0, 32);
  valueI_Pix = 32 - value_Pix;
  tft.drawRect(STEP_FRAME_W * XPos, STEP_FRAME_H * (YPos - 1), STEP_FRAME_W, STEP_FRAME_H * 2, ILI9341_WHITE);
  tft.fillRect(STEP_FRAME_W * XPos + 1, STEP_FRAME_H * (YPos - 1) + 1, STEP_FRAME_W - 2, valueI_Pix - 2, ILI9341_DARKGREY);
  tft.fillRect(STEP_FRAME_W * XPos + 1, STEP_FRAME_H * (YPos + 1) - value_Pix + 1, STEP_FRAME_W - 2, value_Pix - 2, color);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * XPos - 3, STEP_FRAME_H * (YPos + 1) + 4);
  tft.print(fName);
  tft.setCursor(STEP_FRAME_W * XPos + 3, STEP_FRAME_H * YPos + 4);
  tft.print(value_rnd);
}
void drawPot(byte xPos, byte yPos, float fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

  circlePos = fvalue / 50;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.setCursor(STEP_FRAME_W * xPos + 3, STEP_FRAME_H * (yPos + 1) + 6);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos) + 2.25), 4, color);
  circlePos_old = circlePos;
  dvalue_old = dvalue;
}
void drawPotCC(byte xPos, byte yPos, byte fvaluecc, byte dvaluecc, byte dnamecc, int color) {  //xposition, yposition, value 1-127, value to draw, name to draw, color

  circlePoscc = fvaluecc / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_oldcc);
  tft.setCursor(STEP_FRAME_W * xPos + 3, STEP_FRAME_H * (yPos + 1) + 6);
  tft.print(dname_oldcc);

  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvaluecc);
  tft.setCursor(STEP_FRAME_W * xPos + 3, STEP_FRAME_H * (yPos + 1) + 6);
  tft.print(dnamecc);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_oldcc) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_oldcc) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePoscc) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePoscc) + 2.25), 4, color);
  circlePos_oldcc = circlePoscc;
  dvalue_oldcc = dvaluecc;
  dname_oldcc = dnamecc;
}
void drawPotLine(byte xPos, byte yPos, float fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

  drawPotLinePos = fvalue / 50;

  // tft.fillCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 21, ILI9341_DARKGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(drawPotLine_dvalue_old);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.setCursor(STEP_FRAME_W * xPos + 3, STEP_FRAME_H * (yPos + 1) + 6);
  tft.print(dname);
  for (int potLinelength; potLinelength <= 16; potLinelength++) {
    tft.drawPixel(STEP_FRAME_W * (xPos + 1) + potLinelength * cos((3 * drawPotLinePos_old) + 1.37), STEP_FRAME_H * yPos + potLinelength * sin((3 * drawPotLinePos_old) + 1.37), ILI9341_DARKGREY);
    tft.drawPixel(STEP_FRAME_W * (xPos + 1) + potLinelength * cos((3 * drawPotLinePos) + 1.37), STEP_FRAME_H * yPos + potLinelength * sin((3 * drawPotLinePos) + 1.37), color);
  }
  drawPotLinePos_old = drawPotLinePos;
  drawPotLine_dvalue_old = dvalue;
}






void clearWorkSpace() {                                                                                  //clear the whole grid from Display
  tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H, STEP_FRAME_W * 20, STEP_FRAME_H * 13, ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
  tft.fillRect(STEP_FRAME_W, STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H * 12, ILI9341_DARKGREY);
}
