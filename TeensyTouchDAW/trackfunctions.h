
#include <Arduino.h>
byte getValue(byte XPos, byte YPos, byte AnyValue) {
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
  static float circlePos[4];
  static float circlePos_old[4];
  static int dvalue_old[4];
  int xPos = ((XPos + 1) * 4) - 1;
  int yPos = (YPos + 1) * 3;
  circlePos[XPos] = fvalue / 63.5;

  tft.setFont(Arial_8);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue_old[XPos]);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos - 3);
  tft.print(dvalue);
  tft.fillRect(STEP_FRAME_W * (xPos), STEP_FRAME_H * (yPos + 1), STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos, STEP_FRAME_H * (yPos + 1) + 3);
  tft.print(dname);

  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos_old[XPos]) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos_old[XPos]) + 2.25), 4, ILI9341_DARKGREY);
  tft.drawCircle(STEP_FRAME_W * (xPos + 1), STEP_FRAME_H * yPos, 16, ILI9341_LIGHTGREY);
  tft.fillCircle(STEP_FRAME_W * (xPos + 1) + 16 * cos((2.5 * circlePos[XPos]) + 2.25), STEP_FRAME_H * yPos + 16 * sin((2.5 * circlePos[XPos]) + 2.25), 4, color);
  circlePos_old[XPos] = circlePos[XPos];
  dvalue_old[XPos] = dvalue;
}
void drawPot_LVL(int XPos, byte YPos, byte fvalue, int dvalue, char* dname, int color) {  //xposition, yposition, value 1-100, value to draw, name to draw, color
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
//draws a number into a rect of 2x1grids
void drawNrInRect_short(int xPos, byte yPos, int color, const char* function, byte dvalue = 255) {
  tft.fillRect(STEP_FRAME_W * xPos + 1, STEP_FRAME_H * yPos + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
  tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * 2, STEP_FRAME_H, color);
  tft.setFont(Arial_8);
  tft.setTextColor(color);
  tft.setCursor(STEP_FRAME_W * xPos + 2, STEP_FRAME_H * yPos + 4);
  tft.print(function);
  if (dvalue != 255) {
    tft.print(dvalue);
  }
}
void drawNrInRect(int xPos, byte yPos, byte dvalue, int color) {
  static int dvalue_old;
  tft.setFont(Arial_8);
  tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * 2, STEP_FRAME_H, color);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(STEP_FRAME_W * xPos + 2, STEP_FRAME_H * yPos + 4);
  tft.print(dvalue_old);
  tft.setTextColor(color);
  tft.setCursor(STEP_FRAME_W * xPos + 2, STEP_FRAME_H * yPos + 4);
  tft.print(dvalue);
  dvalue_old = dvalue;
}
void drawstepPosition(int current) {
  //#define SONG_POSITION_POINTER_Y 228
  //#define STEP_POSITION_POINTER_Y 236
  //#define GRID_POSITION_POINTER_Y 232
  //draw the songpointer positions
  for (int songPointerThickness = 0; songPointerThickness <= POSITION_POINTER_THICKNESS; songPointerThickness++) {
    for (int stepwidth = 1; stepwidth <= 16; stepwidth++) {
      tft.drawFastHLine(current * stepwidth + STEP_FRAME_W * 2, STEP_POSITION_POINTER_Y + songPointerThickness, STEP_FRAME_W, ILI9341_GREEN);
      tft.drawFastHLine((current - 1) * stepwidth + STEP_FRAME_W * 2, STEP_POSITION_POINTER_Y + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);
    }
    if (current == 0) {
      tft.drawFastHLine(STEP_FRAME_W * 17, STEP_POSITION_POINTER_Y + songPointerThickness, STEP_FRAME_W, ILI9341_DARKGREY);
    }
  }
}
void drawbarPosition() {
  //draw phrasenumber
  tft.fillRect(STEP_FRAME_W * POSITION_BAR_BUTTON + 1, 2, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 3, ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_9);
  tft.setCursor(STEP_FRAME_W * POSITION_BAR_BUTTON + 4, 3);
  tft.print(phrase);
  //draw barPosition
  for (int songPointerThickness = 0; songPointerThickness <= POSITION_POINTER_THICKNESS; songPointerThickness++) {
    tft.drawPixel(phrase + STEP_FRAME_W * 2, (SONG_POSITION_POINTER_Y + songPointerThickness), ILI9341_GREEN);
    tft.drawFastHLine((pixelphrase)*phraseSegmentLength + STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y + songPointerThickness, phraseSegmentLength, ILI9341_GREEN);
    tft.drawFastHLine((pixelphrase - 1) * phraseSegmentLength + STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y + songPointerThickness, phraseSegmentLength, ILI9341_DARKGREY);
  }
  if (phrase % 16 == 0) {
    pixelphrase = 0;
    tft.fillRect(STEP_FRAME_W * 15, GRID_POSITION_POINTER_Y, STEP_FRAME_W * 4, 4, ILI9341_DARKGREY);
    tft.fillRect(STEP_FRAME_W * 2, GRID_POSITION_POINTER_Y, STEP_FRAME_W * 1, 4, ILI9341_GREEN);
  }
}
//draws a number into a rect of 2x1grids
void drawChar(int xPos, byte yPos, char* dvalue_char, int color) {
  static char* dvalue_old_char;
  tft.setFont(Arial_8);
  tft.drawRect(STEP_FRAME_W * xPos, STEP_FRAME_H * yPos, STEP_FRAME_W * 2, STEP_FRAME_H, color);
  tft.fillRect(STEP_FRAME_W * xPos + 1, STEP_FRAME_H * yPos + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
  tft.setTextColor(color);
  tft.setCursor(STEP_FRAME_W * xPos + 4, STEP_FRAME_H * yPos + 4);
  tft.print(dvalue_char);
  dvalue_old_char = dvalue_char;
}




#define SHOW_ENCODER0 1
#define SHOW_ENCODER1 3
#define SHOW_ENCODER2 16
#define SHOW_ENCODER3 18

class classForTracks {
public:


  byte thisTrack;          //desired track for the class
  byte MIDIChannel;        //desired MIDIChannel
  byte clipToEdit = 0;     //this is the clip to edit in the sequencerviews
  byte shownOctaves = 3;   //shown Octave for the melodic tracks
  byte seqVelocity = 99;   //velocity applied in sequencerview
  byte seqMode = 0;        //active Sequencer Mode
  byte voiceCount = 0;     //desired voiceCount number for polyphony
  byte maxVoiceCount;      //sets the maximum voices for the track
  byte stepLenght = 3;     //step lenght for the step sequencerMode
  byte clockDivision = 1;  //desired clockdivision for the track


  bool muted = false;   //todo
  bool soloed = false;  //todo
  bool muteThruSolo = false;


  byte gainVol = 127;  //main volume for plugins
  byte dryVol = 100;   //dry volume
  byte FX1Vol = 0;     //volume to send to FX1 (Reverb)
  byte FX2Vol = 0;     //volume to send to FX2 (BitCrusher)
  byte FX3Vol = 0;     //volume to send to FX3 (Delay)

  //setup function called in setup() to set the tracknumber and initial MIDIChannel
  void setup(byte new_track, byte new_MIDIChannel, byte new_maxVoiceCount = 12) {
    thisTrack = new_track;
    MIDIChannel = new_MIDIChannel;
    maxVoiceCount = new_maxVoiceCount;
  }
  //draws the left navigator for the tracks
  void drawLeftNavigator(const char* sideDigit) {
    tft.fillRect(1, TRACK_FRAME_H * (thisTrack + 1) - 8, 15, TRACK_FRAME_H, trackColor[thisTrack]);  //Xmin, Ymin, Xlength, Ylength, color
    tft.setCursor(4, TRACK_FRAME_H * (thisTrack + 1) - 2);
    tft.print(sideTabDigit[thisTrack]);
  }
  //sets the desired note into the desired voice, "stepPosition" and clip
  //the step is "stepLenght" long
  void setNoteOnToStep(byte tick_s, byte voiceCount_s, byte note_s) {
    if (ctrack[thisTrack].sequence[clipToEdit].tick[tick_s].voice[voiceCount_s] == VALUE_NOTEOFF) {
      for (int touched_ticks = 0; touched_ticks < stepLenght; touched_ticks++) {
        ctrack[thisTrack].sequence[clipToEdit].tick[tick_s + touched_ticks].voice[voiceCount_s] = note_s;
      }
    }
    Serial.printf("Set: Track: %d, Clip: %d, Tick: %d, Voice: %d, Note: %d", thisTrack, clipToEdit, tick_s, voiceCount_s, note_s);
  }
  void setNoteOffToStep(byte tick_s, byte voiceCount_s, byte note_s) {
    if (ctrack[thisTrack].sequence[clipToEdit].tick[tick_s].voice[voiceCount_s] > VALUE_NOTEOFF) {
      for (int touched_ticks = 0; touched_ticks < stepLenght; touched_ticks++) {
        ctrack[thisTrack].sequence[clipToEdit].tick[tick_s + touched_ticks].voice[voiceCount_s] = note_s;
      }
    }
    Serial.printf("Set: Track: %d, Clip: %d, Tick: %d, Voice: %d, Note: %d", thisTrack, clipToEdit, tick_s, voiceCount_s, note_s);
  }
  //sets the desired note into the desired voice, "tickPosition" and clip
  void setNoteOnToTick(byte tick_s, byte voiceCount_s, byte note_s) {
    if (ctrack[thisTrack].sequence[clipToEdit].tick[tick_s].voice[voiceCount_s] == VALUE_NOTEOFF) {
      ctrack[thisTrack].sequence[clipToEdit].tick[tick_s].voice[voiceCount_s] = note_s;
    }
    Serial.printf("Set NoteON: Track: %d, Clip: %d, Tick: %d, Voice: %d, Note: %d\n", thisTrack, clipToEdit, tick_s, voiceCount_s, note_s);
  }
  void setNoteOffToTick(byte tick_s, byte voiceCount_s, byte note_s) {
    if (ctrack[thisTrack].sequence[clipToEdit].tick[tick_s].voice[voiceCount_s] > VALUE_NOTEOFF) {
      ctrack[thisTrack].sequence[clipToEdit].tick[tick_s].voice[voiceCount_s] = note_s;
    }
    Serial.printf("Set NoteOFF: Track: %d, Clip: %d, Tick: %d, Voice: %d, Note: %d\n", thisTrack, clipToEdit, tick_s, voiceCount_s, note_s);
  }
  //sets the desired MIDIChannel
  void setMIDIChannel(int encoderd) {
    MIDIChannel = constrain((MIDIChannel + encoderd), 0, MAX_CHANNELS);
    drawMIDIChannel();
    Serial.printf("Track= %d, MIDIChannel= %d\n", thisTrack, MIDIChannel);
  }
  void drawMIDIChannel() {

    //draw midichannel
    tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 0 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
    tft.setCursor(STEP_FRAME_W * 18 + 2, STEP_FRAME_H * 0 + 3);
    tft.setFont(Arial_8);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(1);
    tft.print("Ch:");
    tft.print(track[desired_track].MIDIchannel);
    tft.drawRect(STEP_FRAME_W * 18, STEP_FRAME_H * 0, STEP_FRAME_W * 2, STEP_FRAME_H, ILI9341_WHITE);
    //draw MidiCC
    for (int plugintext = 0; plugintext <= 16; plugintext++) {
      if (track[desired_instrument].MIDIchannel == plugintext) {
        tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 1 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        tft.setCursor(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 1 + 5);
        tft.setFont(Arial_8);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.print("CC");
      }
    }
    //draw PluginName
    for (int plugintext = 0; plugintext < MAX_PLUGINS; plugintext++) {
      if (track[desired_track].MIDIchannel == plugintext + 17) {
        tft.fillRect(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 1 + 1, STEP_FRAME_W * 2 - 2, STEP_FRAME_H - 2, ILI9341_DARKGREY);
        tft.setCursor(STEP_FRAME_W * 18 + 1, STEP_FRAME_H * 1 + 5);
        tft.setFont(Arial_8);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.print(pluginName[plugintext]);
      }
    }
  }
  //sets the active clip to edit in the sequencerview
  void setClipToEdit(int encoderd) {
    clipToEdit = constrain((clipToEdit + encoderd), 0, MAX_CLIPS - 1);
    drawClipToEdit();
    Serial.printf("Track= %d, clipToEdit= %d\n", thisTrack, clipToEdit);
  }
  void drawClipToEdit() {
    drawNrInRect_short(SHOW_ENCODER1, 0, ILI9341_RED, "Cl:", clipToEdit);
  }
  //sets the active voicecount(number) for polyphony
  void setVoiceCount(int encoderd) {
    voiceCount = constrain((voiceCount + encoderd), 0, maxVoiceCount);
    drawVoiceCount();
    Serial.printf("Track= %d, voiceCount= %d\n", thisTrack, voiceCount);
  }
  void drawVoiceCount() {
    drawNrInRect_short(SHOW_ENCODER2, 0, ILI9341_GREEN, "Vx", voiceCount);
  }
  //sets the desired clockdivision
  //in code we look if (Masterclock.tick % clockdivision == 0)
  //to count the track´s MIDItick upwards
  void setClockDivision(int encoderd) {
    clockDivision = constrain((clockDivision + encoderd), 1, TICKS_PER_BAR);
    drawClockDivision();
    Serial.printf("Track= %d, clockDivision= %d\n", thisTrack, clockDivision);
  }
  void drawClockDivision() {
    drawNrInRect_short(SHOW_ENCODER2, 0, ILI9341_GREEN, "cD:", clockDivision);
  }
  //sets the desired Octave for the melodictracks
  void setShownOctaves(int encoderd) {
    shownOctaves = constrain((shownOctaves + encoderd), 0, 9);
    drawShownOctave();
    Serial.printf("Track= %d, shownOctaves= %d\n", thisTrack, shownOctaves);
  }
  void drawShownOctave() {
    drawNrInRect_short(SHOW_ENCODER0, 0, ILI9341_BLUE, "Oct", shownOctaves);
  }

  //sets the desired stepLenght for the stepsequencer
  void setStepLenght(int encoderd) {
    stepLenght = constrain((stepLenght + encoderd), 1, TICKS_PER_BAR);
    drawStepLenght();
    Serial.printf("Track= %d, stepLenght= %d\n", thisTrack, stepLenght);
  }
  void drawStepLenght() {
    drawNrInRect_short(SHOW_ENCODER3, 0, ILI9341_WHITE, "SL:", stepLenght);
  }
  //sets the desired sequencer Mode
  void setSeqMode(int encoderd) {
    seqMode = constrain((seqMode + encoderd), 0, MAX_SEQMODES - 1);
    drawSeqMode();
    Serial.printf("Track= %d, seqMode= %d\n", thisTrack, seqMode);
  }
  void drawSeqMode() {
    drawNrInRect_short(SHOW_ENCODER0, 0, ILI9341_BLUE, seqModes[seqMode]);
  }
  //sets the desired Octave for the melodictracks
  void setSeqVelocity(int encoderd) {
    seqVelocity = constrain((seqVelocity + encoderd), 0, 127);
    drawSeqVelocity();
    Serial.printf("Track= %d, seqVelocity= %d\n", thisTrack, seqVelocity);
  }
  void drawSeqVelocity() {
    drawNrInRect_short(SHOW_ENCODER2, 0, ILI9341_GREEN, "V", seqVelocity);
  }



  //various "set Volumes" for the mixerpages
  void setVolGain(byte XPos, byte YPos) {

    if (enc_moved[XPos] || incomingCC_changed[XPos]) {
      incomingCC_changed[XPos] = false;
      gainVol = getValue(XPos, YPos, gainVol);
      drawPotPos(XPos, YPos, gainVol);
      if (track[thisTrack].MIDIchannel > 16) {
        gainmax[track[thisTrack].MIDIchannel - 17]->gain((float)(gainVol / 127.00));
      }
    }
  }

  void setVolDry(byte XPos, byte YPos, int encoder) {
    if (enc_moved[XPos] || incomingCC_changed[XPos]) {
      incomingCC_changed[XPos] = false;
      dryVol = getValue(XPos, YPos, dryVol);
      drawPotPos(XPos, YPos, dryVol);
      if (track[thisTrack].MIDIchannel > 16) {
        dryVolume[track[thisTrack].MIDIchannel - 17]->gain((float)(dryVol / 127.00));
      }
    }
  }
  void setVolFX1(byte XPos, byte YPos, int encoder) {
    if (enc_moved[XPos] || incomingCC_changed[XPos]) {
      incomingCC_changed[XPos] = false;
      FX1Vol = getValue(XPos, YPos, FX1Vol);
      drawPotPos(XPos, YPos, FX1Vol);
      if (track[thisTrack].MIDIchannel > 16) {
        FX1Volume[track[thisTrack].MIDIchannel - 17]->gain((float)(FX1Vol / 127.00));
      }
    }
  }
  void setVolFX2(byte XPos, byte YPos, int encoder) {
    if (enc_moved[XPos] || incomingCC_changed[XPos]) {
      incomingCC_changed[XPos] = false;
      FX2Vol = getValue(XPos, YPos, FX2Vol);
      drawPotPos(XPos, YPos, FX2Vol);
      if (track[thisTrack].MIDIchannel > 16) {
        FX2Volume[track[thisTrack].MIDIchannel - 17]->gain((float)(FX2Vol / 127.00));
      }
    }
  }
  void setVolFX3(byte XPos, byte YPos, int encoder) {
    if (enc_moved[XPos] || incomingCC_changed[XPos]) {
      incomingCC_changed[XPos] = false;
      FX3Vol = getValue(XPos, YPos, FX3Vol);
      drawPotPos(XPos, YPos, FX3Vol);
      if (track[thisTrack].MIDIchannel > 16) {
        FX3Volume[track[thisTrack].MIDIchannel - 17]->gain((float)(FX3Vol / 127.00));
      }
    }
  }
  void drawPotPos(byte XPos, byte YPos, byte value) {
    drawPot(XPos, YPos, value, value, trackNames_short[thisTrack], trackColor[thisTrack]);
  }
};

class AudioRecorders {
public:
  byte selected_file;
  byte selected_gain;
  bool monitoring;
  //sets the desired RAW file
  void setRAWfile() {
    if (enc_moved[0] || incomingCC_changed[0]) {
      selected_file = getValue(0, 0, selected_file);
      drawPot(0, 0, selected_file, selected_file, "RAW", ILI9341_OLIVE);
    }
  }
  //sets the desired recording Volume
  void setVolume() {
    if (enc_moved[1] || incomingCC_changed[1]) {
      incomingCC_changed[1] = false;
      selected_gain = getValue(1, 0, selected_gain);
      amp1.gain(selected_gain / 64.00);
      drawPot(1, 0, selected_gain, selected_gain, "Volume", ILI9341_OLIVE);
    }
  }
  //sets the Monitor to active
  void setMonitor() {
    if (enc_moved[0] || incomingCC_changed[0]) {
      incomingCC_changed[0] = false;
      monitoring = constrain(getValue(0, 1, monitoring), 0, 1);
      if (monitoring == 1) {
        mixer11.gain(1, 1);
      }
      if (monitoring == 0) {
        mixer11.gain(1, 0);
      }
      drawActiveRect(CTRL_COL_0, CTRL_ROW_1, 2, 2, monitoring, "Listen", ILI9341_ORANGE);
    }
  }
  //draws a simple Oscilloscope
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
  //draws the volume graph
  void drawAudioPot(float peak) {
    //level meter
    static int peakIn;
    peakIn = peak * 127;
    if (peakIn > 110) {
      drawPot_LVL(3, 0, peakIn, peakIn, "Meter", ILI9341_RED);
    } else {
      drawPot_LVL(3, 0, peakIn, peakIn, "Meter", ILI9341_OLIVE);
    }
  }
};


class Clock {
public:
  uint32_t _next_clock = 0;
  uint32_t _clock = 160;
  uint32_t MIDItick = -1;
  uint32_t stepTick = -1;
  uint32_t barTick = -1;
  byte startOfLoop = 0;
  byte endOfLoop = 0;
  bool seq_run = false;
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
    draw_tempo();
    Serial.printf("tempo= %d\n", tempo);
  }
  void draw_tempo() {
    drawNrInRect_short(11, 0, ILI9341_WHITE, "", master_tempo);
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
    } else {
      MIDItick = 0;
      stepTick = 0;
      barTick = 0;
    }
    return false;
  }
  //returns the actual MIDItick count
  uint32_t get_MIDItick() {
    return MIDItick;
  }


  //returns the actual STEPtick count
  uint32_t get_stepTick() {
    return MIDItick % 6;
  }
  //returns if the clock is on a STEP
  bool is_tick_on_step() {
    return MIDItick % 6 == 0;
  }


  uint32_t get_barTick() {  //returns the actual BARtick count
    return MIDItick % TICKS_PER_BAR;
  }
  bool is_tick_on_bar() {
    return MIDItick % TICKS_PER_BAR == 0;
  }

  //sets the startpoint of loop
  void setStartOfLoop(int encoderd) {
    startOfLoop = constrain((startOfLoop + encoderd), 0, MAX_PHRASES - 2);
    drawStartOfLoop();
    Serial.printf("startOfLoop= %d\n", startOfLoop);
  }
  void drawStartOfLoop() {
    drawNrInRect_short(SHOW_ENCODER2, 0, ILI9341_GREEN, "S", startOfLoop);
  }
  //sets the endpoint of loop
  void setEndOfLoop(int encoderd) {
    endOfLoop = constrain((endOfLoop + encoderd), 0, MAX_PHRASES - 1);
    drawEndOfLoop();
    Serial.printf("endOfLoop= %d\n", endOfLoop);
  }
  void drawEndOfLoop() {
    drawNrInRect_short(SHOW_ENCODER3, 0, ILI9341_WHITE, "E", endOfLoop);
  }
  //draws all the timerelated stuff for the sequencer
  void drawPositionPointers() {
    if (MIDItick % 6 == 0) {
      stepTick++;
      if (stepTick == NUM_STEPS) {
        stepTick = 0;
      }
      drawstepPosition(stepTick);
    }
    if (MIDItick % TICKS_PER_BAR == 0) {
      barTick++;
      if (barTick == 16) {
        barTick == 0;
      }
      drawbarPosition();
    }
  }
};

class Cursors {
public:
};

class externalControllers {
public:
  //Potentiometer
  byte extCC[4];            //sets the CC Number sent from the controller
  byte extCCIn[4];          //sets the CC Value sent from the controller
  bool extCCIn_changed[4];  //a bool to check if ccIn has changed, needs to turned off in code

  //controllButtons
  bool extButton[16];
  bool extGrid[64];
  //assign the midi cc value that will control the encoders
  void assignExternalInputCCs(byte ext0, byte ext1, byte ext2, byte ext3) {
    extCC[0] = ext0;
    extCC[1] = ext1;
    extCC[2] = ext2;
    extCC[3] = ext3;
  }
  //assign the 16 controllbuttons for navigation and transport
  void assignExternalButtons(byte pos, byte button) {
    extButton[pos] = button;
  }
  //assign the 64 gridbuttons for selecting clips and stuff
  void assignExternalGrid(byte pos, byte button) {
    extGrid[pos] = button;
  }
};
