#include "PowerManager.hpp"
#include <Arduino.h>

#define BUZZER_DEVICE 6

PowerManager powerManager;

void PowerManager::buzzer() {
    tone(BUZZER_DEVICE, 2400, 60);
    blockDeepSleep(2000); // 2s delay
}

void PowerManager::buzzerSilent() {
    noTone(BUZZER_DEVICE);
}

void PowerManager::blockDeepSleep(unsigned long durationMs) {
    blockDeepSleepUntil_ = millis() + durationMs;
}

unsigned long PowerManager::getPeriodMs(period_t period) {
    switch (period) {
        case SLEEP_15MS: return 15;
        case SLEEP_30MS: return 30;
        case SLEEP_60MS: return 60;
        case SLEEP_120MS: return 120;
        case SLEEP_250MS: return 250;
        case SLEEP_500MS: return 500;
        case SLEEP_1S: return 1000;
        case SLEEP_2S: return 2000;
        case SLEEP_4S: return 4000;
        case SLEEP_8S: return 8000;
        default: return 0;
    }
}

void PowerManager::sleep(SleepMode mode, period_t period, bool needAdc) {
    unsigned long now = millis();
    bool canDeepSleep = (mode == SleepMode::Deep) && ((long)(now - blockDeepSleepUntil_) >= 0);

    if (canDeepSleep) {
        extern volatile unsigned long timer0_millis;
        LowPower.powerDown(period, ADC_OFF, BOD_OFF);
        noInterrupts();
        timer0_millis += getPeriodMs(period);
        interrupts();
    } else {
        adc_t adcState = needAdc ? ADC_ON : ADC_OFF;
        LowPower.idle(period, adcState, TIMER2_ON, TIMER1_OFF, TIMER0_ON,
                      SPI_OFF, USART0_OFF, TWI_OFF);
    }
}
