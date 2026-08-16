#ifndef CLOCKENGINE_HPP
#define CLOCKENGINE_HPP

#include "../timer/Timer.hpp"

#define WAIT_SLEEP_TIME 300000

struct ClockEngine {
    Timer syncTimer;
    Timer waitSleepTimer = CreateTimer(WAIT_SLEEP_TIME);

    unsigned long timeOffset;
    unsigned char hour;
    unsigned char minutes;
    unsigned char seconds;

    bool isUpdateMinute = false;
    bool isUpdateDay = false;

    ClockEngine();
    void reload();
    void setTime();
    void updateTime(unsigned long);
    void addMinute(unsigned char);
    void subMinute(unsigned char);
    void addHour(unsigned char);
    void subHour(unsigned char);
};

class ClockEngineAdvance : public ClockEngine {
  public:
    bool needSleep();
    void waitSleep(unsigned long duration);
};

#endif // CLOCKENGINE_HPP
