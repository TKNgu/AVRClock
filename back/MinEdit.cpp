#include "MinEdit.hpp"

void MinEdit::on() {
  clockShield.showTime(clockShield.getHour(), this->editMin);
  clockShield.pointOn();
}

void MinEdit::off() {
  unsigned char tmp = clockShield.getHour();
  clockShield.show(0, 0x7f);
  clockShield.show(1, 0x7f);
  clockShield.show(2, tmp % 10);
  clockShield.show(3, tmp / 10);
  clockShield.pointOff();
}
