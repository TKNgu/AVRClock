#include "StateManager.hpp"

#include <Arduino.h> // NOLINT

#include "../utils/PowerManager.hpp"
#include "../utils/Utils.hpp"

StateManager::StateManager() {
    states[IdClockShow] = &clockViewState;
    states[IdHourEdit] = &hourEditState;
    states[IdMinutesEdit] = &minutesEditState;
}

void StateManager::setup() {
    State::manager = this;
    HardwareInit();
    switchToDefaultState();
}

void StateManager::loop() { currentState->loop(); }

void StateManager::switchToNextState() {
    currentStateId = (StateId)((currentStateId + 1) % IdStateCount);
    applyStateTransition();
}

void StateManager::switchToDefaultState() {
    currentStateId = IdClockShow;
    applyStateTransition();
}

void StateManager::switchToSleepState() {
    currentState = &sleepState;
    currentState->reload();
}

void StateManager::switchToDeepSleepState() {
    currentState = &deepSleepState;
    currentState->reload();
}

void StateManager::applyStateTransition() {
    currentState = states[currentStateId];
    currentState->reload();
    powerManager.buzzer();
}
