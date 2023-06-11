#ifndef DayOfWeekEdit_hpp
#define DayOfWeekEdit_hpp

#include "ValueEdit.hpp"

class DayOfWeekEdit : public ValueEdit {
public:
 inline DayOfWeekEdit(State *&nextState) : ValueEdit(nextState) {}

private:
 char editDayOfWeek;

private:
 void resume() override;
 void pause() override;

 inline void up() override {
  if (++this->editDayOfWeek > 7) {
   this->editDayOfWeek = 1;
  }
 }

 inline void down() override {
  if (--this->editDayOfWeek < 1) {
   this->editDayOfWeek = 7;
  }
 }

 void on() override;
 inline void off() override { display.clear(); }
};

#endif
