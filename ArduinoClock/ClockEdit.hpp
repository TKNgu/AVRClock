#ifndef ClockEdit_hpp
#define ClockEdit_hpp

extern unsigned char hour;
extern unsigned char minutes;

extern void(*UpCallback)(unsigned char value);
extern void(*DownCallback)(unsigned char value);
extern void(*BlinkCallback)();

void ClockEditReload();
void ClockEditLoop();

#endif
