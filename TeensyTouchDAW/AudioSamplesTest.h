// Audio data converted from WAV file by wav2sketch

extern const unsigned int AudioSampleTomtom[3489];
extern const unsigned int AudioSampleSnare[2817];
extern const unsigned int AudioSampleCashregister[5809];
extern const unsigned int AudioSampleHihat[5953];
extern const unsigned int AudioSampleKick[2561];
extern const unsigned int AudioSampleP2[929];
extern const unsigned int AudioSampleGong[27633];
extern const unsigned int AudioSamplePongblip[737];
extern const unsigned int AudioSampleClap[3649];


#pragma once
#include <Audio.h>


extern const AudioSynthWavetable::sample_data BasicFlute1_samples[2];
const uint8_t BasicFlute1_ranges[] = {
  54,
  127,
};
const AudioSynthWavetable::instrument_data BasicFlute1 = { 2, BasicFlute1_ranges, BasicFlute1_samples };
extern const uint32_t sample_0_BasicFlute1_BreathyFluteC2[28544];
extern const uint32_t sample_1_BasicFlute1_BreathyFluteA2[31616];

extern const AudioSynthWavetable::sample_data FrenchHorns_samples[1];
const uint8_t FrenchHorns_ranges[] = {
  127,
};
const AudioSynthWavetable::instrument_data FrenchHorns = { 1, FrenchHorns_ranges, FrenchHorns_samples };
extern const uint32_t sample_0_FrenchHorns_FrenchHornsA4L[55040];

extern const AudioSynthWavetable::sample_data Ocarina_samples[3];
const uint8_t Ocarina_ranges[] = {
  78,
  101,
  127,
};
const AudioSynthWavetable::instrument_data Ocarina = { 3, Ocarina_ranges, Ocarina_samples };
extern const uint32_t sample_0_Ocarina_OcarinaF4[1536];
extern const uint32_t sample_1_Ocarina_OcarinaF4[1536];
extern const uint32_t sample_2_Ocarina_OcarinaF6[256];

extern const AudioSynthWavetable::sample_data Pizzicato_samples[4];
const uint8_t Pizzicato_ranges[] = {
  68,
  83,
  93,
  127,
};
const AudioSynthWavetable::instrument_data Pizzicato = { 4, Pizzicato_ranges, Pizzicato_samples };
extern const uint32_t sample_0_Pizzicato_PizzViolinE3[2944];
extern const uint32_t sample_1_Pizzicato_PizzViolinC4[2304];
extern const uint32_t sample_2_Pizzicato_PizzViolinE5[768];
extern const uint32_t sample_3_Pizzicato_PizzViolinE5[768];

extern const AudioSynthWavetable::sample_data Viola_samples[8];
const uint8_t Viola_ranges[] = {
  58,
  65,
  68,
  73,
  79,
  92,
  96,
  127,
};
const AudioSynthWavetable::instrument_data Viola = { 8, Viola_ranges, Viola_samples };
extern const uint32_t sample_0_Viola_ViolinBb2[768];
extern const uint32_t sample_1_Viola_ViolinD3[896];
extern const uint32_t sample_2_Viola_ViolinG3[768];
extern const uint32_t sample_3_Viola_ViolinC4[768];
extern const uint32_t sample_4_Viola_ViolinGb4[768];
extern const uint32_t sample_5_Viola_ViolinC5[640];
extern const uint32_t sample_6_Viola_ViolinEb5[768];
extern const uint32_t sample_7_Viola_ViolinEb6[512];

extern const AudioSynthWavetable::instrument_data SpaceVoice;
static const uint8_t SpaceVoice_ranges[] = {
  127,
};

extern const AudioSynthWavetable::instrument_data Banjo;
extern const AudioSynthWavetable::instrument_data AcouPiano3;
extern const AudioSynthWavetable::instrument_data Piano1;
extern const AudioSynthWavetable::instrument_data Violin;
static const uint8_t Violin_ranges[] = {
  60,
  66,
  71,
  75,
  80,
  85,
  127,
};