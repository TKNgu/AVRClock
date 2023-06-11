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
 static bool onLed;

protected:
 inline State(State *&nextState) : nextState(nextState) {}
 void setDelayTime(unsigned long);
 void buzzeOn(unsigned long);
 void buzzeOff();
 inline virtual void resume() { pointTime = millis(); };

 virtual void loop();
 inline virtual void pause(){};

 virtual void input(unsigned long);
 virtual void update(unsigned long);
 inline virtual void off(){};

 inline virtual void on(){};

private:
 static State *runningState;
 State *&nextState;

 static bool stateKey3;
 static unsigned long delayTime;
 static unsigned long pointTime;
 static bool isOn;
 static unsigned char stateLoop;

 static bool isBuzze;
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
