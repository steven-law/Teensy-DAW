//Lets create a plugin
//1) we copy the automatic generated code from the "15stepTeensyDAW3.ino" and import it to https://www.pjrc.com/teensy/gui/
//   All created plugins are in here.
//2) for this tutorial we add followinig modules from the left side:
// WAVEFORM
// FILTER
// DC
// ENVELOPE

//for a better view add "pl" "number" to each module. double-click on it to change its  name.
//connect the modules together, where DC goes to input of the  envelope2 for the filter
//if needed add a mixer to the chain

// 3) export (Copy-paste) the automatic generated code to the "15stepTeensyDAW3.ino". delete the librarys that come with the code

// 4) now we add a function with the plugin settings for the setup routine
// lets call it Plugin_3_Settings()
// and
// one for the "mainscreen" if we call the plugin
// Plugin3_Page1_Dynamic()

// In Plugin_3_Settings() we define the initial values for our modules, like OSC Waveform, Frequency, level, Filters freq and resonance,.....
// (Look on https://www.pjrc.com/teensy/gui/ @ each module what can be controlled)
// add the settings-function "Plugin_3_Settings();" to the setup() function in "15stepTeensyDAW3.ino"
// look for
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Plugin3_Page1_Dynamic() is only to show the controls of each pluginpage right after you hit the pluginbutton. Else you had to tap on every control to be shown
// Plugin3_Page1_Dynamic() is for all the dynamic stuff like what controls do we see and change,
// there are several functions aviable to draw the value of the parameters
// We can leave Plugin3_Page1_Dynamic() {} empty for now.

// 5) head over to variables.h  and look for the ********************************************************

// you´ve come a long way, your last edited file should be midi.ino.
//Now its time to:
//11) add your controls:
//to make live a bit easier the display and touchscreen is sectioned into grids of  16pixels height and width
// to call a position best way is to ask if gridTouchX or/and gridTouchY is in certain area like
//if (gridTouchX == 10 && gridTouchY == 5)

// to draw something the STEP_FRAME_W and STEP_FRAME_H come handy. use a multiplier and an offset to get to your desired position, like:
//tft.drawPixel(STEP_FRAME_W * 3 + 2, STEP_FRAME_H * 5 - 3, int colour);


// to clear the workspace (Grid, Pluginview or songmode)
//this sets all pixels(ex. startupscreen + coordinates) to darkgrey
//clearWorkSpace();


// some value showing functions are implemented. Just call
//drawbarH(XPos, YPos, value_rnd, Name, int color)  //gridPosX, gridPosY, value 0-100, valuename, backgroundcolor of bargraph
//or
//drawbarV(XPos, YPos, value_rnd, Name, int color) //gridPosX, gridPosY, value 0-100, valuename, backgroundcolor of bargraph
//or
//void drawPot(xPos, yPos, fvalue, dvalue, dname, color) { //xposition, yposition, value 0-100, value to draw, name to draw, color of circle
//or
//void drawPotLine(xPos, yPos, fvalue, dvalue, dname, color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color
//to change pages always use this function, it sets other pages-states to low
//
//selectPage["your-pageNr-here"];



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
  pl3amp.gain(1);
}

//Plugin3_Page_Static(n) to show your control values

void Plugin3_Page_Static(byte Pagenumber, byte desired_instrument) {
  //draw selecting pages buttons
  //draw_sub_page_buttons(2);
  if (Pagenumber == 0) {
    drawPot(3, 3, pl3wfSelect_graph, pl3wfSelect, "WForm", trackColor[desired_track]);
    drawPot(15, 3, plugin[3].Volume_graph, plugin[3].Volume_graph, "MIX", trackColor[desired_track]);

    drawPot(3, 7, pl3Filter1_Frequency_graph, pl3Filter1_Frequency, "Freq", trackColor[desired_track]);
    drawPot(7, 7, pl3Filter1_Resonance_graph, pl3Filter1_Resonance_graph, "Reso", trackColor[desired_track]);
    drawPot(11, 7, pl3Filter1_Sweep_graph, pl3Filter1_Sweep_graph, "Swp", trackColor[desired_track]);

    drawPot(3, 11, pl3Env1_Attack_graph, pl3Env1_Attack, "Atck", trackColor[desired_track]);
    drawPot(7, 11, pl3Env1_Decay_graph, pl3Env1_Decay, "Dec", trackColor[desired_track]);
    drawPot(11, 11, pl3Env1_Sustain_graph, pl3Env1_Sustain_graph, "Sus", trackColor[desired_track]);
    drawPot(15, 11, pl3Env1_Release_graph, pl3Env1_Release, "Rel", trackColor[desired_track]);
  }
}

