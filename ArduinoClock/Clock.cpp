#include "Clock.hpp"

#include <stdbool.h>

#include "TimePoint.hpp"
#include "Arduino.h"
#include "Utils.hpp"
#include "Timer.hpp"
#include "Button.hpp"


void ChangState(void (*init)(void), void (*loop)(void)) {
    init();
    StateLoop = loop;
    Buzzer();
}

#define SLEEP_TIME 50
#define SCHEDULE_SIZE 14
#define TIME_VIEW_TEMP 2000
#define TIME_VIEW_TIME 7000

static Timer timerCheckSchedule = {
    .leng = 60,
    .nextTime = 0,
};
static TimePoint schedule[SCHEDULE_SIZE];
static size_t indexSchedule;
static TimePoint nextTimePoint;
static unsigned lastMin;

static Timer timerCheckTemp = {
    .leng = 10,
    .nextTime = 0,
};
static int temp;
static bool needShowTemp;

static Timer timerPoint = {
    .leng = 750,
    .nextTime = 0,
};
static bool needShowPoint = false;

static Timer timerUpdateTime = {
    .leng = 1000,
    .nextTime = 0,
};
static unsigned char hour;
static unsigned char min;
static unsigned char sec;

static Timer timerAutoLight = {
    .leng = 5000,
    .nextTime = 0,
};

typedef enum StateView {
    viewTemp,
    viewTime,
};
static StateView stateView = StateView::viewTime;
static unsigned long timerStateView = 0;

void MenuClick() {
    ChangState(HourEditInit, HourEditLoop);
}

static Button menuButton = {
    .key = Key::k3,
    .click = false,
    .shortFn = MenuClick,
    .longFn = NOP,
    .time = 0,
    .isLongPress = false,
};

void (*StateLoop)(void) = ClockLoop;

void ClockInit() {
    size_t offset = 0;
    for (unsigned char dayOfWeek = 1; dayOfWeek <= 7; dayOfWeek++) {
        InitTimePoint(schedule + offset, dayOfWeek, 7, 30);
        offset++;
        InitTimePoint(schedule + offset, dayOfWeek, 23, 00);
        offset++;
    }
    TimePoint now;
    GetTimePoint(&now);
    lastMin = GetMin();
    for (indexSchedule = 0; indexSchedule < SCHEDULE_SIZE; indexSchedule++) {
        if (schedule[indexSchedule] > now) {
            break;
        }
    }
    indexSchedule %= SCHEDULE_SIZE;
    nextTimePoint = schedule[indexSchedule];
}

void ClockLoop() {
    unsigned long startTime = millis();

    if (TimerTimeoutFix(&timerCheckSchedule, startTime)) {
        TimePoint now;
        GetTimePoint(&now);
        if (now == nextTimePoint) {
            indexSchedule++;
            indexSchedule %= SCHEDULE_SIZE;
            nextTimePoint = schedule[indexSchedule];
            Buzzer();
        }
    }

    if (TimerTimeoutFix(&timerPoint, startTime)) {
        needShowPoint = !needShowPoint;
    }
    
    if (TimerTimeoutFix(&timerUpdateTime, startTime)) {
        GetTime(&hour, &min, &sec);
    }

    if (TimerTimeoutFix(&timerAutoLight, startTime)) {
        AutoLight();
    }

    if (TimerTimeoutFix(&timerCheckTemp, startTime)) {
        temp = GetTem();
        if (temp < 15 || temp > 32) {
            needShowTemp = true;
        }
    }

    ButtonScan(&menuButton);

    if (needShowTemp || stateView == StateView::viewTemp) {
        if (timerStateView <= startTime) {
            switch (stateView) {
                case StateView::viewTime:
                    stateView = StateView::viewTemp;
                    timerStateView = startTime + TIME_VIEW_TEMP;
                    needShowPoint = false;
                    PointOff();
                    break;
                case StateView::viewTemp:
                default:
                    stateView = StateView::viewTime;
                    timerStateView = startTime + TIME_VIEW_TIME;
                    break;
            }
        }
    }

    switch (stateView) {
        case StateView::viewTemp:
            ShowTemperature(temp);
            break;
        case StateView::viewTime:
        default:
            ShowTime(hour, min);
            needShowPoint ? PointOn() : PointOff();
            break;
    }

    delay(SLEEP_TIME - millis() + startTime);
}
