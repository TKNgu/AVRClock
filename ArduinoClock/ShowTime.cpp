#include "ShowTime.hpp"

void ShowTime::on() {
  display.time(time.getHour(), time.getMin());
  display.pointOn();
}
