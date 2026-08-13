#ifndef CLOCKSTATE_HPP
#define CLOCKSTATE_HPP

#include "StateManager2.hpp"
#include "clock/ClockChime.hpp"
#include "clock/ClockEngine.hpp"
#include "clock/ClockPoint.hpp"

struct ClockState : State2 {
    ClockEngine clockEngine;
    ClockPoint clockPoint;
    ClockChime clockChime;

    ClockState(StateManager2* manager);

    virtual void reload() override;
    virtual void loop() override;
};

#endif // CLOCKSTATE_HPP
