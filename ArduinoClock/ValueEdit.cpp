#include "ValueEdit.hpp"

#define TIME_OUT_SPEED_CHANG 500
#define SPEED_CHANG 250

bool ValueEdit::stateKey1 = false;
unsigned long ValueEdit::timeOutKey1 = 0;
bool ValueEdit::stateKey2 = false;
unsigned long ValueEdit::timeOutKey2 = 0;
unsigned long ValueEdit::timeOut;

void ValueEdit::resume() {
  State::resume();
  timeOut = State::pointTime;
  readState();
}

void ValueEdit::pause() {
  State::pause();
  clockShield.clear();
  if (this->isChanged) {
    writeState();
    this->isChanged = false;
  }
}

#define CHECK_KEY(KEY_STATE, STATE, TIME_OUT, TIME_NOW, CALLBACK) \
  if (KEY_STATE) {                                                \
    if (!STATE) {                                                 \
      TIME_OUT = TIME_NOW + TIME_OUT_SPEED_CHANG;                 \
    }                                                             \
    if (TIME_OUT < TIME_NOW) {                                    \
      this->isChanged = true;                                     \
      CALLBACK;                                                   \
      timeOut = timeNow;                                          \
      TIME_OUT = TIME_NOW + SPEED_CHANG;                          \
    }                                                             \
    STATE = true;                                                 \
  } else if (STATE) {                                             \
    STATE = false;                                                \
    this->isChanged = true;                                       \
    CALLBACK;                                                     \
    timeOut = timeNow;                                            \
  }

void ValueEdit::input(unsigned long timeNow) {
  State::input(timeNow);
  CHECK_KEY(clockShield.digitalReadDown(), stateKey1, timeOutKey1, timeNow,
            down());
  CHECK_KEY(clockShield.digitalReadUp(), stateKey2, timeOutKey2, timeNow, up());
  if (timeOut < timeNow - 3000) {
    changDefault();
  }
}
