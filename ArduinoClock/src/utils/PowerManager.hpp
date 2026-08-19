#ifndef POWERMANAGER_HPP
#define POWERMANAGER_HPP

#include "LowPower.h"

enum class SleepMode { Deep, Idle };

class PowerManager {
  public:
    PowerManager() = default;

    void buzzer();
    void buzzerSilent();

    void sleep(SleepMode mode, period_t period, bool needAdc = true);

    void blockDeepSleep(unsigned long durationMs = 2000);

    unsigned long getMillis();

  private:
    unsigned long blockDeepSleepUntil = 0;
    unsigned long sleepCompensation = 0;
    unsigned long getPeriodMs(period_t period);
};

extern PowerManager powerManager;

#endif // POWERMANAGER_HPP
