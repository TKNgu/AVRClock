#include "StateManager.hpp"
#include <stdlib.h>

#include "Utils.hpp"

static unsigned char stateSize = 0;
static struct State* states = NULL;
static unsigned char indexState = 0;

int InitStateManager(unsigned char size) {
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

void StateManagerChangState(unsigned char index) {
    indexState = index;
    states[indexState].Reload();
    Buzzer();
}

void StateManagerNextState() {
    StateManagerChangState(++indexState % stateSize);
}

void StateManagerStartState() { StateManagerChangState(0); }

void StateManagerLoop() { states[indexState].Loop(); }
