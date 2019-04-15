#ifndef __BUTTONMANAGER__
#define __BUTTONMANAGER__

#include <Wire.h>
#include <Adafruit_Trellis.h>
#include <stdint.h>

class ButtonManager {
public:
    void setupManager();
    bool stateChanged(unsigned long delta);
    bool playPressed();
    bool recordPressed();
    void commitLEDState();
    uint8_t notePressed();
    uint8_t noteReleased();
    void setBeatLED(int beat);

    ButtonManager() :
    previousReadTime(0) {
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

    void clearAllBeats();
};

#endif
