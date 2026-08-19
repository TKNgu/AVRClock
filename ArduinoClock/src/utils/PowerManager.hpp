#ifndef POWERMANAGER_HPP
#define POWERMANAGER_HPP

#include "../timer/Timer.hpp"

class PowerManager {
  public:
    void buzzer();
    void sleep(unsigned long);

  private:
    unsigned long buzzerTime;
};

extern PowerManager powerManager;

#endif // POWERMANAGER_HPP
