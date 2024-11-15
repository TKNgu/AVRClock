#include "Utils.hpp"
#include "Clock.hpp"

bool showPoint = true;
unsigned char level = 0;
unsigned char dayOfWeek = 1;

void setup() {
    HardwareInit();
    ChangState(ClockInit, ClockLoop);
}

void loop() {
    StateLoop();
}

