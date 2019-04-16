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

void MidiManager::midiRead(uint8_t division) {
    if (division != timeDiv) {
        timeDiv = division;
    }

    midiEventPacket_t rx;
    do {
        rx = MidiUSB.read();
        if (rx.header != 0) {
            if (rx.byte1 == 0xFA) {
                isMidiPlaying = true;
                beatCounter = 0;
                (playCallback)();
            }
            if (rx.byte1 == 0xFC) {
                isMidiPlaying = false;
                (stopCallback)();
            }
            if (rx.byte1 == 0xF8) {
                processMidiClock();
            }
        }
    } while (rx.header != 0);
}

void MidiManager::processMidiClock() {
    beatCounter++;
    beatLock = false;
}

bool MidiManager::midiBeat() {
    bool beat = beatCounter % (24 / timeDiv) == 0;

    if (beat && !beatLock) {
        beatLock = true;
        return true;
    }

    return false;
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

void MidiManager::sendPlayStop(bool play) {
    byte header = (play) ? 0xFA : 0xFC;
    midiEventPacket_t packet = {header >> 4, header, 0, 0};
    MidiUSB.sendMIDI(packet);
    MidiUSB.flush();
}

void MidiManager::midiClockCheck(unsigned long delta, int tempo) {
    int inter = (1000 / (tempo * 24)) * 60; // 24 frames per quarter

    if (delta - prevSend >= inter) {
        midiEventPacket_t packet = {0x0F, 0xF8, 0, 0};
        MidiUSB.sendMIDI(packet);

        prevSend = delta;
    }
}
