#ifndef ShowTime_hpp
#define ShowTime_hpp

#include "Schedule.hpp"
#include "State.hpp"

class ShowTime final : public State {
public:
 ShowTime(State *&);
 inline ~ShowTime() { delete[] this->schedule.schedules; }

private:
private:
 unsigned long timeOutCheckTemp;
 unsigned long timeOutShowTemp;
 int temperature;

 unsigned char hour;
 unsigned char minutes;
 unsigned char sec;
 unsigned char dayOfWeek;
 unsigned char tmp;

 Schedule schedule;

private:
 void resume() override;
 void update(unsigned long) override;
 inline void off() override { clockShield.pointOff(); }
 inline void on() override {
  if (onLed) {
   clockShield.pointOn();
  }
 }
 void showTemperature();
};

#endif
