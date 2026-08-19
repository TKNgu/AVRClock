#include "StateManager.hpp"

#include <Arduino.h> // NOLINT

#include "../utils/PowerManager.hpp"
#include "../utils/Utils.hpp"

StateManager::StateManager() {
    states_[IdClockShow] = &clockViewState_;
    states_[IdHourEdit] = &hourEditState_;
    states_[IdMinutesEdit] = &minutesEditState_;
}

void StateManager::setup() {
    State::manager_ = this;
    HardwareInit();
    switchToDefaultState();
    // switchToSleepState();
}

void StateManager::loop() { currentState_->loop(); }

void StateManager::switchToNextState() {
    currentStateId_ = (StateId)((currentStateId_ + 1) % IdStateCount);
    applyStateTransition();
}

void StateManager::switchToDefaultState() {
    currentStateId_ = IdClockShow;
    applyStateTransition();
}

void StateManager::switchToSleepState() {
    currentState_ = &sleepState_;
    currentState_->reload();
}

void StateManager::applyStateTransition() {
    currentState_ = states_[currentStateId_];
    currentState_->reload();
    powerManager.buzzer();
}
