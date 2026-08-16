#include "src/StateManager2.hpp"
#define DEBUG

StateManager2 stateManager;

void setup() {
  stateManager.setUp();
#ifdef DEBUG
  Serial.begin(9600);
#endif
}

void loop() {
  stateManager.loop();
}
