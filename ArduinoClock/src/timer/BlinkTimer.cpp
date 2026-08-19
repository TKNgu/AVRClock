#include "BlinkTimer.hpp"

BlinkTimer::BlinkTimer(unsigned long leng) : timer(CreateTimer(leng)) {}

bool BlinkTimer::blink(unsigned long now) {
    if (TimerTimeoutFix(&timer, now)) {
        isBlink = !isBlink;
        return true;
    }
    return false;
}

void BlinkTimer::reset(unsigned long now, bool isBlink) {
    ResetTimer(&timer, now);
    this->isBlink = isBlink;
}
