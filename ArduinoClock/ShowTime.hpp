#ifndef ShowTime_hpp
#define ShowTime_hpp

#include "LowFrequence.hpp"

class ShowTime final : public LowFrequence {
public:
 inline ShowTime(State *&nextState, State *&temperature) : LowFrequence(nextState), temperature(temperature) {
  buzzeOn();
 }

private:
 void resume() override;
 void input() override;
 inline void off() override { display.pointOff(); }

 void on() override;

private:
 State *&temperature;
 long int timeOutTemperature;
};

#endif
