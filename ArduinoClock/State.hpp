#ifndef State_hpp
#define State_hpp

#include "Arduino.h"
#include "TTSDisplay.h"
#include "TTSTemp.h"
#include "TTSTime.h"

class State {
public:
 static void Init();
 static void SetRunningState(State *);
 inline static void RunningStateLoop() { State::runningState->loop(); }

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
 static TTSDisplay display;
 static TTSTime time;
 static TTSTemp temp;

protected:
 inline State(State *&nextState) : nextState(nextState) {}

 inline void setDelayTime(long int delayTime) { State::delayTime = delayTime; }

 void buzzeOn();
 void buzzeOff();
 inline virtual void resume() { runTime = millis(); };

 virtual void loop();
 inline virtual void pause(){};

 virtual void input();
 virtual void update(long int);
 inline virtual void off(){};

 inline virtual void on(){};

private:
 static State *runningState;
 State *&nextState;

 static bool stateKey3;
 static long int delayTime;
 static long int runTime;

 static bool isBuzze;
 static long int buzzeTimeOut;
 static long int lastDelayTime;

 static unsigned char scheduleLight;
 static unsigned maxLevel;
 static unsigned minLevel;
 static unsigned rangeLevel;

private:
 void updateLight();
};

#endif
