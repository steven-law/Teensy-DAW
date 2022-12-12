//sizes and positions
#define STEP_QUANT 16
#define STEP_FRAME_W 16
#define STEP_FRAME_H 16
#define TRACK_FRAME_H 24
#define SEQ_GRID_LEFT 2
#define SEQ_GRID_RIGHT 17
#define SEQ_GRID_TOP 1
#define SEQ_GRID_BOTTOM 12
#define GRID_LENGTH_HOR 256
#define GRID_LENGTH_VERT 192
#define POSITION_ARR_BUTTON 18
#define POSITION_BPM_BUTTON 11
#define POSITION_SCALE_BUTTON 16
#define POSITION_LOAD_BUTTON 15
#define POSITION_SAVE_BUTTON 13
#define POSITION_STOP_BUTTON 10
#define POSITION_PLAY_BUTTON 8
#define POSITION_RECORD_BUTTON 7
#define POSITION_BAR_BUTTON 5
#define DOT_OFFSET_X 40  //STEP_FRAME_W * 2 + 8
#define DOT_OFFSET_Y 24  //STEP_FRAME_H + 8
#define DOT_RADIUS 5
#define OCTAVE_CHANGE_TEXT 3
#define OCTAVE_CHANGE_LEFTMOST 18
#define OCTAVE_CHANGE_RIGHTMOST 20
#define OCTAVE_CHANGE_UP_TOPMOST 2
#define OCTAVE_CHANGE_UP_BOTTOMMOST 3
#define OCTAVE_CHANGE_DOWN_TOPMOST 4
#define OCTAVE_CHANGE_DOWN_BOTTOMMOST 5
#define SONG_POSITION_POINTER_Y 228
#define STEP_POSITION_POINTER_Y 236
#define GRID_POSITION_POINTER_Y 232
#define POSITION_POINTER_THICKNESS 3
#define POTPICKUP 3
#define SPI_FREQUENCY 40000000
#define SPI_READ_FREQUENCY 10000000

#define VELOCITYOFF 0
#define VALUE_NOTEOFF 0


//variables for own clock
#define NUM_CLIPS 9
#define NUM_TRACKS 8

#define NUM_STEPS 16
#define NUM_PHRASES 256
#define FS_MIN_TEMPO 55
#define FS_MAX_TEMPO 200
unsigned long _next_clock = 0;
unsigned long _clock = 0;
unsigned long MIDItick = 0;
byte noteOff_tick = 0;
byte tick_16 = 0;
bool seq_run = false;
bool seq_rec = false;
byte tempo = 120;

//****************************************************************************
// 3) add your Plugin name (4 chars max) to the pluginName array, if needed decrease MAX-PLUGINS, MAX-CHANNELS & MAX-PAGES
//    for the tutorial we add "1OSC"
//    and define our first Plugin page  -> #define PLUGIN3_PAGE1 42   pluginstartpage has to be in order with the midi (plugin-)channel
//    scroll down and add your plugin variables there, please use one struct for all your variables so things can be handled a bit more easier
//    now we head over to the 15stepTeensyDAW3.ino"
//look for *************************************************************************
////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_PRESETS 8  //max presets per plugin
#define MAX_CLIPS 8    //max cliips per track
#define MAX_PLUGINS 16
#define MAX_CHANNELS 32  //   = MAX_PLUGINS + 16 (Midichannels)
const char* pluginName[MAX_PLUGINS]{ "Chrd", "SDrm", "1OSC", "MDrm", "Raw1", "Raw2", "Drum", "MogL", "Strng", "10", "11", "12", "13", "14", "15", "16" };


