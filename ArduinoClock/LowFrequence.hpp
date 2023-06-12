#ifndef LowFrequence_hpp
#define LowFrequence_hpp

#include "State.hpp"

class LowFrequence : public State {
public:
 LowFrequence(State *&nextState) : State(nextState) {}

protected:
 inline void resume() override { setDelayTime(50); }

 void input() override;
};

#endif
