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

    ClockSleep sleepState_;
    ClockView clockViewState_;
    HourEdit hourEditState_;
    MinutesEdit minutesEditState_;

    State* states_[IdStateCount];
    State* currentState_;
    StateId currentStateId_;

    void applyStateTransition();
};

#endif // STATEMANAGER2_HPP
