

void songModePage(int songpageNumber) {
  page_phrase_start = songpageNumber * 16;
  page_phrase_end = (songpageNumber + 1) * 16;

  phraser = gridTouchX - 2 + (16 * songpageNumber);
  int touched_phrase = gridTouchX - 2 + (16 * songpageNumber);



  if (!button[14] && !button[15]) {

    //gridTouchX
    if (enc_moved[0]) {
      gridTouchX = constrain((gridTouchX + encoded[0]), 0, 19);
      drawCursor();
      showCoordinates();
    }
    //gridTouchY
    if (enc_moved[1]) {
      gridTouchY = constrain((gridTouchY + encoded[1]), 0, 14);
      drawCursor();
      showCoordinates();
    }
    //Start of loop
    if (enc_moved[2]) {
      start_of_loop = constrain((start_of_loop + encoded[2]), 0, MAX_PHRASES - 2);
      draw_start_of_loop();
    }

    //end of loop
    if (enc_moved[3]) {
      end_of_loop = constrain((end_of_loop + encoded[3]), 1, MAX_PHRASES - 1);
      draw_end_of_loop();
    }
  }
  //clipassign
  if (button[15]) {
    if (seq_rec) {
      track[trackTouchY].arrangment1[touched_phrase] = track[trackTouchY].lastclip;
      track[trackTouchY].NoteOffset[touched_phrase] = track[trackTouchY].lastNoteOffset;
      track[trackTouchY].Ttrckprst[touched_phrase] = track[trackTouchY].lastpresetNr;
      track[trackTouchY].volume[touched_phrase] = track[trackTouchY].lastvolume;
    }

    //Clipassign
    if (enc_moved[0]) {
      track[trackTouchY].arrangment1[touched_phrase] = constrain((track[trackTouchY].lastclip + encoded[0]), 0, MAX_CLIPS);
      track[trackTouchY].lastclip = track[trackTouchY].arrangment1[touched_phrase];
    }
    //Note transpose
    if (enc_moved[1]) {
      track[trackTouchY].NoteOffset[touched_phrase] = constrain((track[trackTouchY].lastNoteOffset + encoded[1]), -32, 32);
      track[trackTouchY].lastNoteOffset = track[trackTouchY].NoteOffset[touched_phrase];
    }
    //presetnr
    if (enc_moved[2]) {
      track[trackTouchY].Ttrckprst[touched_phrase] = constrain((track[trackTouchY].lastpresetNr + encoded[2]), 0, MAX_PRESETS - 1);
      track[trackTouchY].lastpresetNr = track[trackTouchY].Ttrckprst[touched_phrase];
    }
    //volume
    if (enc_moved[3]) {
      track[trackTouchY].volume[touched_phrase] = constrain((track[trackTouchY].lastvolume + encoded[3]), 0, 127);
      track[trackTouchY].lastvolume = track[trackTouchY].volume[touched_phrase];
    }
    //draw horizontal song arrangment Lines
    if (msecs % 100 == 0) {
      drawarrengmentLine(songpageNumber, trackTouchY, touched_phrase);
      drawChar(18, 9, "Prst:", trackColor[trackTouchY] + (track[trackTouchY].arrangment1[touched_phrase] * 20));
      drawNrInRect(18, 10, track[trackTouchY].Ttrckprst[touched_phrase], trackColor[trackTouchY] + (track[trackTouchY].arrangment1[touched_phrase] * 20));
      drawChar(18, 11, "Vol:", trackColor[trackTouchY] + (track[trackTouchY].arrangment1[touched_phrase] * 20));
      drawNrInRect2(18, 12, track[trackTouchY].volume[touched_phrase], trackColor[trackTouchY] + (track[trackTouchY].arrangment1[touched_phrase] * 20));
    }
  }

  //end of loop
  if (button[14]) {
    //set Tempo
    if (enc_moved[0]) {
      seq_tempo = constrain((seq_tempo + encoded[0]), 55, 200);
      master_clock.set_tempo(seq_tempo);
      show_tempo();
      Serial.print("seq_tempo");
      Serial.println(seq_tempo);
      //master_clock.get_tempo();
    }
    //Start of loop
    if (enc_moved[2]) {
      start_of_loop = constrain(start_of_loop + (encoded[2] * 8), 0, MAX_PHRASES - 2);
      draw_start_of_loop();
    }
    //end of loop
    if (enc_moved[3]) {
      end_of_loop = constrain(end_of_loop + (encoded[3] * 8), 1, MAX_PHRASES - 1);
      draw_end_of_loop();
    }
  }

  if (ts.touched() || button[15]) {


    /*
    //Assigning clips to the arranger
    if (gridTouchX >= SEQ_GRID_LEFT && gridTouchX <= SEQ_GRID_RIGHT && trackTouchY >= 0 && trackTouchY < 8) {

      //if (abs(map(Potentiometer[0], 0, 127, 0, 8) - track[trackTouchY].arrangment1[touched_phrase]) < POTPICKUP) {
      if (track[trackTouchY].arrangment1[touched_phrase] != map(Potentiometer[0], 0, 127, 0, 8)) {
        track[trackTouchY].arrangment1[touched_phrase] = map(Potentiometer[0], 0, 127, 0, 8);
      }
      //}
      // if (abs(map(Potentiometer[1], 0, 127, -32, 32) - track[trackTouchY].NoteOffset[touched_phrase]) < POTPICKUP) {
      if (track[trackTouchY].NoteOffset[touched_phrase] != map(Potentiometer[1], 0, 127, -32, 32)) {
        track[trackTouchY].NoteOffset[touched_phrase] = map(Potentiometer[1], 0, 127, -32, 32);
      }
      // }
      //if (abs(map(Potentiometer[2], 0, 127, 0, 7) - track[trackTouchY].Ttrckprst[touched_phrase]) < POTPICKUP) {
      if (track[trackTouchY].Ttrckprst[touched_phrase] != map(Potentiometer[2], 0, 127, 0, 7)) {
        track[trackTouchY].Ttrckprst[touched_phrase] = map(Potentiometer[2], 0, 127, 0, 7);
        drawChar(18, 9, "Prst:", trackColor[trackTouchY] + (track[trackTouchY].arrangment1[touched_phrase] * 20));
        drawNrInRect(18, 10, track[trackTouchY].Ttrckprst[touched_phrase], trackColor[trackTouchY] + (track[trackTouchY].arrangment1[touched_phrase] * 20));
      }
      // }
      //if (abs(Potentiometer[3] - track[trackTouchY].volume[touched_phrase]) < POTPICKUP) {
      if (track[trackTouchY].volume[touched_phrase] != Potentiometer[3]) {
        track[trackTouchY].volume[touched_phrase] = Potentiometer[3];
        drawChar(18, 11, "Vol:", trackColor[trackTouchY] + (track[trackTouchY].arrangment1[touched_phrase] * 20));
        drawNrInRect(18, 12, track[trackTouchY].volume[touched_phrase], trackColor[trackTouchY] + (track[trackTouchY].arrangment1[touched_phrase] * 20));
        //pluginVolume(track[trackTouchY].MIDIchannel, Potentiometer[3] / 127.00);
        //   }
      }
      //draw horizontal song arrangment Lines
      drawarrengmentLine(songpageNumber, trackTouchY, touched_phrase);
    }
    */


    //page selection
    if (gridTouchY == 13) {
      for (int songpages = 0; songpages < 16; songpages++) {
        if (gridTouchX == (songpages + 2)) {
          //phraseSegmentLength = 16;
          selectPage = SONGMODE_PAGE_1 + songpages;
          gridSongMode(songpages);
          songModePage(songpages);
        }
      }
    }
    //clear arrangment selection
    if (gridTouchX >= 18) {
      if (gridTouchY == 3 || gridTouchY == 4) {
        clearArrangment();
      }
    }
    //save and load
    if (gridTouchY == 0) {
      //Save button
      if (gridTouchX == POSITION_SAVE_BUTTON || gridTouchX == POSITION_SAVE_BUTTON + 1) {
        savebutton();
      }
      //Load button
      if (gridTouchX == POSITION_LOAD_BUTTON) {
        loadbutton();
      }
    }
  }
}



