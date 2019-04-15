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
    void commitLEDState();

    ButtonManager() :
    previousReadTime(0) {
        for (int i = 0; i < 8; i++) {
            notes[i] = i + 60;
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
};

#endif
