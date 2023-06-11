#include "HourEdit.hpp"

void HourEdit::resume() {
  ValueEdit::resume();
  this->editHour = time.getHour();
}

void HourEdit::on() {
  display.time(this->editHour, time.getMin());
  display.pointOn();
}

void HourEdit::off() {
  unsigned char tmp = time.getMin();
  display.display(0, tmp % 10);
  display.display(1, tmp / 10);
  display.display(2, 0x7f);
  display.display(3, 0x7f);
  display.pointOff();
}
