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

const char* pluginName[MAX_PLUGINS]{ "Chrd", "SDrm", "1OSC", "MDrm", "Raw1", "Raw2", "Drum", "MogL", "Strng", "10", "11", "12", "13", "14", "15", "16" };

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
plugin1* pl1;
byte pl1presetNr = 0;

//plugin 2 variables
struct plugin2 {
  byte Pot_Value_graph[12];
  float Pot_Value[12];
};
plugin2* pl2;
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
plugin3* pl3;
byte pl3presetNr = 0;

//plugin 4 variables
struct plugin4 {
  byte Pot_Value_graph[12];
  float Pot_Value[12];
};
plugin4* pl4;
byte pl4presetNr = 0;

//plugin 5 variables
struct plugin5 {
  float Filter1_Frequency = 260;
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
  float Env1_Release_graph = 50;
  byte selected_file;
  byte selected_file_graph = 0;
  byte Volume_graph = 50;
  float Volume;
};
plugin5* pl5;
byte pl5presetNr = 0;
bool pl5enter_was_pushed = true;

//plugin 6 variables
struct plugin6 {
  float Filter1_Frequency = 260;
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
  byte selected_file;
  byte selected_file_graph = 0;
  byte Volume_graph = 50;
  float Volume_rnd;
  float Volume;
};
plugin6* pl6;
byte pl6presetNr = 0;

//plugin7 variables
struct plugin7 {
  //drum11111111111111111111111111111111111111111111111111111111111111111111111111111111 drum 1
  int _1_frequency;
  byte _1_frequency_graph = 50;
  byte _1_length;
  byte _1_length_graph = 50;
  float _1_pitchMod;  //max 2 !!
  byte _1_pitchMod_graph = 50;
  int _1_pitchMod_rnd;
  float _1_secondMix;
  byte _1_secondMixgraph = 50;
  byte _1_filter_graph;
  int _1_filter;
  byte _1_resonance_graph;
  float _1_resonance;
  float _1_dc1_wavefold = 0.06;
  byte _1_dc1_wavefold_graph = 10;
  //noisemod22222222222222222222222222222222222222222222222222222222222222222222222222222 noise mode 2
  float _2_noise1_amp = 1;
  byte _2_noise1_amp_graph = 100;

  byte _2_wfMod_begin;
  byte _2_wfMod_begin_graph;
  float _2_wfMod_amplitude;
  byte _2_wfMod_amplitude_graph;
  int _2_wfMod_frequency;
  byte _2_wfMod_frequency_graph;
  float _2_wfMod_frequencyModulation;
  byte _2_wfMod_frequencyModulation_graph;
  int _2_wfMod_frequencyModulation_rnd;

  int _2_filter_frequency;
  byte _2_filter_frequency_graph;
  float _2_filter_resonance;
  byte _2_filter_resonance_graph;
  byte _2_filter_resonance_rnd;
  float _2_filter_octaveControl;
  byte _2_filter_octaveControl_graph;

  byte _2_Env_Attack;
  byte _2_Env_Attack_graph;
  byte _2_Env_Decay;
  byte _2_Env_Decay_graph;
  int _2_Env_Release;
  byte _2_Env_Release_graph;



  //FM33333333333333333333333333333333333333333333333333333333333333333333333333333333333 FM 3
  float _3_waveformMod3_amplitude;
  byte _3_waveformMod3_amplitude_rnd;
  byte _3_waveformMod3_amplitude_graph;
  int _3_waveformMod3_frequency;
  byte _3_waveformMod3_frequency_graph;


  byte _3_Env2_Attack;
  byte _3_Env2_Attack_graph;
  byte _3_Env2_Decay;
  byte _3_Env2_Decay_graph;
  int _3_Env2_Release;
  byte _3_Env2_Release_graph;


  byte _3_waveformMod2_begin;
  byte _3_waveformMod2_begin_graph;
  float _3_waveformMod2_amplitude;
  byte _3_waveformMod2_amplitude_graph;
  int _3_waveformMod2_frequency;
  byte _3_waveformMod2_frequency_graph;
  float _3_waveformMod2_frequencyModulation;
  byte _3_waveformMod2_frequencyModulation_graph;
  int _3_waveformMod2_frequencyModulation_rnd;

  byte _3_Env3_Attack;
  byte _3_Env3_Attack_graph;
  byte _3_Env3_Decay;
  byte _3_Env3_Decay_graph;
  int _3_Env3_Release;
  byte _3_Env3_Release_graph;

  //4444444444444444444444444444444444444444444444444444444444444444444444444444 noise
  float _4_noise2_amplitude = 1;
  int _4_noise2_amplitude_rnd = 100;
  byte _4_noise2_amplitude_graph = 100;

  float _4_pink1_amplitude = 1;
  int _4_pink1_amplitude_rnd = 100;
  byte _4_pink1_amplitude_graph = 100;

  int _4_biquad1_frequency = 400;
  byte _4_biquad1_frequency_graph;
  float _4_biquad1_resonance;
  byte _4_biquad1_resonance_graph;
  byte _4_biquad1_resonance_rnd;

  byte _4_Env4_Attack;
  byte _4_Env4_Attack_graph;
  byte _4_Env4_Decay;
  byte _4_Env4_Decay_graph;
  byte _4_Env4_Release;
  byte _4_Env4_Release_graph;
};
plugin7* pl7;
byte pl7presetNr = 0;

//plugin 8 variables
struct plugin8 {
  float Filter1_Frequency;
  byte Filter1_Frequency_graph;
  float Filter1_Resonance;
  byte Filter1_Resonance_graph;
  float Filter1_Sweep;
  byte Filter1_Sweep_graph;
  int Env1_Attack;
  byte Env1_Attack_graph;
  int Env1_Decay;
  byte Env1_Decay_graph;
  float Env1_Sustain;
  byte Env1_Sustain_graph;
  int Env1_Release;
  float Env1_Release_graph;
  float note1_Velo = 1;
  float note1_Velo_rnd;
  byte wfSelect;
  byte wfSelect_graph;
};
plugin8* pl8;
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
plugin9* pl9;
byte pl9presetNr = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_SEQMODES 6
#define NFX1_PAGE1 129
#define NFX2_PAGE1 132
#define NFX3_PAGE1 135
#define NFX4_PAGE1 138
#define NFX5_PAGE1 140
const char* seqModes[MAX_SEQMODES]{ "Step", "Grid", "Drop", "Rand", "PolyR", "Chat1" };

//seqmode "grid"
struct Grids {
  byte Pot_Value[12];
  byte Pot_Value_graph[12];
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
  byte Pot_Value[16];
  byte Pot_Value_graph[16];
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
  byte Pot_Value[16];
  byte Pot_Value_graph[16];
  byte Oct1 = 5;
  byte Oct2 = 6;
};
rands* NFX3;
byte NFX3presetNr = 0;
const char* NFX3_ROW1[4]{ "--", "--", "Oct1", "Oct2" };
const char* NFX3_ROW2[4]{ "--", "--", "--", "--" };


//seqmode "PolyR"
struct PolyR {
  byte Pot_Value[12];
  byte Pot_Value_graph[12];
  byte reset[12];
};
PolyR* NFX4;
byte NFX4presetNr = 0;




//seqmode Chat1
struct Chat1 {
  // Initialize the array of input values (assuming they are provided by some external source)
  int Pot_Value[4];
  int Pot_Value_graph[4] = { 64, 64, 64, 64 };
};
Chat1* NFX5;
byte NFX5presetNr = 0;
int stepValues[numTracks];
