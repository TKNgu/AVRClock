#ifndef TIMEMANAGER_HPP
#define TIMEMANAGER_HPP

#include "../timer/Timer.hpp"

#define WAIT_SLEEP_TIME 300000

struct TimeManager {
    Timer syncTimer;
    Timer waitSleepTimer = CreateTimer(WAIT_SLEEP_TIME);

    unsigned long timeOffset;
    unsigned char hour;
    unsigned char minutes;
    unsigned char seconds;

    bool isUpdateMinute = false;
    bool isUpdateDay = false;

    TimeManager();
    void reload();
    void setTime();
    void updateTime(unsigned long);
    void addMinute(unsigned char);
    void subMinute(unsigned char);
    void addHour(unsigned char);
    void subHour(unsigned char);
};

class TimeManagerAdvance : public TimeManager {
  public:
    bool needSleep();
    void waitSleep(unsigned long duration);
};

#endif // TIMEMANAGER_HPP
