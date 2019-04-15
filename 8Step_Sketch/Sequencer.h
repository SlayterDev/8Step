#ifndef __SEQUENCER__
#define __SEQUENCER__

#include <stdint.h>
#include "ButtonManager.h"

#define MIN_SEQUENCE_LENGTH 8
#define MAX_SEQUENCE_LENGTH 32

class Sequencer {
public:
    enum SequencerState {
        SEQUENCER_STATE_STOPPED = 0,
        SEQUENCER_STATE_PLAYING,
        SEQUENCER_STATE_RECORDING
    };

    void togglePlayPause();
    void startRecording();
    uint8_t processStep(ButtonManager *manager);
    void increaseSequence();
    void decreaseSequence();

    bool addStep(uint8_t step);

    Sequencer() :
    sequenceLength(MIN_SEQUENCE_LENGTH),
    state(SEQUENCER_STATE_STOPPED),
    currentStep(0) {
        for (int i = 0; i < MAX_SEQUENCE_LENGTH; i++) {
            sequence[i] = 0;
        }
    }

    //// INLINE FUNCTIONS ////
    inline bool isPlaying() const { return state == SEQUENCER_STATE_PLAYING; }
    inline int getSequenceLength() const { return sequenceLength; }
    inline int getCurrentStep() { return currentStep; }
    inline SequencerState getState() { return state; }

private:
    uint8_t sequence[MAX_SEQUENCE_LENGTH];
    int sequenceLength;

    SequencerState state;
    int currentStep;
};

#endif
