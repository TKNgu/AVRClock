#ifndef BUTTON2_HPP
#define BUTTON2_HPP

#include "Utils.hpp"

struct Button2 {
    enum State {
        Idle,
        Click,
        LongPress,
    };

    Key key;
    State state = Idle;
    unsigned long time;

    Button2(Key key);
    State scan();
    State scan(unsigned long now);
};

#endif // BUTTON2_HPP
