#ifndef EditHour_hpp
#define EditHour_hpp

#include <Wire.h>
#include "State.hpp"
#include "EditHour.hpp"
#include "SleepState.hpp"
#include "ClockShield.hpp"

class EditHour : public SleepState, private ClockShield
{
public:
  EditHour();
  void update(State *&) override;

private:
  uchar countTime;
  uchar pointOn;
  uchar pointOff;
  bool stateKey;
};

#endif