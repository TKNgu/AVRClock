#include "ClockEdit.hpp"

#include "../../utils/PowerManager.hpp"
#include "../../utils/Utils.hpp"
#include "../StateManager.hpp"

void ClockEdit::reload() {
    unsigned long now = millis();
    ResetTimer(&autoSaveTimer, now);
    ShowTime(timeManager.hour, timeManager.minutes);
    blinkTimer.reset(now);
}

void ClockEdit::loop(unsigned long now) {
    switch (buttonUp.scan(now)) {
    case Button::Click:
        increaseValue(1);
        resetView(now);
        break;
    case Button::LongPress:
        if (TimerTimeoutFix(&longPressTimer, now)) {
            increaseValue(5);
            resetView(now);
        }
        break;
    default:
        break;
    }

    switch (buttonDown.scan(now)) {
    case Button::Click:
        decreaseValue(1);
        resetView(now);
        break;
    case Button::LongPress:
        if (TimerTimeoutFix(&longPressTimer, now)) {
            decreaseValue(5);
            resetView(now);
        }
        break;
    default:
        break;
    }

    switch (buttonMenu.scan(now)) {
    case Button::Click:
        timeManager.setTime();
        manager->switchToNextState();
        return;
    case Button::LongPress:
        timeManager.setTime();
        manager->switchToDefaultState();
        return;
    default:
        break;
    }

    if (TimerTimeoutFix(&autoSaveTimer, now)) {
        timeManager.setTime();
        manager->switchToDefaultState();
        return;
    }

    if (blinkTimer.blink(now)) {
        if (blinkTimer.isBlink) {
            ShowTime(timeManager.hour, timeManager.minutes);
            PointOn();
        } else {
            displayBlinkFrame();
            PointOff();
        }
    }

    powerManager.sleep(100);
}

void ClockEdit::resetView(unsigned long now) {
    blinkTimer.reset(now, false);
    ResetTimer(&autoSaveTimer, now);
    ShowTime(timeManager.hour, timeManager.minutes);
}
