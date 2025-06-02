#ifndef TimePoint_hpp
#define TimePoint_hpp

typedef unsigned int TimePoint;

void TimePointInit(TimePoint *timePoint,
    const unsigned char dayOfWeek,
    const unsigned char hour,
    const unsigned char minutes);

#endif
