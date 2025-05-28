#include "HourEdit.hpp"
#include <Arduino.h>

#include "Button.hpp"
#include "StateManager.hpp"
#include "Timer.hpp"
#include "Utils.hpp"

#define SLEEP_TIME 10
#define HOUR_BLINK 750
#define CANCLE_TIME 5000

static unsigned char hour;
static unsigned char minutes;
static bool hourBlink = false;
static unsigned long lastUpdate;

void HourEditReload() {
    lastUpdate = millis();
    GetClock(&hour, &minutes); }

void UpHour() {
    lastUpdate = millis();
    hourBlink = false;
    hour++;
    if (hour >= 24) {
        hour -= 24;
    }
    Buzzer();
}

void UpHourLong() {
    lastUpdate = millis();
    hourBlink = false;
    hour += 5;
    if (hour >= 24) {
        hour -= 24;
    }
}

void DowHour() {
    lastUpdate = millis();
    hourBlink = false;
    if (hour == 0) {
        hour = 23;
    } else {
        hour--;
    }
    Buzzer();
}

void DowHourLong() {
    lastUpdate = millis();
    hourBlink = false;
    if (hour < 5) {
        hour += 19;
    } else {
        hour -= 5;
    }
}

void Save() {
    unsigned char tmp;
    GetTime(&tmp, &minutes, &tmp);
    SetTime(hour, minutes);
}

void SaveHour() {
    Save();
    StateManagerNextState();
}

void SaveHourSkip() {
    Save();
    StateManagerStartState();
}

void HourEditShow() {
    static unsigned long now;
    now = millis();

    if (lastUpdate + CANCLE_TIME <= now) {
        StateManagerStartState();
    }

    static Button up = CreateButtonLongPress(Key::k2, UpHour, UpHourLong);
    ButtonScan(&up);

    static Button down = CreateButtonLongPress(Key::k1, DowHour, DowHourLong);
    ButtonScan(&down);

    static Button save = CreateButtonLongPress(Key::k3, SaveHour, SaveHourSkip);
    ButtonScan(&save);

    static Timer timerHourBlink = CreateTimer(HOUR_BLINK);
    if (TimerTimeoutFix(&timerHourBlink, now)) {
        if (hourBlink = !hourBlink) {
            ShowTime(hour, minutes);
        } else {
            Clear();
            ShowMin(minutes);
        }
    }

    static unsigned long end;
    end = millis();
    if (now + SLEEP_TIME > end) {
        delay(SLEEP_TIME + now - end);
    }
}
