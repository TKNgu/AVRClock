#ifndef TIMEMANAGER_HPP
#define TIMEMANAGER_HPP

#include "../timer/Timer.hpp"

struct TimeManager {
    Timer syncTimer;

    unsigned long timeNow;
    unsigned int milliseconds;
    unsigned char seconds;
    unsigned char minutes;
    unsigned char hour;
    unsigned char dayOfWeek;

    bool isSecondsUpdate = false;
    bool isUpdateMinute = false;
    bool isUpdateDay = false;

    TimeManager();
    virtual ~TimeManager() = default;

    void reload(unsigned long);
    void updateTime(unsigned long);
    void increaseMinute(unsigned char);
    void decreaseMinute(unsigned char);
    void increaseHour(unsigned char);
    void decreaseHour(unsigned char);
    void setTime();
    void setDayOfWeek(unsigned char);
};

class TimeManagerAdvance : public TimeManager {
  public:
    TimeManagerAdvance();

    bool needSleep();
    bool needDeepSleep();

  private:
    unsigned int dynamicSleepTime;
};

#endif // TIMEMANAGER_HPP
