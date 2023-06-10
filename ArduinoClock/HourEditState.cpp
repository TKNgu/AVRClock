#include "HourEditState.hpp"

void HourEditState::resume() {
  setDelayTime(20);
  ClockShield::display.time(time.getHour(), time.getMin());
  this->tmpHour = time.getHour();
  this->stateUp = false;
  this->stateDown = false;
}

void HourEditState::input() {
  if (digitalRead(ClockShield::Key::K2) == LOW && !this->stateUp) {
    this->stateUp = true;
    return;
  }
  if (digitalRead(ClockShield::Key::K2) == HIGH && this->stateUp) {
    this->stateUp = false;
    this->tmpHour++;
    if (this->tmpHour > 23) {
      this->tmpHour = 0;
    }
    return;
  }
  if (digitalRead(ClockShield::Key::K1) == LOW && !this->stateDown) {
    this->stateDown = true;
    return;
  }
  if (digitalRead(ClockShield::Key::K1) == HIGH && this->stateDown) {
    this->stateDown = false;
    if (!this->tmpHour) {
      this->tmpHour = 24;
    }
    this->tmpHour--;
    return;
  }
  if (digitalRead(ClockShield::Key::K3) == LOW && !this->stateMenu) {
    this->stateMenu = true;
    return;
  }
  if (digitalRead(ClockShield::Key::K3) == HIGH && this->stateMenu) {
    this->stateMenu = false;
    time.setTime(this->tmpHour, time.getMin(), time.getSec());
    changState(this->showTimeState);
    return;
  }
}

void HourEditState::on() {
  ClockShield::display.pointOn();
  ClockShield::display.time(this->tmpHour, time.getMin());
}
void HourEditState::off() {
  ClockShield::display.pointOff();
  auto tmp = time.getMin();
  ClockShield::display.display(0, tmp % 10);
  ClockShield::display.display(1, tmp / 10);
  ClockShield::display.display(2, 0x7f);
  ClockShield::display.display(3, 0x7f);
}
