#ifndef State_hpp
#define State_hpp

class State
{
public:
  State(State *&state) : state(state){};
  virtual ~State(){};
  inline void changState(State *state)
  {
    this->state = state;
  }
  virtual void loop(long int) = 0;

private:
  State *&state;
};

#endif