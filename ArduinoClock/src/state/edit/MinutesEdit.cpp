#include "MinutesEdit.hpp"

void MinutesEdit::displayBlinkFrame() { ShowHour(timeManager.hour); }

void MinutesEdit::increaseValue(unsigned char step) {
    timeManager.increaseMinute(step);
}

void MinutesEdit::decreaseValue(unsigned char step) {
    timeManager.decreaseMinute(step);
}
