#include "State.hpp"

#include "../utils/PowerManager.hpp"
#include <Arduino.h>

void ClockState::loop() {
    unsigned long now = powerManager.getMillis();
    timeManager_.updateTime(now);
    loop(now);
}
