#ifndef CHIMECONTROLLER_HPP
#define CHIMECONTROLLER_HPP

#include "../timer/TimePoint.hpp"

#define HOURLY_CHIME_SIZE 28

struct ChimeController {
    TimePoint timePoints[HOURLY_CHIME_SIZE];
    unsigned char indexTimePoint;
    unsigned long minutesCount;

    ChimeController();
    void reload();
    bool shouldChime();
};

#endif // CHIMECONTROLLER_HPP
