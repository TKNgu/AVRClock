#ifndef STATE2_HPP
#define STATE2_HPP

#include <Arduino.h>

#include "../button/Button.hpp"
#include "../clock/TimeManager.hpp"
#include "../timer/BlinkTimer.hpp"

class StateManager;

class State {
    friend class StateManager;

  public:
    virtual ~State() = default;

    virtual void reload() = 0;
    virtual void loop() = 0;

  protected:
    inline static StateManager* manager_ = nullptr;
    inline static Button buttonMenu_ = Button(Key::KeyMenu);
};

class ClockState : public State {
  public:
    void loop() override;
    virtual void loop(unsigned long) = 0;

  protected:
    inline static BlinkTimer blinkTimer_ = BlinkTimer(500);
    inline static TimeManagerAdvance timeManager_ = TimeManagerAdvance();
};

#endif // STATE2_HPP
