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

#define AUDIO_MEMORYS 600
#define SPI_FREQUENCY 40000000
#define SPI_READ_FREQUENCY 10000000

#define VELOCITYOFF 0
static const int VALUE_NOTEOFF = 0;


//variables for own clock
#define NUM_CLIPS 9
#define NUM_TRACKS 8
#define num_voice 12

#define NUM_STEPS 16
#define MAX_PHRASES 256
#define FS_MIN_TEMPO 55
#define FS_MAX_TEMPO 200
unsigned long _next_clock = 0;
unsigned long _clock = 0;
unsigned long MIDItick = 0;
int tick_16 = -1;
bool seq_run = false;
bool seq_rec = false;
byte tempo = 120;



//****************************************************************************
// 3) add your Plugin name (4 chars max) to the pluginName array, if needed decrease MAX-PLUGINS, MAX-CHANNELS & MAX-PAGES
//    for the tutorial we add "1OSC"
//    and define our first Plugin page  -> #define PLUGIN3_PAGE1 42   pluginstartpage has to be in order with the midi (plugin-)channel
//    scroll down and add your plugin variables there, please use one struct for all your variables so things can be handled a bit more easier
//    now we head over to the functions.ino" to add the static and dynamic page to the desired functions
////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_PRESETS 8  //max presets per plugin
#define MAX_CLIPS 8    //max cliips per track
#define MAX_PLUGINS 16
#define MAX_CHANNELS 32  //   = MAX_PLUGINS + 16 (Midichannels)


byte selectPage;
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

//plugin selectPage defines in c_pluginVariables.h

#define SQ1_PAGE1 119
#define FX1_PAGE1 120
#define FX2_PAGE1 123
#define FX3_PAGE1 126


#define MAX_RAW_FILES 128
#define SAMPLE_ROOT 69
#define MAX_WAV_FILES 11

const char* wavKit[12] = { "P0.WAV", "P1.WAV", "P2.WAV", "P3.WAV", "P4.WAV", "P5.WAV", "P6.WAV", "P7.WAV", "P8.WAV", "P9.WAV", "P10.WAV", "P11.WAV" };
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
const char* trackNames_short[9]{ "TrD", "Tr2", "Tr3", "Tr4", "Tr5", "Tr6", "Tr7", "Tr8", "" };
const char* trackNames_long[8]{ "track1", "track2", "track3", "track4", "track5", "track6", "track7", "track8" };
const char* trackNames_txt[8]{ "track1.txt", "track2.txt", "track3.txt", "track4.txt", "track5.txt", "track6.txt", "track7.txt", "track8.txt" };
const char* filterType[3] = { "LPF", "BPF", "HPF" };

const int steps = 16;      // number of steps in the sequence
const int numTracks = 4;   // number of tracks in the sequence
const int startNote = 36;  // MIDI note number of the first note
const int channel = 9;     // MIDI channel (zero-indexed)




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
int audio_rec_listen_graph = 0;
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
int fx2bitcrush = 16;
byte fx2bitcrush_graph = 127;

int fx2samplerate = 44100;
byte fx2samplerate_graph = 127;

//FX3
//delay variables
int fx3delayTime = 300;
int fx3delayTime_graph = 30;
float fx3delayFeedback = 0;
int fx3delayFeedback_graph = 0;
int fx3delayFilterFreq = 600;
int fx3delayFilterFreq_graph = 40;
float fx3delayFilterReso = 0;
int fx3delayFilterReso_graph = 0;
float fx3delayAmount = 0;
int fx3delayAmount_graph = 0;

//notenumber to frequency chart
float* note_frequency;




//songmode variables

byte page_phrase_start;
byte page_phrase_end;
byte songpageNumber = 10;
#define phraseSegmentLength 16  // a variable for the zoomfactor in songmode
byte pixelphrase = 0;           // a counter for the positionpointers
byte phrase = 0;                // the main unit in songmode 1phrase = 16 bars
byte phraser;
byte end_of_loop = MAX_PHRASES - 1;
byte start_of_loop = 0;
byte end_of_loop_old = MAX_PHRASES - 1;
byte start_of_loop_old = 0;
byte arrangmentSelect = 0;
byte songpages;
byte stepOld;
int deltaStep = 0;

byte step_Frame_X;
byte step_Frame_Y;

//touchscreen variables
byte gridTouchX;  //decided to handle touchthingys with a grid, so here it is, 20 grids
byte gridTouchY;  //decided to handle touchthingys with a grid, so here it is, 15 grids
byte trackTouchY;
bool is_held = true;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
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
bool enc_moved[4]{ 0, 0, 0, 0 };
int encoded[4];
bool enc_button[4];
//button variables

bool drumnotes[12];
bool button[16]{};
int channelPlayed;

bool showSerialonce = false;
bool something_was_pressed = false;
bool otherCtrlButtons = true;
byte last_button_X = 0;
byte last_button_Y = 0;
uint16_t tftRAM[16][16];
int Button_Pos_X_last = (last_button_X)*STEP_FRAME_W;
int Button_Pos_Y_last = (last_button_Y)*STEP_FRAME_H;
int Button_Pos_X_new = (last_button_X - 1) * STEP_FRAME_W;
int Button_Pos_Y_new = (last_button_Y)*STEP_FRAME_H;

//Launchpad
#define LP_GREEN 60
#define LP_GREEN_DIM 28
#define LP_RED 15
#define LP_RED_DIM 13
#define LP_AMBER 63
#define LP_AMBER_DIM 29
#define LP_YELLOW 62

byte* LP_grid_notes;
byte* LP_step_notes;
bool LP_grid_bool[64];
const byte LP_octave_notes[12]{ 64, 49, 65, 50, 66, 67, 52, 68, 53, 69, 54, 70 };
bool LP_octave_bool[12];
bool LP_octave_bool_keys[12];
bool LP_step_bool[16];
bool LP_drawOnce[16];

//drawPot Variables
float circlePos;
float circlePos_old;
int dvalue_old;
int dvalue_old2;
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
  int step[NUM_STEPS];  // stores the PITCH VALUE to be played at this step, or 0xFF (255) for NONE. note this is monophonic only (for now)!!
};

struct track_t {
  byte midi_channel;               // stores the MIDI channel that this track should output on; 10 is drums
  sequence_t sequence[NUM_CLIPS];  // the sequence-clips associated with this track
};
//track_T* ctrack;
track_t ctrack[NUM_TRACKS];

//Scales
bool scaleSelect = LOW;
const int scalesQuant = 9;  //how many scales do we have
int scaleSelected = 0;      //variable for scale selecting


const int scales[scalesQuant][12]{
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
  int tone = 0;
  byte shown_octaves = 5;  //
  byte velocity_ON = 96;
  byte velocity_ON_graph = 96;
  float gain = 1;
  byte gain_graph = 127;
  bool mute_state = LOW;
  bool solo_state = LOW;
  bool solo_mutes_state = LOW;

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
  byte lastclip = 0;
  int NoteOffset[256];
  int lastNoteOffset = 0;
  int NoteOffset_graph[256];
  int presetNr[256];
  int lastpresetNr = 0;
  int volume[256];
  int lastvolume = 100;
  int notePlayed;
  int notePlayedLast;
  bool notePressed;
  bool envActive;
  bool playNoteOnce;
  byte MIDI_velocity = 99;
  int MIDItick = 0;
  int MIDItick_16 = 0;
  int MIDItick_reset = 6;
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

  int seqMode = 0;
};
// make an array of 8 channel_types, numbered 0-7
tracks* track;



//channel 1 variables
byte ch1tone;
bool* dsend_noteOff;
bool*** channel1Clip;
