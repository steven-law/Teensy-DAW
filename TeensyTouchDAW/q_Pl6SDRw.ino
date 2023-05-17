void Plugin_6_Settings() {
  pl6modulator.amplitude(1);
  pl6carrier.amplitude(1);
  pl6envelope1.delay(0);
  pl6envelope1.hold(0);
  pl6envelope2.delay(0);
  pl6envelope2.hold(0);
  pl6envelope3.delay(0);
  pl6envelope3.hold(0);
  pl6mixer1.gain(0, 1);
  pl6mixer1.gain(1, 1);

  pl6mixer2.gain(0, 1);
  pl6mixer2.gain(1, 1);

  pl6mixer3.gain(0, 1);
  pl6mixer3.gain(1, 1);
  pl6mixer4.gain(0, 1);
  pl6mixer4.gain(1, 1);

  pl6mixer5.gain(0, 1);
  pl6mixer5.gain(1, 1);
  pl6mixer5.gain(2, 1);
  pl6mixer5.gain(3, 1);

  pl6amp.gain(1);
  pl6amp2.gain(1);
}

void Plugin6_Page1_Dynamic() {
  change_preset(pl6NR);

  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //Waveform
        for (int v = 0; v < 4; v++) {
          SINE_MOD_ratio(pl6NR, pl6MOD_OSC[v], 0, 0, 0, MAX_RATIOS, "Ratio");
          SINE_MOD_amplitude(pl6NR, pl6MOD_OSC[v], 1, 0, 0, SUSTAIN_LVL, "LVL");
          SINE_MOD_ratio(pl6NR, pl6MOD2_OSC[v], 2, 0, 0, MAX_RATIOS, "Ratio");
          SINE_MOD_amplitude(pl6NR, pl6MOD2_OSC[v], 3, 0, 0, SUSTAIN_LVL, "LVL");
        }

        break;
      case 1:
        for (int v = 0; v < 4; v++) {
          ENV_ADSR(pl6NR, pl6MOD_ENV[v], 0, 1, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
        }
        break;
      case 2:
        for (int v = 0; v < 4; v++) {
          ENV_ADSR(pl6NR, pl6MOD2_ENV[v], 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
        }
        break;
      case 3:
        for (int v = 0; v < 4; v++) {
          ENV_ADSR(pl6NR, pl6CAR_ENV[v], 0, 3, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
        }
        break;
    }
  }

  if (ts.touched() || button[15]) {
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin6", 5);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin6", 5);
      }
    }
  }
}
void Plugin6_Page_Static() {
  clearWorkSpace();
  Plugin6_Change();
  drawNrInRect(18, 1, plpreset[pl6NR], ILI9341_PURPLE);
  //case 0
  //Waveform
  for (int v = 0; v < 4; v++) {
    draw_SINE_MOD_ratio(pl6NR, pl6MOD_OSC[v], 0, 0, 0, MAX_RATIOS, "Ratio");
    draw_SINE_MOD_amplitude(pl6NR, pl6MOD_OSC[v], 1, 0, 0, SUSTAIN_LVL, "LVL");
    draw_SINE_MOD_ratio(pl6NR, pl6MOD2_OSC[v], 2, 0, 0, MAX_RATIOS, "Ratio");
    draw_SINE_MOD_amplitude(pl6NR, pl6MOD2_OSC[v], 3, 0, 0, SUSTAIN_LVL, "LVL");
    draw_ENV_ADSR(pl6NR, pl6MOD_ENV[v], 0, 1, ATTACK_TIME, RELEASE_TIME, "");   //MIN: Attack/Decaytime MAX: Releasetime
    draw_ENV_ADSR(pl6NR, pl6MOD2_ENV[v], 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
    draw_ENV_ADSR(pl6NR, pl6CAR_ENV[v], 0, 3, ATTACK_TIME, RELEASE_TIME, "");   //MIN: Attack/Decaytime MAX: Releasetime
  }
}
void Plugin6_Change() {
  for (int v = 0; v < 4; v++) {
    change_SINE_MOD_ratio(pl6NR, pl6MOD_OSC[v], 0, 0, 0, MAX_RATIOS, "Ratio");
    change_SINE_MOD_amplitude(pl6NR, pl6MOD_OSC[v], 1, 0, 0, SUSTAIN_LVL, "LVL");
    change_SINE_MOD_ratio(pl6NR, pl6MOD2_OSC[v], 2, 0, 0, MAX_RATIOS, "Ratio");
    change_SINE_MOD_amplitude(pl6NR, pl6MOD2_OSC[v], 3, 0, 0, SUSTAIN_LVL, "LVL");
    change_ENV_ADSR(pl6NR, pl6MOD_ENV[v], 0, 1, ATTACK_TIME, RELEASE_TIME, "");   //MIN: Attack/Decaytime MAX: Releasetime
    change_ENV_ADSR(pl6NR, pl6MOD2_ENV[v], 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
    change_ENV_ADSR(pl6NR, pl6CAR_ENV[v], 0, 3, ATTACK_TIME, RELEASE_TIME, "");   //MIN: Attack/Decaytime MAX: Releasetime
  }
}
