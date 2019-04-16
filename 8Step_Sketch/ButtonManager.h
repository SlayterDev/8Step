#ifndef __BUTTONMANAGER__
#define __BUTTONMANAGER__

#include <Wire.h>
#include <Adafruit_Trellis.h>
#include <stdint.h>

class ButtonManager {
public:
    void setupManager();
    bool stateChanged(unsigned long delta, bool currentMode);
    bool playPressed();
    void togglePlayButton();
    bool recordPressed();
    bool tapPressed();
    bool modeChanged(bool currentMode);

    bool extendPressed();
    bool reducePressed();

    void commitLEDState();
    uint8_t notePressed();
    uint8_t noteReleased(bool isRecording);
    void setBeatLED(int beat, int sequenceLength);
    void setStepRecordLEDs(int steps, int sequenceLength);

    ButtonManager() :
    previousReadTime(0),
    stepsPressed(0),
    octaveMod(0) {
        uint8_t temp[] = {60, 62, 64, 65, 67, 69, 71, 72};
        for (int i = 0; i < 8; i++) {
            notes[i] = temp[i];
        }
    }

private: 
    enum ButtonDefs {
        PLAY_BTN = 0,
        REC_BTN,
        TAP_BTN,
        SHIFT_BTN,
        DOWN_BTN,
        UP_BTN,
        PREV_BTN,
        NEXT_BTN,
        NOTE_START_BTN
    };

    Adafruit_Trellis trellis;
    uint8_t notes[8];
    unsigned long previousReadTime;
    uint8_t stepsPressed;
    int octaveMod;

    void clearAllBeats();
    uint8_t addOctave(uint8_t note);
    void checkOctaveButtons();
};

#endif
