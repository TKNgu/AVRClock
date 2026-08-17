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
    isNearWakeUpSynced_ = false;
}

void ClockSleep::loop(unsigned long now) {
    if (!timeManager_.needSleep()) {
        manager_->switchToDefaultState();
        return;
    }

    if (buttonMenu_.scan(now) == Button::LongPress) {
        timeManager_.waitSleep(5);
        manager_->switchToDefaultState();
        return;
    }

    if (GetLight() < SLEEP_LIGHT_LEVEL) {
        if (isNeedClear_) {
            isNeedClear_ = false;
            Clear();
            PointOff();
        }

        if (timeManager_.isNearWakeUp(10)) {
            if (!isNearWakeUpSynced_) {
                timeManager_.reload();
                isNearWakeUpSynced_ = true;
            }
            powerManager.sleep(SleepMode::Idle, SLEEP_1S);
        } else {
            isNearWakeUpSynced_ = false;
            powerManager.sleep(SleepMode::Deep, SLEEP_1S);
        }
    } else {
        if (TimerTimeoutFix(&sleepTimer_, now)) {
            powerManager.buzzer();
        }

        isNeedClear_ = true;
        blinkTimer_.blink(now);
        if (blinkTimer_.isChanged) {
            if (blinkTimer_.isBlink) {
                ShowTime(timeManager_.hour, timeManager_.minutes);
                PointOn();
            } else {
                Clear();
                PointOff();
            }
        }

        powerManager.sleep(SleepMode::Idle, SLEEP_250MS);
    }
}
