#include <avr/io.h>
#include <util/delay.h>
#include "Clock.hpp"

using namespace tkngu::avr::clock;

int main() {
	Clock clock;
	while (true) {
		clock.ledOn(LED::LED1);
		_delay_ms(1000);
		clock.ledOn(LED::LED2);
		_delay_ms(1000);
		clock.ledOn(LED::LED3);
		_delay_ms(1000);
		clock.ledOn(LED::LED4);
		_delay_ms(1000);
		clock.ledOff(LED::ALL);
		_delay_ms(1000);
	}
	return 0;
}
