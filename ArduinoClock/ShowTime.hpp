#ifndef ShowTime_hpp
#define ShowTime_hpp

#include "LowFrequence.hpp"

class ShowTime : public LowFrequence {
public:
 inline ShowTime(State *&nextState) : LowFrequence(nextState) {}

private:
 inline void off() override {
  display.pointOff();
 }

 void on() override;
};

#endif
