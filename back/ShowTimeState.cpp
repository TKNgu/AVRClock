#include "ShowTimeState.hpp"

void ShowTimeState::resume() {
  ClockShield::display.time(time.getHour(), time.getMin());
  setDelayTime(250);
};

void ShowTimeState::input() {
  if (digitalRead(ClockShield::Key::K3) == LOW && !this->menuState) {
    setDelayTime(20);
    this->menuState = true;
    digitalWrite(ClockShield::Led::LED4, HIGH);
  }
  if (digitalRead(ClockShield::Key::K3) == HIGH && this->menuState) {
    this->menuState = false;
    changState(this->hoursEditState);
    digitalWrite(ClockShield::Led::LED4, LOW);
  }
}

void ShowTimeState::on() {
  ClockShield::display.time(time.getHour(), time.getMin());
  ClockShield::display.pointOn();
}

void ShowTimeState::off() { display.pointOff(); }
