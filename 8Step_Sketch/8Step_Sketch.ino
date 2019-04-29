#include "Sequencer.h"
#include "MidiManager.h"
#include "ButtonManager.h"

#define INTER 0
#define USB 1

bool MODE = INTER;

Sequencer sequencer;
MidiManager midiManager;
ButtonManager buttonManager;

int led = 13;
int tempo = 120;

int divs[] = {1, 2, 4, 8};
int timeDiv = 1;

float gate = 0.90;

unsigned long prevMillis = 0;

uint8_t lastNote = 0;

void midiPlayCallback() {
  sequencer.togglePlayPause();
  buttonManager.togglePlayButton();
}

void midiStopCallback() {
  sequencer.togglePlayPause();
  buttonManager.togglePlayButton();

  if (lastNote != 0) {
    midiManager.noteOff(lastNote);
  }
}

void setup() {
  // Serial.begin(250000);
  
  buttonManager.setupManager();

  midiManager.playCallback = &midiPlayCallback;
  midiManager.stopCallback = &midiStopCallback;

  tempo = map(analogRead(0), 0, 1023, 30, 210);
  timeDiv = divs[map(analogRead(1), 0, 1023, 0, 3)];
  gate = map(analogRead(2), 0, 1023, 10, 90) / 100;
}

void readKnobs() {
  int newTempo = tempo;
  if (MODE == INTER) {
    newTempo = map(analogRead(0), 0, 1023, 30, 210);
  } else {
    newTempo = midiManager.midiTempo();
  }
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
  if (buttonManager.stateChanged(currentMillis, MODE)) {
    MODE = buttonManager.modeChanged(MODE);

    if (buttonManager.playPressed()) {
      sequencer.togglePlayPause();

      if (MODE == INTER) {
        midiManager.sendPlayStop(sequencer.isPlaying());
      }
    }

    if (buttonManager.recordPressed()) {
      sequencer.startRecording();

      if (MODE == INTER) {
        midiManager.sendPlayStop(false);
      }
    }

    uint8_t notePressed = buttonManager.notePressed();
    uint8_t noteReleased = buttonManager.noteReleased(sequencer.getState() == 2);

    if (notePressed > 0) {
      midiManager.noteOn(notePressed);
    }
    if (noteReleased > 0) {
      midiManager.noteOff(noteReleased);
      midiManager.noteOff(noteReleased + 1);
      if (sequencer.addStep(noteReleased)) {
        buttonManager.setStepRecordLEDs(sequencer.getCurrentStep(), sequencer.getSequenceLength());
      }
    }

    if (buttonManager.tapPressed()) {
      if (sequencer.addStep(0)) {
        buttonManager.setStepRecordLEDs(sequencer.getCurrentStep(), sequencer.getSequenceLength());
      }
    }

    if (buttonManager.extendPressed()) {
      sequencer.increaseSequence();
    }
    if (buttonManager.reducePressed()) {
      sequencer.decreaseSequence();
    }

    buttonManager.commitLEDState();
  }
}

void handleBeat(unsigned long currentMillis) {
  int inter = (1000 / (tempo * timeDiv)) * 60;
  int gateInter = inter * gate;

  bool beatOccured = false;
  if (MODE == INTER) {
    beatOccured = currentMillis - prevMillis >= inter && sequencer.isPlaying();
  } else if (MODE == USB) {
    beatOccured = midiManager.isPlaying() && midiManager.midiBeat();
  }

  if (beatOccured) {
    // EVERY BEAT

    uint8_t note = sequencer.processStep(&buttonManager);
    buttonManager.commitLEDState();

    if (note != 0) {
      midiManager.noteOn(note);
    }

    lastNote = note;

    prevMillis = currentMillis;
  }

  if (lastNote != 0 && currentMillis - prevMillis >= gateInter) {
    midiManager.noteOff(lastNote);
    lastNote = 0;
  }

  if (MODE == INTER && sequencer.isPlaying()) {
    midiManager.midiClockCheck(currentMillis, tempo);
  }
}

void loop() {
  readKnobs();

  unsigned long currentMillis = millis();

  handleButtons(currentMillis);  

  handleBeat(currentMillis);

  if (MODE == USB)
    midiManager.midiRead(timeDiv, currentMillis);
}
