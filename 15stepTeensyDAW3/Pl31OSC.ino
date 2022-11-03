//Lets create a plugin
// these are the neccessary elements you have to do to add your own plugin:
// 1) copy the existing automatic generated code from "15stepTeensyDAW3.ino" and import it to https://newdigate.github.io/teensy-eurorack-audio-gui/
//    add your modules for the plugin. Dont forget to add your final AMP module for the Mixer section copy the code back to "15stepTeensyDAW3.ino"

// 2) add the plugin- _settings, _Static and _Dynamic functions to your plugin *.ino file add the functions to:
//    Plugin_3_Settings()      -> setup() function in "15stepTeensyDAW3.ino"
//    Plugin3_Page1_Static()   -> Plugin_View_Static(x) function in "functions.ino"
//    Plugin3_Page1_Dynamic()  -> loop() function in "15stepTeensyDAW3.ino"

// 3) define PLUGINx_PAGEnr and variables to "variables.h"

// 4) if not done yet move the plugin- _functions to their desired places

// 5) add NoteOn and Off´s to "midi.ino"

// 6) add controls to Plugin3_Page1_Dynamic()

// 7) add your amp.gain() control to the volume-functions in "functions.ino"


//1) we copy the automatic generated code from the "15stepTeensyDAW3.ino" and import it to https://newdigate.github.io/teensy-eurorack-audio-gui/
//   All created plugins are in here.

// for this tutorial we add followinig modules from the left sidebar:
// WAVEFORM
// FILTER
// DC
// ENVELOPE
// AMP

// rename the modules to your likenings, we will put all variables into a structfor a better view and handling. double-click on it to change its name.
// its recommended to name the variables like: "modulename_function"
// connect the modules together, where DC goes to input of the  envelope2 for the filter
// AMP will be used to control the volume of our mixer. Add your ampX gain function to all "volume-functions"
// if needed add a mixer to the chain. At this point it is easy to add 2 seperate mixers (for 8 plugins), if more are needed we will have to reroute some parts of the plugins

// export (Copy-paste) the new automatic generated code to the "15stepTeensyDAW3.ino". delete the librarys that come with the code

// 2) Add a new *.ino file for your plugin and add following functions to your file:
// Plugin_3_Settings()     -> here are all modules and their initial values stored
//                            like OSC Waveform, Frequency, level, Filters freq and resonance,.....

// Plugin3_Page1_Static(pageNumber)   -> if we open a pluginpage, we want to see the actual values, graphs and other icons immediatly
//                                       add this function to Plugin_View_Static(byte desired_instrument){} in functions.ino
//                                       desired_instrument can be transmitted to your plugin, for corresponding track color or so

// Plugin3_Page1_Dynamic()   -> this is where we assign values to our variables, that will handle our module-functions
//                              (Look on https://www.pjrc.com/teensy/gui/ for each module, what can be controlled)
//                              here happens all the touch, button and potentiometer input for the plugin.
//                              you can have several pages for your plugin
//                              there are several functions aviable to draw the value of the parameters
//                              We can leave Plugin3_Page1_Dynamic() {} empty for now.



///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////   add the settings-function "Plugin_3_Settings();" setup() function in "15stepTeensyDAW3.ino"  //////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// look for
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////   add the Plugin3_Page1_Static()-function to the Plugin_View_Static(x) function in "functions.ino"     //////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////   add the Plugin3_Page1_Dynamic()-function to the loop() function in "15stepTeensyDAW3.ino"     //////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// 3) head over to variables.h  and look for the ********************************************************

// you´ve come a long way, your last edited file should be midi.ino.
// Now its time to:
// 6) add your controls:
//    to make live a bit easier the display and touchscreen is sectioned into grids of  16pixels height and width
//    to call a position best way is to ask if gridTouchX or/and gridTouchY is in certain area like
//    if (gridTouchX == 10 && gridTouchY == 5)

//    to draw something the STEP_FRAME_W and STEP_FRAME_H come handy. use a multiplier and an offset to get to your desired position, like:
//    tft.drawPixel(STEP_FRAME_W * 3 + 2, STEP_FRAME_H * 5 - 3, int colour);


//    to clear the workspace (Grid, Pluginview or songmode)
//    this sets all pixels(ex. startupscreen + coordinates) to darkgrey
//    clearWorkSpace();


//    some value showing functions are implemented. Just call
//    drawbarH(XPos, YPos, value, Name, int color)  //gridPosX, gridPosY, value 0-100, valuename, backgroundcolor of bargraph
//    or

//    drawPot(xPos, yPos, fvalue, dvalue, dname, color) { //xposition, yposition, value 0-100, value to draw, name to draw, color of circle



// 7) add your amp.gain() control to the volume-functions in "functions.ino"

