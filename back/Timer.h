#ifndef Timer_h
#define Timer_h

#include <stdbool.h>

typedef unsigned long Timer;

void TimerSet(Timer *timer, unsigned long next);
bool TimerTimeout(const Timer timer);

#endif
