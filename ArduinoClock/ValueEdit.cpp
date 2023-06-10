#include "ValueEdit.hpp"

void ValueEdit::resume() {
  State::resume();
  this->stateKey1 = false;
  this->stateKey2 = false;
}

void ValueEdit::input() {
  State::input();
  if (digitalRead(Key::K2) == LOW) {
    this->stateKey2 = true;
  } else if (this->stateKey2) {
    this->stateKey2 = false;
    up();
  }

  if (digitalRead(Key::K1) == LOW) {
    this->stateKey1 = true;
  } else if (this->stateKey1) {
    this->stateKey1 = false;
    down();
  }
}
