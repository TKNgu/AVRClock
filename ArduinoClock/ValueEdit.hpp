#ifndef ValueEdit_hpp
#define ValueEdit_hpp

#include "State.hpp"

class ValueEdit : public State {
protected:
 inline ValueEdit(State *&nextStete) : State(nextStete){};

 void input(unsigned long) override;
 virtual void up() = 0;
 virtual void down() = 0;

private:
 static bool stateKey1;
 static unsigned long timeOutKey1;
 static bool stateKey2;
 static unsigned long timeOutKey2;
};

#endif
