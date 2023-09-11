#include "HourEdit.hpp"

void HourEdit::on() {
  clockShield.showTime(this->editHour, clockShield.getMin());
  clockShield.pointOn();
}

void HourEdit::off() {
  unsigned char tmp = clockShield.getMin();
  clockShield.show(0, tmp % 10);
  clockShield.show(1, tmp / 10);
  clockShield.show(2, 0x7f);
  clockShield.show(3, 0x7f);
  clockShield.pointOff();
}
