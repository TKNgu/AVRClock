#ifndef Utils_hpp
#define Utils_hpp

#include "TimePoint.hpp"

typedef enum {
    k1 = 9,
    k2 = 10,
    k3 = 11,
} Key;

typedef enum {
    led1 = 2,
    led2 = 3,
    led3 = 4,
    led4 = 5,
} Led;

void HardwareInit();

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
void ShowTime(unsigned char hour, unsigned char min);
void PointOn();
void PointOff();
void ShowTemperature(int temperature);
void ShowDayOfWeek(const unsigned char dayOfWeek);
void ShowHour(const unsigned char hour);
void ShowMin(const unsigned char min);
void ShowNum(int num);

bool ReadKey(const Key key);
void LedOn(const Led led);
void LedOff(const Led led);
void Buzzer();

int GetTem();
int GetLight();

void AutoLight();

#endif
