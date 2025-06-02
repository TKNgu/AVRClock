#include "ClockEdit.hpp"
#include <Arduino.h>

#include "Button.hpp"
#include "LowPower.h"
#include "StateManager.hpp"
#include "Timer.hpp"
#include "Utils.hpp"

#define CANCLE_TIME 5000

static unsigned char hour;
static unsigned char minutes;

static void (*UpCallback)(unsigned char value) = NULL;
static void (*DownCallback)(unsigned char value) = NULL;
static void (*BlinkCallback)() = NULL;

static bool blink;
static unsigned long lastUpdate;

void ClockEditReload() {
    lastUpdate = millis();
    GetClock(&hour, &minutes);
}

void Up() {
    lastUpdate = millis();
    blink = false;
    UpCallback(1);
    Buzzer();
}

void UpLong() {
    lastUpdate = millis();
    blink = false;
    UpCallback(5);
}

void Down() {
    lastUpdate = millis();
    blink = false;
    DownCallback(1);
    Buzzer();
}

void DownLong() {
    lastUpdate = millis();
    blink = false;
    DownCallback(5);
}

void Save() {
    SetTime(hour, minutes);
    StateManagerNextState();
}

void SaveSkip() {
    SetTime(hour, minutes);
    StateManagerStartState();
}

void ClockEditLoop() {
    static unsigned long now;
    now = millis();
    if (lastUpdate + CANCLE_TIME <= now) {
        StateManagerStartState();
    }

    static Button up = CreateButtonLongPress(Key::KeyUp, Up, UpLong);
    ButtonScan(&up);
    static Button down = CreateButtonLongPress(Key::KeyDown, Down, DownLong);
    ButtonScan(&down);
    static Button save = CreateButtonLongPress(Key::KeyMenu, Save, SaveSkip);
    ButtonScan(&save);

    static Timer timerView = CreateTimer(500);
    if (TimerTimeoutFix(&timerView, now)) {
        if (blink = !blink) {
            ShowTime(hour, minutes);
        } else {
            BlinkCallback();
        }
    }
    PointOn();

    LowPower.idle(SLEEP_500MS, ADC_OFF, TIMER2_ON, TIMER1_OFF, TIMER0_ON,
                  SPI_OFF, USART0_OFF, TWI_OFF);
}
