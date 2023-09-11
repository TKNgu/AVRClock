#include "DayOfWeekEdit.hpp"

void DayOfWeekEdit::readState() {
  unsigned char tmp;
  clockShield.getTime(&tmp, &tmp, &tmp, &this->editDayOfWeek, &tmp, &tmp, &tmp);
}

void DayOfWeekEdit::writeState() {
  clockShield.clear();
  unsigned char hour;
  unsigned char min;
  unsigned char sec;
  unsigned char tmp;
  clockShield.getTime(&hour, &min, &sec, &tmp, &tmp, &tmp, &tmp);
  clockShield.setTime(hour, min, sec, this->editDayOfWeek, tmp, tmp, tmp);
}

void DayOfWeekEdit::on() {
  if (this->editDayOfWeek == 1) {
    clockShield.raw(0, 0b00110111);
    clockShield.raw(1, 0b00111110);
    clockShield.raw(2, 0b01101101);
    clockShield.raw(3, 0x00);
  } else {
    clockShield.num(this->editDayOfWeek);
  }
}
