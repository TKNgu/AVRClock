#include "Utils.hpp"
#include "Clock.hpp"

void setup() {
    HardwareInit();
    ClockInit();
    ChangState(ClockReload, ClockLoop);
}

void loop() {
    StateLoop();
}

