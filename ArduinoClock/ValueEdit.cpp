#include "ValueEdit.hpp"

bool ValueEdit::stateKey1 = false;
bool ValueEdit::stateKey2 = false;

#define CHECK_KEY(KEY, STATE, CALLBACK) \
  if (digitalRead(KEY) == LOW) {        \
    STATE = true;                       \
  } else if (STATE) {                   \
    STATE = false;                      \
    CALLBACK;                           \
  }

void ValueEdit::input() {
  State::input();
  CHECK_KEY(State::Key::K1, this->stateKey1, down());
  CHECK_KEY(State::Key::K2, this->stateKey2, up());
}
