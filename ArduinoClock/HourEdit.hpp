#ifndef HourEdit_hpp
#define HourEdit_hpp

#include "ValueEdit.hpp"

class HourEdit : public ValueEdit {
public:
 inline HourEdit(State *&nextState) : ValueEdit(nextState) {}

private:
 void resume() override;
 inline void pause() override {
  time.setTime(this->editHour, time.getMin(), time.getSec());
 }

 inline void up() {
  if (++this->editHour > 23) {
   this->editHour = 0;
  }
 }

 inline void down() {
  if (--this->editHour < 0) {
   this->editHour = 23;
  }
 }

 void on() override;
 void off() override;

private:
 char editHour;
};

#endif
