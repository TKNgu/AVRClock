#ifndef CLOCKSLEEP_HPP
#define CLOCKSLEEP_HPP

#include "../State.hpp"

class ClockSleep : public ClockState {
  public:
    virtual void reload() override;
    virtual void loop(unsigned long) override;

  private:
    BlinkTimer blinkTimer = BlinkTimer(1000);
    bool isNeedWarning = false;
    bool isNeedDeepSleep = false;
};

#endif // CLOCKSLEEP_HPP
