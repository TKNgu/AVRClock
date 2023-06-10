#ifndef ShowTimeState_hpp
#define ShowTimeState_hpp

#include "BlinkState.hpp"
#include "ClockShield.hpp"

class ShowTimeState : public BlinkState, private ClockShield {
public:
 inline ShowTimeState(State *&state, State *&hoursEditState)
     : BlinkState(state, 250), menuState(false), hoursEditState(hoursEditState){};
 inline void resume() override;
 void input() override;
 void on() override;
 void off() override;

private:
 bool menuState;
 State *&hoursEditState;
};

#endif
