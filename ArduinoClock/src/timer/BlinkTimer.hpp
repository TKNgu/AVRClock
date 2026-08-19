#ifndef BLINKTIMER_HPP
#define BLINKTIMER_HPP

#include "Timer.hpp"

struct BlinkTimer {
    Timer timer;
    bool isBlink = true;

    BlinkTimer(unsigned long);
    bool blink(unsigned long);
    void reset(unsigned long, bool = true);
};

#endif // BLINKTIMER_HPP
