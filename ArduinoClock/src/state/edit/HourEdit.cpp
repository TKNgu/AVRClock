#include "HourEdit.hpp"

void HourEdit::displayBlinkFrame() { ShowMin(clockEngine_.minutes); }

void HourEdit::increaseValue(unsigned char step) {
    clockEngine_.addHour(step);
}

void HourEdit::decreaseValue(unsigned char step) {
    clockEngine_.subHour(step);
}
