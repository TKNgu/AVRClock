#include "ClockLight.hpp"

#include <Arduino.h>
#include <EEPROM.h>

#include "../utils/Utils.hpp"

#define LIGHT_LEVEL_WARNING 30

ArrayMax::ArrayMax() {
    for (unsigned index = 0; index < SIZE_ITEM; index++) {
        const unsigned offset = index * sizeof(unsigned);
        EEPROM.get(offset, valueMax[index]);
    }
    EEPROM.get(SIZE_ITEM * sizeof(unsigned), valueMaxIndex);
}

float ArrayMax::update(unsigned value) {
    valueMaxIndex++;
    if (valueMaxIndex >= SIZE_ITEM) {
        valueMaxIndex = 0;
    }
    EEPROM.put(SIZE_ITEM * sizeof(unsigned), valueMaxIndex);

    if (valueMax[valueMaxIndex] != value) {
        valueMax[valueMaxIndex] = value;
        EEPROM.put(valueMaxIndex * sizeof(unsigned), value);
    }
    return getValueMax();
}

float ArrayMax::getValueMax() {
    float avgValueMax = 0.f;
    for (unsigned index = 0; index < SIZE_ITEM; index++) {
        const unsigned indexValue = (valueMaxIndex + index) % SIZE_ITEM;
        avgValueMax += valueMax[indexValue] * valueMaxWeight[index];
    }
    return avgValueMax;
}

ClockLight::ClockLight() : arrayMax() {
    maxLightGlobal = arrayMax.getValueMax();
}

void ClockLight::check(const unsigned long now) {
    if (TimerTimeoutFix(&timer, now)) {
        update(GetLight());
        (lightLevel == 0) ? LedOn(led2) : LedOff(led2);
    }
}

void ClockLight::update(int light) {
    if (light > maxLightLocal) {
        maxLightLocal = light;
    }

    if (maxLightLocal > maxLightGlobal) {
        maxLightGlobal = maxLightLocal;
    }

    unsigned char tmpLightLevel =
        (unsigned char)(light * 7.0f / maxLightGlobal);
    if (tmpLightLevel != lightLevel) {
        lightLevel = tmpLightLevel;
        SetLightLevel(lightLevel);
    }
}

void ClockLight::updateGlobal() {
    maxLightGlobal = arrayMax.update(maxLightLocal);
    maxLightLocal = GetLight();
}
