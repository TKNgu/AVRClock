#ifndef KAMA_FILTER_H
#define KAMA_FILTER_H

#include <Arduino.h>

class KamaFilter {
public:
    KamaFilter(uint8_t period = 10, uint8_t fast = 2, uint8_t slow = 30);
    ~KamaFilter() { delete[] _buffer; }
    
    // Prevent copying because we have raw pointers
    KamaFilter(const KamaFilter&) = delete;
    KamaFilter& operator=(const KamaFilter&) = delete;

    void begin(int initialValue);
    float update(int newValue);
    float getValue();

private:
    uint8_t _period, _fastSC, _slowSC;
    float _kama;
    int *_buffer;
    int _index;
};

#endif
