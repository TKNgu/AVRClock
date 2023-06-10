#include "MinEdit.hpp"

void MinEdit::resume() {
  ValueEdit::resume();
  this->editMin = time.getMin();
}

void MinEdit::pause() {
  time.setTime(time.getHour(), this->editMin, time.getSec());
}

void MinEdit::up() {
  this->editMin = ++this->editMin > 59 ? 0 : this->editMin;
}

void MinEdit::down() {
  this->editMin = --this->editMin < 0 ? 59 : this->editMin;
}

void MinEdit::on() {
  display.time(time.getHour(), this->editMin);
  display.pointOn();
}

void MinEdit::off() {
  auto tmp = time.getHour();
  display.display(0, 0x7f);
  display.display(1, 0x7f);
  display.display(2, tmp % 10);
  display.display(3, tmp / 10);
  display.pointOff();
}
