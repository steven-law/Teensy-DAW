#ifndef NEWDIGATE_MIDI_SMF_WRITER_SMFWRITER_H
#define NEWDIGATE_MIDI_SMF_WRITER_SMFWRITER_H

#include <Arduino.h>
#include <SD.h>

class SmfWriter
{
  public:
    SmfWriter();
    void setFilename(const char* filename);
    char* getFilename();
    void writeHeader();
    void addEvent(unsigned int deltaticks, byte *data, unsigned int length);
    void addNoteOnEvent(unsigned int deltaticks, byte channel, byte key, byte velocity);
    void addNoteOffEvent(unsigned int deltaticks, byte channel, byte key);
    void addProgramChange(unsigned int deltaticks, byte programNumber, byte channel);
    void addControlChange(unsigned int deltaticks, byte controlNumber, byte controlValue, byte channel);
    void addPitchBend(unsigned int deltaticks, int pitchValue, byte channel);
    void addPitchBend(unsigned int deltaticks, double pitchValue, byte channel);
    void addAfterTouch(unsigned int deltaticks, byte pressure, byte channel);
    void addAfterTouch(unsigned int deltaticks, byte noteNumber, byte pressure, byte channel);
    void addKeySignature(unsigned int deltaticks, byte sf, uint8_t mi );
    void addTimeSignature(unsigned int deltaticks, byte nn, byte dd, byte cc, byte bb);
    void addSMPTEOffset(unsigned int deltaticks, byte hr, byte mn, byte se, byte fr, byte ff );
    void addSetTempo(unsigned int deltaticks, double tempo);
    void addEndofTrack(unsigned int deltaticks, byte trackNumber);
    void addSequenceNumber(unsigned int deltaticks, byte sequenceNumber);
    void addSysEx(unsigned int deltaticks, void *data, unsigned int length);
    void addMetaText(unsigned int deltaticks, byte textType, const char* text); 
    void addTextEvent(unsigned int deltaticks, const char* text);       // FF 01 
    void addCopyrightNotice(unsigned int deltaticks, const char* text); // FF 02
    void addTrackName(unsigned int deltaticks, const char* text);       // FF 03 
    void addInstrumentName(unsigned int deltaticks, const char* text);  // FF 04
    void addLyricText(unsigned int deltaticks, const char* text);       // FF 05
    void addMarkerText(unsigned int deltaticks, const char* text);      // FF 06
    void addCuePointText(unsigned int deltaticks, const char* text);    // FF 07 
    void flush();
    
    static unsigned int get_microseconds_per_tick(double bpm) {
        double micros_per_beat = 60000000.0 / bpm;
        unsigned int micros_per_tick = micros_per_beat / 480;
        return micros_per_tick;
    }
  private:
    byte _buffer[50];
    byte _bufferPos = 0;
    char _filename[80];
    unsigned long trackSize = 0;

    void write_buf_int(unsigned int data);
    void write_buf_byte(byte a);
    void write_buf_var_int(unsigned int data);
};

#endif // NEWDIGATE_MIDI_SMF_WRITER_SMFWRITER_H