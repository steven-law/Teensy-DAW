void Plugin_View_Static(byte desired_instrument) {

  if (selectPage == PLUGIN1_PAGE1) {
    Plugin1_Page_Static(0);
  }
  if (selectPage == PLUGIN1_PAGE2) {
    Plugin1_Page_Static(1);
  }


  if (selectPage == PLUGIN2_PAGE1) {
    Plugin2_Page_Static(0);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////
  ///////// if we select the pluginpage its PLUGINx_PAGE1 bool gets true and selects the Pluginx_Page_Static once
  ///////// now we see the actual graphs and values, but the programm switches over to Pluginx_Page_Dynamic(),
  ///////// which is called all the time in the loop() function as long PLUGINx_PAGE1 is true, for controlling the parameters
  ////////////////////////////////////////////////////////////////////////////////////////////////
  if (selectPage == PLUGIN3_PAGE1) {
    Plugin3_Page_Static(0);
  }
  if (selectPage == PLUGIN4_PAGE1) {
    Plugin4_Page_Static(0);
  }
  if (selectPage == PLUGIN5_PAGE1) {
    Plugin5_Page_Static(0);
  }
  if (selectPage == PLUGIN6_PAGE1) {
    Plugin6_Page_Static(0);
  }
  if (selectPage == PLUGIN7_PAGE1) {
    Plugin7_Page_Static(0);
  }
  if (selectPage == PLUGIN7_PAGE2) {
    Plugin7_Page_Static(1);
  }

  if (selectPage == PLUGIN8_PAGE1) {
    Plugin8_Page_Static(0);
  }
  if (selectPage == PLUGIN9_PAGE1) {
    Plugin9_Page_Static(0);
  }
  if (selectPage == PLUGIN10_PAGE1) {
    Plugin10_Page_Static(0);
  }
}

void Plugin_View_Dynamic() {
  //***********************************************************************************************************************
  // 4) copy one of the plugin Page Views
  //    and change the names according to our variables and functions.
  //    Every page you want to make has to have its own statement
  //    we create:

  //  //setting up the Plugin3 Page1-view
  //    if (selectPage == PLUGIN3_PAGE1) {
  //      Plugin3_Page1_Dynamic();
  //    }

  // after adding the active state statement
  // head over to "midi.ino"
  //look for *****************************************************************************************

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //-----------------------------------------
  //setting up the Plugin1 Page1-view
  if (selectPage == PLUGIN1_PAGE1) {
    Plugin1_Page1_Dynamic();
  }
  //setting up the Plugin1 Page2-view
  if (selectPage == PLUGIN1_PAGE2) {
    Plugin1_Page2_Dynamic();
  }

  //setting up the Plugin2 Page1-view
  if (selectPage == PLUGIN2_PAGE1) {
    Plugin2_Page1_Dynamic();
  }


  /////////////////////////////////////////////////////////////////////////////
  //setting up the Plugin3 Page1-view
  if (selectPage == PLUGIN3_PAGE1) {
    Plugin3_Page1_Dynamic();
  }
  /////////////////////////////////////////////////////////////////////////////


  //setting up the Plugin4 Page1-view
  if (selectPage == PLUGIN4_PAGE1) {
    Plugin4_Page1_Dynamic();
  }

  //setting up the Plugin5 Page1-view
  if (selectPage == PLUGIN5_PAGE1) {
    Plugin5_Page1_Dynamic();
  }
  //setting up the Plugin6 Page1-view
  if (selectPage == PLUGIN6_PAGE1) {
    Plugin6_Page1_Dynamic();
  }
  //setting up the Plugin7 Page1-view
  if (selectPage == PLUGIN7_PAGE1) {
    Plugin7_Page1_Dynamic();
  }
  //setting up the Plugin7 Page2-view
  if (selectPage == PLUGIN7_PAGE2) {
    Plugin7_Page2_Dynamic();
  }
  //setting up the Plugin8 Page1-view
  if (selectPage == PLUGIN8_PAGE1) {
    Plugin8_Page1_Dynamic();
  }
  //setting up the Plugin9 Page1-view
  if (selectPage == PLUGIN9_PAGE1) {
    Plugin9_Page1_Dynamic();
  }
  //setting up the Plugin10 Page1-view
  if (selectPage == PLUGIN10_PAGE1) {
    Plugin10_Page1_Dynamic();
  }



    //setting up the StepSequencer-view for drumtrack #1
  if (selectPage == DRUMTRACK) {
    drumStepSequencer();
  }
  //setting up the melodicStepSequencer-view for #2-8
  for (byte i = 1; i < 8; i++) {
    if (selectPage == i) {
      melodicStepSequencer(i);
    }
  }
  //setting up the scaleSelector-view
  if (selectPage == SCALESELECT) {
    scaleSelector();
  }

  //setting up the songMode-view1
  for (byte pagenr = 0; pagenr < 16; pagenr++) {
    if (selectPage == pagenr + 10) {
      songModePage(pagenr);
    }
  }

  //setting up the Recorder Page
  if (selectPage == RECORDER_PAGE) {
    recorder_Page1_Dynamic();
  }


  //setting up the Mixer Page 1
  if (selectPage == MIXER_PAGE_1) {
    MixerPage1_Dynamic();
  }
  //setting up the Mixer Page 2
  if (selectPage == MIXER_PAGE_2) {
    MixerPage2_Dynamic();
  }
  //setting up the Mixer Page 3
  if (selectPage == MIXER_PAGE_3) {
    MixerPage3_Dynamic();
  }
  //setting up the Mixer Page 3
  if (selectPage == FX1_PAGE1) {
    FX1reverb_dynamic();
  }
  //setting up the Mixer Page 3
  if (selectPage == FX2_PAGE1) {
    FX2Bitcrush_dynamic();
  }
  //setting up the Mixer Page 2
  if (selectPage == MIDICC_PAGE_1) {
    midiCCpage1_Dynamic(desired_track);
  }
}

// 7) add your amp.gain() control to the volume-functions in "functions.ino"
void pluginVolume(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  if (pluginchannel == 17) {
    pl1amp.gain(volume);
  }
  if (pluginchannel == 18) {
    pl2amp.gain(volume);
  }
  if (pluginchannel == 19) {
    pl3amp.gain(volume);
  }
  if (pluginchannel == 20) {
    pl4amp.gain(volume);
  }

  if (pluginchannel == 21) {
    pl5amp.gain(volume);
  }
  if (pluginchannel == 22) {
    pl6amp.gain(volume);
  }
  if (pluginchannel == 23) {
    pl7amp.gain(volume);
  }
  if (pluginchannel == 24) {
    pl8amp.gain(volume);
  }
  if (pluginchannel == 25) {
    pl9amp.gain(volume);
  }
}
// 7) add your amp.gain() control to the volume-functions in "functions.ino"
void pluginGain(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  if (pluginchannel == 17) {
    pl1amp2.gain(volume);
  }
  if (pluginchannel == 18) {
    pl2amp2.gain(volume);
  }
  if (pluginchannel == 19) {
    pl3amp2.gain(volume);
  }
  if (pluginchannel == 20) {
    pl4amp2.gain(volume);
  }

  if (pluginchannel == 21) {
    pl5amp2.gain(volume);
  }
  if (pluginchannel == 22) {
    pl6amp2.gain(volume);
  }
  if (pluginchannel == 23) {
    pl7amp2.gain(volume);
  }
  if (pluginchannel == 24) {
    pl8amp2.gain(volume);
  }
  if (pluginchannel == 25) {
    pl9amp2.gain(volume);
  }
}
void FXDrypluginVolume(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  if (pluginchannel == 17) {
    mixer5.gain(0, volume);
  }
  if (pluginchannel == 18) {
    mixer5.gain(1, volume);
  }
  if (pluginchannel == 19) {
    mixer5.gain(2, volume);
  }
  if (pluginchannel == 20) {
    mixer5.gain(3, volume);
  }

  if (pluginchannel == 21) {
    mixer6.gain(0, volume);
  }
  if (pluginchannel == 22) {
    mixer6.gain(1, volume);
  }
  if (pluginchannel == 23) {
    mixer6.gain(2, volume);
  }
  if (pluginchannel == 24) {
    mixer6.gain(3, volume);
  }
  if (pluginchannel == 25) {
    mixer10.gain(1, volume);
  }
}
void FX1pluginVolume(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  if (pluginchannel == 17) {
    FX1mixer1.gain(0, volume);
  }
  if (pluginchannel == 18) {
    FX1mixer1.gain(1, volume);
  }
  if (pluginchannel == 19) {
    FX1mixer1.gain(2, volume);
  }
  if (pluginchannel == 20) {
    FX1mixer1.gain(3, volume);
  }

  if (pluginchannel == 21) {
    FX1mixer2.gain(0, volume);
  }
  if (pluginchannel == 22) {
    FX1mixer2.gain(1, volume);
  }
  if (pluginchannel == 23) {
    FX1mixer2.gain(2, volume);
  }
  if (pluginchannel == 24) {
    FX1mixer2.gain(3, volume);
  }

  if (pluginchannel == 25) {
    FX1mixer4.gain(0, volume);
  }
}
void FX2pluginVolume(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  if (pluginchannel == 17) {
    FX2mixer1.gain(0, volume);
  }
  if (pluginchannel == 18) {
    FX2mixer1.gain(1, volume);
  }
  if (pluginchannel == 19) {
    FX2mixer1.gain(2, volume);
  }
  if (pluginchannel == 20) {
    FX2mixer1.gain(3, volume);
  }

  if (pluginchannel == 21) {
    FX2mixer2.gain(0, volume);
  }
  if (pluginchannel == 22) {
    FX2mixer2.gain(1, volume);
  }
  if (pluginchannel == 23) {
    FX2mixer2.gain(2, volume);
  }
  if (pluginchannel == 24) {
    FX2mixer2.gain(3, volume);
  }
  if (pluginchannel == 25) {
    FX2mixer4.gain(0, volume);
  }
}
void FX3pluginVolume(byte pluginchannel, float volume) {  //track´s MIDI Channel (>16), mixer.gain 0-5
  if (pluginchannel == 17) {
    FX3mixer1.gain(0, volume);
  }
  if (pluginchannel == 18) {
    FX3mixer1.gain(1, volume);
  }
  if (pluginchannel == 19) {
    FX3mixer1.gain(2, volume);
  }
  if (pluginchannel == 20) {
    FX3mixer1.gain(3, volume);
  }

  if (pluginchannel == 21) {
    FX3mixer2.gain(0, volume);
  }
  if (pluginchannel == 22) {
    FX3mixer2.gain(1, volume);
  }
  if (pluginchannel == 23) {
    FX3mixer2.gain(2, volume);
  }
  if (pluginchannel == 24) {
    FX3mixer2.gain(3, volume);
  }
  if (pluginchannel == 25) {
    FX3mixer4.gain(0, volume);
  }
}
void selectFilterType(byte pluginchannel, byte mixerchannel) {
  if (pluginchannel == 17) {
    pl1mixer2.gain(0, 0);
    pl1mixer2.gain(1, 0);
    pl1mixer2.gain(2, 0);
    pl1mixer2.gain(mixerchannel, 1);
  }
  if (pluginchannel == 19) {
    pl3mixer1.gain(0, 0);
    pl3mixer1.gain(1, 0);
    pl3mixer1.gain(2, 0);
    pl3mixer1.gain(mixerchannel, 1);
  }
  if (pluginchannel == 21) {
    pl5mixer1.gain(0, 0);
    pl5mixer1.gain(1, 0);
    pl5mixer1.gain(2, 0);
    pl5mixer1.gain(mixerchannel, 1);
  }
  if (pluginchannel == 22) {
    pl6mixer1.gain(0, 0);
    pl6mixer1.gain(1, 0);
    pl6mixer1.gain(2, 0);
    pl6mixer1.gain(mixerchannel, 1);
  }
  if (pluginchannel == 25) {
    pl9mixer1.gain(0, 0);
    pl9mixer1.gain(1, 0);
    pl9mixer1.gain(2, 0);
    pl9mixer1.gain(mixerchannel, 1);
  }
}

//draw sub_pages buttons of a plugin, max 4 -- drawActiveRect is recommended
void draw_sub_page_buttons(byte maxpages) {
  for (byte pages = 0; pages < maxpages; pages++) {
    tft.drawRect(STEP_FRAME_W * 18 + 1, ((pages + 1)) * STEP_FRAME_H * 2 + STEP_FRAME_H, STEP_FRAME_W * 2 - 1, STEP_FRAME_H * 2, ILI9341_WHITE);
    tft.setFont(Arial_12);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(STEP_FRAME_W * 18 + 12, ((pages + 1)) * STEP_FRAME_H * 2 + STEP_FRAME_H + 12);
    tft.print(pages + 1);
  }
}
//draw a rectangle, if the state is high the rect gets filled
void drawActiveRect(byte xPos, byte yPos, byte xsize, byte ysize, bool state, char* name, int color) {
  if (state) {
    tft.fillRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * xsize, STEP_FRAME_W * ysize, color);
    tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * xsize, STEP_FRAME_W * ysize, color);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 3);
    tft.print(name);
  }
  if (!state) {
    tft.fillRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * xsize, STEP_FRAME_W * ysize, ILI9341_DARKGREY);
    tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * xsize, STEP_FRAME_W * ysize, color);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 3);
    tft.print(name);
  }
}



