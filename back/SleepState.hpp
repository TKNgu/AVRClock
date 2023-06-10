#ifndef SleepState_hpp
#define SleepState_hpp

#include "State.hpp"

class SleepState : public State
{
public:
    inline SleepState(State *&state, unsigned char delayTime) : State(state), delayTime(delayTime) {}
    void loop(long int) override;
    virtual void update(State *&) = 0;
    inline void setDelayTime(unsigned char delayTime)
    {
        this->delayTime = delayTime;
    }

private:
    unsigned char delayTime;
};

#endif