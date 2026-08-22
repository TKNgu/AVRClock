#ifndef CLOCKDEEPSLEEP_HPP
#define CLOCKDEEPSLEEP_HPP

#include "../State.hpp"

class WDTScale {
  public:
    WDTScale();
    unsigned int start(unsigned char, unsigned char, unsigned char,
                       unsigned int);
    void stop(unsigned char, unsigned char, unsigned char, unsigned int);
    void save();

  public:
    float scale;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
    unsigned int startPoint;
};

class ClockDeepSleep : public State {
  public:
    virtual void reload() override;
    virtual void loop() override;

  private:
    WDTScale wdtScale;
    unsigned int deepSleepTimer;
    bool isNeedView;
};

#endif // CLOCKDEEPSLEEP_HPP
