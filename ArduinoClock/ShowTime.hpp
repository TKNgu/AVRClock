#ifndef ShowTime_hpp
#define ShowTime_hpp

#include "State.hpp"

class ShowTime : public State {
 public:
  ShowTime(State *&, State *&);
  void resume() override;
  void input() override;
  void off() override;
  void on() override;
};

#endif
