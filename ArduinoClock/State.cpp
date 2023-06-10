#include "State.hpp"

#include <math.h>

#define SCHEDULE_LIGHT 60
#define LIGHT A1
#define DELTA_RANGE_LEVEL 80

#define BUZZER 6
#define BUZZER_LEVEL 4
#define BUZZER_TIMEOUR 45
#define BUZZER_DELAY 15

#define DEFAULT_DELAY 20
#define ON_TIME_POINT 1000
#define OFF_TIME_POINT 500

TTSDisplay State::display;
TTSTime State::time;
TTSTemp State::temp;

State *State::runningState = nullptr;

bool State::stateKey3 = false;
long int State::delayTime = DEFAULT_DELAY;
long int State::runTime = millis();

bool State::isBuzze = false;
long int State::buzzeTimeOut = 0;
long int State::lastDelayTime = 0;

unsigned char State::scheduleLight = SCHEDULE_LIGHT;
unsigned State::maxLevel = 0x0000;
unsigned State::minLevel = 0xffff;
unsigned State::rangeLevel = 0xffff;

void State::buzzeOn() {
  if (!this->isBuzze && buzzeTimeOut < millis() + 1000) {
    this->isBuzze = true;
    lastDelayTime = delayTime;
    delayTime = BUZZER_DELAY;
    buzzeTimeOut = millis() + BUZZER_TIMEOUR;
    analogWrite(BUZZER, BUZZER_LEVEL);
  }
}

void State::buzzeOff() {
  digitalWrite(BUZZER, LOW);
  delayTime = lastDelayTime;
  this->isBuzze = false;
}

void State::Init() {
  pinMode(Key::K1, INPUT_PULLUP);
  pinMode(Key::K2, INPUT_PULLUP);
  pinMode(Key::K3, INPUT_PULLUP);

  pinMode(Led::LED1, OUTPUT);
  pinMode(Led::LED2, OUTPUT);
  pinMode(Led::LED3, OUTPUT);
  pinMode(Led::LED4, OUTPUT);

  pinMode(BUZZER, OUTPUT);
}

void State::SetRunningState(State *runningState) {
  State::runningState = runningState;
  State::runningState->resume();
}

void State::input() {
  if (digitalRead(Key::K3) == LOW) {
    stateKey3 = true;
  } else if (stateKey3) {
    stateKey3 = false;
    runningState->pause();
    runningState = this->nextState;
    runningState->resume();
    buzzeOn();
  }
}

void State::update(long int startTime) {
  auto delta = startTime - runTime;
  if (delta > ON_TIME_POINT) {
    on();
    runTime += ON_TIME_POINT;
  } else if (delta > OFF_TIME_POINT) {
    off();
  }
}

void State::loop() {
  auto startTime = millis();
  if (buzzeTimeOut < startTime) {
    buzzeOff();
  }
  if (scheduleLight++ > SCHEDULE_LIGHT) {
    scheduleLight = 0;
    updateLight();
  }
  input();
  update(startTime);
  auto tmpDelayTime = delayTime - millis() + startTime;
  if (tmpDelayTime > 0) {
    delay(tmpDelayTime);
  }
}

void State::updateLight() {
  auto light = analogRead(LIGHT);
  if (light > maxLevel) {
    maxLevel = light;
    rangeLevel = maxLevel - minLevel + DELTA_RANGE_LEVEL;
  }
  if (light < minLevel) {
    minLevel = light;
    rangeLevel = maxLevel - minLevel + DELTA_RANGE_LEVEL;
  }
  auto tmp = light - minLevel;
  display.set(char(char((tmp << 3) / rangeLevel)));
}
