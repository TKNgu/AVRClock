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
    virtual ~TimeManager() = default;

    void reload();
    void setTime();
    void updateTime(unsigned long);
    void increaseMinute(unsigned char);
    void decreaseMinute(unsigned char);
    void increaseHour(unsigned char);
    void decreaseHour(unsigned char);
};

class TimeManagerAdvance : public TimeManager {
  public:
    TimeManagerAdvance();

    bool needSleep();
    bool isNearWakeUp(unsigned int minutesBefore);
    void waitSleep(unsigned long duration);

  private:
    unsigned int dynamicSleepTime;
};

#endif // TIMEMANAGER_HPP
