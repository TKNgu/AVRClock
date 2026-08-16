#include "HourEdit2.hpp"

HourEdit2::HourEdit2(StateManager2* manager) : ClockEdit2(manager) {}

void HourEdit2::show() { ShowMin(minutes); }

void HourEdit2::upCallback(int value) {
    hour += value;
    if (hour >= 24) {
        hour -= 24;
    }
}

void HourEdit2::downCallback(int value) {
    hour = hour >= value ? hour - value : hour + 24 - value;
}
