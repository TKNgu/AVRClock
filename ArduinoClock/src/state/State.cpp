#include "State.hpp"

#include "../utils/PowerManager.hpp"
#include <Arduino.h>

void ClockState::loop() {
    unsigned long now = millis();
    timeManager.updateTime(now);
    loop(now);
}
