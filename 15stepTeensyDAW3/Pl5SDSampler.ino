void Plugin_5_Settings() {


  pl5filter1.frequency(pl5Filter1_Frequency);
  pl5filter1.resonance(pl5Filter1_Resonance);
  pl5filter1.octaveControl(pl5Filter1_Sweep);

  pl5envelope1.delay(0);
  pl5envelope1.attack(pl5Env1_Attack);
  pl5envelope1.hold(0);
  pl5envelope1.decay(500);
  pl5envelope1.sustain(0.8);
  pl5envelope1.release(pl5Env1_Release);

  pl5dc1.amplitude(1);

  pl5envelope2.delay(0);
  pl5envelope2.attack(pl5Env1_Attack);
  pl5envelope2.hold(0);
  pl5envelope2.decay(500);
  pl5envelope2.sustain(0.8);
  pl5envelope2.release(pl5Env1_Release);
}


void Plugin5_Page_Static(byte Pagenumber) {
  //draw selecting pages buttons
  //draw_sub_page_buttons(2);
  drawPot(3, 3, selected_file_graph, selected_file, "WAV", ILI9341_PURPLE);
  drawPot(15, 3, plugin[5].Volume_graph, plugin[5].Volume_graph, "MIX", ILI9341_RED);

  drawPot(3, 7, pl5Filter1_Frequency_graph, pl5Filter1_Frequency, "Frq", ILI9341_BLUE);
  drawPot(7, 7, pl5Filter1_Resonance_graph, pl5Filter1_Resonance_graph, "Res", ILI9341_BLUE);
  drawPot(11, 7, pl5Filter1_Sweep_graph, pl5Filter1_Sweep_graph, "Swp", ILI9341_BLUE);

  drawPot(3, 11, pl5Env1_Attack_graph, pl5Env1_Attack, "Att", ILI9341_BLUE);
  drawPot(7, 11, pl5Env1_Decay_graph, pl5Env1_Decay, "Dec", ILI9341_BLUE);
  drawPot(11, 11, pl5Env1_Sustain_graph, pl5Env1_Sustain_graph, "Sus", ILI9341_BLUE);
  drawPot(15, 11, pl5Env1_Release_graph, pl5Env1_Release, "Rel", ILI9341_BLUE);
}
void Plugin5_Page1_Dynamic() {
  if (ts.touched() || !buttons[6].read()) {
    if (gridTouchY == 3) {

      //WAV select
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, 3, selected_file_graph, selected_file, "WAV", ILI9341_PURPLE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - selected_file_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          selected_file = map(Potentiometer1, 0, 1023, 0, MAX_WAV_FILES);
          selected_file_graph = map(Potentiometer1, 0, 1023, 0, 100);
        }
      }
      //Volume
      if (gridTouchX == 15 || gridTouchX == 16) {
        drawPot(15, 3, plugin[5].Volume_graph, plugin[5].Volume_graph, "MIX", ILI9341_RED);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - plugin[5].Volume) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          plugin[5].Volume_graph = map(Potentiometer1, 0, 1023, 0, 100);
          plugin[5].Volume = plugin[5].Volume_graph / 100.00;
          mixer6.gain(0, plugin[5].Volume);
        }
      }
    }
    if (gridTouchY == 7) {

      //Filter Frequency
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, 7, pl5Filter1_Frequency_graph, pl5Filter1_Frequency, "Frq", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl5Filter1_Frequency_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5Filter1_Frequency = map(Potentiometer1, 0, 1023, 40, 5900.00);
          pl5Filter1_Frequency_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl5filter1.frequency(pl5Filter1_Frequency);
        }
      }
      //Resonance
      if (gridTouchX == 7 || gridTouchX == 8) {
        drawPot(7, 7, pl5Filter1_Resonance_graph, pl5Filter1_Resonance_graph, "Res", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl5Filter1_Resonance_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5Filter1_Resonance_rnd = map(Potentiometer1, 0, 1023, 70, 500.00);
          pl5Filter1_Resonance = pl5Filter1_Resonance_rnd / 100.00;
          pl5Filter1_Resonance_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl5filter1.resonance(pl5Filter1_Resonance);
        }
      }
      //Sweep
      if (gridTouchX == 11 || gridTouchX == 12) {
        drawPot(11, 7, pl5Filter1_Sweep_graph, pl5Filter1_Sweep_graph, "Swp", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl5Filter1_Sweep_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5Filter1_Sweep_rnd = map(Potentiometer1, 0, 1023, 0, 700);
          pl5Filter1_Sweep_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl5Filter1_Sweep = pl5Filter1_Sweep_rnd / 100.00;
          pl5filter1.octaveControl(pl5Filter1_Sweep);
        }
      }
    }
    if (gridTouchY == 11) {

      //Attack
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, 11, pl5Env1_Attack_graph, pl5Env1_Attack, "Att", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl5Env1_Attack_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5Env1_Attack = map(Potentiometer1, 0, 1023, 10, 700);
          pl5Env1_Attack_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl5envelope1.attack(pl5Env1_Attack);
          pl5envelope2.attack(pl5Env1_Attack);
        }
      }
      //Decay
      if (gridTouchX == 7 || gridTouchX == 8) {
        drawPot(7, 11, pl5Env1_Decay_graph, pl5Env1_Decay, "Dec", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl5Env1_Decay_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5Env1_Decay = map(Potentiometer1, 0, 1023, 10, 700);
          pl5Env1_Decay_graph = map(Potentiometer1, 0, 1023, 0, 100.00);
          pl5envelope1.decay(pl5Env1_Decay);
          pl5envelope2.decay(pl5Env1_Decay);
        }
      }
      //Sustain
      if (gridTouchX == 11 || gridTouchX == 12) {
        drawPot(11, 11, pl5Env1_Sustain_graph, pl5Env1_Sustain_graph, "Sus", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl5Env1_Sustain_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5Env1_Sustain_graph = map(Potentiometer1, 0, 1023, 0, 100.00);
          pl5Env1_Sustain = pl5Env1_Sustain_graph / 100.00;
          pl5envelope1.sustain(pl5Env1_Sustain);
          pl5envelope2.sustain(pl5Env1_Sustain);
        }
      }
      //Release
      if (gridTouchX == 15 || gridTouchX == 16) {
        drawPot(15, 11, pl5Env1_Release_graph, pl5Env1_Release, "Rel", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl5Env1_Release_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl5Env1_Release = map(Potentiometer1, 0, 1023, 180, 1200);
          pl5Env1_Release_graph = map(Potentiometer1, 0, 1023, 0, 100.00);
          pl5envelope1.release(pl5Env1_Release);
          pl5envelope2.release(pl5Env1_Release);
        }
      }
    }
  }
}