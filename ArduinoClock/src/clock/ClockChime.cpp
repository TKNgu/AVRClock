#include "ClockChime.hpp"

#include "../utils/Utils.hpp"

ClockChime::ClockChime() {
    unsigned char offset = 0;
    for (unsigned char dayOfWeek = 1; dayOfWeek <= 7; dayOfWeek++) {
        timePoints[offset++] = TimePointInit(dayOfWeek, 5, 00);
        timePoints[offset++] = TimePointInit(dayOfWeek, 7, 30);
        timePoints[offset++] = TimePointInit(dayOfWeek, 22, 30);
        timePoints[offset++] = TimePointInit(dayOfWeek, 23, 30);
    }
}

void ClockChime::reload() {
    TimePoint timePoint = GetTimePoint();
    for (indexTimePoint = 0; indexTimePoint < HOURLY_CHIME_SIZE;
         indexTimePoint++) {
        TimePoint tmp = timePoints[indexTimePoint];
        if (tmp < timePoint) {
            continue;
        }
        if (tmp == timePoint) {
            Buzzer();
            indexTimePoint++;
            break;
        }
        if (tmp > timePoint) {
            break;
        }
    }
    if (indexTimePoint >= HOURLY_CHIME_SIZE) {
        indexTimePoint = 0;
    }
    TimePoint nextTimePoint = timePoints[indexTimePoint];
    minutesCount = nextTimePoint - timePoint;
}

void ClockChime::check() {
    if (minutesCount-- > 1) {
        return;
    }
    Buzzer();

    TimePoint timePoint = timePoints[indexTimePoint];
    indexTimePoint++;
    if (indexTimePoint >= HOURLY_CHIME_SIZE) {
        indexTimePoint = 0;
    }
    TimePoint nextTimePoint = timePoints[indexTimePoint];
    minutesCount = nextTimePoint - timePoint;
}
