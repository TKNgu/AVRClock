#include "HourEdit.hpp"

void HourEdit::resume() {
  ValueEdit::resume();
  this->editHour = time.getHour();
}

void HourEdit::pause() {
  time.setTime(this->editHour, time.getMin(), time.getSec());
}

void HourEdit::up() {
  this->editHour = ++this->editHour > 23 ? 0 : this->editHour;
}

void HourEdit::down() {
  this->editHour = --this->editHour < 0 ? 23 : this->editHour;
}

void HourEdit::on() {
  display.time(this->editHour, time.getMin());
  display.pointOn();
}

void HourEdit::off() {
  display.pointOff();
  auto tmp = time.getMin();
  display.display(0, tmp % 10);
  display.display(1, tmp / 10);
  display.display(2, 0x7f);
  display.display(3, 0x7f);
}
