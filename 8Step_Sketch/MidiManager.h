#ifndef __MIDIMANAGER__
#define __MIDIMANAGER__

#include <stdint.h>
#include "MIDIUSB.h"

class MidiManager {
public:
    void (*playCallback)(void);
    void (*stopCallback)(void);

    void noteOn(uint8_t pitch);
    void noteOff(uint8_t pitch);
    void ccChange(uint8_t ccNum, uint8_t val);
    void sendPlayStop(bool play);
    void midiClockCheck(unsigned long delta, int tempo);
    void midiRead(uint8_t division);
    bool midiBeat();

    MidiManager() :
    channel(1),
    isMidiPlaying(false),
    beatLock(false),
    beatCounter(0),
    timeDiv(1) {}

    inline bool isPlaying() const { return isMidiPlaying; }

private:
    int channel;
    bool isMidiPlaying;
    unsigned int beatCounter;
    bool beatLock;
    uint8_t timeDiv;
    unsigned long prevSend;

    void midiNoteOn(byte channel, byte pitch, byte velocity);
    void midiNoteOff(byte channel, byte pitch, byte velocity);
    void midiControlChange(byte channel, byte control, byte value);
    void processMidiClock();
};

#endif
