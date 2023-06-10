#ifndef State_hpp
#define State_hpp

class State {
public:
 inline State(State *&state) : state(state){};
 virtual ~State(){};
 virtual void resume(){};
 inline virtual void changState(State *state) { (this->state = state)->resume(); }
 virtual void loop() = 0;

private:
 State *&state;
};

#endif
