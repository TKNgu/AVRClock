#ifndef Timer_hpp
#define Timer_hpp

#include <stdbool.h>

typedef struct {
    unsigned long leng;
    unsigned long nextTime;
} Timer;

bool TimerTimeoutFix(Timer *timer, unsigned long timeNow);
bool TimerTimeout(Timer *timer);

#endif