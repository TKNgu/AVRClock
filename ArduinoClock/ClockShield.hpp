#ifndef ClockShield_hpp
#define ClockShield_hpp

#include "src/lib/TTSDisplay.h"
#include "src/lib/TTSTemp.h"
#include "src/lib/TTSTime.h"

#define BUZZER_DEVICE 6

class ClockShield {
public:
 ClockShield();

 // Time
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

 // Led 7 segment
 inline void raw(uchar local, uchar data) { this->display.raw(local, data); }
 inline void show(uchar local, uchar data) {
  this->display.display(local, data);
 }
 inline void pointOn() { this->display.pointOn(); }
 inline void pointOff() { this->display.pointOff(); }
 inline void num(int num) { this->display.num(num); }
 inline void showTime(uchar hour, uchar min) { this->display.time(hour, min); }
 inline void set(uchar level, uchar local = 0x40, uchar data = 0xc0) {
  this->display.set(level, local, data);
 }
 inline void clear() { this->display.clear(); }

 // Button
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
