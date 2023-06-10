// #include "ClockShield.hpp"
// #include "HourEditState.hpp"
// #include "MinEditState.hpp"
// #include "ShowTimeState.hpp"
//
// State *showTimeState;
// State *hourEditState;
// State *minEditState;
// State *runningState;
//
// void setup() {
//  showTimeState = new ShowTimeState(runningState, hourEditState);
//  hourEditState = new HourEditState(runningState, minEditState);
//  minEditState = new MinEditState(runningState, showTimeState);
//  runningState = showTimeState;
// }
//
// void loop() { runningState->loop(); }

#include <Arduino.h>

#include "TTSDisplay.h"
#include "TTSTime.h"

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

TTSDisplay display;
TTSTime time;
long int runTime;
unsigned long delayTime;

bool stateKey3;
bool stateKey2;
bool stateKey1;

char editHour;

void (*on)();
void (*off)();

void setup() {
 pinMode(Key::K1, INPUT_PULLUP);
 pinMode(Key::K2, INPUT_PULLUP);
 pinMode(Key::K3, INPUT_PULLUP);

 pinMode(Led::LED1, OUTPUT);
 pinMode(Led::LED2, OUTPUT);
 pinMode(Led::LED3, OUTPUT);
 pinMode(Led::LED4, OUTPUT);

 runTime = millis();
 stateKey3 = false;
 delayTime = 250;

 on = []() {
  display.time(time.getHour(), time.getMin());
  display.pointOn();
 };
 off = []() { display.pointOff(); };
}

void loop() {
 if (digitalRead(Key::K3) == LOW) {
  stateKey3 = true;
  delayTime = 20;
 } else if (stateKey3) {
  stateKey3 = false;
  digitalWrite(Led::LED1, HIGH);
  editHour = time.getHour();
  on = []() {
   display.time(editHour, time.getMin());
   display.pointOn();
  };
  off = []() {
   display.pointOff();
   auto tmp = time.getMin();
   display.display(0, tmp % 10);
   display.display(1, tmp / 10);
   display.display(2, 0x7f);
   display.display(3, 0x7f);
  };
 }

 if (digitalRead(Key::K2) == LOW) {
  stateKey2 = true;
 } else if (stateKey2) {
  stateKey2 = false;
  editHour = ++editHour > 23 ? 0 : editHour;
 }

 if (digitalRead(Key::K1) == LOW && !stateKey1) {
  stateKey1 = true;
 } else if (stateKey1) {
  stateKey1 = false;
  editHour = --editHour < 0 ? 23 : editHour;
 }

 auto delta = millis() - runTime;
 if (delta > 1000) {
  off();
  runTime += 1000;
 } else if (delta > 500) {
  on();
 }
 delay(delayTime);
}
