#include "LowFrequence.hpp"

void LowFrequence::input() {
  State::input();
  if (digitalRead(State::Key::K3) == LOW) {
    setDelayTime(20);
  }
}
