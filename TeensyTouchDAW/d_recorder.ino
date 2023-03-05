void recorder_settings() {
  amp1.gain(audio_rec_volume_graph);
}

void recorder_Page_Static() {
  clearWorkSpace();
  //place here the (copied!) shown controls for your plugin
  //if needed draw selecting pages buttons
  //draw_sub_page_buttons(n); //max 4

  drawPot(CTRL_COL_0, 0, audio_rec_selected_file_graph, audio_rec_selected_file, "RAW", ILI9341_OLIVE);
  drawPot(CTRL_COL_1, 0, audio_rec_volume_graph, audio_rec_volume, "Volume", ILI9341_OLIVE);
  drawPot_4(CTRL_COL_3, 0, audio_rec_peak_graph, 0, "Meter", ILI9341_OLIVE);

  drawActiveRect(CTRL_COL_0, CTRL_ROW_1, 2, 2, audio_rec_listen, "Listen", ILI9341_ORANGE);
  drawActiveRect(CTRL_COL_1, CTRL_ROW_1, 2, 2, audio_rec_now, "Rec", ILI9341_RED);
}

void recorder_Page1_Dynamic() {
  if (audio_rec_now) {
    continueRecording();
    drawActiveRect(CTRL_COL_1, CTRL_ROW_1, 2, 2, audio_rec_now, "Rec", ILI9341_RED);
  }

  if (peak1.available()) {
    //level meter
    if (millis() % 100 == 0) {
      audio_rec_peak_graph = peak1.read() * 127;
      drawPot_4(CTRL_COL_3, 0, audio_rec_peak_graph, audio_rec_peak_graph, "Meter", ILI9341_OLIVE);
    }
  }


  switch (lastPotRow) {
    case 0:

      //RAW File
      if (enc_moved[0]) {
        audio_rec_selected_file_graph = constrain((audio_rec_selected_file_graph + encoded[0]), 0, 127);
        audio_rec_selected_file = audio_rec_selected_file_graph;
        drawPot(CTRL_COL_0, lastPotRow, audio_rec_selected_file_graph, audio_rec_selected_file, "RAW", ILI9341_OLIVE);
      }
      /*if (abs(Potentiometer[0] - audio_rec_selected_file_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        if (audio_rec_selected_file_graph != Potentiometer[0]) {
          audio_rec_selected_file_graph = Potentiometer[0];
          audio_rec_selected_file = map(audio_rec_selected_file_graph, 0, 127, 0, MAX_RAW_FILES);
          drawPot(CTRL_COL_0, lastPotRow, audio_rec_selected_file_graph, audio_rec_selected_file, "RAW", ILI9341_OLIVE);
        }
      }*/
      //rec volume
      if (enc_moved[1]) {
        audio_rec_volume_graph = constrain((audio_rec_volume_graph + encoded[1]), 0, 127);
        audio_rec_volume = audio_rec_volume_graph / 64.00;
        amp1.gain(audio_rec_volume);
        drawPot_2(CTRL_COL_1, lastPotRow, audio_rec_volume_graph, audio_rec_volume_graph, "Volume", ILI9341_OLIVE);
      }
      /*if (abs(Potentiometer[1] - audio_rec_volume_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        if (audio_rec_volume_graph != Potentiometer[1]) {
          audio_rec_volume_graph = Potentiometer[1];
          audio_rec_volume = audio_rec_volume_graph / 64.00;
          amp1.gain(audio_rec_volume);
          drawPot_2(CTRL_COL_1, lastPotRow, audio_rec_volume_graph, audio_rec_volume_graph, "Volume", ILI9341_OLIVE);
        }
      }*/


      break;
    case 1:
      //monitor
      if (enc_moved[0]) {
        audio_rec_listen_graph = constrain((audio_rec_listen_graph + encoded[0]), 0, 1);
        if (audio_rec_listen_graph == 1) {
          audio_rec_listen = true;
          mixer11.gain(1, 1);
        }
        if (audio_rec_listen_graph == 0) {
          audio_rec_listen = false;
          mixer11.gain(1, 0);
        }
        drawActiveRect(CTRL_COL_0, CTRL_ROW_1, 2, 2, audio_rec_listen, "Listen", ILI9341_ORANGE);
      }

      /*if (abs(Potentiometer[0] - audio_rec_listen_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
        if (audio_rec_listen_graph != Potentiometer[0]) {
          audio_rec_listen_graph = Potentiometer[0];
          if (audio_rec_listen_graph > 64) {
            audio_rec_listen = true;
            mixer11.gain(1, 1);
          }
          if (audio_rec_listen_graph < 64) {
            audio_rec_listen = false;
            mixer11.gain(1, 0);
          }
          drawActiveRect(CTRL_COL_0, CTRL_ROW_1, 2, 2, audio_rec_listen, "Listen", ILI9341_ORANGE);
        }
      }*/

      /* if (abs(Potentiometer[1] - audio_rec_rec_graph) < POTPICKUP) {  // Potiwert muss in die Naehe des letzten Wertes kommen
          if (audio_rec_rec_graph != Potentiometer[1]) {
            audio_rec_rec_graph = Potentiometer[1];
            if (audio_rec_rec_graph > 64) {
              audio_rec_rec = true;
              audio_rec_now = false;
              drawActiveRect(CTRL_COL_1, CTRL_ROW_1, 2, 1, audio_rec_rec, "Rec", ILI9341_ORANGE);
            }
            if (audio_rec_rec_graph < 64) {
              audio_rec_rec = false;
              audio_rec_now = false;
              drawActiveRect(CTRL_COL_1, CTRL_ROW_1, 2, 2, audio_rec_now, "Rec", ILI9341_RED);
            }
          }
        }*/
      // }
      break;
    case 2:

      break;
    case 3:

      break;
  }
  if (ts.touched() || button[15]) {

    if (gridTouchY >= 2 && gridTouchY <= 4) {
      lastPotRow = 0;
    }

    if (gridTouchY >= 5 && gridTouchY <= 7) {
      lastPotRow = 1;
      if (gridTouchX == 3 || gridTouchX == 4) {
        if (audio_rec_listen_graph == 1) {
          audio_rec_listen = true;
          mixer11.gain(1, 1);
        }
        if (audio_rec_listen_graph == 0) {
          audio_rec_listen = false;
          mixer11.gain(1, 0);
        }
        drawActiveRect(CTRL_COL_0, CTRL_ROW_1, 2, 2, audio_rec_listen, "Listen", ILI9341_ORANGE);
      }
    }

    if (gridTouchY >= 8 && gridTouchY <= 10) {
      lastPotRow = 2;
    }
    if (gridTouchY >= 11 && gridTouchY <= 13) {
      lastPotRow = 3;
    }
  }
}


