#include "src/ArduinoClock.hpp"

#include "src/StateManager2.hpp"

// ArduinoClock clock;
StateManager2 stateManager;

void setup() {
  // clock.setup();
  stateManager.setUp();
}

void loop() {
  // clock.loop();
  stateManager.loop();
}
