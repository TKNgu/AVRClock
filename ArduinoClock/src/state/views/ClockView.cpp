#include "ClockView.hpp"

#include <Arduino.h>

#include "../../utils/PowerManager.hpp"
#include "../../utils/Utils.hpp"
#include "../StateManager.hpp"

void ClockView::reload() {
    clockEngine_.reload();
    clockChime_.reload();
}

void ClockView::loop(unsigned long now) {
    if (clockEngine_.isUpdateMinute) {
        if (clockEngine_.needSleep()) {
            manager_->switchToSleepState();
            return;
        }
        if (clockChime_.check()) {
            powerManager.buzzer();
        }
    }

    clockLight_.check(now);
    if (clockEngine_.isUpdateDay) {
        clockLight_.updateGlobal();
    }

    if (buttonMenu_.scan(now) == Button::Click) {
        manager_->switchToNextState();
        return;
    }

    ShowTime(clockEngine_.hour, clockEngine_.minutes);
    blinkTimer_.blink(now) ? PointOn() : PointOff();
    
    powerManager.sleep(SleepMode::Deep, SLEEP_250MS);
}