void Plugin_3_Settings() {

  pl3waveform1.begin(WAVEFORM_SAWTOOTH);
  pl3waveform1.amplitude(1);
  pl3waveform1.frequency(note_frequency[36]);
  pl3waveform1.pulseWidth(0.15);

  pl3filter1.frequency(pl3[pl3presetNr].Filter1_Frequency);
  pl3filter1.resonance(pl3[pl3presetNr].Filter1_Resonance);
  pl3filter1.octaveControl(pl3[pl3presetNr].Filter1_Sweep);

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
}

//Plugin3_Page_Static(n) to show your control values

void Plugin3_Page_Static(byte Pagenumber, byte desired_instrument) {
  //draw selecting pages buttons
  //draw_sub_page_buttons(2);
  drawNrInRect(18, 1, pl3presetNr, ILI9341_PURPLE);
  if (Pagenumber == 0) {
    drawPot(3, CONTROL_ROW_0, pl3[pl3presetNr].wfSelect_graph, pl3[pl3presetNr].wfSelect, "WForm", trackColor[desired_track]);
    drawPot(15, CONTROL_ROW_0, plugin[3].Volume_graph, plugin[3].Volume_graph, "MIX", trackColor[desired_track]);

    drawPot(3, CONTROL_ROW_1, pl3[pl3presetNr].Filter1_Frequency_graph, pl3[pl3presetNr].Filter1_Frequency, "Freq", trackColor[desired_track]);
    drawPot(7, CONTROL_ROW_1, pl3[pl3presetNr].Filter1_Resonance_graph, pl3[pl3presetNr].Filter1_Resonance_graph, "Reso", trackColor[desired_track]);
    drawPot(11, CONTROL_ROW_1, pl3[pl3presetNr].Filter1_Sweep_graph, pl3[pl3presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_track]);

    drawPot(3, CONTROL_ROW_2, pl3[pl3presetNr].Env1_Attack_graph, pl3[pl3presetNr].Env1_Attack, "Atck", trackColor[desired_track]);
    drawPot(7, CONTROL_ROW_2, pl3[pl3presetNr].Env1_Decay_graph, pl3[pl3presetNr].Env1_Decay, "Dec", trackColor[desired_track]);
    drawPot(11, CONTROL_ROW_2, pl3[pl3presetNr].Env1_Sustain_graph, pl3[pl3presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_track]);
    drawPot(15, CONTROL_ROW_2, pl3[pl3presetNr].Env1_Release_graph, pl3[pl3presetNr].Env1_Release, "Rel", trackColor[desired_track]);
  }
}

