#include "HourEdit.hpp"

void HourEdit::displayBlinkFrame() { ShowMin(timeManager.minutes); }

void HourEdit::increaseValue(unsigned char step) {
    timeManager.increaseHour(step);
}

void HourEdit::decreaseValue(unsigned char step) {
    timeManager.decreaseHour(step);
}
