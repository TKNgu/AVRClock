#include "ClockDeepSleep.hpp"

#include <Arduino.h>

#include "../../utils/PowerManager.hpp"
#include "../StateManager.hpp"

#define SLEEP_LIGHT_LEVEL 20

void ClockDeepSleep::reload() {
    deepSleepTimer = timeManager.getDeepSleepTime();
    isNeedView = false;
}

void ClockDeepSleep::loop() {
    if (buttonMenu.isPress()) {
        isNeedView = true;
        PointOn();
    } else if (isNeedView) {
        manager->switchToDefaultState();
        return;
    }

    if (deepSleepTimer > 0) {
        deepSleepTimer--;
        ShowNum(deepSleepTimer);
        if (GetLight() > SLEEP_LIGHT_LEVEL) {
            manager->switchToSleepState();
            return;
        }
        powerManager.powerOff(1);
    } else {
        timeManager.reload(millis());
        deepSleepTimer = timeManager.getDeepSleepTime();
        if (deepSleepTimer == 0) {
            manager->switchToSleepState();
            return;
        }
    }
}
