#ifndef ValueEdit_hpp
#define ValueEdit_hpp

#include "State.hpp"

class ValueEdit : public State {
protected:
 inline ValueEdit(State *&nextStete) : State(nextStete){};

 void resume() override;
 void pause() override;
 void input(unsigned long) override;

 virtual void readState() = 0;
 virtual void writeState() = 0;

 virtual void up() = 0;
 virtual void down() = 0;

protected:
 bool isChanged = false;

private:
 static bool stateKey1;
 static unsigned long timeOutKey1;
 static bool stateKey2;
 static unsigned long timeOutKey2;
 static unsigned long timeOut;
};

#endif
