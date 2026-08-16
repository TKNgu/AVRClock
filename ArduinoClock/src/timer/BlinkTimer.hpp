#ifndef BLINKTIMER_HPP
#define BLINKTIMER_HPP

#include "Timer.hpp"

struct BlinkTimer {
    Timer timer;
    bool isBlink = false;

    BlinkTimer(unsigned long);
    void reset(unsigned long);
    bool blink(unsigned long);
};

#endif // BLINKTIMER_HPP
