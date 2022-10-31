//this is a simple sampleplayer. It reads directly from the sdcard, maybe this is something to change
//about 6-8 samples can be played simultaniously, WHEN WAV-files are Mono and as short as possible (16-bit, 44100Hz)
//a possible alternate would be to change to read from memory.
//No problem for a teensy 4.x, but maybe in the future for my 3.5.


void Plugin_4_Settings() {
  pl4drummixer1.gain(0, 1);
  pl4drummixer1.gain(1, 1);
  pl4drummixer1.gain(2, 1);
  pl4drummixer1.gain(3, 1);

  pl4drummixer2.gain(0, 1);
  pl4drummixer2.gain(1, 1);
  pl4drummixer2.gain(2, 1);
  pl4drummixer2.gain(3, 1);

  pl4drummixer3.gain(0, 1);
  pl4drummixer3.gain(1, 1);
  pl4drummixer3.gain(2, 1);
  pl4drummixer3.gain(3, 1);

  pl4drummixer4.gain(0, 1);
  pl4drummixer4.gain(1, 1);
  pl4drummixer4.gain(2, 1);
  pl4drummixer4.gain(3, 1);
  pl4amp.gain(1);
}
void Plugin4_Page_Static(byte Pagenumber) {
    //draw selecting pages buttons
  //draw_sub_page_buttons(2);
  for (byte touchX = 1; touchX < 5; touchX++) {
  drawbarH(touchX * 3, CONTROL_ROW_0, pl4[0].Vol_rnd[touchX - 1], showVOL[touchX - 1], ILI9341_BLUE);
  drawbarH(touchX * 3, CONTROL_ROW_1, pl4[0].Vol_rnd[touchX + 3], showVOL[touchX + 3], ILI9341_RED);
  drawbarH(touchX * 3, CONTROL_ROW_2, pl4[0].Vol_rnd[touchX + 7], showVOL[touchX + 7], ILI9341_MAGENTA);
  }

}
void Plugin4_Page1_Dynamic() {

    TS_Point p = ts.getPoint();
  if (ts.touched() || !buttons[6].read()) {
    gridTouchX = map(p.x, TS_MINX, TS_MAXX, 0, 19);
    gridTouchY = map(p.y, TS_MINY, TS_MAXY, 0, 14);
    if (gridTouchY == CONTROL_ROW_0) {
      for (byte touchX = 1; touchX < 5; touchX++) {
        drawbarH(touchX * 3, CONTROL_ROW_0, pl4[0].Vol_rnd[touchX - 1], showVOL[touchX - 1], ILI9341_BLUE);
        if (gridTouchX == touchX * 3 || gridTouchX == (touchX * 3) +1) {
          pl4[0].Vol_rnd[touchX - 1] = map(Potentiometer1, 0, 127, 0, 100);
          pl4[0].Vol[touchX - 1] = pl4[0].Vol_rnd[touchX - 1] / 100.00;
          pl4drummixer1.gain(touchX - 1, pl4[0].Vol[touchX - 1]);
        }
      }
    }
    if (gridTouchY == CONTROL_ROW_1) {
      for (byte touchX = 1; touchX < 5; touchX++) {
        drawbarH(touchX * 3, CONTROL_ROW_1, pl4[0].Vol_rnd[touchX + 3], showVOL[touchX + 3], ILI9341_RED);
        if (gridTouchX == touchX * 3 || gridTouchX == (touchX * 3) +1) {
          pl4[0].Vol_rnd[touchX + 3] = map(Potentiometer1, 0, 127, 0, 100);
          pl4[0].Vol[touchX + 3] = pl4[0].Vol_rnd[touchX + 3] / 100.00;
          pl4drummixer2.gain(touchX - 1, pl4[0].Vol[touchX + 3]);
        }
      }
    }
    if (gridTouchY == CONTROL_ROW_2) {
      for (byte touchX = 1; touchX < 5; touchX++) {
        drawbarH(touchX * 3, CONTROL_ROW_2, pl4[0].Vol_rnd[touchX + 7], showVOL[touchX + 7], ILI9341_MAGENTA);
        if (gridTouchX == touchX * 3 || gridTouchX == (touchX * 3) +1) {
          pl4[0].Vol_rnd[touchX + 7] = map(Potentiometer1, 0, 127, 0, 99.00);
          pl4[0].Vol[touchX + 7] = pl4[0].Vol_rnd[touchX + 7] / 100.00;
          pl4drummixer3.gain(touchX - 1, pl4[0].Vol[touchX + 7]);
        }
      }
    }
  }
}