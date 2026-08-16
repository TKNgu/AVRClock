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
}

void ClockSleep::loop(unsigned long now) {
    if (buttonMenu_.scan(now) == Button::LongPress) {
        clockEngine_.waitSleep(1000);
        manager_->switchToDefaultState();
        return;
    }

    if (GetLight() < SLEEP_LIGHT_LEVEL) {
        powerManager.sleep(SleepMode::Deep, SLEEP_1S);
    } else {
        if (TimerTimeoutFix(&sleepTimer_, now)) {
            powerManager.buzzer();
        }
        powerManager.sleep(SleepMode::Idle, SLEEP_250MS);
    }
}
