//Lets create a plugin
// these are the neccessary elements you have to do to add your own plugin:
// 1) copy the existing automatic generated code from "15stepTeensyDAW3.ino" and import it to https://newdigate.github.io/teensy-eurorack-audio-gui/
//    add your modules for the plugin. Dont forget to add your final AMP modules for the Mixer and volume section; copy the code back to "15stepTeensyDAW3.ino"

// 2) add the plugin- _settings, _Static and _Dynamic functions to your plugin *.ino file add the functions to:
//    Plugin_3_Settings()      -> setup() function in "15stepTeensyDAW3.ino" -> this should be already done until we reached the limit oftemplated plugins
//    Plugin3_Page1_Static()   -> Plugin_View_Static() function in "functions.ino" -> this should be already done until we reached the limit oftemplated plugins
//    Plugin3_Page1_Dynamic()  -> Plugin_View_Dynamic() function in "functions.ino" -> this should be already done until we reached the limit oftemplated plugins
//    Plugin3_Control()

// 3) define PLUGINx_PAGEnr and variables to "variables.h"

// 4) add different tasks to the functions in "functions.ino"

// 6) add controls to Plugin3_Page1_Dynamic()      !! it´s easier to start here after point 3 and then distribute the lines over the desired functions

// 7) add your amp.gain() control to the volume-functions in "functions.ino"  -> this should be already done until we reached the limit oftemplated plugins

//Lets start:
//1) we copy the automatic generated code from the "15stepTeensyDAW3.ino" and import it to https://newdigate.github.io/teensy-eurorack-audio-gui/
//   All created plugins are in here.

// for this tutorial we add followinig modules from the left sidebar:
// WAVEFORM
// FILTER
// DC
// ENVELOPE
// AMP

// rename the modules to your likenings, we will put all variables into a struct for a better view, handling and preset storage. double-click on it to change its name.
// its recommended to name the variables like: "module-function" fe.: pl3filter1
// connect the modules together, where DC goes to input of the  envelope2 for the filter
// AMP2 will be used to control the volume of our mixer.
// AMP2  will be used to control the volume while the arrangment is playing
// if needed add a mixer to the chain.

// export (Copy-paste) the new automatic generated code to the "15stepTeensyDAW3.ino". delete the librarys that come with the code

// 2) Add a new *.ino file for your plugin and add following functions to your file:
// Plugin_3_Settings()     -> here are all modules and their initial values stored
//                            like OSC Waveform, Frequency, level, Filters freq and resonance,.....

// Plugin3_Page1_Static(pageNumber)   -> if we open a pluginpage or change presets, we want to see the actual values, graphs and other icons immediatly
//                                       add this function to Plugin_View_Static(int desired_instrument){} in functions.ino
//                                       desired_instrument can be used for your plugin, for corresponding track color

// Plugin3_Page1_Dynamic()   -> this is where we assign values to our variables, that will handle our module-functions
//                              (Look on https://www.pjrc.com/teensy/gui/ for each module, what can be controlled)
//                              here happens all the touch, button and encoder input for the plugin.
//                              you can have several pages for your plugin
//                              there are several functions aviable to draw the value of the parameters
//                              We can leave Plugin3_Page1_Dynamic() {} empty for now. (as i made templates you can go and make your dynamic
//                                                                                      plugin page with all your controls
//                                                                                      and distribute them afterwards to the desired functions)



///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////   add the settings-function "Plugin_3_Settings();" setup() function in "functions.ino"  //////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////   add the Plugin3_Page1_Static()-function to the Plugin_View_Static(x) function in "functions.ino"     //////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////   add the Plugin3_Page1_Dynamic()-function to the loop() function in "functions.ino"     //////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//kkjgjjvhhlkkjgggllhkkllk

// 3) head over to variables.h  and look for the ********************************************************

// you´ve come a long way, your last edited file should be functions.ino.
// Now its time to:
// 6) add your controls:
//    the controls are mostly changed by the onboard encoders, the encoders are set to send a +1 or -1 per step, you than can add or subtract that 1 from your "old value"
//    via "mapping" you get your *_graph-value going from 0-127 to your desired range

//    to make live a bit easier the display and touchscreen is sectioned into grids of  16pixels height and width
//    to set a position best way is to work with gridTouchX or/and gridTouchY for a certain point

//    to draw something the STEP_FRAME_W and STEP_FRAME_H come handy. use a multiplier and an offset to get to your desired position, like:
//    tft.drawPixel(STEP_FRAME_W * 3 + 2, STEP_FRAME_H * 5 - 3, int colour);
//    where 3 is gridTouchX (or 3*16pixel +2 in x direction)

//    to clear the workspace (Grid, Pluginview or songmode)
//    this sets all pixels(ex. startupscreen + coordinates) to darkgrey
//    clearWorkSpace();


//    a value showing function is implemented. Just call

//    drawPot(xPos, yPos, fvalue, dvalue, dname, color) { //xposition, yposition, value 0-127, value to draw, name to draw, color of circle



// 7) add your amp.gain() control to the 4 volume-functions in "functions.ino"

void Plugin_3_Settings() {


  pl3waveform1.amplitude(1);
  pl3waveform1.pulseWidth(0.15);


  pl3waveformMod1.amplitude(1);
  pl3waveformMod1.frequencyModulation(1);

  pl3envelope1.delay(0);
  pl3envelope1.hold(0);
  pl3envelope2.delay(0);
  pl3envelope2.hold(0);

  pl3filter1.octaveControl(6);

  pl3mixer1.gain(0, 1);
  pl3mixer1.gain(1, 0);
  pl3mixer1.gain(2, 0);
  pl3mixer1.gain(3, 0);

  pl3dc1.amplitude(1);
  pl3amp.gain(1);
  pl3amp2.gain(1);
}


