#ifndef HOUREDIT2_HPP
#define HOUREDIT2_HPP

#include "ClockEdit.hpp"

class HourEdit : public ClockEdit {
  public:
    virtual void displayBlinkFrame() override;
    virtual void increaseValue(unsigned char step) override;
    virtual void decreaseValue(unsigned char step) override;
};

#endif // HOUREDIT2_HPP
