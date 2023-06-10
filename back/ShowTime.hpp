#ifndef ShowTime_hpp
#define ShowTime_hpp

#include <Wire.h>
#include "State.hpp"
#include "EditHour.hpp"
#include "SleepState.hpp"
#include "ClockShield.hpp"

class ShowTime : public SleepState, private ClockShield
{
public:
  ShowTime(EditHour *&);
  void update(State *&) override;

private:
  bool stateKey;
  uchar delayDownFrequency;
  bool isLowFrequency = true;
  EditHour *&editHour;
  unsigned char pointOn;
  unsigned char pointOff;
  unsigned char countTime = 0;

private:
  void upFrequency();
  void downFrequency();
};

#endif