#include "ClockEdit.hpp"

#include "../../utils/PowerManager.hpp"
#include "../../utils/Utils.hpp"
#include "../StateManager.hpp"

void ClockEdit::reload() {
    unsigned long now = powerManager.getMillis();
    blinkTimer_.reset(now, true);
    ResetTimer(&autoSaveTimer_, now);
    ShowTime(timeManager_.hour, timeManager_.minutes);
}

void ClockEdit::loop(unsigned long now) {
    switch (buttonUp_.scan(now)) {
    case Button::Click:
        increaseValue(1);
        resetView(now);
        break;
    case Button::LongPress:
        if (TimerTimeoutFix(&longPressTimer_, now)) {
            increaseValue(5);
            resetView(now);
        }
        break;
    default:
        break;
    }

    switch (buttonDown_.scan(now)) {
    case Button::Click:
        decreaseValue(1);
        resetView(now);
        break;
    case Button::LongPress:
        if (TimerTimeoutFix(&longPressTimer_, now)) {
            decreaseValue(5);
            resetView(now);
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

    if (TimerTimeoutFix(&autoSaveTimer_, now)) {
        timeManager_.setTime();
        manager_->switchToDefaultState();
        return;
    }

    if (blinkTimer_.blink(now)) {
        if ((blinkTimer_.isBlink = !blinkTimer_.isBlink)) {
            ShowTime(timeManager_.hour, timeManager_.minutes);
            PointOn();
        } else {
            displayBlinkFrame();
            PointOff();
        }
    }

    powerManager.sleep(SleepMode::Idle, SLEEP_250MS, false);
}

void ClockEdit::resetView(unsigned long now) {
    blinkTimer_.reset(now);
    ResetTimer(&autoSaveTimer_, now);
    ShowTime(timeManager_.hour, timeManager_.minutes);
}
