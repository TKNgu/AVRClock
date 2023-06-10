#ifndef Temperature_hpp
#define Temperature_hpp

#include "LowFrequence.hpp"

class Temperature final : public LowFrequence {
public:
 inline Temperature(State *&nextState, State *&showTime) : LowFrequence(nextState), showTime(showTime) {
  setDelayTime(250);
 };

private:
 void resume() override;
 void update(long int) override;

private:
 State *&showTime;
 long int timeOut;
};

#endif
