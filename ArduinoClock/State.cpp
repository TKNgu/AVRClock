#include "State.hpp"

void State::resume() {
  this->stateKey3 = false;
  this->runTime = millis();
  this->delayTime = 20;
};

void State::input() {
  if (digitalRead(Key::K3) == LOW) {
    this->stateKey3 = true;
  } else if (this->stateKey3) {
    this->runningState->pause();
    this->runningState = this->nextState;
    this->runningState->resume();
  }
}

void State::loop() {
  input();
  auto delta = millis() - this->runTime;
  if (delta > 1000) {
    off();
    this->runTime += 1000;
  } else if (delta > 500) {
    on();
  }
  delay(this->delayTime);
}
