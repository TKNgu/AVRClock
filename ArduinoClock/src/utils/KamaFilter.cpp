#include "KamaFilter.h"

KamaFilter::KamaFilter(uint8_t period, uint8_t fast, uint8_t slow)
    : _period(period), _fastSC(fast), _slowSC(slow), _kama(0), _index(0) {
    _buffer = new int[_period];
}

void KamaFilter::begin(int initialValue) {
    _kama = initialValue;
    for (uint8_t i = 0; i < _period; i++)
        _buffer[i] = initialValue;
}

float KamaFilter::update(int newValue) {
    int past = _buffer[(_index + 1) % _period];
    _buffer[_index] = newValue;
    _index = (_index + 1) % _period;

    float change = abs(newValue - past);
    float volatility = 0;
    for (uint8_t i = 1; i < _period; i++) {
        volatility += abs(_buffer[i] - _buffer[i - 1]);
    }

    float ER = (volatility != 0) ? change / volatility : 0.0;
    float fastSC = 2.0 / (_fastSC + 1);
    float slowSC = 2.0 / (_slowSC + 1);
    float SC = pow((ER * (fastSC - slowSC) + slowSC), 2);

    _kama = _kama + SC * (newValue - _kama);
    return _kama;
}

float KamaFilter::getValue() { return _kama; }
