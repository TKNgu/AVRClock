#include "ChimeController.hpp"

#include "../utils/PowerManager.hpp"
#include "../utils/Utils.hpp"

const unsigned MINUTES_IN_WEEK = 7 * 24 * 60;

ChimeController::ChimeController() {
    unsigned char offset = 0;
    for (unsigned char dayOfWeek = 1; dayOfWeek <= 7; dayOfWeek++) {
        timePoints[offset++] = TimePointInit(dayOfWeek, 5, 00);
        timePoints[offset++] = TimePointInit(dayOfWeek, 7, 30);
        timePoints[offset++] = TimePointInit(dayOfWeek, 22, 30);
        timePoints[offset++] = TimePointInit(dayOfWeek, 23, 30);
    }
}

void ChimeController::reload(unsigned char dayOfWeek, unsigned char hour,
                             unsigned char min) {
    TimePoint timePoint = TimePointInit(dayOfWeek, hour, min);
    for (indexTimePoint = 0; indexTimePoint < HOURLY_CHIME_SIZE;
         indexTimePoint++) {
        TimePoint tmp = timePoints[indexTimePoint];
        if (tmp < timePoint) {
            continue;
        }
        if (tmp == timePoint) {
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
    if (nextTimePoint < timePoint) {
        minutesCount = MINUTES_IN_WEEK + nextTimePoint - timePoint;
    } else {
        minutesCount = nextTimePoint - timePoint;
    }
}

bool ChimeController::shouldChime(unsigned char dayOfWeek, unsigned char hour,
                                  unsigned char min) {
    if (minutesCount-- > 1) {
        return false;
    }

    TimePoint timePoint = timePoints[indexTimePoint];
    indexTimePoint++;
    if (indexTimePoint >= HOURLY_CHIME_SIZE) {
        indexTimePoint = 0;
    }
    TimePoint nextTimePoint = timePoints[indexTimePoint];
    if (nextTimePoint < timePoint) {
        minutesCount = MINUTES_IN_WEEK + nextTimePoint - timePoint;
    } else {
        minutesCount = nextTimePoint - timePoint;
    }
    return true;
}