#define DRUMTRACK 0
// 1-7 are the Sequencer-Tracks: 2-8
#define SCALESELECT 8
#define SONGMODE_PAGE_ZOOM 9
#define SONGMODE_PAGE_1 10
#define SONGMODE_PAGE_2 11
#define SONGMODE_PAGE_3 12
#define SONGMODE_PAGE_4 13
#define SONGMODE_PAGE_5 14
#define SONGMODE_PAGE_6 15
#define SONGMODE_PAGE_7 16
#define SONGMODE_PAGE_8 17
#define SONGMODE_PAGE_9 18
#define SONGMODE_PAGE_10 19
#define SONGMODE_PAGE_11 20
#define SONGMODE_PAGE_12 21
#define SONGMODE_PAGE_13 22
#define SONGMODE_PAGE_14 23
#define SONGMODE_PAGE_15 24
#define SONGMODE_PAGE_16 25

#define MIXER_PAGE_1 30
#define MIXER_PAGE_2 31
#define MIXER_PAGE_3 32
#define MIXER_PAGE_4 33
#define RECORDER_PAGE 34
#define MIDICC_PAGE_1 35
#define MIDICC_PAGE_2 36

#define PLUGIN1_PAGE1 40
#define PLUGIN2_PAGE1 41
#define PLUGIN3_PAGE1 42
#define PLUGIN4_PAGE1 43
#define PLUGIN5_PAGE1 44
#define PLUGIN6_PAGE1 45
#define PLUGIN7_PAGE1 46
#define PLUGIN8_PAGE1 47
#define PLUGIN9_PAGE1 48
#define PLUGIN10_PAGE1 49



#define PLUGIN1_PAGE2 60
#define PLUGIN1_PAGE3 61
#define PLUGIN1_PAGE4 62
#define PLUGIN7_PAGE2 63
#define PLUGIN7_PAGE3 64

#define SQ1_PAGE1 119
#define FX1_PAGE1 120
#define FX2_PAGE1 123
#define FX3_PAGE1 126

byte selectPage;

#define MAX_RAW_FILES 128
#define SAMPLE_ROOT 69
#define MAX_WAV_FILES 11
const char* RAW_files[MAX_RAW_FILES] = { "0.RAW", "1.RAW", "2.RAW", "3.RAW", "4.RAW", "5.RAW", "6.RAW", "7.RAW", "8.RAW", "9.RAW", "10.RAW",
                                         "11.RAW", "12.RAW", "13.RAW", "14.RAW", "15.RAW", "16.RAW", "17.RAW", "18.RAW", "19.RAW", "20.RAW",
                                         "21.RAW", "22.RAW", "23.RAW", "24.RAW", "25.RAW", "26.RAW", "27.RAW", "28.RAW", "29.RAW", "30.RAW",
                                         "31.RAW", "32.RAW", "33.RAW", "34.RAW", "35.RAW", "36.RAW", "37.RAW", "38.RAW", "39.RAW", "40.RAW",
                                         "41.RAW", "42.RAW", "43.RAW", "44.RAW", "45.RAW", "46.RAW", "47.RAW", "48.RAW", "49.RAW", "50.RAW",
                                         "51.RAW", "52.RAW", "53.RAW", "54.RAW", "55.RAW", "56.RAW", "57.RAW", "58.RAW", "59.RAW", "60.RAW",
                                         "61.RAW", "62.RAW", "63.RAW", "64.RAW", "65.RAW", "66.RAW", "67.RAW", "68.RAW", "69.RAW", "70.RAW",
                                         "71.RAW", "72.RAW", "73.RAW", "74.RAW", "75.RAW", "76.RAW", "77.RAW", "78.RAW", "79.RAW", "80.RAW",
                                         "81.RAW", "82.RAW", "83.RAW", "84.RAW", "85.RAW", "86.RAW", "87.RAW", "88.RAW", "89.RAW", "90.RAW",
                                         "91.RAW", "92.RAW", "93.RAW", "94.RAW", "95.RAW", "96.RAW", "97.RAW", "98.RAW", "99.RAW", "100.RAW",
                                         "101.RAW", "102.RAW", "103.RAW", "104.RAW", "105.RAW", "106.RAW", "107.RAW", "108.RAW", "109.RAW", "110.RAW",
                                         "111.RAW", "112.RAW", "113.RAW", "114.RAW", "115.RAW", "116.RAW", "117.RAW", "118.RAW", "119.RAW", "120.RAW",
                                         "121.RAW", "122.RAW", "123.RAW", "124.RAW", "125.RAW", "126.RAW", "127.RAW" };


