#include "ValueEdit.hpp"

#define TIME_OUT_SPEED_CHANG 500
#define SPEED_CHANG 250

bool ValueEdit::stateKey1 = false;
long int ValueEdit::timeOutKey1 = 0;
bool ValueEdit::stateKey2 = false;
long int ValueEdit::timeOutKey2 = 0;

#define CHECK_KEY(KEY, STATE, TIME_OUT, CALLBACK) \
  if (digitalRead(KEY) == LOW) {                  \
    if (!STATE) {                                 \
      TIME_OUT = millis() + TIME_OUT_SPEED_CHANG; \
    }                                             \
    if (TIME_OUT < millis()) {                    \
      CALLBACK;                                   \
      TIME_OUT = millis() + SPEED_CHANG;          \
    }                                             \
    STATE = true;                                 \
  } else if (STATE) {                             \
    STATE = false;                                \
    CALLBACK;                                     \
    buzzeOn();                                    \
  }

void ValueEdit::input() {
  State::input();
  CHECK_KEY(State::Key::K1, stateKey1, timeOutKey1, down());
  CHECK_KEY(State::Key::K2, stateKey2, timeOutKey2, up());
}
