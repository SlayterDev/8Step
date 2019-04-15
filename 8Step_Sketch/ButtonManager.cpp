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

    bool state = trellis.readSwitches();

    if (state) {
        if (trellis.justPressed(SHIFT_BTN)) {
            trellis.setLED(SHIFT_BTN);
        }
        if (trellis.justReleased(SHIFT_BTN)) {
            trellis.clrLED(SHIFT_BTN);
        }
    }

    return state;
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
            clearAllBeats();
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
            clearAllBeats();
        } else {
            trellis.clrLED(REC_BTN);
        }
    }

    return justPressed;
}

bool ButtonManager::tapPressed() {
    bool state = trellis.isLED(TAP_BTN);
    bool justPressed = trellis.justPressed(TAP_BTN);

    if (justPressed) {
        trellis.setLED(TAP_BTN);
    } else {
        trellis.clrLED(TAP_BTN);
    }

    return justPressed;
}

bool ButtonManager::extendPressed() {
    bool justPressed = trellis.justPressed(NEXT_BTN) && trellis.isKeyPressed(SHIFT_BTN);

    if (justPressed) {
        trellis.setLED(NEXT_BTN);
    } else {
        trellis.clrLED(NEXT_BTN);
    }
    
    return justPressed;
}

bool ButtonManager::reducePressed() {
    bool justPressed = trellis.justPressed(PREV_BTN) && trellis.isKeyPressed(SHIFT_BTN);

    if (justPressed) {
        trellis.setLED(PREV_BTN);
    } else {
        trellis.clrLED(PREV_BTN);
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

uint8_t ButtonManager::noteReleased(bool isPlaying) {
    uint8_t note = 0;
    
    for (int i = 8; i < 16; i++) {
        if (trellis.justReleased(i)) {
            note = notes[i - 8];

            if (!isPlaying && i + 8 >= stepsPressed) {
                trellis.clrLED(i);
            }
        }
    }

    return note;
}

void ButtonManager::clearAllBeats() {
    for (int i = 8; i < 16; i++) {
        trellis.clrLED(i);
    }
}

void ButtonManager::setBeatLED(int beat, int sequenceLength) {
    clearAllBeats();
    trellis.setLED((beat % 8) + 8);

    if (sequenceLength > 8) {
        uint8_t pageNum = beat / 8;
        trellis.setLED(pageNum + 8);
    }
}

void ButtonManager::setStepRecordLEDs(int steps, int sequenceLength) {
    if (steps == 8)
        clearAllBeats();

    stepsPressed = steps % 8;
    for (int i = 8; i < 8 + stepsPressed; i++) {
        trellis.setLED(i);
    }

    if (sequenceLength > 8) {
        uint8_t pageLED = (steps / 8) + 8;
        if (trellis.isLED(pageLED)) {
            trellis.clrLED(pageLED);
        } else {
            trellis.setLED(pageLED);
        }
    }
}
