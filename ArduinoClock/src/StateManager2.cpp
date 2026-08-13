#include "StateManager2.hpp"

#include "ClockState.hpp"
#include "utils/Utils.hpp"

StateManager2::StateManager2() {
    states[ClockShow] = new ClockState(this);

    currentStateId = ClockShow;
    currentState = states[currentStateId];
}

StateManager2::~StateManager2() {
    for (int i = 0; i < StateCount; i++) {
        delete states[i];
    }
}

void StateManager2::setUp() {
    HardwareInit();
    currentState->reload();
    Buzzer();
}

void StateManager2::loop() { currentState->loop(); }

void StateManager2::nextState() {
    currentStateId = (State2Id)((currentStateId + 1) % StateCount);
    currentState = states[currentStateId];
    currentState->reload();
}

void StateManager2::startState() {
    currentStateId = ClockShow;
    currentState = states[currentStateId];
    currentState->reload();
}
