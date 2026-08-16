#include "ClockSleep.hpp"

#include "../../utils/PowerManager.hpp"
#include "../StateManager.hpp"

#define SLEEP_LIGHT_LEVEL 20

void ClockSleep::reload() {
    Clear();
    PointOff();
    LedOff(led1);
    LedOff(led2);
    LedOff(led3);
    LedOff(led4);
    ResetTimer(&sleepTimer_);
    isNeedClear_ = true;
}

void ClockSleep::loop(unsigned long now) {
    if (buttonMenu_.scan(now) == Button::LongPress) {
        timeManager_.waitSleep(180000);
        manager_->switchToDefaultState();
        return;
    }

    if (GetLight() < SLEEP_LIGHT_LEVEL) {
        if (isNeedClear_) {
            isNeedClear_ = false;
            Clear();
            PointOff();
        }
        powerManager.sleep(SleepMode::Deep, SLEEP_1S);
    } else {
        if (TimerTimeoutFix(&sleepTimer_, now)) {
            powerManager.buzzer();
        }

        isNeedClear_ = true;
        if (blinkTimer_.blink(now)) {
            ShowTime(timeManager_.hour, timeManager_.minutes);
            PointOn();
        } else {
            Clear();
            PointOff();
        }

        powerManager.sleep(SleepMode::Idle, SLEEP_250MS);
    }
}
