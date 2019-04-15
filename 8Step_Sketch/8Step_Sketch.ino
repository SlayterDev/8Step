#include "Sequencer.h"
#include "MidiManager.h"
#include "ButtonManager.h"

Sequencer sequencer;
MidiManager midiManager;
ButtonManager buttonManager;

int led = 13;
int tempo = 120;
int quater = (1000 / (120 * 8)) * 60; // 1/8

unsigned long prevMillis = 0;

// TODO: Remove
uint8_t lastNote = 0;

void setup() {
  Serial.begin(250000);
  
  buttonManager.setupManager();

  sequencer.startRecording();
  for (int i = 0; i < 8; i++) {
    sequencer.addStep(60 + i);
  }

  tempo = map(analogRead(0), 0, 1023, 30, 210);
}

void loop() {
  // delay(100);

  tempo = map(analogRead(0), 0, 1023, 30, 210);

  int inter = (1000 / tempo) * 60;

  unsigned long currentMillis = millis();

  if (buttonManager.stateChanged(currentMillis)) {
    if (buttonManager.playPressed()) {
      sequencer.togglePlayPause();
    }

    buttonManager.commitLEDState();
  }

  if (currentMillis - prevMillis >= inter && sequencer.isPlaying()) {
    // EVERY BEAT

    uint8_t note = sequencer.processStep();

    if (note != 0) {
      midiManager.noteOn(note);
    }
    Serial.println(note);
    lastNote = note;

    prevMillis = currentMillis;
  }

  if (lastNote != 0 && currentMillis - prevMillis >= quater) {
    midiManager.noteOff(lastNote);
    lastNote = 0;
  }
}
