#include "MidiManager.h"

void MidiManager::midiNoteOn(byte channel, byte pitch, byte velocity) {
    midiEventPacket_t noteOn = {0x09, (byte)(0x90 | channel), pitch, velocity};
    MidiUSB.sendMIDI(noteOn);
    MidiUSB.flush();
}

void MidiManager::midiNoteOff(byte channel, byte pitch, byte velocity) {
    midiEventPacket_t noteOff = {0x08, (byte)(0x80 | channel), pitch, velocity};
    MidiUSB.sendMIDI(noteOff);
    MidiUSB.flush();
}

void MidiManager::midiControlChange(byte channel, byte control, byte value) {
    midiEventPacket_t event = {0x0B, (byte)(0xB0 | channel), control, value};
    MidiUSB.sendMIDI(event);
}

void MidiManager::noteOn(uint8_t pitch) {
    midiNoteOn(channel, pitch, 127);
}

void MidiManager::noteOff(uint8_t pitch) {
    midiNoteOff(channel, pitch, 127);
}

void MidiManager::ccChange(uint8_t ccNum, uint8_t val) {
    midiControlChange(channel, ccNum, val);
}