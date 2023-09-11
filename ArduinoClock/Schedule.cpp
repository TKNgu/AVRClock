#include "Schedule.hpp"

#include "Arduino.h"

Schedule::Schedule()
    : timePointSize(17 * 5 + 12),
      timePoints(new TimePoint[this->timePointSize]) {
  unsigned char index = 0;
  for (unsigned char indexDay = 2; indexDay < 7; indexDay++) {
    this->timePoints[index++] = {indexDay, 7, 30};
    this->timePoints[index++] = {indexDay, 8, 00};
    this->timePoints[index++] = {indexDay, 9, 00};
    this->timePoints[index++] = {indexDay, 9, 15};
    this->timePoints[index++] = {indexDay, 10, 00};
    this->timePoints[index++] = {indexDay, 11, 58};
    this->timePoints[index++] = {indexDay, 12, 30};
    this->timePoints[index++] = {indexDay, 13, 00};
    this->timePoints[index++] = {indexDay, 14, 00};
    this->timePoints[index++] = {indexDay, 14, 30};
    this->timePoints[index++] = {indexDay, 15, 00};
    this->timePoints[index++] = {indexDay, 17, 00};
    this->timePoints[index++] = {indexDay, 17, 30};
    this->timePoints[index++] = {indexDay, 18, 00};
    this->timePoints[index++] = {indexDay, 18, 30};
    this->timePoints[index++] = {indexDay, 18, 45};
    this->timePoints[index++] = {indexDay, 19, 00};
  }
  this->timePoints[index++] = {7, 7, 30};
  this->timePoints[index++] = {7, 8, 00};
  this->timePoints[index++] = {7, 10, 00};
  this->timePoints[index++] = {7, 11, 58};
  this->timePoints[index++] = {7, 13, 00};
  this->timePoints[index++] = {7, 15, 00};
  this->timePoints[index++] = {7, 17, 00};
  this->timePoints[index++] = {7, 17, 30};
  this->timePoints[index++] = {7, 18, 00};
  this->timePoints[index++] = {7, 18, 30};
  this->timePoints[index++] = {7, 18, 45};
  this->timePoints[index++] = {7, 19, 00};
  // Serial.begin(9600);
}

void Schedule::resetTimePoint(const TimePoint &timePoint) {
  for (this->indexTimePoint = 0; this->indexTimePoint < this->timePointSize;
       this->indexTimePoint++) {
    if (timePoint.value < this->timePoints[this->indexTimePoint].value) {
      break;
    }
  }
  this->indexTimePoint %= this->timePointSize;
  this->nextTimePoint = this->timePoints + this->indexTimePoint;
  // Serial.print("Rest");
  // Serial.print((int)(timePoint.dayOfWeek));
  // Serial.print((int)(timePoint.hour));
  // Serial.println((int)(timePoint.minutes));
}

bool Schedule::checkTimePoint(unsigned char dayOfWeek, unsigned char hour,
                              unsigned char minutes) {
  if (minutes == this->nextTimePoint->minutes &&
      hour == this->nextTimePoint->hour &&
      dayOfWeek == this->nextTimePoint->dayOfWeek) {
    this->indexTimePoint = (this->indexTimePoint + 1) % this->timePointSize;
    this->nextTimePoint = this->timePoints + this->indexTimePoint;
    return true;
  }
  return false;
}
