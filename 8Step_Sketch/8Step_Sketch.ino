#include "Sequencer.h"

Sequencer sequencer;

int led = 13;
int tempo = 120;

long prevMillis = 0;
long interval = 1000;

bool ledState = LOW;

// TODO: Remove
uint8_t lastNote = 0;

void setup() {
  Serial.begin(115200);
  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);

  sequencer.startRecording();
  for (int i = 0; i < 8; i++) {
    sequencer.addStep(60 + i);
  }
  sequencer.togglePlayPause();
}

void loop() {
  // delay(100);

  int inter = (1000 / tempo) * 60;
  int quater = (1000 / (tempo * 8)) * 60; // 1/8

  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= inter) {
    // EVERY BEAT

    uint8_t note = sequencer.processStep();

    // usbMIDI.sendNoteOn(note, 127, 1);
    Serial.println(note);
    lastNote = note;

    prevMillis = currentMillis;

    ledState = HIGH;
    digitalWrite(led, ledState);
  }

  if (ledState && currentMillis - prevMillis >= quater) {
    ledState = LOW;
    digitalWrite(led, ledState);
    // usbMIDI.sendNoteOff(lastNote, 127, 1);
  }
}
