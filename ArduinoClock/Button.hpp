#ifndef Button_hpp
#define Button_hpp

#include "Utils.hpp"
#include "Timer.hpp"

#define LONG_PRESS 1000
#define SHORT_PRESS 100

struct Button {
    Key key;
    bool click;
    void (*shortFn)();
    void (*longFn)();
    unsigned long time;
    bool isLongPress;
};

Button CreateButton(const Key key, void (*shortFn)(void));
Button CreateButtonLongPress(const Key key, void (*shortFn)(void), void (*longFn)(void));

void ButtonInit(Button *button, void (*shortFn)(void), void (*longFn)(void));
void ButtonScan(Button *button);
void NOP();

#endif
