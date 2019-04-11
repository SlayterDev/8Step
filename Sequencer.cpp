#include "Sequencer.h"

void Sequencer::togglePlayPause() {
    if (state != SEQUENCER_STATE_PLAYING) {
        if (state == SEQUENCER_STATE_RECORDING) {
            currentStep = 0;
        }

        state = SEQUENCER_STATE_PLAYING;
    } else {
        state = SEQUENCER_STATE_STOPPED;
    }
}

void Sequencer::startRecording() {
    state = SEQUENCER_STATE_RECORDING;
    currentStep = 0;
}

uint8_t Sequencer::processStep() {
    uint8_t step = sequence[currentStep];

    currentStep++;
    if (currentStep == sequenceLength) {
        currentStep = 0;
    }

    return step;
}

void Sequencer::increaseSequence() {
    if (sequenceLength == MAX_SEQUENCE_LENGTH) return;

    sequenceLength += 8;

    // Clear out the new section of the sequence
    for (int i = sequenceLength - 8; i < sequenceLength; i++) {
        sequence[i] = 0;
    }
}

void Sequencer::decreaseSequence() {
    if (sequenceLength == MIN_SEQUENCE_LENGTH) return;

    sequenceLength -= 8;
}

bool Sequencer::addStep(uint8_t step) {
    if (state != SEQUENCER_STATE_RECORDING) return false;
    if (currentStep == sequenceLength) return false; // TODO: Reconsider?

    sequence[currentStep] = step;
    currentStep++;

    return true;
}
