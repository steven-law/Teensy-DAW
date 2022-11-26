//this is a simple sampleplayer. It reads directly from the sdcard, maybe this is something to change
//about 6-8 samples can be played simultaniously, WHEN WAV-files are Mono and as short as possible (16-bit, 44100Hz)
//a possible alternate would be to change to read from memory.
//No problem for a teensy 4.x but maybe in the future for my 3.5.


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
  for (byte touchX = 1; touchX < 5; touchX++) {
    drawPot(touchX * 3, CTRL_ROW_0, pl4[0].Vol_rnd[touchX - 1], pl4[0].Vol_rnd[touchX - 1], showVOL[touchX - 1], trackColor[desired_instrument]);
    drawPot(touchX * 3, CTRL_ROW_1, pl4[0].Vol_rnd[touchX + 3], pl4[0].Vol_rnd[touchX + 3], showVOL[touchX + 3], trackColor[desired_instrument]);
    drawPot(touchX * 3, CTRL_ROW_2, pl4[0].Vol_rnd[touchX + 7], pl4[0].Vol_rnd[touchX + 7], showVOL[touchX + 7], trackColor[desired_instrument]);
  }
}


void Plugin4_Page1_Dynamic() {
  switch (lastPotRow) {
    case 0:
      if (msecs % 11 == 0) {
        for (byte touchX = 1; touchX < 5; touchX++) {
          if (abs(Potentiometer[touchX - 1] - pl4[0].Vol_rnd[touchX - 1]) < POTPICKUP) {
            if (pl4[0].Vol_rnd[touchX - 1] != Potentiometer[touchX - 1]) {
              drawPot(touchX * 3, CTRL_ROW_0, pl4[0].Vol_rnd[touchX - 1], pl4[0].Vol_rnd[touchX - 1], showVOL[touchX - 1], trackColor[desired_instrument]);
              pl4[0].Vol_rnd[touchX - 1] = Potentiometer[touchX - 1];
              pl4[0].Vol[touchX - 1] = pl4[0].Vol_rnd[touchX - 1] / 127.00;
              pl4drummixer1.gain(touchX - 1, pl4[0].Vol[touchX - 1]);
            }
          }
        }
      }
      break;
    case 1:
      if (msecs % 11 == 0) {
        for (byte touchX = 1; touchX < 5; touchX++) {
          if (abs(Potentiometer[touchX -1] - pl4[0].Vol_rnd[touchX + 3]) < POTPICKUP) {
            if (pl4[0].Vol_rnd[touchX + 3] != Potentiometer[touchX - 1]) {
              drawPot(touchX * 3, CTRL_ROW_1, pl4[0].Vol_rnd[touchX + 3], pl4[0].Vol_rnd[touchX + 3], showVOL[touchX + 3], trackColor[desired_instrument]);
              pl4[0].Vol_rnd[touchX + 3] = Potentiometer[touchX - 1];
              pl4[0].Vol[touchX + 3] = pl4[0].Vol_rnd[touchX + 3] / 127.00;
              pl4drummixer2.gain(touchX - 1, pl4[0].Vol[touchX + 3]);
            }
          }
        }
      }
      break;
    case 2:
      if (msecs % 11 == 0) {
        for (byte touchX = 1; touchX < 5; touchX++) {
          if (abs(Potentiometer[touchX -1] - pl4[0].Vol_rnd[touchX + 7]) < POTPICKUP) {
            if (pl4[0].Vol_rnd[touchX + 7] != Potentiometer[touchX - 1]) {
              drawPot(touchX * 3, CTRL_ROW_2, pl4[0].Vol_rnd[touchX + 7], pl4[0].Vol_rnd[touchX + 7], showVOL[touchX + 7], trackColor[desired_instrument]);
              pl4[0].Vol_rnd[touchX + 7] = Potentiometer[touchX - 1];
              pl4[0].Vol[touchX + 7] = pl4[0].Vol_rnd[touchX + 7] / 127.00;
              pl4drummixer3.gain(touchX - 1, pl4[0].Vol[touchX + 7]);
            }
          }
        }
      }
      break;

  }
  TS_Point p = ts.getPoint();
  if (ts.touched() || enter_button) {


    if (gridTouchY >= 2 && gridTouchY <= 4) {
      lastPotRow = 0;
    }

    if (gridTouchY >= 5 && gridTouchY <= 7) {
      lastPotRow = 1;
    }

    if (gridTouchY >= 8 && gridTouchY <= 10) {
      lastPotRow = 2;
    }
    if (gridTouchY >= 11 && gridTouchY <= 13) {
      lastPotRow = 3;
    }
  }
}