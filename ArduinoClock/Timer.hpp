#ifndef Timer_hpp
#define Timer_hpp

struct Timer {
    unsigned long leng;
    unsigned long nextTime;
};

Timer CreateTimer(unsigned long leng);
bool TimerTimeoutFix(Timer *timer, unsigned long timeNow);
bool TimerTimeout(Timer *timer);

#endif
