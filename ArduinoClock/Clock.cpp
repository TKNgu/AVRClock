#include "Clock.hpp"

#include <stdbool.h>

#include "TimePoint.hpp"
#include "Arduino.h"
#include "Utils.hpp"
#include "Timer.hpp"
#include "Button.hpp"

#define SLEEP_TIME 50
#define SCHEDULE_SIZE 28
#define TIME_VIEW_TEMP 2000
#define TIME_VIEW_TIME 7000

static TimePoint schedule[SCHEDULE_SIZE];
static size_t indexSchedule;
static TimePoint nextTimePoint;

void (*StateLoop)(void) = ClockLoop;
void ChangState(void (*reload)(void), void (*loop)(void)) {
    reload();
    StateLoop = loop;
}

void ClockInit() {
    size_t offset = 0;
    for (unsigned char dayOfWeek = 1; dayOfWeek <= 7; dayOfWeek++) {
        InitTimePoint(schedule + offset, dayOfWeek, 7, 30);
        offset++;
        InitTimePoint(schedule + offset, dayOfWeek, 8, 00);
        offset++;
        InitTimePoint(schedule + offset, dayOfWeek, 8, 10);
        offset++;
        InitTimePoint(schedule + offset, dayOfWeek, 23, 00);
        offset++;
    }
}

void ClockReload() {
    TimePoint now;
    GetTimePoint(&now);
    for (indexSchedule = 0; indexSchedule < SCHEDULE_SIZE; indexSchedule++) {
        if (schedule[indexSchedule] > now) {
            break;
        }
    }
    indexSchedule %= SCHEDULE_SIZE;
    nextTimePoint = schedule[indexSchedule];
    Buzzer();
}

typedef enum StateView {
    viewTemp,
    viewTime,
    sleep,
};

void MenuClick() {
    ChangState(HourEditReload, HourEditLoop);
}

void ClockShowTime(const unsigned char hour, const unsigned char min, const unsigned long startTime) {
    static Timer timerPoint = CreateTimer(750);
    static bool needShowPoint = false;
    if (TimerTimeoutFix(&timerPoint, startTime)) {
        needShowPoint = !needShowPoint;
    }

    ShowTime(hour, min);
    needShowPoint ? PointOn() : PointOff();
}


void ClockLoop() {
    unsigned long startTime = millis();

    static Button menuButton = CreateButton(Key::k3, MenuClick);
    ButtonScan(&menuButton);

    static Timer timerAutoLight = CreateTimer(5000);
    if (TimerTimeoutFix(&timerAutoLight, startTime)) {
        AutoLight();
    }

    static Timer timerCheckSchedule = CreateTimer(30);
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
 
    static Timer timerUpdateTime = CreateTimer(900);
    static unsigned char hour;
    static unsigned char min;
    static unsigned char sec;
    if (TimerTimeoutFix(&timerUpdateTime, startTime)) {
        GetTime(&hour, &min, &sec);
    }

    static Timer timerCheckTemp = CreateTimer(10);
    static int temp;
    if (TimerTimeoutFix(&timerCheckTemp, startTime)) {
        temp = GetTem();
    }

    static StateView stateView = StateView::viewTime;
    if (hour < 5) {
        stateView = StateView::sleep;
        Clear();
        PointOff();
    }
    else if (temp <= 15 || temp >= 30) {
        static unsigned long nextShowTime = 0;
        if (nextShowTime < startTime) {
            static bool isShowTemp = false;
            isShowTemp = !isShowTemp;
            if (isShowTemp) {
                nextShowTime = startTime + TIME_VIEW_TIME;
                stateView = StateView::viewTime;
            }
            else {
                nextShowTime = startTime + TIME_VIEW_TEMP;
                stateView = StateView::viewTemp;
                PointOff();
            }
        }
    }
    else {
        stateView = StateView::viewTime;
    }

    switch (stateView) {
        case StateView::viewTime:
            ClockShowTime(hour, min, startTime);
        break;
        case StateView::viewTemp:
            ShowTemperature(temp);
        break;
        case StateView::sleep:
        default:
            break;
    }

    delay(SLEEP_TIME - millis() + startTime);
}
