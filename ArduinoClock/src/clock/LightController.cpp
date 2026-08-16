#include "LightController.hpp"

#include <Arduino.h>
#include <EEPROM.h>

#include "../utils/Utils.hpp"

#define LIGHT_LEVEL_WARNING 30

MovingMaxFilter::MovingMaxFilter() {
    for (unsigned index = 0; index < SIZE_ITEM; index++) {
        const unsigned offset = index * sizeof(unsigned);
        EEPROM.get(offset, valueMax[index]);
    }
    EEPROM.get(SIZE_ITEM * sizeof(unsigned), valueMaxIndex);
}

float MovingMaxFilter::addValue(unsigned value) {
    valueMaxIndex++;
    if (valueMaxIndex >= SIZE_ITEM) {
        valueMaxIndex = 0;
    }
    EEPROM.put(SIZE_ITEM * sizeof(unsigned), valueMaxIndex);

    if (valueMax[valueMaxIndex] != value) {
        valueMax[valueMaxIndex] = value;
        EEPROM.put(valueMaxIndex * sizeof(unsigned), value);
    }
    return getMovingMax();
}

float MovingMaxFilter::getMovingMax() {
    float avgValueMax = 0.f;
    for (unsigned index = 0; index < SIZE_ITEM; index++) {
        const unsigned indexValue = (valueMaxIndex + index) % SIZE_ITEM;
        avgValueMax += valueMax[indexValue] * valueMaxWeight[index];
    }
    return avgValueMax;
}

LightController::LightController() : movingMaxFilter() {
    maxLightGlobal = movingMaxFilter.getMovingMax();
}

void LightController::updateLoop(const unsigned long now) {
    if (TimerTimeoutFix(&timer, now)) {
        calculateBrightness(GetLight());
        (lightLevel == 0) ? LedOn(led2) : LedOff(led2);
    }
}

void LightController::calculateBrightness(int light) {
    if (light > maxLightLocal) {
        maxLightLocal = light;
    }

    if (maxLightLocal > maxLightGlobal) {
        maxLightGlobal = maxLightLocal;
    }

    if (maxLightGlobal < 1.0f) {
        maxLightGlobal = 1.0f;
    }

    unsigned char tmpLightLevel =
        (unsigned char)(light * 7.0f / maxLightGlobal);
    if (tmpLightLevel != lightLevel) {
        lightLevel = tmpLightLevel;
        SetLightLevel(lightLevel);
    }
}

void LightController::commitDailyMaxLight() {
    maxLightGlobal = movingMaxFilter.addValue(maxLightLocal);
    maxLightLocal = GetLight();
}
