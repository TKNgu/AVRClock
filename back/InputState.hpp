#ifndef InputState_hpp
#define InputState_hpp

#include "DelayState.hpp"

class InputState : public DelayState {
 public:
  InputState(State *&state, long int delayTime) : DelayState(state, delayTime){};
  virtual void input() {}
  void loop() override {
    input();
    DelayState::loop();
  };
};

#endif
