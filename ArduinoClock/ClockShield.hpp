#ifndef ClockShield_hpp
#define ClockShield_hpp

#include "src/TTSDisplay.h"
#include "src/TTSTemp.h"
#include "src/TTSTime.h"

#define BUZZER_DEVICE 6
#define BUZZER tone(BUZZER_DEVICE, 2400, 60);
// #define BUZZER

class ClockShield {
public:
 ClockShield();
 inline uchar getHour() { return this->time.getHour(); }
 inline uchar getMin() { return this->time.getMin(); }
 void getTime(uchar *hour, uchar *min, uchar *sec, uchar *dayOfWeek,
              uchar *dayOfMonth, uchar *month, uchar *year) {
  this->time.getTime(hour, min, sec, dayOfWeek, dayOfMonth, month, year);
 }
 inline void setTime(uchar hour, uchar min, uchar sec, uchar dayOfWeek,
                     uchar dayOfMonth, uchar month, uchar year) {
  this->time.setTime(hour, min, sec, dayOfWeek, dayOfMonth, month, year);
 }
 inline void setTime(uchar hour, uchar min, uchar sec) {
  this->time.setTime(hour, min, sec);
 }
 inline void show(uchar local, uchar data) {
  this->display.display(local, data);
 }
 inline void num(int num) { this->display.num(num); }
 inline void raw(uchar local, uchar data) { this->display.raw(local, data); }
 inline void showTime(uchar hour, uchar min) { this->display.time(hour, min); }
 inline void pointOn() { this->display.pointOn(); }
 inline void pointOff() { this->display.pointOff(); }
 inline void set(uchar level, uchar local = 0x40, uchar data = 0xc0) {
  this->display.set(level, local, data);
 }
 inline void clear() { this->display.clear(); }

 inline bool isMenu() { return digitalRead(Key::K3) == LOW; }
 inline int getTem() { return this->temp.get(); }
 inline bool digitalReadDown() { return digitalRead(Key::K1) == LOW; }
 inline bool digitalReadUp() { return digitalRead(Key::K2) == LOW; }

private:
 enum Key {
  K1 = 9,
  K2 = 10,
  K3 = 11,
 };

 enum Led {
  LED1 = 2,
  LED2 = 3,
  LED3 = 4,
  LED4 = 5,
 };

private:
 TTSDisplay display;
 TTSTime time;
 TTSTemp temp;
};

#endif
