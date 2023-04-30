//file for the audio recorder, working on the class to be finished


void recorder_settings() {
  amp1.gain(1);
}


void recorder_Page_Static() {
  clearWorkSpace();


  drawPot(0, 0, AudioRecorder.selected_file, AudioRecorder.selected_file, "RAW", ILI9341_OLIVE);
  drawPot(1, 0, AudioRecorder.selected_gain, AudioRecorder.selected_gain, "Volume", ILI9341_OLIVE);
  AudioRecorder.drawAudioPot(0);

  drawActiveRect(CTRL_COL_0, CTRL_ROW_1, 2, 2, AudioRecorder.monitoring, "Listen", ILI9341_ORANGE);
  drawActiveRect(CTRL_COL_1, CTRL_ROW_1, 2, 2, audio_rec_now, "Rec", ILI9341_RED);
}
#define XPOS_OFFSET 32
#define YPOS_OFFSET 150
#define WAVEHEIGHT 64

void recorder_Page1_Dynamic() {
  float peaker;
  static int posX_old = 288;
  static int posY_old = 214;
  if (audio_rec_now) {
    continueRecording();
    drawActiveRect(CTRL_COL_1, CTRL_ROW_1, 2, 2, audio_rec_now, "Rec", ILI9341_RED);
  }

  if (peak1.available()) {
    peaker = peak1.read();
    //Serial.println(peaker, 3);
    //level meter
    if (millis() % 100 == 0) {
      AudioRecorder.drawAudioPot(peaker);
    }
    //oscilloscope
    if (lastPotRow == 2) {
      AudioRecorder.drawOscilloscope(peaker);
    }
  }

  switch (lastPotRow) {
    case 0:
      //RAW File
      AudioRecorder.setRAWfile();
      //rec volume
      AudioRecorder.setVolume();
      break;
    case 1:
      //monitor
      AudioRecorder.setMonitor();
      break;
    case 2:
      break;
    case 3:
      break;
  }
  if (ts.touched() || button[15]) {
    readTouchinput();
  }
}


void startRecording() {

  Serial.println("startRecording");
  sprintf(_RecFile, "%d.RAW\0", AudioRecorder.selected_file);
  if (SD.exists(_RecFile)) {
    // The SD library writes new data to the end of the
    // file, so to start a new recording, the old file
    // must be deleted before new data is written.
    SD.remove(_RecFile);
  }
  frec = SD.open(_RecFile, FILE_WRITE);
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