void drawPot(byte xPos, byte yPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

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
void drawPot(byte xPos, byte yPos, byte fvalue, char* dvalue_char, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

  circlePos = fvalue / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old_char);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_char);
  tft.setCursor(STEP_FRAME_W * xPos, STEP_FRAME_H * (yPos + 1) + 3);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos) + 2.25), 4, color);
  circlePos_old = circlePos;
  dvalue_old_char = dvalue_char;
}
void drawPot_2(byte xPos, byte yPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

  circlePos_2 = fvalue / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old_2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.setCursor(STEP_FRAME_W * xPos, STEP_FRAME_H * (yPos + 1) + 3);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old_2) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old_2) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_2) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_2) + 2.25), 4, color);
  circlePos_old_2 = circlePos_2;
  dvalue_old_2 = dvalue;
}
void drawPot_3(byte xPos, byte yPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

  circlePos_3 = fvalue / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old_3);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.setCursor(STEP_FRAME_W * xPos, STEP_FRAME_H * (yPos + 1) + 3);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old_3) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old_3) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_3) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_3) + 2.25), 4, color);
  circlePos_old_3 = circlePos_3;
  dvalue_old_3 = dvalue;
}
void drawPot_4(byte xPos, byte yPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color

  circlePos_4 = fvalue / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old_4);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.setCursor(STEP_FRAME_W * xPos, STEP_FRAME_H * (yPos + 1) + 3);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old_4) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old_4) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_4) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_4) + 2.25), 4, color);
  circlePos_old_4 = circlePos_4;
  dvalue_old_4 = dvalue;
}
void drawPotCC(byte xPos, byte yPos, byte fvaluecc, byte dvaluecc, int color) {  //xposition, yposition, value 1-127, value to draw, name to draw, color

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

//draws a number into a rect of 2x1grids  drawActiveRect is recommended
void drawNrInRect(byte xPos, byte yPos, byte dvalue, int color) {
  tft.setFont(Arial_8);
  tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * 2, STEP_FRAME_H, color);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 4);
  tft.print(dvalue_old);
  tft.setTextColor(color);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 4);
  tft.print(dvalue);
  dvalue_old = dvalue;
}
void drawNrInRect2(byte xPos, byte yPos, byte dvalue, int color) {
  tft.setFont(Arial_8);
  tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * 2, STEP_FRAME_H, color);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 4);
  tft.print(dvalue_old2);
  tft.setTextColor(color);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 4);
  tft.print(dvalue);
  dvalue_old2 = dvalue;
}
//draws a number into a rect of 2x1grids  drawActiveRect is recommended
void drawChar(byte xPos, byte yPos, char* dvalue_char, int color) {
  tft.setFont(Arial_8);
  //tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * 2, STEP_FRAME_H, color);
  tft.fillRect(STEP_FRAME_W * xPos + 1, STEP_FRAME_H * yPos + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
  tft.setTextColor(color);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 4);
  tft.print(dvalue_char);
  dvalue_old_char = dvalue_char;
}





void clearWorkSpace() {                                                                                  //clear the whole grid from Display
  tft.fillRect(STEP_FRAME_W * 2, STEP_FRAME_H, STEP_FRAME_W * 20, STEP_FRAME_H * 13, ILI9341_DARKGREY);  //Xmin, Ymin, Xlength, Ylength, color
  tft.fillRect(STEP_FRAME_W, STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H * 12, ILI9341_DARKGREY);
}