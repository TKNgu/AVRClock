#ifndef CLOCKCHIME_HPP
#define CLOCKCHIME_HPP

#include "../utils/TimePoint.hpp"

#define HOURLY_CHIME_SIZE 28

struct ClockChime {
    TimePoint timePoints[HOURLY_CHIME_SIZE];
    unsigned char indexTimePoint;
    unsigned long minutesCount;

    ClockChime();
    void reload();
    void check();
};

#endif // CLOCKCHIME_HPP
