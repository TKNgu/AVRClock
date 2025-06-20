#include "Button.hpp"
#include <Arduino.h>

#include "Utils.hpp"

Button CreateButton(const Key key, void (*shortFn)(void)) {
    return Button {
        .key = key,
        .click = false,
        .shortFn = shortFn,
        .longFn = NOP,
        .time = 0,
        .isLongPress = false,
    };
}

Button CreateButtonLongPress(const Key key, void (*shortFn)(void), void (*longFn)(void)) {
    return Button {
        .key = key,
        .click = false,
        .shortFn = shortFn,
        .longFn = longFn,
        .time = 0,
        .isLongPress = false,
    };
}

void ButtonInit(Button *button, Key key, void (*shortFn)(void), void (*longFn)(void)) {
    *button = CreateButtonLongPress(key, shortFn, longFn);
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
