//Lets create a plugin
//1) we copy the automatic generated code from the "15stepTeensyDAW3.ino" and import it to https://www.pjrc.com/teensy/gui/
//   All created plugins are in here.
//2) for this tutorial we add followinig modules from the left side:
// WAVEFORM
// FILTER
// DC
// ENVELOPE

//for a better view add "pl" "number" to each module. double-click on it to change its  name.
//connect the modules together, where DC goes to input "1" of the filter, you could also connect an envelope to this input
//if needed add a mixer to the chain

// 3) export (Copy-paste) the automatic generated code to the "15stepTeensyDAW3.ino". delete the librarys that come with the code

// 4) now we add a function with the plugin settings for the setup routine and one for the "mainscreen" if we call the plugin
// lets call it Plugin_3_Settings()
// and
// Plugin3_Page1_Dynamic()
// here we define the initial values for our modules, like OSC Waveform, Frequency, level, Filters freq and resonance,.....
// (Look on https://www.pjrc.com/teensy/gui/ @ each module what can be controlled)
// add the settings-function in the setup function in "15stepTeensyDAW3.ino"
// We can leave Plugin3_Page1_Dynamic() {} empty for now.

// 5) head over to variables  and look for the ********************************************************

// you´ve come a long way, your last edited file should be midi.ino.
//Now its time to:
//11) add your controls
//to make live a bit easier the display and touchscreen is sectioned into grids of  16pixels height and width
// to call a position best way is to ask if gridTouchX or/and gridTouchY is in certain area like
//if (gridTouchX == 10 && gridTouchY == 5)

// to draw something the STEP_FRAME_W and STEP_FRAME_H come handy. use a multiplier and an offset to get to your desired position, like:
//tft.drawPixel(STEP_FRAME_W * 3 + 2, STEP_FRAME_H * 5 - 3, int colour);

// some value showing functions are implemented. Just call
//drawbarH(XPos, YPos, value_rnd, Name, int color)  //gridPosX, gridPosY, value 0-100, valuename, backgroundcolor of bargraph
//or
//drawbarV(XPos, YPos, value_rnd, Name, int color) //gridPosX, gridPosY, value 0-100, valuename, backgroundcolor of bargraph
//or
//void drawPot(xPos, yPos, fvalue, dvalue, dname, color) { //xposition, yposition, value 0-100, value to draw, name to draw, color of circle

//to change pages always use this function, it sets other pages-states to low
//for (byte others = 0; others <= MAX_PAGES; others++) {
//selectPage[others] = LOW;
//}
//selectPage["your-pageNr-here"] = HIGH;

