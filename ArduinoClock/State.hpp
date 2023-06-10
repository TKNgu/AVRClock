#ifndef State_hpp
#define State_hpp

#include "Arduino.h"
#include "TTSDisplay.h"
#include "TTSTime.h"

class State {
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
 State(State *&runningState, State *&nextState) : runningState(runningState), nextState(nextState) {}
 inline setDelayTime(long int delayTime) {
  this->delayTime = delayTime;
 }
 virtual void resume();
 virtual void loop();
 virtual void pause(){};

 virtual void input();
 virtual void off() = 0;
 virtual void on() = 0;

protected:
 TTSDisplay display;
 TTSTime time;

private:
 State *&runningState;
 State *&nextState;

 bool stateKey3;
 long int delayTime;
 long int runTime;
};

#endif