void Plugin3_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      lastPotRow = 10;
      plpreset[pl3NR] = constrain((plpreset[pl3NR] + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, plpreset[pl3NR], ILI9341_PURPLE);
      Plugin_View_Static();
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //Waveform
        OSC_MOD_Waveform(pl3NR, pl3OSC_MOD, 0, 0, ZERO, OSC_MOD_MAX_WF, "W~F");  //pluginNr, pointerarrayPos, column, row
        OSC_frequency(pl3NR, pl3OSC, 1, 0, ZERO, 15.00, "LFO");          //pluginNr, pointerarrayPos, column, row, max freq
        OSC_amplitude(pl3NR, pl3OSC, 2, 0, ZERO, GAIN_DIV_4, "LVL");     //pluginNr, pointerarrayPos, column, row
        OSC_Waveform(pl3NR, pl3OSC, 3, 0, ZERO, OSC_MAX_WF, "W~F");      //pluginNr, pointerarrayPos, column, row
        break;
      case 1:
        SVF_frequency(pl3NR, pl3SVF, 0, 1, ZERO, 127, "Freq");                //MIN: unused MAX: unused
        SVF_resonance(pl3NR, pl3SVF, 1, 1, ZERO, MAX_RESONANCE, "Reso");  //MIN: unused MAX: unused
        SVF_octaveControl(pl3NR, pl3SVF, 2, 1, ZERO, SVF_MAX_OCT, "Swp");     //MIN: unused MAX: amplitud
        SVF_Type(pl3NR, pl3TYPE, 3, 1, 0, 2, "");                              //MIN: unused MAX: unused
        break;
      case 2:
        ENV_ADSR(pl3NR, pl3ADSR1, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
        ENV_ADSR(pl3NR, pl3ADSR2, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
        break;
    }
  }


  if (ts.touched() || button[15]) {

    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin("plugin3", 19);
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin("plugin3", 19);
      }
    }
  }
}
void Plugin3_Page_Static() {
  clearWorkSpace();
  Plugin3_Change();
  drawNrInRect(18, 1, plpreset[pl3NR], ILI9341_PURPLE);

  //Waveform
  draw_OSC_MOD_Waveform(pl3NR, pl3OSC_MOD, 0, 0, ZERO, OSC_MOD_MAX_WF, "W~F");  //pluginNr, pointerarrayPos, column, row
  draw_OSC_frequency(pl3NR, pl3OSC, 1, 0, ZERO, 15.00, "LFO");          //pluginNr, pointerarrayPos, column, row, max freq
  draw_OSC_amplitude(pl3NR, pl3OSC, 2, 0, ZERO, GAIN_DIV_4, "LVL");     //pluginNr, pointerarrayPos, column, row
  draw_OSC_Waveform(pl3NR, pl3OSC, 3, 0, ZERO, OSC_MAX_WF, "W~F");      //pluginNr, pointerarrayPos, column, row

  draw_SVF_frequency(pl3NR, pl3SVF, 0, 1, ZERO, 127, "Freq");                //MIN: unused MAX: unused
  draw_SVF_resonance(pl3NR, pl3SVF, 1, 1, ZERO, MAX_RESONANCE, "Reso");  //MIN: unused MAX: unused
  draw_SVF_octaveControl(pl3NR, pl3SVF, 2, 1, ZERO, SVF_MAX_OCT, "Swp");     //MIN: unused MAX: amplitud
  draw_SVF_Type(pl3NR, pl3SVF, 3, 1, 0, 2, "");

  draw_ENV_ADSR(pl3NR, pl3ADSR1, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
  draw_ENV_ADSR(pl3NR, pl3ADSR2, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
}

void Plugin3_Change() {
  //Waveform
  change_OSC_MOD_Waveform(pl3NR, pl3OSC_MOD, 0, 0, ZERO, OSC_MAX_WF, "W~F");  //pluginNr, pointerarrayPos, column, row
  change_OSC_frequency(pl3NR, pl3OSC, 1, 0, ZERO, 15.00, "LFO");          //pluginNr, pointerarrayPos, column, row, max freq
  change_OSC_amplitude(pl3NR, pl3OSC, 2, 0, ZERO, GAIN_DIV_4, "LVL");     //pluginNr, pointerarrayPos, column, row
  change_OSC_Waveform(pl3NR, pl3OSC, 3, 0, ZERO, OSC_MOD_MAX_WF, "W~F");      //pluginNr, pointerarrayPos, column, row

  change_SVF_frequency(pl3NR, pl3SVF, 0, 1, ZERO, 127, "Freq");                //MIN: unused MAX: unused
  change_SVF_resonance(pl3NR, pl3SVF, 1, 1, ZERO, MAX_RESONANCE, "Reso");  //MIN: unused MAX: unused
  change_SVF_octaveControl(pl3NR, pl3SVF, 2, 1, ZERO, SVF_MAX_OCT, "Swp");     //MIN: unused MAX: amplitud
  change_SVF_Type(pl3NR, pl3SVF, 3, 1, 0, 2, "");

  change_ENV_ADSR(pl3NR, pl3ADSR1, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
  change_ENV_ADSR(pl3NR, pl3ADSR2, 0, 2, ATTACK_TIME, RELEASE_TIME, "");  //MIN: Attack/Decaytime MAX: Releasetime
}
