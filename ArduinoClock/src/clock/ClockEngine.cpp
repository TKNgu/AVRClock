#include "ClockEngine.hpp"

#include <Arduino.h>

#include "../utils/Utils.hpp"

#define UPDATE_TIME_TASK 3600000

ClockEngine::ClockEngine() : syncTimer(CreateTimer(UPDATE_TIME_TASK)) {}

void ClockEngine::reload() {
    timeOffset = millis();
    GetTime(&hour, &minutes, &seconds);
}

void ClockEngine::updateTime(unsigned long now) {
    isUpdateMinute = false;
    isUpdateDay = false;
    if (TimerTimeoutFix(&this->syncTimer, now)) {
        GetTime(&hour, &minutes, &seconds);
        return;
    }

    seconds = (now - timeOffset) / 1000;
    if (seconds < 60) {
        return;
    }
    timeOffset = now;
    seconds -= 60;

    minutes++;
    isUpdateMinute = true;
    if (minutes < 60) {
        return;
    }
    minutes -= 60;

    hour++;
    if (hour < 24) {
        return;
    }
    hour -= 24;
    isUpdateDay = true;
}
