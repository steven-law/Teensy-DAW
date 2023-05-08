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
#define PIX_OFFSET_Y 18
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
#define POTPICKUP 10

#define AUDIO_MEMORYS 600
#define SPI_FREQUENCY 40000000
#define SPI_READ_FREQUENCY 10000000

#define VELOCITYOFF 0
static const int VALUE_NOTEOFF = 0;


//variables for own clock
#define NUM_CLIPS 9
#define NUM_TRACKS 8
#define MAX_VOICES 12
#define TICKS_PER_STEP 6
#define NUM_STEPS 16
#define TICKS_PER_BAR 96
#define MAX_PHRASES 256
#define FS_MIN_TEMPO 55
#define FS_MAX_TEMPO 200

#define tuning 440


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
#define MAX_SONGMODE_PAGES 16
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
#define MAX_WAV_FILES 127
const char* wavKits[12]{ "K", "S", "H", "H", "C", "P", "P", "P", "F", "F", "X", "X" };  //kick, snare, hihat, hihat, clap, perc, perc, perc, FX, FX, FX2, FX2
const char* showVOL[12]{ "Vol1", "Vol2", "Vol3", "Vol4", "Vol5", "Vol6", "Vol7", "Vol8", "Vol9", "Vol10", "Vol11", "Vol12" };
const char* noteNames[12]{ "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
char* trackNames_short[9]{ "TrD", "Tr2", "Tr3", "Tr4", "Tr5", "Tr6", "Tr7", "Tr8", "" };
const char* trackNames_long[NUM_TRACKS]{ "track1", "track2", "track3", "track4", "track5", "track6", "track7", "track8" };
char _trackname[20];
char _RawFile[20];
char _RawFile2[20];
char _RecFile[20];
char _pl2Filename[10];
char _pl11Filename[10];
char _pl11Filename1[10];
char _pl11Filename2[10];
char _pl11Filename3[10];
char _pl11Filename4[10];
char _pl11Filename5[10];
char _pl11Filename6[10];
char _pl11Filename7[10];
char _pl11Filename8[10];
char _pl11Filename9[10];
char _pl11Filename10[10];
char _pl11Filename11[10];
char _pl11Filename12[10];
const char* sideTabDigit[NUM_TRACKS]{ "D", "2", "3", "4", "5", "6", "7", "8" };
const char* filterType[3] = { "LPF", "BPF", "HPF" };




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

// The file where data is recorded
File frec;
#define XPOS_OFFSET 32
#define YPOS_OFFSET 150
#define WAVEHEIGHT 64




//FX variables

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
byte arrangmentSelect = 0;
byte songpages;





//touchscreen variables
byte gridTouchX;  //decided to handle touchthingys with a grid, so here it is, 20 grids
byte gridTouchY;  //decided to handle touchthingys with a grid, so here it is, 15 grids
byte trackTouchY;
int pixelTouchX;





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
bool rowButtonpressed = false;
int Potentiometer[4];
bool enc_moved[4]{ 0, 0, 0, 0 };
int encoded[4];
bool enc_button[4];
byte incomingCC[4];
bool incomingCC_changed[4]{ false };

//button variables
#define BUTTON0 68
#define BUTTON1 70
#define BUTTON2 57
#define BUTTON3 66
#define BUTTON4 55
#define BUTTON5 53
#define BUTTON6 51
#define BUTTON7 49
#define BUTTON8 69
#define BUTTON9 67
#define BUTTON10 65
#define BUTTON11 56
#define BUTTON12 52
#define BUTTON13 54
#define BUTTON14 50
#define BUTTON15 48
bool button[16]{};
bool touched;

bool showSerialonce = false;
bool otherCtrlButtons = true;
uint16_t tftRAM[16][16];

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




struct tick_t {
  byte voice[MAX_VOICES]{ 0 };
  byte velo[MAX_VOICES]{ 0 };
};
struct sequence_t {
  tick_t tick[TICKS_PER_BAR];
};
struct track_t {
  sequence_t sequence[NUM_CLIPS];  // the sequence-clips associated with this track
};
//track_t ctrack[NUM_TRACKS];
track_t* ctrack = nullptr;



//Scales
bool scaleSelect = LOW;
const int MAX_SCALES = 13;  //how many scales do we have
int scaleSelected = 0;      //variable for scale selecting


const int scales[MAX_SCALES][12]{
  //bool array for greying out notes that are not in the scale
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  //Chromatic
  { 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 },  //Major
  { 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0 },  //Natural Minor
  { 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1 },  //Harmonic Minor
  { 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1 },  //Melodic Minor
  { 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0 },  //Dorian
  { 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0 },  //Mixolydian
  { 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0 },  //Phrygian
  { 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 },  //Lydian
  { 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0 },  //Pentatonic Major
  { 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0 },  //Pentatonic Minor
  { 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 },  //Blues Major
  { 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0 }   //Blues Minor
};

const char* scaleNames[MAX_SCALES] = { "Chromatic", "Major", "Natural Minor", "Harmonic Minor", "Melodic Minor", "Dorian", "Mixolydian", "Phrygian", "Lydian", "Pentatonic Major", "Pentatonic Minor", "Blues Major", "Blues Minor" };  // Scale Names for selecting
const char* scaleNamesShort[MAX_SCALES] = { "Chrom", "Major", "NatMi", "HarMi", "MelMi", "Dor", "Mixol", "Phryg", "Lyd", "PeMaj", "PeMin", "BlMaj", "BlMin" };                                                                          // Scale Names for selecting



uint32_t seq_MIDItick;

int seq_tempo = 120;
bool seq_rec = false;


//Track Variables
byte desired_track;
byte desired_instrument;
//track 2-8 variables
struct tracks {
  byte MIDIchannel = 0;    // (although you may not need this, depends on how you structure thing later)
  byte clip_songMode = 1;  //clipselection from the arrangement

  byte midicc_value_row_1[4];
  byte midicc_number_row_1[4]{ 20, 21, 22, 23 };
  byte midicc_value_row_2[4];
  byte midicc_number_row_2[4]{ 24, 25, 26, 27 };
  byte midicc_value_row_3[4];
  byte midicc_number_row_3[4];
  byte midicc_value_row_4[4];
  byte midicc_number_row_4[4];

  byte arrangment1[256];
  int NoteOffset[256];
  int NoteOffset_graph[256];
  int Ttrckprst[256];
  int volume[256];
  //copy clipinfo to next clip (in songmode when rec is active)
  byte lastclip = 0;
  int lastNoteOffset = 0;
  int lastpresetNr = 0;
  int lastvolume = 100;

  int notePlayed[MAX_VOICES] = { 0 };
  bool notePressed[MAX_VOICES] = { false };
  bool envActive[MAX_VOICES] = { false };
  bool playNoteOnce[MAX_VOICES] = { false };
  byte MIDI_velocity[MAX_VOICES] = { 99 };

  int MIDItick = 0;
  int MIDItick_16 = 0;
  bool tick_true[MAX_VOICES] = { false };
};
// make an array of 8 channel_types, numbered 0-7
tracks* track;
