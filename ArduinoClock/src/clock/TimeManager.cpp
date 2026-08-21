#include "TimeManager.hpp"

#include <Arduino.h>

#include "../utils/Utils.hpp"

#define WAIT_SLEEP_TIME 300000
#define UPDATE_TIME_TASK 3600000

TimeManager::TimeManager() : syncTimer(CreateTimer(UPDATE_TIME_TASK)) {}

void TimeManager::reload(unsigned long now) {
    timeNow = now;
    milliseconds = 0;
    unsigned char tmp;
    GetDateTime(&hour, &minutes, &seconds, &dayOfWeek, &tmp, &tmp, &tmp);
}

void TimeManager::setTime() { SetTime(hour, minutes); }

void TimeManager::updateTime(unsigned long now) {
    isUpdateMinute = false;
    isUpdateDay = false;

    unsigned int delta = now - timeNow;
    timeNow = now;
    milliseconds += delta;
    const unsigned char tmp = milliseconds / 1000;
    if (tmp < 1) {
        return;
    }

    isSecondsUpdate = true;
    seconds += tmp;
    milliseconds %= 1000;
    if (seconds < 60) {
        return;
    }
    seconds -= 60;

    isUpdateMinute = true;
    minutes++;
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
    dayOfWeek++;
    if (dayOfWeek > 7) {
        dayOfWeek = 1;
    }
}

void TimeManager::increaseMinute(unsigned char value) {
    minutes += value;
    if (minutes >= 60) {
        minutes -= 60;
    }
}

void TimeManager::decreaseMinute(unsigned char value) {
    minutes = minutes >= value ? minutes - value : minutes + 60 - value;
}

void TimeManager::increaseHour(unsigned char value) {
    hour += value;
    if (hour >= 24) {
        hour -= 24;
    }
}

void TimeManager::decreaseHour(unsigned char value) {
    hour = hour >= value ? hour - value : hour + 24 - value;
}

void TimeManager::setDayOfWeek(unsigned char value) {
    dayOfWeek = value;
    SetDayOfWeek(dayOfWeek);
}

#define SLEEP_HOUR 23
#define SLEEP_MINUTE 45
#define WAKE_HOUR 5
#define WAKE_MINUTE 00
#define DEEP_SLEEP_WAIT_TIME 30
#define DEEP_SLEEP_TIME 3600

static const unsigned int wakeUpTime = WAKE_HOUR * 60 + WAKE_MINUTE;
static const unsigned int sleepTime = SLEEP_HOUR * 60 + SLEEP_MINUTE;
static const unsigned int deepSleepTime =
    WAKE_HOUR * 60 + WAKE_MINUTE - DEEP_SLEEP_WAIT_TIME;

TimeManagerAdvance::TimeManagerAdvance() { dynamicSleepTime = sleepTime; }

bool TimeManagerAdvance::needSleep() {
    const unsigned int tmp = hour * 60 + minutes;
    if (tmp < wakeUpTime) {
        return true;
    }
    return tmp > sleepTime;
}

unsigned int TimeManagerAdvance::getDeepSleepTime() {
    const unsigned int tmp = hour * 60 + minutes;
    if (tmp > sleepTime) {
        return DEEP_SLEEP_TIME;
    }
    if (tmp > deepSleepTime) {
        return 0;
    }
    const unsigned int delta = (deepSleepTime - tmp) * 60;
    return (delta > DEEP_SLEEP_TIME) ? DEEP_SLEEP_TIME : delta;
}
