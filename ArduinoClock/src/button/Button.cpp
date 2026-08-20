#include "Button.hpp"

#include <Arduino.h>

#define LONG_PRESS 1000
#define SHORT_PRESS 100

Button::Button(Key key) : key(key) {}

Button::State Button::scan(unsigned long now) {
    if (ReadKey(key)) {
        switch (state) {
        case Idle: {
            state = Click;
            time = now;
            return Idle;
        }
        case Click: {
            if (now - time < LONG_PRESS) {
                return Idle;
            }
            state = LongPress;
            return LongPress;
        }
        default:
            return LongPress;
        }
    }

    const State tmp = state;
    state = Idle;
    switch (tmp) {
    case Idle:
        return Idle;
    case Click: {
        if (now - time < SHORT_PRESS) {
            return Idle;
        } else if (now - time < LONG_PRESS) {
            return Click;
        } else {
            return LongPress;
        }
    }
    case LongPress: {
        return LongPress;
    }
    };
}

bool Button::isPress() { return ReadKey(key); }
