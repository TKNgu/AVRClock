#include "ClockEdit.hpp"

#include "../../utils/LowPower.h"
#include "../../utils/PowerManager.hpp"
#include "../../utils/Utils.hpp"
#include "../StateManager.hpp"

void ClockEdit::reload() {
    unsigned long now = powerManager.getMillis();
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
            return;
        }
        resetView(now);
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
            return;
        }
        resetView(now);
        break;
    default:
        break;
    }

    switch (buttonMenu_.scan(now)) {
    case Button::Click:
        timeManager_.setTime();
        timeManager_.waitSleep(5);
        manager_->switchToNextState();
        return;
    case Button::LongPress:
        timeManager_.setTime();
        timeManager_.waitSleep(5);
        manager_->switchToDefaultState();
        return;
    default:
        break;
    }

    blinkTimer_.blink(now);
    if (blinkTimer_.isChanged || isValueChanged_) {
        isValueChanged_ = false;

        if (blinkTimer_.isBlink) {
            displayBlinkFrame();
            PointOff();
        } else {
            ShowTime(timeManager_.hour, timeManager_.minutes);
            PointOn();
        }
    }

    if (TimerTimeoutFix(&autoSaveTimer_, now)) {
        timeManager_.setTime(); // Perform the actual auto-save
        timeManager_.waitSleep(5);
        manager_->switchToDefaultState();
        return;
    }

    powerManager.sleep(SleepMode::Idle, SLEEP_250MS, false);
}

void ClockEdit::resetView(unsigned long now) {
    ResetTimer(&autoSaveTimer_, now);
    blinkTimer_.reset(now);
}
