#include "ShowTime.hpp"

void ShowTime::input() {
  State::input();
  if (digitalRead(State::Key::K3) == LOW) {
    setDelayTime(20);
  }
}

void ShowTime::on() {
  display.time(time.getHour(), time.getMin());
  display.pointOn();
}
