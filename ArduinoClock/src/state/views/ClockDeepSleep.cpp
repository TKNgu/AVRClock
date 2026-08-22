#include "ClockDeepSleep.hpp"

#include <Arduino.h>

#include "../../utils/PowerManager.hpp"
#include "../../utils/Storage.hpp"
#include "../StateManager.hpp"

#define SLEEP_LIGHT_LEVEL 20
#define SLEEP_TIME_CALC 300

WDTScale::WDTScale() : scale(storage.getWDTScale()) {}

unsigned int WDTScale::start(unsigned char hour, unsigned char minute,
                             unsigned char second, unsigned int sleepTime) {
    this->hour = hour;
    this->minute = minute;
    this->second = second;
    startPoint = static_cast<unsigned int>(sleepTime * scale);
    return startPoint;
}

void WDTScale::stop(unsigned char hour, unsigned char minute,
                    unsigned char second, unsigned int endPoint) {
    const unsigned int sleepTime = startPoint - endPoint;
    if (sleepTime < SLEEP_TIME_CALC) {
        return;
    }
    const unsigned int realSleepTime =
        (hour * 3600 + minute * 60 + second) -
        (this->hour * 3600 + this->minute * 60 + this->second);
    ShowNum(realSleepTime);
    const float newScale =
        static_cast<float>(sleepTime) / static_cast<float>(realSleepTime);
    scale = scale * 0.25f + newScale * 0.75f;
}

void WDTScale::save() { storage.saveWDTScale(scale); }

void ClockDeepSleep::reload() {
    timeManager.reload(millis());
    const unsigned realDeepSleepTime = timeManager.getDeepSleepTime();
    deepSleepTimer = wdtScale.start(timeManager.hour, timeManager.minutes,
                                    timeManager.seconds, realDeepSleepTime);
    isNeedView = false;
}

void ClockDeepSleep::loop() {
    if (buttonMenu.isPress()) {
        isNeedView = true;
        PointOn();
    } else if (isNeedView) {
        manager->switchToDefaultState();
        wdtScale.stop(timeManager.hour, timeManager.minutes,
                      timeManager.seconds, deepSleepTimer);
        return;
    }

    if (deepSleepTimer > 0) {
        deepSleepTimer--;
        if (GetLight() > SLEEP_LIGHT_LEVEL) {
            manager->switchToSleepState();
            wdtScale.stop(timeManager.hour, timeManager.minutes,
                          timeManager.seconds, deepSleepTimer);
            return;
        }
    } else {
        const unsigned realDeepSleepTime = timeManager.getDeepSleepTime();
        if (realDeepSleepTime == 0) {
            manager->switchToSleepState();
            wdtScale.save();
            return;
        }
        timeManager.reload(millis());
        wdtScale.stop(timeManager.hour, timeManager.minutes,
                      timeManager.seconds, deepSleepTimer);
        deepSleepTimer = wdtScale.start(timeManager.hour, timeManager.minutes,
                                        timeManager.seconds, realDeepSleepTime);
    }

    powerManager.powerOff(1);
}
