#ifndef ShowTime_hpp
#define ShowTime_hpp

#include "State.hpp"

class ShowTime : public State {
public:
 inline ShowTime(State *&nextState) : State(nextState) {}

private:
 inline void resume() override {
  setDelayTime(250);
 }

 void input() override;
 inline void off() override {
  display.pointOff();
 }

 void on() override;
};

#endif
