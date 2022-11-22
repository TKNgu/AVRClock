#include "Clock.hpp"
#include <avr/io.h>

using namespace tkngu::avr::clock;

Clock::Clock() {
	DDRD = LED::LED1 | LED::LED2 | LED::LED3 | LED::LED4;
}

void Clock::ledOn(uint8_t mask) {
	PORTD = this->ledState |= mask;
}

void Clock::ledOff(uint8_t mask) {
	PORTD = this->ledState &= (~mask);
}
