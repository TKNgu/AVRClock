#include "src/clock/ClockChime.hpp"
#include "src/clock/ClockEngine.hpp"
#include "src/clock/ClockLight.hpp"
#include "src/state/StateManager.hpp"
#include "src/state/edit/HourEdit.hpp"
#include "src/state/edit/MinutesEdit.hpp"
#include "src/state/views/ClockSleep.hpp"
#include "src/state/views/ClockView.hpp"
#define DEBUG

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
