#include "ClockPoint.hpp"

#include "../utils/Utils.hpp"

#define TIME_POIT_TASK 500

ClockPoint::ClockPoint() : timer(CreateTimer(TIME_POIT_TASK)) {}

void ClockPoint::show(unsigned long now) {
    if (TimerTimeoutFix(&timer, now)) {
        (showTimePoint = !showTimePoint) ? PointOn() : PointOff();
    }
}
