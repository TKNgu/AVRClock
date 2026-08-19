#include "ClockView.hpp"

#include <Arduino.h>

#include "../../utils/PowerManager.hpp"
#include "../../utils/Utils.hpp"
#include "../StateManager.hpp"

void ClockView::reload() {
    unsigned long now = powerManager.getMillis();
    timeManager_.reload(now);
    chimeController_.reload(timeManager_.dayOfWeek, timeManager_.hour,
                            timeManager_.minutes);
    ShowTime(timeManager_.hour, timeManager_.minutes);
}

void ClockView::loop(unsigned long now) {
    if (timeManager_.isUpdateMinute) {
        if (timeManager_.needSleep()) {
            manager_->switchToSleepState();
            return;
        }
        const bool isChime = chimeController_.shouldChime(
            timeManager_.dayOfWeek, timeManager_.hour, timeManager_.minutes);
        if (isChime) {
            powerManager.buzzer();
        }
        ShowTime(timeManager_.hour, timeManager_.minutes);
    }

    if (timeManager_.isSecondsUpdate) {
        lightController_.updateLoop(now);
        if (timeManager_.isUpdateDay) {
            lightController_.commitDailyMaxLight();
        }
    }

    if (blinkTimer_.blink(now)) {
        blinkTimer_.isBlink ? PointOn() : PointOff();
    }

    if (buttonMenu_.scan(now) == Button::Click) {
        manager_->switchToNextState();
        return;
    }

    powerManager.sleep(SleepMode::Idle, SLEEP_250MS);
}
