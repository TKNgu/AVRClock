#include "State.hpp"

#include <math.h>

#define SCHEDULE_LIGHT 30
#define LIGHT A1
#define DELTA_RANGE_LEVEL 80

#define BUZZER_DEVICE 6
#define BUZZER_LEVEL 4
#define BUZZER_TIMEOUR 60

#define TIME_POINT 500
#define STATE_LOOP_NONE 0x00
#define STATE_LOOP_ON 0x01
#define STATE_LOOP_OFF 0x02

TTSDisplay State::display;
TTSTime State::time;
TTSTemp State::temp;

State *State::runningState = nullptr;

bool State::stateKey3 = false;
unsigned long State::delayTime = 20;
unsigned long State::pointTime = 0;
bool State::isOn = false;
unsigned char State::stateLoop = STATE_LOOP_NONE;

bool State::isBuzze = false;
unsigned long State::buzzeTimeOut = 0;
unsigned long State::lastDelayTime = 0;

bool State::onLed = false;
char State::scheduleLight = SCHEDULE_LIGHT;
int State::maxLevel = 0xff;
int State::minLevel = 0xf0;
int State::rangeLevel = 0xffff;

void State::Init() {
  pinMode(Key::K1, INPUT_PULLUP);
  pinMode(Key::K2, INPUT_PULLUP);
  pinMode(Key::K3, INPUT_PULLUP);

  pinMode(Led::LED1, OUTPUT);
  pinMode(Led::LED2, OUTPUT);
  pinMode(Led::LED3, OUTPUT);
  pinMode(Led::LED4, OUTPUT);

  pinMode(BUZZER_DEVICE, OUTPUT);

  display.clear();

  Serial.begin(9600)
}

void State::setDelayTime(unsigned long delayTime) {
  if (isBuzze) {
    lastDelayTime = delayTime;
  } else {
    State::delayTime = delayTime;
  }
}

void State::buzzeOn(unsigned long timeNow) {
  if (!isBuzze && buzzeTimeOut < timeNow + 1000) {
    isBuzze = true;
    lastDelayTime = delayTime;
    delayTime = 20;
    buzzeTimeOut = timeNow + BUZZER_TIMEOUR;
    analogWrite(BUZZER_DEVICE, BUZZER_LEVEL);
  }
}

void State::buzzeOff() {
  digitalWrite(BUZZER_DEVICE, LOW);
  delayTime = lastDelayTime;
  this->isBuzze = false;
}

void State::SetRunningState(State *runningState) {
  State::runningState = runningState;
  State::runningState->resume();
}

void State::input(unsigned long timeNow) {
  Serial.println("Input");
  if (buzzeTimeOut < timeNow && isBuzze) {
    buzzeOff();
  }
  if (digitalRead(Key::K3) == LOW) {
    if (!stateKey3) {
      setDelayTime(20);
    }
    stateKey3 = true;
  } else if (stateKey3) {
    stateKey3 = false;
    runningState->pause();
    runningState = this->nextState;
    runningState->resume();
  }
}

void State::update(unsigned long startTime) {
  Serial.println("Update");
  if (scheduleLight++ > SCHEDULE_LIGHT) {
    scheduleLight = 0;
    updateLight();
  }
  isOn = !isOn;
  isOn ? on() : off();
}

void State::loop() {
  Serial.println("**********************************");
  Serial.println("Loop");
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
  Serial.println("Delay");
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
  display.set(char(char((tmp << 3) / rangeLevel)));
}
