#include "MinutesEdit.hpp"

void MinutesEdit::displayBlinkFrame() { ShowHour(clockEngine_.hour); }

void MinutesEdit::increaseValue(unsigned char step) {
    clockEngine_.addMinute(step);
}

void MinutesEdit::decreaseValue(unsigned char step) {
    clockEngine_.subMinute(step);
}
