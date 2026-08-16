#include "BlinkTimer.hpp"

#include <Arduino.h>

BlinkTimer::BlinkTimer(unsigned long leng) : timer(CreateTimer(leng)) {}

void BlinkTimer::reset(unsigned long now) {
    ResetTimer(&timer, now);
    isBlink = false;
    isChanged = true;
}

bool BlinkTimer::blink(unsigned long now) {
    if (TimerTimeoutFix(&timer, now)) {
        isBlink = !isBlink;
        isChanged = true;
    } else {
        isChanged = false;
    }
    return isBlink;
}
