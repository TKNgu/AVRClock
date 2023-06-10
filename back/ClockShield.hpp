#ifndef ClockShield_hpp
#define ClockShield_hpp

#include "Arduino.h"
#include "TTSDisplay.h"
#include "TTSTime.h"

class ClockShield {
public:
 enum Key {
  K1 = 9,
  K2 = 10,
  K3 = 11,
 };

 enum Led {
  LED1 = 2,
  LED2 = 3,
  LED3 = 4,
  LED4 = 5,
 };

public:
 ClockShield();

protected:
 TTSTime time;
 TTSDisplay display;
};

#endif
