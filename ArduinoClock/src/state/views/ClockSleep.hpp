#ifndef CLOCKSLEEP_HPP
#define CLOCKSLEEP_HPP

#include "../State.hpp"

class ClockSleep : public ClockState {
  public:
    virtual void reload() override;
    virtual void loop(unsigned long) override;

  private:
    Timer sleepTimer_ = CreateTimer(1000);
    bool isNeedClear_ = true;
    bool isNearWakeUpSynced_ = false;
};

#endif // CLOCKSLEEP_HPP
