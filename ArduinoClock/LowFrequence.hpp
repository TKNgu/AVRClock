#ifndef LowFrequence_hpp
#define LowFrequence_hpp

#include "State.hpp"

class LowFrequence : public State {
 public:
  LowFrequence(State *&nextState) : State(nextState) {}

 private:
  inline void resume() override {
    setDelayTime(250);
  }
  void input() override;
};

#endif
