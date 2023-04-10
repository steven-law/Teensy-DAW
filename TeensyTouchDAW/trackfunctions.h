
#include <Arduino.h>
byte getValue(byte XPos, byte YPos, byte AnyValue ) {
  if (enc_moved[XPos]) {
    AnyValue = constrain(AnyValue + encoded[XPos], 0, 127);
  } else if (incomingCC_changed[XPos]) {
    AnyValue = incomingCC[XPos];
    incomingCC_changed[XPos] = false;
  }
  return AnyValue;
}
void drawPot(int XPos, byte YPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color
                                                                                      //drawPot Variables
  static float circlePos;
  static float circlePos_old;
  static int dvalue_old;
  int xPos = ((XPos + 1) * 4) - 1;
  int yPos = (YPos + 1) * 3;
  circlePos = fvalue / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.setCursor(STEP_FRAME_W * xPos, STEP_FRAME_H * (yPos + 1) + 3);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos) + 2.25), 4, color);
  circlePos_old = circlePos;
  dvalue_old = dvalue;
}
void drawPot_2(int XPos, byte YPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color
                                                                                        //drawPot Variables
  static float circlePos_2;
  static float circlePos_old_2;
  static int dvalue_old_2;
  int yPos = (YPos + 1) * 3;
  int xPos = ((XPos + 1) * 4) - 1;
  circlePos_2 = fvalue / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old_2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.setCursor(STEP_FRAME_W * xPos, STEP_FRAME_H * (yPos + 1) + 3);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old_2) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old_2) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_2) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_2) + 2.25), 4, color);
  circlePos_old_2 = circlePos_2;
  dvalue_old_2 = dvalue;
}
void drawPot_3(int XPos, byte YPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color
  //drawPot Variables
  static float circlePos_3;
  static float circlePos_old_3;
  static int dvalue_old_3;
  int yPos = (YPos + 1) * 3;
  int xPos = ((XPos + 1) * 4) - 1;
  circlePos_3 = fvalue / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old_3);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.setCursor(STEP_FRAME_W * xPos, STEP_FRAME_H * (yPos + 1) + 3);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old_3) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old_3) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_3) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_3) + 2.25), 4, color);
  circlePos_old_3 = circlePos_3;
  dvalue_old_3 = dvalue;
}
void drawPot_4(int XPos, byte YPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color
                                                                                        //drawPot Variables
  static float circlePos_4;
  static float circlePos_old_4;
  static int dvalue_old_4;
  int yPos = (YPos + 1) * 3;
  int xPos = ((XPos + 1) * 4) - 1;
  circlePos_4 = fvalue / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old_4);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.setCursor(STEP_FRAME_W * xPos, STEP_FRAME_H * (yPos + 1) + 3);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old_4) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old_4) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_4) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_4) + 2.25), 4, color);
  circlePos_old_4 = circlePos_4;
  dvalue_old_4 = dvalue;
}
//draw a rectangle, if the state is high the rect gets filled
void drawActiveRect(int xPos, byte yPos, byte xsize, byte ysize, bool state, char* name, int color) {
  if (state) {
    tft.fillRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * xsize, STEP_FRAME_W * ysize, color);
    tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * xsize, STEP_FRAME_W * ysize, color);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 3);
    tft.print(name);
  }
  if (!state) {
    tft.fillRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * xsize, STEP_FRAME_W * ysize, ILI9341_DARKGREY);
    tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * xsize, STEP_FRAME_W * ysize, color);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 3);
    tft.print(name);
  }
}

class drumtrack {
public:
  const int DTrack = 0;
  void setDrumnotes(int YPos) {

    for (int i = 0; i < 12; i++) {
      drumnote[YPos] = constrain((drumnote[YPos] + encoded[0]), 0, 99);
      tft.fillRect(STEP_FRAME_W, STEP_FRAME_H * i + STEP_FRAME_H, STEP_FRAME_W, STEP_FRAME_H, trackColor[0]);
      tft.setCursor(18, STEP_FRAME_H * i + 18);
      tft.setFont(Arial_8);
      tft.setTextColor(ILI9341_BLACK);
      tft.setTextSize(1);
      tft.print(drumnote[i]);
    }
  }
};


class classForTracks {
public:
  byte MixTrack;

  bool mute = false;
  bool solo = false;


  byte gainVol = 127;
  byte dryVol = 100;
  byte FX1Vol = 0;
  byte FX2Vol = 0;
  byte FX3Vol = 0;
  
