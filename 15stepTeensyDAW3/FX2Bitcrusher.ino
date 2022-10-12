void FX2Bitcrush_settings() {
  //bitcrusher1 controlled by startKnob on page 3
  bitcrusher2.bits(4);
  bitcrusher2.sampleRate(11025);

  //mixer1 for FX2
  FX2mixer1.gain(0, 0);
  FX2mixer1.gain(1, 0);
  FX2mixer1.gain(2, 0);
  FX2mixer1.gain(3, 0);
  //mixer2 for FX2
  FX2mixer2.gain(0, 0);
  FX2mixer2.gain(1, 0);
  FX2mixer2.gain(2, 0);
  FX2mixer2.gain(3, 0);
  //mixer2 for FX2
  FX2mixer3.gain(0, 1);
  FX2mixer3.gain(1, 1);
  FX2mixer3.gain(2, 1);
  FX2mixer3.gain(3, 1);
}

void FX2Bitcrush_static() {
  clearWorkSpace();
  drawActiveSquare(18, 3, 2, false, "Main", ILI9341_LIGHTGREY);
  drawActiveSquare(18, 5, 2, false, "D-4", ILI9341_LIGHTGREY);
  drawActiveSquare(18, 7, 2, false, "5-8", ILI9341_LIGHTGREY);

  drawActiveSquare(1, 5, 2, false, "Rvrb", ILI9341_LIGHTGREY);
  drawActiveSquare(1, 8, 2, true, "BitC", ILI9341_LIGHTGREY);
  drawActiveSquare(1, 11, 2, false, "Dly", ILI9341_LIGHTGREY);

  drawPot(3, 3, fx2samplerate_graph, fx2samplerate, "SRate", ILI9341_RED);
  drawPot(7, 3, fx2bitcrush_graph, fx2bitcrush, "Crush", ILI9341_RED);
}

void FX2Bitcrush_dynamic() {
  if (ts.touched() || !buttons[6].read()) {


    if (gridTouchY == 3) {

      //samplerate
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, 3, fx2samplerate_graph, fx2samplerate, "SRate", ILI9341_RED);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - fx2samplerate_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          fx2samplerate = map(Potentiometer1, 0, 1023, 0, 44200);
          fx2samplerate_graph = map(Potentiometer1, 0, 1023, 0, 100);
          bitcrusher2.sampleRate(fx2samplerate);
        }
      }

      //samplerate
      if (gridTouchX == 7 || gridTouchX == 8) {
        drawPot(7, 3, fx2bitcrush_graph, fx2bitcrush, "Crush", ILI9341_RED);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - fx2bitcrush_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          fx2bitcrush = map(Potentiometer1, 0, 1023, 0, 12);
          fx2bitcrush_graph = map(Potentiometer1, 0, 1023, 0, 100);
          bitcrusher2.bits(fx2bitcrush);
        }
      }
    }
    if (gridTouchX >= 18) {
      //page selection
      if (gridTouchY >= 3 && gridTouchY <= 4) {
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