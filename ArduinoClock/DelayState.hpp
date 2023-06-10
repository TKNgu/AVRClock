#ifndef SleepState_hpp
#define SleepState_hpp

#include "State.hpp"

class DelayState : public State {
public:
 inline DelayState(State *&state, long int delayTime = 100) : State(state), delayTime(delayTime) {}
 void loop() override;
 virtual void update() = 0;
 inline void setDelayTime(long int delayTime) { this->delayTime = delayTime; }

private:
 long int delayTime;
};

#endif

