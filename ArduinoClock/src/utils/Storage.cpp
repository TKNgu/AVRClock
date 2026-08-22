#include "Storage.hpp"

#include <EEPROM.h>

constexpr unsigned LIGHT_OFFSET = 0;
#define MAX_LIGHT_LEVEL 1000
constexpr unsigned TIME_SCALE_OFFSET =
    sizeof(unsigned) * SIZE_ITEM + sizeof(unsigned);

Storage storage;

void Storage::loadLight(MovingMaxFilter* const movingMaxFilter) {
    for (unsigned index = 0; index < SIZE_ITEM; index++) {
        const unsigned offset = index * sizeof(unsigned) + LIGHT_OFFSET;
        EEPROM.get(offset, movingMaxFilter->valueMax[index]);
        if (movingMaxFilter->valueMax[index] > MAX_LIGHT_LEVEL) {
            movingMaxFilter->valueMax[index] = 0;
        }
    }
    EEPROM.get(SIZE_ITEM * sizeof(unsigned) + LIGHT_OFFSET,
               movingMaxFilter->valueMaxIndex);
}

void Storage::saveLightIndex(unsigned index) {
    EEPROM.put(SIZE_ITEM * sizeof(unsigned) + LIGHT_OFFSET, index);
}

void Storage::saveLightValue(unsigned index, unsigned value) {
    EEPROM.put(index * sizeof(unsigned) + LIGHT_OFFSET, value);
}

float Storage::getWDTScale() {
    float scale;
    EEPROM.get(TIME_SCALE_OFFSET, scale);
    if (scale < 0.5f || scale > 1.5f) {
        scale = 1.0f;
    }
    return scale;
}

void Storage::saveWDTScale(float scale) {
    EEPROM.put(TIME_SCALE_OFFSET, scale);
}
