#include "PowerManager.hpp"

#include <Arduino.h>

#include "../utils/LowPower.h"

#define BUZZER_DEVICE 6

PowerManager powerManager;

void PowerManager::buzzer() {
    tone(BUZZER_DEVICE, 2400, 60);
    buzzerTime = millis();
}

void PowerManager::sleep(unsigned long sleepTime) {
    const unsigned long start = millis();
    while (millis() - start < sleepTime) {
        if (millis() - buzzerTime < 1000) {
            LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_ON, TIMER1_OFF,
                          TIMER0_ON, SPI_OFF, USART0_OFF, TWI_OFF);
        } else {
            LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_OFF, TIMER1_OFF,
                          TIMER0_ON, SPI_OFF, USART0_OFF, TWI_OFF);
        }
    }
}
