#include "Timer.hpp"
#include <Arduino.h>

void ResetTimer(Timer* timer, unsigned long now) {
    timer->nextTime = now + timer->leng;
}

void ResetTimer(Timer* timer) { ResetTimer(timer, millis()); }

Timer CreateTimer(unsigned long leng) {
    return Timer{
        .leng = leng,
        .nextTime = 0,
    };
}

bool TimerTimeoutFix(Timer* timer, unsigned long timeNow) {
    if (timer->nextTime > timeNow) {
        return false;
    }
    timer->nextTime = timeNow + timer->leng;
    return true;
}

bool TimerTimeout(Timer* timer) { return TimerTimeoutFix(timer, millis()); }
