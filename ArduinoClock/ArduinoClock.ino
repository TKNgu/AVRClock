#include "HourEdit.hpp"
#include "MinEdit.hpp"
#include "ShowTime.hpp"
#include "State.hpp"

State *running;
State *showTime;
State *hourEdit;
State *minEdit;

void setup() {
 showTime = new ShowTime(running, hourEdit);
 hourEdit = new HourEdit(running, minEdit);
 minEdit = new MinEdit(running, showTime);

 running = showTime;
 running->resume();
}

void loop() {
 running->loop();
}