void Plugin3_Page1_Dynamic(byte desired_instrument) {



  TS_Point p = ts.getPoint();
  if (ts.touched() || !buttons[6].read()) {
    gridTouchX = map(p.x, TS_MINX, TS_MAXX, 0, 19);
    gridTouchY = map(p.y, TS_MINY, TS_MAXY, 0, 14);

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
    if (gridTouchX >= 18 && gridTouchY == 1) {
      drawNrInRect(18, 1, pl3presetNr, ILI9341_PURPLE);
      if ((abs(map(Potentiometer1, 0, 127, 0, MAX_PRESETS - 1) - pl3presetNr) < 2)) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        pl3presetNr = map(Potentiometer1, 0, 127, 0, MAX_PRESETS - 1);
      }
    }
    if (millis() % 20 > 15) {
      if (gridTouchY == CONTROL_ROW_0) {

        //Waveform
        if (gridTouchX == 3 || gridTouchX == 4) {
          drawPot(3, CONTROL_ROW_0, pl3[pl3presetNr].wfSelect_graph, pl3[pl3presetNr].wfSelect, "WForm", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl3[pl3presetNr].wfSelect_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl3[pl3presetNr].wfSelect_graph = Potentiometer1;
            pl3[pl3presetNr].wfSelect = map(pl3[pl3presetNr].wfSelect_graph, 0, 127, 0, 12);
            pl3waveform1.begin(pl3[pl3presetNr].wfSelect);
          }
        }
        //Volume
        if (gridTouchX == 15 || gridTouchX == 16) {
          drawPot(15, CONTROL_ROW_0, plugin[2].Volume_graph, plugin[2].Volume_graph, "MIX", trackColor[desired_track]);
          if (abs(Potentiometer1 - plugin[2].Volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            plugin[2].Volume_graph = Potentiometer1;
            plugin[2].Volume = plugin[2].Volume_graph / 127.00;
            mixer5.gain(2, plugin[2].Volume);
          }
        }
      }

      if (gridTouchY == CONTROL_ROW_1) {

        //Filter Frequency
        if (gridTouchX == 3 || gridTouchX == 4) {
          drawPot(3, CONTROL_ROW_1, pl3[pl3presetNr].Filter1_Frequency_graph, pl3[pl3presetNr].Filter1_Frequency, "Frq", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl3[pl3presetNr].Filter1_Frequency_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl3[pl3presetNr].Filter1_Frequency_graph = Potentiometer1;
            pl3[pl3presetNr].Filter1_Frequency = map(pl3[pl3presetNr].Filter1_Frequency_graph, 0, 127, 40, 5900.00);
            pl3filter1.frequency(pl3[pl3presetNr].Filter1_Frequency);
          }
        }
        //Resonance
        if (gridTouchX == 7 || gridTouchX == 8) {
          drawPot(7, CONTROL_ROW_1, pl3[pl3presetNr].Filter1_Resonance_graph, pl3[pl3presetNr].Filter1_Resonance_graph, "Res", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl3[pl3presetNr].Filter1_Resonance_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl3[pl3presetNr].Filter1_Resonance_graph = Potentiometer1;
            pl3[pl3presetNr].Filter1_Resonance = pl3[pl3presetNr].Filter1_Resonance_graph / 25.40;
            pl3filter1.resonance(pl3[pl3presetNr].Filter1_Resonance);
          }
        }
        //Sweep
        if (gridTouchX == 11 || gridTouchX == 12) {
          drawPot(11, CONTROL_ROW_1, pl3[pl3presetNr].Filter1_Sweep_graph, pl3[pl3presetNr].Filter1_Sweep_graph, "Swp", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl3[pl3presetNr].Filter1_Sweep_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl3[pl3presetNr].Filter1_Sweep_graph = Potentiometer1;
            pl3[pl3presetNr].Filter1_Sweep = pl3[pl3presetNr].Filter1_Sweep_graph / 18.14;
            pl3filter1.octaveControl(pl3[pl3presetNr].Filter1_Sweep);
          }
        }
      }

      if (gridTouchY == CONTROL_ROW_2) {

        //Attack
        if (gridTouchX == 3 || gridTouchX == 4) {
          drawPot(3, CONTROL_ROW_2, pl3[pl3presetNr].Env1_Attack_graph, pl3[pl3presetNr].Env1_Attack, "Att", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl3[pl3presetNr].Env1_Attack_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl3[pl3presetNr].Env1_Attack_graph = Potentiometer1;
            pl3[pl3presetNr].Env1_Attack = map(pl3[pl3presetNr].Env1_Attack_graph, 0, 127, 10, 700);
            pl3envelope1.attack(pl3[pl3presetNr].Env1_Attack);
            pl3envelope2.attack(pl3[pl3presetNr].Env1_Attack);
          }
        }
        //Decay
        if (gridTouchX == 7 || gridTouchX == 8) {
          drawPot(7, CONTROL_ROW_2, pl3[pl3presetNr].Env1_Decay_graph, pl3[pl3presetNr].Env1_Decay, "Dec", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl3[pl3presetNr].Env1_Decay_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl3[pl3presetNr].Env1_Decay_graph = Potentiometer1;
            pl3[pl3presetNr].Env1_Decay = map(pl3[pl3presetNr].Env1_Decay_graph, 0, 127, 10, 700);
            pl3envelope1.decay(pl3[pl3presetNr].Env1_Decay);
            pl3envelope2.decay(pl3[pl3presetNr].Env1_Decay);
          }
        }
        //Sustain
        if (gridTouchX == 11 || gridTouchX == 12) {
          drawPot(11, CONTROL_ROW_2, pl3[pl3presetNr].Env1_Sustain_graph, pl3[pl3presetNr].Env1_Sustain_graph, "Sus", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl3[pl3presetNr].Env1_Sustain_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl3[pl3presetNr].Env1_Sustain_graph = Potentiometer1;
            pl3[pl3presetNr].Env1_Sustain = pl3[pl3presetNr].Env1_Sustain_graph / 127.00;
            pl3envelope1.sustain(pl3[pl3presetNr].Env1_Sustain);
            pl3envelope2.sustain(pl3[pl3presetNr].Env1_Sustain);
          }
        }
        //Release
        if (gridTouchX == 15 || gridTouchX == 16) {
          drawPot(15, CONTROL_ROW_2, pl3[pl3presetNr].Env1_Release_graph, pl3[pl3presetNr].Env1_Release, "Rel", trackColor[desired_track]);
          if (abs(Potentiometer1 - pl3[pl3presetNr].Env1_Release_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
            pl3[pl3presetNr].Env1_Release_graph = Potentiometer1;
            pl3[pl3presetNr].Env1_Release = map(pl3[pl3presetNr].Env1_Release_graph, 0, 127, 180, 1200);
            pl3envelope1.release(pl3[pl3presetNr].Env1_Release);
            pl3envelope2.release(pl3[pl3presetNr].Env1_Release);
          }
        }
      }
    }
  }
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
      myFile.print((char)pl3[maxpreset].wfSelect_graph);
    }
    myFile.print((char)plugin[2].Volume_graph);
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
      pl3[maxpreset].wfSelect_graph = myFile.read();
    }
    plugin[2].Volume_graph = myFile.read();
    tft.println("Done");
    startUpScreen();
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening plugin3.txt");
  }
}