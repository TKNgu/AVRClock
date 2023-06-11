#include "ShowTime.hpp"

ShowTime::ShowTime::ShowTime(State *&nextState)
    : State(nextState), schedulesSize(17 * 5 + 12), timeOutCheckTemp(0), timeOutShowTemp(0) {
  this->schedules = new Schedule[this->schedulesSize];
  unsigned char index = 0;
  for (unsigned char indexDay = 2; indexDay < 7; indexDay++) {
    this->schedules[index++] = {indexDay, 7, 30, 0};
    this->schedules[index++] = {indexDay, 8, 00, 0};
    this->schedules[index++] = {indexDay, 9, 00, 0};
    this->schedules[index++] = {indexDay, 9, 15, 0};
    this->schedules[index++] = {indexDay, 10, 00, 0};
    this->schedules[index++] = {indexDay, 11, 58, 0};
    this->schedules[index++] = {indexDay, 12, 30, 0};
    this->schedules[index++] = {indexDay, 13, 00, 0};
    this->schedules[index++] = {indexDay, 14, 00, 0};
    this->schedules[index++] = {indexDay, 14, 30, 0};
    this->schedules[index++] = {indexDay, 15, 00, 0};
    this->schedules[index++] = {indexDay, 17, 00, 0};
    this->schedules[index++] = {indexDay, 17, 30, 0};
    this->schedules[index++] = {indexDay, 18, 00, 0};
    this->schedules[index++] = {indexDay, 18, 30, 0};
    this->schedules[index++] = {indexDay, 18, 45, 0};
    this->schedules[index++] = {indexDay, 19, 00, 0};
  }
  this->schedules[index++] = {7, 7, 30, 0};
  this->schedules[index++] = {7, 8, 00, 0};
  this->schedules[index++] = {7, 10, 00, 0};
  this->schedules[index++] = {7, 11, 58, 0};
  this->schedules[index++] = {7, 13, 00, 0};
  this->schedules[index++] = {7, 15, 00, 0};
  this->schedules[index++] = {7, 17, 00, 0};
  this->schedules[index++] = {7, 17, 30, 0};
  this->schedules[index++] = {7, 18, 00, 0};
  this->schedules[index++] = {7, 18, 30, 0};
  this->schedules[index++] = {7, 18, 45, 0};
  this->schedules[index++] = {7, 19, 00, 0};
  for (index = 0; index < this->schedulesSize; index++) {
    this->nextSchedule = this->schedules + index;
    this->nextSchedule->value =
        (this->nextSchedule->dayOfWeek << 11) + (this->nextSchedule->hour << 6) + this->nextSchedule->min;
  }
  buzzeOn(millis());
}

void ShowTime::resume() {
  time.getTime(&this->hour, &this->min, &this->tmp, &this->dayOfWeek, &this->tmp, &this->tmp, &this->tmp);
  unsigned value = (this->dayOfWeek << 11) + (this->hour << 6) + this->min;
  for (this->indexSchedule = 0; this->indexSchedule < this->schedulesSize; this->indexSchedule++) {
    if (value < this->schedules[this->indexSchedule].value) {
      break;
    }
  }
  this->indexSchedule %= this->schedulesSize;
  this->nextSchedule = this->schedules + this->indexSchedule;
  setDelayTime(250);
}

void ShowTime::update(unsigned long timeNow) {
  time.getTime(&this->hour, &this->min, &this->sec, &this->dayOfWeek, &this->tmp, &this->tmp, &this->tmp);
  if (!(onLed = this->hour < 22 && this->hour >= 5)) {
    display.clear();
    display.pointOff();
    return;
  }
  this->temperature = temp.get();
  if ((this->temperature > 31 || this->temperature < 15) && timeNow > this->timeOutCheckTemp) {
    this->timeOutShowTemp = timeNow + 3000;
    this->timeOutCheckTemp = timeNow + 10000;
  }
  if (timeNow < this->timeOutShowTemp) {
    showTemperature();
  } else {
    display.time(this->hour, this->min);
    State::update(timeNow);
  }
  if (!this->sec && this->min == this->nextSchedule->min && this->hour == this->nextSchedule->hour &&
      this->dayOfWeek == this->nextSchedule->dayOfWeek) {
    this->indexSchedule++;
    this->indexSchedule %= this->schedulesSize;
    this->nextSchedule = this->schedules + this->indexSchedule;
    buzzeOn(timeNow);
  }
}

void ShowTime::showTemperature() {
  display.raw(0, 0b00111001);
  display.raw(1, 0b01100011);
  display.display(2, this->temperature % 10);
  display.display(3, this->temperature / 10);
}
