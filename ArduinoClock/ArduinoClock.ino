#include <Arduino.h>

#include "StateManager.hpp"
#include "Utils.hpp"
#include "Clock.hpp"
#include "HourEdit.hpp"
#include "Button.hpp"
#include "MinutesEdit.hpp"

void setup() {
    HardwareInit();
    InitClock();
    InitStateManager(3);
    StateManagerSetState(0, (struct State) {
        .Reload = ClockReload,
        .Loop = ClockShow,
    });
    StateManagerSetState(1, (struct State) {
        .Reload = HourEditReload,
        .Loop = HourEditShow,
    });
    StateManagerSetState(2, (struct State) {
        .Reload = MinutesEditReload,
        .Loop = MinutesEditLoop,
    });
    StateManagerStartState();
    Buzzer();
}


void loop() {
    StateManagerLoop();
}