void Plugin3_Page1_Dynamic(byte desired_instrument) {



  if (ts.touched() || !buttons[6].read()) {
    if (gridTouchY == 3) {

      //Waveform
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, 3, pl3wfSelect_graph, pl3wfSelect, "WForm", trackColor[desired_track]);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl3wfSelect_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl3wfSelect = map(Potentiometer1, 0, 1023, 0, 12);
          pl3wfSelect_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl3waveform1.begin(pl3wfSelect);
        }
      }
      //Volume
      if (gridTouchX == 15 || gridTouchX == 16) {
        drawPot(15, 3, plugin[3].Volume_graph, plugin[3].Volume_graph, "MIX", trackColor[desired_track]);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - plugin[3].Volume_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          plugin[3].Volume_graph = map(Potentiometer1, 0, 1023, 0, 100);
          plugin[3].Volume = plugin[3].Volume_graph / 100.00;
          mixer5.gain(2, plugin[3].Volume);
        }
      }
    }

    if (gridTouchY == 7) {

      //Filter Frequency
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, 7, pl3Filter1_Frequency_graph, pl3Filter1_Frequency, "Frq", trackColor[desired_track]);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl3Filter1_Frequency_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl3Filter1_Frequency = map(Potentiometer1, 0, 1023, 40, 5900.00);
          pl3Filter1_Frequency_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl3filter1.frequency(pl3Filter1_Frequency);
        }
      }
      //Resonance
      if (gridTouchX == 7 || gridTouchX == 8) {
        drawPot(7, 7, pl3Filter1_Resonance_graph, pl3Filter1_Resonance_graph, "Res", trackColor[desired_track]);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl3Filter1_Resonance_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl3Filter1_Resonance_rnd = map(Potentiometer1, 0, 1023, 70, 500.00);
          pl3Filter1_Resonance = pl3Filter1_Resonance_rnd / 100.00;
          pl3Filter1_Resonance_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl3filter1.resonance(pl3Filter1_Resonance);
        }
      }
      //Sweep
      if (gridTouchX == 11 || gridTouchX == 12) {
        drawPot(11, 7, pl3Filter1_Sweep_graph, pl3Filter1_Sweep_graph, "Swp", trackColor[desired_track]);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl3Filter1_Sweep_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl3Filter1_Sweep_rnd = map(Potentiometer1, 0, 1023, 0, 700);
          pl3Filter1_Sweep_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl3Filter1_Sweep = pl3Filter1_Sweep_rnd / 100.00;
          pl3filter1.octaveControl(pl3Filter1_Sweep);
        }
      }
    }

    if (gridTouchY == 11) {

      //Attack
      if (gridTouchX == 3 || gridTouchX == 4) {
        drawPot(3, 11, pl3Env1_Attack_graph, pl3Env1_Attack, "Att", trackColor[desired_track]);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl3Env1_Attack_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl3Env1_Attack = map(Potentiometer1, 0, 1023, 10, 700);
          pl3Env1_Attack_graph = map(Potentiometer1, 0, 1023, 0, 100);
          pl3envelope1.attack(pl3Env1_Attack);
          pl3envelope2.attack(pl3Env1_Attack);
        }
      }
      //Decay
      if (gridTouchX == 7 || gridTouchX == 8) {
        drawPot(7, 11, pl3Env1_Decay_graph, pl3Env1_Decay, "Dec", trackColor[desired_track]);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl3Env1_Decay_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl3Env1_Decay = map(Potentiometer1, 0, 1023, 10, 700);
          pl3Env1_Decay_graph = map(Potentiometer1, 0, 1023, 0, 100.00);
          pl3envelope1.decay(pl3Env1_Decay);
          pl3envelope2.decay(pl3Env1_Decay);
        }
      }
      //Sustain
      if (gridTouchX == 11 || gridTouchX == 12) {
        drawPot(11, 11, pl3Env1_Sustain_graph, pl3Env1_Sustain_graph, "Sus", trackColor[desired_track]);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl3Env1_Sustain_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl3Env1_Sustain_graph = map(Potentiometer1, 0, 1023, 0, 100.00);
          pl3Env1_Sustain = pl3Env1_Sustain_graph / 100.00;
          pl3envelope1.sustain(pl3Env1_Sustain);
          pl3envelope2.sustain(pl3Env1_Sustain);
        }
      }
      //Release
      if (gridTouchX == 15 || gridTouchX == 16) {
        drawPot(15, 11, pl3Env1_Release_graph, pl3Env1_Release, "Rel", trackColor[desired_track]);
        if ((abs(map(Potentiometer1, 0, 1023, 0, 100) - pl3Env1_Release_graph) < POTPICKUP)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          pl3Env1_Release = map(Potentiometer1, 0, 1023, 180, 1200);
          pl3Env1_Release_graph = map(Potentiometer1, 0, 1023, 0, 100.00);
          pl3envelope1.release(pl3Env1_Release);
          pl3envelope2.release(pl3Env1_Release);
        }
      }
    }
  }
}