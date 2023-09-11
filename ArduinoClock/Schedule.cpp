#include "Schedule.hpp"

Schedule::Schedule()
    : schedulesSize(17 * 5 + 12),
      schedules(new Schedule::TimePoint[schedulesSize]) {
  unsigned char index = 0;
  for (unsigned char indexDay = 2; indexDay < 7; indexDay++) {
    this->schedules[index++] = {indexDay, 7, 30};
    this->schedules[index++] = {indexDay, 8, 00};
    this->schedules[index++] = {indexDay, 9, 00};
    this->schedules[index++] = {indexDay, 9, 15};
    this->schedules[index++] = {indexDay, 10, 00};
    this->schedules[index++] = {indexDay, 11, 58};
    this->schedules[index++] = {indexDay, 12, 30};
    this->schedules[index++] = {indexDay, 13, 00};
    this->schedules[index++] = {indexDay, 14, 00};
    this->schedules[index++] = {indexDay, 14, 30};
    this->schedules[index++] = {indexDay, 15, 00};
    this->schedules[index++] = {indexDay, 17, 00};
    this->schedules[index++] = {indexDay, 17, 30};
    this->schedules[index++] = {indexDay, 18, 00};
    this->schedules[index++] = {indexDay, 18, 30};
    this->schedules[index++] = {indexDay, 18, 45};
    this->schedules[index++] = {indexDay, 19, 00};
  }
  this->schedules[index++] = {7, 7, 30};
  this->schedules[index++] = {7, 8, 00};
  this->schedules[index++] = {7, 10, 00};
  this->schedules[index++] = {7, 11, 58};
  this->schedules[index++] = {7, 13, 00};
  this->schedules[index++] = {7, 15, 00};
  this->schedules[index++] = {7, 17, 00};
  this->schedules[index++] = {7, 17, 30};
  this->schedules[index++] = {7, 18, 00};
  this->schedules[index++] = {7, 18, 30};
  this->schedules[index++] = {7, 18, 45};
  this->schedules[index++] = {7, 19, 00};
}

void Schedule::resetPoint(unsigned char dayOfWeek, unsigned char hour,
                          unsigned char minutes) {
  unsigned value = TimePoint::CalculatorValue(dayOfWeek, hour, minutes);
  for (this->indexSchedule = 0; this->indexSchedule < this->schedulesSize;
       this->indexSchedule++) {
    if (value < this->schedules[this->indexSchedule].value) {
      break;
    }
  }
  this->nextSchedule =
      this->schedules + (this->indexSchedule %= this->schedulesSize);
}

bool Schedule::checkPoint(unsigned char dayOfWeek, unsigned char hour,
                          unsigned char minutes) {
  if (this->nextSchedule->value !=
      TimePoint::CalculatorValue(dayOfWeek, hour, minutes)) {
    return false;
  }
  this->nextSchedule =
      this->schedules +
      (this->indexSchedule = ((this->indexSchedule + 1) % this->schedulesSize));
  return true;
}
