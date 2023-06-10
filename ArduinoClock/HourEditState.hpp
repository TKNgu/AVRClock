#ifndef HourEditState_hpp
#define HourEditState_hpp

#include "BlinkState.hpp"
#include "ClockShield.hpp"

class HourEditState : public BlinkState, private ClockShield {
public:
 HourEditState(State *&state, State *&showTimeState)
     : BlinkState(state, 20), tmpHour(time.getHour()), stateUp(false), stateDown(false), showTimeState(showTimeState) {}
 void resume() override;
 void input() override;
 void on() override;
 void off() override;

private:
 uchar tmpHour;
 bool stateMenu;
 bool stateUp;
 bool stateDown;
 State *&showTimeState;
};
#endif
