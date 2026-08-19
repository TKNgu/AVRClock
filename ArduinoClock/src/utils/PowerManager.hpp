#ifndef POWERMANAGER_HPP
#define POWERMANAGER_HPP

class PowerManager {
  public:
    enum SleepTime {
        SLEEP_15MS,
        SLEEP_30MS,
        SLEEP_60MS,
        SLEEP_120MS,
        SLEEP_250MS,
        SLEEP_500MS,
        SLEEP_1S,
        SLEEP_2S,
        SLEEP_4S,
        SLEEP_8S,
        SLEEP_FOREVER
    };

  public:
    unsigned long getMillis();
    void buzzer();
    void sleep(SleepTime);
};

extern PowerManager powerManager;

#endif // POWERMANAGER_HPP
