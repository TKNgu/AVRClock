#ifndef Clock_hpp
#define Clock_hpp

extern void (*GetTimeCallback)(unsigned char hour, unsigned char minutes);

int ClockInit();
void ClockReload();
void ClockShow();

#endif
