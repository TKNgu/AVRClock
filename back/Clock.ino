#include "State.hpp"
#include "ShowTime.hpp"
#include "EditHour.hpp"

#define DEBUG
#ifdef DEBUG
#define LOG(value) Serial.println(value)
#else
#define LOG(value)
#endif

ShowTime* showTime;
EditHour* editHour;
State *runningState;

void setup()
{
  Serial.begin(9600);
  showTime = new ShowTime(editHour);
  editHour = new EditHour();
  runningState = showTime;
  LOG(unsigned(showTime));
  LOG(unsigned(editHour));
  LOG(unsigned(runningState));
}

void loop()
{
  runningState->loop(runningState);
}
