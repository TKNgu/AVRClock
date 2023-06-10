#ifndef State_hpp
#define State_hpp

#include "Arduino.h"
#include "TTSDisplay.h"
#include "TTSTemp.h"
#include "TTSTime.h"

class State {
public:
 static void SetRunningState(State *);
 inline static void RunningStateLoop() {
  State::runningState->loop();
 }

protected:
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

protected:
 inline State(State *&nextState) : nextState(nextState) {}
 inline setDelayTime(long int delayTime) {
  State::delayTime = delayTime;
 }
 inline virtual void resume() {
  runTime = millis();
 };
 virtual void loop();
 inline virtual void pause(){};

 virtual void input();
 virtual void update(long int);
 inline virtual void off(){};
 inline virtual void on(){};

protected:
 static TTSDisplay display;
 static TTSTime time;
 static TTSTemp temp;

private:
 static State *runningState;
 State *&nextState;

 static bool stateKey3;
 static long int delayTime;
 static long int runTime;
};

#endif
