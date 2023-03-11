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
#define PLUGIN11_PAGE1 50
#define PLUGIN12_PAGE1 51
#define PLUGIN13_PAGE1 52
#define PLUGIN14_PAGE1 53
#define PLUGIN15_PAGE1 54
#define PLUGIN16_PAGE1 55



#define PLUGIN1_PAGE2 60
#define PLUGIN1_PAGE3 61
#define PLUGIN1_PAGE4 62
#define PLUGIN7_PAGE2 63
#define PLUGIN7_PAGE3 64

#define MAX_ENC_RANGE 127
#define ATTACK_TIME 700
#define DECAY_TIME 700
#define SUSTAIN_LVL 127.00
#define RELEASE_TIME 1600
#define SVF_RES 25.40
#define SVF_SWP 18.14
#define SVF_TYP 42



int oldWave; //wfselect


int pl2Pot[num_voice];
int pl4Pot[num_voice];


const char* pluginName[MAX_PLUGINS]{ "Chrd", "SDrm", "1OSC", "MDrm", "Raw1", "Raw2", "Drum", "MogL", "Strng", "dtune", "11", "12", "13", "14", "15", "16" };




struct plugin_preset_data_t {
  byte Pot_Value[16]{ 0 };
  byte Pot_Value2[16]{ 0 };
};

struct plugin_t {
  plugin_preset_data_t preset[MAX_PRESETS];
};
plugin_t* plugin;


byte plpreset[MAX_PLUGINS]{ 0 };
#define pl1NR 0
#define pl1OSC 0
#define pl1OSC_MOD0 0
#define pl1OSC_MOD1 1
#define pl1OSC_MOD2 2
#define pl1OSC_MOD3 3
#define pl1SVF 0
#define pl1ADSR1 0
#define pl1ADSR2 1

#define pl3NR 2
#define pl3OSC 1
#define pl3OSC_MOD 4
#define pl3SVF 1
#define pl3ADSR1 2
#define pl3ADSR2 3

#define pl5NR 4
#define pl5RAW 0
#define pl5SVF 2
#define pl5ADSR1 4
#define pl5ADSR2 5

#define pl6NR 5
#define pl6RAW 1
#define pl6SVF 3
#define pl6ADSR1 6
#define pl6ADSR2 7

#define pl7NR 6
#define pl7DRUM 0
#define pl7OSC1 5
#define pl7OSC2 6
#define pl7WHITE1 0
#define pl7WHITE2 1
#define pl7SVF1 4
#define pl7SVF2 5
#define pl7ADSR1 8
#define pl7ADSR2 9
#define pl7ADSR3 10
#define pl7ADSR4 11


#define pl8NR 7
#define pl8OSC 2
#define pl8LADDER 0
#define pl8ADSR1 12
#define pl8ADSR2 13

#define pl9NR 8

#define pl10NR 9
#define pl10OSC_0 4
#define pl10OSC_1 5
#define pl10WHITE 2
#define pl10SVF 7
#define pl10ADSR1 14
#define pl10ADSR2 15
float pl10detune;



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_SEQMODES 6
#define NFX1_PAGE1 129
#define NFX2_PAGE1 132
#define NFX3_PAGE1 135
#define NFX4_PAGE1 138
#define NFX5_PAGE1 140
const char* seqModes[MAX_SEQMODES]{ "Step", "Grid", "Drop", "Rand", "PolyR", "Ratch" };

//seqmode "grid"
struct Grids {
  byte Pot_Value[12]{ 0 };
  //  byte Pot_Value_graph[12]{0};
};
Grids* NFX1;
byte NFX1presetNr = 0;
byte clock_count = 0;
#define BEAT_ARRAY_SIZE 100


const bool beatArray[BEAT_ARRAY_SIZE][NUM_STEPS] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  //silence 0
  { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },  //kick
  { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },  //kick
  { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 },  //kick
  { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },  //kick
  { 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1 },  //kick
  { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0 },  //kick
  { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },  //kick
  { 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0 },
  { 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
  { 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0 },
  { 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
  { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0 },  //kick
  { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0 },  //kick
  { 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },  //kick
  { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },  //kick
  { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },  //kick
  { 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0 },  //kick
  { 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },  //kick
  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },  //snare
  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },  //snare
  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0 },  //snare
  { 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0 },  //snare
  { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0 },  //snare
  { 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1 },  //snare
  { 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0 },  //snare
  { 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1 },  //snare
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },  //hihat
  { 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0 },  //hihat
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },  //hihat
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },  //hihat
  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },  //hihat
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0 },  //hihat
  { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  //hihat
  { 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1 },  //hihat
  { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },  //hihat
  { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },  //hihat
  { 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 },
  { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },  //
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
  { 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0 },
  { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 },  //
  { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },
  { 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0 },
  { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0 },
  { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0 },
  { 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0 },
  { 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
  { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0 },
  { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },  //
  { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
  { 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
  { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 },
  { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
  { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0 },
  { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0 },
  { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
  { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0 },
  { 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
  { 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0 },
  { 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
  { 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
  { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1 },
  { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1 },
  { 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
  { 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
  { 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
  { 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
  { 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0 },  //perc
  { 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0 },  //perc
  { 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0 },  //perc
  { 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 },  //perc
  { 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1 },  //perc
  { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1 },  //perc
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }   //perc
};

//seqmode "dropseq"
struct Drops {
  byte Pot_Value[16]{ 0 };
};
Drops* NFX2;
byte NFX2presetNr = 0;
byte cc23 = 5;
byte cc24 = 6;
byte octave;
byte maxValIndex;
byte maxVal = 0;
byte analogReadArray[16];
const char* NFX2_ROW1[4]{ "Drop", "Tide", "Oct1", "Oct2" };




//seqmode "Rand"
struct rands {
  byte Pot_Value[16]{ 5 };
  byte Oct1 = 5;
  byte Oct2 = 6;
};
rands* NFX3;
byte NFX3presetNr = 0;
const char* NFX3_ROW1[4]{ "--", "--", "Oct1", "Oct2" };
const char* NFX3_ROW2[4]{ "--", "--", "--", "--" };


//seqmode "PolyR"
struct PolyR {
  byte Pot_Value[12]{ 15 };
  byte reset[12];
};
PolyR* NFX4;
byte NFX4presetNr = 0;




//seqmode Ratch
struct Ratch {
  // Initialize the array of input values (assuming they are provided by some external source)
  int Pot_Value[12]{ 3 };
  int repeats[12] = { 0 };
};
//seqmode ratcheting
bool*** ratchet;
Ratch* NFX5;
byte NFX5presetNr = 0;
byte repeatED[12]{ 5 };

