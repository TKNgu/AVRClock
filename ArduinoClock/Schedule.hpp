#ifndef Schedule_hpp
#define Schedule_hpp

class Schedule {
public:
 struct TimePoint {
  unsigned char dayOfWeek;
  unsigned char hour;
  unsigned char minutes;
  unsigned value;
  TimePoint(unsigned char dayOfWeek = 2u, unsigned char hour = 0u,
            unsigned char minutes = 0u)
      : dayOfWeek(dayOfWeek),
        hour(hour),
        minutes(minutes),
        value((dayOfWeek << 11) + (hour << 6) + minutes) {}
 };

public:
 Schedule();
 inline ~Schedule() { delete[] this->timePoints; }
 void resetTimePoint(const TimePoint &);
 bool checkTimePoint(unsigned char, unsigned char, unsigned char);

private:
 TimePoint *nextTimePoint;
 unsigned char indexTimePoint;
 TimePoint *timePoints;
 const unsigned char timePointSize;
};

#endif
