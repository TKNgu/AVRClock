#include "Clock.hpp"

#include "Timer.hpp"
#include "Arduino.h"
#include "Utils.hpp"
#include "Button.hpp"

#define SLEEP_TIME 50
#define CANCLE_TIME 5000

static unsigned char hour;
static unsigned char min;
static bool view;
static unsigned long lastUpdate;

void MinEditInit() {
    lastUpdate = millis();
    unsigned char sec;
    GetTime(&hour, &min, &sec);
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
    }
    else {
        min--;
    }
    Buzzer();
}

void DowMinLong() {
    lastUpdate = millis();
    view = true;
    if (min < 5) {
        min += 55;
    }
    else {
        min -= 5;
    }
}

void SaveMin() {
    SetTime(hour, min);
    ChangState(ClockInit, ClockLoop);
}

void MinEditLoop() {
    unsigned long startTime = millis();

    static bool viewHour = false;
    static Timer timerView = {
        .leng = 500,
        .nextTime = 0,
    };

    static Button up = {
        .key = Key::k2,
        .click = false,
        .shortFn = UpMin,
        .longFn = UpMinLong,
        .time = startTime,
        .isLongPress = false,
    };

    static Button down = {
        .key = Key::k1,
        .click = false,
        .shortFn = DowMin,
        .longFn = DowMinLong,
        .time = startTime,
        .isLongPress = false,
    };

    static Button save = {
        .key = Key::k3,
        .click = false,
        .shortFn = SaveMin,
        .longFn = NOP,
        .time = startTime,
        .isLongPress = false,
    };

    ButtonScan(&up);
    ButtonScan(&down);
    ButtonScan(&save);

    if (TimerTimeoutFix(&timerView, startTime)) {
        viewHour = !viewHour;
        if (view) {
            view = false;
            ShowTime(hour, min);
        }
        else if (viewHour) {
            Clear();
            ShowTime(hour, min);
        }
        else {
            Clear();
            ShowHour(hour);
        }
    }

    if (lastUpdate + CANCLE_TIME <= startTime) {
        ChangState(ClockInit, ClockLoop);
    }

    delay(SLEEP_TIME - millis() + startTime);
}
