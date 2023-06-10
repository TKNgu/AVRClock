#include "DelayState.hpp"

#include <Arduino.h>

void DelayState::loop() {
    long int startTime = millis();
    update();
    long int delta = millis() - startTime;
    if (delta < delayTime) {
        delay(delayTime - delta);
    }
}
