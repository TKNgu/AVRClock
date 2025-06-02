#include "Clock.hpp"
#include <Arduino.h>

#include "Button.hpp"
#include "KamaFilter.h"
#include "LowPower.h"
#include "StateManager.hpp"
#include "TimePoint.hpp"
#include "Timer.hpp"
#include "Utils.hpp"

#define HOURLY_CHIME_TASK 50000
#define HOURLY_CHIME_SIZE 28
#define CHECK_LIGHT_TASK 2000
#define CHECK_TEMPERATURE_TASK 5000
#define SHOW_TEMPERATURE_LONG 10000
#define KEEP_TEMPERATURE_TIMEOUT 3000
#define MIN_TEMPERATURE 10
#define MAX_TEMPERATURE 32
#define UPDATE_TIME_TASK 1000
#define TIME_POIT_TASK 500

#define LIGHT_LEVEL_WARNING 17
#define LIGHT_LEVEL_SLEEP 1

static TimePoint hourlyChime[HOURLY_CHIME_SIZE];
static unsigned char indexTimePoint;
static TimePoint nextTimePoint;
static unsigned char hour;
static unsigned char minutes;
static bool showTemperature = true;
static bool isEnableLightWarning = true;

static void (*GetTimeCallback)(unsigned char hour,
                               unsigned char minutes) = NULL;

int ClockInit() {
    unsigned char offset = 0;
    for (unsigned char dayOfWeek = 1; dayOfWeek <= 7; dayOfWeek++) {
        TimePointInit(hourlyChime + offset++, dayOfWeek, 7, 00);
        TimePointInit(hourlyChime + offset++, dayOfWeek, 7, 30);
        TimePointInit(hourlyChime + offset++, dayOfWeek, 22, 00);
        TimePointInit(hourlyChime + offset++, dayOfWeek, 23, 30);
    }
    return 0;
}

void ClockReload() {
    GetClock(&hour, &minutes);
    TimePoint timePoint;
    GetTimePoint(&timePoint);
    for (indexTimePoint = 0; indexTimePoint < HOURLY_CHIME_SIZE;
         indexTimePoint++) {
        if (hourlyChime[indexTimePoint] == timePoint) {
            Buzzer();
            indexTimePoint++;
            break;
        }
        if (hourlyChime[indexTimePoint] > timePoint) {
            break;
        }
    }
    indexTimePoint %= HOURLY_CHIME_SIZE;
    nextTimePoint = hourlyChime[indexTimePoint];
    isEnableLightWarning = true;
    GetTimeCallback ? GetTimeCallback(hour, minutes) : (void)0;
}

void ChangShowTemperature() { showTemperature = true; }

void StopLightLevelWarning() { isEnableLightWarning = false; }

void ClockShow() {
    static unsigned long now;
    now = millis();

    static struct Button buttonMenu =
        CreateButton(Key::KeyMenu, StateManagerNextState);
    ButtonScan(&buttonMenu);

    static Button up = CreateButton(Key::KeyUp, ChangShowTemperature);
    ButtonScan(&up);

    static Button down = CreateButton(Key::KeyDown, StopLightLevelWarning);
    ButtonScan(&down);

    static struct Timer timerHourlyChime = CreateTimer(HOURLY_CHIME_TASK);
    if (TimerTimeoutFix(&timerHourlyChime, now)) {
        static TimePoint timePoint;
        GetTimePoint(&timePoint);
        if (timePoint == nextTimePoint) {
            indexTimePoint = (++indexTimePoint % HOURLY_CHIME_SIZE);
            nextTimePoint = hourlyChime[indexTimePoint];
            Buzzer();
        }
    }

    static struct Timer timerAutoLight = CreateTimer(CHECK_LIGHT_TASK);
    if (TimerTimeoutFix(&timerAutoLight, now)) {
        static float lightLevel;
        (GetLight() < LIGHT_LEVEL_WARNING && isEnableLightWarning)
            ? LedOn(led2)
            : LedOff(led2);
        AutoLight();
    }

    static unsigned long timeOutA = 0;
    static unsigned long timeOutB = 0;
    static int temperature = 0;
    if (timeOutA < now) {
        static struct Timer timerGetTemperature =
            CreateTimer(CHECK_TEMPERATURE_TASK);
        if (TimerTimeoutFix(&timerGetTemperature, now)) {
            temperature = GetTemperature();
            showTemperature = temperature <= MIN_TEMPERATURE ||
                              temperature >= MAX_TEMPERATURE;
        }
        if (showTemperature) {
            timeOutA = now + SHOW_TEMPERATURE_LONG;
            timeOutB = now + KEEP_TEMPERATURE_TIMEOUT;
        }
    } else {
        showTemperature = timeOutB >= now;
    }

    if (showTemperature) {
        Clear();
        ShowTemperature(temperature);
    } else {
        ShowTime(hour, minutes);
        static struct Timer timerShowPoint = CreateTimer(TIME_POIT_TASK);
        if (TimerTimeoutFix(&timerShowPoint, now)) {
            static bool showTimePoint = false;
            (showTimePoint = !showTimePoint) ? PointOn() : PointOff();
        }

        static struct Timer timerUpdateTime = CreateTimer(UPDATE_TIME_TASK);
        if (TimerTimeoutFix(&timerUpdateTime, now)) {
            GetClock(&hour, &minutes);
            GetTimeCallback ? GetTimeCallback(hour, minutes) : (void)0;
        }
    }

    LowPower.idle(SLEEP_500MS, ADC_ON, TIMER2_ON, TIMER1_OFF, TIMER0_ON,
                  SPI_OFF, USART0_OFF, TWI_OFF);
}
