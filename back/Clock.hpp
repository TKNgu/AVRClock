#ifndef Clock_hpp
#define Clock_hpp

#include <stdint.h>

namespace tkngu::avr::clock {

enum LED {
	ALL = 0b00111100,
	LED1 = 0b00000100,
	LED2 = 0b00001000,
	LED3 = 0b00010000,
	LED4 = 0b00100000,
};

enum KEY {
	KEY1 = 0b00000010,
	KEY2 = 0b00000100,
	KEY3 = 0b00001000,
};

class Clock {
public:
	Clock();
	void ledOn(uint8_t);
	void ledOff(uint8_t);
	bool isKeyPress(uint8_t);
private:
	uint8_t ledState = 0b00000000;
};
}

#endif
