#include "ArduinoClock.hpp"

#include "ClockEdit.hpp"
#include "HourEdit.hpp"
#include "MinutesEdit.hpp"
#include "SleepState.hpp"
#include "StateManager.hpp"
#include "utils/Utils.hpp"

ArduinoClock::ArduinoClock() {}

void ArduinoClock::setup() {
    HardwareInit();
    StateManagerInit(3);
    StateManagerSetState(1, (struct State){
                                .Reload = HourEditReload,
                                .Loop = ClockEditLoop,
                            });
    StateManagerSetState(2, (struct State){
                                .Reload = MinutesEditReload,
                                .Loop = ClockEditLoop,
                            });
    StateManagerSetSleepState((struct State){
        .Reload = SleepStateReload,
        .Loop = SleepStateLoop,
    });
    StateManagerStartState();
}

void ArduinoClock::loop() { StateManagerLoop(); }
