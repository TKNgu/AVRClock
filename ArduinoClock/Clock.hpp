#ifndef Clock_hpp
#define Clock_hpp

extern void(*StateLoop)(void);

void ChangState(void (*init)(void), void (*loop)(void));

void ClockInit();
void ClockLoop();

void HourEditInit();
void HourEditLoop();

void MinEditInit();
void MinEditLoop();

#endif
