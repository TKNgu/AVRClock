#include "ClockView.hpp"

#include <Arduino.h>

#include "../../utils/PowerManager.hpp"
#include "../../utils/Utils.hpp"
#include "../StateManager.hpp"

void ClockView::reload() {
    timeManager_.reload();
    chimeController_.reload();
    ShowTime(timeManager_.hour, timeManager_.minutes);
}

void ClockView::loop(unsigned long now) {
    if (timeManager_.isUpdateMinute) {
        if (timeManager_.needSleep()) {
            manager_->switchToSleepState();
            return;
        }
        if (chimeController_.shouldChime()) {
            powerManager.buzzer();
        }
        ShowTime(timeManager_.hour, timeManager_.minutes);
    }

    lightController_.updateLoop(now);
    if (timeManager_.isUpdateDay) {
        lightController_.commitDailyMaxLight();
    }

    if (buttonMenu_.scan(now) == Button::Click) {
        manager_->switchToNextState();
        return;
    }

    blinkTimer_.blink(now);
    if (blinkTimer_.isChanged) {
        blinkTimer_.isBlink ? PointOn() : PointOff();
    }
    
    powerManager.sleep(SleepMode::Idle, SLEEP_250MS);
}
