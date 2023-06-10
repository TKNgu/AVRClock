#include "State.hpp"

TTSDisplay State::display;
TTSTime State::time;

State *State::runningState = nullptr;

bool State::stateKey3 = false;
long int State::delayTime = 20;
long int State::runTime = millis();

void State::SetRunningState(State *runningState) {
  pinMode(Key::K1, INPUT_PULLUP);
  pinMode(Key::K2, INPUT_PULLUP);
  pinMode(Key::K3, INPUT_PULLUP);

  pinMode(Led::LED1, OUTPUT);
  pinMode(Led::LED2, OUTPUT);
  pinMode(Led::LED3, OUTPUT);
  pinMode(Led::LED4, OUTPUT);

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

void State::loop() {
  auto startTime = millis();
  auto delta = startTime - runTime;
  input();
  if (delta > 1000) {
    on();
    runTime += 1000;
  } else if (delta > 500) {
    off();
  }
  auto tmpDelayTime = delayTime - millis() + startTime;
  if (tmpDelayTime > 0) {
    delay(tmpDelayTime);
  }
}
