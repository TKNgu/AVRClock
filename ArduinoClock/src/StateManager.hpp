#ifndef StateManager_hpp
#define StateManager_hpp

struct State {
    void (*Reload)(void);
    void (*Loop)(void);
};

int StateManagerInit(unsigned char size);
int StateManagerSetState(unsigned char index, struct State state);
void StateManagerSetSleepState(struct State state);

void StateManagerNextState();
void StateManagerStartState();
void StateManagerSleepState();

void StateManagerLoop();

#endif
