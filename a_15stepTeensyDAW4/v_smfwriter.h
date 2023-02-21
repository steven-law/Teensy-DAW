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
    void addControlChange(unsigned int deltaticks, byte controlNumber, byte controlValue, byte channel);
    void addPitchBend(unsigned int deltaticks, int pitchValue, byte channel);
    void addPitchBend(unsigned int deltaticks, double pitchValue, byte channel);

    void addSetTempo(unsigned int deltaticks, double tempo);

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
    void write_buf_byte(int a);
    void write_buf_var_int(unsigned int data);
};

#endif // NEWDIGATE_MIDI_SMF_WRITER_SMFWRITER_H