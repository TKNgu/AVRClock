#include "ClockSleep.hpp"

#include "../../utils/PowerManager.hpp"
#include "../StateManager.hpp"

#define SLEEP_LIGHT_LEVEL 20

void ClockSleep::reload() {
    LightOff();
    isNeedWarning = false;
    timeManager.reload(millis());
    isNeedDeepSleep = timeManager.getDeepSleepTime() != 0;
}

void ClockSleep::loop(unsigned long now) {
    if (!timeManager.needSleep()) {
        manager->switchToDefaultState();
        return;
    }

    if (isNeedWarning) {
        if (GetLight() > SLEEP_LIGHT_LEVEL) {
            if (blinkTimer.blink(now)) {
                powerManager.buzzer();
                blinkTimer.isBlink
                    ? Clear()
                    : ShowTime(timeManager.hour, timeManager.minutes);
            }
        } else {
            isNeedWarning = false;
            Clear();
            PointOff();
        }
    } else {
        if (GetLight() > SLEEP_LIGHT_LEVEL) {
            isNeedWarning = true;
            blinkTimer.reset(now);
            PointOn();
        } else if (isNeedDeepSleep) {
            manager->switchToDeepSleepState();
            return;
        }
    }

    if (buttonMenu.scan(now) == Button::LongPress) {
        manager->switchToDefaultState();
    }

    powerManager.sleep(500);
}
