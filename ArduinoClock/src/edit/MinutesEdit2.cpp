#include "MinutesEdit2.hpp"

MinutesEdit2::MinutesEdit2(StateManager2* manager) : ClockEdit2(manager) {}

void MinutesEdit2::show() { ShowHour(hour); }

void MinutesEdit2::upCallback(int value) {
    minutes += value;
    if (minutes >= 60) {
        minutes -= 60;
    }
}

void MinutesEdit2::downCallback(int value) {
    minutes = minutes >= value ? minutes - value : minutes + 60 - value;
}
