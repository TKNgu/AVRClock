#ifndef CLOCKLIGHT_HPP
#define CLOCKLIGHT_HPP

#include "../utils/Timer.hpp"

#define CHECK_LIGHT_TASK 2000
#define SIZE_ITEM 7

struct ArrayMax {
    unsigned valueMax[SIZE_ITEM] = {0, 0, 0, 0, 0, 0, 0};
    float valueMaxWeight[SIZE_ITEM] = {
        64.f / 127.f, 32.f / 127.f, 16.f / 127.f, 8.f / 127.f,
        4.f / 127.f,  2.f / 127.f,  1.f / 127.f,
    };
    unsigned valueMaxIndex = 0;

    ArrayMax();
    float getValueMax();
    float update(unsigned);
};

struct ClockLight {
    Timer timer = CreateTimer(CHECK_LIGHT_TASK);
    unsigned long maxLightLocal = 0x00;
    float maxLightGlobal = 0x00;
    unsigned char lightLevel = 0xff;
    ArrayMax arrayMax;

    ClockLight();
    void check(const unsigned long);
    void update(int);
    void updateGlobal();
};

#endif // CLOCKLIGHT_HPP
