#ifndef Temperature_hpp
#define Temperature_hpp

#include "LowFrequence.hpp"

class Temperature : public LowFrequence {
public:
 Temperature(State *&nextState) : LowFrequence(nextState){};

private:
 void update(long int) override {
  auto a = temp.get();
  display.num(a);
 }
};

#endif
