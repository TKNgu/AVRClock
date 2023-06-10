#include "Temperature.hpp"

#define TIME_OUT_SHOW 3000

void Temperature::resume() {
  LowFrequence::resume();
  this->timeOut = millis() + TIME_OUT_SHOW;
}

void Temperature::update(long int realTime) {
  if (realTime < this->timeOut) {
    auto temperature = temp.get();
    display.raw(0, 0b00111001);
    display.raw(1, 0b01100011);
    display.display(2, temperature % 10);
    display.display(3, temperature / 10);
  } else {
    State::SetRunningState(this->showTime);
  }
}
