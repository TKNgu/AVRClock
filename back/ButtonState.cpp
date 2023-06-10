#include "ButtonState.hpp"

bool ButtonState::updateState(bool tmp)
{
  if (tmp)
  {
    this->state = true;
  }
  else if (this->state)
  {
    this->state = false;
    return true;
  }
  return false;
}