void Plugin_3_Settings() {
  pl3waveform1.begin(WAVEFORM_SAWTOOTH);
  pl3waveform1.amplitude(1);
  pl3waveform1.frequency(note_frequency[36]);
  pl3waveform1.pulseWidth(0.15);

  pl3filter1.frequency(pl3Filter1_Frequency);
  pl3filter1.resonance(pl3Filter1_Resonance);
  pl3filter1.octaveControl(pl3Filter1_Sweep);

  pl3envelope1.delay(0);
  pl3envelope1.attack(pl3Env1_Attack);
  pl3envelope1.hold(0);
  pl3envelope1.decay(500);
  pl3envelope1.sustain(0.8);
  pl3envelope1.release(pl3Env1_Release);

  pl3dc1.amplitude(1);

  pl3envelope2.delay(0);
  pl3envelope2.attack(pl3Env1_Attack);
  pl3envelope2.hold(0);
  pl3envelope2.decay(500);
  pl3envelope2.sustain(0.8);
  pl3envelope2.release(pl3Env1_Release);
}
void Plugin3_Page1_Dynamic() {
  if (ts.touched()) {


    if (gridTouchY == 3) {

      //Waveform
      if (gridTouchX == 3 || gridTouchX == 4) {
        pl3wfSelect = map(Potentiometer1, 0, 1023, 0, 12);
        pl3wfSelect_graph = map(Potentiometer1, 0, 1023, 0, 100);
        pl3waveform1.begin(pl3wfSelect);
        drawPot(3, 3, pl3wfSelect_graph, pl3wfSelect, "WForm", ILI9341_BLUE);
      }
      //Volume
      if (gridTouchX == 15 || gridTouchX == 16) {
        pl3Volume_graph = map(Potentiometer1, 0, 1023, 0, 100);
        pl3Volume = pl3Volume_graph / 100.00;
        mixer5.gain(2, pl3Volume);
        drawPot(15, 3, pl3Volume_graph, pl3Volume_graph, "MIX", ILI9341_RED);
      }
    }

    if (gridTouchY == 7) {

      //Filter Frequency
      if (gridTouchX == 3 || gridTouchX == 4) {
        pl3Filter1_Frequency = map(Potentiometer1, 0, 1023, 40, 5900.00);
        pl3Filter1_Frequency_graph = map(Potentiometer1, 0, 1023, 0, 100);
        pl3filter1.frequency(pl3Filter1_Frequency);
        drawPot(3, 7, pl3Filter1_Frequency_graph, pl3Filter1_Frequency, "Freq", ILI9341_BLUE);
      }
      //Resonance
      if (gridTouchX == 7 || gridTouchX == 8) {
        pl3Filter1_Resonance_rnd = map(Potentiometer1, 0, 1023, 70, 500.00);
        pl3Filter1_Resonance = pl3Filter1_Resonance_rnd / 100.00;
        pl3Filter1_Resonance_graph = map(Potentiometer1, 0, 1023, 0, 100);
        pl3filter1.resonance(pl3Filter1_Resonance);
        drawPot(7, 7, pl3Filter1_Resonance_graph, pl3Filter1_Resonance_graph, "Reso", ILI9341_BLUE);
      }
      //Sweep
      if (gridTouchX == 11 || gridTouchX == 12) {
        pl3Filter1_Sweep_rnd = map(Potentiometer1, 0, 1023, 0, 700);
        pl3Filter1_Sweep_graph = map(Potentiometer1, 0, 1023, 0, 100);
        pl3Filter1_Sweep = pl3Filter1_Sweep_rnd / 100.00;
        pl3filter1.octaveControl(pl3Filter1_Sweep);
        drawPot(11, 7, pl3Filter1_Sweep_graph, pl3Filter1_Sweep_graph, "Swp", ILI9341_BLUE);
      }
    }

    if (gridTouchY == 11) {

      //Attack
      if (gridTouchX == 3 || gridTouchX == 4) {
        pl3Env1_Attack = map(Potentiometer1, 0, 1023, 10, 700);
        pl3Env1_Attack_graph = map(Potentiometer1, 0, 1023, 0, 100);
        pl3envelope1.attack(pl3Env1_Attack);
        pl3envelope2.attack(pl3Env1_Attack);
        drawPot(3, 11, pl3Env1_Attack_graph, pl3Env1_Attack, "Atck", ILI9341_BLUE);
      }
      //Decay
      if (gridTouchX == 7 || gridTouchX == 8) {
        pl3Env1_Decay = map(Potentiometer1, 0, 1023, 10, 700);
        pl3Env1_Decay_graph = map(Potentiometer1, 0, 1023, 0, 100.00);
        pl3envelope1.decay(pl3Env1_Decay);
        pl3envelope2.decay(pl3Env1_Decay);
        drawPot(7, 11, pl3Env1_Decay_graph, pl3Env1_Decay, "Dec", ILI9341_BLUE);
      }
      //Sustain
      if (gridTouchX == 11 || gridTouchX == 12) {
        pl3Env1_Sustain_graph = map(Potentiometer1, 0, 1023, 0, 100.00);
        pl3Env1_Sustain = pl3Env1_Sustain_graph / 100.00;
        pl3envelope1.sustain(pl3Env1_Sustain);
        pl3envelope2.sustain(pl3Env1_Sustain);
        drawPot(11, 11, pl3Env1_Sustain_graph, pl3Env1_Sustain_graph, "Sus", ILI9341_BLUE);
      }
      //Release
      if (gridTouchX == 15 || gridTouchX == 16) {
        pl3Env1_Release = map(Potentiometer1, 0, 1023, 180, 1200);
        pl3Env1_Release_graph = map(Potentiometer1, 0, 1023, 0, 100.00);
        pl3envelope1.release(pl3Env1_Release);
        pl3envelope2.release(pl3Env1_Release);
        drawPot(15, 11, pl3Env1_Release_graph, pl3Env1_Release, "Rel", ILI9341_BLUE);
      }
    }
  }
}