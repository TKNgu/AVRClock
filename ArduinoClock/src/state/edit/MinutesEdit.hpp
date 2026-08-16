#ifndef MINUTESEDIT2_HPP
#define MINUTESEDIT2_HPP

#include "ClockEdit.hpp"

class MinutesEdit : public ClockEdit {
  public:
    virtual void displayBlinkFrame() override;
    virtual void increaseValue(unsigned char step) override;
    virtual void decreaseValue(unsigned char step) override;
};

#endif // MINUTESEDIT2_HPP
