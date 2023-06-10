#ifndef ClockShield_hpp
#define ClockShield_hpp

#include "TTSTime.h"
#include "TTSDisplay.h"

class ClockShield
{
public:
    virtual ~ClockShield(){};

protected:
    TTSTime time;
    TTSDisplay display;
};

#endif