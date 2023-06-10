#ifndef BlinkState_hpp
#define BlinkState_hpp

#include "InputState.hpp"

class BlinkState : public InputState {
public:
 inline BlinkState(State *&state, long int delayTime = 500)
     : InputState(state, delayTime), isStateOn(true), startTime(0), runTime(0) {}
 void update() override;
 virtual void on() = 0;
 virtual void off() = 0;

private:
 bool isStateOn;
 long int startTime;
 long int runTime;
};

#endif
