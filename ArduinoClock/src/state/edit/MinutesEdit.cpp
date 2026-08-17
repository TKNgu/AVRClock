#include "MinutesEdit.hpp"

void MinutesEdit::displayBlinkFrame() { ShowHour(timeManager_.hour); }

void MinutesEdit::increaseValue(unsigned char step) {
    timeManager_.increaseMinute(step);
}

void MinutesEdit::decreaseValue(unsigned char step) {
    timeManager_.decreaseMinute(step);
}
