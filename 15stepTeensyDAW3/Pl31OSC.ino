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

// a bar graph function is implemented. Just call
//drawbarH(XPos, YPos, value_rnd, Name, int color)  //gridPosX, gridPosY, value 0-100, valuename, backgroundcolor of bargraph
//or
//drawbarV(XPos, YPos, value_rnd, Name, int color) //gridPosX, gridPosY, value 0-100, valuename, backgroundcolor of bargraph

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
void Plugin3_Page1_Dynamic() {}