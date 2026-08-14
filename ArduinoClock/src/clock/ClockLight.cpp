#include "ClockLight.hpp"

#include "../utils/Utils.hpp"

#define CHECK_LIGHT_TASK 2000
#define LIGHT_LEVEL_WARNING 30

ClockLight::ClockLight() : timer(CreateTimer(CHECK_LIGHT_TASK)) {}

void ClockLight::check(const unsigned long now) {
    if (TimerTimeoutFix(&timer, now)) {
        (GetLight() < LIGHT_LEVEL_WARNING) ? LedOn(led2) : LedOff(led2);
        AutoLight();
    }
}
