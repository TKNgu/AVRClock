#include "PowerManager.hpp"
#include <Arduino.h>

#define BUZZER_DEVICE 6

PowerManager powerManager;

unsigned long PowerManager::getMillis() { return millis(); }

void PowerManager::buzzer() { tone(BUZZER_DEVICE, 2400, 60); }

void PowerManager::sleep(SleepTime sleepTime) { delay(100); }
