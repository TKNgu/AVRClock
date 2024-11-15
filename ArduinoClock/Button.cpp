#include "Button.hpp"
#include "Utils.hpp"
#include "Arduino.h"

void ButtonInit(Button *button, Key key, void (*shortFn)(void), void (*longFn)(void)) {
    button->key = key;
    button->click = false;
    button->shortFn = shortFn;
    button->longFn = longFn;
    button->time = 0;
    button->isLongPress = false;
}

void ButtonScan(Button *button) {
    if (ReadKey(button->key)) {
        if (button->click) {
            if (button->time + LONG_PRESS <= millis()) {
                button->isLongPress = true;
                button->longFn();
                button->time += LONG_PRESS;
            }
        }
        else {
            button->click = true;
            button->time = millis();
        }
    }
    else if (button->click) {
        button->click = false;
        if (button->isLongPress) {
            button->isLongPress = false;
        }
        else if (button->time + SHORT_PRESS <= millis()) {
            button->shortFn();
        }
    }
}

void NOP() {}
