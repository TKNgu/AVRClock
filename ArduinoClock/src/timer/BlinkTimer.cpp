#include "BlinkTimer.hpp"

#include <Arduino.h>

BlinkTimer::BlinkTimer(unsigned long leng) : timer(CreateTimer(leng)) {}

void BlinkTimer::reset(unsigned long now) {
    ResetTimer(&timer, now);
    isBlink = false;
}

bool BlinkTimer::blink(unsigned long now) {
    if (TimerTimeoutFix(&timer, now)) {
        isBlink = !isBlink;
    }
    return isBlink;
}
