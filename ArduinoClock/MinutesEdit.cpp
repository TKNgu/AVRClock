#include "MinutesEdit.hpp"
#include <Arduino.h>

#include "ClockEdit.hpp"
#include "Utils.hpp"

void UpMinutes(unsigned char value) {
    minutes += value;
    if (minutes >= 60) {
        minutes -= 60;
    }
}

void DownMinutes(unsigned char value) {
    minutes = minutes >= value ? minutes - value : minutes + 60 - value;
}

void BlinkMinutes() { ShowHour(hour); }

void MinutesEditReload() {
    UpCallback = UpMinutes;
    DownCallback = DownMinutes;
    BlinkCallback = BlinkMinutes;
    ClockEditReload();
}
