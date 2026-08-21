#include "src/state/StateManager.hpp"

StateManager stateManager;

void setup() {
  stateManager.setup();
#ifdef DEBUG
  Serial.begin(9600);
#endif
}

void loop() {
  stateManager.loop();
}
