void Plugin_6_Settings() {


  pl6filter1.frequency(pl6Filter1_Frequency);
  pl6filter1.resonance(pl6Filter1_Resonance);
  pl6filter1.octaveControl(pl6Filter1_Sweep);

  pl6envelope1.delay(0);
  pl6envelope1.attack(pl6Env1_Attack);
  pl6envelope1.hold(0);
  pl6envelope1.decay(500);
  pl6envelope1.sustain(0.8);
  pl6envelope1.release(pl6Env1_Release);

  pl6dc1.amplitude(1);

  pl6envelope2.delay(0);
  pl6envelope2.attack(pl6Env1_Attack);
  pl6envelope2.hold(0);
  pl6envelope2.decay(500);
  pl6envelope2.sustain(0.8);
  pl6envelope2.release(pl6Env1_Release);
}

void Plugin6_Page_Static(byte Pagenumber) {
    //draw selecting pages buttons
  //draw_sub_page_buttons(2);
  drawPotLine(3, 3, selected_file_raw_graph, selected_raw_file, "RAW", ILI9341_BLACK);
  drawPot(15, 3, plugin[6].Volume_graph, plugin[6].Volume_graph, "MIX", ILI9341_RED);

  drawPot(3, 7, pl6Filter1_Frequency_graph, pl6Filter1_Frequency, "Freq", ILI9341_BLUE);
  drawPot(7, 7, pl6Filter1_Resonance_graph, pl6Filter1_Resonance_graph, "Reso", ILI9341_BLUE);
  drawPot(11, 7, pl6Filter1_Sweep_graph, pl6Filter1_Sweep_graph, "Swp", ILI9341_BLUE);

  drawPot(3, 11, pl6Env1_Attack_graph, pl6Env1_Attack, "Atck", ILI9341_BLUE);
  drawPot(7, 11, pl6Env1_Decay_graph, pl6Env1_Decay, "Dec", ILI9341_BLUE);
  drawPot(11, 11, pl6Env1_Sustain_graph, pl6Env1_Sustain_graph, "Sus", ILI9341_BLUE);
  drawPot(15, 11, pl6Env1_Release_graph, pl6Env1_Release, "Rel", ILI9341_BLUE);
 
}
void Plugin6_Page1_Dynamic() {



  if (ts.touched() || !buttons[6].read()) {

    if (gridTouchY == 3) {

      //RAW select
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPotLine(3, 3, selected_file_raw_graph, selected_raw_file, "RAW", ILI9341_BLACK);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - selected_file_raw_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          selected_raw_file = map(Potentiometer1, 0, 1023, 0, MAX_RAW_FILES);
          selected_file_raw_graph = map(Potentiometer1, 0, 1023, 0, 100);
        }
      }

      //Volume
      if (gridTouchX == 15 || gridTouchX == 16) {
        drawPot(15, 3, plugin[6].Volume_graph, plugin[6].Volume_graph, "MIX", ILI9341_RED);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - plugin[6].Volume_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          plugin[6].Volume_graph = map(Potentiometer1, 0, 1023, 0, 100);
          plugin[6].Volume_rnd = map(Potentiometer1, 0, 1023, 0, 500.00);
          plugin[6].Volume = plugin[6].Volume_rnd / 100.00;
          mixer6.gain(1, plugin[6].Volume);
        }
      }
    }
    if (gridTouchY == 7) {

      //Filter Frequency
      if (gridTouchX == 3 || gridTouchX == 4) {
        pl6filter1.frequency(pl6Filter1_Frequency);
        drawPot(3, 7, pl6Filter1_Frequency_graph, pl6Filter1_Frequency, "Freq", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl6Filter1_Frequency_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl6Filter1_Frequency = map(Potentiometer1, 0, 1023, 40, 5900.00);
          pl6Filter1_Frequency_graph = map(Potentiometer1, 0, 1023, 0, 100);
        }
      }
      //Resonance
      if (gridTouchX == 7 || gridTouchX == 8) {
        pl6filter1.resonance(pl6Filter1_Resonance);
        drawPot(7, 7, pl6Filter1_Resonance_graph, pl6Filter1_Resonance_graph, "Reso", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl6Filter1_Resonance_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl6Filter1_Resonance_rnd = map(Potentiometer1, 0, 1023, 70, 500.00);
          pl6Filter1_Resonance = pl6Filter1_Resonance_rnd / 100.00;
          pl6Filter1_Resonance_graph = map(Potentiometer1, 0, 1023, 0, 100);
        }
      }
      //Sweep
      if (gridTouchX == 11 || gridTouchX == 12) {
        pl6filter1.octaveControl(pl6Filter1_Sweep);
        drawPot(11, 7, pl6Filter1_Sweep_graph, pl6Filter1_Sweep_graph, "Swp", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl6Filter1_Sweep_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl6Filter1_Sweep_rnd = map(Potentiometer1, 0, 1023, 0, 700);
          pl6Filter1_Sweep_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl6Filter1_Sweep = pl6Filter1_Sweep_rnd / 100.00;
        }
      }
    }
    if (gridTouchY == 11) {

      //Attack
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, 11, pl6Env1_Attack_graph, pl6Env1_Attack, "Atck", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl6Env1_Attack_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl6Env1_Attack = map(Potentiometer1, 0, 1023, 10, 700);
          pl6Env1_Attack_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl6envelope1.attack(pl6Env1_Attack);
          pl6envelope2.attack(pl6Env1_Attack);
        }
      }
      //Decay
      if (gridTouchX == 7 || gridTouchX == 8) {
        drawPot(7, 11, pl6Env1_Decay_graph, pl6Env1_Decay, "Dec", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl6Env1_Decay_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl6Env1_Decay = map(Potentiometer1, 0, 1023, 10, 700);
          pl6Env1_Decay_graph = map(Potentiometer1, 0, 1023, 0, 100.00);
          pl6envelope1.decay(pl6Env1_Decay);
          pl6envelope2.decay(pl6Env1_Decay);
        }
      }
      //Sustain
      if (gridTouchX == 11 || gridTouchX == 12) {
        drawPot(11, 11, pl6Env1_Sustain_graph, pl6Env1_Sustain_graph, "Sus", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl6Env1_Sustain_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl6Env1_Sustain_graph = map(Potentiometer1, 0, 1023, 0, 100.00);
          pl6Env1_Sustain = pl6Env1_Sustain_graph / 100.00;
          pl6envelope1.sustain(pl6Env1_Sustain);
          pl6envelope2.sustain(pl6Env1_Sustain);
        }
      }
      //Release
      if (gridTouchX == 15 || gridTouchX == 16) {
        drawPot(15, 11, pl6Env1_Release_graph, pl6Env1_Release, "Rel", ILI9341_BLUE);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl6Env1_Release_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl6Env1_Release = map(Potentiometer1, 0, 1023, 180, 1200);
          pl6Env1_Release_graph = map(Potentiometer1, 0, 1023, 0, 100.00);
          pl6envelope1.release(pl6Env1_Release);
          pl6envelope2.release(pl6Env1_Release);
        }
      }
    }
  }
}