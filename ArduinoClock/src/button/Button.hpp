#ifndef BUTTON2_HPP
#define BUTTON2_HPP

#include "../utils/Utils.hpp"

struct Button {
    enum State {
        Idle,
        Click,
        LongPress,
    };

    Key key;
    State state = Idle;
    unsigned long time;

    Button(Key key);
    State scan(unsigned long now);
    bool isPress();
};

#endif // BUTTON2_HPP
