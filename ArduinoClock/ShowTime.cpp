#include "ShowTime.hpp"

#define HIGH_TEMP 31
#define LOW_TEMP 17
#define TIMEOUT_SHOW_TEMP 5000

void ShowTime::resume() {
  LowFrequence::resume();
  this->timeOutTemperature = millis() + TIMEOUT_SHOW_TEMP;
}

void ShowTime::input() {
  LowFrequence::input();
  auto temperature = temp.get();
  if ((temperature > HIGH_TEMP || temperature < LOW_TEMP) && millis() > this->timeOutTemperature) {
    State::SetRunningState(this->temperature);
  }
}

void ShowTime::on() {
  display.time(time.getHour(), time.getMin());
  display.pointOn();
}
