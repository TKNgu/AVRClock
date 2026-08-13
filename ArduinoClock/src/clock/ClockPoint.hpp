#ifndef CLOCKPOINT_HPP
#define CLOCKPOINT_HPP

#include "../utils/Timer.hpp"

struct ClockPoint {
    Timer timer;
    bool showTimePoint = false;

    ClockPoint();
    void show(unsigned long);
};

#endif // CLOCKPOINT_HPP
