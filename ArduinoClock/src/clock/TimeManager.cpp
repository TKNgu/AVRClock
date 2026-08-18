#include "TimeManager.hpp"

#include <Arduino.h>

#include "../utils/PowerManager.hpp"
#include "../utils/Utils.hpp"

#define UPDATE_TIME_TASK 3600000

TimeManager::TimeManager() : syncTimer(CreateTimer(UPDATE_TIME_TASK)) {}

void TimeManager::reload() {
    GetTime(&hour, &minutes, &seconds);
    timeOffset = powerManager.getMillis() - (unsigned long)seconds * 1000;
}

void TimeManager::setTime() { SetTime(hour, minutes); }

void TimeManager::updateTime(unsigned long now) {
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

#define SLEEP_HOUR 23
#define SLEEP_MINUTE 45
#define WAKE_HOUR 5
#define WAKE_MINUTE 00

static const unsigned int wakeUpTime = WAKE_HOUR * 60 + WAKE_MINUTE;
static const unsigned int sleepTime = SLEEP_HOUR * 60 + SLEEP_MINUTE;

static bool inInterval(unsigned int T, unsigned int start, unsigned int end) {
    if (start <= end) {
        return T >= start && T < end;
    } else {
        return T >= start || T < end;
    }
}

TimeManagerAdvance::TimeManagerAdvance() { dynamicSleepTime = sleepTime; }

bool TimeManagerAdvance::needSleep() {
    const unsigned int tmp = hour * 60 + minutes;

    unsigned int safeResetTimeEnd = (sleepTime + 24 * 60 - 60) % (24 * 60);
    if (inInterval(tmp, wakeUpTime, safeResetTimeEnd)) {
        dynamicSleepTime = sleepTime;
    }

    return inInterval(tmp, dynamicSleepTime, wakeUpTime);
}

bool TimeManagerAdvance::isNearWakeUp(unsigned int minutesBefore) {
    unsigned int tmp = hour * 60 + minutes;

    int diff = wakeUpTime - tmp;
    if (diff < 0) {
        diff += 24 * 60;
    }

    return diff > 0 && diff <= (int)minutesBefore;
}

void TimeManagerAdvance::waitSleep(unsigned long duration) {
    unsigned int totalMinutes = hour * 60 + minutes + duration;
    dynamicSleepTime = totalMinutes % (24 * 60);
}
