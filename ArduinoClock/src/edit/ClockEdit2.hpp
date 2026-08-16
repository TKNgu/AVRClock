#ifndef CLOCKEDIT2_HPP
#define CLOCKEDIT2_HPP

#include "../StateManager2.hpp"
#include "../utils/BlinkTimer.hpp"
#include "../utils/Button2.hpp"

struct ClockEdit2 : State2 {
    unsigned char hour;
    unsigned char minutes;

    BlinkTimer blinkTimer;
    Timer autoSaveTimer;
    Timer longPressTimer;

    Button2 buttonUp;
    Button2 buttonDown;
    Button2 buttonMenu;

    ClockEdit2(StateManager2*);

    virtual void reload() override;
    virtual void loop() override;

    virtual void show() = 0;
    virtual void upCallback(int) = 0;
    virtual void downCallback(int) = 0;
};

#endif // CLOCKEDIT2_HPP
