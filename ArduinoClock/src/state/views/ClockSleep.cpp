#include "ClockSleep.hpp"

#include "../../utils/PowerManager.hpp"
#include "../StateManager.hpp"

#define SLEEP_LIGHT_LEVEL 20

void ClockSleep::reload() {
    unsigned long now = powerManager.getMillis();
    timeManager_.reload(now);
    Clear();
    PointOff();
    LedOff(led1);
    LedOff(led2);
    LedOff(led3);
    LedOff(led4);
}

void ClockSleep::loop(unsigned long now) {
    if (!timeManager_.needSleep()) {
        manager_->switchToDefaultState();
        return;
    }

    if (GetLight() > SLEEP_LIGHT_LEVEL) {
        if (!isNeedClear) {
            blinkTimer_.reset(now, false);
            PointOn();
        }
        isNeedClear = true;
        if (blinkTimer_.blink(now)) {
            powerManager.buzzer();
            blinkTimer_.isBlink
                ? Clear()
                : ShowTime(timeManager_.hour, timeManager_.minutes);
        }
    } else if (isNeedClear) {
        isNeedClear = false;
        Clear();
        PointOff();
    }

    if (buttonMenu_.scan(now) == Button::LongPress) {
        manager_->switchToDefaultState();
    }

    powerManager.sleep(SleepMode::Idle, SLEEP_1S);
}
