#include "ShowTime.hpp"

ShowTime::ShowTime::ShowTime(State *&nextState)
    : State(nextState), timeOutCheckTemp(0), timeOutShowTemp(0) {
  BUZZER
}

void ShowTime::resume() {
  clockShield.getTime(&this->hour, &this->minutes, &this->tmp, &this->dayOfWeek,
                      &this->tmp, &this->tmp, &this->tmp);
  this->schedule.resetPoint(this->dayOfWeek, this->hour, this->minutes);
  setDelayTime(250);
}

void ShowTime::update(unsigned long timeNow) {
  clockShield.getTime(&this->hour, &this->minutes, &this->sec, &this->dayOfWeek,
                      &this->tmp, &this->tmp, &this->tmp);
  if (!(onLed = this->hour < 23 && this->hour >= 5)) {
    clockShield.clear();
    clockShield.pointOff();
    return;
  }
  this->temperature = clockShield.getTem();
  if ((this->temperature > 31 || this->temperature < 15) &&
      timeNow > this->timeOutCheckTemp) {
    this->timeOutShowTemp = timeNow + 3000;
    this->timeOutCheckTemp = timeNow + 10000;
  }
  if (timeNow < this->timeOutShowTemp) {
    showTemperature();
  } else {
    clockShield.showTime(this->hour, this->minutes);
    State::update(timeNow);
  }
  if (!this->sec &&
      this->schedule.checkPoint(this->dayOfWeek, this->hour, this->minutes)) {
    BUZZER
  }
}

void ShowTime::showTemperature() {
  clockShield.raw(0, 0b00111001);
  clockShield.raw(1, 0b01100011);
  clockShield.raw(2, this->temperature % 10);
  clockShield.raw(3, this->temperature / 10);
}
