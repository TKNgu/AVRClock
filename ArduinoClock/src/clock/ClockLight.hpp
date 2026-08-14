#ifndef CLOCKLIGHT_HPP
#define CLOCKLIGHT_HPP

#include "../utils/Timer.hpp"

struct ClockLight {
    Timer timer;

    ClockLight();
    void check(const unsigned long);
};

#endif // CLOCKLIGHT_HPP
