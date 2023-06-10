#ifndef ValueEdit_hpp
#define ValueEdit_hpp

#include "State.hpp"

class ValueEdit : public State {
public:
 ValueEdit(State *&runningState, State *&nextStete) : State(runningState, nextStete){};
 void resume() override;
 void input() override;
 virtual void up() = 0;
 virtual void down() = 0;

private:
 bool stateKey1;
 bool stateKey2;
};

#endif
