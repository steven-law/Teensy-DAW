void drumSettings () {
    //drum11111111111111111111111111111111111111111111111111111111111111111111111111111111 drum1
  drum1.frequency(20);
  drum1.length(150);
  drum1.pitchMod(1); //max 2 !!
  drum1.secondMix(0);
    //mixer1 to controll drum1
  mixer1.gain(0, 1);
  mixer1.gain(1, 0.25);
  mixer1.gain(2, 0.25);
  mixer1.gain(3, 0.25);
}
