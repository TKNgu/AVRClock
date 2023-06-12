#include "State.hpp"

#define BUZZER 6
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

void State::Init() {
  pinMode(Key::K1, INPUT_PULLUP);
  pinMode(Key::K2, INPUT_PULLUP);
  pinMode(Key::K3, INPUT_PULLUP);

  pinMode(Led::LED1, OUTPUT);
  pinMode(Led::LED2, OUTPUT);
  pinMode(Led::LED3, OUTPUT);
  pinMode(Led::LED4, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
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
  }
}

void State::update(long int startTime) {
  auto delta = startTime - runTime;
  if (delta > ON_TIME_POINT) {
    Serial.println("On");
    on();
    runTime += ON_TIME_POINT;
  } else if (delta > OFF_TIME_POINT) {
    Serial.println("Off");
    off();
  }
}

void State::loop() {
  Serial.println("Loop");
  auto startTime = millis();
  Serial.println(startTime);
  Serial.println("Input");
  input();
  Serial.println("Update");
  update(startTime);
  auto tmpDelayTime = delayTime - millis() + startTime;
  Serial.println("Delay");
  if (tmpDelayTime > 0) {
    delay(tmpDelayTime);
  }
}
