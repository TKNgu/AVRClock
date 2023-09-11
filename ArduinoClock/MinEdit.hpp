#ifndef MinEdit_hpp
#define MinEdit_hpp

#include "ValueEdit.hpp"

class MinEdit final : public ValueEdit {
public:
 inline MinEdit(State *&nextState) : ValueEdit(nextState){};

private:
 char editMin;

private:
 inline void readState() override { this->editMin = clockShield.getMin(); }
 inline void writeState() override {
  clockShield.setTime(clockShield.getHour(), this->editMin, 0);
 }

 inline void up() override {
  if (++this->editMin > 59) {
   this->editMin = 0;
  }
 }

 inline void down() override {
  if (--this->editMin < 0) {
   this->editMin = 59;
  }
 }

 void on() override;
 void off() override;
};

#endif
