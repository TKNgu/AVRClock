#ifndef ValueEdit_hpp
#define ValueEdit_hpp

#include "State.hpp"

class ValueEdit : public State {
protected:
 inline ValueEdit(State *&nextStete) : State(nextStete){};

 void input() override;
 virtual void up() = 0;
 virtual void down() = 0;

private:
 static bool stateKey1;
 static long int timeOutKey1;
 static bool stateKey2;
 static long int timeOutKey2;
};

#endif
