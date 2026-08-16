#ifndef Timer_hpp
#define Timer_hpp

struct Timer {
    unsigned long leng;
    unsigned long nextTime;
};

Timer CreateTimer(unsigned long leng);
void ResetTimer(Timer*, unsigned long);
void ResetTimer(Timer*);
bool TimerTimeoutFix(Timer* timer, unsigned long timeNow);
bool TimerTimeout(Timer* timer);

#endif
