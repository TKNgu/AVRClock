#ifndef ButtonState_hpp
#define ButtonState_hpp

class ButtonState
{
public:
  bool updateState(bool);
  bool inline getState()
  {
    return this->state;
  }

private:
  bool state = false;
};

#endif