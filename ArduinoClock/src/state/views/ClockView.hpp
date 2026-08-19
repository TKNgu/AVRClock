#ifndef CLOCKVIEW_HPP
#define CLOCKVIEW_HPP

#include "../../clock/ChimeController.hpp"
#include "../../clock/LightController.hpp"
#include "../State.hpp"

class ClockView : public ClockState {
  public:
    virtual void reload() override;
    virtual void loop(unsigned long) override;

  private:
    ChimeController chimeController;
    LightController lightController;
};

#endif // CLOCKVIEW_HPP
