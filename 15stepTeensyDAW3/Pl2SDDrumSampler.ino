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
}

void Plugin2_Page1_Dynamic() {

  if (ts.touched()) {
    if (gridTouchY == 3) {
      for (int touchX = 1; touchX < 5; touchX++) {
        if (gridTouchX == touchX * 3) {
          Pl2Vol_rnd[touchX - 1] = map(Potentiometer1, 0, 1023, 0, 99.00);
          Pl2Vol[touchX - 1] = Pl2Vol_rnd[touchX - 1] / 100.00;
          drummixer1.gain(touchX-1, Pl2Vol[touchX - 1]);
          drawbarH(touchX * 3, 3, Pl2Vol_rnd[touchX - 1], Pl2Controls[touchX - 1], ILI9341_BLUE);
        }
      }
    }
    if (gridTouchY == 7) {
      for (int touchX = 1; touchX < 5; touchX++) {
        if (gridTouchX == touchX * 3) {
          Pl2Vol_rnd[touchX + 3] = map(Potentiometer1, 0, 1023, 0, 99.00);
          Pl2Vol[touchX + 3] = Pl2Vol_rnd[touchX + 3] / 100.00;
          drummixer2.gain(touchX-1, Pl2Vol[touchX + 3]);
          drawbarH(touchX * 3, 7, Pl2Vol_rnd[touchX + 3], Pl2Controls[touchX + 3], ILI9341_RED);
        }
      }
    }
    if (gridTouchY == 11) {
      for (int touchX = 1; touchX < 5; touchX++) {
        if (gridTouchX == touchX * 3) {
          Pl2Vol_rnd[touchX + 7] = map(Potentiometer1, 0, 1023, 0, 99.00);
          Pl2Vol[touchX + 7] = Pl2Vol_rnd[touchX + 7] / 100.00;
          drummixer3.gain(touchX-1, Pl2Vol[touchX + 7]);
          drawbarH(touchX * 3, 11, Pl2Vol_rnd[touchX + 7], Pl2Controls[touchX + 7], ILI9341_MAGENTA);
        }
      }
    }
  }
}