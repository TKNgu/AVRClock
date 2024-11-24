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

void HourEditReload() {
    lastUpdate = millis();
    unsigned char sec;
    GetTime(&hour, &min, &sec);
    Buzzer();
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
    unsigned char tmp;
    GetTime(&tmp, &min, &tmp);
    SetTime(hour, min);
    ChangState(MinEditReload, MinEditLoop);
    Buzzer();
}

void SaveHourSkip() {
    unsigned char tmp;
    GetTime(&tmp, &min, &tmp);
    SetTime(hour, min);
    ChangState(ClockReload, ClockLoop);
    Buzzer();
}

void HourEditLoop() {
    unsigned long startTime = millis();

    static Button up = CreateButtonLongPress(Key::k2, UpHour, UpHourLong);
    ButtonScan(&up);

    static Button down = CreateButtonLongPress(Key::k1, DowHour, DowHourLong);
    ButtonScan(&down);

    static Button save = CreateButton(Key::k3, SaveHour);
    ButtonScan(&save);

    static Timer timerView = CreateTimer(500);
    if (TimerTimeoutFix(&timerView, startTime)) {
        static bool viewHour = false;
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
        ChangState(ClockReload, ClockLoop);
    }

    delay(SLEEP_TIME - millis() + startTime);
}
