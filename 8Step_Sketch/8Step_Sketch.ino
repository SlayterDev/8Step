#include "Sequencer.h"
#include "MidiManager.h"
#include "ButtonManager.h"

Sequencer sequencer;
MidiManager midiManager;
ButtonManager buttonManager;

int led = 13;
int tempo = 120;
int quater = (1000 / (120 * 8)) * 60; // 1/8

int divs[] = {1, 2, 4, 8};
int timeDiv = 1;

float gate = 0.90;

unsigned long prevMillis = 0;

// TODO: Remove
uint8_t lastNote = 0;

void setup() {
  Serial.begin(250000);
  
  buttonManager.setupManager();

  tempo = map(analogRead(0), 0, 1023, 30, 210);
  timeDiv = map(analogRead(1), 0, 1023, 0, 3);
  gate = map(analogRead(2), 0, 1023, 10, 90) / 100;
}

void readKnobs() {
  int newTempo = map(analogRead(0), 0, 1023, 30, 210);
  if (newTempo != tempo) {
    tempo = newTempo;
  }

  int newDiv = divs[map(analogRead(1), 0, 1023, 0, 3)];
  if (newDiv != timeDiv) {
    timeDiv = newDiv;
  }

  float newGate = map(analogRead(2), 0, 1023, 10, 90) / 100.0f;
  if (newGate != gate) {
    gate = newGate;
  }
}

void handleButtons(unsigned long currentMillis) {
  if (buttonManager.stateChanged(currentMillis)) {
    if (buttonManager.playPressed()) {
      sequencer.togglePlayPause();
    }

    if (buttonManager.recordPressed()) {
      sequencer.startRecording();
    }

    uint8_t notePressed = buttonManager.notePressed();
    uint8_t noteReleased = buttonManager.noteReleased();

    if (notePressed > 0) {
      midiManager.noteOn(notePressed);
    }
    if (noteReleased > 0) {
      midiManager.noteOff(noteReleased);
      sequencer.addStep(noteReleased);
    }

    if (buttonManager.tapPressed()) {
      sequencer.addStep(0);
    }

    buttonManager.commitLEDState();
  }
}

void handleBeat(unsigned long currentMillis) {
  int inter = (1000 / (tempo * timeDiv)) * 60;
  int gateInter = inter * gate;

  if (currentMillis - prevMillis >= inter && sequencer.isPlaying()) {
    // EVERY BEAT

    uint8_t note = sequencer.processStep(&buttonManager);
    buttonManager.commitLEDState();

    if (note != 0) {
      midiManager.noteOn(note);
    }
    Serial.println(note);
    lastNote = note;

    prevMillis = currentMillis;
  }

  if (lastNote != 0 && currentMillis - prevMillis >= gateInter) {
    midiManager.noteOff(lastNote);
    lastNote = 0;
  }
}

void loop() {
  readKnobs();

  unsigned long currentMillis = millis();

  handleButtons(currentMillis);  

  handleBeat(currentMillis);
}
