#ifndef SAMPLESTATE_HPP
#define SAMPLESTATE_HPP

#include "StateManager2.hpp"

struct SampleState : State2 {
    SampleState(StateManager2* manager);
    virtual void reload() override;
    virtual void loop() override;
};

#endif // SAMPLESTATE_HPP
