#include "TimePoint.hpp"

void TimePointInit(TimePoint* timePoint, const unsigned char dayOfWeek,
                   const unsigned char hour, const unsigned char minutes) {
    *timePoint = (dayOfWeek << 11) | (hour << 6) | minutes;
}