void savebutton() {

  tft.fillScreen(ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_8);
  tft.setCursor(0, 0);
  for (int ctrack = 0; ctrack < 8; ctrack++) {
    for (int cphrase = 0; cphrase < MAX_PHRASES - 1; cphrase++) {
      track[ctrack].NoteOffset_graph[cphrase] = track[ctrack].NoteOffset[cphrase] + 32;
    }
  }
  // delete the file:
  tft.print("Removing project.txt...");
  SD.remove("project.txt");
  tft.println("Done");

  // open the file.
  tft.print("Creating and opening project.txt...");
  myFile = SD.open("project.txt", FILE_WRITE);
  tft.println("Done");

  // if the file opened okay, write to it:
  if (myFile) {

    //save arrangment
    tft.print("Writing songarrangment to project.txt...");
    for (int ctrack = 0; ctrack < 8; ctrack++) {
      for (int cphrase = 0; cphrase < MAX_PHRASES - 1; cphrase++) {
        myFile.print((char)track[ctrack].arrangment1[cphrase]);
        myFile.print((char)track[ctrack].NoteOffset_graph[cphrase]);
        myFile.print((char)track[ctrack].Ttrckprst[cphrase]);
        myFile.print((char)track[ctrack].volume[cphrase]);
      }
    }
    tft.println("Done");

    // close the file:
    myFile.close();
    tft.println("Saving done.");


    tft.print("Writing track 1 to project.txt...");
    //save plugin 1 variables
    saveTrack(trackNames_long[0], 0);
    saveMIDItrackDrum();
    tft.println("Done");

    tft.print("Writing track 2-8 to project.txt...");
    //save plugin 2-8 variables
    for (int tracks = 1; tracks < 8; tracks++) {
      saveTrack(trackNames_long[tracks], tracks);
      saveMIDItrack(trackNames_long[tracks], tracks);
    }
    //save Mixersettings
    saveMixer();
    tft.println("Done");

    tft.print("Writing plugin 1 to project.txt...");
    //save plugin 1 variables
    savePlugin("plugin1", 17);
    tft.println("Done");

    tft.print("Writing plugin 2 to project.txt...");
    //save plugin 2 variables
    savePlugin("plugin2", 18);
    tft.println("Done");

    tft.print("Writing plugin 3 to project.txt...");
    //save plugin 3 variables
    savePlugin("plugin3", 19);
    tft.println("Done");

    tft.print("Writing plugin 4 to project.txt...");
    //save plugin 4 variables
    savePlugin("plugin4", 20);
    tft.println("Done");

    tft.print("Writing plugin 5 to project.txt...");
    //save plugin 5 variables
    savePlugin("plugin5", 21);
    tft.println("Done");

    tft.print("Writing plugin 6 to project.txt...");
    //save plugin 6 variables
    savePlugin("plugin6", 22);
    tft.println("Done");

    tft.print("Writing plugin 8 to project.txt...");
    //save plugin 8 variables
    savePlugin("plugin8", 24);
    tft.println("Done");

    tft.print("Writing plugin 9 to project.txt...");
    //save plugin 9 variables
    savePlugin("plugin9", 25);
    tft.println("Done");

    tft.print("Writing FX 1 to project.txt...");
    //save FX1 variables
    saveNoteFX("NoteFX1", 0);
    tft.println("Done");

    tft.print("Writing FX 2 to project.txt...");
    //save FX2 variables
    saveNoteFX("NoteFX2", 1);
    tft.println("Done");

    tft.print("Writing FX 3 to project.txt...");
    //save FX2 variables
    saveNoteFX("NoteFX3", 2);
    tft.println("Done");

    tft.print("Writing FX 4 to project.txt...");
    //save FX2 variables
    saveNoteFX("NoteFX4", 3);
    tft.println("Done");

    tft.print("Writing FX 5 to project.txt...");
    //save FX2 variables
    saveNoteFX("NoteFX5", 4);
    tft.println("Done");


    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening project.txt");
  }
}

