#include "BlinkTimer.hpp"

#include <Arduino.h>

BlinkTimer::BlinkTimer(unsigned long leng) : timer(CreateTimer(leng)) {}

bool BlinkTimer::blink(unsigned long now) {
    return TimerTimeoutFix(&timer, now);
}

void BlinkTimer::reset(unsigned long now, bool isBlink) {
    ResetTimer(&timer, now);
    this->isBlink = isBlink;
}
