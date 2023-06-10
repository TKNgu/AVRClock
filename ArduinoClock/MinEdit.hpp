#ifndef MinEdit_hpp
#define MinEdit_hpp

#include "ValueEdit.hpp"

class MinEdit : public ValueEdit {
 public:
  MinEdit(State *&runningState, State *&nextState) : ValueEdit(runningState, nextState){};
  void resume() override;
  void pause() override;

  void up() override;
  void down() override;
  void on() override;
  void off() override;

 private:
  char editMin;
};

#endif
