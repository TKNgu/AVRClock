#include "SleepState.hpp"
#include <Arduino.h>

void SleepState::loop(unsigned int)
{
    long int startTime = millis();
    Serial.println(startTime);
    update(state);
    long int delta = millis() - startTime;
    if (delta < delayTime)
    {
        delay(delayTime - delta);
    }
}