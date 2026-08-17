#include "HourEdit.hpp"

void HourEdit::displayBlinkFrame() { ShowMin(timeManager_.minutes); }

void HourEdit::increaseValue(unsigned char step) {
    timeManager_.increaseHour(step);
}

void HourEdit::decreaseValue(unsigned char step) {
    timeManager_.decreaseHour(step);
}
