#ifndef MIDI_H_
#define MIDI_H_
#include <util.h>

#define MIDIIF_BAUD 31250

void midi_begin();
void midi_note(char channel, char noteNumber, char velocity);

#endif