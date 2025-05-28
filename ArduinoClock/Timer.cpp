#include "Timer.hpp"
#include <Arduino.h>

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
