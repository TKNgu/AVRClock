#ifndef STATEMANAGER2_HPP
#define STATEMANAGER2_HPP

#include "State.hpp"
#include "edit/HourEdit.hpp"
#include "edit/MinutesEdit.hpp"
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

  private:
    enum StateId {
        IdClockShow,
        IdHourEdit,
        IdMinutesEdit,

        IdStateCount,
    };

    ClockSleep sleepState;
    ClockView clockViewState;
    HourEdit hourEditState;
    MinutesEdit minutesEditState;

    State* states[IdStateCount];
    State* currentState;
    StateId currentStateId;

    void applyStateTransition();
};

#endif // STATEMANAGER2_HPP
