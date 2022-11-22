#include <avr/io.h>
#include <util/delay.h>

int main() {
	DDRB = 0b000000001;
	while (true) {
		PORTB = 0b00000001;
		_delay_ms(1000);
		PORTB = 0b00000000;
		_delay_ms(1000);
	}
	return 0;
}
