#ifndef CLOCKVIEW_HPP
#define CLOCKVIEW_HPP

#include "../../clock/ClockChime.hpp"
#include "../../clock/ClockLight.hpp"
#include "../State.hpp"

class ClockView : public ClockState {
  public:
    virtual void reload() override;
    virtual void loop(unsigned long) override;

  private:
    ClockChime clockChime_;
    ClockLight clockLight_;
};

#endif // CLOCKVIEW_HPP
