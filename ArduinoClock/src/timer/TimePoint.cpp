#include "TimePoint.hpp"

TimePoint TimePointInit(const unsigned char dayOfWeek, const unsigned char hour,
                        const unsigned char minutes) {
    return dayOfWeek * 24 * 60 + hour * 60 + minutes;
}
