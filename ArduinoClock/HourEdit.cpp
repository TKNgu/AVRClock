#include "HourEdit.hpp"
#include <Arduino.h>

#include "ClockEdit.hpp"
#include "Utils.hpp"

void UpHour(unsigned char value) {
    hour += value;
    if (hour >= 24) {
        hour -= 24;
    }
}

void DownHour(unsigned char value) {
    hour = hour >= value ? hour - value : hour + 24 - value;
}

void BlinkHour() { ShowMin(minutes); }

void HourEditReload() {
    UpCallback = UpHour;
    DownCallback = DownHour;
    BlinkCallback = BlinkHour;
    ClockEditReload();
}
