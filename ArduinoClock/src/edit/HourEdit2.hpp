#ifndef HOUREDIT2_HPP
#define HOUREDIT2_HPP

#include "ClockEdit2.hpp"

struct HourEdit2 : ClockEdit2 {
    HourEdit2(StateManager2*);

    virtual void show() override;
    virtual void upCallback(int) override;
    virtual void downCallback(int) override;
};

#endif // HOUREDIT2_HPP
