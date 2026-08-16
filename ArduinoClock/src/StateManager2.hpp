#ifndef STATEMANAGER2_HPP
#define STATEMANAGER2_HPP

class StateManager2;

struct State2 {
    StateManager2* manager;

    State2(StateManager2* manager) : manager(manager) {}
    virtual ~State2() = default;

    virtual void reload() = 0;
    virtual void loop() = 0;
};

enum State2Id {
    ClockShow,
    HourEdit,
    MinutesEdit,

    StateCount,
};

struct StateManager2 {
    State2* states[StateCount];
    State2* currentState;
    State2Id currentStateId;

    StateManager2();
    ~StateManager2();
    void setUp();
    void loop();
    void nextState();
    void startState();
    void changeState();
};

#endif // STATEMANAGER2_HPP
