#ifndef Schedule_hpp
#define Schedule_hpp

class Schedule {
 public:
  struct TimePoint {
    unsigned char dayOfWeek;
    unsigned char hour;
    unsigned char minutes;
    unsigned value;
    TimePoint(unsigned char dayOfWeek = 0u, unsigned char hour = 0u,
              unsigned char minutes = 0u)
        : dayOfWeek(dayOfWeek),
          hour(hour),
          minutes(minutes),
          value((dayOfWeek << 11) + (hour << 6) + minutes) {}
  };

 public:
  TimePoint *nextSchedule;
  unsigned char indexSchedule;
  TimePoint *schedules;
  const unsigned char schedulesSize;

 public:
  Schedule();
  void resetPoint(unsigned char, unsigned char, unsigned char);
  bool checkPoint(unsigned char, unsigned char, unsigned char);
};

#endif
