#include "SleepState.hpp"

#include <Arduino.h>

#include "LowPower.h"
#include "StateManager.hpp"
#include "Utils.hpp"

#define LIGHT_LEVEL_SLEEP 20

static const unsigned int SLEEP_TIME_ON = (23 << 6) | 45;
static const unsigned int SLEEP_TIME_OFF = (05 << 6) | 00;

bool CheckTime(unsigned char hour, unsigned char minutes) {
    static unsigned int tmp;
    tmp = hour;
    tmp = (tmp << 6) | minutes;
    return tmp >= SLEEP_TIME_ON || tmp < SLEEP_TIME_OFF;
}

void SleepStateCheck(unsigned char hour, unsigned char minutes) {
    if (!CheckTime(hour, minutes)) {
        return;
    }
    LedBlink(led3);
    Buzzer();
    if (GetLight() < LIGHT_LEVEL_SLEEP) {
        LowPower.idle(SLEEP_2S, ADC_ON, TIMER2_ON, TIMER1_OFF, TIMER0_ON,
                      SPI_OFF, USART0_OFF, TWI_OFF);
        StateManagerSleepState();
    }
}

void SleepStateReload() {
    pinMode(13, OUTPUT);
    LedOff(led2);
    LedOff(led3);
    Clear();
    PointOff();
    BuzzerSilen();
}

void SleepStateLoop() {
    static bool isLedOn = false;
    digitalWrite(13, (isLedOn = !isLedOn) ? HIGH : LOW);
    if (ReadKey(KeyMenu)) {
        StateManagerStartState();
        return;
    }
    static unsigned char hour;
    static unsigned char minutes;
    GetClock(&hour, &minutes);
    if (!CheckTime(hour, minutes) || GetLight() >= LIGHT_LEVEL_SLEEP) {
        StateManagerStartState();
        return;
    }
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}
