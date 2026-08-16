#include "ClockState.hpp"

#include <Arduino.h>

#include "../utils/LowPower.h"
#include "../utils/Utils.hpp"

#define SLEEP_HOUR 23
#define SLEEP_MINUTE 45

#define WAKE_HOUR 5
#define WAKE_MINUTE 00

#define SLEEP_LIGHT_LEVEL 20

bool needSleep(unsigned char hour, unsigned char minutes) {
    const static unsigned int SLEEP_TIME = SLEEP_HOUR * 60 + SLEEP_MINUTE;
    const static unsigned int WAKE_TIME = WAKE_HOUR * 60 + WAKE_MINUTE;
    const unsigned int tmp = hour * 60 + minutes;
    return tmp >= SLEEP_TIME || tmp < WAKE_TIME;
}

ClockState::ClockState(StateManager2* manager)
    : State2(manager), clockEngine(), clockPoint(), clockChime(), clockLight(),
      buttonMenu(Key::KeyMenu), sleepTimer(CreateTimer(1000)) {}

void ClockState::reload() {
    clockEngine.reload();
    clockChime.reload();
    isNeedSleep = needSleep(clockEngine.hour, clockEngine.minutes);
}

void ClockState::loop() {
    unsigned long now = millis();

    clockEngine.updateTime(now);

    if (clockEngine.isUpdateMinute) {
        clockChime.check();
        isNeedSleep = needSleep(clockEngine.hour, clockEngine.minutes);
    }

    clockLight.check(now);
    if (clockEngine.isUpdateDay) {
        clockLight.updateGlobal();
    }

    if (buttonMenu.scan() == Button2::Click) {
        manager->nextState();
    }

    if (isNeedSleep) {
        if (GetLight() > SLEEP_LIGHT_LEVEL && TimerTimeout(&sleepTimer)) {
            Buzzer();
        }
        LowPower.idle(SLEEP_8S, ADC_ON, TIMER2_ON, TIMER1_OFF, TIMER0_ON,
                      SPI_OFF, USART0_OFF, TWI_OFF);
    } else {
        ShowTime(clockEngine.hour, clockEngine.minutes);
        clockPoint.show(now);
        LowPower.idle(SLEEP_500MS, ADC_ON, TIMER2_ON, TIMER1_OFF, TIMER0_ON,
                      SPI_OFF, USART0_OFF, TWI_OFF);
    }
}
