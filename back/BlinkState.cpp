#include "BlinkState.hpp"

#include "Arduino.h"
#include "limits.h"

void BlinkState::update() {
  long int timeNow = millis();
  this->runTime += (timeNow - this->startTime);
  if (this->startTime > timeNow) {
    this->runTime += LONG_MAX;
  } else {
    this->runTime += LONG_MAX - this->startTime + timeNow;
  }
  this->startTime = timeNow;
  if (this->runTime > 1000) {
    this->runTime -= 1000;
    on();
    return;
  }
  if (this->runTime > 500) {
    off();
    return;
  }
}
