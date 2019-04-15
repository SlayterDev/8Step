#ifndef __MIDIMANAGER__
#define __MIDIMANAGER__

#include <stdint.h>
#include "MIDIUSB.h"

class MidiManager {
public:
    void noteOn(uint8_t pitch);
    void noteOff(uint8_t pitch);
    void ccChange(uint8_t ccNum, uint8_t val);

    MidiManager() :
    channel(1) {}

private:
    int channel;

    void midiNoteOn(byte channel, byte pitch, byte velocity);
    void midiNoteOff(byte channel, byte pitch, byte velocity);
    void midiControlChange(byte channel, byte control, byte value);
};

#endif
