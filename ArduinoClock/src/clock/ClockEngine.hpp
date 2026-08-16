#ifndef CLOCKENGINE_HPP
#define CLOCKENGINE_HPP

#include "../utils/Timer.hpp"

struct ClockEngine {
    Timer syncTimer;
    unsigned long timeOffset;
    unsigned char hour;
    unsigned char minutes;
    unsigned char seconds;

    bool isUpdateMinute = false;
    bool isUpdateDay = false;

    ClockEngine();
    void reload();
    void updateTime(unsigned long);
};

#endif // CLOCKENGINE_HPP
