#include "StateManager.hpp"
#include <Arduino.h>
#include <stdlib.h>

#include "Utils.hpp"

#define DELAY_TIME_SLEEP 5000

static unsigned char stateSize = 0;
static struct State* states = NULL;
static unsigned char indexState = 0;

static unsigned long timePoint;
static struct State sleepState;
static bool isNeedSleep = false;
static bool isSleep = false;

int StateManagerInit(unsigned char size) {
    stateSize = size;
    states = (struct State*)malloc(stateSize * sizeof(struct State));
    return !states;
}

int StateManagerSetState(unsigned char index, struct State state) {
    if (index >= stateSize) {
        return 1;
    }
    states[index] = state;
    return 0;
}

void StateManagerSetSleepState(struct State state) { sleepState = state; }

void StateManagerChangState(unsigned char index) {
    Buzzer();
    timePoint = millis();
    isSleep = false;
    states[indexState = index].Reload();
}

void StateManagerNextState() {
    StateManagerChangState(++indexState % stateSize);
}

void StateManagerStartState() { StateManagerChangState(0); }

void StateManagerSleepState() { isNeedSleep = !isSleep; }

void StateManagerLoop() {
    if (isNeedSleep) {
        static unsigned long now;
        now = millis();
        if (timePoint + DELAY_TIME_SLEEP < now) {
            isNeedSleep = false;
            isSleep = true;
            sleepState.Reload();
        }
    }
    isSleep ? sleepState.Loop() : states[indexState].Loop();
}
