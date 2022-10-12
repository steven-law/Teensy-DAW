void FX1reverb_settings() {

  reverb1.reverbTime(1000);
  //mixer1 for FX1
  FX1mixer1.gain(0, 0);
  FX1mixer1.gain(1, 0);
  FX1mixer1.gain(2, 0);
  FX1mixer1.gain(3, 0);
  //mixer2 for FX1
  FX1mixer2.gain(0, 0);
  FX1mixer2.gain(1, 0);
  FX1mixer2.gain(2, 0);
  FX1mixer2.gain(3, 0);
  //mixer2 for FX1
  FX1mixer3.gain(0, 1);
  FX1mixer3.gain(1, 1);
  FX1mixer3.gain(2, 1);
  FX1mixer3.gain(3, 1);
}

void FX1reverb_static() {
  clearWorkSpace();
  drawActiveSquare(18, 3, 2, false, "Main", ILI9341_LIGHTGREY);
  drawActiveSquare(18, 5, 2, false, "D-4", ILI9341_LIGHTGREY);
  drawActiveSquare(18, 7, 2, false, "5-8", ILI9341_LIGHTGREY);

  drawActiveSquare(1, 5, 2, true, "Rvrb", ILI9341_LIGHTGREY);
  drawActiveSquare(1, 8, 2, false, "BitC", ILI9341_LIGHTGREY);
  drawActiveSquare(1, 11, 2, false, "Dly", ILI9341_LIGHTGREY);



  drawPot(3, 3, fx1reverbtime_graph, fx1reverbtime_rnd, "Reverb", ILI9341_RED);
}

void FX1reverb_dynamic() {
  if (ts.touched() || !buttons[6].read()) {


    if (gridTouchY == 3) {

      //reverbTime
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, 3, fx1reverbtime_graph, fx1reverbtime, "Reverb", ILI9341_RED);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - fx1reverbtime_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          fx1reverbtime_rnd = map(Potentiometer1, 0, 1023, 0, 500);
          fx1reverbtime = fx1reverbtime_rnd / 100.00;
          fx1reverbtime_graph = map(Potentiometer1, 0, 1023, 0, 100);
          reverb1.reverbTime(fx1reverbtime);
        }
      }
    }
    if (gridTouchX >= 18) {
      //page selection
      if (gridTouchY == 3 || gridTouchY == 4) {
        select_page(MIXER_PAGE_1);
        mixerPage1_Static(0);
        MixerPage1_Dynamic();
      }
      if (gridTouchY >= 5 && gridTouchY <= 6) {
        select_page(MIXER_PAGE_2);
        mixerPage2_Static();
        MixerPage2_Dynamic();
      }
      if (gridTouchY >= 7 && gridTouchY <= 8) {
        select_page(MIXER_PAGE_3);
        mixerPage3_Static();
        MixerPage3_Dynamic();
      }
    }
    if (gridTouchX == 1 || gridTouchX == 2) {

      if (gridTouchY == 5 || gridTouchY == 6) {
        select_page(FX1_PAGE1);
        FX1reverb_static();
      }
      if (gridTouchY == 8 || gridTouchY == 9) {
        select_page(FX2_PAGE1);
        FX2Bitcrush_static();
      }
    }
  }
}