#include "MinutesEdit.hpp"
#include <Arduino.h>

#include "Button.hpp"
#include "StateManager.hpp"
#include "Timer.hpp"
#include "Utils.hpp"

#define SLEEP_TIME 50
#define CANCLE_TIME 5000

static unsigned char hour;
static unsigned char min;
static bool view;
static unsigned long lastUpdate;

void MinutesEditReload() {
    lastUpdate = millis();
    unsigned char sec;
    GetTime(&hour, &min, &sec);
    Buzzer();
}

void UpMin() {
    lastUpdate = millis();
    view = true;
    min++;
    if (min >= 60) {
        min -= 60;
    }
    Buzzer();
}

void UpMinLong() {
    lastUpdate = millis();
    view = true;
    min += 5;
    if (min >= 60) {
        min -= 60;
    }
}

void DowMin() {
    lastUpdate = millis();
    view = true;
    if (min == 0) {
        min = 59;
    } else {
        min--;
    }
    Buzzer();
}

void DowMinLong() {
    lastUpdate = millis();
    view = true;
    if (min < 5) {
        min += 55;
    } else {
        min -= 5;
    }
}

void SaveMin() {
    SetTime(hour, min);
    StateManagerNextState();
}

void SaveMinSkip() {
    SetTime(hour, min);
    StateManagerStartState();
}

void MinutesEditLoop() {
    unsigned long startTime = millis();

    static bool viewHour = false;
    static Timer timerView = CreateTimer(500);
    static Button up = CreateButtonLongPress(Key::k2, UpMin, UpMinLong);
    static Button down = CreateButtonLongPress(Key::k1, DowMin, DowMinLong);
    static Button save = CreateButtonLongPress(Key::k3, SaveMin, SaveMinSkip);

    ButtonScan(&up);
    ButtonScan(&down);
    ButtonScan(&save);

    if (TimerTimeoutFix(&timerView, startTime)) {
        viewHour = !viewHour;
        if (view) {
            view = false;
            ShowTime(hour, min);
        } else if (viewHour) {
            Clear();
            ShowTime(hour, min);
        } else {
            Clear();
            ShowHour(hour);
        }
    }

    if (lastUpdate + CANCLE_TIME <= startTime) {
        StateManagerStartState();
    }

    delay(SLEEP_TIME - millis() + startTime);
}
