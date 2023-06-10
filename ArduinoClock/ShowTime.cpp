#include "ShowTime.hpp"

ShowTime::ShowTime(State *&runningState, State *&nextState) : State(runningState, nextState) {
  pinMode(Key::K1, INPUT_PULLUP);
  pinMode(Key::K2, INPUT_PULLUP);
  pinMode(Key::K3, INPUT_PULLUP);

  pinMode(Led::LED1, OUTPUT);
  pinMode(Led::LED2, OUTPUT);
  pinMode(Led::LED3, OUTPUT);
  pinMode(Led::LED4, OUTPUT);
}

void ShowTime::resume() {
  State::resume();
  setDelayTime(250);
  on();
}

void ShowTime::input() {
  State::input();
  if (digitalRead(State::Key::K3) == LOW) {
    setDelayTime(20);
  }
}

void ShowTime::off() {
  display.pointOff();
}

void ShowTime::on() {
  display.time(time.getHour(),
               time.getMin());
  display.pointOn();
}
