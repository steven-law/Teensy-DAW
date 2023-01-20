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
//                                       add this function to Plugin_View_Static(byte desired_instrument){} in functions.ino
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

  pl3waveform1.begin(WAVEFORM_SAWTOOTH);
  pl3waveform1.amplitude(1);
  pl3waveform1.frequency(note_frequency[36]);
  pl3waveform1.pulseWidth(0.15);

  pl3filter1.frequency(pl3[pl3presetNr].Filter1_Frequency);
  pl3filter1.resonance(pl3[pl3presetNr].Filter1_Resonance);
  pl3filter1.octaveControl(pl3[pl3presetNr].Filter1_Sweep);

  pl3mixer1.gain(0, 1);
  pl3mixer1.gain(1, 0);
  pl3mixer1.gain(2, 0);
  pl3mixer1.gain(3, 0);

  pl3envelope1.delay(0);
  pl3envelope1.attack(pl3[pl3presetNr].Env1_Attack);
  pl3envelope1.hold(0);
  pl3envelope1.decay(500);
  pl3envelope1.sustain(0.8);
  pl3envelope1.release(pl3[pl3presetNr].Env1_Release);

  pl3dc1.amplitude(1);

  pl3envelope2.delay(0);
  pl3envelope2.attack(pl3[pl3presetNr].Env1_Attack);
  pl3envelope2.hold(0);
  pl3envelope2.decay(500);
  pl3envelope2.sustain(0.8);
  pl3envelope2.release(pl3[pl3presetNr].Env1_Release);
  pl3amp.gain(1);
  pl3amp2.gain(1);
}
void Plugin3_Control() {
  switch (lastPotRow) {
    case 0:
      if (pl3[pl3presetNr].wfSelect_graph != Potentiometer[0]) {
        pl3[pl3presetNr].wfSelect_graph = Potentiometer[0];
        pl3[pl3presetNr].wfSelect = map(pl3[pl3presetNr].wfSelect_graph, 0, 127, 0, 12);
        pl3waveform1.begin(pl3[pl3presetNr].wfSelect);
        drawPot(CTRL_COL_0, CTRL_ROW_0, pl3[pl3presetNr].wfSelect_graph, pl3[pl3presetNr].wfSelect, "WForm", trackColor[desired_track]);
      }
      break;

    case 1:
      if (pl3[pl3presetNr].Filter1_Frequency_graph != Potentiometer[0]) {
        pl3[pl3presetNr].Filter1_Frequency_graph = Potentiometer[0];
        pl3[pl3presetNr].Filter1_Frequency = note_frequency[pl3[pl3presetNr].Filter1_Frequency_graph];
        filter1.frequency(pl3[pl3presetNr].Filter1_Frequency);
        drawPot(CTRL_COL_0, CTRL_ROW_1, pl3[pl3presetNr].Filter1_Frequency_graph, pl3[pl3presetNr].Filter1_Frequency, "Freq", trackColor[desired_track]);
      }

      if (pl3[pl3presetNr].Filter1_Resonance_graph != Potentiometer[1]) {
        pl3[pl3presetNr].Filter1_Resonance_graph = Potentiometer[1];
        pl3[pl3presetNr].Filter1_Resonance = pl3[pl3presetNr].Filter1_Resonance_graph / 25.40;
        filter1.resonance(pl3[pl3presetNr].Filter1_Resonance);
        drawPot_2(CTRL_COL_1, CTRL_ROW_1, pl3[pl3presetNr].Filter1_Resonance_graph, pl3[pl3presetNr].Filter1_Resonance_graph, "Reso", trackColor[desired_track]);
      }
      if (pl3[pl3presetNr].Filter1_Sweep_graph != Potentiometer[2]) {
        pl3[pl3presetNr].Filter1_Sweep_graph = Potentiometer[2];
        pl3[pl3presetNr].Filter1_Sweep = pl3[pl3presetNr].Filter1_Sweep_graph / 18.14;
        filter1.octaveControl(pl3[pl3presetNr].Filter1_Sweep);
        drawPot_3(CTRL_COL_2, CTRL_ROW_1, pl3[pl3presetNr].Filter1_Sweep_graph, pl3[pl3presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_track]);
      }
      if (pl3[pl3presetNr].Filter1_Type_graph != Potentiometer[3]) {
        pl3[pl3presetNr].Filter1_Type_graph = Potentiometer[3];
        pl3[pl3presetNr].Filter1_Type = pl3[pl3presetNr].Filter1_Type_graph / 43;
        selectFilterType(19, pl3[pl3presetNr].Filter1_Type);
        drawPot_4(CTRL_COL_3, CTRL_ROW_1, pl3[pl3presetNr].Filter1_Type_graph, pl3[pl3presetNr].Filter1_Type, "", trackColor[desired_track]);
        drawChar(CTRL_COL_3, 7, filterType[pl3[pl3presetNr].Filter1_Type], ILI9341_WHITE);
      }
      break;

    case 2:
      if (pl3[pl3presetNr].Env1_Attack_graph != Potentiometer[0]) {
        pl3[pl3presetNr].Env1_Attack_graph = Potentiometer[0];
        pl3[pl3presetNr].Env1_Attack = map(pl3[pl3presetNr].Env1_Attack_graph, 0, 127, 10, 700);
        envelope1.attack(pl3[pl3presetNr].Env1_Attack);
        envelope2.attack(pl3[pl3presetNr].Env1_Attack);
        drawPot(CTRL_COL_0, CTRL_ROW_2, pl3[pl3presetNr].Env1_Attack_graph, pl3[pl3presetNr].Env1_Attack, "Atck", trackColor[desired_track]);
      }
      if (pl3[pl3presetNr].Env1_Decay_graph != Potentiometer[1]) {
        pl3[pl3presetNr].Env1_Decay_graph = Potentiometer[1];
        pl3[pl3presetNr].Env1_Decay = map(pl3[pl3presetNr].Env1_Decay_graph, 0, 127, 10, 700);
        envelope1.decay(pl3[pl3presetNr].Env1_Decay);
        envelope2.decay(pl3[pl3presetNr].Env1_Decay);
        drawPot_2(CTRL_COL_1, CTRL_ROW_2, pl3[pl3presetNr].Env1_Decay_graph, pl3[pl3presetNr].Env1_Decay, "Dec", trackColor[desired_track]);
      }
      if (pl3[pl3presetNr].Env1_Sustain_graph != Potentiometer[2]) {
        pl3[pl3presetNr].Env1_Sustain_graph = Potentiometer[2];
        pl3[pl3presetNr].Env1_Sustain = pl3[pl3presetNr].Env1_Sustain_graph / 127.00;
        envelope1.sustain(pl3[pl3presetNr].Env1_Sustain);
        envelope2.sustain(pl3[pl3presetNr].Env1_Sustain);
        drawPot_3(CTRL_COL_2, CTRL_ROW_2, pl3[pl3presetNr].Env1_Sustain_graph, pl3[pl3presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_track]);
      }
      if (pl3[pl3presetNr].Env1_Release_graph != Potentiometer[3]) {
        pl3[pl3presetNr].Env1_Release_graph = Potentiometer[3];
        pl3[pl3presetNr].Env1_Release = map(pl3[pl3presetNr].Env1_Release_graph, 0, 127, 180, 1200);
        envelope1.release(pl3[pl3presetNr].Env1_Release);
        envelope2.release(pl3[pl3presetNr].Env1_Release);
        drawPot_4(CTRL_COL_3, CTRL_ROW_2, pl3[pl3presetNr].Env1_Release_graph, pl3[pl3presetNr].Env1_Release, "Rel", trackColor[desired_track]);
      }
      break;
  }
}
void Plugin3_Page1_Dynamic() {
  //change preset
  if (button[14]) {
    if (enc_moved[0]) {
      pl3presetNr = constrain((pl3presetNr + encoded[0]), 0, MAX_PRESETS - 1);
      drawNrInRect(18, 1, pl3presetNr, ILI9341_PURPLE);
      Plugin3_Page_Static(0);
    }
  }
  if (!button[14]) {
    switch (lastPotRow) {
      case 0:
        //Waveform
        Potentiometer[0] = pl3[pl3presetNr].wfSelect * 11;
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl3[pl3presetNr].wfSelect + encoded[0]), 0, 12) * 11;
        }
        break;

      case 1:
        //Filter Frequency
        Potentiometer[0] = pl3[pl3presetNr].Filter1_Frequency_graph;
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl3[pl3presetNr].Filter1_Frequency_graph + encoded[0]), 0, 127);
        }
        //Resonance
        Potentiometer[1] = pl3[pl3presetNr].Filter1_Resonance_graph;
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl3[pl3presetNr].Filter1_Resonance_graph + encoded[1]), 0, 127);
        }
        //Sweep
        Potentiometer[2] = pl3[pl3presetNr].Filter1_Sweep_graph;
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((pl3[pl3presetNr].Filter1_Sweep_graph + encoded[2]), 0, 127);
        }
        //Filtertype
        Potentiometer[3] = pl3[pl3presetNr].Filter1_Type * 43;
        if (enc_moved[3]) {
          Potentiometer[3] = constrain((pl3[pl3presetNr].Filter1_Type + encoded[3]), 0, 2) * 43;
        }
        break;

      case 2:
        //Attack
        Potentiometer[0] = pl3[pl3presetNr].Env1_Attack_graph;
        if (enc_moved[0]) {
          Potentiometer[0] = constrain((pl3[pl3presetNr].Env1_Attack_graph + encoded[0]), 0, 127);
        }
        //Decay
        Potentiometer[1] = pl3[pl3presetNr].Env1_Decay_graph;
        if (enc_moved[1]) {
          Potentiometer[1] = constrain((pl3[pl3presetNr].Env1_Decay_graph + encoded[1]), 0, 127);
        }
        //Sustain
        Potentiometer[2] = pl3[pl3presetNr].Env1_Sustain_graph;
        if (enc_moved[2]) {
          Potentiometer[2] = constrain((pl3[pl3presetNr].Env1_Sustain_graph + encoded[2]), 0, 127);
        }
        //Release
        Potentiometer[3] = pl3[pl3presetNr].Env1_Release_graph;
        if (enc_moved[3]) {
          Potentiometer[3] = constrain((pl3[pl3presetNr].Env1_Release_graph + encoded[3]), 0, 127);
        }
        break;
    }
  }

  TS_Point p = ts.getPoint();
  if (ts.touched() || button[15]) {


    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savePlugin3();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadPlugin3();
      }
    }
    //change preset
    //if (gridTouchX >= 18 && gridTouchY == 1) {


    /*drawNrInRect(18, 1, pl3presetNr, ILI9341_PURPLE);
    if ((abs(map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1) - pl3presetNr) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
      pl3presetNr = map(Potentiometer[0], 0, 127, 0, MAX_PRESETS - 1);
    }*/
    // }

    if (gridTouchY >= 2 && gridTouchY <= 4) {
      lastPotRow = 0;
    }

    if (gridTouchY >= 5 && gridTouchY <= 7) {
      lastPotRow = 1;
    }

    if (gridTouchY >= 8 && gridTouchY <= 10) {
      lastPotRow = 2;
    }
  }
}
void Plugin3_Page_Static(byte Pagenumber) {
  clearWorkSpace();
  Plugin3_Change();
  //draw selecting pages buttons
  //draw_sub_page_buttons(2);
  drawNrInRect(18, 1, pl3presetNr, ILI9341_PURPLE);
  
  //case 0
  drawPot(CTRL_COL_0, CTRL_ROW_0, pl3[pl3presetNr].wfSelect_graph, pl3[pl3presetNr].wfSelect, "WForm", trackColor[desired_track]);
  //case 1
  drawPot(CTRL_COL_0, CTRL_ROW_1, pl3[pl3presetNr].Filter1_Frequency_graph, note_frequency[pl3[pl3presetNr].Filter1_Frequency_graph], "Freq", trackColor[desired_track]);
  drawPot(CTRL_COL_1, CTRL_ROW_1, pl3[pl3presetNr].Filter1_Resonance_graph, pl3[pl3presetNr].Filter1_Resonance_graph, "Reso", trackColor[desired_track]);
  drawPot(CTRL_COL_2, CTRL_ROW_1, pl3[pl3presetNr].Filter1_Sweep_graph, pl3[pl3presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_track]);
  drawPot(CTRL_COL_3, CTRL_ROW_1, pl3[pl3presetNr].Filter1_Type_graph, pl3[pl3presetNr].Filter1_Type, "", trackColor[desired_track]);
  drawChar(CTRL_COL_3, 7, filterType[pl3[pl3presetNr].Filter1_Type], ILI9341_WHITE);
  //case 2
  drawPot(CTRL_COL_0, CTRL_ROW_2, pl3[pl3presetNr].Env1_Attack_graph, pl3[pl3presetNr].Env1_Attack, "Atck", trackColor[desired_track]);
  drawPot(CTRL_COL_1, CTRL_ROW_2, pl3[pl3presetNr].Env1_Decay_graph, pl3[pl3presetNr].Env1_Decay, "Dec", trackColor[desired_track]);
  drawPot(CTRL_COL_2, CTRL_ROW_2, pl3[pl3presetNr].Env1_Sustain_graph, pl3[pl3presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_track]);
  drawPot(CTRL_COL_3, CTRL_ROW_2, pl3[pl3presetNr].Env1_Release_graph, pl3[pl3presetNr].Env1_Release, "Rel", trackColor[desired_track]);
}
void Plugin3_Change() {
  pl3waveform1.begin(pl3[pl3presetNr].wfSelect);
  pl3filter1.frequency(pl3[pl3presetNr].Filter1_Frequency);
  pl3filter1.resonance(pl3[pl3presetNr].Filter1_Resonance);
  pl3filter1.octaveControl(pl3[pl3presetNr].Filter1_Sweep);
  selectFilterType(19, pl3[pl3presetNr].Filter1_Type);
  pl3envelope1.attack(pl3[pl3presetNr].Env1_Attack);
  pl3envelope2.attack(pl3[pl3presetNr].Env1_Attack);
  pl3envelope1.decay(pl3[pl3presetNr].Env1_Decay);
  pl3envelope2.decay(pl3[pl3presetNr].Env1_Decay);
  pl3envelope1.sustain(pl3[pl3presetNr].Env1_Sustain);
  pl3envelope2.sustain(pl3[pl3presetNr].Env1_Sustain);
  pl3envelope1.release(pl3[pl3presetNr].Env1_Release);
  pl3envelope2.release(pl3[pl3presetNr].Env1_Release);
}


