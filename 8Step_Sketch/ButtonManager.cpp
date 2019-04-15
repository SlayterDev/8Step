#include "ButtonManager.h"

void ButtonManager::setupManager() {
    trellis.begin(0x70);
#ifdef __AVR__
    // Default Arduino I2C speed is 100 KHz, but the HT16K33 supports
    // 400 KHz.  We can force this for faster read & refresh, but may
    // break compatibility with other I2C devices...so be prepared to
    // comment this out, or save & restore value as needed.
    TWBR = 12;
#endif
    trellis.clear();
    trellis.writeDisplay();
}

bool ButtonManager::stateChanged(unsigned long delta) {
    if (delta - previousReadTime < 20L) {
        return false;
    }
    
    previousReadTime = delta;

    return trellis.readSwitches();
}

void ButtonManager::commitLEDState() {
    trellis.writeDisplay();
}

bool ButtonManager::playPressed() {
    bool state = trellis.isLED(PLAY_BTN);
    bool justPressed = trellis.justPressed(PLAY_BTN);

    if (justPressed) {
        if (!state) {
            trellis.setLED(PLAY_BTN);
            trellis.clrLED(REC_BTN);
        } else {
            trellis.clrLED(PLAY_BTN);
        }
    }
    
    return justPressed;
}

bool ButtonManager::recordPressed() {
    bool state = trellis.isLED(REC_BTN);
    bool justPressed = trellis.justPressed(REC_BTN);

    if (justPressed) {
        if (!state) {
            trellis.setLED(REC_BTN);
            trellis.clrLED(PLAY_BTN);
        } else {
            trellis.clrLED(REC_BTN);
        }
    }

    return justPressed;
}

uint8_t ButtonManager::notePressed() {
    uint8_t note = 0;
    
    for (int i = 8; i < 16; i++) {
        if (trellis.justPressed(i)) {
            note = notes[i - 8];

            trellis.setLED(i);
        }
    }

    return note;
}

uint8_t ButtonManager::noteReleased() {
    uint8_t note = 0;
    
    for (int i = 8; i < 16; i++) {
        if (trellis.justReleased(i)) {
            note = notes[i - 8];

            trellis.clrLED(i);
        }
    }

    return note;
}
