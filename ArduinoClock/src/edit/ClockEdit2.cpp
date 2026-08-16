#include "ClockEdit2.hpp"

#include "../utils/LowPower.h"
#include "../utils/Utils.hpp"

ClockEdit2::ClockEdit2(StateManager2* manager)
    : State2(manager), blinkTimer(500), autoSaveTimer(CreateTimer(5000)),
      longPressTimer(CreateTimer(500)), buttonUp(Key::KeyUp),
      buttonDown(Key::KeyDown), buttonMenu(Key::KeyMenu) {}

void ClockEdit2::reload() {
    GetClock(&hour, &minutes);
    ResetTimer(&autoSaveTimer);
    blinkTimer.reset(0);
}

void ClockEdit2::loop() {
    switch (buttonUp.scan()) {
    case Button2::Click: {
        upCallback(1);
        Buzzer();
        ResetTimer(&autoSaveTimer);
        blinkTimer.reset();
        break;
    }
    case Button2::LongPress: {
        if (TimerTimeout(&longPressTimer)) {
            upCallback(5);
            ResetTimer(&autoSaveTimer);
            blinkTimer.reset();
        }
    }
    }

    switch (buttonDown.scan()) {
    case Button2::Click: {
        downCallback(1);
        Buzzer();
        ResetTimer(&autoSaveTimer);
        blinkTimer.reset();
        break;
    }
    case Button2::LongPress: {
        if (TimerTimeout(&longPressTimer)) {
            downCallback(5);
            ResetTimer(&autoSaveTimer);
            blinkTimer.reset();
        }
    }
    }

    switch (buttonMenu.scan()) {
    case Button2::Click: {
        SetTime(hour, minutes);
        manager->nextState();
        break;
    };
    case Button2::LongPress: {
        SetTime(hour, minutes);
        manager->startState();
        break;
    };
    default: {
        break;
    }
    }

    if (blinkTimer.blink()) {
        show();
        PointOn();
    } else {
        ShowTime(hour, minutes);
        PointOff();
    }

    if (TimerTimeout(&autoSaveTimer)) {
        State2::manager->startState();
    }
    LowPower.idle(SLEEP_120MS, ADC_OFF, TIMER2_ON, TIMER1_OFF, TIMER0_ON,
                  SPI_OFF, USART0_OFF, TWI_OFF);
}
