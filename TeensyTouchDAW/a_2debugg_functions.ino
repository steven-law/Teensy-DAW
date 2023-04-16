//some general debug function

void SerialPrintSeq() {

  Serial.print(master_clock.get_tempo());
  Serial.print("-");
  Serial.print(master_clock.get_stepTick());
  Serial.print("-   ");

  for (int i = 0; i < 12; i++) {
    Serial.print(drumnotes[i]);
    Serial.print("-");
  }

  Serial.print("-   ");

  for (int desired_tracks = 1; desired_tracks < 8; desired_tracks++) {
    Serial.print(track[desired_tracks].notePlayed[0]);
    Serial.print("-");
    Serial.print(track[desired_tracks].envActive[0]);
    Serial.print("-   ");
  }
  debug_free_ram();
}
void SerialPrintPlugins() {

  for (int pl = 0; pl < MAX_PLUGINS; pl++) {
    Serial.print("PL");
    Serial.print(pl + 1);
    Serial.print(":   ");
    for (int po = 0; po < 4; po++) {
      for (int pot = 0; pot < 4; pot++) {
      Serial.print(plugin[pl].preset[plpreset[pl]].Pot_Value[pot+(po*4)]);
      Serial.print(" - ");
    }
    Serial.print("  ");
    }
    Serial.println("");
  }
  showSerialonce = false;
}

int freeRam() {
  return (char *)&_heap_end - __brkval;
}

void debug_free_ram() {
  Serial.printf(F("debug_free_ram: %i\n"), freeRam());
}