void startRecording() {
  Serial.println("startRecording");
  if (SD.exists(RAW_files[audio_rec_selected_file])) {
    // The SD library writes new data to the end of the
    // file, so to start a new recording, the old file
    // must be deleted before new data is written.
    SD.remove(RAW_files[audio_rec_selected_file]);
  }
  frec = SD.open(RAW_files[audio_rec_selected_file], FILE_WRITE);
  if (frec) {
    queue1.begin();
    audio_rec_now = true;
  }
}

void continueRecording() {
  if (queue1.available() >= 2) {
    byte buffer[512];
    // Fetch 2 blocks from the audio library and copy
    // into a 512 byte buffer.  The Arduino SD library
    // is most efficient when full 512 byte sector size
    // writes are used.
    memcpy(buffer, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    memcpy(buffer + 256, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    // write all 512 bytes to the SD card
    //elapsedMicros usec = 0;
    frec.write(buffer, 512);
    // Uncomment these lines to see how long SD writes
    // are taking.  A pair of audio blocks arrives every
    // 5802 microseconds, so hopefully most of the writes
    // take well under 5802 us.  Some will take more, as
    // the SD library also must write to the FAT tables
    // and the SD card controller manages media erase and
    // wear leveling.  The queue1 object can buffer
    // approximately 301700 us of audio, to allow time
    // for occasional high SD card latency, as long as
    // the average write time is under 5802 us.
    //Serial.print("SD write, us=");
    //Serial.println(usec);
  }
}

void stopRecording() {
  Serial.println("stopRecording");
  queue1.end();

  while (queue1.available() > 0) {
    frec.write((int*)queue1.readBuffer(), 256);
    queue1.freeBuffer();
  }
  frec.close();
  audio_rec_now = false;
  audio_rec_rec = false;
}