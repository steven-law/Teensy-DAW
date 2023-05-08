//please use this Audio GUI from Newdigate
//https://newdigate.github.io/teensy-eurorack-audio-gui/
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc pl10dc2;                 //xy=65.99999237060547,1984.2001028060913
AudioSynthWaveformDc pl10dc3;                 //xy=69.19999694824219,2107.199996948242
AudioSynthWaveform pl10waveform1;             //xy=77.5,1896.2001028060913
AudioMixer4 pl10mixer4;                       //xy=137.20000457763672,2046.2001037597656
AudioPlaySdRaw playSdRaw10;                   //xy=182.1999969482422,2427.199996948242
AudioPlaySdRaw playSdRaw12;                   //xy=182.20000076293945,2465.1998653411865
AudioPlaySdRaw playSdRaw11;                   //xy=185.20000457763672,2449.1998653411865
AudioPlaySdRaw playSdRaw9;                    //xy=187.1999969482422,2399.199996948242
AudioPlaySdRaw playSdRaw3;                    //xy=192.20000076293945,2258.199863433838
AudioPlaySdRaw playSdRaw4;                    //xy=192.1999969482422,2283.199864387512
AudioPlaySdRaw playSdRaw2;                    //xy=194.20000457763672,2235.199863433838
AudioPlaySdRaw playSdRaw1;                    //xy=195.1999969482422,2210.1998620033264
AudioMixer4 pl10mixer3;                       //xy=208.19998168945312,1965.2001037597656
AudioPlaySdRaw playSdRaw8;                    //xy=208.20001029968262,2375.199866294861
AudioPlaySdRaw playSdRaw6;                    //xy=210.2000026702881,2331.1998653411865
AudioPlaySdRaw playSdRaw5;                    //xy=211.20000648498535,2307.199863433838
AudioPlaySdRaw playSdRaw7;                    //xy=211.20001029968262,2352.1998653411865
AudioSynthWaveformDc pl10dc1;                 //xy=266.99997329711914,2139.199860572815
AudioSynthWaveform pl1waveform1;              //xy=282.1999740600586,100.0001163482666
AudioSynthNoiseWhite pl10noise1;              //xy=297.1999702453613,2078.200086593628
AudioSynthWaveformDc pl5dc1;                  //xy=311.1999702453613,1261.0001049041748
AudioSynthNoiseWhite pl7noise1;               //xy=310.1999702453613,1545.0001049041748
AudioPlayMemory playMem9;                     //xy=312.1999702453613,1045.0001049041748
AudioSynthWaveformDc pl6dc1;                  //xy=313.1999702453613,1365.0001049041748
AudioPlayMemory playMem10;                    //xy=317.1999702453613,1076.0001049041748
AudioPlayMemory playMem7;                     //xy=322.1999702453613,975.0001049041748
AudioPlayMemory playMem8;                     //xy=322.1999702453613,1012.0001049041748
AudioPlayMemory playMem5;                     //xy=332.1999702453613,899.0001049041748
AudioPlayMemory playMem6;                     //xy=333.1999702453613,937.0001049041748
AudioPlaySdWav playSdWav12;                   //xy=337.1999702453613,710.0001049041748
AudioPlayMemory playMem1;                     //xy=337.1999702453613,759.0001049041748
AudioPlaySdWav playSdWav7;                    //xy=339.1999702453613,529.0001049041748
AudioPlayMemory playMem2;                     //xy=338.1999702453613,795.0001049041748
AudioPlaySdWav playSdWav9;                    //xy=339.1999702453613,601.0001049041748
AudioPlaySdWav playSdWav3;                    //xy=340.1999702453613,374.0001049041748
AudioPlaySdWav playSdWav10;                   //xy=339.1999702453613,635.0001049041748
AudioPlaySdWav playSdWav4;                    //xy=340.1999702453613,410.0001049041748
AudioPlaySdWav playSdWav11;                   //xy=339.1999702453613,674.0001049041748
AudioPlaySdWav playSdWav8;                    //xy=340.1999702453613,566.0001049041748
AudioPlayMemory playMem11;                    //xy=339.1999702453613,1115.0001049041748
AudioSynthWaveformSine pl7waveformMod3;       //xy=337.1999702453613,1629.0001049041748
AudioPlaySdWav playSdWav2;                    //xy=343.1999702453613,337.0001049041748
AudioPlaySdWav playSdWav5;                    //xy=343.1999702453613,450.0001049041748
AudioPlaySdWav playSdWav6;                    //xy=343.1999702453613,490.0001049041748
AudioPlaySdWav playSdWav1;                    //xy=346.1999702453613,298.0001049041748
AudioPlayMemory playMem12;                    //xy=344.1999702453613,1153.0001049041748
AudioPlayMemory playMem3;                     //xy=347.1999702453613,829.0001049041748
AudioSynthWaveformPWM pl10pwm1;               //xy=346.19997787475586,1996.200207710266
AudioPlayMemory playMem4;                     //xy=354.1999702453613,865.0001049041748
AudioSynthWaveformPWM pl10pwm2;               //xy=356.1999740600586,2036.2002081871033
AudioSynthWaveformDc pl8dc1;                  //xy=382.1999702453613,1838.0002727508545
AudioSynthNoiseWhite pl7noise2;               //xy=400.1999702453613,1686.0001049041748
AudioSynthNoisePink pl7pink1;                 //xy=400.1999702453613,1726.0001049041748
AudioSynthKarplusStrong pl9string1;           //xy=403.19994354248047,1895.0002737045288
AudioEffectEnvelope pl10envelope2;            //xy=430.1999740600586,2139.199860572815
AudioMixer4 pl11drummixer1;                   //xy=435.1999969482422,2230.199951171875
AudioMixer4 pl11drummixer2;                   //xy=437.1999969482422,2319.199951171875
AudioSynthWaveform pl9bpinput;                //xy=443.1999397277832,1940.0002737045288
AudioMixer4 pl11drummixer3;                   //xy=446.1999969482422,2411.199951171875
AudioEffectEnvelope pl5envelope2;             //xy=459.1999702453613,1260.0001049041748
AudioPlaySdResmp playSdPitch2;                //xy=459.1999702453613,1313.0001049041748
AudioEffectEnvelope pl6envelope2;             //xy=461.1999702453613,1364.0001049041748
AudioPlaySdResmp playSdPitch1;                //xy=463.1999702453613,1214.0001049041748
AudioSynthSimpleDrum pl7drum1;                //xy=466.1999702453613,1466.0001049041748
AudioMixer4 pl10mixer1;                       //xy=469.1999740600586,2071.200086593628
AudioSynthWaveformModulated pl7waveformMod1;  //xy=473.1999702453613,1547.0001049041748
AudioSynthWaveform pl8waveform1;              //xy=484.2000045776367,1794.0002717971802
AudioSynthWaveformModulated pl1waveformMod1;  //xy=493.1999702453613,39.000104904174805
AudioSynthWaveformModulated pl1waveformMod2;  //xy=493.1999702453613,80.0001049041748
AudioSynthWaveformModulated pl1waveformMod4;  //xy=493.1999702453613,162.0001049041748
AudioSynthWaveformModulated pl1waveformMod3;  //xy=494.1999702453613,122.0001049041748
AudioEffectEnvelope pl7envelope2;             //xy=517.1999702453613,1627.0001049041748
AudioEffectEnvelope pl8envelope2;             //xy=523.2000007629395,1837.0002727508545
AudioSynthWaveform pl3waveform1;              //xy=541.1999702453613,590.0001049041748
AudioSynthWaveformDc pl3dc1;                  //xy=542.1999702453613,679.0001049041748
AudioMixer4 pl7mixer4;                        //xy=539.1999702453613,1714.0001049041748
AudioMixer4 drummixer1;                       //xy=547.1999702453613,322.0001049041748
AudioMixer4 drummixer2;                       //xy=549.1999702453613,411.0001049041748
AudioMixer4 drummixer3;                       //xy=558.1999702453613,503.0001049041748
AudioMixer4 pl4drummixer1;                    //xy=559.1999702453613,776.0001049041748
AudioMixer4 pl4drummixer2;                    //xy=561.1999702453613,865.0001049041748
AudioMixer4 pl4drummixer3;                    //xy=570.1999702453613,957.0001049041748
AudioFilterStateVariable pl10filter1;         //xy=593.1999702453613,2134.2001037597656
AudioFilterStateVariable pl9bpfilter;         //xy=610.2000350952148,1923.0002727508545
AudioFilterStateVariable pl5filter1;          //xy=623.1999702453613,1226.0001049041748
AudioFilterStateVariable pl6filter1;          //xy=625.1999702453613,1330.0001049041748
AudioFilterStateVariable pl7filter1;          //xy=636.1999702453613,1466.0001049041748
AudioFilterStateVariable pl7filter2;          //xy=637.1999702453613,1556.0001049041748
AudioMixer4 mixer1;                           //xy=663.1999702453613,74.0001049041748
AudioSynthWaveformDc pl1dc1;                  //xy=667.1999702453613,177.0001049041748
AudioMixer4 pl11drummixer4;                   //xy=663.1999969482422,2239.199951171875
AudioSynthWaveformModulated pl3waveformMod1;  //xy=685.1999702453613,551.0001049041748
AudioEffectEnvelope pl3envelope2;             //xy=685.1999702453613,676.0001049041748
AudioFilterBiquad pl7biquad1;                 //xy=681.1999702453613,1706.0001049041748
AudioFilterLadder pl8filter1;                 //xy=681.1999740600586,1814.0002717971802
AudioSynthWaveformModulated pl7waveformMod2;  //xy=693.1999702453613,1630.0001049041748
AudioMixer4 drummixer4;                       //xy=732.1999702453613,432.0001049041748
AudioMixer4 pl10mixer2;                       //xy=737.200008392334,2070.199598312378
AudioFilterStateVariable pl3filter1;          //xy=747.1999702453613,618.0001049041748
AudioEffectEnvelope envelope1;                //xy=750.1999702453613,134.0001049041748
AudioMixer4 pl6mixer1;                        //xy=760.1999702453613,1342.0001049041748
AudioMixer4 pl5mixer1;                        //xy=775.1999702453613,1127.0001049041748
AudioMixer4 pl9mixer1;                        //xy=772.2000350952148,1918.2001037597656
AudioFilterStateVariable filter1;             //xy=783.1999702453613,79.0001049041748
AudioMixer4 pl4drummixer4;                    //xy=787.1999702453613,785.0001049041748
AudioEffectEnvelope pl7envelope1;             //xy=790.1999702453613,1541.0001049041748
AudioEffectEnvelope pl8envelope1;             //xy=844.2000350952148,1812.0002727508545
AudioEffectEnvelope pl7envelope4;             //xy=869.1999702453613,1704.0001049041748
AudioEffectEnvelope pl7envelope3;             //xy=875.1999702453613,1641.0001049041748
AudioEffectEnvelope pl5envelope1;             //xy=879.1999702453613,1216.0001049041748
AudioAmplifier pl2amp2;                       //xy=891.1999702453613,440.0001049041748
AudioMixer4 pl3mixer1;                        //xy=892.1999702453613,578.0001049041748
AudioEffectEnvelope pl6envelope1;             //xy=892.1999702453613,1317.0001049041748
AudioEffectEnvelope pl10envelope1;            //xy=889.200008392334,2069.1999645233154
AudioAmplifier pl14amp2;                      //xy=900.1999702453613,2719.000104904175
AudioAmplifier pl12amp2;                      //xy=905.1999702453613,2356.000104904175
AudioAmplifier pl16amp2;                      //xy=904.1999702453613,2942.000104904175
AudioAmplifier pl11amp2;                      //xy=907.1999702453613,2237.000104904175
AudioMixer4 pl1mixer2;                        //xy=918.1999702453613,81.0001049041748
AudioAmplifier pl13amp2;                      //xy=917.1999702453613,2571.000104904175
AudioAmplifier pl10amp2;                      //xy=923.1999702453613,2154.000104904175
AudioAmplifier pl9amp2;                       //xy=930.2000370025635,1948.0002727508545
AudioAmplifier pl15amp2;                      //xy=928.1999702453613,2786.000104904175
AudioAmplifier pl4amp2;                       //xy=939.1999702453613,761.0001049041748
AudioEffectEnvelope pl3envelope1;             //xy=969.1999702453613,630.0001049041748
AudioAmplifier pl8amp2;                       //xy=986.1999702453613,1823.0001049041748
AudioAmplifier pl7amp2;                       //xy=1006.1999702453613,1551.0001049041748
AudioMixer4 pl7mixer2;                        //xy=1023.1999702453613,1747.0001049041748
AudioAmplifier pl2amp;                        //xy=1029.1999702453613,442.0001049041748
AudioAmplifier pl6amp2;                       //xy=1031.1999702453613,1284.0001049041748
AudioEffectEnvelope envelope2;                //xy=1036.1999702453613,139.0001049041748
AudioAmplifier pl3amp2;                       //xy=1036.1999702453613,581.0001049041748
AudioMixer4 pl7mixer1;                        //xy=1038.1999702453613,1645.0001049041748
AudioAmplifier pl5amp2;                       //xy=1042.1999702453613,1153.0001049041748
AudioAmplifier pl4amp;                        //xy=1053.1999702453613,773.0001049041748
AudioAmplifier pl11amp;                       //xy=1054.1999702453613,2239.000104904175
AudioAmplifier pl10amp;                       //xy=1056.1999702453613,2145.000104904175
AudioAmplifier pl16amp;                       //xy=1058.1999702453613,2946.000104904175
AudioAmplifier pl12amp;                       //xy=1062.1999702453613,2353.000104904175
AudioAmplifier pl15amp;                       //xy=1073.1999702453613,2787.000104904175
AudioAmplifier pl13amp;                       //xy=1074.1999702453613,2567.000104904175
AudioAmplifier pl14amp;                       //xy=1075.1999702453613,2707.000104904175
AudioAmplifier pl8amp;                        //xy=1086.1999702453613,1861.0001049041748
AudioAmplifier pl9amp;                        //xy=1086.1999702453613,1982.0001049041748
AudioAmplifier pl1amp2;                       //xy=1104.1999702453613,93.0001049041748
AudioAmplifier pl7amp;                        //xy=1106.1999702453613,1575.0001049041748
AudioAmplifier pl3amp;                        //xy=1128.1999702453613,625.0001049041748
AudioAmplifier pl5amp;                        //xy=1127.1999702453613,1215.0001049041748
AudioAmplifier pl6amp;                        //xy=1130.1999702453613,1317.0001049041748
AudioMixer4 pl7mixer3;                        //xy=1175.1999702453613,1698.0001049041748
AudioAmplifier pl2FX2;                        //xy=1182.1999702453613,444.0001049041748
AudioAmplifier pl2FX3;                        //xy=1182.1999702453613,466.0001049041748
AudioAmplifier pl2dry;                        //xy=1185.1999702453613,407.0001049041748
AudioAmplifier pl2FX1;                        //xy=1186.1999702453613,425.0001049041748
AudioAmplifier pl4FX2;                        //xy=1196.1999702453613,776.0001049041748
AudioAmplifier pl4FX3;                        //xy=1196.1999702453613,796.0001049041748
AudioAmplifier pl4dry;                        //xy=1197.1999702453613,734.0001049041748
AudioAmplifier pl4FX1;                        //xy=1197.1999702453613,755.0001049041748
AudioAmplifier pl1amp;                        //xy=1221.1999702453613,174.0001049041748
AudioAmplifier pl14FX3;                       //xy=1211.1999702453613,2728.000104904175
AudioAmplifier pl14FX2;                       //xy=1213.1999702453613,2706.000104904175
AudioAmplifier pl14dry;                       //xy=1216.1999702453613,2669.000104904175
AudioAmplifier pl14FX1;                       //xy=1216.1999702453613,2684.000104904175
AudioAmplifier pl8dry;                        //xy=1220.1999702453613,1829.0001049041748
AudioAmplifier pl8FX1;                        //xy=1220.1999702453613,1851.0001049041748
AudioAmplifier pl10dry;                       //xy=1219.1999702453613,2117.000104904175
AudioAmplifier pl8FX2;                        //xy=1221.1999702453613,1872.0001049041748
AudioAmplifier pl8FX3;                        //xy=1221.1999702453613,1895.0001049041748
AudioAmplifier pl16FX3;                       //xy=1218.1999702453613,2975.000104904175
AudioAmplifier pl10FX1;                       //xy=1222.1999702453613,2136.000104904175
AudioAmplifier pl10FX2;                       //xy=1222.1999702453613,2153.000104904175
AudioAmplifier pl10FX3;                       //xy=1223.1999702453613,2172.000104904175
AudioAmplifier pl16FX2;                       //xy=1220.1999702453613,2953.000104904175
AudioAmplifier pl13FX3;                       //xy=1222.1999702453613,2567.000104904175
AudioAmplifier pl13FX2;                       //xy=1224.1999702453613,2545.000104904175
AudioAmplifier pl16dry;                       //xy=1223.1999702453613,2916.000104904175
AudioAmplifier pl16FX1;                       //xy=1223.1999702453613,2931.000104904175
AudioAmplifier pl9dry;                        //xy=1227.1999702453613,1971.0001049041748
AudioAmplifier pl9FX1;                        //xy=1228.1999702453613,1989.0001049041748
AudioAmplifier pl9FX2;                        //xy=1228.1999702453613,2006.0001049041748
AudioAmplifier pl13dry;                       //xy=1226.1999702453613,2507.000104904175
AudioAmplifier pl11dry;                       //xy=1228.1999702453613,2214.000104904175
AudioAmplifier pl13FX1;                       //xy=1227.1999702453613,2523.000104904175
AudioAmplifier pl11FX2;                       //xy=1230.1999702453613,2248.000104904175
AudioAmplifier pl11FX3;                       //xy=1230.1999702453613,2266.000104904175
AudioAmplifier pl9FX3;                        //xy=1231.1999702453613,2026.0001049041748
AudioAmplifier pl12dry;                       //xy=1230.1999702453613,2310.000104904175
AudioAmplifier pl15FX3;                       //xy=1230.1999702453613,2826.000104904175
AudioAmplifier pl11FX1;                       //xy=1233.1999702453613,2230.000104904175
AudioAmplifier pl15FX2;                       //xy=1232.1999702453613,2804.000104904175
AudioAmplifier pl7dry;                        //xy=1238.1999702453613,1563.0001049041748
AudioAmplifier pl7FX2;                        //xy=1239.1999702453613,1603.0001049041748
AudioAmplifier pl7FX3;                        //xy=1239.1999702453613,1626.0001049041748
AudioAmplifier pl15dry;                       //xy=1235.1999702453613,2767.000104904175
AudioAmplifier pl15FX1;                       //xy=1235.1999702453613,2782.000104904175
AudioAmplifier pl7FX1;                        //xy=1240.1999702453613,1583.0001049041748
AudioAmplifier pl12FX1;                       //xy=1239.1999702453613,2341.000104904175
AudioAmplifier pl12FX2;                       //xy=1241.1999702453613,2358.000104904175
AudioAmplifier pl3dry;                        //xy=1249.1999702453613,602.0001049041748
AudioAmplifier pl3FX1;                        //xy=1249.1999702453613,625.0001049041748
AudioAmplifier pl3FX2;                        //xy=1249.1999702453613,653.0001049041748
AudioAmplifier pl12FX3;                       //xy=1243.1999702453613,2382.000104904175
AudioAmplifier pl3FX3;                        //xy=1251.1999702453613,669.0001049041748
AudioAmplifier pl6FX1;                        //xy=1263.1999702453613,1330.0001049041748
AudioAmplifier pl6dry;                        //xy=1264.1999702453613,1310.0001049041748
AudioAmplifier pl6FX2;                        //xy=1264.1999702453613,1354.0001049041748
AudioAmplifier pl5FX3;                        //xy=1266.1999702453613,1261.0001049041748
AudioAmplifier pl6FX3;                        //xy=1266.1999702453613,1378.0001049041748
AudioAmplifier pl5FX1;                        //xy=1267.1999702453613,1219.0001049041748
AudioAmplifier pl5dry;                        //xy=1268.1999702453613,1198.0001049041748
AudioAmplifier pl5FX2;                        //xy=1268.1999702453613,1242.0001049041748
AudioAmplifier pl1FX3;                        //xy=1304.1999702453613,343.0001049041748
AudioAmplifier pl1dry;                        //xy=1314.1999702453613,220.0001049041748
AudioAmplifier pl1FX1;                        //xy=1316.1999702453613,258.0001049041748
AudioAmplifier pl1FX2;                        //xy=1321.1999702453613,301.0001049041748
AudioMixer4 mixer6;                           //xy=1426.1999702453613,1273.0001049041748
AudioMixer4 FX2mixer1;                        //xy=1438.1999702453613,695.0001049041748
AudioMixer4 mixer5;                           //xy=1440.1999702453613,531.0001049041748
AudioMixer4 FX3mixer2;                        //xy=1437.1999702453613,1530.0001049041748
AudioMixer4 FX1mixer1;                        //xy=1441.1999702453613,608.0001049041748
AudioMixer4 FX2mixer2;                        //xy=1438.1999702453613,1443.0001049041748
AudioMixer4 FX1mixer2;                        //xy=1439.1999702453613,1358.0001049041748
AudioMixer4 FX3mixer1;                        //xy=1443.1999702453613,782.0001049041748
AudioMixer4 FX2mixer4;                        //xy=1474.1999702453613,2160.000104904175
AudioMixer4 FX1mixer6;                        //xy=1480.1999702453613,2632.000104904175
AudioMixer4 drymixer3;                        //xy=1481.1999702453613,2546.000104904175
AudioMixer4 FX3mixer6;                        //xy=1481.1999702453613,2786.000104904175
AudioMixer4 FX2mixer6;                        //xy=1482.1999702453613,2707.000104904175
AudioMixer4 FX3mixer4;                        //xy=1489.1999702453613,2232.000104904175
AudioMixer4 FX1mixer4;                        //xy=1497.1999702453613,2076.000104904175
AudioMixer4 mixer10;                          //xy=1500.1999702453613,1991.0001049041748
AudioMixer4 drymixer2;                        //xy=1826.1999702453613,698.0001049041748
AudioMixer4 FX2mixer3;                        //xy=1830.1999702453613,878.0001049041748
AudioMixer4 FX3mixer3;                        //xy=1832.1999702453613,967.0001049041748
AudioMixer4 FX1mixer3;                        //xy=1836.1999702453613,795.0001049041748
AudioMixer4 FX3mixer5;                        //xy=2083.1999702453613,976.0001049041748
AudioMixer4 drymixer1;                        //xy=2097.1999702453613,699.0001049041748
AudioMixer4 FX1mixer5;                        //xy=2101.1999702453613,805.0001049041748
AudioMixer4 FX2mixer5;                        //xy=2104.1999702453613,888.0001049041748
AudioEffectReverb reverb1;                    //xy=2283.1999702453613,767.0001049041748
AudioEffectBitcrusher bitcrusher2;            //xy=2297.1999702453613,835.0001049041748
AudioFilterStateVariable dlfilter1;           //xy=2320.1999702453613,1004.0001049041748
AudioMixer4 dlmixer1;                         //xy=2322.1999702453613,949.0001049041748
AudioEffectDelay dldelay1;                    //xy=2324.1999702453613,1115.0001049041748
AudioInputI2S i2s2;                           //xy=2490.1999702453613,914.0001049041748
AudioMixer4 mixer9;                           //xy=2520.1999702453613,719.0001049041748
AudioAmplifier amp1;                          //xy=2640.1999702453613,831.0001049041748
AudioMixer4 mixer11;                          //xy=2710.1999702453613,691.0001049041748
AudioRecordQueue queue1;                      //xy=2771.1999702453613,867.0001049041748
AudioAnalyzePeak peak1;                       //xy=2773.1999702453613,914.0001049041748
AudioOutputI2S i2s1;                          //xy=2879.1999702453613,693.0001049041748
AudioConnection patchCord1(pl10dc2, 0, pl10mixer3, 1);
AudioConnection patchCord2(pl10dc3, 0, pl10mixer4, 1);
AudioConnection patchCord3(pl10waveform1, 0, pl10mixer3, 0);
AudioConnection patchCord4(pl10waveform1, 0, pl10mixer4, 0);
AudioConnection patchCord5(pl10mixer4, pl10pwm2);
AudioConnection patchCord6(playSdRaw10, 0, pl11drummixer3, 1);
AudioConnection patchCord7(playSdRaw12, 0, pl11drummixer3, 3);
AudioConnection patchCord8(playSdRaw11, 0, pl11drummixer3, 2);
AudioConnection patchCord9(playSdRaw9, 0, pl11drummixer3, 0);
AudioConnection patchCord10(playSdRaw3, 0, pl11drummixer1, 2);
AudioConnection patchCord11(playSdRaw4, 0, pl11drummixer1, 3);
AudioConnection patchCord12(playSdRaw2, 0, pl11drummixer1, 1);
AudioConnection patchCord13(playSdRaw1, 0, pl11drummixer1, 0);
AudioConnection patchCord14(pl10mixer3, pl10pwm1);
AudioConnection patchCord15(playSdRaw8, 0, pl11drummixer2, 3);
AudioConnection patchCord16(playSdRaw6, 0, pl11drummixer2, 1);
AudioConnection patchCord17(playSdRaw5, 0, pl11drummixer2, 0);
AudioConnection patchCord18(playSdRaw7, 0, pl11drummixer2, 2);
AudioConnection patchCord19(pl10dc1, pl10envelope2);
AudioConnection patchCord20(pl1waveform1, 0, pl1waveformMod1, 0);
AudioConnection patchCord21(pl1waveform1, 0, pl1waveformMod2, 0);
AudioConnection patchCord22(pl1waveform1, 0, pl1waveformMod3, 0);
AudioConnection patchCord23(pl1waveform1, 0, pl1waveformMod4, 0);
AudioConnection patchCord24(pl10noise1, 0, pl10mixer1, 2);
AudioConnection patchCord25(pl5dc1, pl5envelope2);
AudioConnection patchCord26(pl7noise1, 0, pl7waveformMod1, 0);
AudioConnection patchCord27(playMem9, 0, pl4drummixer3, 0);
AudioConnection patchCord28(pl6dc1, pl6envelope2);
AudioConnection patchCord29(playMem10, 0, pl4drummixer3, 1);
AudioConnection patchCord30(playMem7, 0, pl4drummixer2, 2);
AudioConnection patchCord31(playMem8, 0, pl4drummixer2, 3);
AudioConnection patchCord32(playMem5, 0, pl4drummixer2, 0);
AudioConnection patchCord33(playMem6, 0, pl4drummixer2, 1);
AudioConnection patchCord34(playSdWav12, 0, drummixer3, 3);
AudioConnection patchCord35(playMem1, 0, pl4drummixer1, 0);
AudioConnection patchCord36(playSdWav7, 0, drummixer2, 2);
AudioConnection patchCord37(playMem2, 0, pl4drummixer1, 1);
AudioConnection patchCord38(playSdWav9, 0, drummixer3, 0);
AudioConnection patchCord39(playSdWav3, 0, drummixer1, 2);
AudioConnection patchCord40(playSdWav10, 0, drummixer3, 1);
AudioConnection patchCord41(playSdWav4, 0, drummixer1, 3);
AudioConnection patchCord42(playSdWav11, 0, drummixer3, 2);
AudioConnection patchCord43(playSdWav8, 0, drummixer2, 3);
AudioConnection patchCord44(playMem11, 0, pl4drummixer3, 2);
AudioConnection patchCord45(pl7waveformMod3, pl7envelope2);
AudioConnection patchCord46(playSdWav2, 0, drummixer1, 1);
AudioConnection patchCord47(playSdWav5, 0, drummixer2, 0);
AudioConnection patchCord48(playSdWav6, 0, drummixer2, 1);
AudioConnection patchCord49(playSdWav1, 0, drummixer1, 0);
AudioConnection patchCord50(playMem12, 0, pl4drummixer3, 3);
AudioConnection patchCord51(playMem3, 0, pl4drummixer1, 2);
AudioConnection patchCord52(pl10pwm1, 0, pl10mixer1, 0);
AudioConnection patchCord53(playMem4, 0, pl4drummixer1, 3);
AudioConnection patchCord54(pl10pwm2, 0, pl10mixer1, 1);
AudioConnection patchCord55(pl8dc1, pl8envelope2);
AudioConnection patchCord56(pl7noise2, 0, pl7mixer4, 0);
AudioConnection patchCord57(pl7pink1, 0, pl7mixer4, 1);
AudioConnection patchCord58(pl9string1, 0, pl9bpfilter, 0);
AudioConnection patchCord59(pl10envelope2, 0, pl10filter1, 1);
AudioConnection patchCord60(pl11drummixer1, 0, pl11drummixer4, 0);
AudioConnection patchCord61(pl11drummixer2, 0, pl11drummixer4, 1);
AudioConnection patchCord62(pl9bpinput, 0, pl9bpfilter, 1);
AudioConnection patchCord63(pl11drummixer3, 0, pl11drummixer4, 2);
AudioConnection patchCord64(pl5envelope2, 0, pl5filter1, 1);
AudioConnection patchCord65(playSdPitch2, 0, pl6filter1, 0);
AudioConnection patchCord66(pl6envelope2, 0, pl6filter1, 1);
AudioConnection patchCord67(playSdPitch1, 0, pl5filter1, 0);
AudioConnection patchCord68(pl7drum1, 0, pl7filter1, 0);
AudioConnection patchCord69(pl10mixer1, 0, pl10filter1, 0);
AudioConnection patchCord70(pl7waveformMod1, 0, pl7filter2, 0);
AudioConnection patchCord71(pl8waveform1, 0, pl8filter1, 0);
AudioConnection patchCord72(pl1waveformMod1, 0, mixer1, 0);
AudioConnection patchCord73(pl1waveformMod2, 0, mixer1, 1);
AudioConnection patchCord74(pl1waveformMod4, 0, mixer1, 3);
AudioConnection patchCord75(pl1waveformMod3, 0, mixer1, 2);
AudioConnection patchCord76(pl7envelope2, 0, pl7waveformMod2, 0);
AudioConnection patchCord77(pl8envelope2, 0, pl8filter1, 1);
AudioConnection patchCord78(pl3waveform1, 0, pl3waveformMod1, 0);
AudioConnection patchCord79(pl3dc1, pl3envelope2);
AudioConnection patchCord80(pl7mixer4, pl7biquad1);
AudioConnection patchCord81(drummixer1, 0, drummixer4, 0);
AudioConnection patchCord82(drummixer2, 0, drummixer4, 1);
AudioConnection patchCord83(drummixer3, 0, drummixer4, 2);
AudioConnection patchCord84(pl4drummixer1, 0, pl4drummixer4, 0);
AudioConnection patchCord85(pl4drummixer2, 0, pl4drummixer4, 1);
AudioConnection patchCord86(pl4drummixer3, 0, pl4drummixer4, 2);
AudioConnection patchCord87(pl10filter1, 0, pl10mixer2, 0);
AudioConnection patchCord88(pl10filter1, 1, pl10mixer2, 1);
AudioConnection patchCord89(pl10filter1, 2, pl10mixer2, 2);
AudioConnection patchCord90(pl9bpfilter, 0, pl9mixer1, 0);
AudioConnection patchCord91(pl9bpfilter, 1, pl9mixer1, 1);
AudioConnection patchCord92(pl9bpfilter, 2, pl9mixer1, 2);
AudioConnection patchCord93(pl5filter1, 0, pl5mixer1, 0);
AudioConnection patchCord94(pl5filter1, 1, pl5mixer1, 1);
AudioConnection patchCord95(pl5filter1, 2, pl5mixer1, 2);
AudioConnection patchCord96(pl6filter1, 0, pl6mixer1, 0);
AudioConnection patchCord97(pl6filter1, 1, pl6mixer1, 1);
AudioConnection patchCord98(pl6filter1, 2, pl6mixer1, 2);
AudioConnection patchCord99(pl7filter1, 0, pl7mixer1, 0);
AudioConnection patchCord100(pl7filter2, 0, pl7envelope1, 0);
AudioConnection patchCord101(mixer1, 0, filter1, 0);
AudioConnection patchCord102(pl1dc1, envelope1);
AudioConnection patchCord103(pl11drummixer4, pl11amp2);
AudioConnection patchCord104(pl3waveformMod1, 0, pl3filter1, 0);
AudioConnection patchCord105(pl3envelope2, 0, pl3filter1, 1);
AudioConnection patchCord106(pl7biquad1, pl7envelope4);
AudioConnection patchCord107(pl8filter1, pl8envelope1);
AudioConnection patchCord108(pl7waveformMod2, pl7envelope3);
AudioConnection patchCord109(drummixer4, pl2amp2);
AudioConnection patchCord110(pl10mixer2, pl10envelope1);
AudioConnection patchCord111(pl3filter1, 0, pl3mixer1, 0);
AudioConnection patchCord112(pl3filter1, 1, pl3mixer1, 1);
AudioConnection patchCord113(pl3filter1, 2, pl3mixer1, 2);
AudioConnection patchCord114(envelope1, 0, filter1, 1);
AudioConnection patchCord115(pl6mixer1, pl6envelope1);
AudioConnection patchCord116(pl5mixer1, pl5envelope1);
AudioConnection patchCord117(pl9mixer1, pl9amp2);
AudioConnection patchCord118(filter1, 0, pl1mixer2, 0);
AudioConnection patchCord119(filter1, 1, pl1mixer2, 1);
AudioConnection patchCord120(filter1, 2, pl1mixer2, 2);
AudioConnection patchCord121(pl4drummixer4, pl4amp2);
AudioConnection patchCord122(pl7envelope1, 0, pl7mixer1, 1);
AudioConnection patchCord123(pl8envelope1, pl8amp2);
AudioConnection patchCord124(pl7envelope4, 0, pl7mixer1, 3);
AudioConnection patchCord125(pl7envelope3, 0, pl7mixer1, 2);
AudioConnection patchCord126(pl5envelope1, pl5amp2);
AudioConnection patchCord127(pl2amp2, pl2amp);
AudioConnection patchCord128(pl3mixer1, pl3envelope1);
AudioConnection patchCord129(pl6envelope1, pl6amp2);
AudioConnection patchCord130(pl10envelope1, pl10amp2);
AudioConnection patchCord131(pl14amp2, pl14amp);
AudioConnection patchCord132(pl12amp2, pl12amp);
AudioConnection patchCord133(pl16amp2, pl16amp);
AudioConnection patchCord134(pl11amp2, pl11amp);
AudioConnection patchCord135(pl1mixer2, envelope2);
AudioConnection patchCord136(pl13amp2, pl13amp);
AudioConnection patchCord137(pl10amp2, pl10amp);
AudioConnection patchCord138(pl9amp2, pl9amp);
AudioConnection patchCord139(pl15amp2, pl15amp);
AudioConnection patchCord140(pl4amp2, pl4amp);
AudioConnection patchCord141(pl3envelope1, pl3amp2);
AudioConnection patchCord142(pl8amp2, pl8amp);
AudioConnection patchCord143(pl7amp2, pl7amp);
AudioConnection patchCord144(pl7mixer2, 0, pl7mixer3, 1);
AudioConnection patchCord145(pl2amp, pl2FX3);
AudioConnection patchCord146(pl2amp, pl2dry);
AudioConnection patchCord147(pl2amp, pl2FX1);
AudioConnection patchCord148(pl2amp, pl2FX2);
AudioConnection patchCord149(pl6amp2, pl6amp);
AudioConnection patchCord150(envelope2, pl1amp2);
AudioConnection patchCord151(pl3amp2, pl3amp);
AudioConnection patchCord152(pl7mixer1, 0, pl7mixer3, 0);
AudioConnection patchCord153(pl5amp2, pl5amp);
AudioConnection patchCord154(pl4amp, pl4dry);
AudioConnection patchCord155(pl4amp, pl4FX1);
AudioConnection patchCord156(pl4amp, pl4FX2);
AudioConnection patchCord157(pl4amp, pl4FX3);
AudioConnection patchCord158(pl11amp, pl11dry);
AudioConnection patchCord159(pl11amp, pl11FX1);
AudioConnection patchCord160(pl11amp, pl11FX2);
AudioConnection patchCord161(pl11amp, pl11FX3);
AudioConnection patchCord162(pl10amp, pl10dry);
AudioConnection patchCord163(pl10amp, pl10FX1);
AudioConnection patchCord164(pl10amp, pl10FX2);
AudioConnection patchCord165(pl10amp, pl10FX3);
AudioConnection patchCord166(pl16amp, pl16dry);
AudioConnection patchCord167(pl16amp, pl16FX1);
AudioConnection patchCord168(pl16amp, pl16FX2);
AudioConnection patchCord169(pl16amp, pl16FX3);
AudioConnection patchCord170(pl12amp, pl12dry);
AudioConnection patchCord171(pl12amp, pl12FX1);
AudioConnection patchCord172(pl12amp, pl12FX2);
AudioConnection patchCord173(pl12amp, pl12FX3);
AudioConnection patchCord174(pl15amp, pl15dry);
AudioConnection patchCord175(pl15amp, pl15FX1);
AudioConnection patchCord176(pl15amp, pl15FX2);
AudioConnection patchCord177(pl15amp, pl15FX3);
AudioConnection patchCord178(pl13amp, pl13FX3);
AudioConnection patchCord179(pl13amp, pl13FX2);
AudioConnection patchCord180(pl13amp, pl13FX1);
AudioConnection patchCord181(pl13amp, pl13dry);
AudioConnection patchCord182(pl14amp, pl14dry);
AudioConnection patchCord183(pl14amp, pl14FX1);
AudioConnection patchCord184(pl14amp, pl14FX2);
AudioConnection patchCord185(pl14amp, pl14FX3);
AudioConnection patchCord186(pl8amp, pl8dry);
AudioConnection patchCord187(pl8amp, pl8FX1);
AudioConnection patchCord188(pl8amp, pl8FX2);
AudioConnection patchCord189(pl8amp, pl8FX3);
AudioConnection patchCord190(pl9amp, pl9dry);
AudioConnection patchCord191(pl9amp, pl9FX1);
AudioConnection patchCord192(pl9amp, pl9FX2);
AudioConnection patchCord193(pl9amp, pl9FX3);
AudioConnection patchCord194(pl1amp2, pl1amp);
AudioConnection patchCord195(pl7amp, pl7dry);
AudioConnection patchCord196(pl7amp, pl7FX1);
AudioConnection patchCord197(pl7amp, pl7FX2);
AudioConnection patchCord198(pl7amp, pl7FX3);
AudioConnection patchCord199(pl3amp, pl3dry);
AudioConnection patchCord200(pl3amp, pl3FX1);
AudioConnection patchCord201(pl3amp, pl3FX2);
AudioConnection patchCord202(pl3amp, pl3FX3);
AudioConnection patchCord203(pl5amp, pl5dry);
AudioConnection patchCord204(pl5amp, pl5FX1);
AudioConnection patchCord205(pl5amp, pl5FX2);
AudioConnection patchCord206(pl5amp, pl5FX3);
AudioConnection patchCord207(pl6amp, pl6dry);
AudioConnection patchCord208(pl6amp, pl6FX1);
AudioConnection patchCord209(pl6amp, pl6FX2);
AudioConnection patchCord210(pl6amp, pl6FX3);
AudioConnection patchCord211(pl7mixer3, pl7amp2);
AudioConnection patchCord212(pl2FX2, 0, FX2mixer1, 1);
AudioConnection patchCord213(pl2FX3, 0, FX3mixer1, 1);
AudioConnection patchCord214(pl2dry, 0, mixer5, 1);
AudioConnection patchCord215(pl2FX1, 0, FX1mixer1, 1);
AudioConnection patchCord216(pl4FX2, 0, FX2mixer1, 3);
AudioConnection patchCord217(pl4FX3, 0, FX3mixer1, 3);
AudioConnection patchCord218(pl4dry, 0, mixer5, 3);
AudioConnection patchCord219(pl4FX1, 0, FX1mixer1, 3);
AudioConnection patchCord220(pl1amp, pl1dry);
AudioConnection patchCord221(pl1amp, pl1FX1);
AudioConnection patchCord222(pl1amp, pl1FX2);
AudioConnection patchCord223(pl1amp, pl1FX3);
AudioConnection patchCord224(pl14FX3, 0, FX3mixer6, 1);
AudioConnection patchCord225(pl14FX2, 0, FX2mixer6, 1);
AudioConnection patchCord226(pl14dry, 0, drymixer3, 1);
AudioConnection patchCord227(pl14FX1, 0, FX1mixer6, 1);
AudioConnection patchCord228(pl8dry, 0, mixer6, 3);
AudioConnection patchCord229(pl8FX1, 0, FX1mixer2, 3);
AudioConnection patchCord230(pl10dry, 0, mixer10, 1);
AudioConnection patchCord231(pl8FX2, 0, FX2mixer2, 3);
AudioConnection patchCord232(pl8FX3, 0, FX3mixer2, 3);
AudioConnection patchCord233(pl16FX3, 0, FX3mixer6, 3);
AudioConnection patchCord234(pl10FX1, 0, FX1mixer4, 1);
AudioConnection patchCord235(pl10FX2, 0, FX2mixer4, 1);
AudioConnection patchCord236(pl10FX3, 0, FX3mixer4, 1);
AudioConnection patchCord237(pl16FX2, 0, FX2mixer6, 3);
AudioConnection patchCord238(pl13FX3, 0, FX3mixer6, 0);
AudioConnection patchCord239(pl13FX2, 0, FX2mixer6, 0);
AudioConnection patchCord240(pl16dry, 0, drymixer3, 3);
AudioConnection patchCord241(pl16FX1, 0, FX1mixer6, 3);
AudioConnection patchCord242(pl9dry, 0, mixer10, 0);
AudioConnection patchCord243(pl9FX1, 0, FX1mixer4, 0);
AudioConnection patchCord244(pl9FX2, 0, FX2mixer4, 0);
AudioConnection patchCord245(pl13dry, 0, drymixer3, 0);
AudioConnection patchCord246(pl11dry, 0, mixer10, 2);
AudioConnection patchCord247(pl13FX1, 0, FX1mixer6, 0);
AudioConnection patchCord248(pl11FX2, 0, FX2mixer4, 2);
AudioConnection patchCord249(pl11FX3, 0, FX3mixer4, 2);
AudioConnection patchCord250(pl9FX3, 0, FX3mixer4, 0);
AudioConnection patchCord251(pl12dry, 0, mixer10, 3);
AudioConnection patchCord252(pl15FX3, 0, FX3mixer6, 2);
AudioConnection patchCord253(pl11FX1, 0, FX1mixer4, 2);
AudioConnection patchCord254(pl15FX2, 0, FX2mixer6, 2);
AudioConnection patchCord255(pl7dry, 0, mixer6, 2);
AudioConnection patchCord256(pl7FX2, 0, FX2mixer2, 2);
AudioConnection patchCord257(pl7FX3, 0, FX3mixer2, 2);
AudioConnection patchCord258(pl15dry, 0, drymixer3, 2);
AudioConnection patchCord259(pl15FX1, 0, FX1mixer6, 2);
AudioConnection patchCord260(pl7FX1, 0, FX1mixer2, 2);
AudioConnection patchCord261(pl12FX1, 0, FX1mixer4, 3);
AudioConnection patchCord262(pl12FX2, 0, FX2mixer4, 3);
AudioConnection patchCord263(pl3dry, 0, mixer5, 2);
AudioConnection patchCord264(pl3FX1, 0, FX1mixer1, 2);
AudioConnection patchCord265(pl3FX2, 0, FX2mixer1, 2);
AudioConnection patchCord266(pl12FX3, 0, FX3mixer4, 3);
AudioConnection patchCord267(pl3FX3, 0, FX3mixer1, 2);
AudioConnection patchCord268(pl6FX1, 0, FX1mixer2, 1);
AudioConnection patchCord269(pl6dry, 0, mixer6, 1);
AudioConnection patchCord270(pl6FX2, 0, FX2mixer2, 1);
AudioConnection patchCord271(pl5FX3, 0, FX3mixer2, 0);
AudioConnection patchCord272(pl6FX3, 0, FX3mixer2, 1);
AudioConnection patchCord273(pl5FX1, 0, FX1mixer2, 0);
AudioConnection patchCord274(pl5dry, 0, mixer6, 0);
AudioConnection patchCord275(pl5FX2, 0, FX2mixer2, 0);
AudioConnection patchCord276(pl1FX3, 0, FX3mixer1, 0);
AudioConnection patchCord277(pl1dry, 0, mixer5, 0);
AudioConnection patchCord278(pl1FX1, 0, FX1mixer1, 0);
AudioConnection patchCord279(pl1FX2, 0, FX2mixer1, 0);
AudioConnection patchCord280(mixer6, 0, drymixer2, 1);
AudioConnection patchCord281(FX2mixer1, 0, FX2mixer3, 0);
AudioConnection patchCord282(mixer5, 0, drymixer2, 0);
AudioConnection patchCord283(FX3mixer2, 0, FX3mixer3, 1);
AudioConnection patchCord284(FX1mixer1, 0, FX1mixer3, 0);
AudioConnection patchCord285(FX2mixer2, 0, FX2mixer3, 1);
AudioConnection patchCord286(FX1mixer2, 0, FX1mixer3, 1);
AudioConnection patchCord287(FX3mixer1, 0, FX3mixer3, 0);
AudioConnection patchCord288(FX2mixer4, 0, FX2mixer3, 2);
AudioConnection patchCord289(FX1mixer6, 0, FX1mixer3, 3);
AudioConnection patchCord290(drymixer3, 0, drymixer2, 3);
AudioConnection patchCord291(FX3mixer6, 0, FX3mixer3, 3);
AudioConnection patchCord292(FX2mixer6, 0, FX2mixer3, 3);
AudioConnection patchCord293(FX3mixer4, 0, FX3mixer3, 2);
AudioConnection patchCord294(FX1mixer4, 0, FX1mixer3, 2);
AudioConnection patchCord295(mixer10, 0, drymixer2, 2);
AudioConnection patchCord296(drymixer2, 0, drymixer1, 0);
AudioConnection patchCord297(FX2mixer3, 0, FX2mixer5, 0);
AudioConnection patchCord298(FX3mixer3, 0, FX3mixer5, 0);
AudioConnection patchCord299(FX1mixer3, 0, FX1mixer5, 0);
AudioConnection patchCord300(FX3mixer5, 0, dlmixer1, 0);
AudioConnection patchCord301(drymixer1, 0, mixer9, 0);
AudioConnection patchCord302(FX1mixer5, reverb1);
AudioConnection patchCord303(FX2mixer5, bitcrusher2);
AudioConnection patchCord304(reverb1, 0, mixer9, 1);
AudioConnection patchCord305(bitcrusher2, 0, mixer9, 2);
AudioConnection patchCord306(dlfilter1, 2, dlmixer1, 1);
AudioConnection patchCord307(dlmixer1, dldelay1);
AudioConnection patchCord308(dlmixer1, 0, mixer9, 3);
AudioConnection patchCord309(dldelay1, 0, dlfilter1, 0);
AudioConnection patchCord310(i2s2, 0, amp1, 0);
AudioConnection patchCord311(mixer9, 0, mixer11, 0);
AudioConnection patchCord312(amp1, 0, mixer11, 1);
AudioConnection patchCord313(amp1, queue1);
AudioConnection patchCord314(amp1, peak1);
AudioConnection patchCord315(mixer11, 0, i2s1, 0);
AudioConnection patchCord316(mixer11, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=2895.1999702453613,810.0001049041748
// GUItool: end automatically generated code
