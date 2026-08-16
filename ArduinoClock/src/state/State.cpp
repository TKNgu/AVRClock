#include "State.hpp"

#include <Arduino.h>

void ClockState::loop() {
    unsigned long now = millis();
    clockEngine_.updateTime(now);
    loop(now);
}
