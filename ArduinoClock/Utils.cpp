#include "Utils.hpp"

#include <Arduino.h>
#include <EEPROM.h>

#include "KamaFilter.h"
#include "TTSDisplay.h"
#include "TTSTemp.h"
#include "TTSTime.h"

#define LIGHT A1
#define BUZZER_DEVICE 6

static TTSDisplay display;
static TTSTime time;
static TTSTemp temp;
static KamaFilter temperatureFilter;

static float maxLevel = 0x00;
static float minLevel = 0xff;
static int rangeLevel = 0xffff;
static unsigned char lightLevel = 0x00;
static KamaFilter lightFilter;

void ReadLighLevel() {
    float tmpMin;
    EEPROM.get(0, tmpMin);
    if (tmpMin <= minLevel) {
        minLevel = tmpMin;
    }
    float tmpMax;
    EEPROM.get(4, tmpMax);
    if (tmpMax >= maxLevel) {
        maxLevel = tmpMax;
    }
}

void HardwareInit() {
    ReadLighLevel();

    pinMode(Key::KeyDown, INPUT_PULLUP);
    pinMode(Key::KeyUp, INPUT_PULLUP);
    pinMode(Key::KeyMenu, INPUT_PULLUP);

    pinMode(Led::led1, OUTPUT);
    pinMode(Led::led2, OUTPUT);
    pinMode(Led::led3, OUTPUT);
    pinMode(Led::led4, OUTPUT);

    pinMode(BUZZER_DEVICE, OUTPUT);

    lightFilter.begin(analogRead(LIGHT));
    temperatureFilter.begin(temp.get());

    display.clear();
}

void GetClock(unsigned char* hour, unsigned char* min) {
    static unsigned char sec;
    time.getTime(hour, min, &sec);
}

void PointOn() { display.pointOn(); }

void PointOff() { display.pointOff(); }

/////////////////

unsigned char GetDayOfWeek() {
    static unsigned char tmp;
    static unsigned char dayOfWeek;
    time.getTime(&tmp, &tmp, &tmp, &dayOfWeek, &tmp, &tmp, &tmp);
}

unsigned char GetHour() { return time.getHour(); }

unsigned char GetMin() { return time.getMin(); }

TimePoint GetTimePoint(TimePoint* now) {
    static unsigned char hour;
    static unsigned char min;
    static unsigned char dayOfWeek;
    static unsigned char tmp;
    time.getTime(&hour, &min, &tmp, &dayOfWeek, &tmp, &tmp, &tmp);
    TimePointInit(now, dayOfWeek, hour, min);
}

void GetTime(unsigned char* hour, unsigned char* min, unsigned char* sec) {
    time.getTime(hour, min, sec);
}

void SetTime(const unsigned char hour, const unsigned char min) {
    time.setTime(hour, min, 0u);
}

void GetDateTime(unsigned char* hour, unsigned char* min, unsigned char* sec,
                 unsigned char* dayOfWeek, unsigned char* dayOfMonth,
                 unsigned char* month, unsigned char* year) {
    time.getTime(hour, min, sec, dayOfWeek, dayOfMonth, month, year);
}

void SetDateTime(const unsigned char hour, const unsigned char min,
                 const unsigned char sec, const unsigned char dayOfWeek,
                 const unsigned char dayOfMonth, const unsigned char month,
                 const unsigned char year) {

    time.setTime(hour, min, sec, dayOfWeek, dayOfMonth, month, year);
}

void GetDayOfWeek(unsigned char* dayOfWeek) {
    static char tmp;
    time.getTime(&tmp, &tmp, &tmp, dayOfWeek, &tmp, &tmp, &tmp);
}

void SetDayOfWeek(const unsigned char dayOfWeek) {
    static unsigned char hour, min, sec;
    static unsigned char dayOfMonth, month, year;
    static unsigned char tmp;

    time.getTime(&hour, &min, &sec, &tmp, &dayOfMonth, &month, &year);
    time.setTime(hour, min, sec, dayOfWeek, dayOfMonth, month, year);
}

void Clear() { display.clear(); }

void SetLightLevel(unsigned char level) { display.set(level, 0x40, 0xc0); }

void ShowTime(unsigned char hour, unsigned char min) {
    display.time(hour, min);
}

void ShowTemperature(int temperature) {
    display.pointOff();
    display.raw(0, 0b00111001);
    display.raw(1, 0b01100011);
    display.display(2, temperature % 10);
    display.display(3, temperature / 10);
}

void ShowDayOfWeek(const unsigned char dayOfWeek) {
    if (dayOfWeek == 1) {
        display.raw(0, 0b00110111);
        display.raw(1, 0b00111110);
        display.raw(2, 0b01101101);
        display.raw(3, 0x00);
    } else {
        display.num(dayOfWeek);
    }
}

void ShowHour(const unsigned char hour) {
    display.display(0, 0x7f);
    display.display(1, 0x7f);
    display.display(2, hour % 10);
    display.display(3, hour / 10);
}

void ShowMin(const unsigned char min) {
    display.display(0, min % 10);
    display.display(1, min / 10);
    display.display(2, 0x7f);
    display.display(3, 0x7f);
}

void ShowNum(int num) { display.num(num); }

bool ReadKey(const Key key) { return digitalRead(key) == LOW; }

void LedOn(const Led led) { digitalWrite(led, HIGH); }

void LedOff(const Led led) { digitalWrite(led, LOW); }

void LedBlink(const Led led) {
    static bool isBlink = true;
    (isBlink = !isBlink) ? LedOn(led) : LedOff(led);
}

void Buzzer() { tone(BUZZER_DEVICE, 2400, 60); }
void BuzzerSilen() { noTone(BUZZER_DEVICE); }

int GetTemperature() {
    temperatureFilter.update(temp.get());
    return temperatureFilter.getValue();
}

int GetLight() {
    lightFilter.update(analogRead(LIGHT));
    return lightFilter.getValue();
}

void AutoLight() {
    static int light;
    light = GetLight();
    if (light < minLevel) {
        minLevel = light;
        EEPROM.put(0, minLevel);
    }
    if (light > maxLevel) {
        maxLevel = light;
        EEPROM.put(4, maxLevel);
    }
    static unsigned char tmp;
    tmp = (unsigned char)((light - minLevel) * 7.0f / (maxLevel - minLevel));
    if (tmp != lightLevel) {
        lightLevel = tmp;
        SetLightLevel(lightLevel);
    }
}
