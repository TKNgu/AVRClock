#include <Arduino.h>

#include "Utils.hpp"
#include "StateManager.hpp"
#include "Clock.hpp"
#include "ClockEdit.hpp"
#include "HourEdit.hpp"
#include "MinutesEdit.hpp"
#include "SleepState.hpp"
#include "Timer.hpp"
#include "LowPower.h"
#include "Button.hpp"

void setup() {
    HardwareInit();
    StateManagerInit(3);
    StateManagerSetState(0, (struct State) {
        .Reload = ClockReload,
        .Loop = ClockShow,
    });
    StateManagerSetState(1, (struct State) {
        .Reload = HourEditReload,
        .Loop = ClockEditLoop,
    });
    StateManagerSetState(2, (struct State) {
        .Reload = MinutesEditReload,
        .Loop = ClockEditLoop,
    });
    StateManagerSetSleepState((struct State) {
        .Reload = SleepStateReload,
        .Loop = SleepStateLoop,
    });
    ClockInit();
    GetTimeCallback = SleepStateCheck;
    StateManagerStartState();
}

void loop() {
    StateManagerLoop();
}
