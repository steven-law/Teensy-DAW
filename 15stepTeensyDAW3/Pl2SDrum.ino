//this is a simple sampleplayer. It reads directly from the sdcard, maybe this is something to change
//about 6-8 samples can be played simultaniously, WHEN WAV-files are Mono and as short as possible (16-bit, 44100Hz)
//a possible alternate would be to change to read from memory.
//No problem for a teensy 4.x but maybe in the future for my 3.5.


void Plugin_2_Settings() {
  drummixer1.gain(0, 1);
  drummixer1.gain(1, 1);
  drummixer1.gain(2, 1);
  drummixer1.gain(3, 1);

  drummixer2.gain(0, 1);
  drummixer2.gain(1, 1);
  drummixer2.gain(2, 1);
  drummixer2.gain(3, 1);

  drummixer3.gain(0, 1);
  drummixer3.gain(1, 1);
  drummixer3.gain(2, 1);
  drummixer3.gain(3, 1);

  drummixer4.gain(0, 1);
  drummixer4.gain(1, 1);
  drummixer4.gain(2, 1);
  drummixer4.gain(3, 1);

  pl2amp.gain(1);
}
void Plugin2_Page_Static(byte Pagenumber) {
  for (byte touchX = 1; touchX < 5; touchX++) {
    drawbarH(touchX * 3, CTRL_ROW_0, pl4[0].Vol_rnd[touchX - 1], showVOL[touchX - 1], trackColor[desired_instrument]);
    //drawPot(CTRL_COL_3, 3, pl3Volume_graph, pl3Volume_graph, "MIX", trackColor[desired_instrument]);
    drawbarH(touchX * 3, CTRL_ROW_1, pl4[0].Vol_rnd[touchX + 3], showVOL[touchX + 3], trackColor[desired_instrument]);
    drawbarH(touchX * 3, CTRL_ROW_2, pl4[0].Vol_rnd[touchX + 7], showVOL[touchX + 7], ILI9341_MAGENTA);
  }
}


void Plugin2_Page1_Dynamic() {

  TS_Point p = ts.getPoint();
  if (ts.touched() || !buttons[6].read()) {
    
    if (millis() % 20 > 15) {
      //Volume
      if (gridTouchY == CTRL_ROW_0) {
        for (byte touchX = 1; touchX < 5; touchX++) {
          drawbarH(touchX * 3, CTRL_ROW_0, pl4[0].Vol_rnd[touchX - 1], showVOL[touchX - 1], trackColor[desired_instrument]);
          if (gridTouchX == touchX * 3 || gridTouchX == (touchX * 3) + 1) {
            pl4[0].Vol_rnd[touchX - 1] = map(Potentiometer1, 0, 127, 0, 99.00);
            pl4[0].Vol[touchX - 1] = pl4[0].Vol_rnd[touchX - 1] / 100.00;
            drummixer1.gain(touchX - 1, pl4[0].Vol[touchX - 1]);
          }
        }
      }
      if (gridTouchY == CTRL_ROW_1) {
        for (byte touchX = 1; touchX < 5; touchX++) {
          drawbarH(touchX * 3, CTRL_ROW_1, pl4[0].Vol_rnd[touchX + 3], showVOL[touchX + 3], trackColor[desired_instrument]);
          if (gridTouchX == touchX * 3 || gridTouchX == (touchX * 3) + 1) {
            pl4[0].Vol_rnd[touchX + 3] = map(Potentiometer1, 0, 127, 0, 99.00);
            pl4[0].Vol[touchX + 3] = pl4[0].Vol_rnd[touchX + 3] / 100.00;
            drummixer2.gain(touchX - 1, pl4[0].Vol[touchX + 3]);
          }
        }
      }
      if (gridTouchY == CTRL_ROW_2) {
        for (byte touchX = 1; touchX < 5; touchX++) {
          drawbarH(touchX * 3, CTRL_ROW_2, pl4[0].Vol_rnd[touchX + 7], showVOL[touchX + 7], ILI9341_MAGENTA);
          if (gridTouchX == touchX * 3 || gridTouchX == (touchX * 3) + 1) {
            pl4[0].Vol_rnd[touchX + 7] = map(Potentiometer1, 0, 127, 0, 99.00);
            pl4[0].Vol[touchX + 7] = pl4[0].Vol_rnd[touchX + 7] / 100.00;
            drummixer3.gain(touchX - 1, pl4[0].Vol[touchX + 7]);
          }
        }
      }
    }
  }
}