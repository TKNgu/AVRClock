#include "ClockState.hpp"

#include <Arduino.h>

#include "../utils/LowPower.h"
#include "../utils/Utils.hpp"

ClockState::ClockState(StateManager2* manager)
    : State2(manager), clockEngine(), clockPoint(), clockChime(), clockLight() {
}

void ClockState::reload() {
    clockEngine.reload();
    clockChime.reload();
}

void ClockState::loop() {
    unsigned long now = millis();

    clockEngine.updateTime(now);
    ShowTime(clockEngine.hour, clockEngine.minutes);

    clockPoint.show(now);

    if (clockEngine.isUpdateMinute) {
        clockChime.check();
    }

    clockLight.check(now);

    LowPower.idle(SLEEP_500MS, ADC_ON, TIMER2_ON, TIMER1_OFF, TIMER0_ON,
                  SPI_OFF, USART0_OFF, TWI_OFF);
}
