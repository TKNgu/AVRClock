#include "src/state/StateManager.hpp"

StateManager stateManager;

void setup() {
  stateManager.setup();
  // Serial.begin(9600);
}

void loop() {
  stateManager.loop();
}
