#ifndef STATEMANAGER2_HPP
#define STATEMANAGER2_HPP

#include "State.hpp"
#include "edit/HourEdit.hpp"
#include "edit/MinutesEdit.hpp"
#include "views/ClockDeepSleep.hpp"
#include "views/ClockSleep.hpp"
#include "views/ClockView.hpp"

class StateManager {
  public:
    StateManager();

    void setup();
    void loop();
    void switchToNextState();
    void switchToDefaultState();
    void switchToSleepState();
    void switchToDeepSleepState();

  private:
    enum StateId {
        IdClockShow,
        IdHourEdit,
        IdMinutesEdit,

        IdStateCount,
    };

    ClockSleep sleepState;
    ClockDeepSleep deepSleepState;
    ClockView clockViewState;
    HourEdit hourEditState;
    MinutesEdit minutesEditState;

    State* states[IdStateCount];
    State* currentState;
    StateId currentStateId;

    void applyStateTransition();
};

#endif // STATEMANAGER2_HPP
