#include "State.hpp"

#include <Arduino.h>

void ClockState::loop() {
    unsigned long now = millis();
    timeManager_.updateTime(now);
    loop(now);
}
