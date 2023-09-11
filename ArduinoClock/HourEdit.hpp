#ifndef HourEdit_hpp
#define HourEdit_hpp

#include "ValueEdit.hpp"

class HourEdit final : public ValueEdit {
public:
 inline HourEdit(State *&nextState) : ValueEdit(nextState) {}

private:
 char editHour;

private:
 inline void readState() override { this->editHour = clockShield.getHour(); }
 inline void writeState() override {
  clockShield.setTime(this->editHour, clockShield.getMin(), 0);
 }

 inline void up() override {
  if (++this->editHour > 23) {
   this->editHour = 0;
  }
 }

 inline void down() override {
  if (--this->editHour < 0) {
   this->editHour = 23;
  }
 }

 void on() override;
 void off() override;
};

#endif
