#ifndef BlinkState_hpp
#define BlinkState_hpp

#include "SleepState.hpp"

class BlinkState : public SleepState
{
public:
    inline BlinkState(unsigned char delayTime = 250) : SleepState(delayTime) {}
    virtual void showOn() = 0;
    virtual void showOff() = 0;
    void update(State *&) override;

public:
    unsigned char countTime = 0;

public:
    unsigned char pointOn;
    unsigned char pointOff;
};

#endif