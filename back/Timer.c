#include "Timer.h"

void TimerSet(Timer *timer, unsigned long next) {
    timer = millis() + next;
}

bool TimerTimeout(const Timer timer) {
    return timer < millis();
}
