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

void HourEditInit() {
    lastUpdate = millis();
    unsigned char sec;
    GetTime(&hour, &min, &sec);
}

void UpHour() {
    lastUpdate = millis();
    view = true;
    hour++;
    if (hour >= 24) {
        hour -= 24;
    }
    Buzzer();
}

void UpHourLong() {
    lastUpdate = millis();
    view = true;
    hour += 5;
    if (hour >= 24) {
        hour -= 24;
    }
}

void DowHour() {
    lastUpdate = millis();
    view = true;
    if (hour == 0) {
        hour = 23;
    }
    else {
        hour--;
    }
    Buzzer();
}

void DowHourLong() {
    lastUpdate = millis();
    view = true;
    if (hour < 5) {
        hour += 19;
    }
    else {
        hour -= 5;
    }
}

void SaveHour() {
    SetTime(hour, min);
    ChangState(MinEditInit, MinEditLoop);
}

void HourEditLoop() {
    unsigned long startTime = millis();

    static bool viewHour = false;
    static Timer timerView = {
        .leng = 500,
        .nextTime = 0,
    };

    static Button up = {
        .key = Key::k2,
        .click = false,
        .shortFn = UpHour,
        .longFn = UpHourLong,
        .time = startTime,
        .isLongPress = false,
    };

    static Button down = {
        .key = Key::k1,
        .click = false,
        .shortFn = DowHour,
        .longFn = DowHourLong,
        .time = startTime,
        .isLongPress = false,
    };

    static Button save = {
        .key = Key::k3,
        .click = false,
        .shortFn = SaveHour,
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
            ShowMin(min);
        }
    }

    if (lastUpdate + CANCLE_TIME <= startTime) {
        ChangState(ClockInit, ClockLoop);
    }

    delay(SLEEP_TIME - millis() + startTime);
}
