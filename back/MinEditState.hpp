#ifndef MinEditState_hpp
#define MinEditState_hpp

#include "BlinkState.hpp"
#include "ClockShield.hpp"

class MinEditState : public BlinkState, private ClockShield {
public:
 MinEditState(State *&state, State *&showTimeState)
     : BlinkState(state, 20), tmpMin(time.getMin()), stateUp(false), stateDown(false), showTimeState(showTimeState) {}
 void resume() override;
 void input() override;
 void on() override;
 void off() override;

private:
 uchar tmpMin;
 bool stateMenu;
 bool stateUp;
 bool stateDown;
 State *&showTimeState;
};
#endif
