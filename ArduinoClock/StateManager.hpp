#ifndef StateManager_hpp
#define StateManager_hpp

struct State {
    void (*Reload)(void);
    void (*Loop)(void);
};

int InitStateManager(unsigned char size);
int StateManagerSetState(unsigned char index, struct State state);
void StateManagerNextState();
void StateManagerStartState();
void StateManagerLoop();

#endif
