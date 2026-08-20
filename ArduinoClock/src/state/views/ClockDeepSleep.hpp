#ifndef CLOCKDEEPSLEEP_HPP
#define CLOCKDEEPSLEEP_HPP

#include "../State.hpp"

class ClockDeepSleep : public State {
  public:
    virtual void reload() override;
    virtual void loop() override;

  private:
    unsigned int deepSleepTimer;
    bool isNeedView;
};

#endif // CLOCKDEEPSLEEP_HPP
