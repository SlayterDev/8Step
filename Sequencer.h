#ifndef __SEQUENCER__
#define __SEQUENCER__

#include <stdint.h>

class Sequencer {
public:
    enum SequencerState {
        SEQUENCER_STATE_STOPPED = 0,
        SEQUENCER_STATE_PLAYING,
        SEQUENCER_STATE_RECORDING
    };

    void togglePlayPause();
    void startRecording();
    int getCurrentStep();
    SequencerState getState();
    uint8_t processStep();
    void increaseSequence();
    void decreaseSequence();

    bool addStep(uint8_t step);

    Sequencer() :
    sequenceLength(8),
    state(SEQUENCER_STATE_STOPPED),
    currentStep(0) {
        for (int i = 0; i < 32; i++) {
            sequence[i] = 0;
        }
    }

    //// INLINE FUNCTIONS ////
    inline bool isPlaying() const { return state == SEQUENCER_STATE_PLAYING; }

private:
    uint8_t sequence[32];
    int sequenceLength;

    SequencerState state;
    int currentStep;
};

#endif
