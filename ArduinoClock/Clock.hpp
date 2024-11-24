#ifndef Clock_hpp
#define Clock_hpp

extern void(*StateLoop)(void);
void ChangState(void (*reload)(void), void (*loop)(void));

void ClockInit();
void ClockReload();
void ClockLoop();

void HourEditReload();
void HourEditLoop();

void MinEditReload();
void MinEditLoop();

#endif
