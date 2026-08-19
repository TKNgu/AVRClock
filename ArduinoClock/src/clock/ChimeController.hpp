#ifndef CHIMECONTROLLER_HPP
#define CHIMECONTROLLER_HPP

#include "../timer/TimePoint.hpp"

#define HOURLY_CHIME_SIZE 28

struct ChimeController {
    TimePoint timePoints[HOURLY_CHIME_SIZE];
    unsigned char indexTimePoint;
    unsigned long minutesCount;

    ChimeController();
    void reload(unsigned char, unsigned char, unsigned char);
    bool shouldChime(unsigned char, unsigned char, unsigned char);
};

#endif // CHIMECONTROLLER_HPP
