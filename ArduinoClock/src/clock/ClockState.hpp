#ifndef CLOCKSTATE_HPP
#define CLOCKSTATE_HPP

#include "../StateManager2.hpp"
#include "ClockChime.hpp"
#include "ClockEngine.hpp"
#include "ClockLight.hpp"
#include "ClockPoint.hpp"

struct ClockState : State2 {
    ClockEngine clockEngine;
    ClockPoint clockPoint;
    ClockChime clockChime;
    ClockLight clockLight;

    ClockState(StateManager2* manager);

    virtual void reload() override;
    virtual void loop() override;
};

#endif // CLOCKSTATE_HPP
