#ifndef MINUTESEDIT2_HPP
#define MINUTESEDIT2_HPP

#include "ClockEdit2.hpp"

struct MinutesEdit2 : ClockEdit2 {
    MinutesEdit2(StateManager2*);

    virtual void show() override;
    virtual void upCallback(int) override;
    virtual void downCallback(int) override;
};

#endif // MINUTESEDIT2_HPP