void savePlugin3() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  // delete the file:
  tft.print("Removing plugin3.txt...");
  SD.remove("plugin3.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening plugin3.txt...");
  myFile = SD.open("plugin3.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    tft.print("Writing plugin 3 to plugin3.txt...");
    //save plugin 3 variables
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      myFile.print((char)pl3[maxpreset].Filter1_Frequency_graph);
      myFile.print((char)pl3[maxpreset].Filter1_Resonance_graph);
      myFile.print((char)pl3[maxpreset].Filter1_Sweep_graph);
      myFile.print((char)pl3[maxpreset].Env1_Attack_graph);
      myFile.print((char)pl3[maxpreset].Env1_Decay_graph);
      myFile.print((char)pl3[maxpreset].Env1_Sustain_graph);
      myFile.print((char)pl3[maxpreset].Env1_Release_graph);
      myFile.print((char)pl3[maxpreset].wfSelect);
      myFile.print((char)pl3[maxpreset].Filter1_Type_graph);
    }

    tft.println("Done");

    // close the file:
    myFile.close();
    tft.println("Saving done.");
    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin3.txt");
  }
}
void loadPlugin3() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("plugin3.txt");
  if (myFile) {
    tft.println("opening plugin3.txt:");

    // read from the file until there's nothing else in it:

    //load plugin 3 variables
    tft.print("reading plugin 3 from plugin3.txt...");
    for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
      pl3[maxpreset].Filter1_Frequency_graph = myFile.read();
      pl3[maxpreset].Filter1_Resonance_graph = myFile.read();
      pl3[maxpreset].Filter1_Sweep_graph = myFile.read();
      pl3[maxpreset].Env1_Attack_graph = myFile.read();
      pl3[maxpreset].Env1_Decay_graph = myFile.read();
      pl3[maxpreset].Env1_Sustain_graph = myFile.read();
      pl3[maxpreset].Env1_Release_graph = myFile.read();
      pl3[maxpreset].wfSelect = myFile.read();
      pl3[maxpreset].Filter1_Type_graph = myFile.read();
    }

    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin3.txt");
  }
  // execute changes
  for (byte maxpreset = 0; maxpreset < MAX_PRESETS; maxpreset++) {
    pl3[maxpreset].wfSelect_graph = pl3[maxpreset].wfSelect * 10;
    pl3[maxpreset].Filter1_Frequency = note_frequency[pl3[maxpreset].Filter1_Frequency_graph];
    pl3[maxpreset].Filter1_Resonance = pl3[maxpreset].Filter1_Resonance_graph / 25.40;
    pl3[maxpreset].Filter1_Sweep = pl3[maxpreset].Filter1_Sweep_graph / 18.14;
    pl3[maxpreset].Filter1_Type = pl3[maxpreset].Filter1_Type_graph / 43;
    pl3[maxpreset].Env1_Attack = map(pl3[maxpreset].Env1_Attack_graph, 0, 127, 10, 700);
    pl3[maxpreset].Env1_Decay = map(pl3[maxpreset].Env1_Decay_graph, 0, 127, 10, 700);
    pl3[maxpreset].Env1_Sustain = pl3[maxpreset].Env1_Sustain_graph / 127.00;
    pl3[maxpreset].Env1_Release = map(pl3[maxpreset].Env1_Release_graph, 0, 127, 180, 1200);
  }
}