#include "StateManager2.hpp"

#include <Arduino.h> // NOLINT

#include "clock/ClockState.hpp"
#include "edit/HourEdit2.hpp"
#include "edit/MinutesEdit2.hpp"
#include "utils/Utils.hpp"

StateManager2::StateManager2() {
    states[ClockShow] = new ClockState(this);
    states[HourEdit] = new HourEdit2(this);
    states[MinutesEdit] = new MinutesEdit2(this);
}

StateManager2::~StateManager2() {
    for (int i = 0; i < StateCount; i++) {
        delete states[i];
    }
}

void StateManager2::setUp() {
    HardwareInit();
    startState();
}

void StateManager2::loop() { currentState->loop(); }

void StateManager2::nextState() {
    currentStateId = (State2Id)((currentStateId + 1) % StateCount);
    changeState();
}

void StateManager2::startState() {
    currentStateId = ClockShow;
    changeState();
}

void StateManager2::changeState() {
    currentState = states[currentStateId];
    currentState->reload();
    Buzzer();
}
