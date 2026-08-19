#include "KamaFilter.h"

KamaFilter::KamaFilter(uint8_t period, uint8_t fast, uint8_t slow)
    : period(period), fastSC(fast), slowSC(slow), kama(0), index(0) {
    buffer = new int[period];
}

void KamaFilter::begin(int initialValue) {
    kama = initialValue;
    for (uint8_t i = 0; i < period; i++)
        buffer[i] = initialValue;
}

float KamaFilter::update(int newValue) {
    int past = buffer[(index + 1) % period];
    buffer[index] = newValue;
    index = (index + 1) % period;

    float change = abs(newValue - past);
    float volatility = 0;
    for (uint8_t i = 0; i < period - 1; i++) {
        uint8_t curr = (index + i) % period;
        uint8_t next = (index + i + 1) % period;
        volatility += abs(buffer[next] - buffer[curr]);
    }

    float ER = (volatility != 0) ? change / volatility : 0.0;
    float fastConstant = 2.0f / (float)(this->fastSC + 1);
    float slowConstant = 2.0f / (float)(this->slowSC + 1);
    float SC_raw = ER * (fastConstant - slowConstant) + slowConstant;
    float SC = SC_raw * SC_raw;

    kama = kama + SC * (newValue - kama);
    return kama;
}

float KamaFilter::getValue() { return kama; }
