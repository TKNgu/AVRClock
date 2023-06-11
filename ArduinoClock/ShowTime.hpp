#ifndef ShowTime_hpp
#define ShowTime_hpp

#include "State.hpp"

class ShowTime final : public State {
public:
 ShowTime(State *&);
 inline ~ShowTime() { delete[] this->schedules; }

private:
 struct Schedule {
  unsigned char dayOfWeek;
  unsigned char hour;
  unsigned char min;
  unsigned value;
 };

private:
 unsigned long timeOutCheckTemp;
 unsigned long timeOutShowTemp;
 int temperature;

 unsigned char hour;
 unsigned char min;
 unsigned char sec;
 unsigned char dayOfWeek;
 unsigned char tmp;

 Schedule *nextSchedule;
 unsigned char indexSchedule;
 Schedule *schedules;
 const unsigned char schedulesSize;

private:
 void resume() override;
 void update(unsigned long) override;
 inline void off() override { display.pointOff(); }
 inline void on() override {
  if (onLed) {
   display.pointOn();
  }
 }
 void showTemperature();
};

#endif
