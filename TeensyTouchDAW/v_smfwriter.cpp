#include "v_smfwriter.h"

const byte header[] = {
  0x4d, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06,
  0x00, 0x00,  // single-track format
  0x00, 0x01,  // one track
  0x00, 0x10,  // 16 ticks per quarter
  0x4d, 0x54, 0x72, 0x6B
};

SmfWriter::SmfWriter() {
}

char* SmfWriter::getFilename() {
  return &_filename[0];
}

void SmfWriter::write_buf_int(unsigned int data) {
  //Serial.printf("%x\n", data);
  byte b = data >> 24;
  //Serial.printf("%x.", b);
  write_buf_byte(b);

  b = data >> 16;
  //Serial.printf("%x.", b);
  write_buf_byte(b);

  b = data >> 8;
  //Serial.printf("%x.", b);
  write_buf_byte(b);

  b = data;
  //Serial.printf("%x\n", b);
  write_buf_byte(b);
}

void SmfWriter::write_buf_byte(int b) {
  if (_bufferPos > 40) {
    flush();
  }
  _buffer[_bufferPos++] = b;
}

void SmfWriter::setFilename(const char* filename) {
  flush();

  sprintf(_filename, "%s.mid\0", filename);

  if (SD.exists(_filename)) {
    SD.remove(_filename);
  }
  //Serial.printf("using filename '%s'\n", _filename);
}

void SmfWriter::writeHeader() {
  // first 18 bytes of static header
  for (unsigned int i = 0; i < 18; i++)
    write_buf_byte(header[i]);

  // we write zero to the length of the midi track to begin with
  write_buf_int(0);
  flush();
}

void SmfWriter::write_buf_var_int(unsigned int deltaticks) {
  if (deltaticks < 128) {
    write_buf_byte(deltaticks);
    trackSize += 1;
    return;
  }

  uint16_t lengthFieldSize = 0;
  byte b[4];

  // read least signficicant bytes first
  for (int i = 3; i >= 0; i--) {
    b[i] = (int)(deltaticks & 0x7f);
    if (i < 3)  // set the bit that indicates another byte still to follow... except on the least significant byte
      b[i] |= 0x80;
    deltaticks >>= 7;
    lengthFieldSize++;
    if (deltaticks < 1)
      break;
  }

  for (int i = 0; i < lengthFieldSize; i++) {
    write_buf_byte(b[4 - lengthFieldSize + i]);
    trackSize += 1;
  }
}

void SmfWriter::addEvent(unsigned int deltaticks, byte* data, unsigned int length) {
  write_buf_var_int(deltaticks);
  for (int i = 0; i < length; i++) {
    write_buf_byte(data[i]);
  }
  trackSize += length;
}

void SmfWriter::addNoteOnEvent(unsigned int deltaticks, byte channel, byte key, byte velocity) {
  byte statusByte = 0x90 | channel;
  byte data[3] = { statusByte, key, velocity };
  addEvent(deltaticks, data, 3);
 // Serial.print("note added-> ");
}

void SmfWriter::addNoteOffEvent(unsigned int deltaticks, byte channel, byte key) {
  byte statusByte = 0x80 | channel;
  byte data[3] = { statusByte, key, 0 };
  addEvent(deltaticks, data, 3);
}


void SmfWriter::addControlChange(unsigned int deltaticks, byte controlNumber, byte controlValue, byte channel) {
  byte statusByte = 0xC0 | channel;
  byte data[3] = { statusByte, controlNumber, controlValue };
  addEvent(deltaticks, data, 3);
}

void SmfWriter::addPitchBend(unsigned int deltaticks, int pitchValue, byte channel) {
  unsigned int normalizedPitchValue = pitchValue + 0x2000;
  byte statusByte = 0xE0 | channel;
  byte msb = normalizedPitchValue >> 9;
  byte lsb = normalizedPitchValue & 0x7F;
  byte data[3] = { statusByte, lsb, msb };
  addEvent(deltaticks, data, 3);
}

void SmfWriter::addPitchBend(unsigned int deltaticks, double pitchValue, byte channel) {
  int pitch = pitchValue * 0x2000;
  addPitchBend(deltaticks, pitch, channel);
}

void SmfWriter::addSetTempo(unsigned int deltaticks, double tempo) {
  unsigned int microseconds_per_quarter_note = 60000000 / tempo;
  uint8_t nn = microseconds_per_quarter_note >> 16;
  uint8_t dd = microseconds_per_quarter_note >> 8;
  uint8_t cc = microseconds_per_quarter_note & 0xFF;
  byte data[6] = { 0xFF, 0x51, 0x03, nn, dd, cc };
  addEvent(deltaticks, data, 6);
}




void SmfWriter::flush() {
  if (_bufferPos == 0) return;
  File data = SD.open(_filename, O_WRITE);
  if (!data) {
    char* notAbleToOpen = const_cast<char*>("Not able to open ");
    Serial.print(notAbleToOpen);
    Serial.print(_filename);
    Serial.println();
    return;
  }
  data.write(_buffer, _bufferPos);
  data.close();
  _bufferPos = 0;
  if (trackSize > 0) {
    // go back and update the 0'th midi track length
    data = SD.open(_filename, O_READ | O_WRITE);
    data.seek(18);
    //Serial.print("flush-> ");
    write_buf_int(trackSize);
    data.write(_buffer, _bufferPos);
    _bufferPos = 0;
    data.close();
  }
}