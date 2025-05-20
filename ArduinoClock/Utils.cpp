#include "Utils.hpp"

#include "Arduino.h"
#include "TTSDisplay.h"
#include "TTSTemp.h"
#include "TTSTime.h"

#define LIGHT A1
#define BUZZER_DEVICE 6

static TTSDisplay display;
static TTSTime time;
static TTSTemp temp;

static int maxLevel = 0x00;
static int minLevel = 0xff;
static int rangeLevel = 0xffff;
static unsigned char lightLevel = 0x00;

void HardwareInit() {
  pinMode(Key::k1, INPUT_PULLUP);
  pinMode(Key::k2, INPUT_PULLUP);
  pinMode(Key::k3, INPUT_PULLUP);

  pinMode(Led::led1, OUTPUT);
  pinMode(Led::led2, OUTPUT);
  pinMode(Led::led3, OUTPUT);
  pinMode(Led::led4, OUTPUT);

  pinMode(BUZZER_DEVICE, OUTPUT);

  display.clear();
}

unsigned char GetDayOfWeek() {
  unsigned char tmp;
  unsigned char dayOfWeek;
  time.getTime(&tmp, &tmp, &tmp, &dayOfWeek, &tmp, &tmp, &tmp);
}

unsigned char GetHour() { return time.getHour(); }

unsigned char GetMin() { return time.getMin(); }

TimePoint GetTimePoint(TimePoint *now) {
  unsigned char hour;
  unsigned char min;
  unsigned char dayOfWeek;
  unsigned char tmp;
  time.getTime(&hour, &min, &tmp, &dayOfWeek, &tmp, &tmp, &tmp);
  InitTimePoint(now, dayOfWeek, hour, min);
}

void GetTime(unsigned char *hour, unsigned char *min, unsigned char *sec) {
  time.getTime(hour, min, sec);
}

void SetTime(const unsigned char hour, const unsigned char min) {
  time.setTime(hour, min, 0u);
}

void GetDateTime(unsigned char *hour, unsigned char *min, unsigned char *sec,
                 unsigned char *dayOfWeek, unsigned char *dayOfMonth,
                 unsigned char *month, unsigned char *year) {
  time.getTime(hour, min, sec, dayOfWeek, dayOfMonth, month, year);
}

void SetDateTime(const unsigned char hour, const unsigned char min,
                 const unsigned char sec, const unsigned char dayOfWeek,
                 const unsigned char dayOfMonth, const unsigned char month,
                 const unsigned char year) {

  time.setTime(hour, min, sec, dayOfWeek, dayOfMonth, month, year);
}

void GetDayOfWeek(unsigned char *dayOfWeek) {
  const char tmp;
  time.getTime(&tmp, &tmp, &tmp, dayOfWeek, &tmp, &tmp, &tmp);
}

void SetDayOfWeek(const unsigned char dayOfWeek) {
  unsigned char hour, min, sec;
  unsigned char dayOfMonth, month, year;
  unsigned char tmp;

  time.getTime(&hour, &min, &sec, &tmp, &dayOfMonth, &month, &year);
  time.setTime(hour, min, sec, dayOfWeek, dayOfMonth, month, year);
}

void Clear() { display.clear(); }

void SetLightLevel(unsigned char level) { display.set(level, 0x40, 0xc0); }

void ShowTime(unsigned char hour, unsigned char min) {
  display.time(hour, min);
}

void PointOn() { display.pointOn(); }

void PointOff() { display.pointOff(); }

void ShowTemperature(int temperature) {
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

void Buzzer() { tone(BUZZER_DEVICE, 2400, 60); }

int GetTem() { return temp.get(); }

int GetLight() { return analogRead(LIGHT); }

void AutoLight() {
  int light = GetLight();
  if (light < minLevel) {
    minLevel = light;
  }
  if (light > maxLevel) {
    maxLevel = light;
  }
  unsigned char tmp =
      (unsigned char)((light - minLevel) * 7.0f / (maxLevel - minLevel));
  if (tmp != lightLevel) {
    lightLevel = tmp;
    SetLightLevel(lightLevel);
  }
}
