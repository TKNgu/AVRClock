#include "ClockView.hpp"

#include <Arduino.h>

#include "../../utils/PowerManager.hpp"
#include "../../utils/Utils.hpp"
#include "../StateManager.hpp"

void ClockView::reload() {
    unsigned long now = millis();
    timeManager.reload(now);
    chimeController.reload(timeManager.dayOfWeek, timeManager.hour,
                           timeManager.minutes);
    ShowTime(timeManager.hour, timeManager.minutes);
}

void ClockView::loop(unsigned long now) {
    if (timeManager.isUpdateMinute) {
        if (timeManager.needSleep()) {
            manager->switchToSleepState();
            return;
        }
        const bool isChime = chimeController.shouldChime(
            timeManager.dayOfWeek, timeManager.hour, timeManager.minutes);
        if (isChime) {
            powerManager.buzzer();
        }
        ShowTime(timeManager.hour, timeManager.minutes);
    }

    if (timeManager.isSecondsUpdate) {
        lightController.updateLoop(now);
        if (timeManager.isUpdateDay) {
            lightController.commitDailyMaxLight();
        }
    }

    if (blinkTimer.blink(now)) {
        blinkTimer.isBlink ? PointOn() : PointOff();
    }

    if (buttonMenu.scan(now) == Button::Click) {
        manager->switchToNextState();
        return;
    }

    powerManager.sleep(120);
}