  void setup(byte new_track) {
    MixTrack = new_track;
  }

  void drawLeftNavigator(const char* sideDigit, uint16_t color) {
    tft.fillRect(1, TRACK_FRAME_H * (MixTrack + 1) - 8, 15, TRACK_FRAME_H, color);  //Xmin, Ymin, Xlength, Ylength, color
    tft.setCursor(4, TRACK_FRAME_H * (MixTrack + 1) - 2);
    tft.print(sideDigit);
  }

  void setVolGain(byte XPos, byte YPos) {

    if (enc_moved[XPos] || incomingCC_changed[XPos]) {
      incomingCC_changed[XPos] = false;
      gainVol = getValue(XPos, YPos, gainVol);
      drawPotPos(XPos, YPos, gainVol);
      if (track[MixTrack].MIDIchannel > 16) {
        gainmax[track[MixTrack].MIDIchannel - 17]->gain((float)(gainVol / 127.00));
      }
    }
  }
  void setVolDry(byte XPos, byte YPos, int encoder) {
    if (enc_moved[XPos] || incomingCC_changed[XPos]) {
      incomingCC_changed[XPos] = false;
      dryVol = getValue(XPos, YPos);
      drawPotPos(XPos, YPos, dryVol);
      if (track[MixTrack].MIDIchannel > 16) {
        dryVolume[track[MixTrack].MIDIchannel - 17]->gain((float)(dryVol / 127.00));
      }
    }
  }
  void setVolFX1(byte XPos, byte YPos, int encoder) {
    if (enc_moved[XPos] || incomingCC_changed[XPos]) {
      incomingCC_changed[XPos] = false;
      FX1Vol = getValue(XPos, YPos);
      drawPotPos(XPos, YPos, FX1Vol);
      if (track[MixTrack].MIDIchannel > 16) {
        FX1Volume[track[MixTrack].MIDIchannel - 17]->gain((float)(FX1Vol / 127.00));
      }
    }
  }
  void setVolFX2(byte XPos, byte YPos, int encoder) {
    if (enc_moved[XPos] || incomingCC_changed[XPos]) {
      incomingCC_changed[XPos] = false;
      FX2Vol = getValue(XPos, YPos);
      drawPotPos(XPos, YPos, FX2Vol);
      if (track[MixTrack].MIDIchannel > 16) {
        FX2Volume[track[MixTrack].MIDIchannel - 17]->gain((float)(FX2Vol / 127.00));
      }
    }
  }
  void setVolFX3(byte XPos, byte YPos, int encoder) {
    if (enc_moved[XPos] || incomingCC_changed[XPos]) {
      incomingCC_changed[XPos] = false;
      FX3Vol = getValue(XPos, YPos);
      drawPotPos(XPos, YPos, FX3Vol);
      if (track[MixTrack].MIDIchannel > 16) {
        FX3Volume[track[MixTrack].MIDIchannel - 17]->gain((float)(FX3Vol / 127.00));
      }
    }
  }
  void drawPotPos(byte XPos, byte YPos, byte value) {
    drawPot(XPos, YPos, value, value, trackNames_short[MixTrack], trackColor[MixTrack]);
  }
};

