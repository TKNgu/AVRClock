#include "Button2.hpp"

#include <Arduino.h>

#define LONG_PRESS 1000
#define SHORT_PRESS 100

Button2::Button2(Key key) : key(key) {}

Button2::State Button2::scan() { return scan(millis()); }

Button2::State Button2::scan(unsigned long now) {
    if (ReadKey(key)) {
        switch (state) {
        case Idle: {
            state = Click;
            time = now;
            return Idle;
        }
        case Click: {
            if (time + LONG_PRESS > now) {
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
        if (time + SHORT_PRESS > now) {
            return Idle;
        } else if (time + LONG_PRESS > now) {
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