void loadbutton() {
  tft.fillScreen(ILI9341_DARKGREY);
  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 0);
  // open the file for reading:
  myFile = SD.open("project.txt");
  if (myFile) {
    tft.println("opening project.txt:");

    // read from the file until there's nothing else in it:

    //load arrangment
    tft.print("Reading songarrangment from project.txt...");
    for (int ctrack = 0; ctrack < 8; ctrack++) {
      for (int cphrase = 0; cphrase < MAX_PHRASES - 1; cphrase++) {
        track[ctrack].arrangment1[cphrase] = myFile.read();
        track[ctrack].NoteOffset_graph[cphrase] = myFile.read();
        track[ctrack].Ttrckprst[cphrase] = myFile.read();
        track[ctrack].volume[cphrase] = myFile.read();
      }
    }
    tft.println("Done");

    // close the file:
    myFile.close();
    for (int ctrack = 0; ctrack < 8; ctrack++) {
      for (int cphrase = 0; cphrase < MAX_PHRASES - 1; cphrase++) {
        track[ctrack].NoteOffset[cphrase] = track[ctrack].NoteOffset_graph[cphrase] - 32;
      }
    }
    tft.println("Done");


    //load track 1
    tft.print("Reading track1 from project.txt...");
    loadTrack(trackNames_long[0], 0);
    tft.println("Done");
    //load track 2-8
    tft.print("Reading track2-8 from project.txt...");
    for (int tracks = 1; tracks < 8; tracks++) {
      loadTrack(trackNames_long[tracks], tracks);
    }
    //load mixer settings
    loadMixer();
    tft.println("Done");


    //load plugin 1 variables
    tft.print("reading plugin 1 from project.txt...");
    loadPlugin("plugin1", 17);
    tft.println("Done");

    //load plugin 2 variables
    tft.print("reading plugin 2 from project.txt...");
    loadPlugin("plugin2", 18);
    tft.println("Done");

    //load plugin 3 variables
    tft.print("reading plugin 3 from project.txt...");
    loadPlugin("plugin3", 19);
    tft.println("Done");

    //load plugin 4 variables
    tft.print("reading plugin 4 from project.txt...");
    loadPlugin("plugin4", 20);
    tft.println("Done");

    //load plugin 5 variables
    tft.print("reading plugin 5 from project.txt...");
    loadPlugin("plugin5", 21);
    tft.println("Done");

    //load plugin 6 variables
    tft.print("reading plugin 6 from project.txt...");
    loadPlugin("plugin6", 22);
    tft.println("Done");

    //load plugin 8 variables
    tft.print("reading plugin 8 from project.txt...");
    loadPlugin("plugin8", 24);
    tft.println("Done");

    //load plugin 9 variables
    tft.print("reading plugin 9 from project.txt...");
    loadPlugin("plugin9", 25);
    tft.println("Done");


    //load FX 1 variables
    tft.print("reading NoteFX 1 from project.txt...");
    loadNoteFX("NoteFX1", 0);
    tft.println("Done");

    //load FX 2 variables
    tft.print("reading NoteFX 2 from project.txt...");
    loadNoteFX("NoteFX2", 1);
    tft.println("Done");

    //load FX 3 variables
    tft.print("reading NoteFX 3 from project.txt...");
    loadNoteFX("NoteFX3", 2);
    tft.println("Done");

    //load FX 4 variables
    tft.print("reading NoteFX 4 from project.txt...");
    loadNoteFX("NoteFX4", 3);
    tft.println("Done");

    //load FX 5 variables
    tft.print("reading NoteFX 5 from project.txt...");
    loadNoteFX("NoteFX5", 4);
    tft.println("Done");

    startUpScreen();
  } else {
    // if the file didn't open, print an error:
    tft.println("error opening project.txt");
  }
}