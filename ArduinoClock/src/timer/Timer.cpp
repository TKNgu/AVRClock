#include "Timer.hpp"
#include "../utils/PowerManager.hpp"
#include <Arduino.h>

void ResetTimer(Timer* timer, unsigned long now) {
    timer->nextTime = now + timer->leng;
}

void ResetTimer(Timer* timer) { ResetTimer(timer, powerManager.getMillis()); }

Timer CreateTimer(unsigned long leng) {
    return Timer{
        .leng = leng,
        .nextTime = 0,
    };
}

bool TimerTimeoutFix(Timer* timer, unsigned long timeNow) {
    if ((long)(timeNow - timer->nextTime) < 0) {
        return false;
    }
    const unsigned long delta = timeNow - timer->nextTime;
    timer->nextTime = timeNow + timer->leng - delta % timer->leng;
    return true;
}

bool TimerTimeout(Timer* timer) {
    return TimerTimeoutFix(timer, powerManager.getMillis());
}
