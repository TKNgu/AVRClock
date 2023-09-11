#include "State.hpp"

#include <math.h>

#define SCHEDULE_LIGHT 30
#define LIGHT A1
#define DELTA_RANGE_LEVEL 80

#define BUZZER_LEVEL 4
#define BUZZER_TIMEOUR 60

#define TIME_POINT 500
#define STATE_LOOP_NONE 0x00
#define STATE_LOOP_ON 0x01
#define STATE_LOOP_OFF 0x02

ClockShield State::clockShield;

State *State::runningState = nullptr;
State *State::defaultState = nullptr;

bool State::stateKey3 = false;
unsigned long State::delayTime = 20;
unsigned long State::pointTime = 0;
bool State::isOn = false;
unsigned char State::stateLoop = STATE_LOOP_NONE;

unsigned long State::buzzeTimeOut = 0;
unsigned long State::lastDelayTime = 0;

bool State::onLed = false;
char State::scheduleLight = SCHEDULE_LIGHT;
int State::maxLevel = 0xff;
int State::minLevel = 0xf0;
int State::rangeLevel = 0xffff;

void State::setDelayTime(unsigned long delayTime) {
  State::delayTime = delayTime;
}

void State::Init(State *initState) {
  State::defaultState = initState;
  SetRunningState(State::defaultState);
}

void State::SetRunningState(State *runningState) {
  State::runningState = runningState;
  State::runningState->resume();
}

void State::input(unsigned long timeNow) {
  if (clockShield.isMenu()) {
    if (!stateKey3) {
      setDelayTime(20);
    }
    stateKey3 = true;
  } else if (stateKey3) {
    tone(BUZZER_DEVICE, 2400, 60);
    stateKey3 = false;
    runningState->pause();
    runningState = this->nextState;
    runningState->resume();
  }
}

void State::update(unsigned long startTime) {
  if (scheduleLight++ > SCHEDULE_LIGHT) {
    scheduleLight = 0;
    updateLight();
  }
  isOn = !isOn;
  isOn ? on() : off();
}

void State::loop() {
  unsigned long timeNow = millis();
  input(timeNow);
  if (pointTime < timeNow) {
    update(timeNow);
    long delta = timeNow - pointTime;
    do {
      pointTime += TIME_POINT;
    } while ((delta -= TIME_POINT) > 0);
  }
  long tmpDelayTime = delayTime + timeNow - millis();
  if (tmpDelayTime > 0) {
    delay(tmpDelayTime);
  }
}

void State::updateLight() {
  int light = analogRead(LIGHT);
  if (light < minLevel) {
    minLevel = light;
    rangeLevel = maxLevel + DELTA_RANGE_LEVEL - minLevel;
  }
  if (light > maxLevel) {
    maxLevel = light;
    rangeLevel = maxLevel + DELTA_RANGE_LEVEL - minLevel;
  }
  int tmp = light - minLevel;
  clockShield.set(char(char((tmp << 3) / rangeLevel)));
}
