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
#define POSITION_BPM_BUTTON 11
#define POSITION_STOP_BUTTON 10
#define POSITION_PLAY_BUTTON 8
#define POSITION_RECORD_BUTTON 7
#define POSITION_BAR_BUTTON 5
#define DOT_OFFSET_X 40  //STEP_FRAME_W * 2 + 8
#define DOT_OFFSET_Y 24  //STEP_FRAME_H + 8
#define DOT_RADIUS 5
#define OCTAVE_CHANGE_LEFTMOST 18
#define OCTAVE_CHANGE_RIGHTMOST 20
#define OCTAVE_CHANGE_UP_TOPMOST 2
#define OCTAVE_CHANGE_UP_BOTTOMMOST 4
#define OCTAVE_CHANGE_DOWN_TOPMOST 7
#define OCTAVE_CHANGE_DOWN_BOTTOMMOST 9
#define SONG_POSITION_POINTER_Y 228
#define STEP_POSITION_POINTER_Y 236
#define GRID_POSITION_POINTER_Y 232
#define POSITION_POINTER_THICKNESS 3
#define POTPICKUP 10
//potentiomernames
int Potentiometer1;

#define VELOCITYOFF 0
#define VALUE_NOTEOFF 0

//variables for 15step sequencer
#define SEQUENCER_MEMORY 32768
#define NUM_CLIPS 9
#define NUM_TRACKS 8
#define NUM_VOICES 4
#define NUM_STEPS 16
#define NUM_PHRASES 64
int steps = 16;
int polyphony = 64;


//****************************************************************************
// 6)add your Plugin name (4 chars max) to the pluginName array, if needed decrease MAX-PLUGINS, MAX-CHANNELS & MAX-PAGES
// for the tutorial we add "1OSC"
// 7)and define our first Plugin page  -> #define PLUGIN3_PAGE1 22   pluginstartpage has to be in order with the midi (plugin-)channel
// 8)scroll down and add your plugin variables there
// now we head over to the 15stepTeensyDAW3.ino"
//look for *************************************************************************
////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_PLUGINS 10
#define MAX_CHANNELS 26  //   = MAX_PLUGINS + 16 (Midichannels)
char* pluginName[MAX_PLUGINS]{ "Chrd", "SDrm", "1OSC", "MDrm", "SDWv", "SDRw", "Drum", "8", "9", "10" };


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


#define FX1_PAGE1 120
#define FX2_PAGE1 123
#define FX3_PAGE1 126

#define MAX_PAGES 128
bool selectPage[MAX_PAGES];

//plugin 1 variables
int pl1Filter1_Frequency = 560;
byte pl1Filter1_Frequency_graph = 20;
byte pl1Filter1_Resonance_graph = 25;
byte pl1Filter1_Resonance_rnd = 25;
float pl1Filter1_Resonance = 1;
byte pl1Filter1_Sweep_graph = 80;
byte pl1Filter1_Sweep_rnd = 80;
float pl1Filter1_Sweep = 2;
int pl1Env1_Attack = 50;
byte pl1Env1_Attack_graph = 10;
int pl1Env1_Release = 150;
byte pl1Env1_Release_graph = 15;
int pl1note_Offset[4] = { 0, 4, 7, 11 };
byte pl1note_Offset_graph[4] = { 50, 65, 80, 95 };
float pl1note_Velo[4] = { 1, 1, 1, 1 };
byte pl1note_Velo_graph[4] = { 100, 100, 100, 100 };
byte pl1wfSelect[4] = { 0, 0, 0, 0 };
byte pl1wfSelect_graph[4] = { 0, 0, 0, 0 };




//plugin 2 variables

int Pl2Vol_rnd[12];
float Pl2Vol[12];


//plugin 3 variables

int pl3Filter1_Frequency = 260;
float pl3Filter1_Frequency_graph = 50;
float pl3Filter1_Resonance_rnd;
float pl3Filter1_Resonance = 1;
byte pl3Filter1_Resonance_graph = 50;
float pl3Filter1_Sweep_rnd;
float pl3Filter1_Sweep = 2;
byte pl3Filter1_Sweep_graph = 50;
int pl3Env1_Attack = 50;
byte pl3Env1_Attack_graph = 50;
int pl3Env1_Decay = 50;
byte pl3Env1_Decay_graph = 50;
float pl3Env1_Sustain = 1;
byte pl3Env1_Sustain_graph = 50;
int pl3Env1_Release = 150;
float pl3Env1_Release_graph = 50;
float pl3note1_Velo = 1;
float pl3note1_Velo_rnd;
byte pl3wfSelect;
byte pl3wfSelect_graph;




