#include <util.h>
#include <midiif.h>
#include <settings.h>

// For some reason MIDI Library Tx not working on the Pro Micro Serial1, so not using it
void midi_note(char channel, char noteNumber, char velocity) {
  char cmd = 0x90 | channel;
  Serial1.write(cmd);
  Serial1.write(noteNumber);
  Serial1.write(velocity);
  dbg_log(F("[MIDI] Channel %i Note %i Vel %i"), channel, noteNumber, velocity);
}

void midi_begin() {
    inf_log(F("[MIDI] I/F start"));
    Serial1.begin(MIDIIF_BAUD);
}