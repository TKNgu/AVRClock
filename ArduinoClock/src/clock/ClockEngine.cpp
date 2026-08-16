#include "ClockEngine.hpp"

#include <Arduino.h>

#include "../utils/Utils.hpp"

#define UPDATE_TIME_TASK 3600000

ClockEngine::ClockEngine() : syncTimer(CreateTimer(UPDATE_TIME_TASK)) {}

void ClockEngine::reload() {
    GetTime(&hour, &minutes, &seconds);
    timeOffset = millis() - (unsigned long)seconds * 1000;
}

void ClockEngine::setTime() { SetTime(hour, minutes); }

void ClockEngine::updateTime(unsigned long now) {
    isUpdateMinute = false;
    isUpdateDay = false;
    if (TimerTimeoutFix(&this->syncTimer, now)) {
        GetTime(&hour, &minutes, &seconds);
        timeOffset = now - (unsigned long)seconds * 1000;
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

void ClockEngine::addMinute(unsigned char value) {
    minutes += value;
    if (minutes >= 60) {
        minutes -= 60;
    }
}

void ClockEngine::subMinute(unsigned char value) {
    minutes = minutes >= value ? minutes - value : minutes + 60 - value;
}

void ClockEngine::addHour(unsigned char value) {
    hour += value;
    if (hour >= 24) {
        hour -= 24;
    }
}

void ClockEngine::subHour(unsigned char value) {
    hour = hour >= value ? hour - value : hour + 24 - value;
}
#define SLEEP_HOUR 23
#define SLEEP_MINUTE 45
#define WAKE_HOUR 5
#define WAKE_MINUTE 00

bool ClockEngineAdvance::needSleep() {
    if (TimerTimeout(&waitSleepTimer)) {
        const static unsigned int SLEEP_TIME = SLEEP_HOUR * 60 + SLEEP_MINUTE;
        const static unsigned int WAKE_TIME = WAKE_HOUR * 60 + WAKE_MINUTE;
        const unsigned int tmp = hour * 60 + minutes;
        return tmp >= SLEEP_TIME || tmp < WAKE_TIME;
    }
    return false;
}

void ClockEngineAdvance::waitSleep(unsigned long duration) {
    waitSleepTimer.leng = duration;
    ResetTimer(&waitSleepTimer);
}
