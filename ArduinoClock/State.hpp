#ifndef State_hpp
#define State_hpp

#include "Arduino.h"
#include "ClockShield.hpp"

class State {
public:
 static void Init(State *);
 static void SetRunningState(State *);
 static void Changdefault();
 inline static void RunningStateLoop() { State::runningState->loop(); }

protected:
 static bool onLed;
 static ClockShield clockShield;
 static unsigned long pointTime;

protected:
 inline State(State *&nextState) : nextState(nextState) {}
 inline changDefault() { SetRunningState(State::defaultState); }
 void setDelayTime(unsigned long);
 inline virtual void resume() { pointTime = millis(); };

 virtual void loop();
 inline virtual void pause(){};

 virtual void input(unsigned long);
 virtual void update(unsigned long);
 inline virtual void off(){};

 inline virtual void on(){};

private:
 static State *runningState;
 static State *defaultState;
 State *&nextState;

 static bool stateKey3;
 static unsigned long delayTime;
 static bool isOn;
 static unsigned char stateLoop;

 static unsigned long buzzeTimeOut;
 static unsigned long lastDelayTime;

 static char scheduleLight;
 static int maxLevel;
 static int minLevel;
 static int rangeLevel;

private:
 void updateLight();
};

#endif
