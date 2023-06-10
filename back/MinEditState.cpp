#include "MinEditState.hpp"

void MinEditState::resume() {
  setDelayTime(20);
  ClockShield::display.time(time.getHour(), time.getMin());
  this->tmpMin = time.getMin();
  this->stateUp = false;
  this->stateDown = false;
}

void MinEditState::input() {
  if (digitalRead(ClockShield::Key::K2) == LOW && !this->stateUp) {
    this->stateUp = true;
    return;
  }
  if (digitalRead(ClockShield::Key::K2) == HIGH && this->stateUp) {
    this->stateUp = false;
    this->tmpMin++;
    if (this->tmpMin > 59) {
      this->tmpMin = 0;
    }
    return;
  }
  if (digitalRead(ClockShield::Key::K1) == LOW && !this->stateDown) {
    this->stateDown = true;
    return;
  }
  if (digitalRead(ClockShield::Key::K1) == HIGH && this->stateDown) {
    this->stateDown = false;
    if (!this->tmpMin) {
      this->tmpMin = 60;
    }
    this->tmpMin--;
    return;
  }
  if (digitalRead(ClockShield::Key::K3) == LOW && !this->stateMenu) {
    this->stateMenu = true;
    return;
  }
  if (digitalRead(ClockShield::Key::K3) == HIGH && this->stateMenu) {
    this->stateMenu = false;
    time.setTime(time.getHour(), this->tmpMin, time.getSec());
    changState(this->showTimeState);
    return;
  }
}

void MinEditState::on() {
  ClockShield::display.pointOn();
  ClockShield::display.time(time.getHour(), this->tmpMin);
}
void MinEditState::off() {
  ClockShield::display.pointOff();
  auto tmp = time.getHour();
  ClockShield::display.display(0, 0x7f);
  ClockShield::display.display(1, 0x7f);
  ClockShield::display.display(2, tmp % 10);
  ClockShield::display.display(3, tmp / 10);
}