//plugin 4 variables

int Pl4Vol_rnd[12];
float Pl4Vol[12];
//char* Pl4Controls[12]{ "Vol1", "Vol2", "Vol3", "Vol4", "Vol5", "Vol6", "Vol7", "Vol8", "Vol9", "Vol10", "Vol11", "Vol12" };


//plugin 5 variables
int pl5Filter1_Frequency = 260;
float pl5Filter1_Frequency_graph = 50;
float pl5Filter1_Resonance_rnd;
float pl5Filter1_Resonance = 1;
byte pl5Filter1_Resonance_graph = 50;
float pl5Filter1_Sweep_rnd;
float pl5Filter1_Sweep = 2;
byte pl5Filter1_Sweep_graph = 50;
int pl5Env1_Attack = 50;
byte pl5Env1_Attack_graph = 50;
int pl5Env1_Decay = 50;
byte pl5Env1_Decay_graph = 50;
float pl5Env1_Sustain = 1;
byte pl5Env1_Sustain_graph = 50;
int pl5Env1_Release = 150;
float pl5Env1_Release_graph = 50;
byte selected_file;
byte selected_file_graph = 50;
byte pl5Volume_graph = 50;
float pl5Volume;
#define MAX_WAV_FILES 11
#define SAMPLE_ROOT 69
const char* WAV_files[MAX_WAV_FILES] = { "0.WAV", "1.WAV", "2.WAV", "3.WAV", "4.WAV", "5.WAV", "6.WAV", "7.WAV", "8.WAV", "9.WAV", "10.WAV" };

//plugin 6 variables
int pl6Filter1_Frequency = 260;
float pl6Filter1_Frequency_graph = 50;
float pl6Filter1_Resonance_rnd;
float pl6Filter1_Resonance = 1;
byte pl6Filter1_Resonance_graph = 50;
float pl6Filter1_Sweep_rnd;
float pl6Filter1_Sweep = 2;
byte pl6Filter1_Sweep_graph = 50;
int pl6Env1_Attack = 50;
byte pl6Env1_Attack_graph = 50;
int pl6Env1_Decay = 50;
byte pl6Env1_Decay_graph = 50;
float pl6Env1_Sustain = 1;
byte pl6Env1_Sustain_graph = 50;
int pl6Env1_Release = 150;
byte pl6Env1_Release_graph = 50;
byte selected_raw_file;
byte selected_file_raw_graph = 50;
byte pl6Volume_graph = 50;
float pl6Volume_rnd;
float pl6Volume;
#define MAX_RAW_FILES 11
#define SAMPLE_ROOT 69
const char* RAW_files[MAX_RAW_FILES] = { "0.RAW", "1.RAW", "2.RAW", "3.RAW", "4.RAW", "5.RAW", "6.RAW", "7.RAW", "8.RAW", "9.RAW", "10.RAW" };

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
byte pl7noise1_amplitude = 1;
byte pl7noise1_amplitude_graph = 800;

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

//Overall Pluginvariables
struct plugins {
  byte Volume_graph = 50;
  int Volume_rnd = 100;
  float Volume = 1;

  byte FXDryVolume_graph = 100;
  int FXDryVolume_rnd = 100;
  float FXDryVolume = 1;

  byte FX1Volume_graph = 0;
  int FX1Volume_rnd = 0;
  float FX1Volume = 0;

  byte FX2Volume_graph = 0;
  int FX2Volume_rnd = 0;
  float FX2Volume = 0;

  byte FX3Volume_graph = 0;
  int FX3Volume_rnd = 0;
  float FX3Volume = 0;
};
plugins plugin[MAX_PLUGINS];

// plugin[].Volume_graph;
// plugin[].Volume_rnd;
// plugin[].Volume;
// Plugin 1 variables
char* showVOL[12]{ "Vol1", "Vol2", "Vol3", "Vol4", "Vol5", "Vol6", "Vol7", "Vol8", "Vol9", "Vol10", "Vol11", "Vol12" };

//mixer variables
#define MixerPage2_Dynamic_ROW_0 3
#define MixerPage2_Dynamic_ROW_1 6
#define MixerPage2_Dynamic_ROW_2 9
#define MixerPage2_Dynamic_ROW_3 12
//FX variables
//FX1
//reverb variables
float fx1reverbtime = 0;
int fx1reverbtime_rnd = 0;
byte fx1reverbtime_graph = 0;

//FX2
//bitcrusher variables
int fx2bitcrush = 8;
int fx2bitcrush_graph = 100;

int fx2samplerate = 22050;
int fx2samplerate_graph = 100;

