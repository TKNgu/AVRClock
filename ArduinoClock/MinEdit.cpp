#include "MinEdit.hpp"

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