const char* WAV_files[MAX_WAV_FILES] = { "0.WAV", "1.WAV", "2.WAV", "3.WAV", "4.WAV", "5.WAV", "6.WAV", "7.WAV", "8.WAV", "9.WAV", "10.WAV" };
const char* showVOL[12]{ "Vol1", "Vol2", "Vol3", "Vol4", "Vol5", "Vol6", "Vol7", "Vol8", "Vol9", "Vol10", "Vol11", "Vol12" };
const char* noteNames[12]{ "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
char* trackNames_short[9]{ "TrD", "Tr2", "Tr3", "Tr4", "Tr5", "Tr6", "Tr7", "Tr8", "" };
const char* filterType[3] = { "LPF", "BPF", "HPF" };

//plugin 1 variables
struct plugin1 {

  int Filter1_Frequency = 560;
  byte Filter1_Frequency_graph = 20;
  byte Filter1_Resonance_graph = 25;
  float Filter1_Resonance = 1;
  byte Filter1_Sweep_graph = 80;
  float Filter1_Sweep = 2;
  byte Filter1_Type = 0;
  byte Filter1_Type_graph = 0;
  int Env1_Attack = 50;
  byte Env1_Attack_graph = 10;
  int Env1_Decay = 50;
  byte Env1_Decay_graph = 50;
  float Env1_Sustain = 1;
  byte Env1_Sustain_graph = 50;
  int Env1_Release = 150;
  byte Env1_Release_graph = 15;
  int note_Offset[4] = { 0, 4, 7, 11 };
  byte note_Offset_graph[4] = { 50, 65, 80, 95 };
  float note_Velo[4] = { 1, 1, 1, 1 };
  byte note_Velo_graph[4] = { 100, 100, 100, 100 };
  byte wfSelect[4] = { 0, 0, 0, 0 };
  byte wfSelect_graph[4] = { 0, 0, 0, 0 };
};
plugin1 pl1[MAX_PRESETS];
byte pl1presetNr = 0;

//plugin 2 variables
struct plugin2 {
  byte Vol_rnd[12];
  float Vol[12];
};
plugin2 pl2[MAX_PRESETS];
byte pl2presetNr = 0;

//plugin 3 variables
struct plugin3 {
  int Filter1_Frequency = 260;
  byte Filter1_Frequency_graph = 50;
  float Filter1_Resonance = 1;
  byte Filter1_Resonance_graph = 50;
  float Filter1_Sweep = 2;
  byte Filter1_Sweep_graph = 50;
  byte Filter1_Type = 0;
  byte Filter1_Type_graph = 0;
  int Env1_Attack = 50;
  byte Env1_Attack_graph = 50;
  int Env1_Decay = 50;
  byte Env1_Decay_graph = 50;
  float Env1_Sustain = 1;
  byte Env1_Sustain_graph = 50;
  int Env1_Release = 150;
  byte Env1_Release_graph = 50;
  float note1_Velo = 1;
  byte note1_Velo_rnd;
  byte wfSelect;
  byte wfSelect_graph;
};
plugin3 pl3[MAX_PRESETS];
byte pl3presetNr = 0;

//plugin 4 variables
struct plugin4 {
  byte Vol_rnd[12];
  float Vol[12];
};
plugin4 pl4[MAX_PRESETS];
byte pl4presetNr = 0;

//plugin 5 variables
struct plugin5 {
  int Filter1_Frequency = 260;
  float Filter1_Frequency_graph = 50;
  float Filter1_Resonance = 1;
  byte Filter1_Resonance_graph = 50;
  float Filter1_Sweep = 2;
  byte Filter1_Sweep_graph = 50;
  byte Filter1_Type = 0;
  byte Filter1_Type_graph = 0;
  int Env1_Attack = 50;
  byte Env1_Attack_graph = 50;
  int Env1_Decay = 50;
  byte Env1_Decay_graph = 50;
  float Env1_Sustain = 1;
  byte Env1_Sustain_graph = 50;
  int Env1_Release = 150;
  float Env1_Release_graph = 50;
  byte selected_file;
  byte selected_file_graph = 50;
  byte Volume_graph = 50;
  float Volume;
};
plugin5 pl5[MAX_PRESETS];
byte pl5presetNr = 0;
bool pl5enter_was_pushed = true;

//plugin 6 variables
struct plugin6 {
  int Filter1_Frequency = 260;
  byte Filter1_Frequency_graph = 50;
  float Filter1_Resonance = 1;
  byte Filter1_Resonance_graph = 50;
  float Filter1_Sweep = 2;
  byte Filter1_Sweep_graph = 50;
  byte Filter1_Type = 0;
  byte Filter1_Type_graph = 0;
  int Env1_Attack = 50;
  byte Env1_Attack_graph = 50;
  int Env1_Decay = 50;
  byte Env1_Decay_graph = 50;
  float Env1_Sustain = 1;
  byte Env1_Sustain_graph = 50;
  int Env1_Release = 150;
  byte Env1_Release_graph = 50;
  byte selected_raw_file;
  byte selected_file_raw_graph = 50;
  byte Volume_graph = 50;
  float Volume_rnd;
  float Volume;
};
plugin6 pl6[MAX_PRESETS];
byte pl6presetNr = 0;



//plugin7 variables
//drum11111111111111111111111111111111111111111111111111111111111111111111111111111111 drum 1
int pl7drum1_frequency;
byte pl7drum1_frequency_graph = 50;
byte pl7drum1_length;
byte pl7drum1_length_graph = 50;
float pl7drum1_pitchMod;  //max 2 !!
byte pl7drum1_pitchMod_graph = 50;
int pl7drum1_pitchMod_rnd;
float pl7drum1_secondMix;
byte pl7drum1_secondMixgraph = 50;
float pl7dc1_amplitude = 0.06;
byte pl7dc1_amplitude_graph = 10;
//noisemod22222222222222222222222222222222222222222222222222222222222222222222222222222 noise mode 2
float pl7noise1_amplitude = 1;
byte pl7noise1_amplitude_graph = 100;

byte pl7waveformMod1_begin;
byte pl7waveformMod1_begin_graph;
float pl7waveformMod1_amplitude;
byte pl7waveformMod1_amplitude_graph;
int pl7waveformMod1_frequency;
byte pl7waveformMod1_frequency_graph;
float pl7waveformMod1_frequencyModulation;
byte pl7waveformMod1_frequencyModulation_graph;
int pl7waveformMod1_frequencyModulation_rnd;

int pl7filter2_frequency;
byte pl7filter2_frequency_graph;
float pl7filter2_resonance;
byte pl7filter2_resonance_graph;
byte pl7filter2_resonance_rnd;
float pl7filter2_octaveControl;
byte pl7filter2_octaveControl_graph;

byte pl7Env1_Attack;
byte pl7Env1_Attack_graph;
byte pl7Env1_Decay;
byte pl7Env1_Decay_graph;
byte pl7Env1_Release;
byte pl7Env1_Release_graph;



//FM33333333333333333333333333333333333333333333333333333333333333333333333333333333333 FM 3
float pl7_3_waveformMod3_amplitude;
byte pl7_3_waveformMod3_amplitude_rnd;
byte pl7_3_waveformMod3_amplitude_graph;
int pl7_3_waveformMod3_frequency;
byte pl7_3_waveformMod3_frequency_graph;


byte pl7_3_Env2_Attack;
byte pl7_3_Env2_Attack_graph;
byte pl7_3_Env2_Decay;
byte pl7_3_Env2_Decay_graph;
byte pl7_3_Env2_Release;
byte pl7_3_Env2_Release_graph;


byte pl7_3_waveformMod2_begin;
byte pl7_3_waveformMod2_begin_graph;
float pl7_3_waveformMod2_amplitude;
byte pl7_3_waveformMod2_amplitude_graph;
int pl7_3_waveformMod2_frequency;
byte pl7_3_waveformMod2_frequency_graph;
float pl7_3_waveformMod2_frequencyModulation;
byte pl7_3_waveformMod2_frequencyModulation_graph;
int pl7_3_waveformMod2_frequencyModulation_rnd;

byte pl7_3_Env3_Attack;
byte pl7_3_Env3_Attack_graph;
byte pl7_3_Env3_Decay;
byte pl7_3_Env3_Decay_graph;
byte pl7_3_Env3_Release;
byte pl7_3_Env3_Release_graph;

//4444444444444444444444444444444444444444444444444444444444444444444444444444 noise
float pl7_4_noise2_amplitude = 1;
int pl7_4_noise2_amplitude_rnd = 100;
byte pl7_4_noise2_amplitude_graph = 100;

float pl7_4_pink1_amplitude = 1;
int pl7_4_pink1_amplitude_rnd = 100;
byte pl7_4_pink1_amplitude_graph = 100;

int pl7_4_biquad1_frequency = 400;
byte pl7_4_biquad1_frequency_graph;
float pl7_4_biquad1_resonance;
byte pl7_4_biquad1_resonance_graph;
byte pl7_4_biquad1_resonance_rnd;

byte pl7_4_Env4_Attack;
byte pl7_4_Env4_Attack_graph;
byte pl7_4_Env4_Decay;
byte pl7_4_Env4_Decay_graph;
byte pl7_4_Env4_Release;
byte pl7_4_Env4_Release_graph;
byte pl7presetNr;
//plugin 8 variables
struct plugin8 {
  int Filter1_Frequency = 260;
  float Filter1_Frequency_graph = 50;
  float Filter1_Resonance = 1;
  byte Filter1_Resonance_graph = 50;
  float Filter1_Sweep = 2;
  byte Filter1_Sweep_graph = 50;
  int Env1_Attack = 50;
  byte Env1_Attack_graph = 50;
  int Env1_Decay = 50;
  byte Env1_Decay_graph = 50;
  float Env1_Sustain = 1;
  byte Env1_Sustain_graph = 50;
  int Env1_Release = 150;
  float Env1_Release_graph = 50;
  float note1_Velo = 1;
  float note1_Velo_rnd;
  byte wfSelect;
  byte wfSelect_graph;
};
plugin8 pl8[MAX_PLUGINS];
byte pl8presetNr = 0;

struct plugin9 {
  byte wavefold_graph;
  float wavefold;
  byte wah_form;
  byte wah_form_graph;
  float wah_rate;
  byte wah_rate_graph;
  int wah_freq;
  byte wah_freq_graph;
  float wah_reso;
  byte wah_reso_graph;
  float wah_sweep;
  byte wah_sweep_graph;
  int Filter1_Frequency = 260;
  byte Filter1_Frequency_graph = 50;
  float Filter1_Resonance = 1;
  byte Filter1_Resonance_graph = 50;
  float Filter1_Sweep = 2;
  byte Filter1_Sweep_graph = 50;
  byte Filter1_Type = 0;
  byte Filter1_Type_graph = 0;
};
plugin9 pl9[MAX_PLUGINS];
byte pl9presetNr = 0;

//Overall Pluginvariables
struct plugins {
  byte Volume_graph = 50;
  float Volume = 1;

  byte FXDryVolume_graph = 100;
  float FXDryVolume = 1;

  byte FX1Volume_graph = 0;
  float FX1Volume = 0;

  byte FX2Volume_graph = 0;
  float FX2Volume = 0;

  byte FX3Volume_graph = 0;
  float FX3Volume = 0;
};
plugins plugin[MAX_PLUGINS];
float MasterVol = 0.12;
byte MasterVol_graph = 15;


//audiorecorder variables

// which input on the audio shield will be used?
const int myInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC;
bool audio_rec_rec = false;
byte audio_rec_rec_graph = 0;
bool audio_rec_now = false;
bool audio_rec_listen = false;
byte audio_rec_listen_graph = 0;
byte audio_rec_volume_graph = 0;
float audio_rec_volume = 0;
byte audio_rec_selected_file;
byte audio_rec_selected_file_graph = 50;

byte audio_rec_peak_graph;
// The file where data is recorded
File frec;




//FX variables
//FX1
//reverb variables
float fx1reverbtime = 0;
byte fx1reverbtime_graph = 0;

//FX2
//bitcrusher variables
int fx2bitcrush = 8;
byte fx2bitcrush_graph = 100;

int fx2samplerate = 22050;
byte fx2samplerate_graph = 100;





//songmode variables

byte page_phrase_start;
byte page_phrase_end;
byte songpageNumber = 10;
#define phraseSegmentLength 16  // a variable for the zoomfactor in songmode
byte pixelphrase = 0;           // a counter for the positionpointers
byte phrase = 0;                // the main unit in songmode 1phrase = 16 bars
byte end_of_loop = 255;
byte start_of_loop = 0;
byte end_of_loop_old = 255;
byte start_of_loop_old = 0;
byte arrangmentSelect = 0;
byte songpages;

byte step_Frame_X;
byte step_Frame_Y;

//touchscreen variables
byte gridTouchX;  //decided to handle touchthingys with a grid, so here it is, 20 grids
byte gridTouchY;  //decided to handle touchthingys with a grid, so here it is, 15 grids
byte trackTouchY;
bool is_held = true;
unsigned long previousMillis = 0;
//DMAMEM uint16_t fb1[320 * 240];


#define CTRL_ROW_0 3
#define CTRL_ROW_1 6
#define CTRL_ROW_2 9
#define CTRL_ROW_3 12
#define CTRL_COL_0 3
#define CTRL_COL_1 7
#define CTRL_COL_2 11
#define CTRL_COL_3 15

//potentiomer variables

int lastPotRow = 0;
int Potentiometer[4];

//button variables
bool enter_button = false;
bool button_9 = false;
bool button_10 = false;
bool button_11 = false;
bool button_12 = false;
bool button_13 = false;
bool button_14 = false;
bool button_15 = false;
bool something_was_pressed = false;
byte last_button_X = 0;
byte last_button_Y = 0;
uint16_t tftRAM[16][16];
int Button_Pos_X_last = (last_button_X)*STEP_FRAME_W;
int Button_Pos_Y_last = (last_button_Y)*STEP_FRAME_H;
int Button_Pos_X_new = (last_button_X - 1) * STEP_FRAME_W;
int Button_Pos_Y_new = (last_button_Y)*STEP_FRAME_H;

//drawPot Variables
float circlePos;
float circlePos_old;
int dvalue_old;
char* dvalue_old_char;
//drawPot Variables
float circlePos_2;
float circlePos_old_2;
int dvalue_old_2;
//drawPot Variables
float circlePos_3;
float circlePos_old_3;
int dvalue_old_3;
//drawPot Variables
float circlePos_4;
float circlePos_old_4;
int dvalue_old_4;
//drawPotcc Variables
float circlePoscc;
float circlePos_oldcc;
int dvalue_oldcc;
int dname_oldcc;


struct sequence_t {
  byte step[NUM_STEPS];  // stores the PITCH VALUE to be played at this step, or 0xFF (255) for NONE. note this is monophonic only (for now)!!
};

struct track_t {
  byte midi_channel;               // stores the MIDI channel that this track should output on; 10 is drums
  sequence_t sequence[NUM_CLIPS];  // the sequence-clips associated with this track
};
track_t ctrack[NUM_TRACKS];

//notenumber to frequency chart
float note_frequency[128]{ 8.18, 8.66, 9.18, 9.72, 10.30, 10.91, 11.56, 12.25, 12.98, 13.75, 14.57, 15.43,
                           16.35, 17.32, 18.35, 19.45, 20.60, 21.83, 23.12, 24.5, 25.96, 27.5, 29.14, 30.87,
                           32.7, 34.65, 36.71, 38.89, 41.20, 43.65, 46.25, 49.00, 51.91, 55, 58.27, 61.74,
                           65.41, 69.30, 73.42, 77.78, 82.41, 87.31, 92.50, 98, 103.83, 110, 116.54, 123.47,
                           130.81, 138.59, 146.83, 155.56, 164.81, 174, 61, 185, 196, 207.65, 220, 233.08, 246.94,
                           261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392, 415.3, 440, 466.16, 493.88,
                           523.25, 554.37, 587.33, 622.25, 659.26, 698.46, 739.99, 783.99, 830.61, 880, 832.33, 987.77,
                           1046.5, 1108.73, 1174.66, 1244.66, 1318.51, 1396.91, 1479.98, 1567.98, 1661.22, 1760, 1864.66, 1975.53,
                           2093, 2217.46, 2349.32, 2489.02, 2793.83, 2959.96, 3135.96, 3322.44, 3520, 3729.31, 3951.07,
                           4186.01, 4434.92, 4698.64, 4978.03, 5274.04, 5587.65, 5919.91, 6271.93, 6644.88, 7040, 7458.62, 7902.13,
                           8372.02, 8869.84, 9397.27, 9956.06, 10548.08, 11175.30, 11839.82, 12543.85 };

//Scales
bool scaleSelect = LOW;
const int scalesQuant = 9;  //how many scales do we have
int scaleSelected = 0;      //variable for scale selecting


int scales[scalesQuant][12]{
  //bool array for greying out notes that are not in the scale
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  //Chromatic
  { 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 },  //Major
  { 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0 },  //Natural Minor
  { 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1 },  //Harmonic Minor
  { 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1 },  //Melodic Minor
  { 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0 },  //Dorian
  { 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0 },  //Mixolydian
  { 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0 },  //Phrygian
  { 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 }   //Lydian
};
const char* scaleNames[scalesQuant] = { "Chromatic", "Major", "Natural Minor", "Harmonic Minor", "Melodic Minor", "Dorian", "Mixolydian", "Phrygian", "Lydian" };  // Scale Names for selecting
const char* scaleNamesShort[scalesQuant] = { "Chrom", "Major", "NatMi", "HarMi", "MelMi", "Dor", "Mixol", "Phryg", "Lyd" };                                        // Scale Names for selecting






//Track Variables
byte desired_track;
byte desired_instrument;
//track 2-8 variables

struct tracks {
  byte MIDIchannel = 0;    // (although you may not need this, depends on how you structure thing later)
  byte clip_selector = 0;  //clipselection from trackview´s clip selector
  byte clip_songMode = 1;  //clipselection from the arrangement
  byte tone = 0;
  byte shown_octaves = 5;  //
  byte velocity_ON = 96;
  byte velocity_ON_graph = 80;
  bool mute_state = LOW;
  bool solo_state = LOW;
  bool solo_mutes_state = LOW;
  bool send_noteOff;
  byte midicc_value_row_1[4];
  byte midicc_number_row_1[4]{ 20, 21, 22, 23 };
  byte midicc_value_row_2[4];
  byte midicc_number_row_2[4]{ 24, 25, 26, 27 };
  byte midicc_value_row_3[4];
  byte midicc_number_row_3[4];
  byte midicc_value_row_4[4];
  byte midicc_number_row_4[4];
  byte clip[MAX_CLIPS][NUM_STEPS];
  byte arrangment1[256];
  int NoteOffset[256];
  int presetNr[256];
  int volume[256];
};
// make an array of 8 channel_types, numbered 0-7
tracks track[8];



//channel 1 variables
bool channel1Select = LOW;  // a handler to keep the mode active after selecting
byte ch1tone;
byte ch1Octaves = 3;
bool dsend_noteOff[12];
bool channel1Clip[NUM_CLIPS][12][STEP_QUANT]{

  { //Clip 0
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
  { //Clip 1
    { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
  { //Clip2
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
  { //Clip3
    { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
  { //Clip4
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
  { //Clip5
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
  { //Clip6
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
  { //Clip7
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
  { //Clip8
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }
};