class AudioRecorders {
public:
  byte selected_file;
  byte selected_gain;
  bool monitoring;
  void setRAWfile() {
    //RAW File
    if (enc_moved[0] || incomingCC_changed[0]) {
      selected_file = getValue(0, 0);
      drawPot(0, 0, selected_file, selected_file, "RAW", ILI9341_OLIVE);
    }
  }
  void setVolume() {
    //rec volume
    if (enc_moved[1] || incomingCC_changed[1]) {
      incomingCC_changed[1] = false;
      selected_gain = getValue(1, 0);
      amp1.gain(selected_gain / 64.00);
      drawPot_2(1, 0, selected_gain, selected_gain, "Volume", ILI9341_OLIVE);
    }
  }
  void setMonitor() {

    if (enc_moved[0] || incomingCC_changed[0]) {
      incomingCC_changed[0] = false;
      monitoring = constrain(getValue(0, 1), 0, 1);
      if (monitoring == 1) {
        mixer11.gain(1, 1);
      }
      if (monitoring == 0) {
        mixer11.gain(1, 0);
      }
      drawActiveRect(CTRL_COL_0, CTRL_ROW_1, 2, 2, monitoring, "Listen", ILI9341_ORANGE);
    }
  }
  void drawOscilloscope(float peak) {
    static byte AudioYdot = 255;
    static int posX_old = 288;
    static int posY_old = 214;
    if (millis() % 1 == 0) {
      AudioYdot++;
    }
    if (millis() % 2 == 0) {
      int AudioYpos = ((1 - peak) * WAVEHEIGHT) + YPOS_OFFSET;
      int AudioXpos = AudioYdot + XPOS_OFFSET;
      tft.drawFastVLine(AudioXpos + 3, YPOS_OFFSET, WAVEHEIGHT + 1, ILI9341_DARKGREY);  //(x, y-start, y-length, color)
      tft.drawFastVLine(AudioXpos + 2, YPOS_OFFSET, WAVEHEIGHT + 1, ILI9341_DARKGREY);  //(x, y-start, y-length, color)
      tft.drawFastVLine(AudioXpos + 1, YPOS_OFFSET, WAVEHEIGHT + 1, ILI9341_DARKGREY);  //(x, y-start, y-length, color)
      tft.drawLine(posX_old, posY_old, AudioXpos, AudioYpos, ILI9341_WHITE);
      //Serial.print(AudioXpos);
      //Serial.print("-");
      //Serial.println(AudioYpos);
      //Serial.println(peak);

      if (AudioYdot >= 254) {
        AudioYdot = 0;
        posX_old = 32;
        posY_old = 214;
      } else {
        posX_old = AudioXpos;
        posY_old = AudioYpos;
      }
    }
  }
  void drawAudioPot(float peak) {
    //level meter
    static int peakIn;
    peakIn = peak * 127;
    if (peakIn > 110) {
      drawPot(3, 0, peakIn, peakIn, "Meter", ILI9341_RED);
    } else {
      drawPot_4(3, 0, peakIn, peakIn, "Meter", ILI9341_OLIVE);
    }
  }
};


class Clock {
public:
  uint32_t _next_clock = 0;
  uint32_t _clock = 160;
  uint32_t MIDItick = -1;
  uint32_t step_tick = -1;
  uint32_t bar_tick = -1;
  bool seq_run = false;
  bool seq_rec = false;
  bool playing = false;
  byte master_tempo = 120;
  int syncPin = -1;
  uint32_t previousMillis_clock = 0;

  //setup function, so we can put in an analog sync Output (Optional)
  void setup(int new_syncPin) {
    syncPin = new_syncPin;
    if (syncPin >= 0) {            //this "IF" is used if we want a variable to be OPTIONAL assigned
      digitalWrite(syncPin, LOW);  //if we want to have an optional sync out pin
      pinMode(syncPin, OUTPUT);
    }
  }

  bool is_playing() {
    return playing;
  }
  void set_playing(bool p = false) {  //if we want to start the clock use, "clock.is_playing(true);"
    this->playing = p;
  }
  void set_tempo(int tempo) {  //set the tempo with "clock.setTempo(tempo);"
    master_tempo = tempo;
    // midi clock messages should be sent 24 times
    // for every quarter note
    _clock = 60000000L / tempo / 24;
  }
  int get_tempo() {
    return master_tempo;
  }
  void send_MIDIclock() {
    //spit out a MIDItick
    usbMIDI.sendRealTime(usbMIDI.Clock);  //send a midiclock to usb host
    MIDI.sendRealTime(0xF8);              //send a midiclock to serial midi
  }
  void send_sync_clock() {

    //spit out a MIDItick
    if (syncPin >= 0) {
      digitalWrite(syncPin, HIGH);
      uint32_t currentMillis = millis();
      if (currentMillis - previousMillis_clock >= 10) {
        previousMillis_clock = currentMillis;
        digitalWrite(syncPin, LOW);
      }
    }
  }
  bool process_MIDItick() {

    if (playing) {
      //if the clock is running
      if (msecsclock >= _clock) {  //compare clockvalues
        MIDItick++;                //spit out a MIDItick
        send_MIDIclock();
        msecsclock = 0;

        return true;
      }
    }
    return false;
  }
  uint32_t get_MIDItick() {  //returns the actual MIDItick count
    return MIDItick;
  }



  uint32_t get_step_tick() {  //returns the actual STEPtick count
    return MIDItick % 6;
  }
  bool is_tick_on_step() {
    return MIDItick % 6 == 0;
  }


  uint32_t get_bar_tick() {  //returns the actual BARtick count
    return MIDItick % 96;
  }
  bool is_tick_on_bar() {
    return MIDItick % 96 == 0;
  }
};