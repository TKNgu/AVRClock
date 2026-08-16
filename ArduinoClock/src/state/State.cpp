#include "State.hpp"

#include <Arduino.h>
#include "../utils/PowerManager.hpp"

void ClockState::loop() {
    unsigned long now = powerManager.getMillis();
    timeManager_.updateTime(now);
    loop(now);
}
