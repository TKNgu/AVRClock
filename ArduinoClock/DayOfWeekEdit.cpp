#include "DayOfWeekEdit.hpp"

void DayOfWeekEdit::resume() {
  unsigned char tmp;
  time.getTime(&tmp, &tmp, &tmp, &this->editDayOfWeek, &tmp, &tmp, &tmp);
}

void DayOfWeekEdit::pause() {
  display.clear();
  unsigned char hour;
  unsigned char min;
  unsigned char sec;
  unsigned char tmp;
  time.getTime(&hour, &min, &sec, &tmp, &tmp, &tmp, &tmp);
  time.setTime(hour, min, sec, this->editDayOfWeek, tmp, tmp, tmp);
}

void DayOfWeekEdit::on() {
  if (this->editDayOfWeek == 1) {
    display.raw(0, 0b00111110);
    display.raw(1, 0b00110111);
    display.raw(2, 0b01101101);
    display.raw(3, 0x00);
  } else {
    display.num(this->editDayOfWeek);
  }
}
