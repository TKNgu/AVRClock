#ifndef HourEdit_hpp
#define HourEdit_hpp

#include "ValueEdit.hpp"

class HourEdit : public ValueEdit {
 public:
  HourEdit(State *&runningState, State *&nextState) : ValueEdit(runningState, nextState) {}
  void resume() override;
  void pause() override;

  void up() override;
  void down() override;
  void on() override;
  void off() override;

 private:
  char editHour;
};

#endif
