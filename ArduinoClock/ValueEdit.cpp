#include "ValueEdit.hpp"

#define TIME_OUT_SPEED_CHANG 500
#define SPEED_CHANG 250

bool ValueEdit::stateKey1 = false;
unsigned long ValueEdit::timeOutKey1 = 0;
bool ValueEdit::stateKey2 = false;
unsigned long ValueEdit::timeOutKey2 = 0;

#define CHECK_KEY(KEY, STATE, TIME_OUT, TIME_NOW, CALLBACK) \
  if (digitalRead(KEY) == LOW) {                            \
    if (!STATE) {                                           \
      TIME_OUT = TIME_NOW + TIME_OUT_SPEED_CHANG;           \
    }                                                       \
    if (TIME_OUT < TIME_NOW) {                              \
      CALLBACK;                                             \
      TIME_OUT = TIME_NOW + SPEED_CHANG;                    \
    }                                                       \
    STATE = true;                                           \
  } else if (STATE) {                                       \
    STATE = false;                                          \
    CALLBACK;                                               \
  }

void ValueEdit::input(unsigned long timeNow) {
  State::input(timeNow);
  CHECK_KEY(State::Key::K1, stateKey1, timeOutKey1, timeNow, down());
  CHECK_KEY(State::Key::K2, stateKey2, timeOutKey2, timeNow, up());
}