//structure variables
bool clipSelector = LOW;
bool songArranger = HIGH;
bool clipNumberSelector = LOW;


//songmode variables

byte page_phrase_start;
byte page_phrase_end;
byte songpageNumber = 10;
byte phraseSegmentLength = 16;  // a variable for the zoomfactor in songmode
byte tempoSelect = 120;         //variable to select the tempo
byte pixelbarClock = 0;         // a counter for the positionpointers
byte phrase = 0;                // the main unit in songmode 1phrase = 16 bars
byte end_of_loop = 255;
byte start_of_loop = 0;
byte end_of_loop_old = 255;
byte start_of_loop_old = 0;
byte arrangmentSelect = 0;

int step_Frame_X;
int step_Frame_Y;

//touchscreen variables
int gridTouchX;  //decided to handle touchthingys with a grid, so here it is, 20 grids
int gridTouchY;  //decided to handle touchthingys with a grid, so here it is, 15 grids
int trackTouchY;
int constrainedtrackTouchY;
unsigned long previousMillis = 0;

//button variables
#define NUM_BUTTONS 7
const uint8_t BUTTON_PINS[NUM_BUTTONS] = { 30, 28, 27, 29, 26, 24, 25 };  //left, right, up, down, start, stop, enter
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

//drawPotcc Variables
float circlePoscc;
float circlePos_oldcc;
int dvalue_oldcc;
int dname_oldcc;

//drawPotLine Variables
float drawPotLinePos;
float drawPotLinePos_old;
int drawPotLine_dvalue_old;

//clip handling variables
byte desired_step;
byte desired_clip;
byte desired_instrument;

struct sequence_t {
  byte step[NUM_STEPS];  // stores the PITCH VALUE to be played at this step, or 0xFF (255) for NONE. note this is monophonic only (for now)!!
};

struct track_t {
  byte midi_channel;               // stores the MIDI channel that this track should output on; 10 is drums
  sequence_t sequence[NUM_CLIPS];  // the sequence-clips associated with this track
  byte arrangement[NUM_PHRASES];   // stores the INDEX of the sequence-clip to play at each phrase-number
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


byte clip[NUM_TRACKS][NUM_CLIPS][NUM_STEPS]{
  { //channel1
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
  { //channel2
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
  { //channel3
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
  { //channel4
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
  { //channel5
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
  { //channel6
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
  { //channel7
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
  { //channel8
    { 36, 0, 0, 0, 36, 0, 0, 0, 37, 0, 0, 0, 39, 0, 0, 0 },
    { 0, 0, 36, 0, 0, 0, 36, 0, 0, 0, 36, 0, 0, 0, 36, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
};



//Scales
bool scaleSelect = LOW;
const int scalesQuant = 9;  //how many scales do we have
int scaleSelected = 0;      //variable for scale selecting
char* noteNames[12] =       //notenames that are printed on the left
  { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
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
char* scaleNames[scalesQuant] = { "Chromatic", "Major", "Natural Minor", "Harmonic Minor", "Melodic Minor", "Dorian", "Mixolydian", "Phrygian", "Lydian" };  // Scale Names for selecting
char* scaleNamesShort[scalesQuant] = { "Chrom", "Major", "NatMi", "HarMi", "MelMi", "Dor", "Mixol", "Phryg", "Lyd" };                                        // Scale Names for selecting


// save button state
int button_last = 0;

//clock variables
byte barClock = 0;

//Track Variables
byte desired_track;
//track 2-8 variables

struct tracks {
  bool select = false;
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
  char* trackNames_short[9]{ "TrD", "Tr2", "Tr3", "Tr4", "Tr5", "Tr6", "Tr7", "Tr8", "" };
  //char* FXNames_short[8]{ "Send1", "Send2", "Tr3", "Tr4", "Tr5", "Tr6", "Tr7", "Tr8" };
  bool held_notes[STEP_QUANT]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  byte midicc_value_row_1[4];
  byte midicc_number_row_1[4];
  byte midicc_value_row_2[4];
  byte midicc_number_row_2[4];
  byte midicc_value_row_3[4];
  byte midicc_number_row_3[4];
  bool sendCC = false;
  byte arrangment1[256];
};
// make an array of 8 channel_types, numbered 0-7
tracks track[8];
//track[].select;
//track[].MIDIchannel;
//track[].clip_selector;
//track[].clip_songMode;
//track[].tone;
//track[].shown_octaves;
//track[].held_notes;
//track[].velocity_ON;


//channel 1 variables
bool channel1Select = LOW;  // a handler to keep the mode active after selecting

byte ch1Clip = 1;
byte ch1tone;
byte ch1Octaves = 3;
byte ch1songModePlayedClip;
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