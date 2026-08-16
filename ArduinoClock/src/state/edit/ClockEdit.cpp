#include "ClockEdit.hpp"

#include "../StateManager.hpp"
#include "../../utils/LowPower.h"
#include "../../utils/Utils.hpp"
#include "../../utils/PowerManager.hpp"

void ClockEdit::reload() {
    unsigned long now = millis();
    ResetTimer(&autoSaveTimer_, now);
    blinkTimer_.reset(now);
}

void ClockEdit::loop(unsigned long now) {
    switch (buttonUp_.scan(now)) {
    case Button::Click:
        increaseValue(1);
        powerManager.buzzer();
        resetView(now);
        return;
    case Button::LongPress:
        if (TimerTimeoutFix(&longPressTimer_, now)) {
            increaseValue(5);
            resetView(now);
            return;
        }
        break;
    default:
        break;
    }

    switch (buttonDown_.scan(now)) {
    case Button::Click:
        decreaseValue(1);
        powerManager.buzzer();
        resetView(now);
        return;
    case Button::LongPress:
        if (TimerTimeoutFix(&longPressTimer_, now)) {
            decreaseValue(5);
            resetView(now);
            return;
        }
        break;
    default:
        break;
    }

    switch (buttonMenu_.scan(now)) {
    case Button::Click:
        timeManager_.setTime();
        manager_->switchToNextState();
        return;
    case Button::LongPress:
        timeManager_.setTime();
        manager_->switchToDefaultState();
        return;
    default:
        break;
    }

    if (blinkTimer_.blink(now)) {
        displayBlinkFrame();
        PointOff();
    } else {
        ShowTime(timeManager_.hour, timeManager_.minutes);
        PointOn();
    }

    if (TimerTimeoutFix(&autoSaveTimer_, now)) {
        timeManager_.setTime(); // Perform the actual auto-save
        manager_->switchToDefaultState();
        return;
    }

    LowPower.idle(SLEEP_250MS, ADC_OFF, TIMER2_ON, TIMER1_OFF, TIMER0_ON,
                  SPI_OFF, USART0_OFF, TWI_OFF);
}

void ClockEdit::resetView(unsigned long now) {
    ResetTimer(&autoSaveTimer_, now);
    blinkTimer_.reset(now);
}
