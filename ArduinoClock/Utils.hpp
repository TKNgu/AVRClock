#ifndef Utils_hpp
#define Utils_hpp

#include "TimePoint.hpp"

void HardwareInit();

// RTC
void GetClock(unsigned char *hour, unsigned char *min);

// Led
void PointOn();
void PointOff();

void ShowTime(unsigned char hour, unsigned char min);

// Key
typedef enum {
    k1 = 9,
    k2 = 10,
    k3 = 11,
} Key;

bool ReadKey(const Key key);

// Led
typedef enum {
    led1 = 2,
    led2 = 3,
    led3 = 4,
    led4 = 5,
} Led;

void LedOn(const Led led);
void LedOff(const Led led);
void AutoLight();
void ShowTemperature(int temperature);

// Buzzer
void Buzzer();

// Sensor
int GetLight();
int GetTemperature();

// Update version

unsigned char GetDayOfWeek();
unsigned char GetHour();
unsigned char GetMin();
TimePoint GetTimePoint(TimePoint *now);
void GetTime(unsigned char *hour, unsigned char *min, unsigned char *sec);
void SetTime(const unsigned char hour, const unsigned char min);
void GetDateTime(unsigned char *hour, unsigned char *min, unsigned char *sec,
    unsigned char *dayOfWeek,
    unsigned char *dayOfMonth, unsigned char *month, unsigned char *year);
void SetDateTime(const unsigned char hour, const unsigned char min, const unsigned char sec,
    const unsigned char dayOfWeek,
    const unsigned char dayOfMonth, const unsigned char month, const unsigned char year);
void GetDayOfWeek(unsigned char *dayOfWeek);
void SetDayOfWeek(const unsigned char dayOfWeek);

void Clear();
void SetLightLevel(unsigned char level);
void ShowDayOfWeek(const unsigned char dayOfWeek);
void ShowHour(const unsigned char hour);
void ShowMin(const unsigned char min);
void ShowNum(int num);

int GetTem();


#endif
